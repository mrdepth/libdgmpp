namespace dgmpp {
	
	%nodefaultctor Engine;
	
	class Engine
	{
		public:
		Engine(const char* databasePath);
		~Engine(void);
		dgmpp::Area* setArea(dgmpp::TypeID typeID);
		dgmpp::ControlTower* setControlTower(dgmpp::TypeID typeID);
		void clearArea();
		dgmpp::Gang* getGang();
		dgmpp::Area* getArea();
		dgmpp::ControlTower* getControlTower();
	};
	
}