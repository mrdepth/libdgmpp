#include "SqliteConnector.h"

using namespace eufe;

SqliteConnector::SqliteConnector(const char* databasePath) : db_(NULL)
{
	sqlite3_open(databasePath, &db_);
}

SqliteConnector::~SqliteConnector(void)
{
	if (db_)
		sqlite3_close(db_);
}

boost::shared_ptr<FetchResult> SqliteConnector::exec(const char* sql)
{
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db_, sql, -1, &stmt, NULL);

	return boost::shared_ptr<FetchResult>(new SqliteFetchResult(stmt));
}