#pragma once
#include "MetaInfo.hpp"
#include "Modifiers.hpp"

namespace dgmpp2 {
	namespace SDE {
		namespace WafrareBuffs {
			using namespace MetaInfo;
			constexpr MetaInfo::Modifier shieldHarmonizingChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldEmDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier shieldHarmonizingChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldKineticDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier shieldHarmonizingChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldThermalDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier shieldHarmonizingChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldExplosiveDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr auto shieldHarmonizingChargeBuff1 = MakeBuff(WarfareBuffID::shieldHarmonizingChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&shieldHarmonizingChargeBuff1_modifier0,
																																								&shieldHarmonizingChargeBuff1_modifier1,
																																								&shieldHarmonizingChargeBuff1_modifier2,
																																								&shieldHarmonizingChargeBuff1_modifier3));
			constexpr MetaInfo::Modifier activeShieldingChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::shieldOperation};
			constexpr MetaInfo::Modifier activeShieldingChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::shieldEmissionSystems};
			constexpr MetaInfo::Modifier activeShieldingChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::shieldOperation};
			constexpr MetaInfo::Modifier activeShieldingChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::shieldEmissionSystems};
			constexpr auto activeShieldingChargeBuff1 = MakeBuff(WarfareBuffID::activeShieldingChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&activeShieldingChargeBuff1_modifier0,
																																							&activeShieldingChargeBuff1_modifier1,
																																							&activeShieldingChargeBuff1_modifier2,
																																							&activeShieldingChargeBuff1_modifier3));
			constexpr MetaInfo::Modifier shieldExtensionChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldCapacity, AttributeID::warfareBuff1Multiplier};
			constexpr auto shieldExtensionChargeBuff1 = MakeBuff(WarfareBuffID::shieldExtensionChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&shieldExtensionChargeBuff1_modifier0));
			constexpr MetaInfo::Modifier armorEnergizingChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorEmDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier armorEnergizingChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorKineticDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier armorEnergizingChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorThermalDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier armorEnergizingChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorExplosiveDamageResonance, AttributeID::warfareBuff1Multiplier};
			constexpr auto armorEnergizingChargeBuff1 = MakeBuff(WarfareBuffID::armorEnergizingChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&armorEnergizingChargeBuff1_modifier0,
																																							&armorEnergizingChargeBuff1_modifier1,
																																							&armorEnergizingChargeBuff1_modifier2,
																																							&armorEnergizingChargeBuff1_modifier3));
			constexpr MetaInfo::Modifier rapidRepairChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::repairSystems};
			constexpr MetaInfo::Modifier rapidRepairChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::remoteArmorRepairSystems};
			constexpr MetaInfo::Modifier rapidRepairChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::repairSystems};
			constexpr MetaInfo::Modifier rapidRepairChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::remoteArmorRepairSystems};
			constexpr auto rapidRepairChargeBuff1 = MakeBuff(WarfareBuffID::rapidRepairChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&rapidRepairChargeBuff1_modifier0,
																																					&rapidRepairChargeBuff1_modifier1,
																																					&rapidRepairChargeBuff1_modifier2,
																																					&rapidRepairChargeBuff1_modifier3));
			constexpr MetaInfo::Modifier armorReinforcementChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorHP, AttributeID::warfareBuff1Multiplier};
			constexpr auto armorReinforcementChargeBuff1 = MakeBuff(WarfareBuffID::armorReinforcementChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&armorReinforcementChargeBuff1_modifier0));
			constexpr MetaInfo::Modifier sensorOptimizationChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanResolution, AttributeID::warfareBuff1Multiplier};
			constexpr auto sensorOptimizationChargeBuff1 = MakeBuff(WarfareBuffID::sensorOptimizationChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&sensorOptimizationChargeBuff1_modifier0));
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, GroupID::ECM};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, GroupID::sensorDampener};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, GroupID::targetPainter};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier4 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::falloffEffectiveness, AttributeID::warfareBuff1Multiplier, GroupID::ECM};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier5 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::falloffEffectiveness, AttributeID::warfareBuff1Multiplier, GroupID::sensorDampener};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier6 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::falloffEffectiveness, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier7 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::falloffEffectiveness, AttributeID::warfareBuff1Multiplier, GroupID::targetPainter};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier8 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanGravimetricStrengthBonus, AttributeID::warfareBuff1Multiplier, GroupID::ECM};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier9 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanLadarStrengthBonus, AttributeID::warfareBuff1Multiplier, GroupID::ECM};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier10 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanMagnetometricStrengthBonus, AttributeID::warfareBuff1Multiplier, GroupID::ECM};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier11 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanRadarStrengthBonus, AttributeID::warfareBuff1Multiplier, GroupID::ECM};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier12 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::missileVelocityBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier13 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::explosionDelayBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier14 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::aoeVelocityBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier15 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::falloffBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier16 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRangeBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier17 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::aoeCloudSizeBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier18 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::trackingSpeedBonus, AttributeID::warfareBuff1Multiplier, GroupID::weaponDisruptor};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier19 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxTargetRangeBonus, AttributeID::warfareBuff1Multiplier, GroupID::sensorDampener};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier20 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanResolutionBonus, AttributeID::warfareBuff1Multiplier, GroupID::sensorDampener};
			constexpr MetaInfo::Modifier electronicSuperiorityChargeBuff1_modifier21 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::signatureRadiusBonus, AttributeID::warfareBuff1Multiplier, GroupID::targetPainter};
			constexpr auto electronicSuperiorityChargeBuff1 = MakeBuff(WarfareBuffID::electronicSuperiorityChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&electronicSuperiorityChargeBuff1_modifier0,
																																										&electronicSuperiorityChargeBuff1_modifier1,
																																										&electronicSuperiorityChargeBuff1_modifier2,
																																										&electronicSuperiorityChargeBuff1_modifier3,
																																										&electronicSuperiorityChargeBuff1_modifier4,
																																										&electronicSuperiorityChargeBuff1_modifier5,
																																										&electronicSuperiorityChargeBuff1_modifier6,
																																										&electronicSuperiorityChargeBuff1_modifier7,
																																										&electronicSuperiorityChargeBuff1_modifier8,
																																										&electronicSuperiorityChargeBuff1_modifier9,
																																										&electronicSuperiorityChargeBuff1_modifier10,
																																										&electronicSuperiorityChargeBuff1_modifier11,
																																										&electronicSuperiorityChargeBuff1_modifier12,
																																										&electronicSuperiorityChargeBuff1_modifier13,
																																										&electronicSuperiorityChargeBuff1_modifier14,
																																										&electronicSuperiorityChargeBuff1_modifier15,
																																										&electronicSuperiorityChargeBuff1_modifier16,
																																										&electronicSuperiorityChargeBuff1_modifier17,
																																										&electronicSuperiorityChargeBuff1_modifier18,
																																										&electronicSuperiorityChargeBuff1_modifier19,
																																										&electronicSuperiorityChargeBuff1_modifier20,
																																										&electronicSuperiorityChargeBuff1_modifier21));
			constexpr MetaInfo::Modifier electronicHardeningChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanGravimetricStrength, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier electronicHardeningChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanRadarStrength, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier electronicHardeningChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanLadarStrength, AttributeID::warfareBuff1Multiplier};
			constexpr MetaInfo::Modifier electronicHardeningChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::scanMagnetometricStrength, AttributeID::warfareBuff1Multiplier};
			constexpr auto electronicHardeningChargeBuff1 = MakeBuff(WarfareBuffID::electronicHardeningChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&electronicHardeningChargeBuff1_modifier0,
																																									&electronicHardeningChargeBuff1_modifier1,
																																									&electronicHardeningChargeBuff1_modifier2,
																																									&electronicHardeningChargeBuff1_modifier3));
			constexpr MetaInfo::Modifier electronicHardeningChargeBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::sensorDampenerResistance, AttributeID::warfareBuff2Multiplier};
			constexpr MetaInfo::Modifier electronicHardeningChargeBuff2_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::weaponDisruptionResistance, AttributeID::warfareBuff2Multiplier};
			constexpr auto electronicHardeningChargeBuff2 = MakeBuff(WarfareBuffID::electronicHardeningChargeBuff2, AttributeID::warfareBuff2Multiplier, _modifiers(&electronicHardeningChargeBuff2_modifier0,
																																									&electronicHardeningChargeBuff2_modifier1));
			constexpr MetaInfo::Modifier evasiveManeuversChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::signatureRadius, AttributeID::warfareBuff1Multiplier};
			constexpr auto evasiveManeuversChargeBuff1 = MakeBuff(WarfareBuffID::evasiveManeuversChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&evasiveManeuversChargeBuff1_modifier0));
			constexpr MetaInfo::Modifier interdictionManeuversChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, GroupID::stasisWeb};
			constexpr MetaInfo::Modifier interdictionManeuversChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, GroupID::warpScrambler};
			constexpr auto interdictionManeuversChargeBuff1 = MakeBuff(WarfareBuffID::interdictionManeuversChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&interdictionManeuversChargeBuff1_modifier0,
																																										&interdictionManeuversChargeBuff1_modifier1));
			constexpr MetaInfo::Modifier rapidDeploymentChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::speedFactor, AttributeID::warfareBuff1Multiplier, TypeID::afterburner};
			constexpr MetaInfo::Modifier rapidDeploymentChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::speedFactor, AttributeID::warfareBuff1Multiplier, TypeID::highSpeedManeuvering};
			constexpr auto rapidDeploymentChargeBuff1 = MakeBuff(WarfareBuffID::rapidDeploymentChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&rapidDeploymentChargeBuff1_modifier0,
																																							&rapidDeploymentChargeBuff1_modifier1));
			constexpr MetaInfo::Modifier miningLaserFieldEnhancementChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, TypeID::mining};
			constexpr MetaInfo::Modifier miningLaserFieldEnhancementChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, TypeID::iceHarvesting};
			constexpr MetaInfo::Modifier miningLaserFieldEnhancementChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff1Multiplier, TypeID::gasCloudHarvesting};
			constexpr MetaInfo::Modifier miningLaserFieldEnhancementChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::surveyScanRange, AttributeID::warfareBuff1Multiplier, TypeID::CPUManagement};
			constexpr auto miningLaserFieldEnhancementChargeBuff1 = MakeBuff(WarfareBuffID::miningLaserFieldEnhancementChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&miningLaserFieldEnhancementChargeBuff1_modifier0,
																																													&miningLaserFieldEnhancementChargeBuff1_modifier1,
																																													&miningLaserFieldEnhancementChargeBuff1_modifier2,
																																													&miningLaserFieldEnhancementChargeBuff1_modifier3));
			constexpr MetaInfo::Modifier miningLaserOptimizationChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::mining};
			constexpr MetaInfo::Modifier miningLaserOptimizationChargeBuff1_modifier1 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::iceHarvesting};
			constexpr MetaInfo::Modifier miningLaserOptimizationChargeBuff1_modifier2 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::capacitorNeed, AttributeID::warfareBuff1Multiplier, TypeID::gasCloudHarvesting};
			constexpr MetaInfo::Modifier miningLaserOptimizationChargeBuff1_modifier3 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::mining};
			constexpr MetaInfo::Modifier miningLaserOptimizationChargeBuff1_modifier4 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::iceHarvesting};
			constexpr MetaInfo::Modifier miningLaserOptimizationChargeBuff1_modifier5 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::duration, AttributeID::warfareBuff1Multiplier, TypeID::gasCloudHarvesting};
			constexpr auto miningLaserOptimizationChargeBuff1 = MakeBuff(WarfareBuffID::miningLaserOptimizationChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&miningLaserOptimizationChargeBuff1_modifier0,
																																											&miningLaserOptimizationChargeBuff1_modifier1,
																																											&miningLaserOptimizationChargeBuff1_modifier2,
																																											&miningLaserOptimizationChargeBuff1_modifier3,
																																											&miningLaserOptimizationChargeBuff1_modifier4,
																																											&miningLaserOptimizationChargeBuff1_modifier5));
			constexpr MetaInfo::Modifier miningEquipmentPreservationChargeBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::crystalVolatilityChance, AttributeID::warfareBuff1Multiplier, TypeID::mining};
			constexpr auto miningEquipmentPreservationChargeBuff1 = MakeBuff(WarfareBuffID::miningEquipmentPreservationChargeBuff1, AttributeID::warfareBuff1Multiplier, _modifiers(&miningEquipmentPreservationChargeBuff1_modifier0));
			constexpr MetaInfo::Modifier sensorOptimizationChargeBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxTargetRange, AttributeID::warfareBuff2Multiplier};
			constexpr auto sensorOptimizationChargeBuff2 = MakeBuff(WarfareBuffID::sensorOptimizationChargeBuff2, AttributeID::warfareBuff2Multiplier, _modifiers(&sensorOptimizationChargeBuff2_modifier0));
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::rechargeRate, AttributeID::warfareBuff1Value};
			constexpr auto amarrPhenomenaGeneratorBuff1 = MakeBuff(WarfareBuffID::amarrPhenomenaGeneratorBuff1, AttributeID::warfareBuff1Value, _modifiers(&amarrPhenomenaGeneratorBuff1_modifier0));
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorKineticDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff2_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldKineticDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff2_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::kineticDamageResonance, AttributeID::warfareBuff2Value};
			constexpr auto amarrPhenomenaGeneratorBuff2 = MakeBuff(WarfareBuffID::amarrPhenomenaGeneratorBuff2, AttributeID::warfareBuff2Value, _modifiers(&amarrPhenomenaGeneratorBuff2_modifier0,
																																						   &amarrPhenomenaGeneratorBuff2_modifier1,
																																						   &amarrPhenomenaGeneratorBuff2_modifier2));
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff3_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorEmDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff3_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldEmDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff3_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::emDamageResonance, AttributeID::warfareBuff3Value};
			constexpr auto amarrPhenomenaGeneratorBuff3 = MakeBuff(WarfareBuffID::amarrPhenomenaGeneratorBuff3, AttributeID::warfareBuff3Value, _modifiers(&amarrPhenomenaGeneratorBuff3_modifier0,
																																						   &amarrPhenomenaGeneratorBuff3_modifier1,
																																						   &amarrPhenomenaGeneratorBuff3_modifier2));
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorHP, AttributeID::warfareBuff1Value};
			constexpr auto gallentePhenomenaGeneratorBuff1 = MakeBuff(WarfareBuffID::gallentePhenomenaGeneratorBuff1, AttributeID::warfareBuff1Value, _modifiers(&gallentePhenomenaGeneratorBuff1_modifier0));
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorExplosiveDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff2_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldExplosiveDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff2_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::explosiveDamageResonance, AttributeID::warfareBuff2Value};
			constexpr auto gallentePhenomenaGeneratorBuff2 = MakeBuff(WarfareBuffID::gallentePhenomenaGeneratorBuff2, AttributeID::warfareBuff2Value, _modifiers(&gallentePhenomenaGeneratorBuff2_modifier0,
																																								 &gallentePhenomenaGeneratorBuff2_modifier1,
																																								 &gallentePhenomenaGeneratorBuff2_modifier2));
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff3_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorThermalDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff3_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldThermalDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff3_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::thermalDamageResonance, AttributeID::warfareBuff3Value};
			constexpr auto gallentePhenomenaGeneratorBuff3 = MakeBuff(WarfareBuffID::gallentePhenomenaGeneratorBuff3, AttributeID::warfareBuff3Value, _modifiers(&gallentePhenomenaGeneratorBuff3_modifier0,
																																								 &gallentePhenomenaGeneratorBuff3_modifier1,
																																								 &gallentePhenomenaGeneratorBuff3_modifier2));
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::signatureRadius, AttributeID::warfareBuff1Value};
			constexpr auto minmatarPhenomenaGeneratorBuff1 = MakeBuff(WarfareBuffID::minmatarPhenomenaGeneratorBuff1, AttributeID::warfareBuff1Value, _modifiers(&minmatarPhenomenaGeneratorBuff1_modifier0));
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorThermalDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff2_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldThermalDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff2_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::thermalDamageResonance, AttributeID::warfareBuff2Value};
			constexpr auto minmatarPhenomenaGeneratorBuff2 = MakeBuff(WarfareBuffID::minmatarPhenomenaGeneratorBuff2, AttributeID::warfareBuff2Value, _modifiers(&minmatarPhenomenaGeneratorBuff2_modifier0,
																																								 &minmatarPhenomenaGeneratorBuff2_modifier1,
																																								 &minmatarPhenomenaGeneratorBuff2_modifier2));
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff3_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorExplosiveDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff3_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldExplosiveDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff3_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::explosiveDamageResonance, AttributeID::warfareBuff3Value};
			constexpr auto minmatarPhenomenaGeneratorBuff3 = MakeBuff(WarfareBuffID::minmatarPhenomenaGeneratorBuff3, AttributeID::warfareBuff3Value, _modifiers(&minmatarPhenomenaGeneratorBuff3_modifier0,
																																								 &minmatarPhenomenaGeneratorBuff3_modifier1,
																																								 &minmatarPhenomenaGeneratorBuff3_modifier2));
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff1_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldCapacity, AttributeID::warfareBuff1Value};
			constexpr auto caldariPhenomenaGeneratorBuff1 = MakeBuff(WarfareBuffID::caldariPhenomenaGeneratorBuff1, AttributeID::warfareBuff1Value, _modifiers(&caldariPhenomenaGeneratorBuff1_modifier0));
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorEmDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff2_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldEmDamageResonance, AttributeID::warfareBuff2Value};
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff2_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::emDamageResonance, AttributeID::warfareBuff2Value};
			constexpr auto caldariPhenomenaGeneratorBuff2 = MakeBuff(WarfareBuffID::caldariPhenomenaGeneratorBuff2, AttributeID::warfareBuff2Value, _modifiers(&caldariPhenomenaGeneratorBuff2_modifier0,
																																							   &caldariPhenomenaGeneratorBuff2_modifier1,
																																							   &caldariPhenomenaGeneratorBuff2_modifier2));
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff3_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorKineticDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff3_modifier1 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldKineticDamageResonance, AttributeID::warfareBuff3Value};
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff3_modifier2 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::kineticDamageResonance, AttributeID::warfareBuff3Value};
			constexpr auto caldariPhenomenaGeneratorBuff3 = MakeBuff(WarfareBuffID::caldariPhenomenaGeneratorBuff3, AttributeID::warfareBuff3Value, _modifiers(&caldariPhenomenaGeneratorBuff3_modifier0,
																																							   &caldariPhenomenaGeneratorBuff3_modifier1,
																																							   &caldariPhenomenaGeneratorBuff3_modifier2));
			constexpr MetaInfo::Modifier amarrPhenomenaGeneratorBuff4_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxVelocity, AttributeID::warfareBuff4Value};
			constexpr auto amarrPhenomenaGeneratorBuff4 = MakeBuff(WarfareBuffID::amarrPhenomenaGeneratorBuff4, AttributeID::warfareBuff4Value, _modifiers(&amarrPhenomenaGeneratorBuff4_modifier0));
			constexpr MetaInfo::Modifier gallentePhenomenaGeneratorBuff4_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::shieldBonus, AttributeID::warfareBuff4Value, TypeID::shieldEmissionSystems};
			constexpr auto gallentePhenomenaGeneratorBuff4 = MakeBuff(WarfareBuffID::gallentePhenomenaGeneratorBuff4, AttributeID::warfareBuff4Value, _modifiers(&gallentePhenomenaGeneratorBuff4_modifier0));
			constexpr MetaInfo::Modifier caldariPhenomenaGeneratorBuff4_modifier0 = {MetaInfo::Modifier::ModifierType::locationRequiredSkill, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::armorDamageAmount, AttributeID::warfareBuff4Value, TypeID::remoteArmorRepairSystems};
			constexpr auto caldariPhenomenaGeneratorBuff4 = MakeBuff(WarfareBuffID::caldariPhenomenaGeneratorBuff4, AttributeID::warfareBuff4Value, _modifiers(&caldariPhenomenaGeneratorBuff4_modifier0));
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff4_modifier0 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff4Value, GroupID::energyWeapon};
			constexpr MetaInfo::Modifier minmatarPhenomenaGeneratorBuff4_modifier1 = {MetaInfo::Modifier::ModifierType::locationGroup, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::maxRange, AttributeID::warfareBuff4Value, GroupID::hybridWeapon};
			constexpr auto minmatarPhenomenaGeneratorBuff4 = MakeBuff(WarfareBuffID::minmatarPhenomenaGeneratorBuff4, AttributeID::warfareBuff4Value, _modifiers(&minmatarPhenomenaGeneratorBuff4_modifier0,
																																								 &minmatarPhenomenaGeneratorBuff4_modifier1));
			constexpr MetaInfo::Modifier evasiveManeuversChargeBuff2_modifier0 = {MetaInfo::Modifier::ModifierType::item, MetaInfo::Modifier::Association::postPercent, MetaInfo::Modifier::Domain::ship, AttributeID::agility, AttributeID::warfareBuff2Multiplier};
			constexpr auto evasiveManeuversChargeBuff2 = MakeBuff(WarfareBuffID::evasiveManeuversChargeBuff2, AttributeID::warfareBuff2Multiplier, _modifiers(&evasiveManeuversChargeBuff2_modifier0));
		}
		
		constexpr const MetaInfo::WarfareBuff* warfareBuffs[] {
			&WafrareBuffs::shieldHarmonizingChargeBuff1, &WafrareBuffs::activeShieldingChargeBuff1, &WafrareBuffs::shieldExtensionChargeBuff1, &WafrareBuffs::armorEnergizingChargeBuff1, &WafrareBuffs::rapidRepairChargeBuff1, &WafrareBuffs::armorReinforcementChargeBuff1, &WafrareBuffs::sensorOptimizationChargeBuff1, &WafrareBuffs::electronicSuperiorityChargeBuff1, &WafrareBuffs::electronicHardeningChargeBuff1, &WafrareBuffs::electronicHardeningChargeBuff2, &WafrareBuffs::evasiveManeuversChargeBuff1, &WafrareBuffs::interdictionManeuversChargeBuff1, &WafrareBuffs::rapidDeploymentChargeBuff1, &WafrareBuffs::miningLaserFieldEnhancementChargeBuff1, &WafrareBuffs::miningLaserOptimizationChargeBuff1, &WafrareBuffs::miningEquipmentPreservationChargeBuff1, &WafrareBuffs::sensorOptimizationChargeBuff2, &WafrareBuffs::amarrPhenomenaGeneratorBuff1, &WafrareBuffs::amarrPhenomenaGeneratorBuff2, &WafrareBuffs::amarrPhenomenaGeneratorBuff3, &WafrareBuffs::gallentePhenomenaGeneratorBuff1, &WafrareBuffs::gallentePhenomenaGeneratorBuff2, &WafrareBuffs::gallentePhenomenaGeneratorBuff3, &WafrareBuffs::minmatarPhenomenaGeneratorBuff1, &WafrareBuffs::minmatarPhenomenaGeneratorBuff2, &WafrareBuffs::minmatarPhenomenaGeneratorBuff3, &WafrareBuffs::caldariPhenomenaGeneratorBuff1, &WafrareBuffs::caldariPhenomenaGeneratorBuff2, &WafrareBuffs::caldariPhenomenaGeneratorBuff3, &WafrareBuffs::amarrPhenomenaGeneratorBuff4, &WafrareBuffs::gallentePhenomenaGeneratorBuff4, &WafrareBuffs::caldariPhenomenaGeneratorBuff4, &WafrareBuffs::minmatarPhenomenaGeneratorBuff4, &WafrareBuffs::evasiveManeuversChargeBuff2, };
	}
}

