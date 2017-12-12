//
//  DGMAttribute.m
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "Internal.h"
#import "Type.hpp"

@implementation DGMAttribute {
	dgmpp::Attribute* _attribute;
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nonnull instancetype) initWithAttribute:(nonnull dgmpp::Attribute*) attribute {
	if (self = [super init]) {
		_attribute = attribute;
	}
	return self;
}

- (DGMAttributeID) attributeID {
	return static_cast<DGMAttributeID>(_attribute->metaInfo().attributeID);
}

- (nonnull DGMType*) owner {
	return [DGMType type: &_attribute->owner()];
}

- (double) value {
	return _attribute->value();
}

- (double) initialValue {
	return _attribute->metaInfo().defaultValue;
}

- (BOOL) isStackable {
	return _attribute->metaInfo().isStackable;
}

- (BOOL) highIsGood {
	return _attribute->metaInfo().highIsGood;
}


@end
