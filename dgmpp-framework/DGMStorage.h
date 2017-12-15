//
//  DGMStorage.h
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "DGMFacility.h"

@class DGMState;
@interface DGMStorage : DGMFacility
@property (readonly, nonnull) NSArray<DGMState*>* states;
@end
