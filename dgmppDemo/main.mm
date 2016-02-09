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

using namespace dgmpp;

std::shared_ptr<Ship> addShip(std::shared_ptr<Engine> engine, NSString* dna, int level = 5) {
	NSMutableArray* components = [[dna componentsSeparatedByString:@":"] mutableCopy];
	TypeID shipTypeID = [components[0] intValue];
	[components removeObjectAtIndex:0];
	
	auto pilot = engine->getGang()->addPilot();
	pilot->setAllSkillsLevel(level);
	auto ship = pilot->setShip(shipTypeID);
	
	engine->beginUpdates();
	std::list<TypeID> chargeIDs;
	for (NSString* component in components) {
		NSArray* c = [component componentsSeparatedByString:@";"];
		int32_t n = 1;
		TypeID typeID = [c[0] intValue];
		if (typeID == 0)
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
					module->setPreferredState(Module::STATE_ACTIVE);
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
}

int main(int argc, const char * argv[]) {
	@autoreleasepool {
		//std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
		std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/work/git/EVEUniverse/dbTools/dbinit/dgm.sqlite"));
		
		double lastUpdateTime = 1452068276;
		auto planet = engine->setPlanet(2016);
		planet->setLastUpdate(lastUpdateTime - lastUpdateTime);
		planet->addFacility(2524, 1019338918550);
		planet->addFacility(2541, 1019339001861);
		planet->addFacility(2474, 1019339001862);
		planet->addFacility(2544, 1019339001863);
		planet->addFacility(2474, 1019339001865);
		planet->addFacility(2473, 1019339001870);
		planet->addFacility(2473, 1019339001873);
		planet->addFacility(2473, 1019339001877);
		planet->addFacility(2848, 1019339001881);
		planet->addFacility(2473, 1019339001884);
		planet->addFacility(2473, 1019339001885);
		planet->addFacility(2473, 1019339001888);
		planet->addFacility(2474, 1019586416755);
		planet->addFacility(2848, 1019741064685);
		
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001877), Commodity(engine, 2270, 0));
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001873), Commodity(engine, 2270, 0));
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001870), Commodity(engine, 2270, 0));
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001865), Commodity(engine, 2399, 0));
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019339001862), Commodity(engine, 2399, 0));
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019586416755), Commodity(engine, 2399, 0));
		planet->addRoute(planet->findFacility(1019339001861), planet->findFacility(1019586416755), Commodity(engine, 2399, 0));
		
		planet->addRoute(planet->findFacility(1019339001862), planet->findFacility(1019339001863), Commodity(engine, 3689, 0));
		planet->addRoute(planet->findFacility(1019339001865), planet->findFacility(1019339001863), Commodity(engine, 2329, 0));
		planet->addRoute(planet->findFacility(1019339001870), planet->findFacility(1019339001861), Commodity(engine, 2399, 0));
		planet->addRoute(planet->findFacility(1019339001873), planet->findFacility(1019339001861), Commodity(engine, 2399, 0));
		planet->addRoute(planet->findFacility(1019339001877), planet->findFacility(1019339001861), Commodity(engine, 2399, 0));
		planet->addRoute(planet->findFacility(1019339001881), planet->findFacility(1019339001861), Commodity(engine, 2270, 0));
		planet->addRoute(planet->findFacility(1019339001884), planet->findFacility(1019339001861), Commodity(engine, 2396, 0));
		planet->addRoute(planet->findFacility(1019339001885), planet->findFacility(1019339001861), Commodity(engine, 2396, 0));
		planet->addRoute(planet->findFacility(1019339001888), planet->findFacility(1019339001861), Commodity(engine, 2396, 0));
		planet->addRoute(planet->findFacility(1019586416755), planet->findFacility(1019339001863), Commodity(engine, 2329, 0));
		planet->addRoute(planet->findFacility(1019741064685), planet->findFacility(1019339001861), Commodity(engine, 2288, 0));
		
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001862))->setSchematic(73);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001865))->setSchematic(79);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001870))->setSchematic(127);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001873))->setSchematic(127);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001877))->setSchematic(127);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001884))->setSchematic(134);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001885))->setSchematic(134);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019339001888))->setSchematic(134);
		std::dynamic_pointer_cast<IndustryFacility>(planet->findFacility(1019586416755))->setSchematic(79);

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
		

		auto fac = planet->findFacility(1019339001865);
