#include "SqliteConnector.h"

using namespace eufe;

SqliteConnector::SqliteConnector(const char* databasePath) : db_(nullptr)
{
	int ret = sqlite3_open_v2(databasePath, &db_, SQLITE_OPEN_READONLY, nullptr);
	if (ret != SQLITE_OK)
		throw ret;
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

	return std::make_shared<SqliteFetchResult>(stmt);
}