//
//  dgmppTests.m
//  dgmppTests
//
//  Created by Артем Шиманский on 02.05.16.
//
//

#import <XCTest/XCTest.h>
#import <dgmpp/dgmpp.h>

using namespace dgmpp;

@interface dgmppTests : XCTestCase {
	std::shared_ptr<Engine> engine;
}

@end

@implementation dgmppTests

- (void)setUp {
    [super setUp];
	std::shared_ptr<Engine> engine = std::make_shared<Engine>(std::make_shared<SqliteConnector>("/Users/shimanski/Documents/git/EVEUniverse/ThirdParty/dgmpp/dbinit/dgm.sqlite"));
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testShips {
	auto gang = engine->getGang();
	auto pilot = gang->addPilot();
	pilot->setAllSkillsLevel(5);
	
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT typeID FROM invTypes where groupID in (select groupID from invGroups where categoryID=6)");
	auto result = engine->getSqlConnector()->exec(stmt);
	while (result->next()) {
		TypeID typeID = result->getInt(0);
		pilot->setShip(typeID);
	}
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
