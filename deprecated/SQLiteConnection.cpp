//
//  SQLiteConnection.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 31.10.2017.
//

#include "SQLiteConnection.hpp"

using namespace dgmpp2;

SQLiteConnection::SQLiteConnection(const std::string& path) {
	open(path);
}

SQLiteConnection::SQLiteConnection(const SQLiteConnection& other) {
	if (other.database_) {
		auto path = sqlite3_db_filename(other.database_.get(), "main");
		open(path);
	}
}

SQLiteConnection& SQLiteConnection::operator=(const SQLiteConnection& other) {
	if (other.database_) {
		auto path = sqlite3_db_filename(other.database_.get(), "main");
		open(path);
	}
	return *this;
}


template<typename... Ts> SQLiteResult<Ts...>
SQLiteConnection::fetch(const std::string& sql) {
	sqlite3_stmt* stmt = nullptr;
	auto ret = sqlite3_prepare_v2(database_.get(), sql.c_str(), -1, &stmt, nullptr);
	
	if (ret != SQLITE_OK)
		throw SQLiteError(ret);
	
	return SQLiteResult<Ts...>(std::shared_ptr<sqlite3_stmt>(stmt, sqlite3_finalize));
}

void SQLiteConnection::open(const std::string& path) {
	sqlite3* database = nullptr;
	auto ret = sqlite3_open_v2(path.c_str(), &database, SQLITE_OPEN_READONLY, nullptr);
	
	if (ret != SQLITE_OK)
		throw SQLiteError(ret);
	
	database_ = std::shared_ptr<sqlite3>(database, sqlite3_close);
}

template <typename... Ts> SQLiteRow<Ts...>
SQLiteResult<Ts...>::next() {
	if (stmt_ != nullptr && sqlite3_step(stmt_.get()) == SQLITE_ROW) {
		return SQLiteRow<Ts...>(stmt_);
	}
	else {
		return SQLiteRow<Ts...>(nullptr);
	}
}

template <std::size_t I, typename T>
struct getter {
	static T get();
};

template <typename... Ts>
template <std::size_t I>
typename SQLiteColumn<I, Ts...>::type SQLiteRow<Ts...>::get() {
	return getter<I, typename SQLiteColumn<I, Ts...>::type>::get(stmt_);
}

template<std::size_t I, typename T>
struct getter<I, Optional<T>> {
	static Optional<T> get(std::shared_ptr<sqlite3_stmt> stmt) {
		if (sqlite3_column_type(stmt.get(), static_cast<int>(I)) == SQLITE_NULL)
			return nullopt;
		else
			return makeOptional(getter<I, T>::get(stmt));
	}
};


template<std::size_t I>
struct getter<I, int> {
	static int get(std::shared_ptr<sqlite3_stmt> stmt) {
		return sqlite3_column_int(stmt.get(), static_cast<int>(I));
	}
};

template<std::size_t I>
struct getter<I, double> {
	static double get(std::shared_ptr<sqlite3_stmt> stmt) {
		return sqlite3_column_double(stmt.get(), static_cast<int>(I));
	}
};

template<std::size_t I>
struct getter<I, bool> {
	static bool get(std::shared_ptr<sqlite3_stmt> stmt) {
		return sqlite3_column_int(stmt.get(), static_cast<int>(I)) != 0;
	}
};

template<std::size_t I>
struct getter<I, std::string> {
	static std::string get(std::shared_ptr<sqlite3_stmt> stmt) {
		return reinterpret_cast<const char*> (sqlite3_column_text(stmt.get(), static_cast<int>(I)));
	}
};
