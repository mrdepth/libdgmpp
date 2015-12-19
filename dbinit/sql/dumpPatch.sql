--Missing groupID fix
UPDATE dgmExpressions SET expressionGroupID=74 WHERE expressionID=663;
UPDATE dgmExpressions SET expressionGroupID=55 WHERE expressionID=649;
UPDATE dgmExpressions SET expressionGroupID=53 WHERE expressionID=658;
UPDATE dgmExpressions SET expressionGroupID=54 WHERE expressionID=641;
UPDATE dgmExpressions SET expressionGroupID=54 WHERE expressionID=641;

--Missing typeID fix
UPDATE dgmExpressions SET expressionTypeID=3422 WHERE expressionID=1728;
UPDATE dgmExpressions SET expressionTypeID=3423 WHERE expressionID=1555;
UPDATE dgmExpressions SET expressionTypeID=3452 WHERE expressionID=1506;

--Online effect fix
UPDATE dgmEffects SET preExpression=399 WHERE effectID=16;

DELETE FROM "dgmEffects" WHERE effectID IN (10000, 10001, 10002, 10003);

INSERT INTO "dgmEffects" (effectID,effectName,effectCategory,preExpression,postExpression,description,isOffensive,isAssistance)
 VALUES ("10000","characterDamageMissiles","0","0","0","eufe: Character missileDamageMultiplier bonus","0","0");

DELETE FROM "dgmTypeEffects" WHERE effectID IN (10000, 10001, 10002, 10003);

INSERT INTO "dgmTypeEffects" VALUES ("1381","10000","0");

--Warp Disruption Field Generator Fix
DELETE FROM "dgmTypeEffects" WHERE effectID=3461;

INSERT INTO "dgmTypeEffects" VALUES ("4248","3461","0");
INSERT INTO "dgmTypeEffects" VALUES ("28654","3461","0");

--Tactical Modes
INSERT INTO "dgmEffects" (effectID,effectName,effectCategory,preExpression,postExpression,description,isOffensive,isAssistance)
VALUES ("10002","tacticalMode","0","131","131","eufe: Tactical Mode Slot","0","0");
INSERT INTO "dgmAttributeTypes" (attributeID,attributeName,attributeCategory,published,unitID,displayName,description,stackable,highIsGood,categoryID,iconID)
VALUES (10000, "tacticalModes", 4, 0, 122, "Tactical Modes", "eufe: Tactical Modes bonus", 1, 1, 1, NULL);

--Confessor
INSERT INTO "dgmTypeEffects" VALUES ("34319","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("34321","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("34323","10002","0");

INSERT INTO "dgmTypeAttributes" VALUES (34319,1302,34317);
INSERT INTO "dgmTypeAttributes" VALUES (34321,1302,34317);
INSERT INTO "dgmTypeAttributes" VALUES (34323,1302,34317);

INSERT INTO "dgmTypeAttributes" VALUES (34317,10000,1);

--Svipul
INSERT INTO "dgmTypeEffects" VALUES ("34564","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("34566","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("34570","10002","0");

INSERT INTO "dgmTypeAttributes" VALUES (34564,1302,34562);
INSERT INTO "dgmTypeAttributes" VALUES (34566,1302,34562);
INSERT INTO "dgmTypeAttributes" VALUES (34570,1302,34562);

INSERT INTO "dgmTypeAttributes" VALUES (34562,10000,1);

--Jackdaw
INSERT INTO "dgmTypeEffects" VALUES ("35676","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("35677","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("35678","10002","0");

INSERT INTO "dgmTypeAttributes" VALUES (35676,1302,34828);
INSERT INTO "dgmTypeAttributes" VALUES (35677,1302,34828);
INSERT INTO "dgmTypeAttributes" VALUES (35678,1302,34828);

INSERT INTO "dgmTypeAttributes" VALUES (34828,10000,1);

--Hecate
INSERT INTO "dgmTypeEffects" VALUES ("35686","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("35687","10002","0");
INSERT INTO "dgmTypeEffects" VALUES ("35688","10002","0");

INSERT INTO "dgmTypeAttributes" VALUES (35686,1302,35683);
INSERT INTO "dgmTypeAttributes" VALUES (35687,1302,35683);
INSERT INTO "dgmTypeAttributes" VALUES (35688,1302,35683);

INSERT INTO "dgmTypeAttributes" VALUES (35683,10000,1);

--Ancillary Armor Repairer fix
INSERT INTO "dgmAttributeTypes" (attributeID,attributeName,attributeCategory,published,unitID,displayName,description,stackable,highIsGood,categoryID,iconID)
VALUES (10002, "chargedArmorDamageMultiplierPostDiv", 5, 0, 0, NULL, "eufe: Ancillary Armor Repairer chargedArmorDamageMultiplier bonus", 1, 1, 1, NULL);

INSERT INTO "dgmEffects" (effectID,effectName,effectCategory,preExpression,postExpression,description,isOffensive,isAssistance)
VALUES ("10001","naniteRepairPasteArmorDamageBonus","0","59","59","eufe: Ancillary Armor Repairer chargedArmorDamageMultiplier bonus","0","0");
INSERT INTO "dgmEffects" (effectID,effectName,effectCategory,preExpression,postExpression,description,isOffensive,isAssistance)
VALUES ("10003","fueledArmorRepairBonus","0","59","59","eufe: Ancillary Armor Repairer chargedArmorDamageMultiplier bonus","0","0");

INSERT INTO dgmTypeAttributes SELECT typeID, 10002 as attributeID, value FROM dgmTypeAttributes WHERE attributeID=1886;
INSERT INTO dgmTypeEffects SELECT typeID, 10003, 1 FROM dgmTypeEffects WHERE effectID=5275;

INSERT INTO "dgmTypeEffects" VALUES ("28668","10001","0");
INSERT INTO "dgmTypeAttributes" VALUES ("28668","10002","1");
