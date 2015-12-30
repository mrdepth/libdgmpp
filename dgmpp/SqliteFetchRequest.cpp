#include "SqliteFetchRequest.h"

using namespace dgmpp;

SqliteFetchRequest::SqliteFetchRequest(sqlite3_stmt* stmt): stmt_(stmt) {
	
}

SqliteFetchRequest::~SqliteFetchRequest() {
	sqlite3_finalize(stmt_);
}

void SqliteFetchRequest::bindInt(int parameterIndex, int value) {
	sqlite3_bind_int(stmt_, parameterIndex, value);
}

void SqliteFetchRequest::bindDouble(int parameterIndex, double value) {
	sqlite3_bind_double(stmt_, parameterIndex, value);
}

void SqliteFetchRequest::bindText(int parameterIndex, const std::string& value) {
	sqlite3_bind_text(stmt_, parameterIndex, value.c_str(), -1, SQLITE_TRANSIENT);
}

int SqliteFetchRequest::parameterIndex(const std::string& name) {
	return sqlite3_bind_parameter_index(stmt_, name.c_str());
}

sqlite3_stmt* SqliteFetchRequest::getStmt() {
	return stmt_;
}