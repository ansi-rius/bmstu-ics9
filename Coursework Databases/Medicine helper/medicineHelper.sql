USE master;
GO
IF DB_ID (N'MEDICINE_HELPER2') IS NOT NULL
DROP DATABASE MEDICINE_HELPER2;
GO

create database MEDICINE_HELPER2 ON ( NAME = SQLserv_1_dat,
FILENAME = '/Users/anemone/sqltest/sql-9.mdf',
SIZE = 10, MAXSIZE = 150, FILEGROWTH = 5% )
LOG ON ( NAME = Lab13_1_log,
FILENAME = '/Users/anemone/sqltest/sql-9.ldf',
SIZE = 5MB, MAXSIZE = 150MB, FILEGROWTH = 5MB )
GO

use MEDICINE_HELPER2
go



/*-----     ГРУППЫ БОЛЕЗНЕЙ     -----*/
IF OBJECT_ID (N'ClassificationOfDiseases') IS NOT NULL
DROP TABLE ClassificationOfDiseases;
GO

create table ClassificationOfDiseases (
    ClassID       int PRIMARY KEY               not null,
    ClassName     nvarchar(150)                 not null,
    ClassDescr    nvarchar(2000)                not null,
)
GO



/*-----       БОЛЕЗНИ       -----*/
IF OBJECT_ID (N'Diseases') IS NOT NULL
DROP TABLE Diseases;
GO

create table Diseases (
    DiseaseID           varchar(10) PRIMARY KEY       not null,
    DiseaseName         nvarchar(150)                 not null,       /*    Название болезни                 */
    AlternativeNames    nvarchar(300)                 not null,       /*    Иные названия                    */
    RiskGroup           nvarchar(2000)                not null,       /*    Риск заболеть выше у след лиц    */
    Cause               nvarchar(800)                 not null,       /*    Причина заболевания              */
    Symptoms            nvarchar(2000)                not null,       /*    Симптомы                         */
    Diagnostics         nvarchar(2000)                not null,       /*    Диагностика                      */
    Complications       nvarchar(2000)                not null,       /*    Осложнения                       */

    ClassID int not NULL
        constraint FK_DiseaseClass
            foreign key references ClassificationOfDiseases (ClassID)
                on update cascade
)
GO



/*-----       ЛЕКАРСТВА       -----*/
IF OBJECT_ID (N'Medicine') IS NOT NULL
DROP TABLE Medicine;
GO

create table Medicine (
    MedicineID                   nvarchar(20) PRIMARY KEY    not null,
    MedName                      nvarchar(300)               not null,      /*    Торговое наименование препарата    */
    InternationalName            nvarchar(600)               not null,      /*    Международное наименование         */
    PharmacotherapeuticGroup     nvarchar(300)               not null,      /*    Фармакотерапевтическая группа      */
    PharmacologicalProperties    nvarchar(4000)              not null,      /*    Фармакологические свойства         */
    Caution                      nvarchar(3000)              not null,      /*    С осторожностью                    */
    HowToUse                     nvarchar(4000)              not null,      /*    Способ применения                  */
    Receipt                      nvarchar(100)               not null       /*    Условия отпуска из аптек           */
)



/*-----       ОСОБЕННОСТИ      -----*/
IF OBJECT_ID (N'Features') IS NOT NULL
DROP TABLE Features;
GO

create table Features (
    FeatureID       int PRIMARY KEY                   not null,
    FeatureName     nvarchar(100)                     not null,       /*    Название особенности     */
    FeatureDescr    nvarchar(500)                     not null        /*    Описание особенности     */
)



/*-----       СВЯЗЬ ЛЕКАРСТВА-ОСОБЕННОСТИ      -----*/
IF OBJECT_ID (N'MedicineFeatures_INT') IS NOT NULL
DROP TABLE MedicineFeatures_INT;
GO

create table MedicineFeatures_INT (
    MedicineID nvarchar(20) not NULL
        constraint FK_MedicineFeatures_MedicineID
            foreign key references Medicine (MedicineID)
                on update cascade,
    FeatureID int not NULL
        constraint FK_MedicineFeatures_FeatureID
            foreign key references Features (FeatureID)
                on update cascade,
    primary key (MedicineID, FeatureID)
)



/*-----       СВЯЗЬ БОЛЕЗНИ-ЛЕКАРСТВА-ПОКАЗАНИЯ      -----*/
IF OBJECT_ID (N'DiseaseMedicine_indications') IS NOT NULL
DROP TABLE DiseaseMedicine_indications;
GO

