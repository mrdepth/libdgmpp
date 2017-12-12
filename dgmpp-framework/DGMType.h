//
//  DGMType.h
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import <Foundation/Foundation.h>
#import "Utility.h"

@class DGMAttribute;
@interface DGMAttributes : NSObject
- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
- (nullable DGMAttribute*) objectAtIndexedSubscript:(DGMAttributeID) attributeID;
@end

@interface DGMType : NSObject
@property (readonly) DGMTypeID typeID;
@property (readonly) DGMGroupID groupID;
@property (readonly) DGMCategoryID categoryID;
@property (readonly) BOOL isEnabled;
@property (readonly, nonnull) NSArray<DGMType*>* affectors;
@property (readonly, nonnull) DGMAttributes* attributes;
@property (readonly, nullable) DGMType* parent;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
@end
