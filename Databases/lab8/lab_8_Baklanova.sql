USE master;
GO
--удаление БД
IF DB_ID (N'Lab81') IS NOT NULL
DROP DATABASE Lab81;
GO

--создание БД
CREATE DATABASE Lab81
ON ( NAME = Lab81_dat,
FILENAME = '/Users/anemone/sqltest/salesdat2.mdf',
SIZE = 10, MAXSIZE = 150, FILEGROWTH = 5% )
LOG ON ( NAME = Lab81_log,
FILENAME = '/Users/anemone/sqltest/salelog2.ldf',
SIZE = 5MB, MAXSIZE = 150MB, FILEGROWTH = 5MB )
GO

USE Lab81;
GO

IF OBJECT_ID (N'Book') IS NOT NULL
DROP TABLE Book;
GO
--таблица с первичным ключом на основе последовательности
CREATE TABLE Book(
    BookId int PRIMARY KEY,
    BookName VARCHAR(50) NOT NULL,
    Year int NULL,
    Country VARCHAR(50) NULL,
    Genre VARCHAR (50) NULL,
    AuthorBirthDate DATE NULL
    );
GO

IF OBJECT_ID (N'CountBy') IS NOT NULL
DROP SEQUENCE CountBy;
GO
CREATE SEQUENCE CountBy
START WITH 1
INCREMENT BY 1;
GO

INSERT Book (BookId, BookName, Year, Country, Genre, AuthorBirthDate)
VALUES (NEXT VALUE FOR CountBy, 'Dark Avenues', 2013, 'Rus', 'Story', '19640622');
INSERT Book (BookId, BookName, Year, Country, Genre, AuthorBirthDate)
VALUES (NEXT VALUE FOR CountBy, '1984', 1949, 'UK', 'Dystopian', '19030625');
INSERT Book (BookId, BookName, Year, Country, Genre, AuthorBirthDate)
VALUES (NEXT VALUE FOR CountBy, 'Pride and prejudice', 1945, 'UK', 'Romance', '19030625');
INSERT Book (BookId, BookName, Year, Country, Genre, AuthorBirthDate)
VALUES (NEXT VALUE FOR CountBy, 'Crime and Punishment', 1719, 'Rus', 'Phylosophy', '16600101');
GO

SELECT * FROM Book
GO

-------------------------------------------1-------------------------------------------
--Создать хранимую процедуру, производящую выборку из некоторой таблицы и 
--возвращающую результат выборки в виде курсора.
IF OBJECT_ID ('dbo.proc1', 'P') IS NOT NULL
DROP PROCEDURE dbo.proc1;
GO

CREATE PROCEDURE dbo.proc1
    @procCursor CURSOR VARYING OUTPUT
AS
    SET @procCursor = CURSOR
    FORWARD_ONLY STATIC FOR
        SELECT BookName, Genre
        FROM Book;
        OPEN @procCursor;   
GO

DECLARE @Mycursor CURSOR;
DECLARE @BookNameCursor1 VARCHAR(30);
DECLARE @BookGenreCursor1 VARCHAR(30);
EXEC dbo.proc1 @procCursor = @Mycursor
    OUTPUT;
    FETCH NEXT FROM @Mycursor INTO @BookNameCursor1, @BookGenreCursor1;    --позиционирование курсора
WHILE (@@FETCH_STATUS = 0)
BEGIN;
    SELECT @BookNameCursor1 AS Name, @BookGenreCursor1 AS Genre; --Вывод со 2 строки
    FETCH NEXT FROM @Mycursor INTO @BookNameCursor1, @BookGenreCursor1;    --позиционирование курсора
    
END;
CLOSE @Mycursor;    --закрытие курсора очищает текущий результирующий набор, связанный с курсором.
DEALLOCATE @Mycursor;  --удаление курcора освобождает ресурсы, используемые курсором.
GO

--EXECUTE dbo.proc1;

-------------------------------------------2-------------------------------------------
--Модифицировать хранимую процедуру п.1. таким образом, чтобы выборка осуществлялась с
--формированием столбца, значение которого формируется пользовательской функцией.

IF OBJECT_ID ('dbo.FunctionTask2', 'F') IS NOT NULL
DROP FUNCTION dbo.FunctionTask2
GO

CREATE FUNCTION dbo.FunctionTask2 (@BookID int, @Year int)
RETURNS int
AS
BEGIN
	DECLARE @ret int;
	SELECT @ret = @BookID + @Year
RETURN @ret
END;

GO


ALTER PROCEDURE dbo.proc1 @procCursor CURSOR VARYING OUTPUT
AS
SET @procCursor = CURSOR FOR SELECT BookName,dbo.FunctionTask2(BookId, Year) as YearIdSum FROM Book;
OPEN @procCursor
GO

