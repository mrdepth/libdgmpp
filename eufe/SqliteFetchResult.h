#pragma once
#include "ThirdParty/sqlite3.h"
#include "FetchResult.h"

namespace eufe {

	class SqliteFetchResult: public FetchResult
	{
	public:
		SqliteFetchResult(sqlite3_stmt* stmt);
		virtual ~SqliteFetchResult(void);
		virtual bool next();
		virtual int getInt(int columnIndex);
		virtual double getDouble(int columnIndex);
		virtual std::string getText(int columnIndex);
		virtual Blob getBlob(int columnIndex);
		virtual void finalize();
	private:
		sqlite3_stmt* stmt_;
	};
}