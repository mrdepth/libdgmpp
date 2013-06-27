#!/bin/sh
cd ./dump
./datadump.py
cd ..
rm *.sqlite
sqlite3 ./database.sqlite ".read init.sql"
sqlite3 ./database.sqlite ".read fixes.sql"
./compiler database.sqlite ./
sqlite3 ./database.sqlite ".read eufeInit.sql"
sqlite3 ./eufe.sqlite ".read dgmCompiledEffects.sql"
rm ./database.sqlite