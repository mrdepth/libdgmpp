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
/*	if (argc != 3)
		return 0;
	Compiler compiler = Compiler(argv[1], argv[2]);
	compiler.compile();
	return 0;*/
	
#ifdef WIN32
	Engine engine("E:\\Programing\\dbinit\\eufe.sqlite");
#else
	//Engine engine("/Users/mr_depth/Work/My/svn/EVEUniverse/trunk/eufe.sqlite");
	Engine engine("/Users/mrdepth/Documents/svn/EVEUniverse/trunk/eufe.sqlite");
#endif
	
	boost::shared_ptr<Gang> gang = engine.getGang();
	boost::shared_ptr<Character> character1 = gang->addPilot();
	character1->setAllSkillsLevel(5);
	
	boost::shared_ptr<Ship> gila = character1->setShip(17715);
	boost::shared_ptr<Module> module1 = gila->addModule(10836);
	boost::shared_ptr<Module> module2 = gila->addModule(10836);
	boost::shared_ptr<Module> module3 = gila->addModule(10836);
	gila->addModule(10836);
	gila->addModule(10836);
	gila->addModule(10836);
	module1->setState(Module::STATE_OVERLOADED);
	//module2->setState(Module::STATE_OFFLINE);
	module3->setState(Module::STATE_OVERLOADED);
	float lifeTime1 = module1->getLifetime();
	float lifeTime2 = module2->getLifetime();
	float lifeTime3 = module3->getLifetime();

	
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
	return 0;
}