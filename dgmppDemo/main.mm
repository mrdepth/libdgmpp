//
//  main.m
//  dgmppDemo
//
//  Created by Артем Шиманский on 11.12.15.
//
//

#import <Foundation/Foundation.h>
#import <dgmpp/dgmpp.h>
#import <QuartzCore/QuartzCore.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <future>
#include <array>
#include <numeric>
#include <type_traits>
#include <sstream>
#include <queue>
#include <chrono>

/*std::shared_ptr<Ship> addShip(std::shared_ptr<Engine> engine, NSString* dna, int level = 5) {
	NSMutableArray* components = [[dna componentsSeparatedByString:@":"] mutableCopy];
	TypeID shipTypeID = static_cast<TypeID>([components[0] intValue]);
	[components removeObjectAtIndex:0];
	
	auto pilot = engine->getGang()->addPilot();
	pilot->setAllSkillsLevel(level);
	auto ship = pilot->setShip(shipTypeID);
	
	engine->beginUpdates();
	std::list<TypeID> chargeIDs;
	for (NSString* component in components) {
		NSArray* c = [component componentsSeparatedByString:@";"];
		int32_t n = 1;
		TypeID typeID = static_cast<TypeID>([c[0] intValue]);
		if (typeID == TypeID::none)
			continue;
		if (c.count == 2)
			n = [c[1] intValue];
		bool isModule = true;
		for (int i = 0; i < n; i++) {
			if (isModule) {
				auto module = ship->addModule(typeID);
				if (!module) {
					isModule = false;
				}
				else
					module->setState(Module::State::active);
			}
			if (!isModule) {
				auto drone = ship->addDrone(typeID);
				if (!drone) {
					chargeIDs.push_back(typeID);
					break;
				}
			}
		}
	}
	for (auto typeID: chargeIDs) {
		for (auto module: ship->getModules()) {
			if (!module->getCharge())
				module->setCharge(typeID);
		}
	}
	engine->commitUpdates();
	return ship;
}*/

