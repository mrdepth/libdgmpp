//
//  SQLiteDatabase.cpp
//  dgm
//
//  Created by Artem Shimanski on 31.10.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

#include "SQLiteDatabase.hpp"

SQLiteDatabase::SQLiteDatabase(const std::string& path) {
	open(path);
}

SQLiteDatabase::SQLiteDatabase(const SQLiteDatabase& other) {
	if (other.database_) {
		auto path = sqlite3_db_filename(other.database_.get(), "main");
		open(path);
	}
}

SQLiteDatabase& SQLiteDatabase::operator=(const SQLiteDatabase& other) {
	if (other.database_) {
		auto path = sqlite3_db_filename(other.database_.get(), "main");
		open(path);
	}
	return *this;
}


/*template<typename... Ts> SQLiteResult<Ts...>
SQLiteDatabase::fetch(const std::string& sql) {
	sqlite3_stmt* stmt = nullptr;
	auto ret = sqlite3_prepare_v2(database_.get(), sql.c_str(), -1, &stmt, nullptr);
	
	if (ret != SQLITE_OK)
		throw SQLiteError(ret);
	
	return SQLiteResult<Ts...>(std::shared_ptr<sqlite3_stmt>(stmt, sqlite3_finalize));
}*/

void SQLiteDatabase::open(const std::string& path) {
	sqlite3* database = nullptr;
	auto ret = sqlite3_open_v2(path.c_str(), &database, SQLITE_OPEN_READONLY, nullptr);
	
	if (ret != SQLITE_OK)
		throw SQLiteError(ret);
	
	database_ = std::shared_ptr<sqlite3>(database, sqlite3_close);
}



