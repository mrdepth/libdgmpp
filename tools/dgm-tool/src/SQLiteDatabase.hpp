//
//  SQLiteDatabase.hpp
//  dgm
//
//  Created by Artem Shimanski on 31.10.2017.
//  Copyright © 2017 Artem Shimanski. All rights reserved.
//

#pragma once

#include <stdexcept>
#include <memory>
#include <string>
#include <sqlite3.h>
#include <cassert>
#include <cstdio>

template <typename T> using Optional = std::shared_ptr<T>;
static auto nullopt = nullptr;

template <typename T> Optional<T> makeOptional(T&& t) {
	return Optional<T>(new T(std::forward<T>(t)));
}

class SQLiteError: public std::runtime_error {
public:
	SQLiteError(int errorCode): std::runtime_error(sqlite3_errstr(errorCode)) {};
};

class SQLiteInvalidColumnsCountError: public std::runtime_error {
public:
	SQLiteInvalidColumnsCountError(int columns, int expected): std::runtime_error("Invalid columns count:  " +  std::to_string(columns) + ", expected: " + std::to_string(expected)) {};
};

template <typename... Ts> class SQLiteResult;
template <typename... Ts> class SQLiteRow;

class SQLiteDatabase {
public:
	SQLiteDatabase(const std::string& path);
	SQLiteDatabase(const SQLiteDatabase& other);
	SQLiteDatabase(SQLiteDatabase&& other) noexcept = default;
	SQLiteDatabase& operator=(const SQLiteDatabase& other);
	SQLiteDatabase& operator=(SQLiteDatabase&& other) noexcept = default;
	SQLiteDatabase() = default;
	template<typename... Ts> SQLiteResult<Ts...> fetch(const std::string& sql) {
		sqlite3_stmt* stmt = nullptr;
		auto ret = sqlite3_prepare_v2(database_.get(), sql.c_str(), -1, &stmt, nullptr);
		
		if (ret != SQLITE_OK)
			throw SQLiteError(ret);
		auto ptr = std::shared_ptr<sqlite3_stmt>(stmt, sqlite3_finalize);
		const int columns = sqlite3_column_count(stmt);
		const int expected = sizeof...(Ts);
		if (columns != expected)
			throw SQLiteInvalidColumnsCountError(columns, expected);
		return SQLiteResult<Ts...>(ptr);
	}
private:
	std::shared_ptr<sqlite3> database_;
	void open(const std::string& path);
};

template <typename... Ts>
class SQLiteResult {
public:
	SQLiteResult(std::shared_ptr<sqlite3_stmt> stmt): stmt_(stmt) {};
	SQLiteRow<Ts...> next() {
		if (stmt_ != nullptr && sqlite3_step(stmt_.get()) == SQLITE_ROW) {
			return SQLiteRow<Ts...>(stmt_);
		}
		else {
			return SQLiteRow<Ts...>(nullptr);
		}
	}
private:
	std::shared_ptr<sqlite3_stmt> stmt_;
};

template<std::size_t I, typename... Ts>
struct SQLiteColumn;

template<std::size_t I, typename Head, typename... Tail>
struct SQLiteColumn<I, Head, Tail...>: SQLiteColumn<I - 1, Tail...> {};

template<typename Head, typename... Tail>
struct SQLiteColumn<0, Head, Tail...> {
	using type = Head;
};

template <std::size_t I, typename T>
struct getter {
	static T get();
};

template <typename... Ts>
class SQLiteRow {
public:
	static const auto size = sizeof...(Ts);
	SQLiteRow(const std::shared_ptr<sqlite3_stmt>& stmt): stmt_(stmt) {}
	operator bool() { return stmt_ != nullptr; }
	template <std::size_t I> typename SQLiteColumn<I, Ts...>::type get() {
		return getter<I, typename SQLiteColumn<I, Ts...>::type>::get(stmt_);
	}
private:
	std::shared_ptr<sqlite3_stmt> stmt_;
};

template<std::size_t I, typename T>
struct getter<I, Optional<T>> {
	static Optional<T> get(const std::shared_ptr<sqlite3_stmt>& stmt) {
		if (sqlite3_column_type(stmt.get(), static_cast<int>(I)) == SQLITE_NULL)
			return nullopt;
		else
			return makeOptional(getter<I, T>::get(stmt));
	}
};


template<std::size_t I>
struct getter<I, int> {
	static int get(const std::shared_ptr<sqlite3_stmt>& stmt) {
		return sqlite3_column_int(stmt.get(), static_cast<int>(I));
	}
};

template<std::size_t I>
struct getter<I, double> {
	static double get(const std::shared_ptr<sqlite3_stmt>& stmt) {
		return sqlite3_column_double(stmt.get(), static_cast<int>(I));
	}
};

template<std::size_t I>
struct getter<I, bool> {
	static bool get(const std::shared_ptr<sqlite3_stmt>& stmt) {
		return sqlite3_column_int(stmt.get(), static_cast<int>(I)) != 0;
	}
};

template<std::size_t I>
struct getter<I, std::string> {
	static std::string get(const std::shared_ptr<sqlite3_stmt>& stmt) {
		return reinterpret_cast<const char*> (sqlite3_column_text(stmt.get(), static_cast<int>(I)));
	}
};
