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
	Character* character1 = gang->addPilot();
	character1->setAllSkillsLevel(5);

	
	Ship* gila = character1->setShip(17715);
	Module* module1 = gila->addModule(28756);
	module1->setCharge(30488);

	int l = module1->getMaxRange();

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