create table DiseaseMedicine_indications (
    DiseaseID varchar(10) not NULL
        constraint FK_DiseaseMedicine_DiseaseID
            foreign key references Diseases (DiseaseID)
                on update cascade,
    MedicineID nvarchar(20) not NULL
        constraint FK_DiseaseMedicine_MedicineID
            foreign key references Medicine (MedicineID)
                on update cascade,
    primary key (DiseaseID, MedicineID)
)


/*-----       СВЯЗЬ БОЛЕЗНИ-ЛЕКАРСТВА-ПРОТИВОПОКАЗАНИЯ      -----*/
IF OBJECT_ID (N'DiseaseMedicine_contraindications') IS NOT NULL
DROP TABLE DiseaseMedicine_contraindications;
GO

create table DiseaseMedicine_contraindications (
    DiseaseID varchar(10) not NULL
        constraint FK_DiseaseMedicine_contr_DiseaseID
            foreign key references Diseases (DiseaseID)
                on update cascade,
    MedicineID nvarchar(20) not NULL
        constraint FK_DiseaseMedicine_contr_MedicineID
            foreign key references Medicine (MedicineID)
                on update cascade,
    primary key (DiseaseID, MedicineID)
)

/* --------------------------------- НОВАЯ СВЯЗЬ ПОКАЗАНИЯ-ПРОТИВОПОКАЗАНИЯ ------------------------------------ */
IF OBJECT_ID (N'DiseaseMedicine_int') IS NOT NULL
DROP TABLE DiseaseMedicine_int;
GO

create table DiseaseMedicine_int (
    DiseaseID varchar(10) not NULL
        constraint FK_DiseaseMedicine1_DiseaseID
            foreign key references Diseases (DiseaseID)
                on update cascade,
    MedicineID nvarchar(20) not NULL
        constraint FK_DiseaseMedicine1_MedicineID
            foreign key references Medicine (MedicineID)
                on update cascade,
    primary key (DiseaseID, MedicineID),
    ContradictionsFlag bit not null
)

/*--------           VIEWS         ---------*/
/*      Представление Болезнь-Показания-Лекарство     */
IF OBJECT_ID (N'DiseaseAndMedicineView') IS NOT NULL
DROP VIEW DiseaseAndMedicineView;
GO

CREATE VIEW DiseaseAndMedicineView AS
    SELECT
        Medicine.MedicineID,
        Medicine.MedName,
        Medicine.InternationalName,
        Medicine.PharmacotherapeuticGroup,
        Medicine.PharmacologicalProperties,
        Medicine.Caution,
        Medicine.HowToUse,
        Medicine.Receipt,
        Diseases.DiseaseName,
        DiseaseMedicine_int.ContradictionsFlag
    from DiseaseMedicine_int
    inner join Medicine
        on DiseaseMedicine_int.MedicineID = Medicine.MedicineID
    inner join Diseases
        on DiseaseMedicine_int.DiseaseID = Diseases.DiseaseID
GO



/*      Представление Болезнь-Противопоказания-Лекарство     */
IF OBJECT_ID (N'ContraDiseaseAndMedicineView') IS NOT NULL
DROP VIEW ContraDiseaseAndMedicineView;
GO

CREATE VIEW ContraDiseaseAndMedicineView AS
    SELECT
        Medicine.MedicineID,
        Medicine.MedName,
        Medicine.InternationalName,
        Medicine.PharmacotherapeuticGroup,
        Medicine.PharmacologicalProperties,
        Medicine.Caution,
        Medicine.HowToUse,
        Medicine.Receipt,
        Diseases.DiseaseName
    from DiseaseMedicine_contraindications 
    inner join Medicine
        on DiseaseMedicine_contraindications.MedicineID = Medicine.MedicineID
    inner join Diseases
        on DiseaseMedicine_contraindications.DiseaseID = Diseases.DiseaseID
GO



/*      Представление Класс болезни-Болезнь       */
IF OBJECT_ID (N'DiseaseAndClassView') IS NOT NULL
DROP VIEW DiseaseAndClassView;
GO

CREATE VIEW DiseaseAndClassView AS
    SELECT
        ClassificationOfDiseases.ClassID, ClassificationOfDiseases.ClassName,
        Diseases.DiseaseID, Diseases.DiseaseName

    FROM ClassificationOfDiseases INNER JOIN Diseases
        ON ClassificationOfDiseases.ClassID = Diseases.ClassID
GO



