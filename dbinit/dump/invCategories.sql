DROP TABLE IF EXISTS "invCategories";
CREATE TABLE "invCategories" (
"categoryID"  INTEGER NOT NULL,
"categoryName"  TEXT(100),
"description"  TEXT(3000),
"published"  INTEGER,
"iconID" smallint(6) default NULL,
"categoryNameID" smallint(6) default NULL,
"dataID" smallint(6) default NULL,
PRIMARY KEY ("categoryID")
);

BEGIN TRANSACTION;
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(0,'#System','',0,0,63539,16545519);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(1,'Owner','',0,0,63540,16545520);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(2,'Celestial','',1,0,63541,16545521);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(3,'Station','',0,0,63542,16545522);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(4,'Material','',1,22,63543,16545523);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(5,'Accessories','',1,33,63560,16545540);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(6,'Ship','',1,0,63544,16545524);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(7,'Module','',1,67,63545,16545525);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(8,'Charge','',1,0,63546,16545526);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(9,'Blueprint','',1,21,63547,16545527);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(10,'Trading','',0,0,63548,16545528);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(11,'Entity','',0,0,63549,16545529);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(14,'Bonus','Character creation bonuses.  Like innate skills but genetic rather than learned.',0,0,63550,16545530);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(16,'Skill','Where all the skills go under.',1,33,63551,16545531);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(17,'Commodity','',1,0,63552,16545532);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(18,'Drone','Player owned and controlled drones.',1,0,63553,16545533);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(20,'Implant','Implant',1,0,63554,16545534);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(22,'Deployable','',1,0,63555,16545535);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(23,'Structure','Player owned structure related objects',1,0,63556,16545536);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(24,'Reaction','',1,0,63557,16545537);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(25,'Asteroid','',1,0,63558,16545538);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(26,'WorldSpace','Worldspaces and related stuff',0,0,63568,16545548);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(29,'Abstract','Abstract grouping, global types and groups for the UI, such as Ranks, Ribbons and Medals.',0,0,63559,16545539);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(30,'Apparel','1. clothing, especially outerwear; garments; attire; raiment.\r\n2. anything that decorates or covers.\r\n3. superficial appearance; aspect; guise. ',1,0,63572,16545551);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(32,'Subsystem','Subsystems for tech 3 ships',1,0,63562,16545542);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(34,'Ancient Relics','',1,0,63561,16545541);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(35,'Decryptors','',1,0,63563,16545543);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(39,'Infrastructure Upgrades','',1,0,63565,16545545);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(40,'Sovereignty Structures','',1,0,63564,16545544);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(41,'Planetary Interaction','Stuff for planetary interaction',1,0,63569,16545549);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(42,'Planetary Resources','These are Items that can be extracted from a planet. ',1,0,63566,16545546);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(43,'Planetary Commodities','',1,0,63567,16545547);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(46,'Orbitals','Anchorable/Onlinable objects that operate similar to POS/SOV structures, but do not link to towers or sovereignty. Each class of orbital defines its own valid anchoring locations via Python code.',1,0,63570,16545555);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(49,'Placeables','Placeables are things you can put into rooms. ',0,0,63571,16545550);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(53,'Effects','',0,0,63573,16545552);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(54,'Lights','',0,0,63574,22244434);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(59,'Cells','',0,0,235965,16545554);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(63,'Special Edition Assets','Special Edition Assets',1,0,285070,85634237);
INSERT INTO invCategories (categoryID,categoryName,description,published,iconID,categoryNameID,dataID) VALUES(350001,'Infantry','',0,0,267649,64275205);
COMMIT TRANSACTION;
