%include "types.i"
%include "SqlConnector.i"
%include "Gang.i"
%include "Area.i"
%include "ControlTower.i"

%shared_ptr(dgmpp::Engine);

namespace dgmpp {
	
	%nodefaultctor Engine;

	class Engine
	{
		public:
		
		Engine(const std::shared_ptr<dgmpp::SqlConnector>& sqlConnector);
		~Engine(void);
		std::shared_ptr<dgmpp::Area> setArea(dgmpp::TypeID typeID);
		std::shared_ptr<dgmpp::ControlTower> setControlTower(dgmpp::TypeID typeID);
		void clearArea();
		std::shared_ptr<dgmpp::Gang> getGang();
		std::shared_ptr<dgmpp::Area> getArea();
		std::shared_ptr<dgmpp::ControlTower> getControlTower();
	};
	
}