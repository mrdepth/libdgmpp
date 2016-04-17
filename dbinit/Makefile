SHELL:=/bin/sh
CC=g++
#CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
CFLAGS=-std=c++11
OUTPUT_DIR+=./
DUMP=${PWD}/dump
SQL=${PWD}/sql
T+=${PWD}/tmp

all: dgm.sqlite

dgmExpressions.sql:
	cd $(T); ${DUMP}/sisidump.py

dbpatch: dbpatch.h
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o $(T)/$@ -lsqlite3 -I $(T)/

compiler: tmp
	$(CC) $(CFLAGS) ../Compiler/Compiler.cpp -o $(T)/$@ -lsqlite3 -I "../dgmpp/"

modifiersdump: tmp
	$(CC) $(CFLAGS) ../modifiersdump/main.cpp -o $(T)/$@ -lsqlite3

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