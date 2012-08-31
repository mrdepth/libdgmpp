namespace eufe {
	
	%nodefaultctor Engine;
	
	class Engine
	{
		public:
		Engine(const char* databasePath);
		~Engine(void);
		Area* setArea(TypeID typeID);
		ControlTower* setControlTower(TypeID typeID);
		void clearArea();
		Gang* getGang();
		Area* getArea();
		ControlTower* getControlTower();
	};
	
}