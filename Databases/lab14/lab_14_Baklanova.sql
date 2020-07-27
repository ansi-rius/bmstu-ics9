--Задание 14. Создание вертикально фрагментированных таблиц средствами СУБД SQL Server 2012
--1. Создать в базах данных пункта 1 задания 13 таблицы, содержащие вертикально
--фрагментированные данные.
USE Lab13_1
GO
--удаление таблицы
IF OBJECT_ID (N'Orders') IS NOT NULL
DROP TABLE Orders;
GO

CREATE TABLE Orders (
    --Film NVARCHAR(100) NOT NULL
    OrderID         INTEGER NOT NULL PRIMARY KEY,
    DateOfOrder     DATE                NOT NULL,
    DateOfDelivery  DATE                NOT NULL,
    TypeOfOrder     VARCHAR(50)         NOT NULL
)
INSERT Orders VALUES  
        (1, '01-jan-2001', '02-jan-2001', 'delivery'),
	    (2, '02-jan-2002', '02-jan-2002', 'at shop');
GO

USE Lab13_2
GO

IF OBJECT_ID (N'Orders') IS NOT NULL
DROP TABLE Orders;
GO
CREATE TABLE Orders (
    OrderID         INTEGER NOT NULL PRIMARY KEY,
    SummaryPrice    INT                 NOT NULL,
    Discount        INT                 NOT NULL,
    AdditionalInfo  VARCHAR(50)
)
GO
INSERT Orders VALUES
        (1, 175, 15, ':)'),
        (2, 999, 0, 'too expensive')
GO

--2. Создать необходимые элементы базы данных (представления, триггеры), обеспечивающие работу
--с данными вертикально фрагментированных таблиц (выборку, вставку, изменение, удаление).
IF OBJECT_ID(N'OrderView') IS NOT NULL
    DROP VIEW OrderView;
GO

CREATE VIEW OrderView
AS
    SELECT  o1.DateOfOrder,     o1.DateOfDelivery,  o1.TypeOfOrder,     o1.OrderID,
            o2.SummaryPrice,    o2.Discount,        o2.AdditionalInfo
    FROM lab13_1.dbo.Orders AS o1 INNER JOIN lab13_2.dbo.Orders AS o2 
    ON o1.OrderID = o2.OrderID;
GO
    
SELECT * FROM OrderView;
GO

CREATE TRIGGER insert_trigger ON OrderView
INSTEAD OF INSERT AS
BEGIN
    IF (EXISTS (SELECT * FROM inserted AS i
        WHERE (EXISTS (SELECT *
            FROM Lab13_1.dbo.Orders AS o1 WHERE (o1.OrderID = i.OrderID)))))
            BEGIN
                RAISERROR(N'Repeat Id', 18, 10);
                ROLLBACK;
            END;
            INSERT Lab13_1.dbo.Orders
            SELECT OrderID, DateOfOrder, DateOfDelivery, TypeOfOrder
            FROM inserted;

            INSERT Lab13_2.dbo.Orders
            SELECT OrderID, SummaryPrice, Discount, AdditionalInfo
            FROM inserted;
END
GO

CREATE TRIGGER delete_trigger ON OrderView
INSTEAD OF DELETE AS
BEGIN
    DELETE Lab13_1.dbo.Orders
    WHERE EXISTS(SELECT * FROM deleted
        WHERE(Lab13_1.dbo.Orders.OrderID = deleted.OrderID))
    DELETE Lab13_2.dbo.Orders
    WHERE EXISTS(SELECT * FROM deleted
        WHERE(Lab13_2.dbo.Orders.OrderID = deleted.OrderID))
      
END
GO

CREATE TRIGGER update_trigger ON OrderView
INSTEAD OF UPDATE 
AS
BEGIN
    IF (UPDATE (OrderID))
    BEGIN
        RAISERROR (N'You can not update Id', 18, 20);
        ROLLBACK;
    END
    IF UPDATE (DateOfOrder)
    BEGIN
        UPDATE Lab13_1.dbo.Orders
        SET DateOfOrder = (SELECT DateOfOrder FROM inserted
            WHERE (inserted.OrderID = Lab13_1.dbo.Orders.OrderID))
        WHERE (EXISTS (SELECT * FROM inserted 
            WHERE (Lab13_1.dbo.Orders.OrderID = inserted.OrderID)));
    END
    IF (UPDATE (AdditionalInfo))
    BEGIN
        UPDATE Lab13_2.dbo.Orders
            SET AdditionalInfo = (SELECT AdditionalInfo FROM inserted
                WHERE (inserted.OrderID = Lab13_2.dbo.Orders.OrderID))
            WHERE (EXISTS (SELECT * FROM inserted 
                WHERE (Lab13_2.dbo.Orders.OrderID = inserted.OrderID AND AdditionalInfo IS NOT NULL)));
    END
    IF (UPDATE (SummaryPrice))
    BEGIN
        UPDATE Lab13_2.dbo.Orders
            SET SummaryPrice = (SELECT SummaryPrice FROM inserted
                WHERE (inserted.OrderID = Lab13_2.dbo.Orders.OrderID))
            WHERE (EXISTS (SELECT * FROM inserted 
                WHERE (Lab13_2.dbo.Orders.OrderID = inserted.OrderID AND SummaryPrice IS NOT NULL)));
        
    END
END
GO