/*
void addFacility(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, dgmpp::TypeID typeID, int64_t identifier) {
	planet1->addFacility(typeID, identifier);
	planet2.add(typeID, identifier);
}

void route(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t from, int64_t to, dgmpp::TypeID typeID) {
	planet1->addRoute(planet1->findFacility(from), planet1->findFacility(to), Commodity(planet1->getEngine(), typeID, 0));
	planet2.add({planet2[from], planet2[to], dgmpp::Commodity(typeID)});
}

void setSchematic(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t identifier, dgmpp::SchematicID schematicID) {
	std::dynamic_pointer_cast<dgmpp::IndustryFacility>(planet1->findFacility(identifier))->setSchematic(schematicID);
	dynamic_cast<dgmpp::Factory*>(planet2[identifier])->schematic(schematicID);
}

void setLaunchTime(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t identifier, double launchTime) {
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet1->findFacility(identifier))->setLaunchTime(launchTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet2[identifier])->launchTime(std::chrono::seconds(static_cast<long long>(launchTime)));

}

void setInstallTime(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t identifier, double installTime) {
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet1->findFacility(identifier))->setInstallTime(installTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet2[identifier])->installTime(std::chrono::seconds(static_cast<long long>(installTime)));
}

void setExpiryTime(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t identifier, double expiryTime) {
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet1->findFacility(identifier))->setExpiryTime(expiryTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet2[identifier])->expiryTime(std::chrono::seconds(static_cast<long long>(expiryTime)));
}

void setCycleTime(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t identifier, double cycleTime) {
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet1->findFacility(identifier))->setCycleTime(cycleTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet2[identifier])->cycleTime(std::chrono::seconds(static_cast<long long>(cycleTime)));
}

void setQuantityPerCycle(std::shared_ptr<dgmpp::Planet> planet1, dgmpp::Planet& planet2, int64_t identifier, uint32_t quantityPerCycle) {
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet1->findFacility(identifier))->setQuantityPerCycle(quantityPerCycle);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet2[identifier])->quantityPerCycle(quantityPerCycle);
}


void testPI(std::shared_ptr<Engine> const& engine) {
	using namespace dgmpp;
	double lastUpdateTime = 1452068276;
	auto planet = engine->setPlanet(TypeID::none);
	planet->setLastUpdate(lastUpdateTime - lastUpdateTime);
	planet->addFacility(TypeID::barrenCommandCenter, 1019338918550);
	planet->addFacility(TypeID::barrenStorageFacility, 1019339001861);
	planet->addFacility(TypeID::barrenAdvancedIndustryFacility, 1019339001862);
	planet->addFacility(TypeID::barrenLaunchpad, 1019339001863);
	planet->addFacility(TypeID::barrenAdvancedIndustryFacility, 1019339001865);
	planet->addFacility(TypeID::barrenBasicIndustryFacility, 1019339001870);
	planet->addFacility(TypeID::barrenBasicIndustryFacility, 1019339001873);
	planet->addFacility(TypeID::barrenBasicIndustryFacility, 1019339001877);
	planet->addFacility(TypeID::barrenExtractorControlUnit, 1019339001881);
	planet->addFacility(TypeID::barrenBasicIndustryFacility, 1019339001884);
	planet->addFacility(TypeID::barrenBasicIndustryFacility, 1019339001885);
	planet->addFacility(TypeID::barrenBasicIndustryFacility, 1019339001888);
	planet->addFacility(TypeID::barrenAdvancedIndustryFacility, 1019586416755);
	planet->addFacility(TypeID::barrenExtractorControlUnit, 1019741064685);
	
	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001877), Commodity(engine, TypeID::nobleMetals, 0));
	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001873), Commodity(engine, TypeID::nobleMetals, 0));
	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001870), Commodity(engine, TypeID::nobleMetals, 0));
	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001865), Commodity(engine, TypeID::preciousMetals, 0));
	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001862), Commodity(engine, TypeID::preciousMetals, 0));
	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019586416755), Commodity(engine, TypeID::preciousMetals, 0));
//	planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019586416755), Commodity(engine, TypeID::preciousMetals, 0));
	
	planet->addRoute(planet->findFacility(1019339001862), planet->findFacility(1019339001863), Commodity(engine, TypeID::mechanicalParts, 0));
	planet->addRoute(planet->findFacility(1019339001865), planet->findFacility(1019339001863), Commodity(engine, TypeID::biocells, 0));
	planet->addRoute(planet->findFacility(1019339001870), planet->findFacility(1019339001861), Commodity(engine, TypeID::preciousMetals, 0));
	planet->addRoute(planet->findFacility(1019339001873), planet->findFacility(1019339001861), Commodity(engine, TypeID::preciousMetals, 0));
	planet->addRoute(planet->findFacility(1019339001877), planet->findFacility(1019339001861), Commodity(engine, TypeID::preciousMetals, 0));
	planet->addRoute(planet->findFacility(1019339001881), planet->findFacility(1019339001861), Commodity(engine, TypeID::nobleMetals, 0));
	planet->addRoute(planet->findFacility(1019339001884), planet->findFacility(1019339001861), Commodity(engine, TypeID::biofuels, 0));
	planet->addRoute(planet->findFacility(1019339001885), planet->findFacility(1019339001861), Commodity(engine, TypeID::biofuels, 0));
	planet->addRoute(planet->findFacility(1019339001888), planet->findFacility(1019339001861), Commodity(engine, TypeID::biofuels, 0));
	planet->addRoute(planet->findFacility(1019586416755), planet->findFacility(1019339001863), Commodity(engine, TypeID::biocells, 0));
	planet->addRoute(planet->findFacility(1019741064685), planet->findFacility(1019339001861), Commodity(engine, TypeID::carbonCompounds, 0));
	
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001862))->setSchematic(SchematicID::mechanicalParts);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001865))->setSchematic(SchematicID::biocells);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001870))->setSchematic(SchematicID::preciousMetals);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001873))->setSchematic(SchematicID::preciousMetals);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001877))->setSchematic(SchematicID::preciousMetals);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001884))->setSchematic(SchematicID::biofuels);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001885))->setSchematic(SchematicID::biofuels);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001888))->setSchematic(SchematicID::biofuels);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019586416755))->setSchematic(SchematicID::biocells);
	
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019339001881))->setCycleTime(120 * 60);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019339001881))->setQuantityPerCycle(4741);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019339001881))->setLaunchTime(1452068276 - lastUpdateTime);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019339001881))->setInstallTime(1452068276 - lastUpdateTime);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019339001881))->setExpiryTime(1452500276 - lastUpdateTime);
	
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019741064685))->setCycleTime(120 * 60);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019741064685))->setQuantityPerCycle(6425);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019741064685))->setLaunchTime(1452068276 - lastUpdateTime);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019741064685))->setInstallTime(1452068276 - lastUpdateTime);
	std::dynamic_pointer_cast<ExtractorControlUnit>(planet->findFacility(1019741064685))->setExpiryTime(1452500276 - lastUpdateTime);
	
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019586416755))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001865))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001870))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001873))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001877))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001884))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001885))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001888))->setLaunchTime(0);
	std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019586416755))->setLaunchTime(0);
	
	double endTime = planet->simulate();
	auto fac1 = planet->findFacility(1019339001877);
	auto fac2 = planet->findFacility(1019339001873);
	auto fac3 = planet->findFacility(1019339001870);
	auto i = fac1->getIncomming(Commodity(engine, TypeID::preciousMetals, 0)).getQuantity() +
			fac2->getIncomming(Commodity(engine, TypeID::preciousMetals, 0)).getQuantity() +
			fac3->getIncomming(Commodity(engine, TypeID::preciousMetals, 0)).getQuantity();
	
//	i = planet->findFacility(1019339001861)->getIncomming(Commodity(engine, TypeID::nobleMetals, 0)).getQuantity();
//	auto ecu1 = planet->findFacility(1019339001881);
//	auto ecu2 = planet->findFacility(1019741064685);
//	i = ecu1->getIncomming(Commodity(engine, TypeID::nobleMetals, 0)).getQuantity();
//	i += ecu2->getIncomming(Commodity(engine, TypeID::carbonCompounds, 0)).getQuantity();
	std::cout <<"endTime1:" << endTime << "; income1: " << i << std::endl;
}

void testPI2() {
	using namespace std::chrono_literals;
	
	auto planet = dgmpp::Planet();
	auto lastUpdateTime = 1452068276s;
//	planet.lastUpdate(0s);
	
	planet.add(TypeID::barrenCommandCenter, 1019338918550);
	planet.add(TypeID::barrenStorageFacility, 1019339001861);
	planet.add(TypeID::barrenAdvancedIndustryFacility, 1019339001862);
	planet.add(TypeID::barrenLaunchpad, 1019339001863);
	planet.add(TypeID::barrenAdvancedIndustryFacility, 1019339001865);
	planet.add(TypeID::barrenBasicIndustryFacility, 1019339001870);
	planet.add(TypeID::barrenBasicIndustryFacility, 1019339001873);
	planet.add(TypeID::barrenBasicIndustryFacility, 1019339001877);
	planet.add(TypeID::barrenExtractorControlUnit, 1019339001881);
	planet.add(TypeID::barrenBasicIndustryFacility, 1019339001884);
	planet.add(TypeID::barrenBasicIndustryFacility, 1019339001885);
	planet.add(TypeID::barrenBasicIndustryFacility, 1019339001888);
	planet.add(TypeID::barrenAdvancedIndustryFacility, 1019586416755);
	planet.add(TypeID::barrenExtractorControlUnit, 1019741064685);
	
	planet.add(dgmpp::Route{planet[1019339001861], planet[1019339001877], dgmpp::Commodity{TypeID::nobleMetals}});
	planet.add(dgmpp::Route{planet[1019339001861], planet[1019339001873], dgmpp::Commodity{TypeID::nobleMetals}});
	planet.add(dgmpp::Route{planet[1019339001861], planet[1019339001870], dgmpp::Commodity{TypeID::nobleMetals}});
	planet.add(dgmpp::Route{planet[1019339001861], planet[1019339001865], dgmpp::Commodity{TypeID::preciousMetals}});
	planet.add(dgmpp::Route{planet[1019339001861], planet[1019339001862], dgmpp::Commodity{TypeID::preciousMetals}});
	planet.add(dgmpp::Route{planet[1019339001861], planet[1019586416755], dgmpp::Commodity{TypeID::preciousMetals}});
//	planet.add(dgmpp::Route{planet[1019339001861], planet[1019586416755], dgmpp::Commodity{TypeID::preciousMetals}});

	planet.add(dgmpp::Route{planet[1019339001862], planet[1019339001863], dgmpp::Commodity{TypeID::mechanicalParts}});
	planet.add(dgmpp::Route{planet[1019339001865], planet[1019339001863], dgmpp::Commodity{TypeID::biocells}});
	planet.add(dgmpp::Route{planet[1019339001870], planet[1019339001861], dgmpp::Commodity{TypeID::preciousMetals}});
	planet.add(dgmpp::Route{planet[1019339001873], planet[1019339001861], dgmpp::Commodity{TypeID::preciousMetals}});
	planet.add(dgmpp::Route{planet[1019339001877], planet[1019339001861], dgmpp::Commodity{TypeID::preciousMetals}});
	planet.add(dgmpp::Route{planet[1019339001881], planet[1019339001861], dgmpp::Commodity{TypeID::nobleMetals}});
	planet.add(dgmpp::Route{planet[1019339001884], planet[1019339001861], dgmpp::Commodity{TypeID::biofuels}});
	planet.add(dgmpp::Route{planet[1019339001885], planet[1019339001861], dgmpp::Commodity{TypeID::biofuels}});
	planet.add(dgmpp::Route{planet[1019339001888], planet[1019339001861], dgmpp::Commodity{TypeID::biofuels}});
	planet.add(dgmpp::Route{planet[1019586416755], planet[1019339001863], dgmpp::Commodity{TypeID::biocells}});
	planet.add(dgmpp::Route{planet[1019741064685], planet[1019339001861], dgmpp::Commodity{TypeID::carbonCompounds}});

	dynamic_cast<dgmpp::Factory*>(planet[1019339001862])->schematic(SchematicID::mechanicalParts);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001865])->schematic(SchematicID::biocells);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001870])->schematic(SchematicID::preciousMetals);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001873])->schematic(SchematicID::preciousMetals);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001877])->schematic(SchematicID::preciousMetals);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001884])->schematic(SchematicID::biofuels);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001885])->schematic(SchematicID::biofuels);
	dynamic_cast<dgmpp::Factory*>(planet[1019339001888])->schematic(SchematicID::biofuels);
	dynamic_cast<dgmpp::Factory*>(planet[1019586416755])->schematic(SchematicID::biocells);

	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019339001881])->cycleTime(2h);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019339001881])->quantityPerCycle(4741);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019339001881])->launchTime(1452068276s - lastUpdateTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019339001881])->installTime(1452068276s - lastUpdateTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019339001881])->expiryTime(1452500276s - lastUpdateTime);

	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019741064685])->cycleTime(2h);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019741064685])->quantityPerCycle(6425);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019741064685])->launchTime(1452068276s - lastUpdateTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019741064685])->installTime(1452068276s - lastUpdateTime);
	dynamic_cast<dgmpp::ExtractorControlUnit*>(planet[1019741064685])->expiryTime(1452500276s - lastUpdateTime);

//	dynamic_cast<dgmpp::Factory*>(planet[1019586416755])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001865])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001870])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001873])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001877])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001884])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001885])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019339001888])->launchTime(0s);
//	dynamic_cast<dgmpp::Factory*>(planet[1019586416755])->launchTime(0s);

	auto endTime = planet.run();
	auto fac1 = planet[1019339001877];
	auto fac2 = planet[1019339001873];
	auto fac3 = planet[1019339001870];
	auto i = fac1->income(TypeID::preciousMetals).quantity() +
			fac2->income(TypeID::preciousMetals).quantity() +
			fac3->income(TypeID::preciousMetals).quantity();
//	i = planet[1019339001861]->income(TypeID::nobleMetals).quantity();
//	auto free = fac->freeVolume();
	
//	auto ecu1 = planet[1019339001881];
//	auto ecu2 = planet[1019741064685];
//	i = ecu1->income(TypeID::nobleMetals).quantity() +
//		ecu2->income(TypeID::carbonCompounds).quantity();
	
	std::cout <<"endTime2:" << endTime.count() << "; income2: " << i << std::endl;

}

void testPI3(std::shared_ptr<Engine> const& engine) {
	using namespace dgmpp;
	auto planet1 = engine->setPlanet(TypeID::none);
	auto planet2 = dgmpp::Planet();
	
	addFacility(planet1, planet2, TypeID::barrenStorageFacility, 10);

	for (int i = 30; i <= 45; i++)
		addFacility(planet1, planet2, TypeID::barrenBasicIndustryFacility, i);
	for (int i = 20; i <= 28; i++) {
		addFacility(planet1, planet2, TypeID::barrenExtractorControlUnit, i);
		setCycleTime(planet1, planet2, i, 2 * 3600);
		setQuantityPerCycle(planet1, planet2, i, 4000);
		setExpiryTime(planet1, planet2, i, 432000);
	}
	
	setSchematic(planet1, planet2, 30, dgmpp::SchematicID::nanoFactory);
	route(planet1, planet2, 10, 30, TypeID::industrialExplosives);
	route(planet1, planet2, 10, 30, TypeID::reactiveMetals);
	route(planet1, planet2, 10, 30, TypeID::ukomiSuperconductors);
	route(planet1, planet2, 30, 10, TypeID::nanoFactory);

	setSchematic(planet1, planet2, 31, dgmpp::SchematicID::industrialExplosives);
	route(planet1, planet2, 10, 31, TypeID::fertilizer);
	route(planet1, planet2, 10, 31, TypeID::polytextiles);
	route(planet1, planet2, 31, 10, TypeID::industrialExplosives);

	setSchematic(planet1, planet2, 32, dgmpp::SchematicID::reactiveMetals);
	route(planet1, planet2, 10, 32, TypeID::baseMetals);
	route(planet1, planet2, 32, 10, TypeID::reactiveMetals);

	setSchematic(planet1, planet2, 33, dgmpp::SchematicID::ukomiSuperconductor);
	route(planet1, planet2, 10, 33, TypeID::syntheticOil);
	route(planet1, planet2, 10, 33, TypeID::superconductors);
	route(planet1, planet2, 33, 10, TypeID::ukomiSuperconductors);

	setSchematic(planet1, planet2, 34, dgmpp::SchematicID::fertilizer);
	route(planet1, planet2, 10, 34, TypeID::bacteria);
	route(planet1, planet2, 10, 34, TypeID::proteins);
	route(planet1, planet2, 34, 10, TypeID::fertilizer);

	setSchematic(planet1, planet2, 35, dgmpp::SchematicID::polytextiles);
	route(planet1, planet2, 10, 35, TypeID::biofuels);
	route(planet1, planet2, 10, 35, TypeID::industrialFibers);
	route(planet1, planet2, 35, 10, TypeID::polytextiles);

	setSchematic(planet1, planet2, 36, dgmpp::SchematicID::syntheticOil);
	route(planet1, planet2, 10, 36, TypeID::electrolytes);
	route(planet1, planet2, 10, 36, TypeID::oxygen);
	route(planet1, planet2, 36, 10, TypeID::syntheticOil);

	setSchematic(planet1, planet2, 37, dgmpp::SchematicID::superconductors);
	route(planet1, planet2, 10, 37, TypeID::plasmoids);
	route(planet1, planet2, 10, 37, TypeID::water);
	route(planet1, planet2, 37, 10, TypeID::superconductors);

	setSchematic(planet1, planet2, 38, dgmpp::SchematicID::bacteria);
	route(planet1, planet2, 10, 38, TypeID::microorganisms);
	route(planet1, planet2, 38, 10, TypeID::bacteria);

	setSchematic(planet1, planet2, 39, dgmpp::SchematicID::proteins);
	route(planet1, planet2, 10, 39, TypeID::complexOrganisms);
	route(planet1, planet2, 39, 10, TypeID::proteins);

	setSchematic(planet1, planet2, 40, dgmpp::SchematicID::biofuels);
	route(planet1, planet2, 10, 40, TypeID::carbonCompounds);
	route(planet1, planet2, 40, 10, TypeID::biofuels);

	setSchematic(planet1, planet2, 41, dgmpp::SchematicID::industrialFibers);
	route(planet1, planet2, 10, 41, TypeID::autotrophs);
	route(planet1, planet2, 41, 10, TypeID::industrialFibers);

	setSchematic(planet1, planet2, 42, dgmpp::SchematicID::electrolytes);
	route(planet1, planet2, 10, 42, TypeID::ionicSolutions);
	route(planet1, planet2, 42, 10, TypeID::electrolytes);

	setSchematic(planet1, planet2, 43, dgmpp::SchematicID::oxygen);
	route(planet1, planet2, 10, 43, TypeID::nobleGas);
	route(planet1, planet2, 43, 10, TypeID::oxygen);

	setSchematic(planet1, planet2, 44, dgmpp::SchematicID::plasmoids);
	route(planet1, planet2, 10, 44, TypeID::suspendedPlasma);
	route(planet1, planet2, 44, 10, TypeID::plasmoids);

	setSchematic(planet1, planet2, 45, dgmpp::SchematicID::water);
	route(planet1, planet2, 10, 45, TypeID::aqueousLiquids);
	route(planet1, planet2, 45, 10, TypeID::water);

	
	route(planet1, planet2, 20, 10, TypeID::baseMetals);
	route(planet1, planet2, 21, 10, TypeID::microorganisms);
	route(planet1, planet2, 22, 10, TypeID::complexOrganisms);
	route(planet1, planet2, 23, 10, TypeID::carbonCompounds);
	route(planet1, planet2, 24, 10, TypeID::autotrophs);
	route(planet1, planet2, 25, 10, TypeID::ionicSolutions);
	route(planet1, planet2, 26, 10, TypeID::nobleGas);
	route(planet1, planet2, 27, 10, TypeID::suspendedPlasma);
	route(planet1, planet2, 28, 10, TypeID::aqueousLiquids);
	
	auto e1 = planet1->simulate();
	auto e2 = planet2.run();
	
	auto s1 = planet1->findFacility(10).get();
	auto s2 = planet2[10];
	
	auto raw = 	{TypeID::baseMetals,
	TypeID::microorganisms,
	TypeID::complexOrganisms,
	TypeID::carbonCompounds,
	TypeID::autotrophs,
	TypeID::ionicSolutions,
	TypeID::nobleGas,
	TypeID::suspendedPlasma,
		TypeID::aqueousLiquids};

	
	size_t sum1 = 0;
	for (auto i: s1->getCommodities()) {
		if (i.getQuantity() > 0)
			std::cout << (int)i.getTypeID() << ": " << i.getQuantity() << " ";
		sum1 += i.getQuantity();
	}
	std::cout << std::endl;
	size_t sum2 = 0;
	for (auto i: s2->commodities()) {
		if (i.quantity() > 0)
			std::cout << (int)i.metaInfo().typeID << ": " << i.quantity() << " ";
		sum2 += i.quantity();
	}
	
//	sum1 = sum2 = 0;
//	for (auto i: raw) {
//		auto a = s1->getIncomming(dgmpp::Commodity(planet1->getEngine(), i)).getQuantity();
//		auto b = s2->income(i).quantity();
//		sum1 += a;
//		sum2 += b;
//		if (a != b)
//			std::cout << a - b << " ";
//	}
	
	std::cout << std::endl;
	for (auto i: planet1->getFacilities())
		std::cout << i->getIdentifier() << " ";
	std::cout << std::endl;
	
	
	for (auto i: planet2.facilities())
		std::cout << i->identifier() << " ";
	std::cout << std::endl;

	std::cout << sum1 << " " << sum2 << std::endl;

}
*/

int main(int argc, const char * argv[]) {
    return 0;
}


