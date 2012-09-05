namespace eufe {
	
	%nodefaultctor Engine;
	
	class Engine
	{
		public:
		Engine(const char* databasePath);
		~Engine(void);
		eufe::Area* setArea(eufe::TypeID typeID);
		eufe::ControlTower* setControlTower(eufe::TypeID typeID);
		void clearArea();
		eufe::Gang* getGang();
		eufe::Area* getArea();
		eufe::ControlTower* getControlTower();
	};
	
}