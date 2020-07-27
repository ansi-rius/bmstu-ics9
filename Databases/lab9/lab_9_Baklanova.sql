USE master;
GO
IF DB_ID (N'BookStore9') IS NOT NULL
DROP DATABASE BookStore9;
GO
CREATE DATABASE BookStore9
GO
--------------------------------
USE BookStore9;
GO

IF OBJECT_ID (N'Customer') IS NOT NULL
DROP TABLE Customer; 
GO

CREATE TABLE Customer(
	CustomerID INT PRIMARY KEY,
	FirstName VARCHAR(100) NOT NULL, 
	LastName VARCHAR(100) NOT NULL,
	City VARCHAR(50) NOT NULL,
	Phone VARCHAR (20),
	Email VARCHAR(50),
	)

IF OBJECT_ID (N'Ordered') IS NOT NULL
DROP TABLE Ordered; 
GO

CREATE TABLE Ordered(
	OrderedID INT PRIMARY KEY IDENTITY(1,1),
	Price INT NOT NULL,
	DateOfDelivery DATE NOT NULL, 
	DateOfOrder DATE NOT NULL,
	CustomerID INT, CONSTRAINT FK_Customer FOREIGN KEY (CustomerID) REFERENCES Customer (CustomerID))
GO

INSERT Customer(CustomerID, FirstName, LastName, City, Phone, Email)
	VALUES (1, 'Nikolay', 'Zadorozniy', 'Moscow', '+7 985-678-23-54 ', 'nik_cool@zmail.com'),
	(2, 'Alexander', 'Pusheen', 'Volgograd', '+7 985-644-54-90 ', 'alex-poet@zmail.com'),
	(3, 'Ekaterina', 'Velikaya', 'Saint Petersburg', '+7 930-543-12-04 ', 'graet-queen@zmail.com'),
	(4, 'Ernest', 'Skobinsky', 'Saint Petersburg', '+7 910-776-87-00 ', 'ernest@zmail.com');

INSERT Ordered(Price, DateOfDelivery, DateOfOrder, CustomerID)
	VALUES (112, '12-mar-2013', '12-dec-2012', 1),
	(212, '11-nov-2011', '15-dec-2011', 2),
	(312, '10-oct-2010', '19-dec-2010', 3),
	(412, '19-oct-2009', '19-dec-2009', 4);
SELECT *FROM Customer;
SELECT *FROM Ordered;
GO

IF OBJECT_ID (N'OrderedView') IS NOT NULL
DROP VIEW OrderedView;
GO

CREATE VIEW OrderedView AS
	SELECT 
		Ordered.Price AS Price,
		Ordered.DateOfDelivery AS DateOfDelivery,
		Ordered.DateOfOrder AS DateOfOrder,
		Customer.FirstName AS CustomerName,
		Customer.Email AS CustomerEmail
	FROM Ordered INNER JOIN Customer ON Ordered.CustomerID = Customer.CustomerID
GO
SELECT *FROM OrderedView
GO

-------------------------------------------1-------------------------------------------
--Для одной из таблиц пункта 2 задания 7 создать триггеры на вставку, удаление и добавление, при
--выполнении заданных условий один из триггеров должен инициировать возникновение ошибки 
--(RAISERROR / THROW).

IF OBJECT_ID ('trigger_insert', 'TR')  IS NOT NULL
	DROP TRIGGER trigger_insert;
GO

CREATE TRIGGER trigger_insert
	ON Ordered
	INSTEAD OF INSERT
	AS
	BEGIN
		IF EXISTS (
					SELECT * FROM inserted
					WHERE DateOfDelivery < DateOfOrder  
				)
		BEGIN
			RAISERROR('Please check dates', 16, 1)
			ROLLBACK TRANSACTION
			RETURN
		END
		INSERT INTO Ordered (Price, DateOfDelivery, DateOfOrder, CustomerID)
			 SELECT Price, DateOfDelivery, DateOfOrder, CustomerID
			 FROM inserted
		PRINT 'Add Order Info' 
	END
GO


IF OBJECT_ID ('trigger_delete', 'TR')  IS NOT NULL
	DROP TRIGGER trigger_delete;
GO

CREATE TRIGGER trigger_delete
	ON Ordered
	AFTER DELETE
	AS
	BEGIN
		PRINT 'Deleting Order'
	END
GO

IF OBJECT_ID ('trigger_update', 'TR')  IS NOT NULL
	DROP TRIGGER trigger_update;
GO

CREATE TRIGGER trigger_update
	ON Ordered
	AFTER UPDATE
	AS
	BEGIN
	IF UPDATE(CustomerID)
	BEGIN
		RAISERROR ('ERROR ID', 16, 1)
		ROLLBACK TRANSACTION
		RETURN
	END
	IF  UPDATE (DateOfDelivery) or UPDATE (DateOfOrder)
		BEGIN
			RAISERROR('error!', 16, 1)
			ROLLBACK TRANSACTION
			RETURN
		END
	IF UPDATE(Price)
		BEGIN
			RAISERROR('Careful! Price changing!', 16, 1)
			ROLLBACK TRANSACTION
			RETURN
		END
	END
