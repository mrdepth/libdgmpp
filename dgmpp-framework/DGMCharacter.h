//
//  DGMCharacter.h
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "DGMType.h"

@interface DGMSkill : DGMType
@property (assign) NSInteger level;
@end

@interface DGMImplant : DGMType
@property (readonly) DGMImplantSlot slot;
- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;
@end

@interface DGMBooster : DGMType
@property (readonly) DGMBoosterSlot slot;
- (nullable instancetype) initWithTypeID:(DGMTypeID) typeID error:(NSErrorPtr) error;
@end

@class DGMShip;
@class DGMStructure;
@class DGMArea;
@interface DGMCharacter : DGMType
@property (nullable) DGMShip* ship;
@property (nullable) DGMStructure* structure;
@property (readonly, nonnull) NSArray<DGMImplant*>* implants;
@property (readonly, nonnull) NSArray<DGMBooster*>* boosters;
@property (readonly, nonnull) NSArray<DGMSkill*>* skills;

- (nonnull instancetype) init;
- (void) setSkillLevels:(NSInteger) level;
- (BOOL) addImplant:(nonnull DGMImplant*) implant replace:(BOOL) replace error:(NSErrorPtr) error;
- (BOOL) addBooster:(nonnull DGMBooster*) booster replace:(BOOL) replace error:(NSErrorPtr) error;
- (void) removeImplant:(nonnull DGMImplant*) implant;
- (void) removeBooster:(nonnull DGMBooster*) booster;

@end
