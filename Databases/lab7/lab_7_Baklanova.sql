USE master ;  
GO  
IF DB_ID (N'Bookstore4') IS NOT NULL
DROP DATABASE Bookstore4; 
GO
CREATE DATABASE Bookstore4  
GO

-- представление - это виртуальная таблица, состоящая из совокупности 
-- именованных столбцов и строк данных, содержимое которой определяется 
-- запросом;

-- *****************
USE Bookstore4;
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

ALTER TABLE Publisher ADD MainLanguage varchar(60) DEFAULT 'RU' 
GO

INSERT INTO Publisher(NameOfOrganisation, AddressOfOrganisation, [Year])
VALUES ('Prosveshenie', 'Backer Street 1B', YEAR('1998-04-30'));

INSERT INTO Publisher(NameOfOrganisation, AddressOfOrganisation, [Year])
VALUES ('ABC', 'Backer Street 2B', YEAR('1978-04-30'));

Select*from Publisher;
GO
-- ******** 1 ********
USE Bookstore4
GO
CREATE VIEW showPublisher AS
    SELECT
        Publisher.PublisherID, Publisher.NameOfOrganisation,
        Publisher.AddressOfOrganisation
    FROM Publisher
GO

-- ****************
USE Bookstore4;
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
		ON UPDATE CASCADE
		--ON UPDATE NO ACTION
		--ON UPDATE SET NULL
		--ON UPDATE SET DEFAULT 

	);
	GO

	INSERT Authors (AuthorID, FirstName, LastName)
	VALUES (111, 'Bunin', 'Ivan');

	INSERT Literature (NameBook, AuthorID)
	VALUES ('Dark Avenues', 111);

	Select *from Literature;
	GO

-- ******** 2 ********

USE Bookstore4
GO
CREATE VIEW author_lit_view AS
    SELECT
        Authors.AuthorID, Authors.FirstName,
        Authors.LastNAme, Literature.NameBook
    FROM Authors INNER JOIN Literature
        ON Authors.AuthorID = Literature.AuthorID
		WHERE NameBook = 'aaa'
    WITH CHECK OPTION
GO

-- ****************

USE Bookstore4;
	GO

	IF OBJECT_ID (N'Customer') IS NOT NULL
DROP TABLE Customer; 
GO

	CREATE TABLE Customer (
	CustomerID UNIQUEIDENTIFIER DEFAULT NEWID(),
	FirstName varchar(20),
	LastName varchar(20),
    Email varchar(20)
	)
	GO 

	INSERT INTO Customer(FirstName, LastName, Email) VALUES ('Anastasia', 'Kelter', 'Anna99@mail.com');
	INSERT INTO Customer(FirstName, LastName, Email) VALUES ('Petr', 'The First', 'great_man@pigeon.ru');
Select*from Customer;
	GO

-- ******* 3 *******

--CREATE INDEX pub_ind
--    ON Customer (CustomerID)
--    INCLUDE (FirstName, LastName, Email) --Индекс с неключевыми столбцами может 
--GO 								--значительно повысить производительность запроса

CREATE NONCLUSTERED INDEX pub_ind --нет смысла если праймари; он сам создает кластеризованный индекс
    ON Literature (BookID)
    INCLUDE (NameBook) --Индекс с неключевыми столбцами может 
GO 								--значительно повысить производительность запроса

-- ******* 4 *******
IF OBJECT_ID ('Lit_authorintview', 'view') IS NOT NULL
DROP VIEW Lit_authorintview;
GO

CREATE VIEW Lit_authorintview
	WITH SCHEMABINDING AS  --Привязывает представление к схеме базовой таблицы
	SELECT dbo.Authors.AuthorID, dbo.Authors.FirstName --нельзя изменить структуру, с которой связано представление
	FROM dbo.Authors; --который будет влиять на определение представления
GO


select * from Authors

--update Authors set AuthorID = AuthorID+1;


CREATE UNIQUE CLUSTERED INDEX ind1
	ON Lit_authorintview (AuthorID);
GO

Alter table dbo.Authors drop column FirstName;