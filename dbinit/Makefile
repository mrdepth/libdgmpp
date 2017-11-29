SHELL:=/bin/sh
CC=g++
#CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
CFLAGS=-std=gnu++14 -fvisibility-inlines-hidden
OUTPUT_DIR+=./
DUMP=${PWD}/dump
SQL=${PWD}/sql
T+=${PWD}/tmp

all: dgm.sqlite AttributeID.hpp Attributes.hpp CategoryID.hpp EffectID.hpp Effects.hpp GroupID.hpp Modifiers.hpp Skills.hpp TypeID.hpp Types.hpp WarfareBuffID.hpp WarfareBuffs.hpp Commodities.hpp Facilities.hpp SchematicID.hpp Schematics.hpp

dgm: tmp
	$(CC) $(CFLAGS) ../dgm/dgm/Compiler.cpp ../dgm/dgm/main.cpp ../dgm/dgm/modifiersdump.cpp ../dgm/dgm/SQLiteDatabase.cpp -o $(T)/$@ -lsqlite3

dgmExpressions.sql:
	cd $(T); ${DUMP}/dump.py

dbpatch: dbpatch.h
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o $(T)/$@ -lsqlite3 -I $(T)/

dbpatch.h: dgm dgmExpressions.sql
	cd $(T); sqlite3 $(T)/dump.sqlite ".read $(SQL)/dump.sql"
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dumpPatch.sql"
	$(T)/dgm $(T)/dump.sqlite --convertModifiers > $(T)/dbpatch.h


dump.sqlite: dbpatch
	$(T)/dbpatch $(T)/dump.sqlite


dgmModifiers.sql: dump.sqlite dgm
	$(T)/dgm $(T)/dump.sqlite --compile > $(T)/dgmModifiers.sql

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

AttributeID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --attributeIDs > ${T}/AttributeID.hpp
	cp -rf ${T}/AttributeID.hpp ../dgmpp2/AttributeID.hpp

TypeID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --typeIDs > ${T}/TypeID.hpp
	cp -rf ${T}/TypeID.hpp ../dgmpp2/TypeID.hpp

GroupID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --groupIDs > ${T}/GroupID.hpp
	cp -rf ${T}/GroupID.hpp ../dgmpp2/GroupID.hpp

CategoryID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --categoryIDs > ${T}/CategoryID.hpp
	cp -rf ${T}/CategoryID.hpp ../dgmpp2/CategoryID.hpp

EffectID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --effectIDs > ${T}/EffectID.hpp
	cp -rf ${T}/EffectID.hpp ../dgmpp2/EffectID.hpp

WarfareBuffID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --warfareBuffIDs > ${T}/WarfareBuffID.hpp
	cp -rf ${T}/WarfareBuffID.hpp ../dgmpp2/WarfareBuffID.hpp

Attributes.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --attributes > ${T}/Attributes.hpp
	cp -rf ${T}/Attributes.hpp ../dgmpp2/Attributes.hpp

Types.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --types > ${T}/Types.hpp
	cp -rf ${T}/Types.hpp ../dgmpp2/Types.hpp

Modifiers.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --modifiers > ${T}/Modifiers.hpp
	cp -rf ${T}/Modifiers.hpp ../dgmpp2/Modifiers.hpp

Effects.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --effects > ${T}/Effects.hpp
	cp -rf ${T}/Effects.hpp ../dgmpp2/Effects.hpp

WarfareBuffs.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --warfareBuffs > ${T}/WarfareBuffs.hpp
	cp -rf ${T}/WarfareBuffs.hpp ../dgmpp2/WarfareBuffs.hpp

Skills.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --skills > ${T}/Skills.hpp
	cp -rf ${T}/Skills.hpp ../dgmpp2/Skills.hpp

Commodities.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --commodities > ${T}/Commodities.hpp
	cp -rf ${T}/Commodities.hpp ../dgmpp2/Commodities.hpp

Facilities.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --facilities > ${T}/Facilities.hpp
	cp -rf ${T}/Facilities.hpp ../dgmpp2/Facilities.hpp

SchematicID.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --schematicIDs > ${T}/SchematicID.hpp
	cp -rf ${T}/SchematicID.hpp ../dgmpp2/SchematicID.hpp

Schematics.hpp: dgm dgm.sqlite
	$(T)/dgm dgm.sqlite --schematics > ${T}/Schematics.hpp
	cp -rf ${T}/Schematics.hpp ../dgmpp2/Schematics.hpp
