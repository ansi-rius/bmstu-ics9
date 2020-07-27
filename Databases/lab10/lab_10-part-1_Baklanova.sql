USE master;
GO
--удаление БД
IF DB_ID (N'Lab10') IS NOT NULL
DROP DATABASE Lab10;
GO

--создание БД
CREATE DATABASE Lab10
ON ( NAME = Lab10_dat,
FILENAME = '/Users/anemone/sqltest/salesdat3.mdf',
SIZE = 10, MAXSIZE = 150, FILEGROWTH = 5% )
LOG ON ( NAME = Lab10_log,
FILENAME = '/Users/anemone/sqltest/salelog3.ldf',
SIZE = 5MB, MAXSIZE = 150MB, FILEGROWTH = 5MB )
GO

USE Lab10;
GO

IF OBJECT_ID (N'Table1') IS NOT NULL
DROP TABLE Table1;
GO
--
CREATE TABLE Table1(
    Id INT IDENTITY,
    value INT
    );
GO

INSERT INTO Table1 (Value) VALUES (1)
--

-- незавершенное чтение(readuncommited); – завершенное чтение(readcommited);
-- воспроизводимое чтение(repeatableread); – сериализуемость(serializable);

--потерянное обновление

BEGIN TRAN; -- (6) - 8 value во временной переменной

DECLARE @Value INT;

SELECT @Value = Value
FROM Table1
WHERE Id = 1;

WAITFOR DELAY '00:00:06';

UPDATE Table1 
SET Value = @Value + 5
WHERE Id = 1;

COMMIT TRAN;

SELECT Value 
FROM Table1
WHERE Id = 1;
*/
--

UPDATE Table1 --рестарт
SET Value = 1
WHERE Id = 1;
*/
----------
----------


--«Грязное» чтение (dirty read)
--при нем могут быть считаны добавленные или изменённые данные из 
--другой транзакции, которая впоследствии не подтвердится (откатится).
--Так как данный эффект возможен только при минимальном уровне изоляции, а по умолчанию используется более 
--высокий уровень изоляции (READ COMMITTED), то в скрипте чтения данных уровень изоляции будет 
--явно установлен как READ UNCOMMITTED.

BEGIN TRAN; --всегда 1

UPDATE Table1
SET Value = Value * 10
WHERE Id = 1;

WAITFOR DELAY '00:00:06';

ROLLBACK;

SELECT Value 
FROM Table1
WHERE Id = 1;
*/

----------
----------


--Неповторяющееся чтение (non-repeatable read)
--когда при повторном чтении в рамках одной транзакции, ранее прочитанные данные, оказываются изменёнными.
-- Данный эффект может наблюдаться при уровне изоляции ниже, чем REPEATABLE READ.


--SET TRANSACTION ISOLATION LEVEL READ COMMITTED -- 1 -- 42 мгновенное выполнение
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ -- 1 -- 1 ожидание завершения первой транзакции
BEGIN TRAN;

SELECT Value 
FROM Table1
WHERE Id = 1;

WAITFOR DELAY '00:00:06';

SELECT Value 
FROM Table1
WHERE Id = 1;

COMMIT;
*/

----------
----------


--Фантомное чтение (phantom reads)
--когда одна транзакция в ходе своего выполнения несколько раз выбирает множество
--строк по одним и тем же критериям. При этом другая транзакция в интервалах между этими выборками
--производит некие действия, используемых в критериях выборки первой транзакции, и успешно заканчивается.
--В результате получится, что одни и те же выборки в первой транзакции дают разные множества строк.

--SET TRANSACTION ISOLATION LEVEL REPEATABLE READ --мгновенное выполнение
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE --ожидание завершения транзакции 1
BEGIN TRAN;

SELECT * FROM Table1  -- 1 -- 1         -- 1 -- 1

WAITFOR DELAY '00:00:10'  

SELECT * FROM Table1 -- 1 -- 1          -- 1 -- 1
                     -- 2 -- 100
COMMIT;

*/


