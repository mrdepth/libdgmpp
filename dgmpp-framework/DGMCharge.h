//
//  DGMCharge.h
//  dgmpp
//
//  Created by Artem Shimanski on 12.12.2017.
//

#import "DGMType.h"

@interface DGMCharge : DGMType
@property (readonly) DGMChargeSize chargeSize;
- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;

@end
