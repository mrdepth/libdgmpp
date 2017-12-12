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
	return nullptr;
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