/*        Представление Лекарство-Противопоказания       */
IF OBJECT_ID (N'MedicineAndFeaturesView') IS NOT NULL
DROP VIEW MedicineAndFeaturesView;
GO

CREATE VIEW MedicineAndFeaturesView AS
    SELECT
        Medicine.MedicineID,
        Medicine.MedName,
        Medicine.InternationalName,
        Medicine.PharmacotherapeuticGroup,
        Medicine.PharmacologicalProperties,
        Medicine.Caution,
        Medicine.HowToUse,
        Medicine.Receipt,
        Features.FeatureName


    from MedicineFeatures_INT 
    inner join Medicine
        on MedicineFeatures_INT.MedicineID = Medicine.MedicineID
    inner join Features
        on MedicineFeatures_INT.FeatureID = Features.FeatureID
GO



/*        Представление Лекарство-Противопоказания-Особенности       */
IF OBJECT_ID (N'MedicineAndFeaturesAndContradictionsView') IS NOT NULL
DROP VIEW MedicineAndFeaturesAndContradictionsView;
GO

CREATE VIEW MedicineAndFeaturesAndContradictionsView AS
    SELECT
        Medicine.MedicineID,
        Medicine.MedName,
        Medicine.InternationalName,
        Medicine.PharmacotherapeuticGroup,
        Medicine.PharmacologicalProperties,
        Medicine.Caution,
        Medicine.HowToUse,
        Medicine.Receipt,
        Features.FeatureName,
        Diseases.DiseaseName,
        DiseaseMedicine_int.ContradictionsFlag

    from Medicine
    
    inner join MedicineFeatures_INT
        on MedicineFeatures_INT.MedicineID=Medicine.MedicineID
    join Features
        on MedicineFeatures_INT.FeatureID=Features.FeatureID
    join DiseaseMedicine_int
        on DiseaseMedicine_int.MedicineID=Medicine.MedicineID
    join Diseases
        on DiseaseMedicine_int.DiseaseID=Diseases.DiseaseID
GO


