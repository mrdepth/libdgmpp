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
	auto ship = pilot->ship(TypeID::nyx);
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++)
		ship->addDrone(TypeID::termiteII);
	}
	
	
	
	std::cout << "DPS: " << (ship->dronesDPS() * 1s).total() << std::endl;
	std::cout << "Volley: " << ship->dronesVolley().total() << std::endl;
	
	handle h;
	*reinterpret_cast<std::unique_ptr<A>*>(&h.handle) = std::unique_ptr<A>(new A());
	
    return 0;
}


