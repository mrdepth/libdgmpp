//
//  DGMFacility.m
//  dgmpp
//
//  Created by Artem Shimanski on 13.12.2017.
//

#import "Internal.h"

@implementation DGMFacility

+ (nullable instancetype) facility:(nullable dgmpp::Facility*) facility {
	if (dynamic_cast<dgmpp::ExtractorControlUnit*>(facility) != nullptr)
		return [[DGMExtractorControlUnit alloc] initWithFacility:facility];
	else if (dynamic_cast<dgmpp::Factory*>(facility) != nullptr)
		return [[DGMFactory alloc] initWithFacility:facility];
	else if (dynamic_cast<dgmpp::CommandCenter*>(facility) != nullptr)
		return [[DGMCommandCenter alloc] initWithFacility:facility];
	else if (dynamic_cast<dgmpp::Spaceport*>(facility) != nullptr)
		return [[DGMSpaceport alloc] initWithFacility:facility];
	else if (dynamic_cast<dgmpp::Storage*>(facility) != nullptr)
		return [[DGMStorage alloc] initWithFacility:facility];
	else
		return [[DGMFacility alloc] initWithFacility:facility];
}

- (nonnull instancetype) init {
	if (self = [super init]) {
	}
	return self;
}


- (nonnull instancetype) initWithFacility:(nonnull dgmpp::Facility*) facility {
	if (self = [super init]) {
		self.facility = facility;
	}
	return self;
}

- (int64_t) identifier {
	return self.facility->identifier();
}

- (DGMCubicMeter) capacity {
	return self.facility->capacity();
}

- (DGMCubicMeter) freeVolume {
	return self.facility->freeVolume();
}

- (DGMCubicMeter) usedVolume {
	return self.facility->usedVolume();
}

- (nonnull NSArray<DGMCommodity*>*) commodities {
	auto v = self.facility->commodities();
	NSMutableArray* result = [[NSMutableArray alloc] initWithCapacity:v.size()];
	for (const auto& i: v)
		[result addObject: [[DGMCommodity alloc] initWithCommodity:i]];
	return result;
}

- (nullable DGMCommodity*) objectAtIndexedSubscript: (DGMTypeID) typeID {
	try {
		return [[DGMCommodity alloc] initWithCommodity:(*self.facility)[static_cast<dgmpp::TypeID>(typeID)]];
	}
	catch(std::logic_error&) {
		return nil;
	}
}

- (nullable DGMCommodity*) incomeWithTypeID:(DGMTypeID) typeID {
	try {
		return [[DGMCommodity alloc] initWithCommodity:self.facility->income(static_cast<dgmpp::TypeID>(typeID))];
	}
	catch(std::logic_error&) {
		return nil;
	}
}

- (void) addCommodity:(nonnull DGMCommodity*) commodity {
	self.facility->add(commodity.commodity);
}

- (void) extractCommodity:(nonnull DGMCommodity*) commodity {
	self.facility->extract(commodity.commodity);
}



@end