/*		for (const auto& warning: planet->getWarnings()) {
			switch (warning->getCode()) {
				case Warning::CODE_WASTED:
					std::cout << (int64_t) (warning->getTimeStamp() - lastUpdateTime) << " Wasted: " << warning->getSource()->getTypeName() << " " << (int32_t) (warning->getArg() * 100) << "%" << std::endl;
					break;
				case Warning::CODE_PRODUCTION_STOPPED:
					std::cout << (int64_t) (warning->getTimeStamp() - lastUpdateTime) << " Production stopped: " << warning->getSource()->getTypeName() << std::endl;
					break;
				case Warning::CODE_STORAGE_IS_FULL:
					std::cout << (int64_t) (warning->getTimeStamp() - lastUpdateTime) << " Storage is full: " << warning->getSource()->getTypeName() << " " << (warning->getArg() * 100.0) << "%" << std::endl;
					break;
				default:
					break;
			}
		}*/
		
		//std::cout << *planet << std::endl;
		auto free = fac->getFreeVolume();
		return 0;
		NSString* garmurDNA = @"33816:2404;3:14248;1:1952;1:19349;1:28746;1:31936;1:2605;1:2048;1:31183;1:31153;1:31111;1:29009;1:27371;3::";
		NSString* ishkurDNA = @"12042:3178;3:5973;1:448;1:4025;1:1183;1:1447;1:10190;1:2048;1:31538;1:31526;1:2456;5:12612;3::";
		NSString* vigilantDNA = @"17722:3146;5:5439;1:4025;1:6160;1:5975;1:10190;3:4405;2:2048;1:31546;1:31055;1:2185;5:12789;5:29011;1::";
		//NSString* vigilantDNA = @"17722:3146;5:5439;1:4025;1:10850;1:5975;1:3530;1:4405;2:10190;3:31546;1:31055;1:2185;5:12789;5::";
		NSString* magusDNA = @"37483:4284;1:4282;1:4280;1:11014;2::";
		//NSString* morosDNA = @"19724:4292;1::";
		NSString* dramielDNA = @"17932:34595;1:12084;1::";
		CFTimeInterval t0 = CACurrentMediaTime();
		auto garmur = addShip(engine, garmurDNA);
		auto ishkur = addShip(engine, ishkurDNA);
		auto vigilant = addShip(engine, vigilantDNA);
		auto dramiel = addShip(engine, dramielDNA);
//		auto magus1 = addShip(engine, magusDNA, 1);
//		auto magus5 = addShip(engine, magusDNA, 5);
		CFTimeInterval t1 = CACurrentMediaTime();
		NSLog(@"load %f", t1 - t0);
		
		
/*		Tank tankOff = vigilant->getTank();
		HitPoints hpOff = vigilant->getHitPoints();
		float capOff = vigilant->getCapUsed();
		engine->getGang()->setFleetBooster(std::dynamic_pointer_cast<Character>(magus1->getOwner()));
		Tank tank1 = vigilant->getSustainableTank();
		HitPoints hp1 = vigilant->getHitPoints();
		float cap1 = vigilant->getCapUsed();
		engine->getGang()->setFleetBooster(std::dynamic_pointer_cast<Character>(magus5->getOwner()));
		Tank tank5 = vigilant->getSustainableTank();
		HitPoints hp5 = vigilant->getHitPoints();
		float cap5 = vigilant->getCapUsed();
		engine->getGang()->setSquadBooster(std::dynamic_pointer_cast<Character>(magus1->getOwner()));
		Tank tank15 = vigilant->getSustainableTank();
		HitPoints hp15 = vigilant->getHitPoints();
		float cap15 = vigilant->getCapUsed();*/
		
/*		std::ofstream os;
		os.open("/Users/shimanski/tmp/gang.json");
		os << *engine->getGang() << std::endl;
		os.close();*/
		return 0;
		auto velocity = dramiel->getVelocity();
		auto hp = vigilant->getHitPoints();
		float dps = vigilant->getWeaponDps();
		
		for (int j = 0; j < 5; j++) {
			CFTimeInterval t0 = CACurrentMediaTime();
			CombatSimulator simulator(garmur, ishkur);
			CombatSimulator::OrbitState state(garmur, ishkur, 0, 5000);
			int n = 300;
			float dx = 50000 / n;
			float x = dx;
			for (int i = 0; i < n; i++) {
				state.setOrbitRadius(x);
				simulator.setState(state);
				simulator.timeToDie();
				simulator.timeToKill();
				x += dx;
			}
			CFTimeInterval t1 = CACurrentMediaTime();
			NSLog(@"%f", t1 - t0);
		}
	}
    return 0;
}

/*

 2015-12-14 13:20:07.863 dgmppDemo[7185:846124] load 0.321260
 2015-12-14 13:20:08.490 dgmppDemo[7185:846124] 0.613162
 2015-12-14 13:20:09.085 dgmppDemo[7185:846124] 0.595061
 2015-12-14 13:20:09.679 dgmppDemo[7185:846124] 0.593356
 2015-12-14 13:20:10.267 dgmppDemo[7185:846124] 0.587562
 2015-12-14 13:20:10.849 dgmppDemo[7185:846124] 0.581632
 Program ended with exit code: 0
*/