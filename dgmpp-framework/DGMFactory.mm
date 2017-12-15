//
//  DGMFactory.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMFactory

- (DGMSchematicID) schematicID {
	return static_cast<DGMSchematicID>(dynamic_cast<dgmpp::Factory*>(self.facility)->schematic()->schematicID);
}

- (BOOL) setSchematicID:(DGMSchematicID)schematicID error:(NSErrorPtr) error {
	try {
		dynamic_cast<dgmpp::Factory*>(self.facility)->schematic(static_cast<dgmpp::SchematicID>(schematicID));
		return YES;
	}
	catch(const std::logic_error& exc) {
		if (error)
			*error = [NSError errorWithDomain:DGMErrorDomain code:0 userInfo:@{NSLocalizedDescriptionKey: [NSString stringWithUTF8String:exc.what()]}];
		return NO;
	}
}

- (nonnull NSDate*) launchTime {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(dynamic_cast<dgmpp::Factory*>(self.facility)->launchTime())];
}

- (void) setLaunchTime:(NSDate *)launchTime {
	dynamic_cast<dgmpp::Factory*>(self.facility)->launchTime(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(launchTime.timeIntervalSinceReferenceDate)));
}

- (NSTimeInterval) cycleTime {
	if (auto cycleTime = dynamic_cast<dgmpp::Factory*>(self.facility)->cycleTime())
		return NSTimeIntervalMake(*cycleTime);
	else
		return 0;
}

- (nullable DGMCommodity*) output {
	if (auto output = dynamic_cast<dgmpp::Factory*>(self.facility)->output())
		return [[DGMCommodity alloc] initWithCommodity:*output];
	else
		return nil;
}

- (nonnull NSArray<DGMProductionState*>*) states {
	const auto& v = dynamic_cast<dgmpp::Factory*>(self.facility)->states();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto& i: v)
		[result addObject: [[DGMProductionState alloc] initWithState: i.get()]];
	return result;
}

- (nonnull NSArray<DGMProductionCycle*>*) cycles {
	const auto& v = dynamic_cast<dgmpp::Factory*>(self.facility)->cycles();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto& i: v)
		[result addObject: [[DGMProductionCycle alloc] initWithCycle: i.get()]];
	return result;
}



@end
