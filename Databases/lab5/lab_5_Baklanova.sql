USE master;
GO
IF DB_ID (N'Sales') IS NOT NULL 
DROP DATABASE Sales;
GO
-- execute the CREATE DATABASE statement
CREATE DATABASE Sales 
    ON PRIMARY 
        ( NAME = Sales_dat, FILENAME = "/Users/anemone/sqltest/salesdat.mdf",
        SIZE = 10, MAXSIZE = UNLIMITED, 
        FILEGROWTH = 5% )
LOG ON ( 
    NAME = Sales_log, 
    FILENAME = "/Users/anemone/sqltest/salelog.ldf",
    SIZE = 5MB,  -- указывает размер файла.
    MAXSIZE = 25MB, --задает максимальное значение, до которого может увеличиваться размер файла
    FILEGROWTH = 5MB ); --задает шаг автоматического приращения при увеличении размера файла
GO

USE Sales;
GO
CREATE TABLE Nine (
    source int,
    cost int
)
GO

ALTER DATABASE Sales
ADD FILEGROUP LargeFileGroup;
GO

ALTER DATABASE Sales
ADD FILE
        ( NAME = Data1,
        FILENAME = "/Users/anemone/sqltest/mydb1.ndf"),
        ( NAME = Data2,
        FILENAME = "/Users/anemone/sqltest/mydb2.ndf")
TO FILEGROUP LargeFileGroup;

ALTER DATABASE Sales
MODIFY FILEGROUP LargeFileGroup DEFAULT;
GO

USE Sales;
GO
CREATE TABLE Nine2 (
    test int
);
GO


CREATE UNIQUE CLUSTERED INDEX ind --changes location of table
ON dbo.Nine2 (test)
ON [primary]

GO



ALTER DATABASE Sales
MODIFY FILEGROUP [PRIMARY] DEFAULT;
GO

ALTER DATABASE Sales
REMOVE FILE Data1;
GO

ALTER DATABASE Sales
REMOVE FILE Data2;
GO

--DROP TABLE Nine2;

ALTER DATABASE Sales
REMOVE FILEGROUP LargeFileGroup;
GO

USE Sales;
GO
IF OBJECT_ID (N'Schema2') IS NOT NULL
DROP SCHEMA Schema2;
GO
-- CREATE SCHEMA statement 
CREATE SCHEMA Schema2
GO
-- ALTER SCHEMA statement
ALTER SCHEMA Schema2 TRANSFER dbo.Nine2;
-- DROP SCHEMA statement
GO
DROP TABLE Schema2.Nine2;


DROP SCHEMA Schema2;
