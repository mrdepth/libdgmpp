//
//  DGMCommodity.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMCommodity {
	std::unique_ptr<dgmpp::Commodity> _commodity;
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID quantity:(NSInteger) quantity error:(NSErrorPtr) error {
	try {
		if (self = [super init]) {
			_commodity.reset(new dgmpp::Commodity(static_cast<dgmpp::TypeID>(typeID), quantity));
		}
		return self;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return nil;
	}
}

- (nonnull instancetype) initWithCommodity:(dgmpp::Commodity) commodity {
	if (self = [super init]) {
		_commodity.reset(new dgmpp::Commodity(commodity));
	}
	return self;
}

- (dgmpp::Commodity) commodity {
	return dgmpp::Commodity(static_cast<dgmpp::TypeID>(self.typeID), self.quantity);
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	return [self initWithTypeID:typeID quantity:0 error:error];
}

- (DGMTypeID) typeID {
	return static_cast<DGMTypeID>(_commodity->metaInfo().typeID);
}

- (DGMCommodityTier) tier {
	return static_cast<DGMCommodityTier>(_commodity->metaInfo().tier);
}

- (DGMCubicMeter) itemVolume {
	return static_cast<DGMCubicMeter>(_commodity->metaInfo().volume);
}

- (DGMCubicMeter) totalVolume {
	return static_cast<DGMCubicMeter>(_commodity->volume());
}

- (NSInteger) quantity {
	return static_cast<NSInteger>(_commodity->quantity());
}

@end
