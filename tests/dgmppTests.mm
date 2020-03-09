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
#include <iterator>

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
    auto pilot = std::make_shared<Character>();
	gang.add(pilot);
    auto ship = std::make_shared<Ship>(TypeID::dominix);
	pilot->ship(ship);
    
	auto hi0 = ship->freeSlots(Module::Slot::hi);
	auto med0 = ship->freeSlots(Module::Slot::med);
	auto low0 = ship->freeSlots(Module::Slot::low);
	auto turrets0 = ship->freeHardpoints(Module::Hardpoint::turret);
	
    auto module = std::make_shared<Module>(TypeID::ionBlasterCannonII);
	ship->add(module);
	
	auto hi1 = ship->freeSlots(Module::Slot::hi);
	auto med1 = ship->freeSlots(Module::Slot::med);
	auto low1 = ship->freeSlots(Module::Slot::low);
	auto turrets1 = ship->freeHardpoints(Module::Hardpoint::turret);
	
	ship->remove(module.get());

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

//	auto launchers0 = ship->freeHardpoints(Module::Hardpoint::launcher);
//	ship->addModule(TypeID::lightMissileLauncherII);
//	auto launchers1 = ship->freeHardpoints(Module::Hardpoint::launcher);
//	XCTAssertEqual(launchers0, launchers1 + 1);

}

- (void) testSkills {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    auto ship = std::make_shared<Ship>(TypeID::dominix);
    pilot->ship(ship);
    ship->add(std::make_shared<Module>(TypeID::largeArmorRepairerI));
	
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
    auto gang = Gang();
    auto pilotA = std::make_shared<Character>();
    gang.add(pilotA);
	pilotA->setSkillLevels(5);
    auto shipA = std::make_shared<Ship>(TypeID::dominix);
	pilotA->ship(shipA);
    shipA->add(std::make_shared<Module>(TypeID::largeArmorRepairerI));
	
	auto ehp0 = shipA->effectiveHitPoints();

    auto pilotB = std::make_shared<Character>();
    gang.add(pilotB);
	pilotB->setSkillLevels(5);
    auto shipB = std::make_shared<Ship>(TypeID::erebus);
    pilotB->ship(shipB);
    shipB->add(std::make_shared<Module>(TypeID::gallentePhenomenaGenerator));
	
	auto ehp1 = shipA->effectiveHitPoints();
	
    auto burst = std::make_shared<Module>(TypeID::shieldCommandBurstI);
	shipB->add(burst);
	burst->charge(std::make_shared<Charge>(TypeID::shieldHarmonizingCharge));
	
	auto ehp2 = shipA->effectiveHitPoints();
	burst->charge(nullptr);
	auto ehp3 = shipA->effectiveHitPoints();
	
	XCTAssertGreaterThan(ehp1.total(), ehp0.total());
	XCTAssertGreaterThan(ehp2.total(), ehp1.total());
	XCTAssertEqual(ehp3.total(), ehp1.total());

}


- (void) testRepairers {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
	pilot->setSkillLevels(5);

    auto ship = std::make_shared<Ship>(TypeID::dominix);
    pilot->ship(ship);
	auto tank0 = ship->tank();
    ship->add(std::make_shared<Module>(TypeID::largeArmorRepairerI));
    ship->add(std::make_shared<Module>(TypeID::largeShieldBoosterI));
    ship->add(std::make_shared<Module>(TypeID::largeHullRepairerI));
	auto tank1 = ship->tank();
	
	XCTAssertTrue(tank1.armorRepair > tank0.armorRepair);
	XCTAssertTrue(tank1.shieldRepair > tank0.shieldRepair);
	XCTAssertTrue(tank1.hullRepair > tank0.hullRepair);
	
}

- (void) testRemoteRepairers {
    auto gang = Gang();
    auto pilotA = std::make_shared<Character>();
    auto pilotB = std::make_shared<Character>();
	gang.add(pilotA);
	gang.add(pilotB);
	pilotA->setSkillLevels(5);
	pilotB->setSkillLevels(5);
	
    auto shipA = std::make_shared<Ship>(TypeID::dominix);
    auto shipB = std::make_shared<Ship>(TypeID::dominix);
	pilotA->ship(shipA);
	pilotB->ship(shipB);
	
	auto repairers = {std::make_shared<Module>(TypeID::largeRemoteArmorRepairerI), std::make_shared<Module>(TypeID::largeRemoteShieldBoosterI), std::make_shared<Module>(TypeID::largeRemoteHullRepairerI)};
    for (auto i: repairers)
        shipA->add(i);
	
	auto tank0 = shipB->tank();
	
	for (auto i: repairers)
		i->target(shipB);
	auto tank1 = shipB->tank();

	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank1.shieldRepair, tank0.shieldRepair);
	XCTAssertGreaterThan(tank1.hullRepair, tank0.hullRepair);
}

