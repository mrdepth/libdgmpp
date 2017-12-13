//
//  DGMCommodity.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import <Foundation/Foundation.h>
#import "Utility.h"

@interface DGMCommodity : NSObject
@property (readonly) DGMTypeID typeID;
@property (readonly) DGMCommodityTier tier;
@property (readonly) DGMCubicMeter itemVolume;
@property (readonly) DGMCubicMeter totalVolume;
@property (readonly) NSInteger quantity;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("") NS_DESIGNATED_INITIALIZER;
- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID quantity:(NSInteger) quantity error:(NSErrorPtr) error NS_DESIGNATED_INITIALIZER;
- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;
@end
