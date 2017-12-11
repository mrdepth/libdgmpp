//
//  dgmppTests.m
//  dgmppTests
//
//  Created by Артем Шиманский on 02.05.16.
//
//

#import <XCTest/XCTest.h>
#import <dgmpp/dgmpp.h>
#include <memory>

//using namespace dgmpp;
using namespace std::chrono_literals;

std::shared_ptr<dgmpp::Engine> createEngine() {
	return std::make_shared<dgmpp::Engine>(std::make_shared<dgmpp::SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
//	return std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/work/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
}

@interface dgmppTests : XCTestCase {
}

@end

@implementation dgmppTests

- (void)setUp {
    [super setUp];
//	std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/dbTools/dbinit/dgm.sqlite"));
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void) testSkills {
	using namespace dgmpp;
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	auto ship = pilot->setShip(Ship::Create(TypeID::dominix));
	ship->add(Module::Create(TypeID::largeArmorRepairerI));
	
	auto hp0 = ship->hitPoints();
	auto tank0 = ship->tank();
	auto cap0 = ship->capacitor().lastsTime();
	pilot->setSkillLevels(5);
	auto hp1 = ship->hitPoints();
	auto tank1 = ship->tank();
	auto cap1 = ship->capacitor().lastsTime();
	
	XCTAssertGreaterThan(hp1.total(), hp0.total());
	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank1.passiveShield, tank0.passiveShield);
	XCTAssertGreaterThan(cap1, cap0);
}

- (void) testGangBoost {
	using namespace dgmpp;
	auto gang = Gang::Create();
	auto pilotA = gang->add(Character::Create());
	pilotA->setSkillLevels(5);
	auto shipA = pilotA->setShip(Ship::Create(TypeID::dominix));
	shipA->add(Module::Create(TypeID::largeArmorRepairerI));
	
	auto ehp0 = shipA->effectiveHitPoints();

	auto pilotB = gang->add(Character::Create());
	pilotB->setSkillLevels(5);
	auto shipB = pilotB->setShip(Ship::Create(TypeID::erebus));
	shipB->add(Module::Create(TypeID::gallentePhenomenaGenerator));
	
	auto ehp1 = shipA->effectiveHitPoints();
	
	auto burst = shipB->add(Module::Create(TypeID::shieldCommandBurstI));
	burst->charge(Charge::Create(TypeID::shieldHarmonizingCharge));
	
	auto ehp2 = shipA->effectiveHitPoints();
	burst->charge(nullptr);
	auto ehp3 = shipA->effectiveHitPoints();
	
	XCTAssertGreaterThan(ehp1.total(), ehp0.total());
	XCTAssertGreaterThan(ehp2.total(), ehp1.total());
	XCTAssertEqual(ehp3.total(), ehp1.total());

}


- (void) testRepairers {
	using namespace dgmpp;
	auto engine = createEngine();
	auto gang = engine->getGang();
	auto pilot = gang->addPilot();
	pilot->setAllSkillsLevel(5);

	auto ship = pilot->setShip(TypeID::dominix);
	auto tank0 = ship->getTank();
	XCTAssertNotEqual(ship->addModule(TypeID::largeArmorRepairerI), nullptr);
	XCTAssertNotEqual(ship->addModule(TypeID::largeShieldBoosterI), nullptr);
	XCTAssertNotEqual(ship->addModule(TypeID::largeHullRepairerI), nullptr);
	auto tank1 = ship->getTank();
	
	XCTAssertTrue(tank1.armorRepair > tank0.armorRepair);
	XCTAssertTrue(tank1.shieldRepair > tank0.shieldRepair);
	XCTAssertTrue(tank1.hullRepair > tank0.hullRepair);
	
	auto gang2 = dgmpp::Gang::Create();
	auto pilot2 = gang2->add(dgmpp::Character::Create());
	pilot2->setSkillLevels(5);
	auto ship2 = pilot2->setShip(dgmpp::Ship::Create(TypeID::dominix));
	ship2->add(dgmpp::Module::Create(TypeID::largeArmorRepairerI));
	ship2->add(dgmpp::Module::Create(TypeID::largeShieldBoosterI));
	ship2->add(dgmpp::Module::Create(TypeID::largeHullRepairerI));
	auto tank2 = ship2->tank();
	
	XCTAssertTrue(tank1.armorRepair == tank2.armorRepair * 1s);
	XCTAssertTrue(tank1.shieldRepair == tank2.shieldRepair * 1s);
	XCTAssertTrue(tank1.hullRepair == tank2.hullRepair * 1s);
}

