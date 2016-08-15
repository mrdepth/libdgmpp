#!/usr/bin/python
from sys import platform
from os.path import expanduser
import glob
import sys
import os
import ConfigParser

from reverence import blue

if platform == "darwin":
	#folders = glob.glob(expanduser("~/Library/Application Support/EVE Online/p_drive/Local Settings/Application Data/CCP/EVE/SharedCache/cider-EveOnlinePremium-iso-*"))
	#folders = sorted(folders, None, None, reverse=True)
	#if len(folders) == 0:
	#	print "Error: EVE Online client not found"
	#	sys.exit
	#else:
	#	EVEPATH = folders[0] + "/EVE Online.app/Contents/Resources/transgaming/c_drive/tq"
	EVEPATH = glob.glob(expanduser("~/Library/Application Support/EVE Online/p_drive/Local Settings/Application Data/CCP/EVE/SharedCache/wineenv/drive_c/tq"))[0]
else:
	EVEPATH = "E:/Games/EVE"

OUTPATH = "./"

eve = blue.EVE(EVEPATH, cachepath=expanduser("~/Library/Application Support/EVE Online/p_drive/Local Settings/Application Data/CCP/EVE/c_tq_tranquility"))
cfg = eve.getconfigmgr()

def sqlstr(x):
	t = type(x)
	if t in (list, tuple, dict):
		raise ValueError("Unsupported type")
	if t is unicode:
		return repr(x)[1:].replace("\\'","''")
	if t is str:
		return repr(x).replace("\\'","''")
	if t is bool:
		#return repr(x).lower()
		if x:
			return "1"
		else:
			return "0"
	else:
		r = str(x)
		r = r.replace("e+", "E").replace("e-", "E-")
		if r.endswith(".0"):
			r = r[:-2]
		if r == "None":
			return "null"
		return r

