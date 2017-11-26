SHELL:=/bin/sh
CC=g++
#CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
CFLAGS=-std=c++11 -fvisibility-inlines-hidden
OUTPUT_DIR+=./
DUMP=${PWD}/dump
SQL=${PWD}/sql
T+=${PWD}/tmp

all: dgm.sqlite EffectID.h AttributeID.h CategoryID.h GroupID.h TypeID.h

dgmExpressions.sql:
	cd $(T); ${DUMP}/dump.py

dbpatch: dbpatch.h
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o $(T)/$@ -lsqlite3 -I $(T)/

compiler: tmp EffectID.h AttributeID.h CategoryID.h GroupID.h TypeID.h
	$(CC) $(CFLAGS) ../Compiler/Compiler.cpp -o $(T)/$@ -lsqlite3 -I "../dgmpp/" -I "../dgmpp2/"

modifiersdump: tmp
	$(CC) $(CFLAGS) ../modifiersdump/main.cpp -o $(T)/$@ -lsqlite3

idsdump: tmp
	$(CC) $(CFLAGS) ../idsdump/idsdump/main.cpp -o $(T)/$@ -lsqlite3

dbpatch.h: modifiersdump dgmExpressions.sql
	cd $(T); sqlite3 $(T)/dump.sqlite ".read $(SQL)/dump.sql"
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dumpPatch.sql"
	$(T)/modifiersdump $(T)/dump.sqlite $(T)/dbpatch.h


dump.sqlite: dbpatch
	$(T)/dbpatch $(T)/dump.sqlite


dgmModifiers.sql: dump.sqlite compiler
	$(T)/compiler $(T)/dump.sqlite $(T)/

dgm.sqlite: dgmModifiers.sql
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dgmpp.sql"
	sqlite3 dgm.sqlite ".read $(T)/dgmModifiers.sql"
	sqlite3 dgm.sqlite ".read $(T)/dgmEffectModifiers.sql"
	sqlite3 dgm.sqlite "vacuum"
	mv ./dgm.sqlite $(OUTPUT_DIR)/dgm.sqlite

tmp:
	mkdir -p $(T)

clean:
	echo ${T}
	rm -rf ${T}
	rm -f *.sqlite

EffectID.h: idsdump dump.sqlite
	$(T)/idsdump $(T)/dump.sqlite EffectID "select effectID, effectName from dgmEffects order by effectID" > ${T}/EffectID.h
	cp -rf ${T}/EffectID.h ../dgmpp/EffectID.h

AttributeID.h: idsdump dump.sqlite
	$(T)/idsdump $(T)/dump.sqlite AttributeID "select attributeID, attributeName c from dgmAttributeTypes GROUP BY attributeName order by attributeID" > ${T}/AttributeID.h
	cp -rf ${T}/AttributeID.h ../dgmpp/AttributeID.h

CategoryID.h: idsdump dump.sqlite
	$(T)/idsdump $(T)/dump.sqlite CategoryID "select categoryID, categoryName from invCategories order by categoryID" > ${T}/CategoryID.h
	cp -rf ${T}/CategoryID.h ../dgmpp/CategoryID.h

GroupID.h: idsdump dump.sqlite
	$(T)/idsdump $(T)/dump.sqlite GroupID "SELECT groupID, groupName FROM invGroups WHERE categoryID NOT IN (1,2) GROUP BY groupName ORDER BY groupID" > ${T}/GroupID.h
	cp -rf ${T}/GroupID.h ../dgmpp/GroupID.h

TypeID.h: idsdump dump.sqlite
	$(T)/idsdump $(T)/dump.sqlite TypeID "select typeID, typeName from invTypes where published = 1 OR groupID = 1 order by typeID" > ${T}/TypeID.h
	cp -rf ${T}/TypeID.h ../dgmpp/TypeID.h
