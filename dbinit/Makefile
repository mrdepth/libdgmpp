SHELL:=/bin/sh
CC=g++
#CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
CFLAGS=-std=c++11
OUTPUT_DIR+=./
DUMP+=./dump
SQL=${PWD}/sql
SDE+=${PWD}/sde/eve.sqlite
T+=${PWD}/tmp

all: dgm.sqlite

dbpatch: dbpatch.h
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o $(T)/$@ -lsqlite3 -I $(T)/

compiler: tmp
	$(CC) $(CFLAGS) ../Compiler/Compiler.cpp -o $(T)/$@ -lsqlite3 -I "../dgmpp/"

modifiersdump: tmp
	$(CC) $(CFLAGS) ../modifiersdump/main.cpp -o $(T)/$@ -lsqlite3

dbpatch.h: modifiersdump
	cd $(DUMP); sqlite3 $(SDE) ".read $(SQL)/eve.sql"; mv dump.sqlite $(T)/dump.sqlite
	cd $(DUMP); sqlite3 $(T)/dump.sqlite ".read $(SQL)/dump.sql"
	sqlite3 $(T)/dump.sqlite ".read $(SQL)/dumpPatch.sql"
	$(T)/modifiersdump $(T)/dump.sqlite $(T)/dbpatch.h


dump.sqlite: dbpatch
	$(T)/dbpatch $(T)/dump.sqlite


dgmppdump.sqlite: dump.sqlite
	cp $(T)/dump.sqlite $(T)/dgmppdump.sqlite
	sqlite3 $(T)/dgmppdump.sqlite ".read $(SQL)/dgmppDumpPatch.sql"

dgmModifiers.sql: dgmppdump.sqlite compiler
	$(T)/compiler $(T)/dgmppdump.sqlite $(T)/

dgm.sqlite: dgmModifiers.sql
	sqlite3 $(T)/dgmppdump.sqlite ".read $(SQL)/dgmpp.sql"
	sqlite3 dgm.sqlite ".read $(T)/dgmModifiers.sql"
	sqlite3 dgm.sqlite ".read $(T)/dgmEffectModifiers.sql"
	mv ./dgm.sqlite $(OUTPUT_DIR)/dgm.sqlite

tmp:
	mkdir -p $(T)

clean:
	echo ${T}
	rm -rf ${T}
	rm -f *.sqlite