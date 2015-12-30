#pragma once
#if _WIN32
#include "ThirdParty\sqlite3.h"
#else
#include <sqlite3.h>
#endif
#include "FetchResult.h"
#include "SqliteFetchRequest.h"

namespace dgmpp {

	class SqliteFetchResult: public FetchResult
	{
	public:
		SqliteFetchResult(const std::shared_ptr<SqliteFetchRequest>& request);
		virtual ~SqliteFetchResult(void);
		virtual bool next();
		virtual int getInt(int columnIndex);
		virtual double getDouble(int columnIndex);
		virtual std::string getText(int columnIndex);
		virtual Blob getBlob(int columnIndex);
		virtual void finalize();
	private:
		std::shared_ptr<SqliteFetchRequest> request_;
	};
}