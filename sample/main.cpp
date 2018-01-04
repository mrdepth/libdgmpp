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
	auto ship = pilot->ship(TypeID::scorpionNavyIssue);
	
	for (int i = 0; i < 3; i++)
		ship->add(Module::Create(TypeID::caldariNavyBallisticControlSystem));
	
	for (int i = 0; i < 6; i++)
		ship->add(Module::Create(TypeID::cruiseMissileLauncherII))->charge(Charge::Create(TypeID::scourgeFuryCruiseMissile));
	
	
	std::cout << "DPS: " << (ship->launchersDPS() * 1s).total() << std::endl;
	
	handle h;
	*reinterpret_cast<std::unique_ptr<A>*>(&h.handle) = std::unique_ptr<A>(new A());
	
    return 0;
}


