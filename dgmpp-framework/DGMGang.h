//
//  DGMGang.h
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "DGMType.h"

@class DGMCharacter;
@interface DGMGang : DGMType
@property (readonly, nonnull) NSArray<DGMCharacter*>* pilots;

- (nonnull instancetype) init;
- (void) addPilot:(nonnull DGMCharacter*) pilot;
- (void) removePilot:(nonnull DGMCharacter*) pilot;

@end