- (void) testAncillaries {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
	pilot->setSkillLevels(5);
	
    auto ship = std::make_shared<Ship>(TypeID::dominix);
    pilot->ship(ship);
	auto tank0 = ship->tank();
    auto repairer = std::make_shared<Module>(TypeID::largeAncillaryArmorRepairer);
	ship->add(repairer);
    
	auto tank1 = ship->tank();
	repairer->charge(std::make_shared<Charge>(TypeID::naniteRepairPaste));
	auto tank2 = ship->tank();

	XCTAssertGreaterThan(tank1.armorRepair, tank0.armorRepair);
	XCTAssertGreaterThan(tank2.armorRepair, tank1.armorRepair);
	
	ship->remove(repairer.get());
	auto capUsed0 = ship->capacitor().use();
    auto booster = std::make_shared<Module>(TypeID::largeAncillaryShieldBooster);
	ship->add(booster);
	auto capUsed1 = ship->capacitor().use();
	booster->charge(std::make_shared<Charge>(TypeID::capBooster200));
	auto capUsed2 = ship->capacitor().use();

	XCTAssertGreaterThan(capUsed1, capUsed0);
	XCTAssertGreaterThan(capUsed1, capUsed2);
	
}

- (void) testEnergyDrainers {
    auto gang = Gang();
    auto pilotA = std::make_shared<Character>();
    auto pilotB = std::make_shared<Character>();
    gang.add(pilotA);
    gang.add(pilotB);
	pilotA->setSkillLevels(5);
	pilotB->setSkillLevels(5);
	
    auto shipA = std::make_shared<Ship>(TypeID::dominix);
    auto shipB = std::make_shared<Ship>(TypeID::dominix);
    pilotA->ship(shipA);
    pilotB->ship(shipB);

	GigaJoulePerSecond capUsed0[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};
    auto moduleA = std::make_shared<Module>(TypeID::heavyEnergyNeutralizerI);
    shipA->add(moduleA);
    moduleA->target(shipB);
    
	GigaJoulePerSecond capUsed1[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};
    
    auto moduleB = std::make_shared<Module>(TypeID::heavyEnergyNosferatuI);
    shipA->add(moduleB);
    moduleB->target(shipB);

	GigaJoulePerSecond capUsed2[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};

	XCTAssertGreaterThan(capUsed1[0], capUsed0[0]);
	XCTAssertEqual(capUsed1[2], capUsed0[2]);
	XCTAssertGreaterThan(capUsed2[2], capUsed1[2]);
	XCTAssertEqual(capUsed2[0], capUsed1[0]);
	
	XCTAssertGreaterThan(capUsed1[1], capUsed0[1]);
	XCTAssertGreaterThan(capUsed2[1], capUsed1[1]);
	
    auto moduleC = std::make_shared<Module>(TypeID::largeRemoteCapacitorTransmitterI);
    shipA->add(moduleC);
    moduleC->target(shipB);
	GigaJoulePerSecond capUsed3[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};

	XCTAssertGreaterThan(capUsed3[0], capUsed2[0]);
	XCTAssertGreaterThan(capUsed3[3], capUsed2[3]);
}

- (void) testDrones {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::dominix);
    pilot->ship(ship);

	auto dps0 = ship->dronesDPS() * 1s;
	for (int i = 0; i < 5; i++)
		ship->add(std::make_shared<Drone>(TypeID::ogreII));
	auto dps1 = ship->dronesDPS() * 1s;
	
	for (const auto& i: ship->drones())
		ship->remove(i.get());
	
	auto dps2 = ship->dronesDPS() * 1s;

	XCTAssertGreaterThan(dps1.total(), dps0.total());
	XCTAssertEqual(dps2.total(), dps0.total());
	XCTAssertEqualWithAccuracy(dps1.total(), 475, 0.5);
}