/*----- inserts -----*/
insert into ClassificationOfDiseases (classID, className, classDescr) 
    values (9, N'Болезни системы кровообращения', N'Включены: Острая ревматическая лихорадка;Хронические ревматические болезни сердца;
Болезни, характеризующиеся повышенным кровяным давлением;Ишемическая болезнь сердца;
Легочное сердце и нарушения легочного кровообращения;Другие болезни сердца;
Цереброваскулярные болезни;Болезни артерий, артериол и капилляров;
Болезни вен, лимфатических сосудов и лимфатических узлов, не классифицированные в других рубриках;
Другие и неуточненные болезни системы кровообращения'),
(1, N'Некоторые инфекционные и паразитарные болезни', N'Включены:
болезни, обычно рассматриваемые как передающиеся, или трансмиссивные
При необходимости используется дополнительный код (U82-U84) для определения резистентности к противомикробным препаратам.'),
(4,N'Болезни эндокринной системы, расстройства питания и нарушения обмена веществ', N'Примечание. Все новообразования (как функционально активные,так и неактивные) включены в класс II. Соответствующие коды в этом классе (например, E05.8, E07.0, E16-E31, E34.-)
 при необходимости можно использовать в качестве дополнительных кодов для идентификации функционально активных новообразований и эктопической эндокринной ткани, а также гиперфункции и гипофункции эндокринных желез, связанных с новообразованиями и другими расстройствами, классифицированными в других рубриках.'),
(2, N'Новообразования', N'Этот класс содержит следующие широкие группы новообразований.'),
(3, N'Болезни крови, кроветворных органов и отдельные нарушения, вовлекающие иммунный механизм', N'Этот класс содержит следующие блоки:D50-D53 Анемии, связанные с питанием;
D55-D59 Гемолитические анемии;D60-D64 Апластические и другие анемии;D65-D69 Нарушения свертываемости крови, пурпура и другие геморрагические состояния;
D70-D77 Другие болезни крови и кроветворных органов;D80-D89 Отдельные нарушения, вовлекающие иммунный механизм'),
(5, N'Психические расстройства и расстройства поведения', N'Этот класс содержит следующие блоки:Органические, включая симптоматические, психические расстройства;
Психические расстройства и расстройства поведения, связанные с употреблением психоактивных веществ;Шизофрения, шизотипические и бредовые расстройства;Расстройства настроения [аффективные расстройства];
Невротические, связанные со стессом, и соматоформные расстройства;Поведенческие синдромы, связанные с физиологическими нарушениями и физическими факторами;Расстройства личности и поведения в зрелом возрасте;
Умственная отсталость;Расстройства психологического развития;Эмоциональные расстройства, расстройства поведения, обычно начинающиеся в детском и подростковом возрасте;Неуточненные психические расстройства'),
(6, N'Болезни нервной системы', N'Этот класс содержит следующие блоки:Воспалительные болезни центральной нервной ситемы;Системные атрофии, поражающие преимущественно центральную нервную систему;
Экстрапирамидные и другие двигательные нарушения;Другие дегенеративные болезни центральной нервной системы;Демиелинизирующие болезни центральной нервной системы;
Эпизодические и пароксизмальные расстройства;Поражения отдельных нервов, нервных корешков и сплетений;Полиневропатии и другие поражения периферической нервной системы;Болезни нервно-мышечного синапса и мышц;
Церебральный паралич и другие паралитические синдромы;Другие нарушения нервной системы'),
(7, N'Болезни глаза и его придаточного аппарата', N'Этот класс содержит следующие блоки:Болезни век, слезных путей и глазницы;Болезни конъюнктивы;Болезни склеры, роговицы, радужной оболочки и цилиарного тела;
Болезни хрусталика;Болезни сосудистой оболочки и сетчатки;Глаукома;Болезни стекловидного тела и глазного яблока;Болезни зрительного нерва и зрительных путей;
Болезни мышц глаза, нарушения содружественного движения глаз, аккомодации и рефракции;Зрительные расстройства и слепота;Другие болезни глаза и его придаточного аппарата'),
(8, N'Болезни уха и сосцевидного отростка', N'Этот класс содержит следующие блоки:Болезни наружного уха;Болезни среднего уха и сосцевидного отростка;
Болезни внутреннего уха;Другие болезни уха'),
(10, N'Болезни органов дыхания', N'Примечание. Если поражение органов дыхания вовлекает более чем одну анатомическую область, не обозначенную специально, его следует квалифицировать по анатомически ниже расположенной локализации (например, трахеобронхит кодируется как бронхит в рубрике J40).')




insert into Diseases (DiseaseID, DiseaseName, AlternativeNames, RiskGroup, Cause, Symptoms, Diagnostics, Complications, ClassID)
    values ('I64', N'Инсульт, не уточненный как кровоизлияние или инфаркт',
    N'ОНМК;инсульт;геморрагический инсульт;ишемический инсульт;ранзиторная ишемическая атака;
    преходящее нарушение мозгового кровообращения;кардиоэмболический инсульт;
    атеротромбический инсульт;гемодинамический инсульт;малый инсульт',
    N'курение;сахарный диабет;нарушения ритма сердца;высокий уровень холестерина;
    избыточная масса тела;низкий уровень физической активности;злоупотребление алкоголем',
    N'Причина ишемического инсульта — развитие локальной ишемии ткани головного мозга из-за закупорки артерии. 
    Чаще всего закупорка происходит на фоне распространенного атеросклероза, когда атеросклеротическая бляшка закрывает просвет сосуда, делая невозможным адекватное питание головного мозга (атеротромбический ишемический инсульт).
    Ишемия может возникать и вследствие тромбоэмболии артериального русла. В большинстве случаев тромб находится в камерах сердца и с током крови попадает в головной мозг, 
    приводя к обструкции (кардиоэмболический инсульт). Такие тромбы часто встречаются при мерцательной аритмии, стенозах митрального клапана, инфекционном эндокардите и других патологиях.',
    N'головная боль;головокружение;нарушение сознания (оглушение, сопор);потеря ориентировки во времени и пространстве;психомоторное возбуждение;Двигательные нарушения — ограничение двигательной функции в одной половине туловища (к примеру, левая рука, левая нога, левая часть лица) часто сочетается со слабостью, неловкостью в конечностях. На пораженной стороне характерно постепенное усиление тонуса мышц-сгибателей, усиление глубоких рефлексов. Нарушения возникают на стороне, противоположной стороне поражения;
    Речевые нарушения — появляются трудности в подборе слов и построении фраз. Речь становится замедленной, невнятной, сложно произносить даже элементарные слова. Также больные могут испытывать трудности в понимании обращенной речи',
    N'Пациента просят произвести следующие действия: 1)Выговорить фразу — оценивают четкость произношения отдельных звуков и слов, правильный порядок построение фразы.
    2)Поднять руки перед собой — смотрят, может ли человек поднять и держать руки перед собой, одинакова ли сила в конечностях.
    3)Попробовать улыбнуться — проверяют, симметрично ли лицо при мимических сокращениях, нет ли провисаний одной половины лица, затруднено ли движение мышц лица при улыбке.',
    N'Окклюзионная гидроцефалия — гематома, возникающая при развитии геморрагического инсульта, может сдавливать пути оттока ликвора. Это приводит к накоплению жидкости в полостях желудочков мозга и повышению внутричерепного давления;
    Инфекционные осложнения — у пациентов, которые длительно находятся в лежачем положении, повышается риск развития инфекционных осложнений, таких как пневмония, инфекции мочевыводящих путей и т.д;
    Тромбоз вен нижних конечностей — у пациентов с вынужденным постельном режимом повышается риск развития тромбов в системе вен нижних конечностей, что может быть источником тромбоэмболических осложнений, в т.ч. тромбоэмболии легочной артерии (ТЭЛА);
    Пролежни — некроз мягких тканей в связи с длительным механическим давлением на ткани и нарушением местного кровообращения и трофики. Чаще возникают на спине, задней поверхности верхних и нижних конечностей, ягодицах, крестце;',
    9),

    ('A15', N'Туберкулез органов дыхания, подтвержденный бактериологически и гистологически',
    N'Туберкулез легких;внелегочный туберкулез', N'Лица, контактировавшие с больными туберкулезом;лица, проживающие в эндемических регионах по отношению к туберкулезной инфекции;
    лица с ВИЧ-инфекцией, онкологическими заболеваниями;лица с хроническими заболеваниями легких;пациенты с сахарным диабетом;
    лица с недостаточным питанием;страдающие алкоголизмом;курящие лица', N'Заболевание вызывают микобактерии туберкулезного комплекса — M. tuberculosis (палочка Коха), M. africanum, M. microti, M. canetti, M. pinnipedii, M. caprae, M. bovis, M. bovis BCG, — которые обладают высокой устойчивостью во внешней среде, постоянной изменчивостью, медленно размножаются в организме и способны вызывать специфическое воспаление.
    Естественный “резервуар” туберкулезной инфекции — человек, животные и птицы. Основной путь передачи инфекции — воздушно-капельный, реже контактный, через пищу и от матери к ребенку.
    В 90–95 % случаев туберкулезные изменения локализуются в органах дыхания, но также могут поражать лимфоузлы, кожу, глаза, костно-суставную, мочеполовую, нервную системы и желудочно-кишечный тракт.',
    N'боли в костях скелета при ходьбе, отек пораженного сустава (туберкулез костей и суставов);
    боли и частые позывы при мочеиспускании, появление крови в моче (туберкулез мочеполовой системы);
    боль и вздутие живота (туберкулез кишечника);
    головная боль, слабость, онемение, нарушение сознания (туберкулезный менингит);
    безболезненное и постепенное увеличение в размерах шейных, подмышечных и паховых лимфоузлов (туберкулез периферических лимфоузлов)',
    N'Проводится тщательный опрос пациента о характере начала болезни, интоксикации, о симптомах со стороны дыхательной системы, наличии контакта с больным туберкулезом, сопутствующих заболеваниях, длительности лечения какими-либо препаратами, подавляющих иммунитет, а также вакцинации против туберкулеза.
    При обследовании врач проводит общий осмотр пациента, измеряет температуру тела, артериальное давление, частоту сердечных сокращений и дыхания, осмотр кожных покровов и видимых слизистых, пальпацию (прощупывание) лимфоузлов, аускультацию (выслушивание) легких и сердца, а также оценивает выраженность интоксикации, кашля и одышки.',
    N'Легочное кровотечение;обширная деструкция легкого;дыхательная и сердечная недостаточность;пневмоторакс — накопление воздуха в плевральной полости, что приводит к сдавлению легкого и затруднению дыхания;
    амилоидоз — системное поражение организма, вызванное отложением в тканях вещества амилоида, сопровождающееся развитием недостаточности и атрофии органов и тканей;
    воспалительный синдром восстановления иммунной системы — усиление воспалительной реакции на проводимую противотуберкулезную терапию у пациентов с ВИЧ-инфекцией;
    острый респираторный дистресс-синдром — угрожающее жизни состояние, при котором отмечается воспалительный отек и повреждение легких;
    снижение или утрата функции пораженных суставов;
    полиорганная недостаточность.',
    1),
    ('E10', N'Сахарный диабет', N'Инсулинзависимый диабет;ювенильный диабет', N'Те, у кого есть родственники, болеющие сахарным диабетом.Обычно болеют молодые люди до 30 лет.',
    N'Повреждение бета-клеток поджелудочной железы, снижающее секрецию инсулина, приводит к развитию сахарного диабета. Это происходит в результате аутоиммунного нарушения. Организм воспринимает бета-клетки как чужеродные и вырабатывает антитела, разрушающие их. В результате недостаточной выработки инсулина увеличивается концентрация глюкозы в крови (гипергликемия). Хроническая гипергликемия запускает каскад патологических реакций в организме.',
    N'тошнота и рвота;боль в животе;специфический запах при дыхании: «фруктовый», «ацетоновый» (из-за избытка в организме кетонных тел);
    затем, по мере развития этого нарушения, появляется учащенное глубокое дыхание, падает артериальное давление, нарушается сознание вплоть до комы',
    N'Врач попросит рассказать о времени возникновения и характере жалоб и симптомов, о случаях заболеваний сахарным диабетом в семье. Оценит работу жизненно важных органов, подтвердит наличие признаков диабета и проверит наличие других угрожающих жизни нарушений.',
    N'Диабетический кетоацидоз;Диабетическая ретинопатия — тяжелое нарушение сосудов глаза;Диабетическая нефропатия — тяжелое нарушение сосудов почек;
    Диабетическая ангиопатия (поражение сосудов), ишемическая болезнь сердца, атеросклероз;Диабетическая нейропатия (поражение нервных волокон)',
    4)


insert into Medicine (MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt)
    values ('N07XX', N'Мексидол', N'этилметилгидроксипиридина сукцинат', N'Антиоксидантное средство', 
    N'Мексидол® является ингибитором свободнорадикальных процессов, мембранопротектором, обладающим антигипоксическим, стресс-протективным, ноотропным, противосудорожным и анксиолитическим действием. Препарат повышает резистентность организма к 
    воздействию различных повреждающих факторов (шок, гипоксия и ишемия, нарушения мозгового кровообращения, интоксикация алкоголем и антипсихотическими средствами /нейролептиками/).Препарат улучшает метаболизм и кровоснабжение головного мозга, улучшает микроциркуляцию и реологические свойства крови, уменьшает агрегацию тромбоцитов. Стабилизирует мембранные структуры клеток крови (эритроцитов и тромбоцитов) при гемолизе. Обладает гиполипидемическим действием, уменьшает содержание общего холестерина и ЛПНП.
Антистрессорное действие проявляется в нормализации постстрессового поведения, сомато-вегетативных нарушений, восстановлении циклов "сон-бодрствование", 
нарушенных процессов обучения и памяти, снижении дистрофических и морфологических изменений в различных структурах головного мозга.Мексидол® улучшает функциональное состояние ишемизированного миокарда. В условиях коронарной недостаточности увеличивает коллатеральное кровоснабжение ишемизированного миокарда, способствует сохранению целостности кардиомиоцитов и поддержанию их функциональной активности. Эффективно восстанавливает сократимость миокарда при обратимой сердечной дисфункции.',
N'--', N'Внутрь, по 125–250 мг 3 раза в сутки; максимальная суточная доза — 800 мг (6 табл.).
Длительность лечения — 2–6 нед; для купирования алкогольной абстиненции — 5–7 дней. Лечение прекращают постепенно, уменьшая дозу в течение 2–3 дней.
Начальная доза — 125–250 мг (1–2 табл.) 1–2 раза в сутки с постепенным повышением до получения терапевтического эффекта; максимальная суточная доза — 800 мг (6 табл.).
Продолжительность курса терапии у больных ИБС — не менее 1,5–2 мес. Повторные курсы (по рекомендации врача), желательно проводить в весенне-осенние периоды.',
N'По рецепту'),
    ('R05C', N'Аскорил', N'БРОМГЕКСИН;ГВАЙФЕНЕЗИН;САЛЬБУТАМОЛ', N'Отхаркивающее комбинированное средство', N'Комбинированное лекарственное средство, оказывает бронхолитическое, отхаркивающее и муколитическое действие.
Сальбутамол - бронхолитическое средство, стимулирует β2-адренорецепторы бронхов, кровеносных сосудов и миометрия. Предупреждает или устраняет спазм бронхов, снижает сопротивление в дыхательных путях, увеличивает жизненную емкость лекгих. Вызывает расширение коронарных артерий, не снижает АД.
Бромгексин - муколитическое средство, оказывает отхаркивающее и противокашлевое действие. Увеличивает серозный компонент бронхиального секрета; активирует реснички мерцательного эпителия, снижает вязкость мокроты, увеличивает ее объем и улучшает отхождение.',
    N'Гвайфенезин окрашивает мочу в розовый цвет. Не рекомендуется принимать одновременно с щелочное питье.', N'Для приема внутрь. Разовая доза зависит от возраста, частота приема - 3 раза/сут.',
    N'Отпуск по рецепту'),
    ('A10AB01', N'Ринсулин® Р', N'инсулин растворимый [человеческий генно-инженерный]', N'Инсулин человеческий короткого действия', N'Гипогликемическое средство, инсулин короткого действия. Взаимодействуя со специфическим рецептором внешней мембраны клеток, образует инсулинрецепторный комплекс. Повышая синтез цАМФ (в жировых клетках и клетках печени) или непосредственно проникая в клетку (мышцы), инсулинрецепторный комплекс стимулирует внутриклеточные процессы, в т.ч. синтез ряда ключевых ферментов (включая гексокиназу, пируваткиназу, гликогенсинтетазу).
    Снижение концентрации глюкозы в крови обусловлено повышением ее внутриклеточного транспорта, усилением поглощения и усвоения тканями, стимуляцией липогенеза, гликогеногенеза, синтеза белка, снижением скорости продукции глюкозы печенью (снижение распада гликогена).
    Начало действия – через 30 мин, максимальный эффект - через 1-3 ч, длительность действия - 8 ч.', N'С осторожностью проводят подбор дозы препарата у пациентов с имевшимися ранее нарушениями мозгового кровообращения по ишемическому типу и с тяжелыми формами ИБС.
Потребность в инсулине может меняться в следующих случаях: при переходе на другой вид инсулина; при изменении режима питания, диарее, рвоте; при изменении привычного объема физических нагрузок; при заболеваниях почек, печени, гипофиза, щитовидной железы; при смене места инъекции.
Коррекция дозы инсулина требуется при инфекционных заболеваниях, нарушении функции щитовидной железы, болезни Аддисона, гипопитуитаризме, хронической почечной недостаточности и сахарном диабете у пациентов старше 65 лет.', N'Доза и путь введения препарата определяются индивидуально в каждом конкретном случае на основании содержания глюкозы в крови до еды и через 1-2 ч после еды, а также в зависимости от степени глюкозурии и особенностей течения заболевания.
Вводят, как правило, п/к за 15-20 мин до приема пищи. Места инъекций каждый раз меняют. В случае необходимости допускается в/м или в/в введение.
Можно комбинировать с инсулинами длительного действия.', N'По рецепту')

insert into Features (FeatureID, FeatureName, FeatureDescr)
    values (1, N'Почечная недостаточность',  'Синдром нарушения всех функций почек, приводящий к расстройству водного, электролитного, азотистого и других видов обмена. Различают острую и хроническую почечную недостаточность.'),
    (2, N'Детский возраст до 12 лет', N'--'),
    (3, N'Беременность', N'--'),
    (4, N'Период грудного вскармливания', N'--'),
    (5, N'Подростковый возраст от 12 лет до 18 лет', N'--'),
    (6, N'Взрослый возраст от 19 лет до 60 лет', N'--'),
    (7, N'Старческий возраст от 61 лет', N'--')
    



insert into MedicineFeatures_INT (MedicineID, FeatureID)
    values ('N07XX', 1), ('N07XX', 2), ('N07XX', 3), ('N07XX', 4),
    ('R05C',1), ('R05C',3)



/*-----         Показания         ----- */
--insert into DiseaseMedicine_indications (DiseaseID, MedicineID)
--    values ('I64', 'N07XX'), -- мексидол лечит инсульт
--    ('A15', 'R05C'), -- аскорил лечит туберкулез
--    ('E10', 'A10AB01') -- ринсулин лечит сахарный диабет

/*-----     Противопоказания      ----- */
--insert into DiseaseMedicine_contraindications (DiseaseID, MedicineID)
--    values ('E10', 'R05C') -- прием Ринсулина запрещен больным Сахарным диабетом

insert into DiseaseMedicine_int (DiseaseID, MedicineID, ContradictionsFlag)
    values ('I64', 'N07XX', 1),
    ('A15', 'R05C', 1),
    ('E10', 'A10AB01', 1),
    ('E10', 'R05C', 0)


/*-----   Selects   -----*/

--SELECT * from DiseaseAndClassView

--Select * from Diseases where DiseaseName = N'Инсульт, не уточненный как кровоизлияние или инфаркт'
--Select * from ClassificationOfDiseases
--SELECT * from Medicine


--Select * from MedicineAndFeaturesView

--Select * from DiseaseAndMedicineView

--Select * From DiseaseAndClassView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'
/*Select MedName From DiseaseAndMedicineView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт' 
EXCEPT (Select MedName from MedicineAndFeaturesView where FeatureName = N'Беременность' AND FeatureName=N'Детский возраст до 12 лет')*/

--SELECT * from ClassificationOfDiseases where ClassID = (Select ClassID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт')

--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))
--And (select DiseaseID from Diseases)=(select DiseaseID from DiseaseMedicine_indications) AND (select DiseaseName from Diseases)=N'Инсульт, не уточненный как кровоизлияние или инфаркт')

--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))
--EXCEPT Select * From Medicine where MedicineID=(select MedicineID from MedicineFeatures_INT where FeatureID=(select FeatureID from Features where ((FeatureName=N'Взрослый возраст от 19 лет до 60 лет'))))

--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))
--EXCEPT Select * From Medicine where MedicineID=(select MedicineID from MedicineFeatures_INT where FeatureID=(select FeatureID from Features where ((FeatureName=N'Беременность'))))
--GO

--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))
--EXCEPT select MedicineID from Features join MedicineFeatures_INT on (Features.FeatureID=MedicineFeatures_INT.FeatureID) where FeatureName=N'Беременность' or FeatureName=N'Взрослый возраст от 19 лет до 60 лет'
--GO

