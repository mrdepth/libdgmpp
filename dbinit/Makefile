CC=clang++
CFLAGS=-arch x86_64 -std=gnu++11 -stdlib=libc++ -lsqlite3

all: eufe.sqlite

dbpatch: tmp
	$(CC) $(CFLAGS) ../dbpatch/dbpatch.cpp -o ./tmp/$@

compiler: tmp
	$(CC) $(CFLAGS) ../eufe/Compiler.cpp -o ./tmp/$@

dump.sqlite: dbpatch
	sqlite3 ./tmp/dump.sqlite ".read ./sql/dump.sql"
	./tmp/dbpatch ./tmp/dump.sqlite

dgmCompiledEffects.sql: dump.sqlite compiler
	./tmp/compiler ./tmp/dump.sqlite ./tmp/

eufe.sqlite: dgmCompiledEffects.sql
	sqlite3 ./tmp/dump.sqlite ".read ./sql/eufe.sql"
	sqlite3 eufe.sqlite ".read ./tmp/dgmCompiledEffects.sql"

tmp:
	mkdir tmp

clean:
	rm -rf tmp
	rm -rf *.o dbpatch compiler *.sqlite *.sql