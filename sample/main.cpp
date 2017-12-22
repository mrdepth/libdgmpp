#include <iostream>
#include "dgmpp.hpp"

using namespace dgmpp;

class A {
public:
	int i = 15;
	~A() {
		std::cout<<"~A()" << std::endl;
	}
};

struct handle {
	int tag;
	void* handle;
} ;

int main(int argc, const char * argv[]) {
	auto gang = Gang::Create();
	auto pilot = gang->addPilot();
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(TypeID::dominix);
		
	auto ab = ship->add(Module::Create(TypeID::_100MNAfterburnerII));
	ab->state(Module::State::overloaded);
	
	std::cout << "Velocity: " << ship->velocity().count() << " m/s" << std::endl;
	
	handle h;
	*reinterpret_cast<std::unique_ptr<A>*>(&h.handle) = std::unique_ptr<A>(new A());
	
    return 0;
}


