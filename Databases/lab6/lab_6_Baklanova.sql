USE master ;  
GO  
IF DB_ID (N'Bookstore3') IS NOT NULL
DROP DATABASE Bookstore3; 
GO
CREATE DATABASE Bookstore3  
GO

-- *********1********
USE Bookstore3;
	GO

IF OBJECT_ID (N'Publisher') IS NOT NULL
DROP TABLE Publisher;
GO
	CREATE TABLE Publisher (
	PublisherID int IDENTITY(1,1) NOT NULL,
	NameOfOrganisation varchar(20),
	AddressOfOrganisation varchar(20),
	[Year] int,
	
	CONSTRAINT PK_Publisher PRIMARY KEY CLUSTERED (PublisherID),
	CONSTRAINT CHK_Year CHECK ([Year] > 1686),
	)
	GO  



--****2*****

ALTER TABLE Publisher ADD MainLanguage varchar(60) DEFAULT 'RU' 
GO

INSERT INTO Publisher(NameOfOrganisation, AddressOfOrganisation, [Year])
VALUES ('Prosveshenie', 'Backer Street 1B', YEAR('1998-04-30'));

INSERT INTO Publisher(NameOfOrganisation, AddressOfOrganisation, [Year])
VALUES ('ABC', 'Backer Street 2B', YEAR('1978-04-30'));

Select*from Publisher;
GO

SELECT SCOPE_IDENTITY() --Возвращает последнее значение идентификатора (до триггера)
--SELECT @@IDENTITY --если есть триггер, то возвращает индификатор, созданный триггером
--SELECT PublisherID = IDENT_CURRENT('Publisher') --возвращает последнее значение для конкретной таблицы
--не ограничена областью действия и сеансом, но ограничена указанной таблицей;
--слаба к race conditions

INSERT INTO Publisher(NameOfOrganisation, AddressOfOrganisation, [Year])
VALUES ('ABCD', 'Backer Street 2B', YEAR('1978-04-30'));

Select*from Publisher;
GO

--*******3*******
USE Bookstore3;
	GO

	IF OBJECT_ID (N'Customer') IS NOT NULL
DROP TABLE Customer; 
GO

	CREATE TABLE Customer (
	CustomerID UNIQUEIDENTIFIER DEFAULT NEWID(), --глобальный
	FirstName varchar(20),
	LastName varchar(20),
    Email varchar(20)
	CONSTRAINT PK_Customer PRIMARY KEY CLUSTERED (CustomerID)
	)
	GO 

	INSERT INTO Customer(FirstName, LastName, Email) VALUES ('Anastasia', 'Kelter', 'Anna99@mail.com');
	INSERT INTO Customer(FirstName, LastName, Email) VALUES ('Petr', 'The First', 'great_man@pigeon.ru');
Select*from Customer;
	GO


	--******4********
	USE Bookstore3;
	GO

	IF OBJECT_ID (N'Books') IS NOT NULL
DROP TABLE Books; 

	CREATE TABLE Books
	(BookID int PRIMARY KEY,
	Autor varchar(60),
	NameBook varchar(30)
	);
	GO

	IF OBJECT_ID (N'CountBook') IS NOT NULL
DROP SEQUENCE CountBook; 		--последовательность
	CREATE SEQUENCE CountBook
	START WITH 1
	INCREMENT BY 4;
	GO

	INSERT Books (BookID, Autor, NameBook)
	VALUES (NEXT VALUE FOR CountBook, 'Jane Austen', 'pride and prejudice');
	INSERT Books (BookID, Autor, NameBook)
	VALUES (NEXT VALUE FOR CountBook, 'Fyodor Dostoyevsky', 'Crime and Punishment');

	Select*from Books;
GO

	--******5********

USE Bookstore3;
	GO

IF OBJECT_ID (N'Authors') IS NOT NULL
DROP TABLE Authors; 
	CREATE TABLE Authors
	(AuthorID int PRIMARY KEY,
	FirstName varchar(30),
	LastNAme varchar(30),
	);
	GO

	IF OBJECT_ID (N'Literature') IS NOT NULL
DROP TABLE Literature; 

	CREATE TABLE Literature
	(BookID int PRIMARY KEY IDENTITY(1,1),
	NameBook varchar(30),
	AuthorID int
	CONSTRAINT FK_Autors_Books FOREIGN KEY (AuthorID) REFERENCES Authors (AuthorID)
		ON UPDATE CASCADE --каскадное изменение ссылающихся таблиц;
		--ON UPDATE NO ACTION --выдаст ошибку при удалении/изменении
		--ON UPDATE SET NULL --установка NULL для ссылающихся внешних ключей;
		--ON UPDATE SET DEFAULT --установка значений по умолчанию для ссылающихся внешних ключей;

	);
	GO

	INSERT Authors (AuthorID, FirstName, LastName)
	VALUES (111, 'Bunin', 'Ivan');

	INSERT Literature (NameBook, AuthorID)
	VALUES ('Dark Avenues', 111);

	Select *from Literature;
	GO

	UPDATE Authors
	SET AuthorID = 222
	WHERE AuthorID = 111

	Select *from Literature;
	GO

Select *from Authors;
	GO
	
	