- (void) testArea {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::dominix);
    pilot->ship(ship);

	auto ehp0 = ship->effectiveHitPoints();
	gang.area(std::make_shared<Area>(TypeID::wolfRayetEffectBeaconClass6));
	auto ehp1 = ship->effectiveHitPoints();
	gang.area(nullptr);
	auto ehp2 = ship->effectiveHitPoints();
	
	XCTAssertGreaterThan(ehp1.total(), ehp0.total());
	XCTAssertEqual(ehp2.total(), ehp0.total());

}

- (void) testCopy {
    auto gang = Gang();
    auto pilotA = std::make_shared<Character>();
    auto pilotB = std::make_shared<Character>();
    gang.add(pilotA);
    gang.add(pilotB);
    pilotA->setSkillLevels(5);
    pilotB->setSkillLevels(5);
    
    auto shipA = std::make_shared<Ship>(TypeID::dominix);
    auto shipB = std::make_shared<Ship>(TypeID::dominix);
    pilotA->ship(shipA);
    pilotB->ship(shipB);

    auto module = std::make_shared<Module>(TypeID::heavyEnergyNeutralizerI);
	shipA->add(module);
    module->target(shipB);
	GigaJoulePerSecond capUsed0[] = {shipA->capacitor().use(), shipB->capacitor().use(), shipA->capacitor().recharge(), shipB->capacitor().recharge()};
	
	auto gangB = Gang(gang);
    auto pilots = gangB.pilots();
    auto i = pilots.begin();
	auto shipA2 = (*i)->ship();
    i = std::next(i);
	auto shipB2 = (*i)->ship();
	GigaJoulePerSecond capUsed1[] = {shipA2->capacitor().use(), shipB2->capacitor().use(), shipA2->capacitor().recharge(), shipB2->capacitor().recharge()};
	
	for (auto i = 0; i < 3; i++)
		XCTAssertEqual(capUsed0[i], capUsed1[i]);
}

- (void) testDisallows {
    auto gang = Gang();
    auto pilotA = std::make_shared<Character>();
    auto pilotB = std::make_shared<Character>();
    auto pilotC = std::make_shared<Character>();
    gang.add(pilotA);
    gang.add(pilotB);
    gang.add(pilotC);
    pilotA->setSkillLevels(5);
    pilotB->setSkillLevels(5);
    pilotC->setSkillLevels(5);
    
    auto shipA = std::make_shared<Ship>(TypeID::kronos);
    auto shipB = std::make_shared<Ship>(TypeID::dominix);
    auto shipC = std::make_shared<Ship>(TypeID::erebus);
    pilotA->ship(shipA);
    pilotB->ship(shipB);
    pilotC->ship(shipC);

	auto capUse0 = shipA->capacitor().use();
	auto tankA0 = shipA->tank();
	auto tankC0 = shipC->tank();
	
    auto module1 = std::make_shared<Module>(TypeID::heavyEnergyNeutralizerI);
    auto module2 = std::make_shared<Module>(TypeID::largeRemoteArmorRepairerI);
    auto module3 = std::make_shared<Module>(TypeID::largeRemoteArmorRepairerI);
    
    shipB->add(module1);
    shipB->add(module2);
    shipB->add(module3);
    
	module1->target(shipA);
	module2->target(shipA);
	module3->target(shipC);
	
	auto capUse1 = shipA->capacitor().use();
	auto tankA1 = shipA->tank();
	auto tankC1 = shipC->tank();
	
    auto bastion = std::make_shared<Module>(TypeID::bastionModuleI);
	shipA->add(bastion);
	shipC->add(std::make_shared<Module>(TypeID::jumpPortalGeneratorI));

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
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::nyx);
    pilot->ship(ship);

	auto volley0 = ship->dronesVolley();
	
	for (int i = 0; i < 6 * 3; i++)
		ship->add(std::make_shared<Drone>(TypeID::shadow));
	
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
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::loki);
    pilot->ship(ship);
	
	ship->add(std::make_shared<Module>(TypeID::lokiCoreImmobilityDrivers));
	ship->add(std::make_shared<Module>(TypeID::lokiDefensiveCovertReconfiguration));
	ship->add(std::make_shared<Module>(TypeID::lokiOffensiveProjectileScopingArray));
	ship->add(std::make_shared<Module>(TypeID::lokiPropulsionWakeLimiter));
	
	ship->add(std::make_shared<Module>(TypeID::gyrostabilizerII));
	ship->add(std::make_shared<Module>(TypeID::gyrostabilizerII));

	ship->add(std::make_shared<Module>(TypeID::adaptiveInvulnerabilityFieldII));
	ship->add(std::make_shared<Module>(TypeID::pithXTypeLargeShieldBooster));
	ship->add(std::make_shared<Module>(TypeID::_100MNYS8CompactAfterburner));
	auto capBooster = std::make_shared<Module>(TypeID::ammatarNavyMediumCapacitorBooster);
    ship->add(capBooster);
	capBooster->charge(std::make_shared<Charge>(TypeID::navyCapBooster800));
	ship->add(std::make_shared<Module>(TypeID::caldariNavyStasisWebifier));
	ship->add(std::make_shared<Module>(TypeID::caldariNavyWarpDisruptor));
	ship->add(std::make_shared<Module>(TypeID::caldariNavyStasisWebifier));
	
    for (int i = 0; i < 5; i++) {
        auto module = std::make_shared<Module>(TypeID::_425mmAutoCannonII);
        ship->add(module);
        module->charge(std::make_shared<Charge>(TypeID::republicFleetEMPM));
    }
	
	auto lasts0 = ship->capacitor().lastsTime().count();
	capBooster->state(Module::State::offline);
	auto lasts1 = ship->capacitor().lastsTime().count();
	XCTAssertGreaterThan(lasts0, lasts1);
}