GO

DELETE FROM Ordered WHERE (Price = 112)
SELECT *FROM Ordered;
GO

INSERT Ordered(Price, DateOfDelivery, DateOfOrder, CustomerID)
	VALUES (333, '13-dec-2013', '14-dec-2013', 2);
SELECT *FROM Ordered;
GO

UPDATE Ordered SET Price = 666 WHERE (DateOfDelivery = '10-oct-2010')
UPDATE Ordered SET DateOfDelivery = '01-jan-2010', DateOfOrder = '01-jan-2010'  WHERE (CustomerID = 4)
SELECT *FROM Ordered;
GO

UPDATE Ordered SET Price = 999 WHERE (Price = 333)
UPDATE Ordered SET CustomerID = 1 WHERE (Price = 999)
SELECT *FROM Ordered;
GO

-------------------------------------------2-------------------------------------------
--Для одной из таблиц пункта 2 задания 7 создать триггеры на вставку, удаление и добавление, при
--выполнении заданных условий один из триггеров должен инициировать возникновение ошибки 
--(RAISERROR / THROW).

IF OBJECT_ID ('trigger_insert_view', 'TR')  IS NOT NULL
	DROP TRIGGER trigger_insert_view;
GO

CREATE TRIGGER trigger_insert_view
    ON OrderedView
    INSTEAD OF INSERT
    AS
    BEGIN
        IF EXISTS (
                    SELECT * FROM inserted
                    WHERE CustomerEmail IN (SELECT Email FROM Customer)
                )
        BEGIN
            RAISERROR('error', 16, 1)
            ROLLBACK TRANSACTION
            RETURN
        END
        INSERT INTO Ordered(Price, DateOfDelivery, DateOfOrder, CustomerID)
             SELECT
             inserted.Price,
             inserted.DateOfDelivery,
             inserted.DateOfOrder,
             (SELECT CustomerID FROM Customer WHERE FirstName = inserted.CustomerName AND Email = inserted.CustomerEmail) --добавить фамилию?
             FROM inserted
        END
GO
 

IF OBJECT_ID ('trigger_update_view', 'TR')  IS NOT NULL
	DROP TRIGGER trigger_update_view;
GO

CREATE TRIGGER trigger_update_view
    ON OrderedView
    INSTEAD OF UPDATE
    AS
    BEGIN
		IF UPDATE (Price) or UPDATE (DateOfDelivery) or UPDATE (DateOfOrder) or UPDATE (CustomerEmail)
		BEGIN
			RAISERROR('error!', 16, 1)
			ROLLBACK TRANSACTION --Откатывает явные или неявные транзакции до начала или до точки сохранения транзакции.
			RETURN
		END
        IF UPDATE(CustomerName)
        BEGIN
            UPDATE Customer
            SET FirstName = i.CustomerName
            FROM
                (SELECT *, ROW_NUMBER() OVER (ORDER BY CustomerID) AS row_num FROM inserted) AS i
                JOIN
                (SELECT *, ROW_NUMBER() OVER (ORDER BY CustomerID) AS row_num FROM deleted) AS d
            ON i.row_num = d.row_num
            WHERE Customer.FirstName = d.CustomerName
        END
    END
GO

select * from OrderedView
update OrderedView set CustomerName = 'new Name' WHERE (Price = '212')
select * from OrderedView


select * from OrderedView
update OrderedView set CustomerName = 'mister ' + CustomerName
select * from OrderedView

 IF OBJECT_ID ('trigger_delete_view', 'TR')  IS NOT NULL
	DROP TRIGGER trigger_delete_view;
GO

CREATE TRIGGER trigger_delete_view
    ON OrderedView
    INSTEAD OF DELETE
    AS
        BEGIN
            MERGE Ordered USING(SELECT DateOfDelivery FROM deleted) AS OrderedView(DateOfDelivery)
            ON Ordered.DateOfDelivery = OrderedView.DateOfDelivery
            WHEN MATCHED 
            THEN DELETE;
        END
GO


INSERT INTO OrderedView (Price, DateOfOrder, DateOfDelivery, CustomerEmail)
	VALUES( 222, '11-oct-2011', '12-dec-2012', 'nik_c00ool@zmail.com'),
		  ( 333, '22-nov-2022', '23-dec-2023', 'alex-p000oet@zmail.com')
select * from OrderedView
select * from Customer
select * from Ordered
go
select * from OrderedView

select * from OrderedView
UPDATE OrderedView SET CustomerName = 'AAAAA' WHERE (CustomerName = 'mister Ernest')
select * from Customer
select * from OrderedView
go


select * from Ordered
select * from OrderedView
DELETE FROM OrderedView WHERE (Price = 312)

select * from Customer
select * from Ordered
select * from OrderedView
go