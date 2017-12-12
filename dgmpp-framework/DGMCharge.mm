//
//  DGMCharge.m
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "Internal.h"

@implementation DGMCharge {
	std::unique_ptr<dgmpp::Charge> _charge;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	@try {
		_charge = dgmpp::Charge::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_charge.get()]) {
		}
		return self;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return nil;
	}
}

- (DGMChargeSize) chargeSize {
	return static_cast<DGMChargeSize>(dynamic_cast<dgmpp::Charge*>(self.type)->chargeSize());
}

@end