- (void) testRemoteRepairers {
	using namespace dgmpp;
	auto engine = createEngine();
	auto gang = engine->getGang();
	auto pilotA = gang->addPilot();
	auto pilotB = gang->addPilot();
	pilotA->setAllSkillsLevel(5);
	pilotB->setAllSkillsLevel(5);
	
	auto shipA = pilotA->setShip(TypeID::dominix);
	auto shipB = pilotB->setShip(TypeID::dominix);
	
	auto repairers = {shipA->addModule(TypeID::largeRemoteArmorRepairerI), shipA->addModule(TypeID::largeRemoteShieldBoosterI), shipA->addModule(TypeID::largeRemoteHullRepairerI)};
	
	auto tank0 = shipB->getTank();
	
	for (auto i: repairers)
		i->setTarget(shipB);
	auto tank1 = shipB->getTank();

	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank1.shieldRepair, tank0.shieldRepair);
	XCTAssertGreaterThan(tank1.hullRepair, tank0.hullRepair);
	
	auto gang2 = dgmpp::Gang::Create();
	auto pilotA2 = gang2->add(dgmpp::Character::Create());
	auto pilotB2 = gang2->add(dgmpp::Character::Create());
	pilotA2->setSkillLevels(5);
	pilotB2->setSkillLevels(5);
	auto shipA2 = pilotA2->setShip(dgmpp::Ship::Create(TypeID::dominix));
	auto shipB2 = pilotB2->setShip(dgmpp::Ship::Create(TypeID::dominix));
	auto repairers2 = {
		shipA2->add(dgmpp::Module::Create(TypeID::largeRemoteArmorRepairerI)),
		shipA2->add(dgmpp::Module::Create(TypeID::largeRemoteShieldBoosterI)),
		shipA2->add(dgmpp::Module::Create(TypeID::largeRemoteHullRepairerI))};
	
	for (auto i: repairers2)
		i->target(shipB2);
	
	auto tank2 = shipB2->tank();

	for (auto i: repairers2)
		shipA2->remove(i);
	
	auto tank3 = shipB2->tank();

	XCTAssertTrue(tank1.armorRepair == tank2.armorRepair * 1s);
	XCTAssertTrue(tank1.shieldRepair == tank2.shieldRepair * 1s);
	XCTAssertTrue(tank1.hullRepair == tank2.hullRepair * 1s);
	XCTAssertEqual(tank3.armorRepair * 1s + tank3.shieldRepair * 1s + tank3.hullRepair * 1s, 0);

}

- (void) testAncillaries {
	using namespace dgmpp;
	auto engine = createEngine();
	auto gang = engine->getGang();
	auto pilot = gang->addPilot();
	pilot->setAllSkillsLevel(5);
	
	auto ship = pilot->setShip(TypeID::dominix);
	auto tank0 = ship->getTank();
	auto repairer = ship->addModule(TypeID::largeAncillaryArmorRepairer);
	auto tank1 = ship->getTank();
	repairer->setCharge(TypeID::naniteRepairPaste);
	auto tank2 = ship->getTank();

	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank2.armorRepair, tank1.armorRepair);
	
	ship->removeModule(repairer);
	auto capUsed0 = ship->getCapUsed();
	auto booster = ship->addModule(TypeID::largeAncillaryShieldBooster);
	auto capUsed1 = ship->getCapUsed();
	auto charge = booster->setCharge(TypeID::capBooster200);
	XCTAssertNotEqual(charge, nullptr);
	auto capUsed2 = ship->getCapUsed();

	XCTAssertGreaterThan(capUsed1, capUsed0);
	XCTAssertGreaterThan(capUsed1, capUsed2);
	
	auto gang2 = dgmpp::Gang::Create();
	auto pilot2 = gang2->add(dgmpp::Character::Create());
	pilot2->setSkillLevels(5);
	auto ship2 = pilot2->setShip(dgmpp::Ship::Create(TypeID::dominix));
	auto repairer2 = ship2->add(dgmpp::Module::Create(TypeID::largeAncillaryArmorRepairer));
	repairer2->charge(dgmpp::Charge::Create(TypeID::naniteRepairPaste));
	auto tank3 = ship2->tank();
	auto capUsed3 = ship2->capacitor().use();
	XCTAssertTrue(tank2.armorRepair == tank3.armorRepair * 1s);
	XCTAssertTrue(tank2.shieldRepair == tank3.shieldRepair * 1s);
	XCTAssertTrue(tank2.hullRepair == tank3.hullRepair * 1s);
//	XCTAssertTrue(capUsed2 == capUsed3 * 1s);
	
}

