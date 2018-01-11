%module dgmpp

%{
#include "dgmpp.hpp"
using namespace std::chrono_literals;
	
	namespace dgmpp {
		typedef double Seconds;
		
		template<typename Rep, typename Ratio>
		inline Seconds MakeSeconds(const std::chrono::duration<Rep, Ratio>& v) {
			return std::chrono::duration_cast<std::chrono::seconds>(v).count();
		}
	}

%}
%include "enumtypeunsafe.swg"
%javaconst(1);
%include "SDE/TypeID.hpp"
%include "SDE/GroupID.hpp"
%include "SDE/CategoryID.hpp"
%include "SDE/AttributeID.hpp"
%include "Utility.i"
%include "Gang.i"