- (void) testStructure {
	auto structure = std::make_shared<Structure>(TypeID::astrahus);
	auto hi0 = structure->freeSlots(Module::Slot::hi);
	auto med0 = structure->freeSlots(Module::Slot::med);
	auto low0 = structure->freeSlots(Module::Slot::low);
	auto pg0 = structure->usedPowerGrid();
	auto cpu0 = structure->usedCPU();
	auto ehp0 = structure->effectiveHitPoints();

	structure->add(std::make_shared<Module>(TypeID::standupXLEnergyNeutralizerII));
	structure->add(std::make_shared<Module>(TypeID::standupCapBatteryII));
	structure->add(std::make_shared<Module>(TypeID::standupCapacitorPowerRelayII));
	structure->add(std::make_shared<Module>(TypeID::standupHyasyodaResearchLab));
	structure->add(std::make_shared<Module>(TypeID::standupLayeredArmorPlatingI));

	auto hi1 = structure->freeSlots(Module::Slot::hi);
	auto med1 = structure->freeSlots(Module::Slot::med);
	auto low1 = structure->freeSlots(Module::Slot::low);
	auto pg1 = structure->usedPowerGrid();
	auto cpu1 = structure->usedCPU();
	auto ehp1 = structure->effectiveHitPoints();

	XCTAssertEqual(hi0, hi1 + 1);
	XCTAssertEqual(med0, med1 + 1);
	XCTAssertEqual(low0, low1 + 2);
	XCTAssertLessThan(pg0, pg1);
	XCTAssertLessThan(cpu0, cpu1);
	XCTAssertLessThan(ehp0.armor, ehp1.armor);
}