- (void) testEnergyDrainers {
	using namespace dgmpp;
	auto engine = createEngine();
	auto gang = engine->getGang();
	auto pilotA = gang->addPilot();
	auto pilotB = gang->addPilot();
	pilotA->setAllSkillsLevel(5);
	pilotB->setAllSkillsLevel(5);
	
	auto shipA = pilotA->setShip(TypeID::dominix);
	auto shipB = pilotB->setShip(TypeID::dominix);

	Float capUsed0[] = {shipA->getCapUsed(), shipB->getCapUsed(), shipA->getCapRecharge(), shipB->getCapRecharge()};
	shipA->addModule(TypeID::heavyEnergyNeutralizerI)->setTarget(shipB);
	Float capUsed1[] = {shipA->getCapUsed(), shipB->getCapUsed(), shipA->getCapRecharge(), shipB->getCapRecharge()};
	shipA->addModule(TypeID::heavyEnergyNosferatuI)->setTarget(shipB);
	Float capUsed2[] = {shipA->getCapUsed(), shipB->getCapUsed(), shipA->getCapRecharge(), shipB->getCapRecharge()};
	
	XCTAssertGreaterThan(capUsed1[0], capUsed0[0]);
	XCTAssertEqual(capUsed1[2], capUsed0[2]);
	XCTAssertGreaterThan(capUsed2[2], capUsed1[2]);
	XCTAssertEqual(capUsed2[0], capUsed1[0]);
	
	XCTAssertGreaterThan(capUsed1[1], capUsed0[1]);
	XCTAssertGreaterThan(capUsed2[1], capUsed1[1]);
	
	shipA->addModule(TypeID::largeRemoteCapacitorTransmitterI)->setTarget(shipB);
	Float capUsed3[] = {shipA->getCapUsed(), shipB->getCapUsed(), shipA->getCapRecharge(), shipB->getCapRecharge()};

	XCTAssertGreaterThan(capUsed3[0], capUsed2[0]);
	XCTAssertGreaterThan(capUsed3[3], capUsed2[3]);
}

- (void) testDrones {
	using namespace dgmpp;
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->setShip(Ship::Create(TypeID::dominix));
	
	auto dps0 = ship->dronesDPS() * 1s;
	for (int i = 0; i < 5; i++)
		ship->add(Drone::Create(TypeID::ogreII));
	auto dps1 = ship->dronesDPS() * 1s;
	
	for (const auto& i: ship->drones())
		ship->remove(i);
	
	auto dps2 = ship->dronesDPS() * 1s;

	XCTAssertGreaterThan(dps1.total(), dps0.total());
	XCTAssertEqual(dps2.total(), dps0.total());
	
}

- (void) testArea {
	using namespace dgmpp;
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->setShip(Ship::Create(TypeID::dominix));
	
	auto ehp0 = ship->effectiveHitPoints();
	ship->area(Area::Create(TypeID::wolfRayetEffectBeaconClass6));
	auto ehp1 = ship->effectiveHitPoints();
	ship->area(nullptr);
	auto ehp2 = ship->effectiveHitPoints();
	
	XCTAssertGreaterThan(ehp1.total(), ehp0.total());
	XCTAssertEqual(ehp2.total(), ehp0.total());

}

- (void)testShips {
	using namespace dgmpp;
	return;
	
	[self measureBlock:^{
		auto typeIDs = {1912,
		1914,
		1916,
		1918,
		4005,
		33623,
		33625,
		33627,
		33629,
		33631,
		33633,
		33635,
		33637,
		34118,
		34151,
		34213,
		34215,
		34217,
		34225,
		34227,
		34229,
		34237,
		34239,
		34247,
		34249,
		34251,
		34441,
		34457,
		34459,
		34461,
		34463,
		34465,
		34467,
		34469,
		34471,
		638,
		639,
		640,
		641,
		642,
		643,
		644,
		645,
		11936,
		11938,
		13202,
		17636,
		17726,
		17728,
		17732,
		17736,
		17738,
		17740,
		17918,
		17920,
		24688,
		24690,
		24692,
		24694,
		26840,
		26842,
		32305,
		32307,
		32309,
		32311,
		33472,
			33820};
		
		
		{
/*//			auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT typeID FROM invTypes where groupID in (select groupID from invGroups where categoryID=6) LIMIT 100");
//			auto result = engine->getSqlConnector()->exec(stmt);
//			while (result->next()) {
//			}*/

//			for (auto typeID: typeIDs) {
//				auto engine = createEngine();
//				auto gang = engine->getGang();
//				auto pilot = gang->addPilot();
//				pilot->setAllSkillsLevel(5);
//				auto ship = pilot->setShip(static_cast<TypeID>(typeID));
//				ship->getVelocity();
////				gang->removePilot(pilot);
//			}
			
		}
		
		{
			for (auto typeID: typeIDs) {
				auto gang = dgmpp::Gang::Create();
				auto pilot = gang->add(dgmpp::Character::Create());
				pilot->setSkillLevels(5);
				auto ship = pilot->setShip(dgmpp::Ship::Create(static_cast<TypeID>(typeID)));
				(*ship)[dgmpp::AttributeID::maxVelocity]->value();
			}
		}

	}];
}

@end
