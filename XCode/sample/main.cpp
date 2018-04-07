#include <iostream>
#include "dgmpp.hpp"
#include <typeinfo>
#include <type_traits>

using namespace dgmpp;


int main(int argc, const char * argv[]) {
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(Ship::Create(TypeID::proteus));
	auto modules = {
		ship->addModule(TypeID::_10MNAfterburnerI, Module::anySocket, true),
		ship->addModule(TypeID::mediumShieldBoosterII, Module::anySocket, true),
		ship->addModule(TypeID::ionBlasterCannonII, Module::anySocket, true),
		ship->addModule(TypeID::ionBlasterCannonII, Module::anySocket, true)
	};

	
	std::cout << "DPS: " << (ship->dronesDPS() * 1s).total() << std::endl;
	std::cout << "Volley: " << ship->dronesVolley().total() << std::endl;
	
    return 0;
}


