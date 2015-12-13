#pragma once
#include <sqlite3.h>
#include "FetchRequest.h"

namespace eufe {
	class SqliteFetchRequest : public FetchRequest {
	public:
		SqliteFetchRequest(sqlite3_stmt* stmt);
		virtual ~SqliteFetchRequest();
		virtual void bindInt(int parameterIndex, int value);
		virtual void bindDouble(int parameterIndex, double value);
		virtual void bindText(int parameterIndex, const std::string& value);
		virtual int parameterIndex(const std::string& name);
		sqlite3_stmt* getStmt();
	private:
		sqlite3_stmt* stmt_;
	};
}