#pragma once
#include <map>
#include "SqlConnector.h"
#include "SqliteFetchResult.h"

namespace dgmpp {

	class SqliteConnector: public SqlConnector
	{
	public:
		SqliteConnector(const char* databasePath);
		virtual ~SqliteConnector(void);
		//virtual std::shared_ptr<FetchResult> exec(const char* sql);
		virtual std::shared_ptr<FetchResult> exec(const std::shared_ptr<FetchRequest>& request);
		virtual std::shared_ptr<FetchRequest> getReusableFetchRequest(const char* sql);
	private:
		sqlite3* db_;
		std::map<size_t, std::shared_ptr<SqliteFetchRequest>> reusableFetchRequests_;
		std::hash<std::string> hash_;
	};

}