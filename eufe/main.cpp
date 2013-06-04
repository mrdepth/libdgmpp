#include "eufe.h"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <ios>
#include <queue>
#include <time.h>

using namespace eufe;

void usageExample()
{
#ifdef WIN32
	Engine engine(new SqliteConnector("E:\\Programing\\dbinit\\eufe.sqlite"));
#else
	Engine engine("/Users/shimanski/Documents/git/EVEUniverse/eufe.sqlite");
#endif
	
	Gang* gang = engine.getGang();
	gang->addPilot();

	Character* character1 = gang->addPilot();
	character1->setAllSkillsLevel(5);

	Ship* domi1 = character1->setShip(645);

	std::list<TypeID> typeIDs;
	typeIDs.push_back(10836);
	typeIDs.push_back(10836);
	typeIDs.push_back(645);
	typeIDs.push_back(10836);

	ModulesList modules = domi1->addModules(typeIDs);

	Resistances res1 = domi1->getResistances();
	
	Ship* gila = character1->setShip(17715);
	Module* module1 = gila->addModule(10836);
	Module* module2 = gila->addModule(10836);
	Module* module3 = gila->addModule(10836);
	gila->addModule(10836);
	gila->addModule(10836);
	gila->addModule(10836);
	gila->removeModule(module2);
	module1->setState(Module::STATE_OVERLOADED);
	gila->getWeaponDps();
	gila->getResistances();
	gila->getCapStableLevel();

#if _DEBUG
#ifdef WIN32
	std::ofstream ofs("E:\\Programing\\EVE\\fit.json");
#else
	std::ofstream ofs("/Users/mrdepth/Desktop/fit.json");
#endif
	ofs << engine << std::endl;
	ofs.close();
#endif
}

int main(int argc, char* argv[])
{
	usageExample();
	return 0;
	if (argc != 3) {
		std::cout<<"Usage: compiler source_database.sqlite output_dir"<<std::endl;
		return 0;
	}
	Compiler compiler = Compiler(argv[1], argv[2]);
	compiler.compile();
	return 0;
}