def dump(table, header, lines):
	# see what we can pull out of the hat...
	f = []
	f2 = open( os.path.join(OUTPATH, table) + ".sql", "w")
	f.append("BEGIN TRANSACTION;")
	if (table == "dgmExpressions"):
			f.append("DROP TABLE IF EXISTS dgmExpressions;\nCREATE TABLE \"dgmExpressions\" (\n\"expressionID\"  INTEGER NOT NULL,\n\"operandID\"  INTEGER NOT NULL,\n\"arg1\"  INTEGER,\n\"arg2\"  INTEGER,\n\"expressionValue\"  TEXT,\n\"description\"  TEXT,\n\"expressionName\"  TEXT,\n\"expressionTypeID\"  INTEGER,\n\"expressionGroupID\"  INTEGER,\n\"expressionAttributeID\"  INTEGER,\nPRIMARY KEY (\"expressionID\")\n);")
	elif (table == "dgmOperands"):
		f.append("DROP TABLE IF EXISTS dgmOperands;\nCREATE TABLE \"dgmOperands\" (\n\"operandID\"  INTEGER NOT NULL,\n\"operandKey\"  TEXT,\n\"description\"  TEXT,\n\"format\"  TEXT,\n\"arg1categoryID\"  INTEGER,\n\"arg2categoryID\"  INTEGER,\n\"resultCategoryID\"  INTEGER,\n\"pythonFormat\"  TEXT,\nPRIMARY KEY (\"operandID\")\n);")
	elif (table == "invTypes"):
		f.append("DROP TABLE IF EXISTS invTypes;\nCREATE TABLE invTypes (\n  \"typeID\"  INTEGER NOT NULL,\n  \"groupID\"  INTEGER,\n  \"typeName\" varchar(100) default NULL,\n  \"description\" varchar(3000) default NULL,\n  \"graphicID\" smallint(6) default NULL,\n  \"radius\" double default NULL,\n  \"mass\" double default NULL,\n  \"volume\" double default NULL,\n  \"capacity\" double default NULL,\n  \"portionSize\" int(11) default NULL,\n  \"raceID\" tinyint(3) default NULL,\n  \"basePrice\" double default NULL,\n  \"published\" tinyint(1) default NULL,\n  \"marketGroupID\" smallint(6) default NULL,\n  \"chanceOfDuplicating\" double default NULL,\n  soundID smallint(6) default NULL,\n  \"iconID\" smallint(6) default NULL,\n  dataID smallint(6) default NULL,\n  typeNameID smallint(6) default NULL,\n  descriptionID smallint(6) default NULL,\n  copyTypeID smallint(6) default NULL,\n  PRIMARY KEY  (\"typeID\")\n);")
	elif (table == "dgmTypeAttributes"):
		f.append("DROP TABLE IF EXISTS dgmTypeAttributes;\nCREATE TABLE \"dgmTypeAttributes\" (\n \"typeID\"  INTEGER NOT NULL,\n \"attributeID\"  INTEGER NOT NULL,\n \"value\"  double default NULL,\n PRIMARY KEY (\"typeID\", \"attributeID\")\n);")
	elif (table == "dgmAttributeTypes"):
		f.append("DROP TABLE IF EXISTS dgmAttributeTypes;\nCREATE TABLE dgmAttributeTypes (\n  \"attributeID\" smallint(6) NOT NULL,\n  \"attributeName\" varchar(100) default NULL,\n  attributeCategory smallint(6) NOT NULL,\n  \"description\" varchar(1000) default NULL,\n  maxAttributeID smallint(6) default NULL,\n  attributeIdx smallint(6) default NULL,\n  chargeRechargeTimeID smallint(6) default NULL,\n  \"defaultValue\" double default NULL,\n  \"published\" tinyint(1) default NULL,\n  \"displayName\" varchar(100) default NULL,\n  \"unitID\" tinyint(3) default NULL,\n  \"stackable\" tinyint(1) default NULL,\n  \"highIsGood\" tinyint(1) default NULL,\n  \"categoryID\" tinyint(3) default NULL,\n  \"iconID\" smallint(6) default NULL,\n  displayNameID smallint(6) default NULL,\n  tooltipTitleID smallint(6) default NULL,\n  tooltipDescriptionID smallint(6) default NULL,\n  dataID smallint(6) default NULL,\n  PRIMARY KEY  (\"attributeID\")\n);")
	elif (table == "dgmEffects"):
		f.append("DROP TABLE IF EXISTS dgmEffects;\nCREATE TABLE dgmEffects (\n\"effectID\"  INTEGER NOT NULL,\n\"effectName\"  TEXT(400),\n\"effectCategory\"  INTEGER,\n\"preExpression\"  INTEGER,\n\"postExpression\"  INTEGER,\n\"description\"  TEXT(1000),\n\"guid\"  TEXT(60),\n\"isOffensive\"  INTEGER,\n\"isAssistance\"  INTEGER,\n\"durationAttributeID\"  INTEGER,\n\"trackingSpeedAttributeID\"  INTEGER,\n\"dischargeAttributeID\"  INTEGER,\n\"rangeAttributeID\"  INTEGER,\n\"falloffAttributeID\"  INTEGER,\n\"disallowAutoRepeat\"  INTEGER,\n\"published\"  INTEGER,\n\"displayName\"  TEXT(100),\n\"isWarpSafe\"  INTEGER,\n\"rangeChance\"  INTEGER,\n\"electronicChance\"  INTEGER,\n\"propulsionChance\"  INTEGER,\n\"distribution\"  INTEGER,\n\"sfxName\"  TEXT(20),\n\"npcUsageChanceAttributeID\"  INTEGER,\n\"npcActivationChanceAttributeID\"  INTEGER,\n\"fittingUsageChanceAttributeID\"  INTEGER,\n\"iconID\" smallint(6) default NULL,\n\"displayNameID\" smallint(6) default NULL,\n\"descriptionID\" smallint(6) default NULL,\n\"resistanceID\" smallint(6) default NULL,\n\"modifierInfo\"  TEXT(1000),\n\"dataID\" smallint(6) default NULL,\nPRIMARY KEY (\"effectID\")\n);")
	elif (table == "dgmTypeEffects"):
		f.append("DROP TABLE IF EXISTS \"dgmTypeEffects\";\nCREATE TABLE \"dgmTypeEffects\" (\n\"typeID\"  INTEGER NOT NULL,\n\"effectID\"  INTEGER NOT NULL,\n\"isDefault\"  INTEGER,\nPRIMARY KEY (\"typeID\", \"effectID\")\n);")
	elif (table == "invCategories"):
		f.append("DROP TABLE IF EXISTS \"invCategories\";\nCREATE TABLE \"invCategories\" (\n\"categoryID\"  INTEGER NOT NULL,\n\"categoryName\"  TEXT(100),\n\"description\"  TEXT(3000),\n\"published\"  INTEGER,\n\"iconID\" smallint(6) default NULL,\n\"categoryNameID\" smallint(6) default NULL,\n\"dataID\" smallint(6) default NULL,\nPRIMARY KEY (\"categoryID\")\n);")
	elif (table == "invGroups"):
		f.append("DROP TABLE IF EXISTS \"invGroups\";\nCREATE TABLE \"invGroups\" (\n\"groupID\" INTEGER NOT NULL,\n\"categoryID\"  INTEGER,\n\"groupName\"  TEXT(100),\n\"description\"  TEXT(3000),\n\"useBasePrice\"  INTEGER,\n\"allowManufacture\"  INTEGER,\n\"allowRecycler\"  INTEGER,\n\"anchored\"  INTEGER,\n\"anchorable\"  INTEGER,\n\"fittableNonSingleton\"  INTEGER,\n\"published\"  INTEGER,\n\"iconID\"   smallint(6) default NULL,\n\"groupNameID\"   smallint(6) default NULL,\n\"dataID\"   smallint(6) default NULL,\nPRIMARY KEY (\"groupID\")\n);")
	elif (table == "invControlTowerResources"):
		f.append("DROP TABLE IF EXISTS invControlTowerResources;\nCREATE TABLE invControlTowerResources (\n  \"controlTowerTypeID\" int(11) NOT NULL,\n  \"resourceTypeID\" int(11) NOT NULL,\n  \"purpose\" tinyint(4) default NULL,\n  \"quantity\" int(11) default NULL,\n  \"minSecurityLevel\" double default NULL,\n  \"factionID\" int(11) default NULL,\n  \"wormholeClassID\" INTEGER default NULL,\n  PRIMARY KEY  (\"controlTowerTypeID\",\"resourceTypeID\")\n);")
	elif (table == "planetSchematics"):
		f.append("DROP TABLE IF EXISTS planetSchematics;\nCREATE TABLE planetSchematics (\n \"schematicID\" integer NOT NULL,\n \"schematicName\" varchar(255) DEFAULT NULL,\n \"cycleTime\" integer DEFAULT NULL,\n PRIMARY KEY (\"schematicID\"));");
	elif (table == "planetSchematicsPinMap"):
		f.append("DROP TABLE IF EXISTS planetSchematicsPinMap;\nCREATE TABLE planetSchematicsPinMap (\n \"schematicID\" integer NOT NULL,\n \"pinTypeID\" integer DEFAULT NULL,\n PRIMARY KEY (\"schematicID\",\"pinTypeID\"));");
	elif (table == "planetSchematicsTypeMap"):
		f.append("DROP TABLE IF EXISTS planetSchematicsTypeMap;\nCREATE TABLE planetSchematicsTypeMap (\n \"schematicID\" integer NOT NULL,\n \"typeID\" integer NOT NULL,\n \"quantity\" integer DEFAULT NULL,\n \"isInput\" integer DEFAULT NULL,\n PRIMARY KEY (\"schematicID\",\"typeID\"));");
	elif (table == "invMarketGroups"):
		f.append("DROP TABLE IF EXISTS invMarketGroups;\nCREATE TABLE invMarketGroups (\n \"parentGroupID\" integer DEFAULT NULL,\n \"marketGroupID\" integer NOT NULL,\n \"marketGroupName\" varchar(100) DEFAULT NULL,\n \"description\" varchar(3000) DEFAULT NULL,\n \"graphicID\" integer DEFAULT NULL,\n  \"hasTypes\" integer DEFAULT NULL,\n \"iconID\" integer DEFAULT NULL,\n  \"dataID\" integer DEFAULT NULL,\n  \"marketGroupNameID\" integer DEFAULT NULL,\n  \"descriptionID\" integer DEFAULT NULL,\n  PRIMARY KEY (\"marketGroupID\"));");
	f.append("")

	name = table
	item = name.split(".")[-1]

	# create XML file and dump the lines.
	try:
		for line in lines:
			line = ','.join([sqlstr(getattr(line, x) if hasattr(line,x) else None) for x in header])
			f.append("INSERT INTO %s (%s) VALUES(%s);" % (item, ','.join(header), line))


		#print "OK"
	except:
		print "FAILED " + table
	f.append("COMMIT TRANSACTION;");
	for line in f:
		print >>f2, line
	del f
	f2.close()

