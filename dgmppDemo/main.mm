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

using namespace dgmpp;

std::shared_ptr<Ship> addShip(std::shared_ptr<Engine> engine, NSString* dna, int level = 5) {
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
}

int main2()
{
	// future from a packaged_task
	/*std::packaged_task<int()> task([](){ return 7; }); // wrap the function
	std::future<int> f1 = task.get_future();  // get a future
	std::thread(std::move(task)).detach(); // launch on a thread
	
	// future from an async()
	std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });
	
	// future from a promise
	std::promise<int> p;
	std::future<int> f3 = p.get_future();
	std::thread( [](std::promise<int>& p){ p.set_value(9); },
				std::ref(p) ).detach();
	
	std::cout << "Waiting...";
	f1.wait();
	f2.wait();
	f3.wait();
	
	auto b = f1.valid();
	auto i = f1.get();
	b = f1.valid();

	i = f1.get();
	i = f1.get();
	i = f1.get();

	std::cout << "Done!\nResults are: "
	<< f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';*/
	
	for (int i = 0; i < 10; i++) {
	
	auto t0 = CACurrentMediaTime();
	auto b = 	sqlite3_threadsafe();


		
	std::mutex m;

	std::future<bool> f[1000];
	for (auto& ff: f) {
		ff = std::async(std::launch::async, [&]() -> bool {
//			m.lock();
			std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/dbTools/dbinit/dgm.sqlite"));
			auto request = engine->getSqlConnector()->getReusableFetchRequest("select * from invTypes");
//			auto request = std::make_shared<SqliteFetchRequest>("select * from invTypes");
			auto result = engine->getSqlConnector()->exec(request);
//			m.unlock();
		for (int j = 0; j < 1000; j++)
			result->next();
//			while (result->next()) {
//			}
			return true;
		});
	}
	for (auto& ff: f)
		ff.wait();
	auto t1 = CACurrentMediaTime();
	
	auto t = t1 - t0;
		NSLog(@"%f", t);
	}
	return 0;
}

int main(int argc, const char * argv[]) {
	@autoreleasepool {
//		main2();
//		std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
		std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/work/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
		auto pilot = engine->getGang()->addPilot();
		pilot->setAllSkillsLevel(5);
		
/*
		//pilot->setAllSkillsLevel(5);
		std::map<int, int> skills;
		skills[32339] = 5;
		pilot->setSkillLevels(skills);
		
		auto spaceStructure = pilot->setStructure(35832);
 
		std::shared_ptr<Drone> drone;
		for (int i = 0; i < 30; i++) {
			drone = spaceStructure->addDrone(40365);
		}
		int heavy = spaceStructure->getDroneSquadronUsed(Drone::FIGHTER_SQUADRON_HEAVY);
		int light = spaceStructure->getDroneSquadronUsed(Drone::FIGHTER_SQUADRON_LIGHT);
		float v = drone->getAttribute(2226)->getValue();
		
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
		
		//std::cout << *planet << std::endl;
		auto free = fac->getFreeVolume();
		return 0;
*/
		
		
		auto eos = pilot->setShip(TypeID(22442));
		auto armorRepairer = eos->addModule(TypeID(3540));
		
		auto before = eos->getEffectiveTank().armorRepair;
		
		auto armorCommandBurst = eos->addModule(TypeID(43552));
//		armorCommandBurst->setCharge(42832); //Armor Energizing Charge
		armorCommandBurst->setCharge(TypeID(42833)); //Rapid Repair Charge
		armorCommandBurst->setState(dgmpp::Module::State::active);
		auto after = eos->getEffectiveTank().armorRepair;
		
		
		
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
