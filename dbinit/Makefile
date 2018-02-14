SHELL:=/bin/sh
CC=g++
#CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
CFLAGS=-std=gnu++14 -fvisibility-inlines-hidden
OUTPUT_DIR+=./
DUMP=${PWD}/dump
SQL=${PWD}/sql
T+=${PWD}/tmp
SDE=${PWD}/../src/SDE

all: dgm.sqlite AttributeID.hpp Attributes.hpp CategoryID.hpp EffectID.hpp Effects.hpp GroupID.hpp Modifiers.hpp Skills.hpp TypeID.hpp Types.hpp WarfareBuffID.hpp WarfareBuffs.hpp Commodities.hpp Facilities.hpp SchematicID.hpp Schematics.hpp

dgm-tool: tmp
	$(CC) $(CFLAGS) ../tools/dgm-tool/src/Compiler.cpp ../tools/dgm-tool/src/main.cpp ../tools/dgm-tool/src/modifiersdump.cpp ../tools/dgm-tool/src/SQLiteDatabase.cpp -o $(T)/$@ -lsqlite3

dgmExpressions.sql:
	cd $(T); ${DUMP}/dump.py

dbpatch: dbpatch.h
	$(CC) $(CFLAGS) ../tools/dbpatch/dbpatch/dbpatch.cpp -o $(T)/$@ -lsqlite3 -I $(T)/

dbpatch.h: dgm-tool dgmExpressions.sql
	cd $(T); sqlite3 $(T)/dump.sqlite ".read $(SQL)/dump.sql"
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dumpPatch.sql"
	$(T)/dgm-tool $(T)/dump.sqlite --convertModifiers > $(T)/dbpatch.h


dump.sqlite: dbpatch
	$(T)/dbpatch $(T)/dump.sqlite


dgmModifiers.sql: dump.sqlite dgm-tool
	$(T)/dgm-tool $(T)/dump.sqlite --compile > $(T)/dgmModifiers.sql

dgm.sqlite: dgmModifiers.sql
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dgmpp.sql"
	sqlite3 dgm.sqlite ".read $(T)/dgmModifiers.sql"
	sqlite3 dgm.sqlite "vacuum"
	mv ./dgm.sqlite $(OUTPUT_DIR)/dgm.sqlite

tmp:
	mkdir -p $(T)

clean:
	echo ${T}
	rm -rf ${T}
	rm -f *.sqlite

AttributeID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --attributeIDs > ${T}/AttributeID.hpp
	cp -rf ${T}/AttributeID.hpp $(SDE)/AttributeID.hpp

TypeID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --typeIDs > ${T}/TypeID.hpp
	cp -rf ${T}/TypeID.hpp $(SDE)/TypeID.hpp

GroupID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --groupIDs > ${T}/GroupID.hpp
	cp -rf ${T}/GroupID.hpp $(SDE)/GroupID.hpp

CategoryID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --categoryIDs > ${T}/CategoryID.hpp
	cp -rf ${T}/CategoryID.hpp $(SDE)/CategoryID.hpp

EffectID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --effectIDs > ${T}/EffectID.hpp
	cp -rf ${T}/EffectID.hpp $(SDE)/EffectID.hpp

WarfareBuffID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --warfareBuffIDs > ${T}/WarfareBuffID.hpp
	cp -rf ${T}/WarfareBuffID.hpp $(SDE)/WarfareBuffID.hpp

Attributes.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --attributes > ${T}/Attributes.hpp
	cp -rf ${T}/Attributes.hpp $(SDE)/Attributes.hpp

Types.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --types > ${T}/Types.hpp
	cp -rf ${T}/Types.hpp $(SDE)/Types.hpp

Modifiers.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --modifiers > ${T}/Modifiers.hpp
	cp -rf ${T}/Modifiers.hpp $(SDE)/Modifiers.hpp

Effects.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --effects > ${T}/Effects.hpp
	cp -rf ${T}/Effects.hpp $(SDE)/Effects.hpp

WarfareBuffs.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --warfareBuffs > ${T}/WarfareBuffs.hpp
	cp -rf ${T}/WarfareBuffs.hpp $(SDE)/WarfareBuffs.hpp

Skills.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --skills > ${T}/Skills.hpp
	cp -rf ${T}/Skills.hpp $(SDE)/Skills.hpp

Commodities.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --commodities > ${T}/Commodities.hpp
	cp -rf ${T}/Commodities.hpp $(SDE)/Commodities.hpp

Facilities.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --facilities > ${T}/Facilities.hpp
	cp -rf ${T}/Facilities.hpp $(SDE)/Facilities.hpp

SchematicID.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --schematicIDs > ${T}/SchematicID.hpp
	cp -rf ${T}/SchematicID.hpp $(SDE)/SchematicID.hpp

Schematics.hpp: dgm-tool dgm.sqlite
	$(T)/dgm-tool $(OUTPUT_DIR)/dgm.sqlite --schematics > ${T}/Schematics.hpp
	cp -rf ${T}/Schematics.hpp $(SDE)/Schematics.hpp
