#pragma once
#include "SqlConnector.h"
#include "SqliteFetchResult.h"

namespace eufe {

	class SqliteConnector: public SqlConnector
	{
	public:
		SqliteConnector(const char* databasePath);
		virtual ~SqliteConnector(void);
		virtual boost::shared_ptr<FetchResult> exec(const char* sql);
	private:
		sqlite3* db_;
	};

}