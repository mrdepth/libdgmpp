//
//  DGMType.m
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "Internal.h"


@implementation DGMAttributes {
	dgmpp::Type* _type;
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nonnull instancetype) initWithType:(nonnull dgmpp::Type*) type {
	if (self = [super init]) {
		_type = type;
	}
	return self;
}

- (nullable DGMAttribute*) objectAtIndexedSubscript:(DGMAttributeID) attributeID {
	if (auto attribute = (*_type)[static_cast<dgmpp::AttributeID>(attributeID)]) {
		return [[DGMAttribute alloc] initWithAttribute:attribute.get()];
	}
	else
		return nil;
}

@end

@implementation DGMType

+ (nullable instancetype) type:(nullable dgmpp::Type*) type {
	if (dynamic_cast<dgmpp::Module*>(type) != nullptr)
		return [[DGMModule alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Drone*>(type) != nullptr)
		return [[DGMDrone alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Structure*>(type) != nullptr)
		return [[DGMStructure alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Ship*>(type) != nullptr)
		return [[DGMShip alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Character*>(type) != nullptr)
		return [[DGMCharacter alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Skill*>(type) != nullptr)
		return [[DGMSkill alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Implant*>(type) != nullptr)
		return [[DGMImplant alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Booster*>(type) != nullptr)
		return [[DGMBooster alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Charge*>(type) != nullptr)
		return [[DGMCharge alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Gang*>(type) != nullptr)
		return [[DGMGang alloc] initWithType:type];
	else if (dynamic_cast<dgmpp::Area*>(type) != nullptr)
		return [[DGMArea alloc] initWithType:type];
	else
		return [[DGMType alloc] initWithType:type];
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nonnull instancetype) initWithType:(nonnull dgmpp::Type*) type {
	if (self = [super init]) {
		_type = type;
	}
	return self;
}

- (DGMTypeID) typeID {
	return static_cast<DGMTypeID>(_type->metaInfo().typeID);
}

- (DGMGroupID) groupID {
	return static_cast<DGMGroupID>(_type->metaInfo().groupID);
}

- (DGMCategoryID) categoryID {
	return static_cast<DGMCategoryID>(_type->metaInfo().categoryID);
}
- (BOOL) isEnabled {
	return _type->isEnabled();
}

- (nonnull NSArray<DGMType*>*) affectors {
	return nil;
}

- (nonnull DGMAttributes*) attributes {
	return [[DGMAttributes alloc] initWithType:_type];
}

- (nullable DGMType*) parent {
	return [DGMType type:_type->parent()];
}

@end
