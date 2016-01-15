#pragma once
#include "types.h"

namespace dgmpp {
	class Warning {
	public:
		enum Code {
			CODE_WASTED,
			CODE_STORAGE_IS_FULL,
			CODE_PRODUCTION_STOPPED
		};
		Warning(std::shared_ptr<Facility> const& source, Code code, double timeStamp, double arg) : source_(source), code_(code), timeStamp_(timeStamp), arg_(arg) {};
		std::shared_ptr<Facility> getSource() const {return source_;};
		Code getCode() const {return code_;};
		double getTimeStamp() const {return timeStamp_;};
		double getArg() const {return arg_;};
	private:
		std::shared_ptr<Facility> source_;
		Code code_;
		double timeStamp_;
		double arg_;
	};
}