def map(header, objects):
	return [objects.Get(key) for key in objects.keys()]

config = ConfigParser.RawConfigParser(allow_no_value=True)
config.read(os.path.join(EVEPATH, "start.ini"))
version = config.get("main", "version")
build = config.get("main", "build")

f = open( os.path.join(OUTPATH, "version.sql"), "w")
print >>f, "DROP TABLE IF EXISTS version;\nCREATE TABLE \"version\" (\n\"build\"  INTEGER NOT NULL,\n\"version\"  TEXT,\nPRIMARY KEY (\"build\"));"
print >>f, "INSERT INTO version (build, version) VALUES (%s, \"%s\");" % (build, version)
f.close()


cache = eve.getcachemgr()
res = cache.LoadCachedMethodCall(("dogma", "GetOperandsForChar"));
dgmOperands = cache.LoadCachedMethodCall(("dogma", "GetOperandsForChar"))["lret"].values()
dgmOperandsHeader = dgmOperands[0].__header__.Keys()

v = cache.LoadCachedMethodCall(("marketProxy", "GetMarketGroups"))

invMarketGroups = [r for rows in cache.LoadCachedMethodCall(("marketProxy", "GetMarketGroups"))["lret"].values() for r in rows]
for row in invMarketGroups:
	key = row["marketGroupNameID"]
	if (key and cfg._localization.primary.has_key(int(key))):
		row.__setattr__("marketGroupName", cfg._localization.primary[int(key)][0])
