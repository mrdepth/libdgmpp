//
//  DGMRoute.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import <Foundation/Foundation.h>

@class DGMFacility;
@class DGMCommodity;
@interface DGMRoute : NSObject
@property (readonly, nonnull) DGMFacility* from;
@property (readonly, nonnull) DGMFacility* to;
@property (readonly, nonnull) DGMCommodity* commodity;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
- (nonnull instancetype) initWithCommodity:(nonnull DGMCommodity*) commodity from:(nonnull DGMFacility*) from to:(nonnull DGMFacility*) to;

@end
