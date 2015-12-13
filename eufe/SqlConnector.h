#pragma once
#include "FetchResult.h"
#include "FetchRequest.h"

namespace eufe {
	class SqlConnector	{
	public:
		SqlConnector(void);
		virtual ~SqlConnector(void);
		//virtual std::shared_ptr<FetchResult> exec(const char* sql) = 0;
		virtual std::shared_ptr<FetchResult> exec(const std::shared_ptr<FetchRequest>& request) = 0;
		virtual std::shared_ptr<FetchRequest> getReusableFetchRequest(const char* sql) = 0;
	};
}