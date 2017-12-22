//
//  dgmppTests.m
//  dgmppTests
//
//  Created by Артем Шиманский on 02.05.16.
//
//

#import <XCTest/XCTest.h>
#import "dgmpp.hpp"
#include <memory>

using namespace std::chrono_literals;
using namespace dgmpp;

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

- (void) testSlots {
	auto gang = Gang();
	auto pilot = gang.addPilot();
	auto ship = pilot->ship(TypeID::dominix);
	auto hi0 = ship->freeSlots(Module::Slot::hi);
	auto med0 = ship->freeSlots(Module::Slot::med);
	auto low0 = ship->freeSlots(Module::Slot::low);
	auto turrets0 = ship->freeHardpoints(Module::Hardpoint::turret);
	
	auto module = ship->addModule(TypeID::ionBlasterCannonII);
	
	auto hi1 = ship->freeSlots(Module::Slot::hi);
	auto med1 = ship->freeSlots(Module::Slot::med);
	auto low1 = ship->freeSlots(Module::Slot::low);
	auto turrets1 = ship->freeHardpoints(Module::Hardpoint::turret);
	
	ship->remove(module);

	auto hi2 = ship->freeSlots(Module::Slot::hi);
	auto med2 = ship->freeSlots(Module::Slot::med);
	auto low2 = ship->freeSlots(Module::Slot::low);
	auto turrets2 = ship->freeHardpoints(Module::Hardpoint::turret);

	XCTAssertEqual(hi0, hi1 + 1);
	XCTAssertEqual(med0, med1);
	XCTAssertEqual(low0, low1);
	XCTAssertEqual(turrets0, turrets1 + 1);
	
	XCTAssertEqual(hi0, hi2);
	XCTAssertEqual(med0, med2);
	XCTAssertEqual(low0, low2);
	XCTAssertEqual(turrets0, turrets2);

	auto launchers0 = ship->freeHardpoints(Module::Hardpoint::launcher);
	ship->addModule(TypeID::lightMissileLauncherII);
	auto launchers1 = ship->freeHardpoints(Module::Hardpoint::launcher);
	XCTAssertEqual(launchers0, launchers1 + 1);

}

- (void) testSkills {
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	auto ship = pilot->ship(Ship::Create(TypeID::dominix));
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
	auto gang = Gang::Create();
	auto pilotA = gang->add(Character::Create());
	pilotA->setSkillLevels(5);
	auto shipA = pilotA->ship(Ship::Create(TypeID::dominix));
	shipA->add(Module::Create(TypeID::largeArmorRepairerI));
	
	auto ehp0 = shipA->effectiveHitPoints();

	auto pilotB = gang->add(Character::Create());
	pilotB->setSkillLevels(5);
	auto shipB = pilotB->ship(Ship::Create(TypeID::erebus));
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
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);

	auto ship = pilot->ship(TypeID::dominix);
	auto tank0 = ship->tank();
	XCTAssertNotEqual(ship->addModule(TypeID::largeArmorRepairerI), nullptr);
	XCTAssertNotEqual(ship->addModule(TypeID::largeShieldBoosterI), nullptr);
	XCTAssertNotEqual(ship->addModule(TypeID::largeHullRepairerI), nullptr);
	auto tank1 = ship->tank();
	
	XCTAssertTrue(tank1.armorRepair > tank0.armorRepair);
	XCTAssertTrue(tank1.shieldRepair > tank0.shieldRepair);
	XCTAssertTrue(tank1.hullRepair > tank0.hullRepair);
	
}

- (void) testRemoteRepairers {
	auto gang = Gang::Create();
	auto pilotA = gang->addPilot();
	auto pilotB = gang->addPilot();
	pilotA->setSkillLevels(5);
	pilotB->setSkillLevels(5);
	
	auto shipA = pilotA->ship(TypeID::dominix);
	auto shipB = pilotB->ship(TypeID::dominix);
	
	auto repairers = {shipA->addModule(TypeID::largeRemoteArmorRepairerI), shipA->addModule(TypeID::largeRemoteShieldBoosterI), shipA->addModule(TypeID::largeRemoteHullRepairerI)};
	
	auto tank0 = shipB->tank();
	
	for (auto i: repairers)
		i->target(shipB);
	auto tank1 = shipB->tank();

	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank1.shieldRepair, tank0.shieldRepair);
	XCTAssertGreaterThan(tank1.hullRepair, tank0.hullRepair);
}

- (void) testAncillaries {
	auto gang = Gang::Create();
	auto pilot = gang->addPilot();
	pilot->setSkillLevels(5);
	
	auto ship = pilot->ship(TypeID::dominix);
	auto tank0 = ship->tank();
	auto repairer = ship->addModule(TypeID::largeAncillaryArmorRepairer);
	auto tank1 = ship->tank();
	repairer->charge(TypeID::naniteRepairPaste);
	auto tank2 = ship->tank();

	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank2.armorRepair, tank1.armorRepair);
	
	ship->remove(repairer);
	auto capUsed0 = ship->capacitor().use();
	auto booster = ship->addModule(TypeID::largeAncillaryShieldBooster);
	auto capUsed1 = ship->capacitor().use();
	auto charge = booster->charge(TypeID::capBooster200);
	XCTAssertNotEqual(charge, nullptr);
	auto capUsed2 = ship->capacitor().use();

	XCTAssertGreaterThan(capUsed1, capUsed0);
	XCTAssertGreaterThan(capUsed1, capUsed2);
	
}

- (void) testEnergyDrainers {
	auto gang = Gang::Create();
	auto pilotA = gang->addPilot();
	auto pilotB = gang->addPilot();
	pilotA->setSkillLevels(5);
	pilotB->setSkillLevels(5);
	
	auto shipA = pilotA->ship(TypeID::dominix);
	auto shipB = pilotB->ship(TypeID::dominix);

	GigaJoulePerSecond capUsed0[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};
	shipA->addModule(TypeID::heavyEnergyNeutralizerI)->target(shipB);
	GigaJoulePerSecond capUsed1[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};
	shipA->addModule(TypeID::heavyEnergyNosferatuI)->target(shipB);
	GigaJoulePerSecond capUsed2[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};

	XCTAssertGreaterThan(capUsed1[0], capUsed0[0]);
	XCTAssertEqual(capUsed1[2], capUsed0[2]);
	XCTAssertGreaterThan(capUsed2[2], capUsed1[2]);
	XCTAssertEqual(capUsed2[0], capUsed1[0]);
	
	XCTAssertGreaterThan(capUsed1[1], capUsed0[1]);
	XCTAssertGreaterThan(capUsed2[1], capUsed1[1]);
	
	shipA->addModule(TypeID::largeRemoteCapacitorTransmitterI)->target(shipB);
	GigaJoulePerSecond capUsed3[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};

	XCTAssertGreaterThan(capUsed3[0], capUsed2[0]);
	XCTAssertGreaterThan(capUsed3[3], capUsed2[3]);
}

- (void) testDrones {
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(Ship::Create(TypeID::dominix));
	
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
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(Ship::Create(TypeID::dominix));
	
	auto ehp0 = ship->effectiveHitPoints();
	ship->area(Area::Create(TypeID::wolfRayetEffectBeaconClass6));
	auto ehp1 = ship->effectiveHitPoints();
	ship->area(nullptr);
	auto ehp2 = ship->effectiveHitPoints();
	
	XCTAssertGreaterThan(ehp1.total(), ehp0.total());
	XCTAssertEqual(ehp2.total(), ehp0.total());

}

- (void)testShips {
}

@end