--Select * From Medicine where MedicineID=(select MedicineID from MedicineFeatures_INT where FeatureID=(select FeatureID from Features where FeatureName=N'Беременность'))
--select FeatureID from Features where ((FeatureName=N'Взрослый возраст от 19 лет до 60 лет') or (FeatureName=N'Беременность') )

--select * from Features

--select MedicineID from MedicineFeatures_INT where (FeatureID=(select FeatureID from Features where ((FeatureName=N'Беременность'))) and (FeatureID=(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт')))

--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))

--Select * from Medicine where MedicineID=(Select MedicineID from MedicineFeatures_INT where FeatureID=(select FeatureID from Features where FeatureName=N'Беременность'))

--select MedicineID from Features join MedicineFeatures_INT on (Features.FeatureID=MedicineFeatures_INT.FeatureID) where FeatureName=N'Беременность' or FeatureName=N'Взрослый возраст от 19 лет до 60 лет'

--select * from Medicine inner join MedicineFeatures_INT using (MedicineID)


--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))
--EXCEPT Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where FeatureName = N'Беременность'
--EXCEPT Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where FeatureName =N'Взрослый возраст от 19 лет до 60 лет'

--Select * from MedicineAndFeaturesView except (select * from MedicineAndFeaturesView where MedName=N'')


