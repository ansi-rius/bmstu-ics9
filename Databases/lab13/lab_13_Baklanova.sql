--Задание 13. Создание распределенных баз данных на основе секционированных представлений
--1. Создать две базы данных на одном экземпляре СУБД SQL Server 2012.
USE master;
GO
--удаление БД
IF DB_ID (N'Lab13_1') IS NOT NULL
DROP DATABASE Lab13_1;
GO
--создание БД
CREATE DATABASE Lab13_1
ON ( NAME = Lab13_1_dat,
FILENAME = '/Users/anemone/sqltest/lab113-1.mdf',
SIZE = 10, MAXSIZE = 150, FILEGROWTH = 5% )
LOG ON ( NAME = Lab13_1_log,
FILENAME = '/Users/anemone/sqltest/lab113-1.ldf',
SIZE = 5MB, MAXSIZE = 150MB, FILEGROWTH = 5MB )
GO

--------------------

USE master;
GO
--удаление БД
IF DB_ID (N'Lab13_2') IS NOT NULL
DROP DATABASE Lab13_2;
GO
--создание БД
CREATE DATABASE Lab13_2
ON ( NAME = Lab13_2_dat,
FILENAME = '/Users/anemone/sqltest/lab13-2.mdf',
SIZE = 10, MAXSIZE = 150, FILEGROWTH = 5% )
LOG ON ( NAME = Lab13_2_log,
FILENAME = '/Users/anemone/sqltest/lab13-2.ldf',
SIZE = 5MB, MAXSIZE = 150MB, FILEGROWTH = 5MB )
GO

--2. Создать в базах данных п.1. горизонтально фрагментированные таблицы.
USE Lab13_1
GO
--удаление таблицы
IF OBJECT_ID (N'Author') IS NOT NULL
DROP TABLE Author;
GO
--Создание горизонтальной фрагментации
CREATE TABLE Author (
    AuthorID    INT PRIMARY KEY   NOT NULL CHECK (AuthorID < 50),
    FirstName     VARCHAR(50)     NOT NULL,
    LastName      VARCHAR(50)     NOT NULL,
    DateOfBirth      DATE         NOT NULL,
    AuthorAddress VARCHAR(80)     NOT NULL
)

INSERT INTO Author(AuthorID,  FirstName, LastName, DateOfBirth, AuthorAddress)
    VALUES  (1, 'Nikolay', 'Zadorozniy', '01-jan-2001', 'Moscow'),
	        (2, 'Alexander', 'Pusheen', '02-feb-2002', 'Volgograd');


USE Lab13_2
GO
--Создание горизонтальной фрагментации

--удаление таблицы
IF OBJECT_ID (N'Author') IS NOT NULL
DROP TABLE Author;
GO
CREATE TABLE Author (
    AuthorID    INT PRIMARY KEY   NOT NULL CHECK (AuthorID > 50),
    FirstName     VARCHAR(50)     NOT NULL,
    LastName      VARCHAR(50)     NOT NULL,
    DateOfBirth      DATE         NOT NULL,
    AuthorAddress VARCHAR(80)     NOT NULL
)

INSERT INTO Author(AuthorID,  FirstName, LastName, DateOfBirth, AuthorAddress)
    VALUES  (53, 'Ekaterina', 'Velikaya', '03-mar-2003', 'Saint Petersburg'),
	        (54, 'Ernest', 'Skobinsky', '04-apr-2004', 'Saint Petersburg');

--3. Создать секционированные представления, обеспечивающие работу с данными таблиц
--(выборку, вставку, изменение, удаление).

USE Lab13_2;
GO

IF OBJECT_ID(N'All_Authors') IS NOT NULL
    DROP VIEW All_Authors;
GO

CREATE VIEW All_Authors
AS
    SELECT * FROM Lab13_2.dbo.Author
    UNION ALL
    SELECT * FROM Lab13_1.dbo.Author
GO
SELECT * FROM All_Authors;
GO

USE Lab13_1;
GO

IF OBJECT_ID(N'All_Authors') IS NOT NULL
    DROP VIEW All_Authors;
GO

CREATE VIEW All_Authors
AS
    SELECT * FROM lab13_2.dbo.Author
    UNION ALL
    SELECT * FROM lab13_1.dbo.Author
GO
SELECT * FROM All_Authors;
GO

INSERT INTO lab13_1.dbo.All_Authors VALUES
    (3, 'Lubov', 'Romanova', '13-mar-2013', 'Ekaterinburg'),
    (55, 'Veliki', 'Author', '30-may-1999', 'Nowhere')
GO
SELECT * FROM All_Authors;
GO

UPDATE All_Authors
    SET AuthorAddress = 'In the middle of nowhere'
    WHERE AuthorID = 53;

DELETE FROM All_Authors
WHERE AuthorID = 1


SELECT * FROM All_Authors;
GO