#include <iostream>
#include "dgmpp.hpp"
#include <typeinfo>
#include <type_traits>

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
	auto ship = pilot->ship(TypeID::apostle);
	
	for (int i = 0; i < 4; i++)
		ship->addModule(TypeID::CONCORDCapitalRemoteArmorRepairer);
	ship->addModule(TypeID::triageModuleII);
	ship->addModule(TypeID::armorCommandBurstII)->charge(TypeID::armorEnergizingCharge);
	
	ship->addModule(TypeID::imperialNavyCapRecharger);
	ship->addModule(TypeID::imperialNavyCapRecharger);
	
	ship->addModule(TypeID::dominationCapitalCapBattery);
	ship->addModule(TypeID::dominationCapitalCapBattery);
	
	ship->addModule(TypeID::CONCORDCapitalArmorRepairer);
	ship->addModule(TypeID::CONCORDCapitalArmorRepairer);
	for (int i = 0; i < 4; i++)
		ship->addModule(TypeID::darkBloodCapacitorPowerRelay);
//	ship->addModule(TypeID::centumATypeEnergizedAdaptiveNanoMembrane);
	
	ship->addModule(TypeID::capitalCapacitorControlCircuitI);
	ship->addModule(TypeID::capitalCapacitorControlCircuitII);
	ship->addModule(TypeID::capitalCapacitorControlCircuitII);
	
	(*ship)[AttributeID::armorKineticDamageResonance]->dumpAffectors();

	
	std::cout << "DPS: " << (ship->dronesDPS() * 1s).total() << std::endl;
	std::cout << "Volley: " << ship->dronesVolley().total() << std::endl;
	
	handle h;
	*reinterpret_cast<std::unique_ptr<A>*>(&h.handle) = std::unique_ptr<A>(new A());
	
    return 0;
}


