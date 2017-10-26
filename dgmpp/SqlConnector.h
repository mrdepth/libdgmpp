#pragma once
#include "FetchResult.h"
#include "FetchRequest.h"
#include <tuple>

template<int i, class T, class... P> struct get {
	static std::tuple<T, P...> exec(std::shared_ptr<dgmpp::FetchResult> result) {
		return std::tuple_cat(get<i, T>::exec(result), get<i + 1, P...>::exec(result));
	}
};

template<int i> struct get<i, int> {
	static std::tuple<int> exec(std::shared_ptr<dgmpp::FetchResult> result) {
		return std::make_tuple(result->getInt(i));
	}
};

template<int i> struct get<i, std::string> {
	static std::tuple<std::string> exec(std::shared_ptr<dgmpp::FetchResult> result) {
		return std::make_tuple(result->getText(i));
	}
};

namespace dgmpp {
	class SqlConnector	{
	public:
		SqlConnector(void);
		virtual ~SqlConnector(void);
		//virtual std::shared_ptr<FetchResult> exec(const char* sql) = 0;
		virtual std::shared_ptr<FetchResult> exec(const std::shared_ptr<FetchRequest>& request) = 0;
		virtual std::shared_ptr<FetchRequest> getReusableFetchRequest(const char* sql) = 0;
		
		template<class... T> std::tuple<T...> fetch(std::string sql) {
			return get<0, T...>::exec(exec(getReusableFetchRequest(sql.c_str())));
		}
		
	private:
		
		
		
		
	};
}


