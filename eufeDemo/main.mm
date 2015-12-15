//
//  main.m
//  eufeDemo
//
//  Created by Артем Шиманский on 11.12.15.
//
//

#import <Foundation/Foundation.h>
#import <eufe/eufe.h>
#import <QuartzCore/QuartzCore.h>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace eufe;

std::shared_ptr<Ship> addShip(std::shared_ptr<Engine> engine, NSString* dna, int level = 5) {
	NSMutableArray* components = [[dna componentsSeparatedByString:@":"] mutableCopy];
	TypeID shipTypeID = [components[0] intValue];
	[components removeObjectAtIndex:0];
	
	auto pilot = engine->getGang()->addPilot();
	pilot->setAllSkillsLevel(level);
	auto ship = pilot->setShip(shipTypeID);
	
	//engine->beginUpdates();
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
	//engine->commitUpdates();
	return ship;
}

int main(int argc, const char * argv[]) {
	@autoreleasepool {
		NSString* garmurDNA = @"33816:2404;3:14248;1:1952;1:19349;1:28746;1:31936;1:2605;1:2048;1:31183;1:31153;1:31111;1:29009;1:27371;3::";
		NSString* ishkurDNA = @"12042:3178;3:5973;1:448;1:4025;1:1183;1:1447;1:10190;1:2048;1:31538;1:31526;1:2456;5:12612;3::";
		NSString* vigilantDNA = @"17722:3146;5:5439;1:4025;1:6160;1:5975;1:10190;3:4405;2:2048;1:31546;1:31055;1:2185;5:12789;5:29011;1::";
		//NSString* vigilantDNA = @"17722:3146;5:5439;1:4025;1:10850;1:5975;1:3530;1:4405;2:10190;3:31546;1:31055;1:2185;5:12789;5::";
		NSString* magusDNA = @"37483:4284;1:4282;1:4280;1:11014;2::";
		std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/dbTools/dbinit/eufe.sqlite"));
		//std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/work/git/EVEUniverse/dbTools/dbinit/eufe.sqlite"));
		CFTimeInterval t0 = CACurrentMediaTime();
		auto garmur = addShip(engine, garmurDNA);
		auto ishkur = addShip(engine, ishkurDNA);
		auto vigilant = addShip(engine, vigilantDNA);
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
		
		/*std::ofstream os;
		os.open("/Users/shimanski/tmp/gang.json");
		os << *engine->getGang() << std::endl;
		os.close();*/
		
		auto hp = vigilant->getHitPoints();
		float dps = vigilant->getWeaponDps();
		
		for (int j = 0; j < 5; j++) {
			CFTimeInterval t0 = CACurrentMediaTime();
			CombatSimulator simulator(garmur, ishkur);
			CombatSimulator::OrbitState state(garmur, ishkur, 0, 5000);
			int n = 500;
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

 2015-12-14 13:20:07.863 eufeDemo[7185:846124] load 0.321260
 2015-12-14 13:20:08.490 eufeDemo[7185:846124] 0.613162
 2015-12-14 13:20:09.085 eufeDemo[7185:846124] 0.595061
 2015-12-14 13:20:09.679 eufeDemo[7185:846124] 0.593356
 2015-12-14 13:20:10.267 eufeDemo[7185:846124] 0.587562
 2015-12-14 13:20:10.849 eufeDemo[7185:846124] 0.581632
 Program ended with exit code: 0
*/