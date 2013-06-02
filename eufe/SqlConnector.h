#pragma once
#include "FetchResult.h"

namespace eufe {
	class SqlConnector	{
	public:
		SqlConnector(void);
		virtual ~SqlConnector(void);
		virtual boost::shared_ptr<FetchResult> exec(const char* sql) = 0;
	};
}