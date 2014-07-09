//
//  eufeTests.m
//  eufeTests
//
//  Created by Артем Шиманский on 09.07.14.
//
//

#import <XCTest/XCTest.h>
#import "eufe.h"

@interface eufeTests : XCTestCase {
	eufe::Engine* _engine;
}

@end

@implementation eufeTests

- (void)setUp
{
    [super setUp];
	NSString* path = [[NSBundle bundleForClass:self.class] pathForResource:@"eufe" ofType:@"sqlite"];
	_engine = new eufe::Engine(new eufe::SqliteConnector([path UTF8String]));
}

- (void)tearDown
{
	delete _engine;
    [super tearDown];
}

- (void)testShips
{
	eufe::Gang* gang = _engine->getGang();
	eufe::Character* character = gang->addPilot();
	character->setAllSkillsLevel(5);
	auto result = _engine->getSqlConnector()->exec("SELECT typeID FROM invTypes as a, invGroups as b where a.groupID=b.groupID and b.categoryID=6;");
	while (result->next()) {
		int32_t typeID = result->getInt(0);
		NSLog(@"%d", typeID);
		eufe::Ship* ship = character->setShip(typeID);
		
		{
			auto result = _engine->getSqlConnector()->exec("SELECT typeID FROM invTypes as a, invGroups as b where a.groupID=b.groupID and b.categoryID=7 group by b.groupID;");
			while (result->next()) {
				int32_t typeID = result->getInt(0);
				ship->addModule(typeID, true);
			}
		}

		ship->getCalibrationUsed();
		ship->getTotalCalibration();
		ship->getPowerGridUsed();
		ship->getTotalPowerGrid();
		ship->getCpuUsed();
		ship->getTotalCpu();
		ship->getDroneBandwidthUsed();
		ship->getTotalDroneBandwidth();
		ship->getDroneBayUsed();
		ship->getTotalDroneBay();
		
		ship->getCapCapacity();
		ship->isCapStable();
		ship->getCapLastsTime();
		ship->getCapStableLevel();
		ship->getCapUsed();
		ship->getCapRecharge();

		ship->getResistances();
		ship->getTank();
		ship->getEffectiveTank();
		ship->getSustainableTank();
		ship->getEffectiveSustainableTank();
		ship->getHitPoints();
		ship->getEffectiveHitPoints();
		ship->getShieldRecharge();
		
		ship->getWeaponDps();
		ship->getWeaponVolley();
		ship->getDroneDps();
		ship->getDroneVolley();
		ship->getAlignTime();
		ship->getWarpSpeed();
		ship->getMaxWarpDistance();
		ship->getVelocity();
		ship->getSignatureRadius();
		
		ship->getMaxTargets();
		ship->getMaxTargetRange();
		ship->getScanStrength();
		ship->getScanType();
		ship->getProbeSize();
		ship->getScanResolution();
		
		ship->getMaxActiveDrones();
		ship->getActiveDrones();
//		break;
	};
	gang->removePilot(character);
//    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
}

- (void)testModules {
	eufe::Gang* gang = _engine->getGang();
	eufe::Character* character = gang->addPilot();
	character->setAllSkillsLevel(5);
	eufe::Ship* ship = character->setShip(645);
	auto result = _engine->getSqlConnector()->exec("SELECT typeID FROM invTypes as a, invGroups as b where a.groupID=b.groupID and b.categoryID=7 group by b.groupID;");
	while (result->next()) {
		int32_t typeID = result->getInt(0);
		ship->addModule(typeID, true);
	}
	
	ship->getCalibrationUsed();
	ship->getTotalCalibration();
	ship->getPowerGridUsed();
	ship->getTotalPowerGrid();
	ship->getCpuUsed();
	ship->getTotalCpu();
	ship->getDroneBandwidthUsed();
	ship->getTotalDroneBandwidth();
	ship->getDroneBayUsed();
	ship->getTotalDroneBay();
	
	ship->getCapCapacity();
	ship->isCapStable();
	ship->getCapLastsTime();
	ship->getCapStableLevel();
	ship->getCapUsed();
	ship->getCapRecharge();
	
	ship->getResistances();
	ship->getTank();
	ship->getEffectiveTank();
	ship->getSustainableTank();
	ship->getEffectiveSustainableTank();
	ship->getHitPoints();
	ship->getEffectiveHitPoints();
	ship->getShieldRecharge();
	
	ship->getWeaponDps();
	ship->getWeaponVolley();
	ship->getDroneDps();
	ship->getDroneVolley();
	ship->getAlignTime();
	ship->getWarpSpeed();
	ship->getMaxWarpDistance();
	ship->getVelocity();
	ship->getSignatureRadius();
	
	ship->getMaxTargets();
	ship->getMaxTargetRange();
	ship->getScanStrength();
	ship->getScanType();
	ship->getProbeSize();
	ship->getScanResolution();
	
	ship->getMaxActiveDrones();
	ship->getActiveDrones();
}


@end