--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'
--except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where FeatureName = N'' or FeatureName=N'Детский возраст до 12 лет'

--Select * From Medicine where MedicineID=(Select MedicineID from DiseaseMedicine_indications where DiseaseID =(select DiseaseID from Diseases where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'))
--except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where FeatureName = N'

--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'
--except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where FeatureName = N'' or FeatureName=N'Взрослый возраст от 19 лет до 60 лет' 

--Select * from MedicineAndFeaturesView
Select * from MedicineAndFeaturesAndContradictionsView

--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Туберкулез органов дыхания, подтвержденный бактериологически и гистологически'
--except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesAndContradictionsView where (FeatureName = N'Беременность' or FeatureName=N'Взрослый возраст от 19 лет до 60 лет')


--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт' except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesAndContradictionsView where FeatureName = N'Взрослый возраст от 19 лет до 60 лет' or FeatureName=N'Беременность'
--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Туберкулез органов дыхания, подтвержденный бактериологически и гистологически' except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesAndContradictionsView where FeatureName = N'Взрослый возраст от 19 лет до 60 лет' or FeatureName=N''

--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт' 
--except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesAndContradictionsView where FeatureName=N'Беременность'

--Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where DiseaseName=N'Инсульт, не уточненный как кровоизлияние или инфаркт'
--except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from MedicineAndFeaturesView where (FeatureName = N'Беременность' or FeatureName=N'Взрослый возраст от 19 лет до 60 лет')
 
select * from DiseaseMedicine_int

Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where (DiseaseName=N'Туберкулез органов дыхания, подтвержденный бактериологически и гистологически' and ContradictionsFlag=1)
except Select MedicineID, MedName, InternationalName, PharmacotherapeuticGroup, PharmacologicalProperties, Caution, HowToUse, Receipt from DiseaseAndMedicineView where (DiseaseName=N'Сахарный диабет' and ContradictionsFlag=0)