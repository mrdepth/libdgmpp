#pragma once
#include "FetchResult.h"

namespace eufe {
	class SqlConnector	{
	public:
		SqlConnector(void);
		virtual ~SqlConnector(void);
		virtual std::shared_ptr<FetchResult> exec(const char* sql) = 0;
	};
}