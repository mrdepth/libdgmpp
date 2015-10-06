#include "SqliteConnector.h"

using namespace eufe;

SqliteConnector::SqliteConnector(const char* databasePath) : db_(nullptr)
{
	sqlite3_open(databasePath, &db_);
}

SqliteConnector::~SqliteConnector(void)
{
	if (db_)
		sqlite3_close(db_);
}

std::shared_ptr<FetchResult> SqliteConnector::exec(const char* sql)
{
	sqlite3_stmt* stmt = nullptr;
	sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

	return std::shared_ptr<FetchResult>(new SqliteFetchResult(stmt));
}