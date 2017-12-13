//
//  DGMExtractorControlUnit.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMExtractorControlUnit

- (nonnull NSDate*) launchTime {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->launchTime())];
}

- (void) setLaunchTime:(NSDate *)launchTime {
	dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->launchTime(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(launchTime.timeIntervalSinceReferenceDate)));
}

- (nonnull NSDate*) installTime {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->installTime())];
}

- (void) setInstallTime:(NSDate *)installTime {
	dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->installTime(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(installTime.timeIntervalSinceReferenceDate)));
}

- (nonnull NSDate*) expiryTime {
	return [NSDate dateWithTimeIntervalSinceReferenceDate:NSTimeIntervalMake(dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->expiryTime())];
}

- (void) setExpiryTime:(NSDate *)expiryTime {
	dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->expiryTime(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(expiryTime.timeIntervalSinceReferenceDate)));
}

- (NSTimeInterval) cycleTime {
	return NSTimeIntervalMake(dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->cycleTime());
}

- (void) setCycleTime:(NSTimeInterval)cycleTime {
	dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->cycleTime(std::chrono::seconds(static_cast<std::chrono::seconds::rep>(cycleTime)));
}

- (NSInteger) quantityPerCycle {
	return dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->quantityPerCycle();
}

- (void) setQuantityPerCycle:(NSInteger)quantityPerCycle {
	dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->quantityPerCycle(quantityPerCycle);
}

- (nullable DGMCommodity*) output {
	if (auto output = dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->output())
		return [[DGMCommodity alloc] initWithCommodity:*output];
	else
		return nil;
}

- (nonnull NSArray<DGMProductionState*>*) states {
	const auto& v = dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->states();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto& i: v)
		[result addObject: [[DGMProductionState alloc] initWithState: i.get()]];
	return result;
}

- (nonnull NSArray<DGMProductionCycle*>*) cycles {
	const auto& v = dynamic_cast<dgmpp::ExtractorControlUnit*>(self.facility)->cycles();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (auto& i: v)
		[result addObject: [[DGMProductionCycle alloc] initWithCycle: i.get()]];
	return result;
}



@end
