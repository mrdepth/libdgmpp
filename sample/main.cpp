#include <iostream>
#include "dgmpp.hpp"

using namespace dgmpp;

int main(int argc, const char * argv[]) {
	auto gang = Gang::Create();
	auto pilot = gang->addPilot();
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(TypeID::dominix);
	
	auto ab = ship->add(Module::Create(TypeID::_100MNAfterburnerII));
	ab->state(Module::State::overloaded);
	
	std::cout << "Velocity: " << ship->velocity().count() << " m/s" << std::endl;
    return 0;
}


