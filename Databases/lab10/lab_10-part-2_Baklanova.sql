USE Lab10;
GO

--
--потерянное обновление
BEGIN TRAN; -- 6 - (8) value во временной переменной

DECLARE @Value INT;

SELECT @Value = Value
FROM Table1
WHERE Id = 1;

UPDATE Table1 
SET Value = @Value + 7
WHERE Id = 1;

COMMIT TRAN;

SELECT Value 
FROM Table1
WHERE Id = 1;
*/

----------
----------

--Грязное чтение
--SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED; -- 1 - 10(не было успешно сохранено в базу(оно было отклонено командой Rollback))
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;  -- 1 - 1

BEGIN TRAN;

SELECT Value 
FROM Table1
WHERE Id = 1;

COMMIT TRAN;
*/

----------
----------

--неповторяющееся чтение
BEGIN TRAN;

UPDATE Table1 
SET Value = 42
WHERE Id = 1;

SELECT Value 
FROM Table1
WHERE Id = 1;

COMMIT TRAN;
*/

----------
----------


--фантомное чтение
BEGIN TRAN;

INSERT INTO Table1 (Value)
VALUES(100)

SELECT Value 
FROM Table1
WHERE Id = 1;

COMMIT TRAN;

*/

BEGIN TRAN  
    UPDATE t_lock SET c1 = 10  