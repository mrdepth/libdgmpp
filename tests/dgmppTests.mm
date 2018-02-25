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
	gang->area(Area::Create(TypeID::wolfRayetEffectBeaconClass6));
	auto ehp1 = ship->effectiveHitPoints();
	gang->area(nullptr);
	auto ehp2 = ship->effectiveHitPoints();
	
	XCTAssertGreaterThan(ehp1.total(), ehp0.total());
	XCTAssertEqual(ehp2.total(), ehp0.total());

}

- (void) testCopy {
	auto gang = Gang::Create();
	auto pilotA = gang->addPilot();
	auto pilotB = gang->addPilot();
	pilotA->setSkillLevels(5);
	pilotB->setSkillLevels(5);
	
	auto shipA = pilotA->ship(TypeID::dominix);
	auto shipB = pilotB->ship(TypeID::dominix);
	
	shipA->addModule(TypeID::heavyEnergyNeutralizerI)->target(shipB);
	GigaJoulePerSecond capUsed0[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};
	
	auto gangB = Gang::Create(*gang);
	auto shipA2 = gangB->pilots()[0]->ship();
	auto shipB2 = gangB->pilots()[1]->ship();
	GigaJoulePerSecond capUsed1[] = {shipA2->capacitor().use(), shipB2->capacitor().use(), shipA2->capacitor().recharge(), shipB2->capacitor().recharge()};
	
	for (auto i = 0; i < 3; i++)
		XCTAssertEqual(capUsed0[i], capUsed1[i]);
}

- (void) testDisallows {
	auto gang = Gang::Create();
	auto pilotA = gang->addPilot();
	auto pilotB = gang->addPilot();
	auto pilotC = gang->addPilot();
	pilotA->setSkillLevels(5);
	pilotB->setSkillLevels(5);
	pilotC->setSkillLevels(5);
	
	auto shipA = pilotA->ship(TypeID::kronos);
	auto shipB = pilotB->ship(TypeID::dominix);
	auto shipC = pilotC->ship(TypeID::erebus);
	
	auto capUse0 = shipA->capacitor().use();
	auto tankA0 = shipA->tank();
	auto tankC0 = shipC->tank();
	
	shipB->addModule(TypeID::heavyEnergyNeutralizerI)->target(shipA);
	shipB->addModule(TypeID::largeRemoteArmorRepairerI)->target(shipA);
	shipB->addModule(TypeID::largeRemoteArmorRepairerI)->target(shipC);
	
	auto capUse1 = shipA->capacitor().use();
	auto tankA1 = shipA->tank();
	auto tankC1 = shipC->tank();
	
	auto bastion = shipA->addModule(TypeID::bastionModuleI);
	shipC->addModule(TypeID::jumpPortalGeneratorI);

	auto capUse2 = shipA->capacitor().use();
	auto tankA2 = shipA->tank();
	auto tankC2 = shipC->tank();

	XCTAssertGreaterThan(capUse1, capUse0);
	XCTAssertGreaterThan(tankA1.armorRepair, tankA0.armorRepair);
	XCTAssertGreaterThan(tankC1.armorRepair, tankC0.armorRepair);
	
	XCTAssertEqual(capUse2, bastion->capUse());
	XCTAssertEqual(tankA2.armorRepair, tankA1.armorRepair);
	XCTAssertEqual(tankC2.armorRepair, tankC0.armorRepair);
}
	
- (void) testKamikaze {
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(Ship::Create(TypeID::nyx));
	
	auto volley0 = ship->dronesVolley();
	
	for (int i = 0; i < 6 * 3; i++)
		ship->add(Drone::Create(TypeID::shadow));
	
	auto volley1 = ship->dronesVolley();
	
	for (auto drone: ship->drones()) {
		XCTAssertTrue(drone->hasKamikazeAbility());
		drone->kamikaze(true);
	}
	
	auto volley2 = ship->dronesVolley();
	
	XCTAssertGreaterThan(volley1.total(), volley0.total());
	XCTAssertGreaterThan(volley2.total(), volley1.total());
}

- (void) testCapBooster {
	auto gang = Gang::Create();
	auto pilot = gang->add(Character::Create());
	pilot->setSkillLevels(5);
	auto ship = pilot->ship(Ship::Create(TypeID::loki));
	
	ship->addModule(TypeID::lokiCoreImmobilityDrivers);
	ship->addModule(TypeID::lokiDefensiveCovertReconfiguration);
	ship->addModule(TypeID::lokiOffensiveProjectileScopingArray);
	ship->addModule(TypeID::lokiPropulsionWakeLimiter);
	
	ship->addModule(TypeID::gyrostabilizerII);
	ship->addModule(TypeID::gyrostabilizerII);

	ship->addModule(TypeID::adaptiveInvulnerabilityFieldII);
	ship->addModule(TypeID::pithXTypeLargeShieldBooster);
	ship->addModule(TypeID::_100MNYS8CompactAfterburner);
	auto capBooster = ship->addModule(TypeID::ammatarNavyMediumCapacitorBooster);
	capBooster->charge(TypeID::navyCapBooster800);
	ship->addModule(TypeID::caldariNavyStasisWebifier);
	ship->addModule(TypeID::caldariNavyWarpDisruptor);
	ship->addModule(TypeID::caldariNavyStasisWebifier);
	
	for (int i = 0; i < 5; i++)
		ship->addModule(TypeID::_425mmAutoCannonII)->charge(TypeID::republicFleetEMPM);
	
	auto lasts0 = ship->capacitor().lastsTime().count();
	capBooster->state(Module::State::offline);
	auto lasts1 = ship->capacitor().lastsTime().count();
	XCTAssertGreaterThan(lasts0, lasts1);
}

- (void) testStructure {
	auto structure = Structure::Create(TypeID::astrahus);
	auto hi0 = structure->freeSlots(Module::Slot::hi);
	auto med0 = structure->freeSlots(Module::Slot::med);
	auto low0 = structure->freeSlots(Module::Slot::low);
	auto pg0 = structure->usedPowerGrid();
	auto cpu0 = structure->usedCPU();
	structure->add(Module::Create(TypeID::standupXLEnergyNeutralizerII));
	structure->add(Module::Create(TypeID::standupCapBatteryII));
	structure->add(Module::Create(TypeID::standupCapacitorPowerRelayII));
	
	auto hi1 = structure->freeSlots(Module::Slot::hi);
	auto med1 = structure->freeSlots(Module::Slot::med);
	auto low1 = structure->freeSlots(Module::Slot::low);
	auto pg1 = structure->usedPowerGrid();
	auto cpu1 = structure->usedCPU();

	XCTAssertEqual(hi0, hi1 + 1);
	XCTAssertEqual(med0, med1 + 1);
	XCTAssertEqual(low0, low1 + 1);
	XCTAssertLessThan(pg0, pg1);
	XCTAssertLessThan(cpu0, cpu1);
}


@end