USE Lab13_1;
GO

IF OBJECT_ID(N'OrderView') IS NOT NULL
    DROP VIEW OrderView;
GO

CREATE VIEW OrderView
AS
    SELECT  o1.DateOfOrder,     o1.DateOfDelivery,  o1.TypeOfOrder,     o1.OrderID,
            o2.SummaryPrice,    o2.Discount,        o2.AdditionalInfo
    FROM lab13_1.dbo.Orders AS o1,
         lab13_2.dbo.Orders AS o2
    WHERE o1.OrderID = o2.OrderID;
GO

CREATE TRIGGER insert_trigger ON OrderView
INSTEAD OF INSERT AS
BEGIN
    IF (EXISTS (SELECT * FROM inserted AS i
        WHERE (EXISTS (SELECT *
            FROM Lab13_1.dbo.Orders AS o1 WHERE (o1.OrderID = i.OrderID)))))
            BEGIN
                RAISERROR(N'Repeat Id', 18, 10);
                ROLLBACK;
            END;
            INSERT Lab13_1.dbo.Orders
            SELECT OrderID, DateOfOrder, DateOfDelivery, TypeOfOrder
            FROM inserted;

            INSERT Lab13_2.dbo.Orders
            SELECT OrderID, SummaryPrice, Discount, AdditionalInfo
            FROM inserted;
END
GO

CREATE TRIGGER delete_trigger ON OrderView
INSTEAD OF DELETE AS
BEGIN
    DELETE Lab13_1.dbo.Orders
    WHERE EXISTS(SELECT * FROM deleted
        WHERE(Lab13_1.dbo.Orders.OrderID = deleted.OrderID))
    DELETE Lab13_2.dbo.Orders
    WHERE EXISTS(SELECT * FROM deleted
        WHERE(Lab13_2.dbo.Orders.OrderID = deleted.OrderID))
      
END
GO

CREATE TRIGGER update_trigger ON OrderView
INSTEAD OF UPDATE 
AS
BEGIN
    IF (UPDATE (OrderID))
    BEGIN
        RAISERROR (N'You can not update Id', 18, 20);
        ROLLBACK;
    END
    IF UPDATE (DateOfOrder)
    BEGIN
        UPDATE Lab13_1.dbo.Orders
        SET DateOfOrder = (SELECT DateOfOrder FROM inserted
            WHERE (inserted.OrderID = Lab13_1.dbo.Orders.OrderID))
        WHERE (EXISTS (SELECT * FROM inserted 
            WHERE (Lab13_1.dbo.Orders.OrderID = inserted.OrderID)));
    END
    IF (UPDATE (AdditionalInfo))
    BEGIN
        UPDATE Lab13_2.dbo.Orders
            SET AdditionalInfo = (SELECT AdditionalInfo FROM inserted
                WHERE (inserted.OrderID = Lab13_2.dbo.Orders.OrderID))
            WHERE (EXISTS (SELECT * FROM inserted 
                WHERE (Lab13_2.dbo.Orders.OrderID = inserted.OrderID AND AdditionalInfo IS NOT NULL)));
    END
    IF (UPDATE (SummaryPrice))
    BEGIN
        UPDATE Lab13_2.dbo.Orders
            SET SummaryPrice = (SELECT SummaryPrice FROM inserted
                WHERE (inserted.OrderID = Lab13_2.dbo.Orders.OrderID))
            WHERE (EXISTS (SELECT * FROM inserted 
                WHERE (Lab13_2.dbo.Orders.OrderID = inserted.OrderID AND SummaryPrice IS NOT NULL)));
        
    END
END
GO


INSERT OrderView(OrderID, DateOfOrder, DateOfDelivery, TypeOfOrder, SummaryPrice, Discount, AdditionalInfo)
        VALUES  (3, '03-mar-2003', '04-mar-2003', 'delivery', 300, 2, 'none'),
                (4, '04-apr-2004', '05-apr-2004', 'at shop', 1000, 0, 'yoooo'),
                (5, '05-may-2005', '15-may-2005', 'delivery', 3500, 10, 'thaaanks');
GO
SELECT * FROM OrderView;
GO

UPDATE OrderView
SET AdditionalInfo = AdditionalInfo + ' !NEW! ' + 'Forgot to say, u look awesome'
WHERE OrderID = 1;
GO
UPDATE OrderView
SET SummaryPrice = 0
WHERE (OrderID = 2);
GO
SELECT * FROM OrderView;
GO

DELETE OrderView
WHERE OrderID = 3;
SELECT * FROM OrderView;
GO

INSERT Lab13_2.dbo.OrderView(OrderID, DateOfOrder, DateOfDelivery, TypeOfOrder, SummaryPrice, Discount, AdditionalInfo)
                    VALUES  (10, '10-oct-2010','11-oct-2010', 'delivery', 255, 0, 'nyehehe');
GO
--INSERT into Lab13_2.dbo.OrderView VALUES (10, '10-oct-2010','11-oct-2010', 'delivery', 255, 0, 'nyehehe');
--GO
SELECT * FROM Lab13_2.dbo.OrderView;
GO

UPDATE Lab13_2.dbo.OrderView
SET AdditionalInfo = AdditionalInfo + ' !NEW! ' + ' 2nd building'
WHERE OrderID = 10;
GO

SELECT * FROM Lab13_2.dbo.OrderView;
GO