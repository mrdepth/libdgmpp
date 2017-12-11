//
//  SQLiteConnection.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 31.10.2017.
//

#pragma once
#include <stdexcept>
#include <sqlite3.h>
#include "types.h"

namespace dgmpp2 {

	class SQLiteError: public std::runtime_error {
	public:
		SQLiteError(int errorCode): std::runtime_error(sqlite3_errstr(errorCode)) {};
	};
	
	template <typename... Ts> class SQLiteResult;
	template <typename... Ts> class SQLiteRow;

	class SQLiteConnection final {
	public:
		SQLiteConnection(const std::string& path);
		SQLiteConnection(const SQLiteConnection& other);
		SQLiteConnection(SQLiteConnection&& other) noexcept = default;
		SQLiteConnection& operator=(const SQLiteConnection& other);
		SQLiteConnection& operator=(SQLiteConnection&& other) noexcept = default;
		~SQLiteConnection() = default;
		template<typename... Ts> SQLiteResult<Ts...> fetch(const std::string& sql);
	private:
		std::shared_ptr<sqlite3> database_;
		void open(const std::string& path);
	};
	
	template <typename... Ts>
	class SQLiteResult {
	public:
		SQLiteResult(std::shared_ptr<sqlite3_stmt> stmt): stmt_(stmt) {};
		SQLiteRow<Ts...> next();
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

	
	template <typename... Ts>
	class SQLiteRow {
	public:
		static const auto size = sizeof...(Ts);
		SQLiteRow(std::shared_ptr<sqlite3_stmt> stmt): stmt_(stmt) {}
		operator bool() { return stmt_ != nullptr; }
		template <std::size_t I> typename SQLiteColumn<I, Ts...>::type get();
	private:
		std::shared_ptr<sqlite3_stmt> stmt_;
	};
}
