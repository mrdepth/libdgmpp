DROP TABLE IF EXISTS dgmpp.invGroups;
CREATE TABLE dgmpp.invGroups (
  "groupID" smallint(6) NOT NULL,
  "categoryID" tinyint(3) default NULL,
  "groupName" varchar(100) DEFAULT NULL,
  PRIMARY KEY  ("groupID")
);
DROP TABLE IF EXISTS dgmpp.invTypes;
CREATE TABLE dgmpp.invTypes (
  "typeID" int(11) NOT NULL,
  "groupID" smallint(6) default NULL,
  "typeName" varchar(100) default NULL,
  "radius" double default NULL,
  "mass" double default NULL,
  "volume" double default NULL,
  "capacity" double default NULL,
  "portionSize" int(11) default NULL,
  "raceID" tinyint(3) default NULL,
  "published" tinyint(1) default NULL,
  PRIMARY KEY  ("typeID")
);
DROP TABLE IF EXISTS dgmpp.dgmAttributeTypes;
CREATE TABLE dgmpp.dgmAttributeTypes (
  "attributeID" smallint(6) NOT NULL,
  "attributeName" varchar(100) default NULL,
  "displayName" varchar(100) default NULL,
  "maxAttributeID" smallint(6) default NULL,
  "defaultValue" double default NULL,
  "stackable" tinyint(1) default NULL,
  "highIsGood" tinyint(1) default NULL,
  "categoryID" tinyint(3) default NULL,
  PRIMARY KEY  ("attributeID")
);
DROP TABLE IF EXISTS dgmpp.dgmTypeAttributes;
CREATE TABLE dgmpp.dgmTypeAttributes (
  "typeID" smallint(6) NOT NULL,
  "attributeID" smallint(6) NOT NULL,
  "value" double default NULL,
  PRIMARY KEY  ("typeID","attributeID")
);
DROP TABLE IF EXISTS dgmpp.dgmTypeEffects;
CREATE TABLE dgmpp.dgmTypeEffects (
  "typeID" smallint(6) NOT NULL,
  "effectID" smallint(6) NOT NULL,
  "isDefault" tinyint(1) default NULL,
  PRIMARY KEY  ("typeID","effectID")
);
--DROP TABLE IF EXISTS dgmpp.invCategories;
--CREATE TABLE dgmpp.invCategories (
--"categoryID"  tinyint(3) NOT NULL,
--"categoryName"  TEXT(100),
--"description"  TEXT(3000),
--"published"  tinyint(1),
--"iconID" smallint(6) default NULL,
--"categoryNameID" smallint(6) default NULL,
--"dataID" smallint(6) default NULL,
--PRIMARY KEY ("categoryID")
--);
DROP TABLE IF EXISTS dgmpp.invCategories;
CREATE TABLE dgmpp.invCategories (
"categoryID"  tinyint(3) NOT NULL,
"categoryName"  TEXT(100),
"iconID" smallint(6) default NULL,
"published"  tinyint(1),
PRIMARY KEY ("categoryID")
);

DROP TABLE IF EXISTS dgmpp.dgmEffects;
CREATE TABLE dgmpp.dgmEffects (
"effectID"  INTEGER NOT NULL,
"effectName"  TEXT(400),
"effectCategory"  INTEGER,
"isOffensive"  INTEGER,
"isAssistance"  INTEGER,
PRIMARY KEY ("effectID")
);

INSERT INTO dgmpp.invGroups SELECT groupID, categoryID, groupName  FROM invGroups;
INSERT INTO dgmpp.invTypes SELECT typeID, groupID, typeName, radius, mass, volume, capacity, portionSize, raceID, published FROM invTypes;
INSERT INTO dgmpp.dgmAttributeTypes SELECT attributeID, attributeName, displayName, maxAttributeID, defaultValue, stackable, highIsGood, categoryID FROM dgmAttributeTypes;
INSERT INTO dgmpp.dgmTypeAttributes SELECT * FROM dgmTypeAttributes;
INSERT INTO dgmpp.dgmTypeEffects SELECT * FROM dgmTypeEffects;
INSERT INTO dgmpp.invCategories SELECT categoryID, categoryName, iconID, published FROM invCategories;
INSERT INTO dgmpp.dgmEffects SELECT effectID, effectName, effectCategory, isOffensive, isAssistance  FROM dgmEffects;

CREATE INDEX dgmpp.invGroups_categoryID ON "invGroups" ("categoryID" ASC);
CREATE INDEX dgmpp.invTypes_groupID_published ON "invTypes" ("groupID" ASC, "published" ASC);
CREATE INDEX dgmpp.invTypes_typeName ON "invTypes" ("typeName" ASC);