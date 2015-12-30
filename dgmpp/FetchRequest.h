#pragma once
#include <string>

namespace dgmpp {
	class FetchRequest {
	public:
		virtual void bindInt(int parameterIndex, int value) = 0;
		virtual void bindDouble(int parameterIndex, double value) = 0;
		virtual void bindText(int parameterIndex, const std::string& value) = 0;
		virtual int parameterIndex(const std::string& name) = 0;
	};
}