
import yaml
import json
import sqlite3
from functools import reduce
import operator
import time

def f():
    return None


def load(path):
    t0 = time.time()
    s=open(path, "r", encoding="utf-8").read()
    result = yaml.load(s, yaml.CLoader)
    if isinstance(result, dict):
        result = result#.items()
    t1 = time.time()
    print('yaml: {} {}s'.format(path, int((t1 - t0))))
    return result

f=open('./tmp/sde/typeIDs.json', 'r', encoding='utf-8')
j=json.load(f)

#y=load("./tmp/sde/fsd/typeIDs.yaml")
#f=open('./tmp/sde/typeIDs.json', 'w', encoding='utf-8')
#json.dump(y, f)
#f.write(json.dump(y))
#f.close()

#db = sqlite3.connect(':memory:')
db = sqlite3.connect("./tmp/db.sqlite")
c = db.cursor()
c.execute('''
CREATE TABLE invCategories (
"categoryID"  tinyint(3) NOT NULL,
"categoryName"  TEXT(100),
"published"  tinyint(1),
PRIMARY KEY ("categoryID")
);
''')

c.execute('''
CREATE TABLE invGroups (
  "groupID" smallint(6) NOT NULL,
  "groupName" varchar(100) DEFAULT NULL,
  "categoryID" tinyint(3) default NULL,
  "published"  tinyint(1),
  PRIMARY KEY  ("groupID")
);
''')

c.execute('''
CREATE TABLE invTypes (
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
  "metaGroupID" integer default NULL,
  "parentTypeID" integer default NULL,
  PRIMARY KEY  ("typeID")
);
''')

c.execute('''
CREATE TABLE dgmAttributeTypes (
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
''')

c.execute('''
CREATE TABLE dgmTypeAttributes (
  "typeID" smallint(6) NOT NULL,
  "attributeID" smallint(6) NOT NULL,
  "value" double default NULL,
  PRIMARY KEY  ("typeID","attributeID")
);
''')

c.execute('''
CREATE TABLE dgmTypeEffects (
  "typeID" smallint(6) NOT NULL,
  "effectID" smallint(6) NOT NULL,
  "isDefault" tinyint(1) default NULL,
  PRIMARY KEY  ("typeID","effectID")
);
''')

c.execute('''
CREATE TABLE dgmEffects (
  "effectID"  smallint(6),
  "effectName"  TEXT(400),
  "effectCategory"  TEXT(100),
  "isOffensive"  INTEGER,
  "isAssistance"  INTEGER,
  "modifierInfo" TEXT,
  PRIMARY KEY ("effectID")
);
''')

c.execute('''
CREATE TABLE planetSchematics (
"schematicID" smallint(6) NOT NULL,
"schematicName" varchar(255) DEFAULT NULL,
"cycleTime" integer DEFAULT NULL,
PRIMARY KEY ("schematicID")
);
''')

c.execute('''
CREATE TABLE planetSchematicsPinMap (
"schematicID" smallint(6) NOT NULL,
"pinTypeID" integer NOT NULL,
PRIMARY KEY ("schematicID","pinTypeID")
);
''')

c.execute('''
CREATE TABLE planetSchematicsTypeMap (
"schematicID" smallint(6) NOT NULL,
"typeID" integer NOT NULL,
"quantity" integer DEFAULT NULL,
"isInput" integer DEFAULT NULL,
PRIMARY KEY ("schematicID","typeID")
);
''')

def find(element, json):
    try:
        return reduce(operator.getitem, element.split('.'), json)
    except:
        return None
def insert(table, id, keys, row):
    values=[id] + [find(x, row) for x in keys]
    marks = ','.join(['?' for x in values])
    sql='INSERT INTO {} VALUES ({})'.format(table, marks)
    c.execute(sql, tuple(values))
    

for id, row in load("./tmp/sde/fsd/categoryIDs.yaml"):
    insert('invCategories', id, ['name.en', 'published'], row)

for id, row in load("./tmp/sde/fsd/groupIDs.yaml"):
    insert('invGroups', id, ['name.en', 'categoryID', 'published'], row)

for id, row in load("./tmp/sde/fsd/dogmaAttributes.yaml"):
    insert('dgmAttributeTypes', id, ['name', 'displayNameID.en', 'maxAttributeID', 'defaultValue', 'stackable', 'highIsGood', 'categoryID'], row)

for id, row in load("./tmp/sde/fsd/dogmaEffects.yaml"):
    modifierInfo = find('modifierInfo', row)
    if modifierInfo:
        row['modifierInfo'] = yaml.dump(modifierInfo)
    insert('dgmEffects', id, ['effectName', 'effectCategory', 'isOffensive', 'isAssistance', 'modifierInfo'], row)

for id, row in load("./tmp/sde/fsd/typeIDs.yaml"):
    insert('invTypes', id, ['groupID', 'name.en', 'radius', 'mass', 'valume', 'capacity', 'portionSize', 'raceID', 'published', 'metaGroupID', 'variationParentTypeID'], row)

for id, type in load("./tmp/sde/fsd/typeDogma.yaml"):
    try:
        for row in find("dogmaAttributes", type):
            insert('dgmTypeAttributes', id, ['attributeID', 'value'], row)
    except:
        pass
    try:
        for row in find("dogmaEffects", type):
            insert('dgmTypeEffects', id, ['effectID', 'isDefault'], row)
    except:
        pass

for row in load("./tmp/sde/bsd/planetSchematics.yaml"):
    insert('planetSchematics', row['schematicID'], ['schematicName', 'cycleTime'], row)

for row in load("./tmp/sde/bsd/planetSchematicsPinMap.yaml"):
    insert('planetSchematicsPinMap', row['schematicID'], ['pinTypeID'], row)

for row in load("./tmp/sde/bsd/planetSchematicsTypeMap.yaml"):
    insert('planetSchematicsTypeMap', row['schematicID'], ['typeID', 'quantity', 'isInput'], row)
db.commit()
db.close()
