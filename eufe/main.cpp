#include "eufe.h"
#include <boost/lexical_cast.hpp>
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
	{
#ifdef WIN32
	Engine engine("E:\\Programing\\dbinit\\eufe.sqlite");
#else
	//Engine engine("/Users/mr_depth/Work/My/svn/EVEUniverse/trunk/eufe.sqlite");
	Engine engine("/Users/shimanski/Documents/git/EVEUniverse/eufe.sqlite");
#endif
	
	Gang* gang = engine.getGang();
	Character* character1 = gang->addPilot();
	character1->setAllSkillsLevel(5);
	
	Ship* gila = character1->setShip(17715);
	Module* module1 = gila->addModule(10836);
	Module* module2 = gila->addModule(10836);
	Module* module3 = gila->addModule(10836);
	gila->addModule(10836);
	gila->addModule(10836);
	gila->addModule(10836);
	gila->removeModule(module2);
	module1->setState(Module::STATE_OVERLOADED);
	//module2->setState(Module::STATE_OFFLINE);
	module3->setState(Module::STATE_OVERLOADED);
	float lifeTime1 = module1->getLifeTime();
	//float lifeTime2 = module2->getLifeTime();
	float lifeTime3 = module3->getLifeTime();
//	ControlTower* controlTower = engine.setControlTower(16214);
/*	controlTower->addStructure(16689);
	controlTower->addStructure(17184);
	controlTower->addStructure(17185);
	controlTower->addStructure(17186);
	controlTower->addStructure(17187);

	controlTower->addStructure(17184);
	controlTower->addStructure(17185);
	controlTower->addStructure(17186);
	controlTower->addStructure(17187);

	controlTower->addStructure(17184);
	controlTower->addStructure(17185);
	controlTower->addStructure(17186);
	controlTower->addStructure(17187);*/

//	Tank tank = controlTower->getEffectiveTank();
//	HitPoints hp = controlTower->getEffectiveHitPoints();
	
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
	}
	return 0;
}