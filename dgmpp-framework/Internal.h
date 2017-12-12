//
//  Internal.h
//  dgmpp
//
//  Created by Artem Shimanski on 11.12.2017.
//

#import "DGMType.h"
#import "DGMAttribute.h"
#import "DGMArea.h"
#import "DGMGang.h"
#import "DGMCharacter.h"
#import "DGMShip.h"
#import "DGMStructure.h"
#import "DGMModule.h"
#import "DGMDrone.h"
#import "DGMCharge.h"

#import "Gang.hpp"

using namespace std::chrono_literals;

@interface DGMAttribute()
- (nonnull instancetype) initWithAttribute:(nonnull dgmpp::Attribute*) attribute;
@end

@interface DGMType()
@property (nonatomic, nonnull) dgmpp::Type* type;
+ (nullable instancetype) type:(nullable dgmpp::Type*) type;
- (nonnull instancetype) initWithType:(nonnull dgmpp::Type*) type;
@end


@interface DGMArea()
@property (readonly) std::unique_ptr<dgmpp::Area>& area;
@end

@interface DGMCharacter()
@property (readonly) std::unique_ptr<dgmpp::Character>& character;
@end

@interface DGMImplant()
@property (readonly) std::unique_ptr<dgmpp::Implant>& implant;
@end

@interface DGMBooster()
@property (readonly) std::unique_ptr<dgmpp::Booster>& booster;
@end

@interface DGMShip()
@property (readonly) std::unique_ptr<dgmpp::Ship>& ship;
@end

@interface DGMModule()
@property (readonly) std::unique_ptr<dgmpp::Module>& module;
@end

@interface DGMDrone()
@property (readonly) std::unique_ptr<dgmpp::Drone>& drone;
@end

@interface DGMCharge()
@property (readonly) std::unique_ptr<dgmpp::Charge>& charge;
@end

inline DGMDamageVector DGMDamageVectorMake(const dgmpp::DamageVector& v) {
	return {v.em, v.thermal, v.kinetic, v.explosive};
}

inline dgmpp::DamageVector DamageVectorMake(const DGMDamageVector& v) {
	return {v.em, v.thermal, v.kinetic, v.explosive};
}

inline DGMDamagePerSecond DGMDamagePerSecondMake(const dgmpp::DamagePerSecond& v) {
	return DGMDamageVectorMake(v * 1s);
}


inline DGMHitPoints DGMHitPointsMake(const dgmpp::HitPoints& v) {
	return {v.shield, v.armor, v.hull};
}

inline DGMTank DGMTankMake(const dgmpp::Tank& v) {
	return {v.passiveShield * 1s, v.shieldRepair * 1s, v.armorRepair * 1s, v.hullRepair * 1s};
}

inline DGMResistances DGMResistancesMake(const dgmpp::Resistances& v) {
	return {
		v.shield.em, v.shield.thermal, v.shield.kinetic, v.shield.explosive,
		v.armor.em, v.armor.thermal, v.armor.kinetic, v.armor.explosive,
		v.hull.em, v.hull.thermal, v.hull.kinetic, v.hull.explosive};
}

inline dgmpp::HostileTarget HostileTargetMake(const DGMHostileTarget& v) {
	return {dgmpp::make_rate(v.angularVelocity, 1s), dgmpp::make_rate(v.velocity, 1s), v.signature, v.range};
}

template<typename Rep, typename Ratio>
NSTimeInterval NSTimeIntervalMake(const std::chrono::duration<Rep, Ratio>& v) {
	return std::chrono::duration_cast<std::chrono::seconds>(v).count();
}
