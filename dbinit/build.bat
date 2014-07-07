rem cd ./dump
rem ./datadump.py
rem cd ..
del *.sqlite
sqlite3 ./database.sqlite ".read init.sql"
sqlite3 ./database.sqlite ".read fixes.sql"
compiler.exe database.sqlite ./
sqlite3 ./database.sqlite ".read eufeInit.sql"
sqlite3 ./eufe.sqlite ".read dgmCompiledEffects.sql"
del ./database.sqlite