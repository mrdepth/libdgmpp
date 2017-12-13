//
//  DGMCharacter.m
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "Internal.h"

@implementation DGMSkill

- (NSInteger) level {
	return dynamic_cast<dgmpp::Skill*>(self.type)->level();
}

- (void) setLevel:(NSInteger)level {
	return dynamic_cast<dgmpp::Skill*>(self.type)->level(static_cast<int>(level));
}

@end

@implementation DGMImplant {
	std::unique_ptr<dgmpp::Implant> _implant;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	try {
		_implant = dgmpp::Implant::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_implant.get()]) {
		}
		return self;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return nil;
	}
}

- (DGMImplantSlot) slot {
	return static_cast<DGMImplantSlot>(dynamic_cast<dgmpp::Implant*>(self.type)->slot());
}

@end

@implementation DGMBooster {
	std::unique_ptr<dgmpp::Booster> _booster;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	try {
		_booster = dgmpp::Booster::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_booster.get()]) {
		}
		return self;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return nil;
	}
}

- (DGMBoosterSlot) slot {
	return static_cast<DGMBoosterSlot>(dynamic_cast<dgmpp::Booster*>(self.type)->slot());
}

@end

@implementation DGMCharacter {
	std::unique_ptr<dgmpp::Character> _character;
}

- (nonnull instancetype) init {
	_character = dgmpp::Character::Create();
	if (self = [super initWithType:_character.get()]) {
	}
	return self;
}

- (void) setSkillLevels:(NSInteger) level {
	dynamic_cast<dgmpp::Character*>(self.type)->setSkillLevels(static_cast<int>(level));
}

- (BOOL) addImplant:(nonnull DGMImplant*) implant replace:(BOOL) replace error:(NSErrorPtr) error {
	try {
		if (auto& ptr = implant.implant)
			dynamic_cast<dgmpp::Character*>(self.type)->add(std::move(ptr));
		return YES;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return NO;
	}
}

- (BOOL) addBooster:(nonnull DGMBooster*) booster replace:(BOOL) replace error:(NSErrorPtr) error {
	try {
		if (auto& ptr = booster.booster)
			dynamic_cast<dgmpp::Character*>(self.type)->add(std::move(ptr));
		return YES;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return NO;
	}
}

- (void) removeImplant:(nonnull DGMImplant*) implant {
	dynamic_cast<dgmpp::Character*>(self.type)->remove(dynamic_cast<dgmpp::Implant*>(implant.type));
}

- (void) removeBooster:(nonnull DGMBooster*) booster {
	dynamic_cast<dgmpp::Character*>(self.type)->remove(dynamic_cast<dgmpp::Booster*>(booster.type));
}

- (nullable DGMShip*) ship {
	return (DGMShip*) [DGMType type:dynamic_cast<dgmpp::Character*>(self.type)->ship()];
}

- (void) setShip:(nullable DGMShip *)ship {
	if (ship && ship.ship)
		dynamic_cast<dgmpp::Character*>(self.type)->ship(std::move(ship.ship));
	else
		dynamic_cast<dgmpp::Character*>(self.type)->ship(nullptr);
}

- (nullable DGMStructure*) structure {
	return (DGMStructure*) [DGMType type:dynamic_cast<dgmpp::Character*>(self.type)->structure()];
}

- (void) setStructure:(nullable DGMStructure *)structure {
	if (auto& ptr = structure.ship)
		dynamic_cast<dgmpp::Character*>(self.type)->ship(std::move(ptr));
}

- (nonnull NSArray<DGMImplant*>*) implants {
	auto character = dynamic_cast<dgmpp::Character*>(self.type);
	auto implants = character->implants();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:implants.size()];
	for (auto i: implants)
		[result addObject:[DGMType type:i]];
	return result;
}

- (nonnull NSArray<DGMBooster*>*) boosters {
	auto character = dynamic_cast<dgmpp::Character*>(self.type);
	auto boosters = character->boosters();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:boosters.size()];
	for (auto i: boosters)
		[result addObject:[DGMType type:i]];
	return result;
}

- (nonnull NSArray<DGMSkill*>*) skills {
	auto character = dynamic_cast<dgmpp::Character*>(self.type);
	auto skills = character->skills();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:skills.size()];
	for (auto i: skills)
		[result addObject:[DGMType type:i]];
	return result;
}


@end
