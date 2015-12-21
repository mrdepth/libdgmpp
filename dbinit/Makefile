SHELL:=/bin/sh
CC=g++
#CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
CFLAGS=-std=c++11
OUTPUT_DIR+=./
DUMP+=./dump
SQL=${PWD}/sql
SDE+=${PWD}/sde/eve.sqlite
T+=${PWD}/tmp

all: eufe.sqlite

dbpatch: dbpatch.h
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o $(T)/$@ -lsqlite3 -I $(T)/

compiler: tmp
	$(CC) $(CFLAGS) ../eufe/Compiler.cpp -o $(T)/$@ -lsqlite3

modifiersdump: tmp
	$(CC) $(CFLAGS) ../modifiersdump/main.cpp -o $(T)/$@ -lsqlite3

dbpatch.h: modifiersdump
	cd $(DUMP); sqlite3 $(SDE) ".read $(SQL)/eve.sql"; mv dump.sqlite $(T)/dump.sqlite
	cd $(DUMP); sqlite3 $(T)/dump.sqlite ".read $(SQL)/dump.sql"
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dumpPatch.sql"
	$(T)/modifiersdump $(T)/dump.sqlite $(T)/dbpatch.h


dump.sqlite: dbpatch
	$(T)/dbpatch $(T)/dump.sqlite


eufedump.sqlite: dump.sqlite
	cp $(T)/dump.sqlite $(T)/eufedump.sqlite
	sqlite3 $(T)/eufedump.sqlite ".read $(SQL)/eufeDumpPatch.sql"

dgmModifiers.sql: eufedump.sqlite compiler
	$(T)/compiler $(T)/eufedump.sqlite $(T)/

eufe.sqlite: dgmModifiers.sql
	sqlite3 $(T)/eufedump.sqlite ".read $(SQL)/eufe.sql"
	sqlite3 eufe.sqlite ".read $(T)/dgmModifiers.sql"
	sqlite3 eufe.sqlite ".read $(T)/dgmEffectModifiers.sql"
	mv ./eufe.sqlite $(OUTPUT_DIR)/eufe.sqlite

tmp:
	mkdir -p $(T)

clean:
	echo ${T}
	rm -rf ${T}
	rm -f *.sqlite