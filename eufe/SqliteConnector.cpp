#include "SqliteConnector.h"
#include <cassert>

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

/*std::shared_ptr<FetchResult> SqliteConnector::exec(const char* sql)
{
	sqlite3_stmt* stmt = nullptr;
	sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

	return std::make_shared<SqliteFetchResult>(stmt);
}*/

std::shared_ptr<FetchResult> SqliteConnector::exec(const std::shared_ptr<FetchRequest>& request) {
	assert(sqlite3_stmt_busy(std::dynamic_pointer_cast<SqliteFetchRequest>(request)->getStmt()) == 0);
	return std::make_shared<SqliteFetchResult>(std::dynamic_pointer_cast<SqliteFetchRequest>(request));
}

std::shared_ptr<FetchRequest> SqliteConnector::getReusableFetchRequest(const char* sql) {
	size_t key = hash_(sql);
	auto i = reusableFetchRequests_.find(key);
	if (i == reusableFetchRequests_.end()) {
		sqlite3_stmt* stmt = nullptr;
		sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
		std::shared_ptr<SqliteFetchRequest> request = std::make_shared<SqliteFetchRequest>(stmt);
		reusableFetchRequests_[key] = request;
		return request;
	}
	else
		return i->second;
}
