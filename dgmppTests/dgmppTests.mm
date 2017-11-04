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

using namespace dgmpp;

std::shared_ptr<Engine> createEngine() {
	return std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
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

- (void) testRepairers {
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
}

- (void) testRemoteRepairers {
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
	
}

- (void) testAncillaries {
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
}

- (void) testEnergyDrainers {
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

- (void)testShips {
	[self measureBlock:^{
		
		auto engine = createEngine();
		auto gang = engine->getGang();
		auto pilot = gang->addPilot();
		pilot->setAllSkillsLevel(5);
		
		auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT typeID FROM invTypes where groupID in (select groupID from invGroups where categoryID=6)");
		auto result = engine->getSqlConnector()->exec(stmt);
		while (result->next()) {
			TypeID typeID = static_cast<TypeID>(result->getInt(0));
			auto ship = pilot->setShip(typeID);
			ship->getCapUsed();
			ship->getEffectiveSustainableTank();
			ship->getHitPoints();
			ship->getWeaponDps();
			ship->getDrones();
		}
	}];
}

@end
