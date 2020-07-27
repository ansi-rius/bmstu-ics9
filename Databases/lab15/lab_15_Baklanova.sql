
--1. Создать в базах данных пункта 1 задания 13 связанные таблицы.
--2. Создать необходимые элементы базы данных (представления, триггеры), обеспечивающие работу
--с данными связанных таблиц (выборку, вставку, изменение, удаление).
USE Lab13_1
GO
IF OBJECT_ID (N'Genre') IS NOT NULL
DROP TABLE Genre;
GO
CREATE TABLE Genre (
    GenreID INTEGER NOT NULL,
    GenreName VARCHAR(100) NOT NULL ,
    CONSTRAINT PK_id_Edition PRIMARY KEY(GenreID)
)
GO
INSERT Genre VALUES(1, 'Myphology'),
         (2, 'Science'),
         (3, 'Math'),
         (4, 'Programming');
GO

USE Lab13_2
GO

--удаление таблицы
IF OBJECT_ID (N'Editions') IS NOT NULL
DROP TABLE Editions;
GO

CREATE TABLE Editions (
    EditionsID INTEGER NOT NULL PRIMARY KEY,
    Title VARCHAR(100) NOT NULL,
    Descr VARCHAR(1000),
    Genres INT
)
INSERT Editions VALUES (1, 'Introduction to C', 'Language C is the first for ICS9', 4),
         (2, 'Phylosophy of Java', 'java is my favourite', 4),
         (3, 'Math for dummies', 'Math is cool', 3),
         (4, 'Algebra', 'Golubkov', 3),
         (5, 'Ancient Greece Myphology', 'Zeus', 1),
         (6, 'Physics', 'We had no physics yet', 2);
GO

--2. Создать необходимые элементы базы данных (представления, триггеры), обеспечивающие работу
--с данными вертикально фрагментированных таблиц (выборку, вставку, изменение, удаление).
USE Lab13_1
GO

IF OBJECT_ID(N'EditionGenreView') IS NOT NULL
    DROP VIEW EditionGenreView;
GO

CREATE VIEW EditionGenreView
AS
    SELECT e.Title, e.Descr, g.GenreName
    FROM Lab13_1.dbo.Genre g
    INNER JOIN Lab13_2.dbo.Editions e
    ON g.GenreId = e.Genres
GO
SELECT * FROM EditionGenreView;
GO

USE Lab13_2
GO

IF OBJECT_ID(N'EditionGenreView') IS NOT NULL
    DROP VIEW EditionGenreView;
GO

CREATE VIEW EditionGenreView
AS
    SELECT g.GenreName, e.Title, e.Descr
    FROM Lab13_2.dbo.Editions e
    INNER JOIN Lab13_1.dbo.Genre g
    ON g.GenreId = e.Genres
GO
SELECT * FROM EditionGenreView;
GO

USE Lab13_1
GO

CREATE TRIGGER UpdateGenre ON Genre 
    AFTER UPDATE 
    AS
    BEGIN
        IF UPDATE(GenreID)
        BEGIN
            RAISERROR (N'You can not update genre id', 16, 1);
            ROLLBACK;
        END
        IF UPDATE(GenreName)
        BEGIN
            RAISERROR (N'You can not update genre name', 16, 1);
            ROLLBACK;
        END
    END
--END
GO

CREATE TRIGGER DeleteGenre ON Genre 
AFTER DELETE AS
BEGIN
    DELETE Lab13_2.dbo.Editions 
    WHERE (EXISTS(SELECT * FROM deleted
        WHERE(Lab13_2.dbo.Editions.Genres = deleted.GenreID)));
END
GO

USE Lab13_2
GO

CREATE TRIGGER InsertEditions ON Editions
AFTER INSERT 
AS
BEGIN
    IF ((SELECT COUNT(*) FROM inserted) <> (SELECT COUNT(*) FROM inserted AS i
        WHERE (EXISTS (SELECT * FROM Lab13_1.dbo.Genre AS d
            WHERE (i.Genres = d.GenreID)))))
        BEGIN
            RAISERROR(N'This ID does not exists', 18, 10);
            ROLLBACK;
        END
END
GO


CREATE TRIGGER UpdateEditions ON Editions 
AFTER UPDATE 
AS
BEGIN
    IF ((SELECT COUNT(*) FROM inserted) <> (SELECT COUNT(*) FROM inserted AS i
        WHERE (EXISTS (SELECT * FROM Lab13_1.dbo.Genre AS d
            WHERE (i.Genres = d.GenreID)))))
        BEGIN
            RAISERROR(N'This ID does not exists', 18, 10);
            ROLLBACK;
        END
END
GO

--INSERT Danser VALUES (9, N'Группа  JabbaWockeeZ');
INSERT Lab13_1.dbo.Genre VALUES (5, 'Cooking');
GO
INSERT Lab13_1.dbo.Genre VALUES (6, 'For kids');
GO
SELECT * FROM Editions;
SELECT * FROM Lab13_1.dbo.Genre;
GO


DELETE Lab13_1.dbo.Genre
WHERE (GenreId = 1);
SELECT * FROM Editions;
SELECT * FROM Lab13_1.dbo.Genre;
GO

DELETE Lab13_1.dbo.Genre
WHERE (GenreId = 6);
SELECT * FROM Editions;
SELECT * FROM Lab13_1.dbo.Genre;
GO

UPDATE Editions
SET Title = 'Animal Planet Magazine'
WHERE (EditionsID = 2);
GO
--UPDATE Lab13_1.dbo.Genre --cant upd name
--SET GenreName = 'OWOWOWO'
--WHERE (GenreId = 4);
GO
SELECT * FROM Editions;
SELECT * FROM Lab13_1.dbo.Genre;
GO
INSERT Lab13_2.dbo.Editions VALUES (15, 'Italy', 'Scince', 2); --id not exists
GO
SELECT * FROM Editions;
SELECT * FROM Lab13_1.dbo.Genre;
GO