DECLARE @bookCursor2 CURSOR;
DECLARE @bookNameCursor2 VARCHAR(200);
DECLARE @bookGenreCursor2 INTEGER;

EXEC dbo.proc1 @procCursor= @bookCursor2 OUTPUT;
UPDATE Book SET Genre = '\n' WHERE BookName = 'Dark Avenues';
FETCH NEXT FROM @bookCursor2 into @bookNameCursor2, @bookGenreCursor2;
WHILE (@@FETCH_STATUS = 0)
    BEGIN;
        SELECT @bookNameCursor2 AS Book_Name, @bookGenreCursor2 AS YearIdSum;
        FETCH NEXT FROM @bookCursor2 into @bookNameCursor2, @bookGenreCursor2;
    END;
CLOSE @bookCursor2;
DEALLOCATE @bookCursor2;
GO

-------------------------------------------3-------------------------------------------
--Создать хранимую процедуру, вызывающую процедуру п.1., осуществляющую прокрутку возвращаемого
--курсора и выводящую сообщения, сформированные из записей при выполнении условия, заданного еще одной
--пользовательской функцией.
IF OBJECT_ID ('dbo.FunctionTask3', 'F') IS NOT NULL
DROP FUNCTION dbo.FunctionTask3
GO

CREATE FUNCTION FunctionTask3(@Name varchar(50)) 
RETURNS INT
AS BEGIN
    IF @Name = '1984'
    RETURN 1;
    RETURN 0;
END;
GO

IF OBJECT_ID ('dbo.proc3', 'P') IS NOT NULL
DROP PROCEDURE dbo.proc3;
GO

CREATE PROCEDURE dbo.proc3
AS
DECLARE @Mycursor CURSOR;
DECLARE @BookNameCursor1 VARCHAR(200), @BookGenreCursor1 VARCHAR(80);
EXEC dbo.proc1 @procCursor= @Mycursor OUTPUT;
FETCH NEXT FROM @Mycursor into @BookNameCursor1, @BookGenreCursor1;
WHILE (@@FETCH_STATUS = 0)
    BEGIN
        IF (dbo.FunctionTask3(@BookNameCursor1) = 1)
            PRINT ' Name: ' + @BookNameCursor1;

        SELECT dbo.FunctionTask3(@BookNameCursor1) AS task3_name;

        FETCH NEXT FROM @Mycursor into @BookNameCursor1, @BookGenreCursor1;
    END;
CLOSE @Mycursor;
DEALLOCATE @Mycursor;
GO

EXEC dbo.proc3;
GO

-------------------------------------------4-------------------------------------------
--Модифицировать хранимую процедуру п.2. таким образом, чтобы выборка формировалась с помощью
--табличной функции.

IF OBJECT_ID ('dbo.FunctionTask4', 'F') IS NOT NULL
DROP FUNCTION dbo.FunctionTask4
GO

CREATE FUNCTION dbo.FunctionTask4(@min_year INTEGER) RETURNS TABLE    --inline function
AS RETURN(
    SELECT BookName,dbo.FunctionTask2(Year, BookId) as year_id_sum FROM Book WHERE Year > @min_year
);
GO

CREATE FUNCTION dbo.FunctionTask4d(@min_year INTEGER) RETURNS @sum_res TABLE   --не inline function
(
    NameOfBook VARCHAR(200) NOT NULL,
    YearIdSum INTEGER NOT NULL
)
AS
BEGIN
    INSERT @sum_res SELECT BookName,dbo.FunctionTask2(Year, BookId) as year_sum FROM Book WHERE Year > @min_year;
    RETURN
END;
GO    

IF OBJECT_ID ('dbo.proc4', 'P') IS NOT NULL
DROP PROCEDURE dbo.proc4
GO

CREATE PROCEDURE dbo.proc4 @min_year INTEGER = 0, @procCursor CURSOR VARYING OUTPUT
AS
SET @procCursor = CURSOR FOR SELECT * FROM dbo.FunctionTask4(@min_year);
OPEN @procCursor
GO

DECLARE @bookCursor4 CURSOR;
DECLARE @BookNameCursor4 VARCHAR(200);
DECLARE @BookSumCursor4 INTEGER;
EXEC dbo.proc4 @min_year=1950, @procCursor= @bookCursor4 OUTPUT;

FETCH NEXT FROM @bookCursor4 into @BookNameCursor4, @BookSumCursor4;
WHILE (@@FETCH_STATUS = 0)
    BEGIN;
        PRINT 'name: ' + @BookNameCursor4;
        SELECT @BookNameCursor4 AS Task4_Book_Name, @BookSumCursor4 AS YearIdSum;
        FETCH NEXT FROM @bookCursor4 into @BookNameCursor4, @BookSumCursor4;
    END;
CLOSE @bookCursor4;
DEALLOCATE @bookCursor4;
GO