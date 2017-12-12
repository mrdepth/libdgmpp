//
//  DGMAttribute.h
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import <Foundation/Foundation.h>
#import "Utility.h"

@class DGMType;
@interface DGMAttribute : NSObject
@property (readonly) DGMAttributeID attributeID;
@property (readonly, nonnull) DGMType* owner;
@property (readonly) double value;
@property (readonly) double initialValue;
@property (readonly) BOOL isStackable;
@property (readonly) BOOL highIsGood;

- (nonnull instancetype) init NS_SWIFT_UNAVAILABLE("");
@end
