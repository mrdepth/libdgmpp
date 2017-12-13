//
//  DGMProductionCycle.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import <Foundation/Foundation.h>

@class DGMCommodity;
@interface DGMProductionCycle : NSObject
@property (readonly, nonnull) DGMCommodity* yield;
@property (readonly, nonnull) DGMCommodity* waste;
@property (readonly, nonnull) NSDate* start;
@property (readonly) NSTimeInterval duration;
@property (readonly, nonnull) NSDate* end;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
@end