- (void) testVindicator1 {
	auto gang = std::make_shared<Gang>();
    auto pilot = std::make_shared<Character>();
	gang->add(pilot);
	pilot->setSkillLevels(5);

	auto skills = pilot->skills();
	(*std::find_if(skills.begin(), skills.end(), [](auto i) { return i->metaInfo().typeID == TypeID::armorRigging; }))->level(4);

	(*std::find_if(skills.begin(), skills.end(), [](auto i) { return i->metaInfo().typeID == TypeID::largeBlasterSpecialization; }))->level(4);

    auto ship = std::make_shared<Ship>(TypeID::vindicator);
	pilot->ship(ship);
	
	ship->add(std::make_shared<Module>(TypeID::expandedCargoholdII));
	ship->add(std::make_shared<Module>(TypeID::expandedCargoholdI));
	ship->add(std::make_shared<Module>(TypeID::overdriveInjectorSystemI));
	ship->add(std::make_shared<Module>(TypeID::overdriveInjectorSystemII));
	ship->add(std::make_shared<Module>(TypeID::largeAntiKineticPumpI));
	ship->add(std::make_shared<Module>(TypeID::largeAntiThermalPumpII));
	ship->add(std::make_shared<Module>(TypeID::_500MNMicrowarpdriveII));
	ship->add(std::make_shared<Module>(TypeID::magneticFieldStabilizerI));
	ship->add(std::make_shared<Module>(TypeID::magneticFieldStabilizerII));
	ship->add(std::make_shared<Module>(TypeID::magneticFieldStabilizerII));
	auto res0 = ship->resistances();
	ship->add(std::make_shared<Module>(TypeID::largeAntiExplosivePumpII));
	auto res1 = ship->resistances();
    for (int i = 0; i < 3; i++) {
        auto module = std::make_shared<Module>(TypeID::neutronBlasterCannonII);
        ship->add(module);
        module->charge(std::make_shared<Charge>(TypeID::nullL));
    }
	auto dps = ship->turretsDPS() * 1s;
	
	XCTAssertLessThan(res0.armor.explosive, res1.armor.explosive);
	XCTAssertEqualWithAccuracy(ship->velocity() * 1s, 890.1, 0.05);
	XCTAssertEqualWithAccuracy(dps.total(), 351.1, 0.05);
	
}

- (void) testVindicator2 {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::vindicator);
    pilot->ship(ship);
	
//	ship->addModule(TypeID::capitalFlexArmorHardenerII)->charge(TypeID::armorExplosiveResistanceScript);
	ship->add(std::make_shared<Module>(TypeID::imperialNavyEnergizedAdaptiveNanoMembrane));
	ship->add(std::make_shared<Module>(TypeID::imperialNavyEnergizedAdaptiveNanoMembrane));
	ship->add(std::make_shared<Module>(TypeID::armorExplosiveHardenerII));
	auto res0 = ship->resistances();
	ship->add(std::make_shared<Module>(TypeID::largeAntiExplosivePumpII));
	auto res1 = ship->resistances();
	
	XCTAssertLessThan(res0.armor.explosive, res1.armor.explosive);
	XCTAssertEqualWithAccuracy(res1.armor.explosive, 0.782, 0.0005);
}

- (void) testVindicator3 {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::vindicator);
    pilot->ship(ship);

	ship->add(std::make_shared<Module>(TypeID::reinforcedBulkheadsII));
	ship->add(std::make_shared<Module>(TypeID::reinforcedBulkheadsII));
	ship->add(std::make_shared<Module>(TypeID::reinforcedBulkheadsI));
	ship->add(std::make_shared<Module>(TypeID::inertialStabilizersII));
	ship->add(std::make_shared<Module>(TypeID::inertialStabilizersII));
	ship->add(std::make_shared<Module>(TypeID::inertialStabilizersI));
	ship->add(std::make_shared<Module>(TypeID::_500MNMicrowarpdriveII));
	ship->add(std::make_shared<Module>(TypeID::expandedCargoholdII));

	auto alignTime = ship->alignTime();
	
	XCTAssertEqualWithAccuracy(alignTime.count() / 1000.0, 8.03, 0.005);
	XCTAssertEqualWithAccuracy(ship->cargoCapacity(), 772.59, 0.05);
}

- (void) testVindicator4 {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::vindicator);
    pilot->ship(ship);

	ship->add(std::make_shared<Module>(TypeID::shieldPowerRelayII));
	ship->add(std::make_shared<Module>(TypeID::shieldPowerRelayII));
	ship->add(std::make_shared<Module>(TypeID::shieldPowerRelayI));
	ship->add(std::make_shared<Module>(TypeID::capacitorFluxCoilII));
	ship->add(std::make_shared<Module>(TypeID::capacitorFluxCoilII));
	ship->add(std::make_shared<Module>(TypeID::capacitorFluxCoilI));
	
	auto rechargeTime = ship->capacitor().rechargeTime();
	XCTAssertEqualWithAccuracy(rechargeTime.count() / 1000.0, 488, 0.5);
}

