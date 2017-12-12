//
//  DGMArea.m
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "Internal.h"

@implementation DGMArea {
	std::unique_ptr<dgmpp::Area> _area;
}

- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error {
	@try {
		_area = dgmpp::Area::Create(static_cast<dgmpp::TypeID>(typeID));
		if (self = [super initWithType:_area.get()]) {
		}
		return self;
	}
	@catch(NSException* exc) {
		if (error)
			*error = [NSError errorWithDomain:exc.name code:0 userInfo:exc.userInfo];
		return nil;
	}
}

@end
