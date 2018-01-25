//
//  SDE.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 01.11.2017.
//

#pragma once
#include <stdexcept>
#include "Type.hpp"
#include "Attribute.hpp"
#include "Errors.hpp"

namespace dgmpp {
	namespace SDE {
		extern const MetaInfo::Attribute& get (AttributeID attributeID);
		extern const MetaInfo::Type& get (TypeID typeID);
		extern const MetaInfo::WarfareBuff& get (WarfareBuffID warfareBuffID);
		extern const MetaInfo::Schematic& get (SchematicID schematicID);
		extern const MetaInfo::Commodity& commodity (TypeID typeID);
		extern const MetaInfo::Facility& facility (TypeID typeID);

		extern const MetaInfo::Type* const *skills;
		extern const std::size_t skillsCount;
		
		
		const auto canFitShipGroupAttributes = {
			AttributeID::canFitShipGroup01,
			AttributeID::canFitShipGroup02,
			AttributeID::canFitShipGroup03,
			AttributeID::canFitShipGroup04,
			AttributeID::canFitShipGroup05,
			AttributeID::canFitShipGroup06,
			AttributeID::canFitShipGroup07,
			AttributeID::canFitShipGroup08,
			AttributeID::canFitShipGroup09,
			AttributeID::canFitShipGroup10,
			AttributeID::canFitShipGroup11,
			AttributeID::canFitShipGroup12,
			AttributeID::canFitShipGroup13,
			AttributeID::canFitShipGroup14,
			AttributeID::canFitShipGroup15,
			AttributeID::canFitShipGroup16,
			AttributeID::canFitShipGroup17,
			AttributeID::canFitShipGroup18,
			AttributeID::canFitShipGroup19,
			AttributeID::canFitShipGroup20
		};
		
		const auto canFitShipTypeAttributes = {
			AttributeID::fitsToShipType,
			AttributeID::canFitShipType1,
			AttributeID::canFitShipType2,
			AttributeID::canFitShipType3,
			AttributeID::canFitShipType4,
			AttributeID::canFitShipType5,
			AttributeID::canFitShipType6,
			AttributeID::canFitShipType7,
			AttributeID::canFitShipType8,
			AttributeID::canFitShipType9,
			AttributeID::canFitShipType10,
		};
		
		const auto chargeGroupAttributeIDs = {
			AttributeID::chargeGroup1,
			AttributeID::chargeGroup2,
			AttributeID::chargeGroup3,
			AttributeID::chargeGroup4,
			AttributeID::chargeGroup5
		};
		
		const auto moduleOptimalAttributes = {
			AttributeID::maxRange,
			AttributeID::shieldTransferRange,
			AttributeID::powerTransferRange,
			AttributeID::energyNeutralizerRangeOptimal,
			AttributeID::empFieldRange,
			AttributeID::ecmBurstRange,
			AttributeID::warpScrambleRange,
			AttributeID::cargoScanRange,
			AttributeID::shipScanRange,
			AttributeID::surveyScanRange
		};

		const auto moduleFalloffAttributes = {
			AttributeID::falloff, AttributeID::shipScanFalloff, AttributeID::falloffEffectiveness};

		const auto moduleCycleTimeAttributes = {
			AttributeID::speed, AttributeID::duration, AttributeID::durationSensorDampeningBurstProjector, AttributeID::durationTargetIlluminationBurstProjector, AttributeID::durationECMJammerBurstProjector, AttributeID::durationWeaponDisruptionBurstProjector, AttributeID::missileLaunchDuration};
		
		const auto droneDamageAttributes = {
			AttributeID::emDamage,
			AttributeID::explosiveDamage,
			AttributeID::kineticDamage,
			AttributeID::thermalDamage,
			AttributeID::fighterAbilityMissilesDamageMultiplier,
			AttributeID::fighterAbilityAttackMissileDamageMultiplier,
			AttributeID::fighterAbilityAttackTurretDamageMultiplier
		};
		
		const auto droneOptimalAttributes = {
			AttributeID::maxRange,
			AttributeID::shieldTransferRange,
			AttributeID::powerTransferRange,
			AttributeID::energyNeutralizerRangeOptimal,
			AttributeID::empFieldRange,
			AttributeID::ecmBurstRange,
			AttributeID::fighterAbilityAttackMissileRangeOptimal,
			AttributeID::fighterAbilityAttackTurretRangeOptimal,
			AttributeID::fighterAbilityECMRangeOptimal,
			AttributeID::fighterAbilityEnergyNeutralizerOptimalRange,
			AttributeID::fighterAbilityStasisWebifierOptimalRange,
			AttributeID::fighterAbilityWarpDisruptionRange
		};
		
		const auto droneFalloffAttributes = {
			AttributeID::falloff,
			AttributeID::fighterAbilityAttackMissileRangeFalloff,
			AttributeID::fighterAbilityAttackTurretRangeFalloff,
			AttributeID::fighterAbilityECMRangeFalloff,
			AttributeID::fighterAbilityEnergyNeutralizerFalloffRange,
			AttributeID::fighterAbilityStasisWebifierFalloffRange
		};

		const auto chargeDamageAttributes = {
			AttributeID::emDamage,
			AttributeID::explosiveDamage,
			AttributeID::kineticDamage,
			AttributeID::thermalDamage
		};
		
		const auto scanStrengthAttributes = {
			AttributeID::scanRadarStrength,
			AttributeID::scanLadarStrength,
			AttributeID::scanMagnetometricStrength,
			AttributeID::scanGravimetricStrength
		};

		const auto warfareBuffIDAttributes = {
			AttributeID::warfareBuff1ID,
			AttributeID::warfareBuff2ID,
			AttributeID::warfareBuff3ID,
			AttributeID::warfareBuff4ID
		};
		
		const auto specialHoldCapacityAttributes = {
			AttributeID::specialOreHoldCapacity,
			AttributeID::specialMineralHoldCapacity,
			AttributeID::specialPlanetaryCommoditiesHoldCapacity
		};

		
		/*const auto warfareBuffValueAttributes = {
			AttributeID::warfareBuff1Value,
			AttributeID::warfareBuff2Value,
			AttributeID::warfareBuff3Value,
			AttributeID::warfareBuff4Value,
			AttributeID::warfareBuff1Multiplier,
			AttributeID::warfareBuff2Multiplier,
			AttributeID::warfareBuff3Multiplier,
			AttributeID::warfareBuff4Multiplier
		};*/
	}
}
