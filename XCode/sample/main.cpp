#include <iostream>
#include "dgmpp.hpp"
#include <typeinfo>
#include <type_traits>

using namespace dgmpp;


int main(int argc, const char * argv[]) {
    auto gang = std::make_shared<Gang>();
    auto pilot = std::make_shared<Character>();
    gang->add(pilot);
	pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::proteus);
	pilot->ship(ship);
    ship->add(std::make_shared<Module>(TypeID::_10MNAfterburnerI), Module::anySocket, true);
    ship->add(std::make_shared<Module>(TypeID::mediumShieldBoosterII), Module::anySocket, true);
    ship->add(std::make_shared<Module>(TypeID::ionBlasterCannonII), Module::anySocket, true);
    ship->add(std::make_shared<Module>(TypeID::ionBlasterCannonII), Module::anySocket, true);

//    auto modules = ship->modules();
	
	std::cout << "DPS: " << (ship->dronesDPS() * 1s).total() << std::endl;
	std::cout << "Volley: " << ship->dronesVolley().total() << std::endl;
	
    ship = nullptr;
    pilot = nullptr;
    gang = nullptr;
    return 0;
}