- (void) testNyx {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::nyx);
    pilot->ship(ship);
	
    auto module = std::make_shared<Module>(TypeID::capitalFlexArmorHardenerII);
    module->charge(std::make_shared<Charge>(TypeID::armorExplosiveResistanceScript));
	ship->add(module);
	ship->add(std::make_shared<Module>(TypeID::imperialNavyEnergizedAdaptiveNanoMembrane));
	ship->add(std::make_shared<Module>(TypeID::imperialNavyEnergizedAdaptiveNanoMembrane));
	ship->add(std::make_shared<Module>(TypeID::armorExplosiveHardenerII));
	auto res0 = ship->resistances();
	ship->add(std::make_shared<Module>(TypeID::capitalAntiExplosivePumpII));
	auto res1 = ship->resistances();
	
	XCTAssertLessThan(res0.armor.explosive, res1.armor.explosive);
	XCTAssertEqualWithAccuracy(res1.armor.explosive, 0.856, 0.0005);
}

- (void) testCyno {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::drake);
    pilot->ship(ship);

    try {
		ship->add(std::make_shared<Module>(TypeID::covertCynosuralFieldGeneratorI));
		XCTFail("Error");
	}
	catch(...) {
	}
    ship = std::make_shared<Ship>(TypeID::sin);
	pilot->ship(ship);
    ship->add(std::make_shared<Module>(TypeID::covertCynosuralFieldGeneratorI));

}

- (void) testProteus {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::proteus);
    pilot->ship(ship);

    
    ship->add(std::make_shared<Module>(TypeID::_10MNAfterburnerI), Module::anySocket, true);
    ship->add(std::make_shared<Module>(TypeID::mediumShieldBoosterII), Module::anySocket, true);
    ship->add(std::make_shared<Module>(TypeID::ionBlasterCannonII), Module::anySocket, true);
    ship->add(std::make_shared<Module>(TypeID::ionBlasterCannonII), Module::anySocket, true);
    auto modules = ship->modules();
	for (auto module: modules) {
		XCTAssertEqual(module->fail(), true);
	}
	
	ship->add(std::make_shared<Module>(TypeID::proteusCoreAugmentedFusionReactor));
	ship->add(std::make_shared<Module>(TypeID::proteusDefensiveAugmentedPlating));
	ship->add(std::make_shared<Module>(TypeID::proteusOffensiveDroneSynthesisProjector));
	ship->add(std::make_shared<Module>(TypeID::proteusPropulsionHyperspatialOptimization));
	
	for (auto module: modules) {
		XCTAssertEqual(module->fail(), false);
	}
	
    auto ship2 = std::make_shared<Ship>(TypeID::proteus);
	
	ship2->add(std::make_shared<Module>(TypeID::proteusCoreAugmentedFusionReactor));
	ship2->add(std::make_shared<Module>(TypeID::proteusDefensiveAugmentedPlating));
	ship2->add(std::make_shared<Module>(TypeID::proteusOffensiveDroneSynthesisProjector));
	ship2->add(std::make_shared<Module>(TypeID::proteusPropulsionHyperspatialOptimization));

    ship2->add(std::make_shared<Module>(TypeID::_10MNAfterburnerI), Module::anySocket, true);
    ship2->add(std::make_shared<Module>(TypeID::mediumShieldBoosterII), Module::anySocket, true);
    ship2->add(std::make_shared<Module>(TypeID::ionBlasterCannonII), Module::anySocket, true);
    ship2->add(std::make_shared<Module>(TypeID::ionBlasterCannonII), Module::anySocket, true);
    modules = ship2->modules();
               
	pilot->ship(std::move(ship2));
	
	for (auto module: modules) {
		XCTAssertEqual(module->fail(), false);
	}
}

- (void) testMonitor {
    auto gang = Gang();
    auto pilot = std::make_shared<Character>();
    gang.add(pilot);
    pilot->setSkillLevels(5);
    auto ship = std::make_shared<Ship>(TypeID::monitor);
    pilot->ship(ship);

    
	ship->add(std::make_shared<Module>(TypeID::_50MNMicrowarpdriveII));
	ship->add(std::make_shared<Module>(TypeID::targetPainterII));
	ship->add(std::make_shared<Module>(TypeID::sistersExpandedProbeLauncher));

	
	XCTAssertGreaterThan(ship->totalCPU(), ship->usedCPU());
	XCTAssertGreaterThan(ship->totalPowerGrid(), ship->usedPowerGrid());
	ship->add(std::make_shared<Module>(TypeID::smallShieldBoosterI));
	XCTAssertLessThan(ship->totalCPU(), ship->usedCPU());

}

@end