invMarketGroupsHeader = invMarketGroups[0].__header__.Keys()


#dump (cfg.dgmexpressions, "dgmExpressions")

invTypesHeader = ("typeID", "groupID", "typeName", "description", "radius", "mass", "volume", "capacity", "portionSize", "raceID", "published", "marketGroupID", "iconID", "basePrice")
invGroupsHeader = ("groupID", "groupName", "categoryID", "published", "iconID")
invCategoriesHeader = ("categoryID", "categoryName", "published", "iconID")
invTypeAttributesHeader = ("typeID", "attributeID", "value")
invTypeEffectsHeader = ("typeID", "effectID", "isDefault")
planetSchematicsHeader = ("schematicID", "schematicName", "cycleTime")

invTypes = map(invTypesHeader, cfg.invtypes)
invGroups = map(invGroupsHeader, cfg.invgroups)
invCategories = map(invCategoriesHeader, cfg.invcategories)
invTypeAttributes = [r for rows in cfg.dgmtypeattribs.values() for r in rows]
invTypeEffects = [r for rows in cfg.dgmtypeeffects.values() for r in rows]
planetSchematicsPinMap = [r for rows in cfg.schematicspinmap.items.values() for r in rows]
planetSchematicsTypeMap = [r for rows in cfg.schematicstypemap.items.values() for r in rows]

dump ("invMarketGroups", invMarketGroupsHeader, invMarketGroups)
dump ("dgmOperands", dgmOperandsHeader, dgmOperands)
dump ("invCategories", invCategoriesHeader, invCategories)
dump ("invGroups", invGroupsHeader, invGroups)
dump ("invTypes", invTypesHeader, invTypes)
dump ("dgmEffects", cfg.dgmeffects.header, cfg.dgmeffects.values())
dump ("dgmTypeEffects", invTypeEffectsHeader, invTypeEffects)
dump ("dgmExpressions", cfg.dgmexpressions.header, cfg.dgmexpressions.values())
dump ("dgmAttributeTypes", cfg.dgmattribs.header, cfg.dgmattribs.values())
dump ("dgmTypeAttributes", invTypeAttributesHeader, invTypeAttributes)
dump ("planetSchematics", planetSchematicsHeader, cfg.schematics.values())
dump ("planetSchematicsPinMap", cfg.schematicspinmap.header, planetSchematicsPinMap)
dump ("planetSchematicsTypeMap", cfg.schematicstypemap.header, planetSchematicsTypeMap)
