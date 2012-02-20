#include "eufe.h"
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <ios>
#include <queue>

using namespace eufe;

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 0;
	Compiler compiler = Compiler(argv[1], argv[2]);
	compiler.compile();
	return 0;
	/*
#ifdef WIN32
	Engine engine("E:\\Programing\\dbinit\\eufe.sqlite");
#else
	//Engine engine("/Users/mr_depth/Work/My/svn/EVEUniverse/trunk/eufe.sqlite");
	Engine engine("/Users/mrdepth/Documents/svn/EVEUniverse/trunk/eufe.sqlite");
#endif
	
	boost::shared_ptr<Gang> gang = engine.getGang();
	boost::shared_ptr<Character> character1 = gang->addPilot();
	boost::shared_ptr<Character> character2 = gang->addPilot();
	character1->setAllSkillsLevel(5);
	character2->setAllSkillsLevel(5);
	
	boost::shared_ptr<Ship> gila = character1->setShip(17715);
	gila->addModule(3841);
	gila->addModule(3841);
	gila->addModule(3841);
	gila->addModule(3841);
	gila->addModule(2281);
	gila->addModule(2531);
	gila->addModule(1422);
	gila->addModule(1422);
	gila->addModule(1422);
	Module* dc = gila->addModule(2048).get();
	gila->addModule(31802);
	gila->addModule(31802);
	gila->addModule(31802);
	dc->getAttribute(271)->getValue();
	
	boost::shared_ptr<Ship> tengu = character2->setShip(29984);
	tengu->addModule(29972);
	tengu->addModule(4284);
	character2->addImplant(21888);
	gang->setFleetBooster(character2);
	Resistances res = gila->getResistances();

	
#if _DEBUG
#ifdef WIN32
	std::ofstream ofs("E:\\Programing\\EVE\\fit.json");
#else
	//std::ofstream ofs("/Users/mr_depth/Desktop/fit.json");
	std::ofstream ofs("/Users/mrdepth/Desktop/fit.json");
#endif
	ofs << engine << std::endl;
	ofs.close();
#endif
	return 0;*/
}