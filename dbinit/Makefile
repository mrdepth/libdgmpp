SHELL:=/bin/sh
CC=clang++
CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3
OUTPUT_DIR+=./
DUMP+=./dump
SQL=${PWD}/sql
TMP+=${PWD}/tmp

all: eufe.sqlite

dbpatch: tmp
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o $(TMP)/$@

compiler: tmp
	$(CC) $(CFLAGS) ../eufe/Compiler.cpp -o $(TMP)/$@

dump.sqlite: dbpatch
	cd $(DUMP); sqlite3 $(TMP)/dump.sqlite ".read $(SQL)/dump.sql"
	sqlite3 $(TMP)/dump.sqlite ".read $(SQL)/dumpPatch.sql"
	$(TMP)/dbpatch $(TMP)/dump.sqlite

dgmCompiledEffects.sql: dump.sqlite compiler
	$(TMP)/compiler $(TMP)/dump.sqlite $(TMP)/

eufe.sqlite: dgmCompiledEffects.sql
	sqlite3 $(TMP)/dump.sqlite ".read $(SQL)/eufe.sql"
	sqlite3 eufe.sqlite ".read $(TMP)/dgmCompiledEffects.sql"
	mv ./eufe.sqlite $(OUTPUT_DIR)/eufe.sqlite

tmp:
	mkdir -p $(TMP)

clean:
	rm -rf $(TMP)
	rm -f *.sqlite