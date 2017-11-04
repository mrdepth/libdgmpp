#pragma once
#include "Effect.h"
#include "Modifiers.hpp"

namespace dgmpp2 {
	namespace SDE {
		constexpr const Effect::MetaInfo effects[] {
			{EffectID::shieldBoosting, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[0]},
			}},
			{EffectID::missileLaunching, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::targetAttack, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::loPower, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::hiPower, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::medPower, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::online, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[1]},{modifiers[2]},
			}},
			{EffectID::mining, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::shieldTransfer, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[3]},
			}},
			{EffectID::shieldCapacityBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[4]},
			}},
			{EffectID::capacitorCapacityBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[5]},
			}},
			{EffectID::structureRepair, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[6]},
			}},
			{EffectID::armorRepair, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[7]},
			}},
			{EffectID::projectileFired, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::empWave, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::warpScramble, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[8]},
			}},
			{EffectID::launcherFitted, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[9]},
			}},
			{EffectID::turretFitted, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[10]},
			}},
			{EffectID::shipScan, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::cargoScan, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::powerBooster, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::modifyShieldRechargeRate, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[11]},
			}},
			{EffectID::modifyPowerRechargeRate, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[12]},
			}},
			{EffectID::targetPassively, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::targetHostiles, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::powerOutputMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[13]},
			}},
			{EffectID::shieldCapacityMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[14]},
			}},
			{EffectID::capacitorCapacityMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[15]},
			}},
			{EffectID::cargoCapacityMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[16]},
			}},
			{EffectID::structureHPMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[17]},
			}},
			{EffectID::agilityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[18]},
			}},
			{EffectID::armorHPMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[19]},
			}},
			{EffectID::miningLaser, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::surveyScan, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::corporationMemberLimitBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[20]},
			}},
			{EffectID::projectileWeaponSpeedMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[21]},
			}},
			{EffectID::energyWeaponDamageMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[22]},
			}},
			{EffectID::projectileWeaponDamageMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[23]},
			}},
			{EffectID::hybridWeaponDamageMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[24]},
			}},
			{EffectID::energyWeaponSpeedMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[25]},
			}},
			{EffectID::hybridWeaponSpeedMultiply, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[26]},
			}},
			{EffectID::useMissiles, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::mineLaying, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::defenderMissileLaunching, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::fofMissileLaunching, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::shieldResonanceMultiplyOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[27]},{modifiers[28]},{modifiers[29]},{modifiers[30]},
			}},
			{EffectID::electronicAttributeModifyOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[31]},{modifiers[32]},{modifiers[33]},
			}},
			{EffectID::torpedoLaunching, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::skillEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[34]},{modifiers[35]},
			}},
			{EffectID::damageMultiplierSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[36]},
			}},
			{EffectID::skillBoostDamageMultiplierBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[36]},
			}},
			{EffectID::largeHybridTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringLargeHybridTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[37]},
			}},
			{EffectID::mediumEnergyTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringMediumEnergyTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[38]},
			}},
			{EffectID::mediumHybridTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringMediumHybridTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[39]},
			}},
			{EffectID::mediumProjectileTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringMediumProjectileTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[40]},
			}},
			{EffectID::largeEnergyTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringLargeEnergyTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[41]},
			}},
			{EffectID::rapidFiringSkillBoostRofBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[42]},
			}},
			{EffectID::sharpshooterSkillBoostRangeSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[43]},
			}},
			{EffectID::smallEnergyTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringSmallEnergyTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[44]},
			}},
			{EffectID::smallHybridTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringSmallHybridTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[45]},
			}},
			{EffectID::smallProjectileTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringSmallProjectileTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[46]},
			}},
			{EffectID::caldariCruiserSkillBoostCcTRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[47]},
			}},
			{EffectID::caldariFrigateSkillBoostCfTRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[48]},
			}},
			{EffectID::signatureAnalysisSkillBoostScanspeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[49]},
			}},
			{EffectID::signatureAnalysisScanspeedBonusPostPercentScanSpeedLocationShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[50]},
			}},
			{EffectID::longRangeTargetingSkillBoostMaxTargetRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[51]},
			}},
			{EffectID::propulsionJammingSkillBoostDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[52]},
			}},
			{EffectID::sensorUpgradesSkillBoostCpuNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[53]},
			}},
			{EffectID::sensorUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringSensorUpgrades, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[54]},
			}},
			{EffectID::targetingSkillBoostMaxTargetBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[55]},
			}},
			{EffectID::targetingMaxTargetBonusModAddMaxLockedTargetsLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[56]},
			}},
			{EffectID::electronicWarfareSkillBoostDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[57]},
			}},
			{EffectID::engineeringSkillBoostPowerOutputBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[58]},
			}},
			{EffectID::energyManagementSkillBoostCapRechargeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[59]},
			}},
			{EffectID::navigationSkillBoostVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[60]},
			}},
			{EffectID::navigationVelocityBonusPostPercentMaxVelocityLocationShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[61]},
			}},
			{EffectID::accerationControlSkillBoostCapNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[62]},
			}},
			{EffectID::accerationControlCapNeedBonusPostPercentCapacitorNeedLocationShipGroupAfterburner, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[63]},
			}},
			{EffectID::accerationControlSkillBoostSpeedFBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[64]},
			}},
			{EffectID::afterburnerDurationBonusPostPercentDurationLocationShipModulesRequiringAfterburner, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[65]},
			}},
			{EffectID::evasiveManuveringSkillBoostAgilityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[66]},
			}},
			{EffectID::warpdriveoperationSkillBoostWarpCapacitorNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[67]},
			}},
			{EffectID::warpdriveoperationWarpCapacitorNeedBonusPostPercentWarpCapacitorNeedLocationShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[68]},
			}},
			{EffectID::corporationManagementSkillBoostCorporationMemberBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[69]},
			}},
			{EffectID::accerationControlSpeedFBonusPostPercentSpeedFactorLocationShipGroupAfterburner, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[70]},
			}},
			{EffectID::highSpeedManuveringSkillBoostCapacitorNeedMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[71]},
			}},
			{EffectID::highSpeedManuveringCapacitorNeedMultiplierPostPercentCapacitorNeedLocationShipModulesRequiringHighSpeedManuvering, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[72]},
			}},
			{EffectID::sensorUpgradesSkillBoostPowerNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[73]},
			}},
			{EffectID::hullUpgradesSkillBoostHullHpBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[74]},
			}},
			{EffectID::shadowBarrageDmgMultiplierWithDamageMultiplierPostPercentBarrageDmgMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[75]},{modifiers[76]},
			}},
			{EffectID::shadowBarrageFalloffWithFalloffPostPercentBarrageFalloffMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[77]},{modifiers[78]},
			}},
			{EffectID::barrage, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::amarrCruiserSkillBoostPowerOutputBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[79]},
			}},
			{EffectID::hullUpgradesSkillBoostArmorHpBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[80]},
			}},
			{EffectID::hullUpgradesArmorHpBonusPostPercentHpLocationShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[81]},
			}},
			{EffectID::repairSystemsDurationBonusPostPercentDurationLocationShipModulesRequiringRepairSystems, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[82]},
			}},
			{EffectID::shieldUpgradesPowerNeedBonusPostPercentPowerLocationShipModulesRequiringShieldUpgrades, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[83]},
			}},
			{EffectID::tacticalshieldManipulationSkillBoostUniformityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[84]},
			}},
			{EffectID::shieldEmmisionSystemsCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringShieldEmmisionSystems, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[85]},
			}},
			{EffectID::shieldManagementSkillBoostShieldCapacityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[86]},
			}},
			{EffectID::shieldoperationSkillBoostRechargeratebonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[87]},
			}},
			{EffectID::controlledBurstsCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[88]},
			}},
			{EffectID::motionPredictionTrackingSpeedMultiplierPostPercentTrackingSpeedLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[89]},
			}},
			{EffectID::sharpshooterRangeSkillBonusPostPercentMaxRangeLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[90]},
			}},
			{EffectID::skillBoostFalloffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[91]},
			}},
			{EffectID::surgicalStrikeFalloffBonusPostPercentFalloffLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[92]},
			}},
			{EffectID::empathyCharismaBonusModAddCharismaLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[93]},
			}},
			{EffectID::instantRecallMemoryBonusModAddMemoryLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[94]},
			}},
			{EffectID::analyticalMindIntelligenceBonusModAddIntelligenceLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[95]},
			}},
			{EffectID::ironWillWillpowerBonusModAddWillpowerLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[96]},
			}},
			{EffectID::spatialAwarenessPerceptionBonusModAddPerceptionLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[97]},
			}},
			{EffectID::dronesSkillBoostMaxActiveDroneBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[98]},
			}},
			{EffectID::dronesMaxActiveDroneBonusModAddMaxActiveLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[99]},
			}},
			{EffectID::amarrTechSkillBoostAmarrTechMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[100]},
			}},
			{EffectID::amarrTechAmarrTechMutatorPostPercentAmarrTechTimePercentLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[101]},
			}},
			{EffectID::caldariTechSkillBoostCaldariTechMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[102]},
			}},
			{EffectID::caldariTechCaldariTechMutatorPostPercentCaldariTechTimePercentLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[103]},
			}},
			{EffectID::gallenteTechSkillBoostGallenteTechMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[104]},
			}},
			{EffectID::gallenteTechGallenteTechMutatorPostPercentGallenteTechTimePercentLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[105]},
			}},
			{EffectID::refineryEfficiencySkillBoostRefiningYieldMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[106]},
			}},
			{EffectID::cSOTrainingSkillBoostResearchGangSizeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[107]},
			}},
			{EffectID::cSOTrainingResearchGangSizeBonusModAddMaxResearchGangSizeShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[108]},
			}},
			{EffectID::battleshipConstructionSkillBoostBattleshipConstructionTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[109]},
			}},
			{EffectID::battleshipConstructionBattleshipConstructionTimeBonusPostPercentBattleshipConstructionTimeChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[110]},
			}},
			{EffectID::cruiserConstructionSkillBoostCruiserConstructionTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[111]},
			}},
			{EffectID::cruiserConstructionCruiserConstructionTimeBonusPostPercentCruiserConstructionTimeChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[112]},
			}},
			{EffectID::frigateConstructionSkillBoostFrigateConstructionTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[113]},
			}},
			{EffectID::frigateConstructionFrigateConstructionTimeBonusPostPercentFrigateConstructionTimeChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[114]},
			}},
			{EffectID::industrialConstructionSkillBoostIndustrialConstructionTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[115]},
			}},
			{EffectID::industrialConstructionIndustrialConstructionTimeBonusPostPercentIndustrialConstructionTimeChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[116]},
			}},
			{EffectID::connectionsSkillBoostConnectionBonusMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[117]},
			}},
			{EffectID::criminalConnectionsSkillBoostCriminalConnectionsMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[118]},
			}},
			{EffectID::diplomacySkillBoostDiplomacyMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[119]},
			}},
			{EffectID::diplomacyDiplomacyMutatorModAddDiplomacyBonusChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[120]},
			}},
			{EffectID::fasttalkSkillBoostFastTalkMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[121]},
			}},
			{EffectID::fasttalkFastTalkMutatorPostPercentFastTalkPercentageChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[122]},
			}},
			{EffectID::gallenteFrigateSkillBoostCpuOutputBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[123]},
			}},
			{EffectID::astrogeologySkillBoostMiningAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[124]},
			}},
			{EffectID::astrogeologyMiningAmountBonusPostPercentMiningAmountLocationShipModulesRequiringMining, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[125]},
			}},
			{EffectID::mechanicHullHpBonusPostPercentHpShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[126]},
			}},
			{EffectID::navigationVelocityBonusPostPercentMaxVelocityShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[61]},
			}},
			{EffectID::evasiveManeuveringAgilityBonusPostPercentAgilityShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[127]},
			}},
			{EffectID::energyGridUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringEnergyGridUpgrades, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[128]},
			}},
			{EffectID::electronicsCpuOutputBonusPostPercentCpuOutputLocationShipGroupComputer, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[129]},
			}},
			{EffectID::connectionsConnectionBonusMutatorModAddConnectionsBonusChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[130]},
			}},
			{EffectID::criminalConnectionsCriminalConnectionsMutatorModAddCriminalConnectionsBonusChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[131]},
			}},
			{EffectID::negotiationSkillBoostNegotiationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[132]},
			}},
			{EffectID::negotiationNegotiationBonusPostPercentNegotiationPercentageChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[133]},
			}},
			{EffectID::socialSkillBoostSocialMutator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[134]},
			}},
			{EffectID::socialSocialMutatorPostPercentSocialBonusChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[135]},
			}},
			{EffectID::largeProjectileTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringLargeProjectileTurret, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[136]},
			}},
			{EffectID::industrySkillBoostManufacturingTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[137]},
			}},
			{EffectID::gunnerySkillBoostTurretSpeeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[138]},
			}},
			{EffectID::gunneryTurretSpeeBonusPostPercentSpeedLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[139]},
			}},
			{EffectID::tradeSkillBoostTradePremiumBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[140]},
			}},
			{EffectID::tradeTradePremiumBonusPostPercentTradePremiumChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[141]},
			}},
			{EffectID::smugglingSkillBoostSmugglingChanceBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[142]},
			}},
			{EffectID::industryManufacturingTimeBonusPostPercentManufactureTimeMultiplierChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[143]},
			}},
			{EffectID::scienceSkillBoostCopySpeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[144]},
			}},
			{EffectID::scienceCopySpeedBonusPostPercentCopySpeedPercentChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[145]},
			}},
			{EffectID::researchSkillBoostBlueprintmanufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[146]},
			}},
			{EffectID::researchBlueprintmanufactureTimeBonusPostPercentProductionTimeResearchSpeedChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[147]},
			}},
			{EffectID::refineryEfficiencyRefiningYieldMutatorPostPercentRefiningYieldPercentageChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[148]},
			}},
			{EffectID::missileLauncherOperationSpeedBonusPostPercentSpeedLocationShipModulesRequiringMissileLauncherOperation, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[149]},
			}},
			{EffectID::energyManagementCapacitorBonusPostPercentCapacityLocationShipGroupCapacitor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[150]},
			}},
			{EffectID::shieldManagementShieldCapacityBonusPostPercentCapacityLocationShipGroupShield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[151]},
			}},
			{EffectID::scoutDroneOperationSkillBoostDroneRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[152]},
			}},
			{EffectID::minmatarFrigateSkillLevelPreMulShipBonusMFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[153]},
			}},
			{EffectID::shipTargetRangeBonusMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[154]},
			}},
			{EffectID::caldariFrigateSkillLevelPreMulShipBonusCFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[155]},
			}},
			{EffectID::shipShieldCapBonusCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[156]},
			}},
			{EffectID::gallenteFrigateSkillLevelPreMulShipBonusGFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[157]},
			}},
			{EffectID::amarrFrigateSkillLevelPreMulShipBonusAFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[158]},
			}},
			{EffectID::metallurgySkillBoostMineralNeedResearchBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[159]},
			}},
			{EffectID::energysystemsoperationCapRechargeBonusPostPercentRechargeRateLocationShipGroupCapacitor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[160]},
			}},
			{EffectID::shieldOperationRechargeratebonusPostPercentRechargeRateLocationShipGroupShield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[161]},
			}},
			{EffectID::engineeringPowerEngineeringOutputBonusPostPercentPowerOutputLocationShipGroupPowerCore, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[162]},
			}},
			{EffectID::warpDriveOperationWarpCapacitorNeedBonusPostPercentWarpCapacitorNeedLocationShipGroupPropulsion, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[68]},
			}},
			{EffectID::inventionSkillBoostInventionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[163]},
			}},
			{EffectID::amarrCruiserSkillLevelPreMulShipBonusACShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[164]},
			}},
			{EffectID::scoutDroneOperationDroneRangeBonusModAddDroneControlDistanceChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[165]},
			}},
			{EffectID::fuelConservationCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringAfterburner, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[166]},
			}},
			{EffectID::longRangeTargetingMaxTargetRangeBonusPostPercentMaxTargetRangeLocationShipGroupElectronic, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[167]},
			}},
			{EffectID::shipPDmgBonusMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[168]},
			}},
			{EffectID::amarrFrigateSkillLevelPreMulShipBonus2AFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[169]},
			}},
			{EffectID::shipEnergyTCapNeedBonusAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[170]},
			}},
			{EffectID::shipSHTDmgBonusGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[171]},
			}},
			{EffectID::shipSETDmgBonusAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[172]},
			}},
			{EffectID::shipTCapNeedBonusAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[173]},
			}},
			{EffectID::gallenteCruiserSkillLevelPreMulShipBonusGCShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[174]},
			}},
			{EffectID::caldariCruiserSkillLevelPreMulShipBonusCCShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[175]},
			}},
			{EffectID::shipHRangeBonusCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[176]},
			}},
			{EffectID::minmatarCruiserSkillLevelPreMulShipBonusMCShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[177]},
			}},
			{EffectID::minmatarIndustrialSkillLevelPreMulShipBonusMIShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[178]},
			}},
			{EffectID::shipVelocityBonusMI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[179]},
			}},
			{EffectID::shipCargoBonusAI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[180]},
			}},
			{EffectID::caldariIndustrialSkillLevelPreMulShipBonusCIShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[181]},
			}},
			{EffectID::gallenteIndustrialSkillLevelPreMulShipBonusGIShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[182]},
			}},
			{EffectID::cpuMultiplierPostMulCpuOutputShip, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[183]},
			}},
			{EffectID::amarrBattleshipSkillLevelPostMulShipBonusABShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[184]},
			}},
			{EffectID::caldariBattleshipSkillLevelPreMulShipBonusCBShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[185]},
			}},
			{EffectID::shipCapNeedBonusAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[186]},
			}},
			{EffectID::minmatarBattleshipSkillLevelPreMulShipBonusMBShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[187]},
			}},
			{EffectID::shipPTDmgBonusMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[188]},
			}},
			{EffectID::shipHTDmgBonusGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[189]},
			}},
			{EffectID::shipHTTrackingBonusGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[190]},
			}},
			{EffectID::caldariBattleshipSkillLevelPreMulShipBonus2CBShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[191]},
			}},
			{EffectID::metallurgyMineralNeedResearchBonusPostPercentMineralNeedResearchSpeedChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[192]},
			}},
			{EffectID::shipHTDmgBonusfixedGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[193]},
			}},
			{EffectID::laboratoryOperationSkillLevelModAddMaxLaborotorySlotsChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[194]},
			}},
			{EffectID::massProductionSkillLevelModAddManufactureSlotLimitChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[195]},
			}},
			{EffectID::missileLaunchingForEntity, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::reverseEngineeringInventionBonusModAddReverseEngineeringChanceLocationChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[196]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[197]},
			}},
			{EffectID::rapidFiringRofBonusPostPercentSpeedLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[198]},
			}},
			{EffectID::amarrIndustrialSkillLevelPreMulShipBonusAI2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[199]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringGunnery, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[200]},
			}},
			{EffectID::decreaseTargetSpeed, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[201]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipGroupEnergyWeapon, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[202]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipGroupProjectileWeapon, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[203]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipGroupHybridWeapon, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[204]},
			}},
			{EffectID::energyPulseWeaponsDurationBonusPostPercentDurationLocationShipModulesRequiringEnergyPulseWeapons, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[205]},
			}},
			{EffectID::targetArmorRepair, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[206]},
			}},
			{EffectID::ammoInfluenceRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[207]},
			}},
			{EffectID::ammoSpeedMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[208]},
			}},
			{EffectID::ammoFallofMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[209]},
			}},
			{EffectID::ammoTrackingMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[210]},
			}},
			{EffectID::shipPTurretSpeedBonusMC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[211]},
			}},
			{EffectID::shipPTspeedBonusMB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[212]},
			}},
			{EffectID::minmatarBattleshipSkillLevelPreMulShipBonusMB2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[213]},
			}},
			{EffectID::cloaking, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[214]},
			}},
			{EffectID::gallenteBattleshipSkillLevelPreMulShipBonusGBShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[215]},
			}},
			{EffectID::miningDroneOperationMiningAmountBonusPostPercentMiningDroneAmountPercentChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[216]},
			}},
			{EffectID::powerIncrease, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[217]},
			}},
			{EffectID::shipSpecialityMining, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[218]},
			}},
			{EffectID::anchorDrop, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::anchorLift, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::cloakingSkillBoostCloakVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[219]},
			}},
			{EffectID::agilityMultiplierEffect, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[220]},
			}},
			{EffectID::missileEMDmgBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[221]},
			}},
			{EffectID::missileExplosiveDmgBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[222]},
			}},
			{EffectID::missileThermalDmgBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[223]},
			}},
			{EffectID::heavyMissilesSkillBoostMaxflightTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[224]},
			}},
			{EffectID::missileKineticDmgBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[225]},
			}},
			{EffectID::antiWarpScramblingPassive, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[226]},
			}},
			{EffectID::weaponUpgradesSkillBoostCpu, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[227]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringEnergyPulseWeapons, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[228]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringMissileLauncherOperation, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[229]},
			}},
			{EffectID::gallenteBattleshipSkillLevelPreMulShipBonusGB2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[230]},
			}},
			{EffectID::signatureAnalysisSkillLevelPreMulScanResolutionBonusSelf, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[231]},
			}},
			{EffectID::signatureAnalysisScanResolutionBonusPostPercentScanResolutionShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[232]},
			}},
			{EffectID::interceptorsSkillLevelPreMulEliteBonusInterceptorShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[233]},
			}},
			{EffectID::covertOpsSkillLevelPreMulEliteBonusCoverOpsShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[234]},
			}},
			{EffectID::covertOpsWarpResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[235]},
			}},
			{EffectID::bomberRocketRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[236]},
			}},
			{EffectID::bomberLightsRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[237]},
			}},
			{EffectID::interceptorSignatoreRadiusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[238]},
			}},
			{EffectID::speedBoostFactorCalculator, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[239]},{modifiers[240]},
			}},
			{EffectID::speedBoostFactorCalculator2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[241]},
			}},
			{EffectID::stealthActive, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[242]},
			}},
			{EffectID::shipBonusCargo2GI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[243]},
			}},
			{EffectID::shipBonusCargoCI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[244]},
			}},
			{EffectID::shipBonusCargoMI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[245]},
			}},
			{EffectID::shipBonusVelocityGI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[246]},
			}},
			{EffectID::shipBonusVelocityCI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[247]},
			}},
			{EffectID::shipVelocityBonusAI, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[248]},
			}},
			{EffectID::amarrBattleshipSkillLevelPreMulShipBonusAB2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[249]},
			}},
			{EffectID::shipBonusCapCapAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[250]},
			}},
			{EffectID::surveyScanspeedBonusPostPercentDurationLocationShipModulesRequiringElectronics, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[251]},
			}},
			{EffectID::gallenteFrigateSkillLevelPreMulShipBonusGF2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[252]},
			}},
			{EffectID::shipHybridDamageBonusCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[253]},
			}},
			{EffectID::shipETDamageAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[172]},
			}},
			{EffectID::shipBonusSmallMissileRoFCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[254]},{modifiers[255]},
			}},
			{EffectID::caldariFrigateSkillLevelPreMulShipBonusCF2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[256]},
			}},
			{EffectID::minmatarFrigateSkillLevelPreMulShipBonusMF2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[257]},
			}},
			{EffectID::missileDMGBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[258]},
			}},
			{EffectID::hypereuclideanNavigationCloakVelocityBonusModAddSpeedFactorLocationShipModulesRequiringCloaking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[259]},
			}},
			{EffectID::missileBombardmentMaxFlightTimeBonusPostPercentExplosionDelayOwnerCharModulesRequiringMissileLauncherOperation, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[260]},
			}},
			{EffectID::escortHullUpgradeCpuBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[261]},
			}},
			{EffectID::escortShieldUpgradeCpuBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[262]},
			}},
			{EffectID::caldariBattleshipSkillLevelPreMulShipBonusCB3Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[263]},
			}},
			{EffectID::ammoInfluenceCapNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[264]},
			}},
			{EffectID::ammoInfluenceCapRecharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[12]},
			}},
			{EffectID::freightSkillBoostCargoCapacityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[265]},
			}},
			{EffectID::skillFreightBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[266]},
			}},
			{EffectID::ammoInfluenceShipVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[214]},
			}},
			{EffectID::cloakingTargetingDelayBonusPostPercentCloakingTargetingDelayBonusForShipModulesRequiringCloaking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[267]},
			}},
			{EffectID::cloakingSkillBoostCloakingTargetingDelayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[268]},
			}},
			{EffectID::cloakingScanResolutionMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[269]},
			}},
			{EffectID::warpSkillSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[270]},
			}},
			{EffectID::bountyHuntingSkillBoostBountySkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[271]},
			}},
			{EffectID::bountyhunterskill, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[272]},
			}},
			{EffectID::shipProjectileOptimalBonuseMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[273]},
			}},
			{EffectID::shipHybridRangeBonusCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[274]},
			}},
			{EffectID::shipETspeedBonusAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[275]},
			}},
			{EffectID::missileLauncherSpeedMultiplier, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[276]},
			}},
			{EffectID::shipCruiseMissileVelocityBonusCB3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[277]},
			}},
			{EffectID::shipTorpedosVelocityBonusCB3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[278]},
			}},
			{EffectID::covertOpsCpuBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[279]},
			}},
			{EffectID::shipMissileKineticDamageCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[280]},
			}},
			{EffectID::shipMissileKineticDamageCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[281]},
			}},
			{EffectID::shipDroneScoutThermalDamageGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[282]},
			}},
			{EffectID::onlineForStructures, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::ammoInfluenceSignatureRadius, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[283]},
			}},
			{EffectID::ammoInfluenceShieldCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[14]},
			}},
			{EffectID::shipLaserRofAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[284]},
			}},
			{EffectID::shipArmorHpAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[285]},
			}},
			{EffectID::shipMissileLauncherRofCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[286]},
			}},
			{EffectID::shipDronesMaxGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[287]},
			}},
			{EffectID::shipHybridTrackingGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[288]},
			}},
			{EffectID::amarrCruiserSkillLevelPreMulShipBonusAC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[289]},
			}},
			{EffectID::caldariCruiserSkillLevelPreMulShipBonusCC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[290]},
			}},
			{EffectID::gallenteCruiserSkillLevelPreMulShipBonusGC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[291]},
			}},
			{EffectID::minmatarCruiserSkillLevelPreMulShipBonusMC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[292]},
			}},
			{EffectID::shipArmorEmResistanceAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[293]},
			}},
			{EffectID::shipArmorExplosiveResistanceAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[294]},
			}},
			{EffectID::shipArmorKineticResistanceAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[295]},
			}},
			{EffectID::shipArmorThermalResistanceAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[296]},
			}},
			{EffectID::shipProjectileDmgMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[297]},
			}},
			{EffectID::cloakingWarpSafe, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[214]},
			}},
			{EffectID::gunshipSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[298]},
			}},
			{EffectID::gunshipSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[299]},
			}},
			{EffectID::eliteBonusGunshipHybridOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[300]},
			}},
			{EffectID::eliteBonusGunshipProjectileOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[301]},
			}},
			{EffectID::eliteBonusGunshipLaserOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[302]},
			}},
			{EffectID::eliteBonusGunshipHybridTracking2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[303]},
			}},
			{EffectID::eliteBonusGunshipProjectileFalloff2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[304]},
			}},
			{EffectID::eliteBonusGunshipShieldBoost2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[305]},
			}},
			{EffectID::eliteBonusGunshipCapRecharge2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[306]},
			}},
			{EffectID::eliteBonusGunshipDroneCapacity2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[307]},
			}},
			{EffectID::selfT2SmallLaserPulseDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[308]},
			}},
			{EffectID::selfT2SmallLaserBeamDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[309]},
			}},
			{EffectID::selfT2SmallHybridBlasterDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[310]},
			}},
			{EffectID::selfT2SmallHybridRailDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[311]},
			}},
			{EffectID::selfT2SmallProjectileACDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[312]},
			}},
			{EffectID::selfT2SmallProjectileArtyDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[313]},
			}},
			{EffectID::selfT2MediumLaserPulseDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[314]},
			}},
			{EffectID::selfT2MediumLaserBeamDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[315]},
			}},
			{EffectID::selfT2MediumHybridBlasterDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[316]},
			}},
			{EffectID::selfT2MediumHybridRailDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[317]},
			}},
			{EffectID::selfT2MediumProjectileACDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[318]},
			}},
			{EffectID::selfT2MediumProjectileArtyDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[319]},
			}},
			{EffectID::selfT2LargeLaserPulseDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[320]},
			}},
			{EffectID::selfT2LargeLaserBeamDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[321]},
			}},
			{EffectID::selfT2LargeHybridBlasterDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[322]},
			}},
			{EffectID::selfT2LargeHybridRailDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[323]},
			}},
			{EffectID::selfT2LargeProjectileACDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[324]},
			}},
			{EffectID::selfT2LargeProjectileArtyDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[325]},
			}},
			{EffectID::eliteBonusGunshipHybridDmg2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[326]},
			}},
			{EffectID::anchorDropForStructures, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::anchorLiftForStructures, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::shipMissileHeavyVelocityBonusCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[327]},
			}},
			{EffectID::shipMissileLightVelocityBonusCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[328]},
			}},
			{EffectID::remoteArmorSystemsCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringRemoteArmorSystems, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[329]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairCapNeed1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[330]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairCapNeed2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[331]},
			}},
			{EffectID::eliteBonusLogisticShieldTransferCapNeed2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[332]},
			}},
			{EffectID::eliteBonusLogisticShieldTransferCapNeed1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[333]},
			}},
			{EffectID::shipRemoteArmorRangeGC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[334]},
			}},
			{EffectID::shipRemoteArmorRangeAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[335]},
			}},
			{EffectID::shipShieldTransferRangeCC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[336]},
			}},
			{EffectID::shipShieldTransferRangeMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[337]},
			}},
			{EffectID::logisticSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[338]},
			}},
			{EffectID::logisticSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[339]},
			}},
			{EffectID::eliteBonusHeavyGunshipHybridOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[340]},
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[341]},
			}},
			{EffectID::eliteBonusHeavyGunshipLaserOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[342]},
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileFallOff1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[343]},
			}},
			{EffectID::eliteBonusHeavyGunshipHybridDmg2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[344]},
			}},
			{EffectID::eliteBonusHeavyGunshipLaserDmg2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[345]},
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileTracking2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[346]},
			}},
			{EffectID::warshipSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[347]},
			}},
			{EffectID::warshipSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[348]},
			}},
			{EffectID::eliteBonusHeavyGunshipHybridFallOff1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[349]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyMissileFlightTime1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[350]},
			}},
			{EffectID::eliteBonusHeavyGunshipLightMissileFlightTime1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[351]},
			}},
			{EffectID::eliteBonusHeavyGunshipDroneControlRange1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[352]},
			}},
			{EffectID::projectileFiredForEntities, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileDmg2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[353]},
			}},
			{EffectID::shipProjectileTrackingMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[354]},
			}},
			{EffectID::controlTowerAmarrLaserDMGBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[355]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[356]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[357]},
			}},
			{EffectID::structureUnanchorForced, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::controlTowerAmarrLaserOptimalBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[358]},
			}},
			{EffectID::controlTowerSiloCapacityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[359]},
			}},
			{EffectID::controlTowerMinmatarProjectileOptimalBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[360]},
			}},
			{EffectID::controlTowerMinmatarProjectileFallOffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[361]},
			}},
			{EffectID::controlTowerMinmatarProjectileRofBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[362]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusDF2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[363]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusDF1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[364]},
			}},
			{EffectID::controlTowerGallenteHybridDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[365]},
			}},
			{EffectID::controlTowerTrackingArrayHybridOptimalBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[366]},
			}},
			{EffectID::controlTowerTrackingArrayLaserOptimalBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[367]},
			}},
			{EffectID::controlTowerTrackingArrayProjectileOptimalBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[368]},
			}},
			{EffectID::controlTowerTrackingArrayProjectileTrackingBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[369]},
			}},
			{EffectID::controlTowerTrackingArrayHybridTrackingBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[370]},
			}},
			{EffectID::controlTowerTrackingArrayLaserTrackingBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[371]},
			}},
			{EffectID::massFactor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[372]},
			}},
			{EffectID::ammoInfluenceEntityFlyRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[373]},
			}},
			{EffectID::accerationControlSkillAbMwdSpeedBoost, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[70]},{modifiers[374]},
			}},
			{EffectID::eliteBonusGunshipLaserDamage2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[375]},
			}},
			{EffectID::eliteBonusLogisticEnergyTransferCapNeed1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[376]},
			}},
			{EffectID::shipEnergyTransferRange1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[377]},
			}},
			{EffectID::eliteBonusLogisticEnergyTransferCapNeed2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[378]},
			}},
			{EffectID::shipEnergyTransferRange2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[379]},
			}},
			{EffectID::structureStealthEmitterArraySigDecrease, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[380]},
			}},
			{EffectID::miningBargeSkillLevelPostMulShipBonusORE2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[381]},
			}},
			{EffectID::iceHarvestCycleTimeModulesRequiringIceHarvesting, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[382]},
			}},
			{EffectID::iceHarvestCycleTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[383]},
			}},
			{EffectID::controlTowerCaldariEwTargetSwitchDelayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[384]},
			}},
			{EffectID::targetAttackForStructures, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::miningInfoMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[385]},
			}},
			{EffectID::controlTowerCaldariMissileVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[386]},
			}},
			{EffectID::controlTowerCaldariMissileRofBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[387]},
			}},
			{EffectID::crystalMiningamountInfo2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[388]},
			}},
			{EffectID::shipEnergyDrainAmountAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[389]},
			}},
			{EffectID::shipBonusPirateSmallHybridDmg, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[390]},
			}},
			{EffectID::shipEnergyVampireTransferAmountBonusAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[391]},
			}},
			{EffectID::shipEnergyVampireTransferAmountBonusAc, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[392]},
			}},
			{EffectID::shipStasisWebRangeBonusMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[393]},
			}},
			{EffectID::shipStasisWebRangeBonusMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[394]},
			}},
			{EffectID::shipProjectileTrackingGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[395]},
			}},
			{EffectID::shipMissileVelocityPirateFactionFrigate, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[396]},
			}},
			{EffectID::shipProjectileRofPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[397]},
			}},
			{EffectID::shipHybridDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[398]},
			}},
			{EffectID::shipMissileVelocityPirateFactionLight, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[399]},
			}},
			{EffectID::shipProjectileRofPirateBattleship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[400]},
			}},
			{EffectID::shipHybridDmgPirateBattleship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[401]},
			}},
			{EffectID::smugglingModifier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[402]},
			}},
			{EffectID::setBonusBloodraider, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[403]},
			}},
			{EffectID::setBonusBloodraiderNosferatu, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[404]},
			}},
			{EffectID::blackMarketTradingSkillBoostContrabandDetectionChanceBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[405]},
			}},
			{EffectID::skillBoostContrabandDetectionChanceBonusEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[406]},
			}},
			{EffectID::setBonusSerpentis, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[407]},
			}},
			{EffectID::setBonusSerpentis2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[408]},
			}},
			{EffectID::interceptor2HybridTracking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[409]},
			}},
			{EffectID::interceptor2LaserTracking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[410]},
			}},
			{EffectID::interceptors2SkillLevelPreMulEliteBonusInterceptorShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[411]},
			}},
			{EffectID::structuralAnalysisEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[412]},
			}},
			{EffectID::eliteIndustrial1SkillLevelPreMulEliteBonusEliteIndustrialShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[413]},
			}},
			{EffectID::eliteIndustrial2SkillLevelPreMulEliteBonusEliteIndustrialShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[414]},
			}},
			{EffectID::amarrIndustrialSkillLevelPreMulShipBonusAI22Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[415]},
			}},
			{EffectID::caldariIndustrialSkillLevelPreMulShipBonusCI2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[416]},
			}},
			{EffectID::gallenteIndustrialSkillLevelPreMulShipBonusGI2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[417]},
			}},
			{EffectID::minmatarIndustrialSkillLevelPreMulShipBonusMI2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[418]},
			}},
			{EffectID::ewSkillScanStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[419]},{modifiers[420]},{modifiers[421]},{modifiers[422]},
			}},
			{EffectID::ewSkillScanStrengthBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[423]},
			}},
			{EffectID::propulsionSkillPropulsionStrengthBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[424]},
			}},
			{EffectID::ewSkillRsdCapNeedBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[425]},
			}},
			{EffectID::ewSkillTdCapNeedBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[426]},
			}},
			{EffectID::ewSkillTpCapNeedBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[427]},
			}},
			{EffectID::ewSkillEwCapNeedSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[428]},
			}},
			{EffectID::ewSkillTargetPaintingStrengthBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[429]},
			}},
			{EffectID::leadershipCpuBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[430]},
			}},
			{EffectID::shieldBoostAmplifierPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[431]},
			}},
			{EffectID::setBonusGuristas, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[432]},
			}},
			{EffectID::covertOpsSkillLevelPreMulEliteBonusCoverOpsShip2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[433]},
			}},
			{EffectID::systemScanDurationSkillAstrometrics, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[434]},
			}},
			{EffectID::propulsionSkillCapNeedBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[435]},
			}},
			{EffectID::shipBonusHybridOptimalCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[436]},
			}},
			{EffectID::caldariShipEwStrengthCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[437]},{modifiers[438]},{modifiers[439]},{modifiers[440]},
			}},
			{EffectID::caldariShipEwOptimalRangeCB3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[441]},
			}},
			{EffectID::caldariShipEwOptimalRangeCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[442]},
			}},
			{EffectID::caldariShipEwCapacitorNeedCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[443]},
			}},
			{EffectID::ewSkillRsdMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[444]},
			}},
			{EffectID::ewSkillTpMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[445]},
			}},
			{EffectID::ewSkillTdMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[446]},
			}},
			{EffectID::ewSkillRsdFallOffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[447]},
			}},
			{EffectID::ewSkillTpFallOffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[448]},
			}},
			{EffectID::ewSkillTdFallOffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[449]},
			}},
			{EffectID::ewSkillEwMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[450]},
			}},
			{EffectID::ewSkillEwFallOffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[451]},
			}},
			{EffectID::missileSkillAoeVelocityBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[452]},
			}},
			{EffectID::missileSkillAoeCloudSizeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[453]},
			}},
			{EffectID::missileSkillAoeCloudSizeBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[454]},
			}},
			{EffectID::contrabandMasking, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[242]},{modifiers[406]},
			}},
			{EffectID::flagshipmultiRelayEffect, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[455]},
			}},
			{EffectID::shieldOperationSkillBoostCapacitorNeedBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[456]},
			}},
			{EffectID::shieldOperationSkillBoostCapacitorNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[457]},
			}},
			{EffectID::ewTargetPaint, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[458]},
			}},
			{EffectID::ewSkillTargetPaintingStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[459]},
			}},
			{EffectID::minmatarShipEwTargetPainterMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[460]},
			}},
			{EffectID::angelsetbonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[461]},
			}},
			{EffectID::setBonusSansha, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[462]},
			}},
			{EffectID::jumpDriveSkillsRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[463]},
			}},
			{EffectID::jumpDriveSkillsRangeBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[464]},
			}},
			{EffectID::capitalTurretSkillLaserDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[465]},
			}},
			{EffectID::capitalTurretSkillProjectileDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[466]},
			}},
			{EffectID::capitalTurretSkillHybridDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[467]},
			}},
			{EffectID::capitalLauncherSkillCitadelKineticDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[468]},
			}},
			{EffectID::missileSkillAoeVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[469]},
			}},
			{EffectID::capitalLauncherSkillCitadelEmDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[470]},
			}},
			{EffectID::capitalLauncherSkillCitadelExplosiveDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[471]},
			}},
			{EffectID::capitalLauncherSkillCitadelThermalDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[472]},
			}},
			{EffectID::missileSkillWarheadUpgradesEmDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[473]},
			}},
			{EffectID::missileSkillWarheadUpgradesExplosiveDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[474]},
			}},
			{EffectID::missileSkillWarheadUpgradesKineticDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[475]},
			}},
			{EffectID::skillAdvancedSpaceshipAgilityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[476]},
			}},
			{EffectID::shipAdvancedSpaceshipCommandAgilityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[477]},
			}},
			{EffectID::skillCapitalShipsAdvancedAgility, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[478]},
			}},
			{EffectID::shipCapitalAgilityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[479]},
			}},
			{EffectID::capitalShieldOperationSkillCapacitorNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[480]},
			}},
			{EffectID::capitalRepairSystemsSkillDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[481]},
			}},
			{EffectID::skillAdvancedWeaponUpgradesPowerNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[482]},{modifiers[483]},
			}},
			{EffectID::armoredCommandMindlink, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[484]},{modifiers[485]},{modifiers[486]},{modifiers[487]},{modifiers[488]},
			}},
			{EffectID::skirmishCommandMindlink, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[489]},{modifiers[490]},{modifiers[491]},{modifiers[492]},{modifiers[493]},
			}},
			{EffectID::shieldCommandMindlink, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[494]},{modifiers[495]},{modifiers[496]},{modifiers[497]},{modifiers[498]},
			}},
			{EffectID::informationCommandMindlink, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[499]},{modifiers[500]},{modifiers[501]},{modifiers[502]},{modifiers[503]},
			}},
			{EffectID::skillSiegeModuleConsumptionQuantityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[504]},
			}},
			{EffectID::skillCynosuralSiegeConsumQuantityBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[505]},
			}},
			{EffectID::missileSkillWarheadUpgradesThermalDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[506]},
			}},
			{EffectID::freighterA1SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[507]},
			}},
			{EffectID::freighterA2SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[508]},
			}},
			{EffectID::freighterC1SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[509]},
			}},
			{EffectID::freighterC2SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[510]},
			}},
			{EffectID::freighterG1SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[511]},
			}},
			{EffectID::freighterG2SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[512]},
			}},
			{EffectID::freighterM1SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[513]},
			}},
			{EffectID::freighterM2SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[514]},
			}},
			{EffectID::freighterCargoBonusA2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[515]},
			}},
			{EffectID::freighterCargoBonusC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[516]},
			}},
			{EffectID::freighterCargoBonusG2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[517]},
			}},
			{EffectID::freighterCargoBonusM2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[518]},
			}},
			{EffectID::freighterMaxVelocityBonusA1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[519]},
			}},
			{EffectID::freighterMaxVelocityBonusC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[520]},
			}},
			{EffectID::freighterMaxVelocityBonusG1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[521]},
			}},
			{EffectID::freighterMaxVelocityBonusM1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[522]},
			}},
			{EffectID::shieldBoostAmplifier, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[431]},{modifiers[523]},
			}},
			{EffectID::jumpDriveSkillsCapacitorNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[524]},
			}},
			{EffectID::jumpDriveSkillsCapacitorNeedBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[525]},
			}},
			{EffectID::droneDmgBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[526]},
			}},
			{EffectID::doHacking, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::missileSkillRapidLauncherRoF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[527]},
			}},
			{EffectID::missileSkillMissileProjectileVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[528]},
			}},
			{EffectID::missileSkillMissileProjectileVelocityBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[529]},
			}},
			{EffectID::shipFalloffBonusGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[530]},
			}},
			{EffectID::shipArmorEMResistanceAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[531]},
			}},
			{EffectID::shipArmorTHResistanceAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[532]},
			}},
			{EffectID::shipArmorKNResistanceAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[533]},
			}},
			{EffectID::shipArmorEXResistanceAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[534]},
			}},
			{EffectID::shipShieldEMResistanceCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[535]},
			}},
			{EffectID::shipShieldThermalResistanceCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[536]},
			}},
			{EffectID::shipShieldKineticResistanceCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[537]},
			}},
			{EffectID::shipShieldExplosiveResistanceCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[538]},
			}},
			{EffectID::shipShieldEMResistanceCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[539]},
			}},
			{EffectID::shipShieldThermalResistanceCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[540]},
			}},
			{EffectID::shipShieldKineticResistanceCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[541]},
			}},
			{EffectID::shipShieldExplosiveResistanceCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[542]},
			}},
			{EffectID::eliteBargeSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[543]},
			}},
			{EffectID::eliteBargeSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[544]},
			}},
			{EffectID::miningForemanMindlink, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[545]},{modifiers[546]},{modifiers[547]},{modifiers[548]},{modifiers[549]},
			}},
			{EffectID::miningBargeSkillLevelPostMulShipBonusORE3Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[550]},
			}},
			{EffectID::selfRof, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[551]},
			}},
			{EffectID::shipMissileEMDamageCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[552]},
			}},
			{EffectID::shipMissileThermalDamageCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[553]},
			}},
			{EffectID::shipMissileExplosiveDamageCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[554]},
			}},
			{EffectID::miningYieldMultiplyPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[125]},
			}},
			{EffectID::shipCruiseLauncherROFBonus2CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[555]},
			}},
			{EffectID::shipSiegeLauncherROFBonus2CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[556]},
			}},
			{EffectID::miningUpgradeCPUReductionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[557]},
			}},
			{EffectID::eliteBargeBonusIceHarvestingCycleTimeBarge3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[558]},
			}},
			{EffectID::shieldCompensationSkillBoostHardeningBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[559]},
			}},
			{EffectID::reconShipSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[560]},
			}},
			{EffectID::reconShipSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[561]},
			}},
			{EffectID::eliteBonusVampireDrainAmount2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[562]},
			}},
			{EffectID::eliteReconBonusGravimetricStrength2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[563]},
			}},
			{EffectID::eliteReconBonusMagnetometricStrength2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[564]},
			}},
			{EffectID::eliteReconBonusRadarStrength2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[565]},
			}},
			{EffectID::eliteReconBonusLadarStrength2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[566]},
			}},
			{EffectID::eliteReconStasisWebBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[567]},
			}},
			{EffectID::eliteReconScramblerRangeBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[568]},
			}},
			{EffectID::ammoEMResistOther, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[569]},
			}},
			{EffectID::armorReinforcerMassAdd, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[570]},
			}},
			{EffectID::signatureRadiusBonus, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[571]},
			}},
			{EffectID::shipBonusShieldTransferCapneed1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[572]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedGC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[573]},
			}},
			{EffectID::caldariShipEwCapacitorNeedCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[574]},
			}},
			{EffectID::droneRangeBonusAdd, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[165]},
			}},
			{EffectID::cynosuralDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[575]},
			}},
			{EffectID::propulsionDroneJammingStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[576]},
			}},
			{EffectID::droneMaxVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[577]},
			}},
			{EffectID::droneMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[578]},
			}},
			{EffectID::droneDurabilityShieldCapBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[579]},
			}},
			{EffectID::droneDurabilityArmorHPBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[580]},
			}},
			{EffectID::droneDurabilityHPBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[581]},
			}},
			{EffectID::damageRepairedSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[582]},
			}},
			{EffectID::repairDroneShieldBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[583]},
			}},
			{EffectID::repairDroneArmorDamageAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[584]},
			}},
			{EffectID::addToSignatureRadius2, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[585]},
			}},
			{EffectID::modifyArmorResonancePostPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::modifyShieldResonancePostPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::emShieldCompensationHardeningBonusGroupShieldAmp, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[594]},
			}},
			{EffectID::explosiveShieldCompensationHardeningBonusGroupShieldAmp, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[595]},
			}},
			{EffectID::kineticShieldCompensationHardeningBonusGroupShieldAmp, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[596]},
			}},
			{EffectID::thermalShieldCompensationHardeningBonusGroupShieldAmp, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[597]},
			}},
			{EffectID::emArmorCompensationHardeningBonusGroupArmorCoating, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[598]},
			}},
			{EffectID::explosiveArmorCompensationHardeningBonusGroupArmorCoating, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[599]},
			}},
			{EffectID::kineticArmorCompensationHardeningBonusGroupArmorCoating, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[600]},
			}},
			{EffectID::thermicArmorCompensationHardeningBonusGroupArmorCoating, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[601]},
			}},
			{EffectID::emArmorCompensationHardeningBonusGroupEnergized, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[602]},
			}},
			{EffectID::explosiveArmorCompensationHardeningBonusGroupEnergized, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[603]},
			}},
			{EffectID::kineticArmorCompensationHardeningBonusGroupEnergized, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[604]},
			}},
			{EffectID::thermicArmorCompensationHardeningBonusGroupEnergized, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[605]},
			}},
			{EffectID::smallHybridMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[606]},
			}},
			{EffectID::smallEnergyMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[607]},
			}},
			{EffectID::smallProjectileMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[608]},
			}},
			{EffectID::energyTransferArrayMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[609]},
			}},
			{EffectID::shieldTransporterMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[610]},{modifiers[611]},
			}},
			{EffectID::armorRepairProjectorMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[612]},{modifiers[613]},
			}},
			{EffectID::minmatarShipEwTargetPainterMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[614]},
			}},
			{EffectID::droneDamageBonusRequringDrones, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[615]},
			}},
			{EffectID::jumpPortalGeneration, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},
			}},
			{EffectID::eliteBonusCommandShipProjectileDamageCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[618]},
			}},
			{EffectID::eliteBonusCommandShipProjectileFalloffCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[619]},
			}},
			{EffectID::eliteBonusCommandShipLaserDamageCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[620]},
			}},
			{EffectID::eliteBonusCommandShipLaserROFCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[621]},
			}},
			{EffectID::eliteBonusCommandShipHybridFalloffCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[622]},
			}},
			{EffectID::eliteBonusCommandShipHybridOptimalCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[623]},
			}},
			{EffectID::shipBonusDroneHitpointsGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[624]},{modifiers[625]},{modifiers[626]},
			}},
			{EffectID::shipBonusDroneHitpointsFixedAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[627]},{modifiers[628]},{modifiers[629]},
			}},
			{EffectID::shipBonusDroneHitpointsGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[630]},{modifiers[631]},{modifiers[632]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[633]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[634]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[635]},
			}},
			{EffectID::eliteBonusInterdictorsMissileKineticDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[636]},
			}},
			{EffectID::eliteBonusInterdictorsProjectileFalloff1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[637]},
			}},
			{EffectID::shipBonusPirateFrigateProjDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[638]},
			}},
			{EffectID::scanStrengthBonusPercentActivate, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::scanStrengthBonusPercentOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::scanStrengthTargetPercentBonus, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[643]},{modifiers[644]},{modifiers[645]},{modifiers[646]},
			}},
			{EffectID::shipBonusDroneMiningAmountAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[647]},
			}},
			{EffectID::shipBonusDroneMiningAmountGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[648]},
			}},
			{EffectID::commandshipMultiRelayEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[455]},{modifiers[649]},
			}},
			{EffectID::covertOpsAndReconOpsCloakModuleDelayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[650]},
			}},
			{EffectID::covertOpsStealthBomberTargettingDelayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[651]},
			}},
			{EffectID::tractorBeamCan, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::modifyArmorResonancePassivePostPercentPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[652]},{modifiers[653]},{modifiers[654]},{modifiers[655]},
			}},
			{EffectID::modifyShieldResonancePassivePostPercentPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[656]},{modifiers[657]},{modifiers[658]},{modifiers[659]},
			}},
			{EffectID::scanStrengthBonusPercentPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::damageControl, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[660]},{modifiers[661]},{modifiers[662]},{modifiers[663]},{modifiers[664]},{modifiers[665]},{modifiers[666]},{modifiers[667]},{modifiers[668]},{modifiers[669]},{modifiers[670]},{modifiers[671]},
			}},
			{EffectID::eliteReconBonusEnergyNeutAmount2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[672]},
			}},
			{EffectID::skillADDmaxJumpClones, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[673]},
			}},
			{EffectID::disallowOffensiveActChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[674]},
			}},
			{EffectID::capitalRemoteArmorRepairerCapNeedBonusSkill, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[675]},
			}},
			{EffectID::capitalRemoteShieldTransferCapNeedBonusSkill, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[676]},
			}},
			{EffectID::capitalRemoteEnergyTransferCapNeedBonusSkill, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[677]},
			}},
			{EffectID::skillSuperWeaponDmgBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[678]},{modifiers[679]},{modifiers[680]},{modifiers[681]},
			}},
			{EffectID::cloneVatMaxJumpCloneBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[682]},
			}},
			{EffectID::snowBallLaunching, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::implantVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[683]},
			}},
			{EffectID::skillInterdictorEliteBonus1SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[684]},
			}},
			{EffectID::skillInterdictorEliteBonus2SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[685]},
			}},
			{EffectID::energyManagementSkillBoostCapacitorCapacityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[686]},
			}},
			{EffectID::energyManagementCapacitorBonusPostPercentCapacityLocationShipGroupCapacitorCapacityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[687]},
			}},
			{EffectID::minerCpuUsageMultiplyPercent2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[688]},
			}},
			{EffectID::iceMinerCpuUsagePercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[689]},
			}},
			{EffectID::commandShipSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[690]},
			}},
			{EffectID::commandShipSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[691]},
			}},
			{EffectID::miningUpgradeCPUPenaltyReductionModulesRequiringMiningUpgradePercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[692]},
			}},
			{EffectID::shipBonusArmorResistAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[693]},{modifiers[694]},{modifiers[695]},{modifiers[696]},
			}},
			{EffectID::iceHarvestCycleTimeModulesRequiringIceHarvestingOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[382]},
			}},
			{EffectID::warpScrambleForStructure, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[8]},
			}},
			{EffectID::implantArmorHpBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[697]},
			}},
			{EffectID::implantVelocityBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[698]},
			}},
			{EffectID::shipBonusRemoteTrackingComputerFalloffMC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[699]},
			}},
			{EffectID::shipBonusRemoteTrackingComputerFalloffGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[700]},
			}},
			{EffectID::ewSkillEcmBurstRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[701]},
			}},
			{EffectID::ewSkillEcmBurstCapNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[702]},
			}},
			{EffectID::shipHTTrackingBonusGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[703]},
			}},
			{EffectID::shipBonusHybridTrackingGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[704]},
			}},
			{EffectID::eliteBonusAssaultShipMissileVelocity1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[705]},
			}},
			{EffectID::neurotoxinRecoverySkillBoostChanceBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[706]},
			}},
			{EffectID::modifyBoosterEffectChanceWithBoosterChanceBonusPostPercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[707]},{modifiers[708]},{modifiers[709]},{modifiers[710]},{modifiers[711]},
			}},
			{EffectID::naniteControlSkillBoostBoosterAttributeModifier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[712]},
			}},
			{EffectID::shipBonusEmShieldResistanceCB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[713]},
			}},
			{EffectID::shipBonusExplosiveShieldResistanceCB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[714]},
			}},
			{EffectID::shipBonusKineticShieldResistanceCB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[715]},
			}},
			{EffectID::shipBonusThermicShieldResistanceCB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[716]},
			}},
			{EffectID::eliteBonusGunshipProjectileDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[717]},
			}},
			{EffectID::eliteBonusGunshipProjectileDamage2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[718]},
			}},
			{EffectID::increaseSignatureRadiusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[380]},
			}},
			{EffectID::scanResolutionMultiplierOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[269]},
			}},
			{EffectID::maxTargetRangeBonus, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[167]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyMissileLaunhcerRof2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[719]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyAssaultMissileLaunhcerRof2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[720]},
			}},
			{EffectID::eliteBonusHeavyGunshipAssaultMissileLaunhcerRof2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[721]},
			}},
			{EffectID::scanStrengthBonusSkillLevelIncrease, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[722]},
			}},
			{EffectID::rigSlot, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::sensorBoosterActivePercentage, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[167]},{modifiers[232]},{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::capNeedBonusEffectLasers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[723]},
			}},
			{EffectID::capNeedBonusEffectHybrids, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[724]},
			}},
			{EffectID::cpuNeedBonusEffectLasers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[725]},
			}},
			{EffectID::cpuNeedBonusEffectHybrid, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[726]},
			}},
			{EffectID::cpuNeedBonusEffectProjectile, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[727]},
			}},
			{EffectID::falloffBonusEffectLasers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[728]},
			}},
			{EffectID::falloffBonusEffectHybrids, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[729]},
			}},
			{EffectID::falloffBonusEffectProjectiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[730]},
			}},
			{EffectID::maxRangeBonusEffectLasers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[731]},
			}},
			{EffectID::maxRangeBonusEffectHybrids, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[732]},
			}},
			{EffectID::maxRangeBonusEffectProjectiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[733]},
			}},
			{EffectID::drawbackPowerNeedLasers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[734]},
			}},
			{EffectID::drawbackPowerNeedHybrids, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[735]},
			}},
			{EffectID::drawbackPowerNeedProjectiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[736]},
			}},
			{EffectID::drawbackArmorHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[737]},
			}},
			{EffectID::drawbackCPUOutput, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[738]},
			}},
			{EffectID::drawbackCPUNeedLaunchers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[739]},
			}},
			{EffectID::drawbackSigRad, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[740]},
			}},
			{EffectID::drawbackMaxVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[741]},
			}},
			{EffectID::drawbackShieldCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[742]},
			}},
			{EffectID::rigDrawbackSkillEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[743]},
			}},
			{EffectID::miningClouds, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::gasCloudHarvestingMaxGroupSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[744]},
			}},
			{EffectID::shipECMScanStrengthBonusCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[745]},{modifiers[746]},{modifiers[747]},{modifiers[748]},
			}},
			{EffectID::boosterArmorHpPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[749]},
			}},
			{EffectID::boosterArmorRepairAmountPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[750]},
			}},
			{EffectID::boosterShieldCapacityPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[751]},
			}},
			{EffectID::boosterTurretOptimalRangePenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[752]},
			}},
			{EffectID::boosterTurretFalloffPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[753]},
			}},
			{EffectID::boosterCapacitorCapacityPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[754]},
			}},
			{EffectID::boosterMaxVelocityPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[755]},
			}},
			{EffectID::boosterTurretTrackingPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[756]},
			}},
			{EffectID::boosterMissileVelocityPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[757]},
			}},
			{EffectID::boosterMissileExplosionVelocityPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[758]},
			}},
			{EffectID::shipBonusECMStrengthBonusCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[759]},{modifiers[760]},{modifiers[761]},{modifiers[762]},
			}},
			{EffectID::salvaging, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::boosterModifyBoosterArmorPenalties, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[763]},{modifiers[764]},
			}},
			{EffectID::boosterModifyBoosterShieldPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[765]},{modifiers[766]},
			}},
			{EffectID::boosterModifyBoosterMaxVelocityAndCapacitorPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[767]},{modifiers[768]},
			}},
			{EffectID::boosterModifyBoosterMissilePenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[769]},{modifiers[770]},{modifiers[771]},
			}},
			{EffectID::boosterModifyBoosterTurretPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[772]},{modifiers[773]},{modifiers[774]},
			}},
			{EffectID::boosterMissileExplosionCloudPenaltyFixed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[775]},
			}},
			{EffectID::modifyArmorResonancePostPercentPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::salvagingAccessDifficultyBonusEffectPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[776]},
			}},
			{EffectID::modifyShieldResonancePostPercentPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::massReductionBonusPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[777]},
			}},
			{EffectID::projectileWeaponSpeedMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[21]},
			}},
			{EffectID::projectileWeaponDamageMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[23]},
			}},
			{EffectID::missileLauncherSpeedMultiplierPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[276]},
			}},
			{EffectID::energyWeaponSpeedMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[25]},
			}},
			{EffectID::hybridWeaponDamageMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[24]},
			}},
			{EffectID::energyWeaponDamageMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[22]},
			}},
			{EffectID::hybridWeaponSpeedMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[26]},
			}},
			{EffectID::shipBonusLargeEnergyWeaponDamageAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[778]},
			}},
			{EffectID::shipMissileAssaultMissileVelocityBonusCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[779]},
			}},
			{EffectID::eliteBonusHeavyGunshipAssaultMissileFlightTime1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[780]},
			}},
			{EffectID::caldariShipECMBurstOptimalRangeCB3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[781]},
			}},
			{EffectID::maxScanDeviationSelfSkillModifier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[782]},
			}},
			{EffectID::armorHPBonusAdd, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[783]},
			}},
			{EffectID::skillBoostTrackingSpeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[784]},
			}},
			{EffectID::trackingSpeedBonusPassiveRequiringGunneryTrackingSpeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[785]},
			}},
			{EffectID::accessDifficultyBonusModifierRequiringArchaelogy, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[786]},
			}},
			{EffectID::accessDifficultyBonusModifierRequiringHacking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[787]},
			}},
			{EffectID::durationBonusForGroupAfterburner, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[788]},
			}},
			{EffectID::missileDMGBonusPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[258]},
			}},
			{EffectID::maxTargetingRangeBonusPremulPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[31]},
			}},
			{EffectID::cloakingTargetingDelayBonusLRSMCloakingPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[789]},
			}},
			{EffectID::cynosuralGeneration, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[790]},
			}},
			{EffectID::cloneJumpAccepting, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[790]},
			}},
			{EffectID::velocityBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[683]},
			}},
			{EffectID::biologyTimeBonusFixed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[791]},
			}},
			{EffectID::sentryDroneDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[792]},
			}},
			{EffectID::armorDamageAmountBonusCapitalArmorRepairers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[793]},
			}},
			{EffectID::missileVelocityBonusDefender, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[794]},
			}},
			{EffectID::missileEMDmgBonusCruise3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[795]},
			}},
			{EffectID::missileExplosiveDmgBonusCruise3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[796]},
			}},
			{EffectID::missileKineticDmgBonusCruise3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[797]},
			}},
			{EffectID::missileThermalDmgBonusCruise3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[798]},
			}},
			{EffectID::gasHarvestingCycleTimeModulesRequiringGasCloudHarvesting, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[799]},
			}},
			{EffectID::setMaxLockedTargets, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[800]},
			}},
			{EffectID::missileEMDmgBonusRocket, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[801]},
			}},
			{EffectID::missileExplosiveDmgBonusRocket, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[802]},
			}},
			{EffectID::missileKineticDmgBonusRocket, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[803]},
			}},
			{EffectID::missileThermalDmgBonusRocket, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[804]},
			}},
			{EffectID::missileEMDmgBonusStandard, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[805]},
			}},
			{EffectID::missileExplosiveDmgBonusStandard, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[806]},
			}},
			{EffectID::missileKineticDmgBonusStandard, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[807]},
			}},
			{EffectID::missileThermalDmgBonusStandard, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[808]},
			}},
			{EffectID::missileEMDmgBonusHeavy, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[809]},
			}},
			{EffectID::missileExplosiveDmgBonusHeavy, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[810]},
			}},
			{EffectID::missileKineticDmgBonusHeavy, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[811]},
			}},
			{EffectID::missileThermalDmgBonusHeavy, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[812]},
			}},
			{EffectID::missileEMDmgBonusHAM, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[813]},
			}},
			{EffectID::missileExplosiveDmgBonusHAM, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[814]},
			}},
			{EffectID::missileKineticDmgBonusHAM, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[815]},
			}},
			{EffectID::missileThermalDmgBonusHAM, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[816]},
			}},
			{EffectID::missileEMDmgBonusTorpedo, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[817]},
			}},
			{EffectID::missileExplosiveDmgBonusTorpedo, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[818]},
			}},
			{EffectID::missileKineticDmgBonusTorpedo, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[819]},
			}},
			{EffectID::missileThermalDmgBonusTorpedo, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[820]},
			}},
			{EffectID::dataminerModuleDurationReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[821]},
			}},
			{EffectID::posStructureControlAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[822]},
			}},
			{EffectID::skillTriageModuleConsumptionQuantityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[823]},
			}},
			{EffectID::bombLaunching, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::skillRemoteECMDurationBonusSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[824]},
			}},
			{EffectID::tskillRemoteHullRepairSystemsCapNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[825]},
			}},
			{EffectID::skillCapitalRemoteHullRepairSystemsCapNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[826]},
			}},
			{EffectID::skillRemoteECMDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[827]},{modifiers[828]},{modifiers[829]},{modifiers[830]},{modifiers[831]},
			}},
			{EffectID::overloadRofBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[832]},
			}},
			{EffectID::overloadSelfDurationBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[833]},
			}},
			{EffectID::eliteBonusCoverOpsBombExplosiveDmg1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[834]},
			}},
			{EffectID::overloadSelfDamageBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[835]},
			}},
			{EffectID::eliteBonusCoverOpsBombKineticDmg1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[836]},
			}},
			{EffectID::eliteBonusCoverOpsBombThermalDmg1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[837]},
			}},
			{EffectID::eliteBonusCoverOpsBombEmDmg1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[838]},
			}},
			{EffectID::overloadSelfEmHardeningBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[839]},
			}},
			{EffectID::overloadSelfThermalHardeningBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[840]},
			}},
			{EffectID::overloadSelfExplosiveHardeningBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[841]},
			}},
			{EffectID::overloadSelfKineticHardeningBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[842]},
			}},
			{EffectID::overloadSelfHardeningInvulnerabilityBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[839]},{modifiers[840]},{modifiers[841]},{modifiers[842]},
			}},
			{EffectID::skillBombDeploymentModuleReactivationDelayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[843]},
			}},
			{EffectID::modifyMaxVelocityOfShipPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[214]},
			}},
			{EffectID::structureHPMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[17]},
			}},
			{EffectID::heatDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[844]},
			}},
			{EffectID::controlTowerGenericHullResistanceBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[845]},{modifiers[846]},{modifiers[847]},{modifiers[848]},{modifiers[849]},{modifiers[850]},{modifiers[851]},{modifiers[852]},{modifiers[853]},{modifiers[854]},{modifiers[855]},{modifiers[856]},{modifiers[857]},{modifiers[858]},{modifiers[859]},{modifiers[860]},{modifiers[861]},{modifiers[862]},{modifiers[863]},{modifiers[864]},{modifiers[865]},{modifiers[866]},{modifiers[867]},{modifiers[868]},{modifiers[869]},{modifiers[870]},{modifiers[871]},{modifiers[872]},{modifiers[873]},{modifiers[874]},{modifiers[875]},{modifiers[876]},{modifiers[877]},{modifiers[878]},{modifiers[879]},{modifiers[880]},{modifiers[881]},{modifiers[882]},{modifiers[883]},{modifiers[884]},{modifiers[885]},{modifiers[886]},{modifiers[887]},{modifiers[888]},{modifiers[889]},{modifiers[890]},{modifiers[891]},{modifiers[892]},
			}},
			{EffectID::shieldTransportCpuNeedBonusEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[893]},
			}},
			{EffectID::droneArmorDamageBonusEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[894]},
			}},
			{EffectID::droneShieldBonusBonusEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[895]},
			}},
			{EffectID::overloadSelfRangeBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[896]},
			}},
			{EffectID::overloadSelfSpeedBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[897]},
			}},
			{EffectID::overloadSelfECMStrenghtBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[898]},{modifiers[899]},{modifiers[900]},{modifiers[901]},
			}},
			{EffectID::overloadSelfECCMStrenghtBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[902]},{modifiers[903]},{modifiers[904]},{modifiers[905]},
			}},
			{EffectID::thermodynamicsSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[906]},
			}},
			{EffectID::thermodynamicsSkillDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[907]},
			}},
			{EffectID::overloadSelfArmorDamageAmountDurationBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[833]},{modifiers[908]},
			}},
			{EffectID::overloadSelfShieldBonusDurationBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[833]},{modifiers[909]},
			}},
			{EffectID::missileSkillFoFAoeCloudSizeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[910]},
			}},
			{EffectID::shipRocketExplosiveDmgAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[911]},
			}},
			{EffectID::shipRocketKineticDmgAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[912]},
			}},
			{EffectID::shipRocketThermalDmgAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[913]},
			}},
			{EffectID::shipRocketEmDmgAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[914]},
			}},
			{EffectID::eliteBonusGunshipArmorEmResistance1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[915]},
			}},
			{EffectID::eliteBonusGunshipArmorThermalResistance1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[916]},
			}},
			{EffectID::eliteBonusGunshipArmorKineticResistance1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[917]},
			}},
			{EffectID::eliteBonusGunshipArmorExplosiveResistance1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[918]},
			}},
			{EffectID::shipCapRecharge2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[919]},
			}},
			{EffectID::tacticalShieldManipulationBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[920]},
			}},
			{EffectID::shipCommandBonusEffectiveMultiplierOreCapital2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[921]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[922]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[923]},
			}},
			{EffectID::skillIndustrialReconfigurationConsumptionQuantityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[924]},
			}},
			{EffectID::shipConsumptionQuantityBonusIndustrialReconfigurationORECapital1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[925]},
			}},
			{EffectID::miningDirectorBonusCommandBonusEffective, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[926]},
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[927]},
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[928]},
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[929]},
			}},
			{EffectID::oreCapitalShipShieldTransferRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[930]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[931]},
			}},
			{EffectID::cloneVatMaxJumpCloneBonusSkillNew, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[932]},
			}},
			{EffectID::shipBonusORECapShipDroneDmgBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[933]},
			}},
			{EffectID::shipBonusORECapShipDroneArmorHPAndShieldHPAndHpBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[934]},{modifiers[935]},{modifiers[936]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier4, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[937]},
			}},
			{EffectID::eliteBonusCommandShipArmorHP1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[938]},
			}},
			{EffectID::shipArmorEmResistanceMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[939]},
			}},
			{EffectID::shipArmorExplosiveResistanceMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[940]},
			}},
			{EffectID::shipArmorKineticResistanceMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[941]},
			}},
			{EffectID::shipArmorThermalResistanceMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[942]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsProjectileFalloff1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[943]},
			}},
			{EffectID::heavyInterdictorsSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[944]},
			}},
			{EffectID::heavyInterdictorsSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[945]},
			}},
			{EffectID::eliteBonusHeavyInterdictorHeavyMissileVelocityBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[946]},
			}},
			{EffectID::eliteBonusHeavyInterdictorHeavyAssaultMissileVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[947]},
			}},
			{EffectID::eliteBonusHeavyInterdictorLightMissileVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[948]},
			}},
			{EffectID::electronicAttackShipsSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[949]},
			}},
			{EffectID::electronicAttackShipsSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[950]},
			}},
			{EffectID::shipRemoteSensorDampenerCapNeedGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[951]},
			}},
			{EffectID::eliteBonusElectronicAttackShipWarpScramblerMaxRange1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[952]},
			}},
			{EffectID::eliteBonusElectronicAttackShipECMOptimalRange1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[953]},
			}},
			{EffectID::eliteBonusElectronicAttackShipStasisWebMaxRange1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[954]},
			}},
			{EffectID::eliteBonusElectronicAttackShipWarpScramblerCapNeed2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[955]},
			}},
			{EffectID::eliteBonusElectronicAttackShipSignatureRadius2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[956]},
			}},
			{EffectID::implantHardwiringABcapacitorNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[166]},
			}},
			{EffectID::warpDisruptSphere, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::eliteBonusBlackOpsLargeEnergyTurretTracking1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[957]},
			}},
			{EffectID::eliteBonusBlackOpsCloakVelocity2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[958]},
			}},
			{EffectID::blackOpsSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[959]},
			}},
			{EffectID::blackOpsSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[960]},
			}},
			{EffectID::eliteBonusBlackOpsMaxVelocity1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[961]},
			}},
			{EffectID::violatorsSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[962]},
			}},
			{EffectID::violatorsSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[963]},
			}},
			{EffectID::eliteBonusViolatorsLargeEnergyTurretDamageRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[964]},
			}},
			{EffectID::eliteBonusViolatorsLargeHybridTurretDamageRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[965]},
			}},
			{EffectID::eliteBonusViolatorsLargeProjectileTurretDamageRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[966]},
			}},
			{EffectID::eliteBonusViolatorsLargeHybridTurretTracking1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[967]},
			}},
			{EffectID::eliteBonusViolatorsLargeProjectileTurretTracking1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[968]},
			}},
			{EffectID::eliteBonusViolatorsTractorBeamMaxRangeRole2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[969]},
			}},
			{EffectID::eliteBonusViolatorsEwTargetPainting1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[970]},
			}},
			{EffectID::shipBonusPTFalloffMB1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[971]},
			}},
			{EffectID::eliteBonusElectronicAttackShipRechargeRate2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[972]},
			}},
			{EffectID::eliteBonusElectronicAttackShipCapacitorCapacity2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[973]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsWarpDisruptFieldGeneratorWarpScrambleRange2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[974]},
			}},
			{EffectID::eliteBonusViolatorsTractorBeamMaxTractorVelocityRole3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[975]},
			}},
			{EffectID::shipLaserDamagePirateBattleship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[976]},
			}},
			{EffectID::shipTrackingBonusAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[977]},
			}},
			{EffectID::shipBonusMediumEnergyTurretDamagePirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[978]},
			}},
			{EffectID::shipBonusMediumEnergyTurretTrackingAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[979]},
			}},
			{EffectID::shipBonusSmallEnergyTurretDamagePirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[980]},
			}},
			{EffectID::shipBonusSmallEnergyTurretTracking2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[981]},
			}},
			{EffectID::rorqualCargoScanRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[982]},
			}},
			{EffectID::rorqualSurveyScannerRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[983]},
			}},
			{EffectID::shipCapPropulsionJamming, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[984]},
			}},
			{EffectID::setBonusThukker, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[985]},
			}},
			{EffectID::setBonusSisters, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[986]},
			}},
			{EffectID::setBonusSyndicate, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[987]},
			}},
			{EffectID::miningLaserMaxRangeMultBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[988]},
			}},
			{EffectID::setBonusMordus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[989]},
			}},
			{EffectID::interceptor2WarpScrambleRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[990]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringBombLauncher, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[991]},
			}},
			{EffectID::skillAdvancedWeaponUpgradesPowerNeedBonusBombLaunchers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[992]},
			}},
			{EffectID::skillNaniteOperationRepairCost, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[993]},
			}},
			{EffectID::skillNaniteOperationRepairCostLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[994]},
			}},
			{EffectID::skillNaniteInterfacingRepairTimeLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[995]},
			}},
			{EffectID::cynosuralTheoryConsumptionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[996]},
			}},
			{EffectID::skillConsumptionQuantityBonusPercentageSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[997]},
			}},
			{EffectID::drawbackCapacitorRecharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[998]},
			}},
			{EffectID::eliteBonusBlackOpsAgiliy1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[999]},
			}},
			{EffectID::skillJumpDriveConsumptionAmountBonusPercentage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1000]},
			}},
			{EffectID::gunneryMaxRangeBonus, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[1001]},
			}},
			{EffectID::ewSkillTrackingDisruptionTrackingSpeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1002]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkMaxRangeBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1003]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkMaxRangeBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1004]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkTrackingSpeedBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1005]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkTrackingSpeedBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1006]},
			}},
			{EffectID::ewSkillSignalSuppressionScanResolutionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1007]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerMaxTargetRangeBonusGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1008]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerMaxTargetRangeBonusGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1009]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerScanResolutionBonusGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1010]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerScanResolutionBonusGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1011]},
			}},
			{EffectID::ewSkillSignalSuppressionMaxTargetRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1012]},
			}},
			{EffectID::eliteBonusJumpFreighterHullHP1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1013]},
			}},
			{EffectID::eliteBonusJumpFreighterJumpDriveConsumptionAmount2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1014]},
			}},
			{EffectID::jumpFreightersSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1015]},
			}},
			{EffectID::jumpFreightersSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1016]},
			}},
			{EffectID::scriptSensorBoosterScanResolutionBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1017]},
			}},
			{EffectID::scriptSensorBoosterMaxTargetRangeBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1018]},
			}},
			{EffectID::scriptTrackingComputerTrackingSpeedBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1019]},
			}},
			{EffectID::scriptTrackingComputerMaxRangeBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1020]},
			}},
			{EffectID::scriptWarpDisruptionFieldGeneratorSetDisallowInEmpireSpace, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1021]},
			}},
			{EffectID::scriptDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1022]},
			}},
			{EffectID::scriptWarpDisruptionFieldGeneratorSetScriptCapacitorNeedHidden, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1023]},
			}},
			{EffectID::scriptSignatureRadiusBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1024]},
			}},
			{EffectID::scriptMassBonusPercentageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1025]},
			}},
			{EffectID::scriptSpeedBoostFactorBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1026]},
			}},
			{EffectID::scriptSpeedFactorBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1027]},
			}},
			{EffectID::scriptWarpScrambleRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1028]},
			}},
			{EffectID::eliteBonusViolatorsLargeEnergyTurretDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1029]},
			}},
			{EffectID::ewGroupRsdMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1030]},
			}},
			{EffectID::ewGroupTpMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1031]},
			}},
			{EffectID::ewGroupTdMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1032]},
			}},
			{EffectID::ewGroupEcmBurstMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1033]},
			}},
			{EffectID::gunneryMaxRangeBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1001]},
			}},
			{EffectID::gunneryTrackingSpeedBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[785]},
			}},
			{EffectID::shipScanResolutionBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[232]},
			}},
			{EffectID::shipMaxTargetRangeBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[167]},
			}},
			{EffectID::shipMaxLockedTargetsBonusAddOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[33]},
			}},
			{EffectID::miningLaserRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1034]},
			}},
			{EffectID::frequencyMiningLaserMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1035]},
			}},
			{EffectID::stripMinerMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1036]},
			}},
			{EffectID::gasHarvesterMaxRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1037]},
			}},
			{EffectID::setBonusOre, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1038]},
			}},
			{EffectID::jumpPortalGenerationBO, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},
			}},
			{EffectID::shipBonusLargeEnergyTurretMaxRangeAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1039]},
			}},
			{EffectID::eliteBonusJumpFreighterShieldHP1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1040]},
			}},
			{EffectID::eliteBonusJumpFreighterArmorHP1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1041]},
			}},
			{EffectID::freighterAgilityBonusC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1042]},
			}},
			{EffectID::freighterAgilityBonusM1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1043]},
			}},
			{EffectID::freighterAgilityBonusG1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1044]},
			}},
			{EffectID::freighterAgilityBonusA1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1045]},
			}},
			{EffectID::scriptTrackingComputerFalloffBonusBonus, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1046]},
			}},
			{EffectID::dungeonMaxTargetingRangeShip, Effect::MetaInfo::Category::dungeon, true, true, {
				{modifiers[167]},
			}},
			{EffectID::shipMissileLauncherSpeedBonusMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1047]},{modifiers[1048]},{modifiers[1049]},
			}},
			{EffectID::shipHybridTurretROFBonusGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1050]},
			}},
			{EffectID::shipBonusProjectileTrackingMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1051]},
			}},
			{EffectID::skillNaniteInterfacingRepairTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1052]},
			}},
			{EffectID::agilityMultiplierEffectPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[220]},
			}},
			{EffectID::velocityBonusPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[683]},
			}},
			{EffectID::zColinOrcaTractorRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1053]},
			}},
			{EffectID::zColinOrcaTractorVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1054]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1055]},
			}},
			{EffectID::cargoAndOreHoldCapacityBonusICS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1056]},{modifiers[1057]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1058]},
			}},
			{EffectID::miningForemanBurstBonusICS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1059]},{modifiers[1060]},{modifiers[1061]},{modifiers[1062]},{modifiers[1063]},
			}},
			{EffectID::zColinOrcaSurveyScannerBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1064]},
			}},
			{EffectID::eliteIndustrialExtenderSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1065]},
			}},
			{EffectID::zColinSkillTransportCovertCloakMod, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1066]},
			}},
			{EffectID::covertOpsStealthBomberSiegeMissileLauncerPowerNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1067]},
			}},
			{EffectID::interceptorMWDSignatureRadiusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1068]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyMissileExplosionVelocityCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1069]},
			}},
			{EffectID::armorHPBonusAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[783]},
			}},
			{EffectID::subSystem, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::hardPointModifierEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1070]},{modifiers[1071]},
			}},
			{EffectID::slotModifier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1072]},{modifiers[1073]},{modifiers[1074]},
			}},
			{EffectID::powerOutputAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1075]},
			}},
			{EffectID::cpuOutputAddCpuOutputPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1076]},
			}},
			{EffectID::maxVelocityAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1077]},
			}},
			{EffectID::modifyHullResonancePostPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1078]},{modifiers[1079]},{modifiers[1080]},{modifiers[1081]},
			}},
			{EffectID::probeLaunching, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::dungeonMaxVelocityModifier, Effect::MetaInfo::Category::dungeon, true, true, {
				{modifiers[1082]},
			}},
			{EffectID::dungeonMiningLaserDurationBonus, Effect::MetaInfo::Category::dungeon, true, true, {
				{modifiers[1083]},
			}},
			{EffectID::dungeonTurretTrackingBonus, Effect::MetaInfo::Category::dungeon, true, true, {
				{modifiers[785]},
			}},
			{EffectID::droneBandwidthAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1084]},
			}},
			{EffectID::droneCapacityAdddroneCapacityPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1085]},
			}},
			{EffectID::scanStrengthAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1086]},{modifiers[1087]},{modifiers[1088]},{modifiers[1089]},
			}},
			{EffectID::maxTargetRangeAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1090]},
			}},
			{EffectID::signatureRadiusAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1091]},
			}},
			{EffectID::scanResolutionAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1092]},
			}},
			{EffectID::capacityAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1093]},
			}},
			{EffectID::capacitorCapacityAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1094]},
			}},
			{EffectID::shieldCapacityAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1095]},
			}},
			{EffectID::subsystemSkillLevelAmarrDefensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1096]},
			}},
			{EffectID::subsystemSkillLevelCaldariDefensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1097]},
			}},
			{EffectID::subsystemSkillLevelGallenteDefensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1098]},
			}},
			{EffectID::subsystemSkillLevelMinmatarDefensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1099]},
			}},
			{EffectID::subsystemSkillLevelMinmatarElectronic, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1100]},
			}},
			{EffectID::subsystemSkillLevelGallenteElectronic, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1101]},
			}},
			{EffectID::subsystemSkillLevelCaldariElectronic, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1102]},
			}},
			{EffectID::subsystemSkillLevelAmarrElectronic, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1103]},
			}},
			{EffectID::subsystemSkillLevelAmarrEngineering, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1104]},
			}},
			{EffectID::subsystemSkillLevelCaldariEngineering, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1105]},
			}},
			{EffectID::subsystemSkillLevelGallenteEngineering, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1106]},
			}},
			{EffectID::subsystemSkillLevelMinmatarEngineering, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1107]},
			}},
			{EffectID::subsystemSkillLevelMinmatarOffensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1108]},
			}},
			{EffectID::subsystemSkillLevelGallenteOffensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1109]},
			}},
			{EffectID::subsystemSkillLevelCaldariOffensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1110]},
			}},
			{EffectID::subsystemSkillLevelAmarrOffensive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1111]},
			}},
			{EffectID::subsystemSkillLevelAmarrPropulsion, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1112]},
			}},
			{EffectID::subsystemSkillLevelCaldariPropulsion, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1113]},
			}},
			{EffectID::subsystemSkillLevelGallentePropulsion, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1114]},
			}},
			{EffectID::subsystemSkillLevelMinmatarPropulsion, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1115]},
			}},
			{EffectID::rechargeRateAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1116]},
			}},
			{EffectID::shieldRechargeRateAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1117]},
			}},
			{EffectID::subsystemBonusAmarrPropulsionMaxVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1118]},
			}},
			{EffectID::subsystemBonusCaldariPropulsionMaxVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1119]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsionMaxVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1120]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsionAfterburnerSpeedFactor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1121]},
			}},
			{EffectID::subsystemBonusCaldariPropulsionAfterburnerSpeedFactor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1122]},
			}},
			{EffectID::subsystemBonusAmarrPropulsionAfterburnerSpeedFactor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1123]},
			}},
			{EffectID::subsystemBonusAmarrPropulsion2Agility, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1124]},
			}},
			{EffectID::subsystemBonusCaldariPropulsion2Agility, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1125]},
			}},
			{EffectID::subsystemBonusGallentePropulsion2Agility, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1126]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsion2Agility, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1127]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsion2MWDPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1128]},
			}},
			{EffectID::subsystemBonusGallentePropulsionMWDPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1129]},
			}},
			{EffectID::subsystemBonusAmarrPropulsion2MWDPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1130]},
			}},
			{EffectID::subsystemBonusGallentePropulsionABMWDCapNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1131]},
			}},
			{EffectID::subsystemBonusGallenteElectronicCPU, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1132]},
			}},
			{EffectID::subsystemBonusCaldariElectronicCPU, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1133]},
			}},
			{EffectID::subsystemBonusMinmatarCoreScanStrengthLADAR, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1134]},
			}},
			{EffectID::subsystemBonusGallenteCoreScanStrengthMagnetometric, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1135]},
			}},
			{EffectID::subsystemBonusCaldariCoreScanStrengthGravimetric, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1136]},
			}},
			{EffectID::subsystemBonusAmarrCoreScanStrengthRADAR, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1137]},
			}},
			{EffectID::subsystemBonusAmarrDefensiveArmorResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1138]},{modifiers[1139]},{modifiers[1140]},{modifiers[1141]},
			}},
			{EffectID::subsystemBonusGallenteDefensiveArmorResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1142]},{modifiers[1143]},{modifiers[1144]},{modifiers[1145]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveArmorResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1146]},{modifiers[1147]},{modifiers[1148]},{modifiers[1149]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveShieldResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1150]},{modifiers[1151]},{modifiers[1152]},{modifiers[1153]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1154]},{modifiers[1155]},{modifiers[1156]},{modifiers[1157]},
			}},
			{EffectID::subsystemBonusAmarrDefensiveArmorRepairAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1158]},
			}},
			{EffectID::subsystemBonusGallenteDefensiveArmorRepairAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1159]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveShieldArmorRepairAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1160]},{modifiers[1161]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldBoostAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1162]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1163]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveShieldArmorHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1164]},{modifiers[1165]},
			}},
			{EffectID::subsystemBonusGallenteDefensiveArmorHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1166]},
			}},
			{EffectID::subsystemBonusAmarrDefensiveArmorHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1167]},
			}},
			{EffectID::systemShieldHP, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[14]},
			}},
			{EffectID::systemTargetingRange, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[31]},
			}},
			{EffectID::systemSignatureRadius, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[283]},
			}},
			{EffectID::systemArmorEmResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1168]},
			}},
			{EffectID::systemArmorExplosiveResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1169]},
			}},
			{EffectID::systemArmorKineticResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1170]},
			}},
			{EffectID::systemArmorThermalResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1171]},
			}},
			{EffectID::systemMissileVelocity, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1172]},
			}},
			{EffectID::systemMaxVelocity, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1173]},
			}},
			{EffectID::systemDamageMultiplierGunnery, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1174]},
			}},
			{EffectID::systemDamageThermalMissiles, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1175]},
			}},
			{EffectID::systemDamageEmMissiles, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1176]},
			}},
			{EffectID::systemDamageExplosiveMissiles, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1177]},
			}},
			{EffectID::systemDamageKineticMissiles, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1178]},
			}},
			{EffectID::systemDamageDrones, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1179]},
			}},
			{EffectID::systemTracking, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[89]},
			}},
			{EffectID::systemAoeVelocity, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1180]},
			}},
			{EffectID::systemHeatDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1181]},
			}},
			{EffectID::systemOverloadArmor, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1182]},
			}},
			{EffectID::systemOverloadDamageModifier, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1183]},
			}},
			{EffectID::systemOverloadDurationBonus, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1184]},
			}},
			{EffectID::systemOverloadEccmStrength, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1185]},
			}},
			{EffectID::systemOverloadEcmStrength, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1186]},
			}},
			{EffectID::systemOverloadHardening, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1187]},
			}},
			{EffectID::systemOverloadRange, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1188]},
			}},
			{EffectID::systemOverloadRof, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1189]},
			}},
			{EffectID::systemOverloadSelfDuration, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1190]},
			}},
			{EffectID::systemOverloadShieldBonus, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1191]},
			}},
			{EffectID::systemOverloadSpeedFactor, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1192]},
			}},
			{EffectID::systemSmartBombRange, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1193]},
			}},
			{EffectID::systemSmartBombEmDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1194]},
			}},
			{EffectID::systemSmartBombThermalDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1195]},
			}},
			{EffectID::systemSmartBombKineticDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1196]},
			}},
			{EffectID::systemSmartBombExplosiveDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1197]},
			}},
			{EffectID::systemSmallEnergyDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1198]},
			}},
			{EffectID::systemSmallProjectileDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1199]},
			}},
			{EffectID::systemSmallHybridDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1200]},
			}},
			{EffectID::systemRocketEmDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1201]},
			}},
			{EffectID::systemRocketExplosiveDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1202]},
			}},
			{EffectID::systemRocketKineticDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1203]},
			}},
			{EffectID::systemRocketThermalDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1204]},
			}},
			{EffectID::systemStandardMissileThermalDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1205]},
			}},
			{EffectID::systemStandardMissileEmDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1206]},
			}},
			{EffectID::systemStandardMissileExplosiveDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1207]},
			}},
			{EffectID::systemArmorRepairAmount, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1208]},{modifiers[1209]},
			}},
			{EffectID::systemArmorRemoteRepairAmount, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1210]},
			}},
			{EffectID::systemShieldRemoteRepairAmount, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1211]},
			}},
			{EffectID::systemCapacitorCapacity, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1212]},
			}},
			{EffectID::systemCapacitorRecharge, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1213]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveEnergyWeaponDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1214]},
			}},
			{EffectID::subsystemBonusCaldariOffensiveHybridWeaponMaxRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1215]},
			}},
			{EffectID::subsystemBonusGallenteOffensiveHybridWeaponFalloff, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1216]},
			}},
			{EffectID::subsystemBonusGallenteOffensiveHybridWeaponDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1217]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveProjectileWeaponROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1218]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveProjectileWeaponFalloff, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1219]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveProjectileWeaponMaxRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1220]},
			}},
			{EffectID::subsystemBonusCaldariOffensiveHeavyMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1221]},
			}},
			{EffectID::subsystemBonusCaldariOffensiveHeavyAssaultMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1222]},
			}},
			{EffectID::subsystemBonusCaldariOffensive1LauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1221]},{modifiers[1222]},{modifiers[1223]},
			}},
			{EffectID::systemShieldEmResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1224]},
			}},
			{EffectID::systemShieldExplosiveResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1225]},
			}},
			{EffectID::systemShieldKineticResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1226]},
			}},
			{EffectID::systemShieldThermalResistance, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1227]},
			}},
			{EffectID::subsystemBonusAmarrEngineeringHeatDamageReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1228]},
			}},
			{EffectID::subsystemBonusCaldariEngineeringHeatDamageReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1229]},
			}},
			{EffectID::subsystemBonusGallenteEngineeringHeatDamageReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1230]},
			}},
			{EffectID::subsystemBonusMinmatarEngineeringHeatDamageReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1231]},
			}},
			{EffectID::subsystemBonusMinmatarEngineeringCapacitorCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1232]},
			}},
			{EffectID::subsystemBonusCaldariCoreCapacitorCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1233]},
			}},
			{EffectID::subsystemBonusAmarrCoreCapacitorCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1234]},
			}},
			{EffectID::massAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1235]},
			}},
			{EffectID::baseMaxScanDeviationModifierRequiringAstrometrics, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1236]},
			}},
			{EffectID::baseSensorStrengthModifierRequiringAstrometrics, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1237]},
			}},
			{EffectID::shipBonusScanProbeStrengthCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1238]},
			}},
			{EffectID::shipBonusScanProbeStrengthMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1239]},
			}},
			{EffectID::shipBonusScanProbeStrengthGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1240]},
			}},
			{EffectID::eliteBonusCoverOpsScanProbeStrength2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1241]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveEnergyWeaponCapacitorNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1242]},
			}},
			{EffectID::shipBonusStrategicCruiserAmarrHeatDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1243]},
			}},
			{EffectID::shipBonusStrategicCruiserCaldariHeatDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1244]},
			}},
			{EffectID::shipBonusStrategicCruiserGallenteHeatDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1245]},
			}},
			{EffectID::shipBonusStrategicCruiserMinmatarHeatDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1246]},
			}},
			{EffectID::strategicCruiserAmarrSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1247]},
			}},
			{EffectID::strategicCruiserCaldariSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1248]},
			}},
			{EffectID::strategicCruiserGallenteSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1249]},
			}},
			{EffectID::strategicCruiserMinmatarSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1250]},
			}},
			{EffectID::subsystemSkillLevelAmarrDefensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1251]},
			}},
			{EffectID::subsystemSkillLevelCaldariDefensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1252]},
			}},
			{EffectID::subsystemSkillLevelGallenteDefensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1253]},
			}},
			{EffectID::subsystemSkillLevelMinmatarDefensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1254]},
			}},
			{EffectID::subsystemSkillLevelMinmatarElectronic2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1255]},
			}},
			{EffectID::subsystemSkillLevelGallenteElectronic2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1256]},
			}},
			{EffectID::subsystemSkillLevelCaldariElectronic2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1257]},
			}},
			{EffectID::subsystemSkillLevelAmarrElectronic2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1258]},
			}},
			{EffectID::subsystemSkillLevelAmarrEngineering2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1259]},
			}},
			{EffectID::subsystemSkillLevelCaldariEngineering2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1260]},
			}},
			{EffectID::subsystemSkillLevelGallenteEngineering2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1261]},
			}},
			{EffectID::subsystemSkillLevelMinmatarEngineering2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1262]},
			}},
			{EffectID::subsystemSkillLevelMinmatarOffensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1263]},
			}},
			{EffectID::subsystemSkillLevelGallenteOffensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1264]},
			}},
			{EffectID::subsystemSkillLevelCaldariOffensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1265]},
			}},
			{EffectID::subsystemSkillLevelAmarrOffensive2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1266]},
			}},
			{EffectID::subsystemSkillLevelAmarrPropulsion2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1267]},
			}},
			{EffectID::subsystemSkillLevelCaldariPropulsion2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1268]},
			}},
			{EffectID::subsystemSkillLevelGallentePropulsion2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1269]},
			}},
			{EffectID::subsystemSkillLevelMinmatarPropulsion2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1270]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2EnergyWeaponCapacitorNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1271]},
			}},
			{EffectID::subsystemBonusAmarrCore2EnergyVampireAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1272]},
			}},
			{EffectID::subsystemBonusAmarrCore2EnergyDestabilizerAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1273]},
			}},
			{EffectID::modifyArmorResonancePassivePreAssignment, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1274]},{modifiers[1275]},{modifiers[1276]},{modifiers[1277]},
			}},
			{EffectID::modifyShieldResonancePassivePreAssignment, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1278]},{modifiers[1279]},{modifiers[1280]},{modifiers[1281]},
			}},
			{EffectID::subsystemBonusCaldariOffensive2MissileLauncherKineticDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1282]},{modifiers[1283]},{modifiers[1284]},
			}},
			{EffectID::subsystemBonusGallenteOffensiveDroneDamageHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1285]},{modifiers[1286]},{modifiers[1287]},{modifiers[1288]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2ProjectileWeaponDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1289]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2ProjectileWeaponROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1290]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2MissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1291]},{modifiers[1292]},{modifiers[1293]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveAssaultMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1294]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveHeavyMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1295]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveHeavyAssaultMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1296]},
			}},
			{EffectID::subsystemBonusAmarrEngineeringPowerOutput, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1297]},
			}},
			{EffectID::subsystemBonusCaldariEngineeringPowerOutput, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1298]},
			}},
			{EffectID::subsystemBonusGallenteEngineeringPowerOutput, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1299]},
			}},
			{EffectID::subsystemBonusMinmatarEngineeringPowerOutput, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1300]},
			}},
			{EffectID::subsystemBonusMinmatarCoreCapacitorRecharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1301]},
			}},
			{EffectID::subsystemBonusGallenteCoreCapacitorRecharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1302]},
			}},
			{EffectID::subsystemBonusCaldariEngineeringCapacitorRecharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1303]},
			}},
			{EffectID::subsystemBonusAmarrEngineeringCapacitorRecharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1304]},
			}},
			{EffectID::subsystemBonusAmarrCore3ScanResolution, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1305]},
			}},
			{EffectID::subsystemBonusMinmatarCore3ScanResolution, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1306]},
			}},
			{EffectID::subsystemBonusCaldariCore2MaxTargetingRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1307]},
			}},
			{EffectID::subsystemBonusGallenteCore2MaxTargetingRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1308]},
			}},
			{EffectID::subsystemBonusGallenteCore2WarpScrambleRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1309]},
			}},
			{EffectID::subsystemBonusMinmatarCore2StasisWebifierRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1310]},
			}},
			{EffectID::subsystemBonusCaldariPropulsion2WarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1311]},
			}},
			{EffectID::subsystemBonusGallentePropulsionWarpCapacitor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1312]},
			}},
			{EffectID::subsystemBonusGallentePropulsion2WarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1313]},
			}},
			{EffectID::systemAgility, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1314]},
			}},
			{EffectID::modifyShipAgilityPassivePreAssignment, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1315]},
			}},
			{EffectID::subsystemBonusGallenteOffensive2HybridWeaponDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1316]},
			}},
			{EffectID::subsystemBonusCaldariOffensive2HybridWeaponDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1317]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2RemoteArmorRepairCapUse, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1318]},
			}},
			{EffectID::subsystemBonusGallenteOffensive2RemoteArmorRepairCapUse, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1319]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2RemoteRepCapUse, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1320]},{modifiers[1321]},
			}},
			{EffectID::subsystemBonusCaldariOffensive2RemoteShieldBoosterCapUse, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1322]},
			}},
			{EffectID::subsystemBonusGallenteEngineeringDroneHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1323]},{modifiers[1324]},{modifiers[1325]},
			}},
			{EffectID::subsystemBonusGallenteEngineering2DroneMWD, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1326]},
			}},
			{EffectID::subsystemBonusCaldariCore2ECMStrengthRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1327]},{modifiers[1328]},{modifiers[1329]},{modifiers[1330]},{modifiers[1331]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveDroneDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1332]},
			}},
			{EffectID::subsystemBonusAmarrOffensive3DroneDamageHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1333]},{modifiers[1334]},{modifiers[1335]},{modifiers[1336]},
			}},
			{EffectID::subsystemBonusGallenteOffensive3DroneDamageMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1337]},
			}},
			{EffectID::subsystemBonusAmarrOffensive3EnergyWeaponMaxRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1338]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3HMLHAMVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1339]},{modifiers[1340]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3HeavyMissileVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1340]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthGrav, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1341]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthLadar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1342]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthMagn, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1343]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthRadar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1344]},
			}},
			{EffectID::subsystemSkillLevelAmarrOffensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1345]},
			}},
			{EffectID::subsystemSkillLevelCaldariOffensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1346]},
			}},
			{EffectID::subsystemSkillLevelGallenteOffensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1347]},
			}},
			{EffectID::subsystemBonusMinmatarCore2MaxTargetingRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1348]},
			}},
			{EffectID::subsystemBonusAmarrCore2MaxTargetingRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1349]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveSignatureRadius, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1350]},
			}},
			{EffectID::subsystemBonusGallenteOffensive3TurretTracking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1351]},
			}},
			{EffectID::subsystemSkillLevelMinmatarOffensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1352]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive3TurretTracking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1353]},
			}},
			{EffectID::caldariCruiserSkillLevelPreMulShipBonusCC3Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1354]},
			}},
			{EffectID::ecmRangeBonusModuleEffect, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1355]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveHeavyMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1356]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1356]},{modifiers[1357]},{modifiers[1358]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveHeavyAssaultMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1358]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2MissileDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1359]},{modifiers[1360]},{modifiers[1361]},{modifiers[1362]},{modifiers[1363]},{modifiers[1364]},{modifiers[1365]},{modifiers[1366]},{modifiers[1367]},{modifiers[1368]},{modifiers[1369]},{modifiers[1370]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2HAMThermalDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1371]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2HAMKineticDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1372]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2HAMExplosiveDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1373]},
			}},
			{EffectID::shipBonusMediumHybridDmgCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1374]},
			}},
			{EffectID::subsystemBonusWarpBubbleImmune, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1375]},
			}},
			{EffectID::caldariShipEwFalloffRangeCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1376]},
			}},
			{EffectID::caldariShipEwFalloffRangeCB3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1377]},
			}},
			{EffectID::subSystemBonusAmarrOffensiveCommandBursts, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1378]},{modifiers[1379]},{modifiers[1380]},{modifiers[1381]},{modifiers[1382]},{modifiers[1383]},{modifiers[1384]},{modifiers[1385]},{modifiers[1386]},{modifiers[1387]},{modifiers[1388]},{modifiers[1389]},{modifiers[1390]},{modifiers[1391]},{modifiers[1392]},
			}},
			{EffectID::subSystemBonusCaldariDefensiveSiegeWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1393]},{modifiers[1394]},{modifiers[1395]},{modifiers[1396]},{modifiers[1397]},
			}},
			{EffectID::subSystemBonusGallenteDefensiveInformationWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1398]},{modifiers[1399]},{modifiers[1400]},{modifiers[1401]},{modifiers[1402]},
			}},
			{EffectID::subSystemBonusMinmatarDefensiveSkirmishWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1403]},{modifiers[1404]},{modifiers[1405]},{modifiers[1406]},{modifiers[1407]},
			}},
			{EffectID::shipBonusTorpedoVelocityGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1408]},
			}},
			{EffectID::shipBonusTorpedoVelocityMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1409]},
			}},
			{EffectID::shipBonusTorpedoVelocity2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1410]},
			}},
			{EffectID::shipBonusTorpedoVelocityCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1411]},
			}},
			{EffectID::eliteReconBonusHeavyMissileVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1412]},
			}},
			{EffectID::eliteReconBonusHeavyAssaultMissileVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1413]},
			}},
			{EffectID::subSystemBonusAmarrElectronicScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1414]},
			}},
			{EffectID::subSystemBonusCaldariElectronicScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1415]},
			}},
			{EffectID::subSystemBonusGallenteElectronicScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1416]},
			}},
			{EffectID::subSystemBonusMinmatarElectronicScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1417]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoThermalDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1418]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoEMDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1419]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoExplosiveDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1420]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoKineticDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1421]},
			}},
			{EffectID::shipBonusGFTorpedoExplosionVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1422]},
			}},
			{EffectID::shipBonusMF1TorpedoExplosionVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1423]},
			}},
			{EffectID::shipBonusCF1TorpedoExplosionVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1424]},
			}},
			{EffectID::shipBonusAF1TorpedoExplosionVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1425]},
			}},
			{EffectID::subSystemBonusAmarrElectronic2TractorBeamVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1426]},
			}},
			{EffectID::subSystemBonusCaldariElectronic2TractorBeamVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1427]},
			}},
			{EffectID::subSystemBonusGallenteElectronic2TractorBeamVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1428]},
			}},
			{EffectID::subSystemBonusMinmatarElectronic2TractorBeamVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1429]},
			}},
			{EffectID::subSystemBonusMinmatarElectronic2TractorBeamRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1430]},
			}},
			{EffectID::subSystemBonusGallenteElectronic2TractorBeamRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1431]},
			}},
			{EffectID::subSystemBonusCaldariElectronic2TractorBeamRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1432]},
			}},
			{EffectID::subSystemBonusAmarrElectronic2TractorBeamRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1433]},
			}},
			{EffectID::signatureRadiusPreAssignment, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1434]},
			}},
			{EffectID::subsystemBonusScanProbeLauncherCPU, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1435]},
			}},
			{EffectID::subsystemBonusJumpHarmonics, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1436]},
			}},
			{EffectID::shipBonusGF1TorpedoFlightTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1437]},
			}},
			{EffectID::shipBonusMF1TorpedoFlightTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1438]},
			}},
			{EffectID::shipBonusCF1TorpedoFlightTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1439]},
			}},
			{EffectID::shipBonusAF1TorpedoFlightTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1440]},
			}},
			{EffectID::scanRadarStrengthModifierEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1441]},
			}},
			{EffectID::scanLadarStrengthModifierEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1442]},
			}},
			{EffectID::scanGravimetricStrengthModifierEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1443]},
			}},
			{EffectID::scanMagnetometricStrengthModifierEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1444]},
			}},
			{EffectID::federationsetbonus3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1445]},
			}},
			{EffectID::imperialsetbonus3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1446]},
			}},
			{EffectID::republicsetbonus3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1447]},
			}},
			{EffectID::caldarisetbonus3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1448]},
			}},
			{EffectID::imperialsetLGbonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1449]},
			}},
			{EffectID::federationsetLGbonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1450]},
			}},
			{EffectID::caldarisetLGbonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1451]},
			}},
			{EffectID::republicsetLGbonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1452]},
			}},
			{EffectID::shipBonusStasisMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1453]},
			}},
			{EffectID::shipProjectileDmgMC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1454]},
			}},
			{EffectID::shipVelocityBonusATC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1455]},
			}},
			{EffectID::shipMTMaxRangeBonusATC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1456]},
			}},
			{EffectID::shipMTFalloffBonusATC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1457]},
			}},
			{EffectID::shipMTFalloffBonusATF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1458]},
			}},
			{EffectID::shipMTMaxRangeBonusATF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1459]},
			}},
			{EffectID::shipBonusAfterburnerCapNeedATF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1460]},
			}},
			{EffectID::shipBonusSurveyProbeExplosionDelaySkillSurveyCovertOps3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1461]},
			}},
			{EffectID::covertOpsSkillLevelPreMulEliteBonusCoverOpsShip3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1462]},
			}},
			{EffectID::shipETOptimalRange2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1463]},
			}},
			{EffectID::shipPTurretFalloffBonusGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1464]},
			}},
			{EffectID::shipBonusStasisWebSpeedFactorMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1465]},
			}},
			{EffectID::superWeaponAmarr, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::superWeaponCaldari, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::superWeaponGallente, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::superWeaponMinmatar, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::shipStasisWebStrengthBonusMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1466]},
			}},
			{EffectID::shipPTurretFalloffBonusGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1467]},
			}},
			{EffectID::shipStasisWebStrengthBonusMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1468]},
			}},
			{EffectID::shipFalloffBonusMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1469]},
			}},
			{EffectID::shipHTurretFalloffBonusGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1470]},
			}},
			{EffectID::gunneryFalloffBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[92]},
			}},
			{EffectID::tcapitalLauncherSkillCruiseCitadelEmDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1471]},
			}},
			{EffectID::capitalLauncherSkillCruiseCitadelExplosiveDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1472]},
			}},
			{EffectID::capitalLauncherSkillCruiseCitadelKineticDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1473]},
			}},
			{EffectID::capitalLauncherSkillCruiseCitadelThermalDamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1474]},
			}},
			{EffectID::gunneryMaxRangeFalloffTrackingSpeedBonus, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[92]},{modifiers[785]},{modifiers[1001]},
			}},
			{EffectID::industrialCoreEffect2, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[1475]},{modifiers[1476]},{modifiers[1477]},{modifiers[1478]},{modifiers[1479]},{modifiers[1480]},{modifiers[1481]},{modifiers[1482]},{modifiers[1483]},{modifiers[1484]},{modifiers[1485]},{modifiers[1486]},{modifiers[1487]},{modifiers[1488]},{modifiers[1489]},{modifiers[1490]},{modifiers[1491]},{modifiers[1492]},{modifiers[1493]},{modifiers[1494]},{modifiers[1495]},{modifiers[1496]},{modifiers[1497]},{modifiers[1498]},{modifiers[1499]},{modifiers[1500]},{modifiers[1501]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkFalloffBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1502]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkFalloffBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1503]},
			}},
			{EffectID::droneRigStasisWebSpeedFactorBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1504]},
			}},
			{EffectID::amarrFrigateSkillLevelPreMulShipBonus3AFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1505]},
			}},
			{EffectID::caldariFrigateSkillLevelPreMulShipBonus3CFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1506]},
			}},
			{EffectID::gallenteFrigateSkillLevelPreMulShipBonus3GFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1507]},
			}},
			{EffectID::minmatarFrigateSkillLevelPreMulShipBonus3MFShip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1508]},
			}},
			{EffectID::shipBonusDroneDamageGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1509]},
			}},
			{EffectID::shipBonusWarpScramblerMaxRangeGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1510]},
			}},
			{EffectID::shipBonusHeatDamageATF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1511]},
			}},
			{EffectID::shipBonusSmallHybridMaxRangeATF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1512]},
			}},
			{EffectID::shipBonusSmallHybridTrackingSpeedATF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1513]},
			}},
			{EffectID::shipBonusHybridTrackingATC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1514]},
			}},
			{EffectID::shipBonusHybridFalloffATC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1515]},
			}},
			{EffectID::shipBonusWarpScramblerMaxRangeGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1516]},
			}},
			{EffectID::eliteBonusMaraudersCruiseAndTorpedoDamageRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1517]},{modifiers[1518]},{modifiers[1519]},{modifiers[1520]},{modifiers[1521]},{modifiers[1522]},{modifiers[1523]},{modifiers[1524]},
			}},
			{EffectID::shipBonusAoeVelocityCruiseAndTorpedoCB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1525]},{modifiers[1526]},
			}},
			{EffectID::shipCruiseAndTorpedoVelocityBonusCB3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[277]},{modifiers[278]},
			}},
			{EffectID::shipArmorEMAndExpAndkinAndThmResistanceAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[293]},{modifiers[294]},{modifiers[295]},{modifiers[296]},
			}},
			{EffectID::shipHeavyAssaultMissileEMAndExpAndKinAndThmDmgAC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1527]},{modifiers[1528]},{modifiers[1529]},{modifiers[1530]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyAndHeavyAssaultAndAssaultMissileLauncherROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[719]},{modifiers[720]},{modifiers[721]},
			}},
			{EffectID::eliteBonusBlackOpsECMGravAndLadarAndMagnetometricAndRadarStrength1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1531]},{modifiers[1532]},{modifiers[1533]},{modifiers[1534]},
			}},
			{EffectID::shipCruiseAndSiegeLauncherROFBonus2CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[555]},{modifiers[556]},
			}},
			{EffectID::oreIndustrialSkillLevelPostMulShipBonusOreIndustrial1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1535]},
			}},
			{EffectID::oreIndustrialSkillLevelPostMulShipBonusOreIndustrial2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1536]},
			}},
			{EffectID::shipBonusNoctisSalvageCycle, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1537]},
			}},
			{EffectID::shipBonusNoctisTractorCycle, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1538]},
			}},
			{EffectID::shipBonusNoctisTractorVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1539]},
			}},
			{EffectID::shipBonusNoctisTractorRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1540]},
			}},
			{EffectID::offensiveDefensiveReduction, Effect::MetaInfo::Category::system, false, false, {
				
			}},
			{EffectID::subsystemBonusCaldariPropulsionWarpCapacitor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1541]},
			}},
			{EffectID::hackOrbital, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1542]},
			}},
			{EffectID::shipBonusSmallEnergyWeaponOptimalRangeATF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1543]},
			}},
			{EffectID::shipBonusSmallEnergyTurretDamageATF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1544]},
			}},
			{EffectID::shipBonusMissileLauncherHeavyROFATC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1545]},
			}},
			{EffectID::shipBonusMissileLauncherAssaultROFATC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1546]},
			}},
			{EffectID::shipBonusMissileLauncherHeavyAssaultROFATC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1547]},
			}},
			{EffectID::eliteBonusBlackOpsECMBurstGravAndLadarAndMagnetoAndRadar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1548]},{modifiers[1549]},{modifiers[1550]},{modifiers[1551]},
			}},
			{EffectID::salvagingAccessDifficultyBonusMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1552]},
			}},
			{EffectID::hackingAccessDifficultyBonusMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1553]},
			}},
			{EffectID::archaeologyAccessDifficultyBonusMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1554]},
			}},
			{EffectID::dataMiningSkillBoostAccessDifficultyBonusAbsolutePercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1555]},
			}},
			{EffectID::ecmGravimetricStrengthBonusPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1556]},
			}},
			{EffectID::ecmLadarStrengthBonusPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1557]},
			}},
			{EffectID::ecmMagnetometricStrengthBonusPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1558]},
			}},
			{EffectID::ecmRadarStrengthBonusPercent, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1559]},
			}},
			{EffectID::skillConsumptionQuantityBonusPercentSkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1560]},
			}},
			{EffectID::jumpPortalConsumptionBonusPercentSkill, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1561]},
			}},
			{EffectID::salvagerModuleDurationReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1562]},
			}},
			{EffectID::bcLargeEnergyTurretPowerNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1563]},
			}},
			{EffectID::bcLargeHybridTurretPowerNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1564]},
			}},
			{EffectID::bcLargeProjectileTurretPowerNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1565]},
			}},
			{EffectID::bcLargeEnergyTurretCPUNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1566]},
			}},
			{EffectID::bcLargeHybridTurretCPUNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1567]},
			}},
			{EffectID::bcLargeProjectileTurretCPUNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1568]},
			}},
			{EffectID::bcLargeEnergyTurretCapacitorNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1569]},
			}},
			{EffectID::bcLargeHybridTurretCapacitorNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1570]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC3Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1571]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC4Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1572]},
			}},
			{EffectID::setBonusChristmasPowergrid, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1573]},
			}},
			{EffectID::setBonusChristmasCapacitorCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1574]},
			}},
			{EffectID::setBonusChristmasCPUOutput, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1575]},
			}},
			{EffectID::setBonusChristmasCapacitorRecharge2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1576]},
			}},
			{EffectID::maxRangeHiddenPreAssignmentWarpScrambleRange, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1577]},
			}},
			{EffectID::shipBonusDroneHitpointsGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1578]},
			}},
			{EffectID::shipBonusDroneArmorHitpointsGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1579]},
			}},
			{EffectID::shipBonusDroneShieldHitpointsGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1580]},
			}},
			{EffectID::shipSETTrackingBonusAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1581]},
			}},
			{EffectID::shipMissileSpeedBonusAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1582]},
			}},
			{EffectID::MWDSignatureRadiusRoleBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1583]},
			}},
			{EffectID::systemDamageFighters, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1584]},
			}},
			{EffectID::modifyShieldArmorHullResonancePostPercent, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},{modifiers[1078]},{modifiers[1079]},{modifiers[1080]},{modifiers[1081]},
			}},
			{EffectID::setWeaponSpeedToValue, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1585]},
			}},
			{EffectID::modifyShieldRechargeRatePassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[11]},
			}},
			{EffectID::damageMultiplierMultiplierActivation, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[1586]},
			}},
			{EffectID::missileDamageMultiplier, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1587]},
			}},
			{EffectID::setMassAndAgilityAndSpeed, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[1588]},{modifiers[1589]},{modifiers[1590]},
			}},
			{EffectID::microJumpDrive, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::skillMJDdurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1591]},
			}},
			{EffectID::adaptiveArmorHardener, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[1592]},{modifiers[1593]},{modifiers[1594]},{modifiers[1595]},
			}},
			{EffectID::scriptConsumptionQuantityBonus, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1596]},
			}},
			{EffectID::shipSETDmgBonus2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1597]},
			}},
			{EffectID::shipArmorRepairingGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1598]},
			}},
			{EffectID::fueledShieldBoosting, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[0]},
			}},
			{EffectID::shipHybridDamageBonusCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1599]},
			}},
			{EffectID::targetBreaker, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::skillTargetBreakerDurationBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1600]},
			}},
			{EffectID::skillTargetBreakerCapNeedBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1601]},
			}},
			{EffectID::shipBonusShieldBoosterMB1a, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1602]},
			}},
			{EffectID::shieldBoostAmplifierPassiveBooster, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[431]},{modifiers[523]},
			}},
			{EffectID::systemShieldRepairAmountShieldSkills, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1603]},{modifiers[1604]},
			}},
			{EffectID::shieldBoosterDurationBonusShieldSkills, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1605]},{modifiers[1606]},
			}},
			{EffectID::boosterShieldBoostAmountPenaltyShieldSkills, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1607]},{modifiers[1608]},
			}},
			{EffectID::eliteBonusAssaultShipLightMissileROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1609]},
			}},
			{EffectID::eliteBonusAssaultShipRocketROF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1610]},
			}},
			{EffectID::eliteBonusMarauderShieldBonus2a, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1611]},
			}},
			{EffectID::shipBonusMissileKineticlATF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1612]},
			}},
			{EffectID::skillReactiveArmorHardenerDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1613]},{modifiers[1614]},
			}},
			{EffectID::skillWarAllyCostModifier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1615]},
			}},
			{EffectID::relationsAllyCostSkillBoost, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1616]},
			}},
			{EffectID::missileSkillAoeCloudSizeBonusAllIncludingCapitals, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[453]},
			}},
			{EffectID::shipEnergyTCapNeedBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1617]},
			}},
			{EffectID::shipSETDmgBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1618]},
			}},
			{EffectID::shipArmorEMResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1619]},
			}},
			{EffectID::shipArmorEXResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1620]},
			}},
			{EffectID::shipArmorKNResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1621]},
			}},
			{EffectID::shipArmorTHResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1622]},
			}},
			{EffectID::shipHybridRangeBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1623]},
			}},
			{EffectID::shipMissileKineticDamageRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1624]},
			}},
			{EffectID::shipShieldEMResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1625]},
			}},
			{EffectID::shipShieldExplosiveResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1626]},
			}},
			{EffectID::shipShieldKineticResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1627]},
			}},
			{EffectID::shipShieldThermalResistanceRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1628]},
			}},
			{EffectID::shipSHTDmgBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1629]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1630]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerMaxTargetRangeBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1631]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerScanResolutionBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1632]},
			}},
			{EffectID::shipArmorRepairingRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1633]},
			}},
			{EffectID::shipVelocityBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1634]},
			}},
			{EffectID::minmatarShipEwTargetPainterRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1635]},
			}},
			{EffectID::shipSPTDmgBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1636]},
			}},
			{EffectID::shipShieldBoostRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1637]},
			}},
			{EffectID::shipECMScanStrengthBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1638]},{modifiers[1639]},{modifiers[1640]},{modifiers[1641]},
			}},
			{EffectID::shipBonusDroneMiningAmountRole, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1642]},
			}},
			{EffectID::shipBonusMiningDroneAmountPercentRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1643]},
			}},
			{EffectID::shipBonusDroneHitpointsRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1644]},{modifiers[1645]},{modifiers[1646]},
			}},
			{EffectID::shipBonusSalvageCycleAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1647]},
			}},
			{EffectID::shipBonusSalvageCycleCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1648]},
			}},
			{EffectID::shipBonusSalvageCycleGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1649]},
			}},
			{EffectID::shipBonusSalvageCycleMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1650]},
			}},
			{EffectID::baseDefenderAllyCostCharAssignment, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1651]},
			}},
			{EffectID::iceHarvesterDurationMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1652]},
			}},
			{EffectID::iceHarvesterCapacitorNeedMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1653]},
			}},
			{EffectID::miningYieldMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1654]},
			}},
			{EffectID::shipBonusIceHarvesterDurationORE3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1655]},
			}},
			{EffectID::shipBonusTargetPainterOptimalMF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1656]},
			}},
			{EffectID::shipBonusOreHoldORE2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1657]},
			}},
			{EffectID::shipBonusShieldCapacityORE2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1658]},
			}},
			{EffectID::mercoxitCrystalBonus, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1659]},
			}},
			{EffectID::shipMissileKineticDamageCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1660]},
			}},
			{EffectID::shipMissileVelocityCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1661]},
			}},
			{EffectID::maxTargetingRangeBonusPostPercentPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[167]},
			}},
			{EffectID::shipBonusDroneHitpointsGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1662]},{modifiers[1663]},{modifiers[1664]},
			}},
			{EffectID::shipShieldBoostMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1665]},
			}},
			{EffectID::shipBonusShieldTransferCapNeedCF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1666]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1667]},
			}},
			{EffectID::shipBonusShieldTransferCapNeedMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1668]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1669]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1670]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmountGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1671]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedAF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1672]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmount2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1673]},
			}},
			{EffectID::shipBonusDroneTrackingGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1674]},
			}},
			{EffectID::shipBonusScanProbeStrength2AF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1675]},
			}},
			{EffectID::energyTransferArrayTransferAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1676]},
			}},
			{EffectID::shipBonusShieldTransferCapneedMC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1677]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedAC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1678]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmountAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1679]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmountGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1680]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1681]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1682]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerOptimalBonusGC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1683]},
			}},
			{EffectID::minmatarShipEwTargetPainterMC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1684]},
			}},
			{EffectID::shipMissileRofCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1685]},{modifiers[1686]},{modifiers[1687]},
			}},
			{EffectID::shipPTurretFalloffBonusMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1688]},
			}},
			{EffectID::shipHTDamageBonusCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1689]},
			}},
			{EffectID::shipMETCDamageBonusAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1690]},
			}},
			{EffectID::miningFrigateSkillLevelPostMulShipBonusORE1frig, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1691]},
			}},
			{EffectID::miningFrigateSkillLevelPostMulShipBonusORE2frig, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1692]},
			}},
			{EffectID::shipMiningBonusOREfrig1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1693]},
			}},
			{EffectID::GCHYieldMultiplyPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1694]},
			}},
			{EffectID::shipMissileVelocityPirateFactionRocket, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1695]},
			}},
			{EffectID::shipGCHYieldBonusOREfrig2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1696]},
			}},
			{EffectID::skillReactiveArmorHardenerCapNeedBonus, Effect::MetaInfo::Category::generic, true, true, {
				{modifiers[1697]},{modifiers[1698]},
			}},
			{EffectID::salvageDroneEffect, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::shipBonusDroneMWDboostrole, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1699]},
			}},
			{EffectID::droneSalvageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1700]},
			}},
			{EffectID::droneSalvageSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1701]},
			}},
			{EffectID::sensorIntegritySkillLevelPreMulSensorStrengthBonusSelf, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1702]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusGravimetric, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1703]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusLadar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1704]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusMagnetometric, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1705]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusRadar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1706]},
			}},
			{EffectID::shipEnergyVampireAmountBonusFixedAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1707]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerFalloffBonusGC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1708]},
			}},
			{EffectID::trackingSpeedBonusEffectHybrids, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1709]},
			}},
			{EffectID::trackingSpeedBonusEffectLasers, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1710]},
			}},
			{EffectID::trackingSpeedBonusEffectProjectiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1711]},
			}},
			{EffectID::spaceAnchorEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1712]},
			}},
			{EffectID::armorUpgradesSkillBoostMassPenaltyReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1713]},
			}},
			{EffectID::armorUpgradesMassPenaltyReductionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1714]},
			}},
			{EffectID::shipSETTrackingBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1715]},
			}},
			{EffectID::shipSETOptimalBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1716]},
			}},
			{EffectID::shipNOSTransferAmountBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1717]},
			}},
			{EffectID::shipNeutDestabilizationAmountBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1718]},
			}},
			{EffectID::shipWebVelocityBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1719]},
			}},
			{EffectID::shipDroneMWDSpeedBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1720]},
			}},
			{EffectID::shipRocketMaxVelocityBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1721]},
			}},
			{EffectID::shipLightMissileMaxVelocityBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1722]},
			}},
			{EffectID::shipSHTTrackingSpeedBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1723]},
			}},
			{EffectID::shipSHTFalloffBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1724]},
			}},
			{EffectID::shipSPTTrackingSpeedBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1725]},
			}},
			{EffectID::shipSPTFalloffBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1726]},
			}},
			{EffectID::shipSPTOptimalRangeBonusRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1727]},
			}},
			{EffectID::shipProjectileDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1728]},
			}},
			{EffectID::shipHeavyAssaultMissileEMDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1729]},
			}},
			{EffectID::shipHeavyAssaultMissileKinDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1730]},
			}},
			{EffectID::shipHeavyAssaultMissileThermDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1731]},
			}},
			{EffectID::shipHeavyAssaultMissileExpDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1732]},
			}},
			{EffectID::shipHeavyMissileEMDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1733]},
			}},
			{EffectID::shipHeavyMissileExpDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1734]},
			}},
			{EffectID::shipHeavyMissileKinDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1735]},
			}},
			{EffectID::shipHeavyMissileThermDmgPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1736]},
			}},
			{EffectID::shipScanProbeStrengthBonusPirateCruiser, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1737]},
			}},
			{EffectID::modifyActiveShieldResonancePostPercent, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::modifyActiveArmorResonancePostPercent, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::shipSmallMissileExpDmgCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1738]},{modifiers[1739]},
			}},
			{EffectID::shipSmallMissileKinDmgCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1740]},{modifiers[1741]},
			}},
			{EffectID::shipSmallMissileThermDmgCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1742]},{modifiers[1743]},
			}},
			{EffectID::shipSmallMissileEMDmgCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1744]},{modifiers[1745]},
			}},
			{EffectID::reconShipCloakCpuBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1746]},
			}},
			{EffectID::covertOpsCloakCpuPercentBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1747]},
			}},
			{EffectID::covertCloakCPUAddition, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1748]},
			}},
			{EffectID::covertOpsCloakCpuPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1749]},
			}},
			{EffectID::covertCynoCpuPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1750]},
			}},
			{EffectID::warfareLinkCPUAddition, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1751]},
			}},
			{EffectID::warfareLinkCpuPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1752]},
			}},
			{EffectID::blockadeRunnerCloakCpuPercentBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1753]},
			}},
			{EffectID::drawbackRepairSystemsPGNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1754]},
			}},
			{EffectID::drawbackCapRepPGNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1755]},
			}},
			{EffectID::fueledArmorRepair, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[7]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusAD1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1756]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusAD2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1757]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusCD1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1758]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusCD2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1759]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusGD1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1760]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusGD2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1761]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusMD1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1762]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusMD2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1763]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusABC1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1764]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusABC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1765]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusCBC1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1766]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusCBC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1767]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusGBC1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1768]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusGBC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1769]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusMBC1Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1770]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusMBC2Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1771]},
			}},
			{EffectID::shipLaserCapNeed2AD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1772]},
			}},
			{EffectID::shipLaserTracking2AD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1773]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierAD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1774]},
			}},
			{EffectID::shipBonusDroneHitpointsAD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1775]},{modifiers[1776]},{modifiers[1777]},
			}},
			{EffectID::shipHybridRange1CD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1778]},
			}},
			{EffectID::shipHybridTrackingCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1779]},
			}},
			{EffectID::shipBonusFrigateSizedMissileKineticDamageCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1780]},
			}},
			{EffectID::shipRocketKineticDmgCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1781]},
			}},
			{EffectID::shipBonusAoeVelocityRocketsCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1782]},
			}},
			{EffectID::shipBonusAoeVelocityStandardMissilesCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1783]},
			}},
			{EffectID::shipHybridFallOff1GD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1784]},
			}},
			{EffectID::shipHybridTracking1GD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1785]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1786]},
			}},
			{EffectID::shipBonusDroneHitpointsGD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1787]},{modifiers[1788]},{modifiers[1789]},
			}},
			{EffectID::shipProjectileDamageMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1790]},
			}},
			{EffectID::shipProjectileTracking1MD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1791]},
			}},
			{EffectID::shipBonusFrigateSizedLightMissileExplosiveDamageMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1792]},
			}},
			{EffectID::shipRocketExplosiveDmgMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1793]},
			}},
			{EffectID::shipBonusMWDSignatureRadiusMD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1794]},
			}},
			{EffectID::shipArmorEMResistance1ABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1795]},
			}},
			{EffectID::shipArmorExplosiveResistance1ABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1796]},
			}},
			{EffectID::shipArmorKineticResistance1ABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1797]},
			}},
			{EffectID::shipArmorThermResistance1ABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1798]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1799]},
			}},
			{EffectID::shipBonusDroneHitpointsABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1800]},{modifiers[1801]},{modifiers[1802]},
			}},
			{EffectID::shipLaserCapABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1803]},
			}},
			{EffectID::shipLaserDamageBonusABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1804]},
			}},
			{EffectID::shipHybridOptimal1CBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1805]},
			}},
			{EffectID::shipShieldEmResistance1CBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1806]},
			}},
			{EffectID::shipShieldExplosiveResistance1CBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1807]},
			}},
			{EffectID::shipShieldKineticResistance1CBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1808]},
			}},
			{EffectID::shipShieldThermalResistance1CBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1809]},
			}},
			{EffectID::shipBonusHeavyAssaultMissileKineticDamageCBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1810]},
			}},
			{EffectID::shipBonusHeavyMissileKineticDamageCBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1811]},
			}},
			{EffectID::shipHybridDmg1GBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1812]},
			}},
			{EffectID::shipArmorRepairing1GBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1813]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1814]},
			}},
			{EffectID::shipBonusDroneHitpointsGBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1815]},{modifiers[1816]},{modifiers[1817]},
			}},
			{EffectID::shipBonusHeavyMissileLauncherRofMBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1818]},
			}},
			{EffectID::shipBonusHeavyAssaultMissileLauncherRofMBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1819]},
			}},
			{EffectID::shipShieldBoost1MBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1820]},
			}},
			{EffectID::shipBonusProjectileDamageMBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1821]},
			}},
			{EffectID::shipProjectileRof1MBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1822]},
			}},
			{EffectID::shipLargeLaserCapABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1823]},
			}},
			{EffectID::shipLargeLaserDamageBonusABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1824]},
			}},
			{EffectID::shipHybridRangeBonusCBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1825]},
			}},
			{EffectID::shipHybridDamageBonusCBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1826]},
			}},
			{EffectID::shipLargeHybridTrackingBonusGBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1827]},
			}},
			{EffectID::shipHybridDamageBonusGBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1828]},
			}},
			{EffectID::shipProjectileRofBonusMBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1829]},
			}},
			{EffectID::shipProjectileFalloffBonusMBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1830]},
			}},
			{EffectID::armorAllRepairSystemsAmountBonusPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1831]},{modifiers[1832]},
			}},
			{EffectID::eliteBonusViolatorsRepairSystemsArmorDamageAmount2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1833]},
			}},
			{EffectID::shipBonusRepairSystemsBonusATC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1834]},
			}},
			{EffectID::shipBonusRepairSystemsArmorRepairAmountGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1835]},
			}},
			{EffectID::damageCloudChanceReductionFixed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1836]},
			}},
			{EffectID::deepCoreMiningSkillBoostDamageCloudChanceReductionMul, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1837]},
			}},
			{EffectID::shipHeavyMissileAOECloudSizeCBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1838]},
			}},
			{EffectID::shipHeavyAssaultMissileAOECloudSizeCBC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1839]},
			}},
			{EffectID::shipHybridTrackingGBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1840]},
			}},
			{EffectID::shipEnergyTrackingABC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1841]},
			}},
			{EffectID::shipBonusMETOptimalAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1842]},
			}},
			{EffectID::shipMissileEMDamageCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1843]},
			}},
			{EffectID::shipMissileThermDamageCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1844]},
			}},
			{EffectID::shipMissileExpDamageCC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1845]},
			}},
			{EffectID::shipMissileKinDamageCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1846]},
			}},
			{EffectID::shipHeavyAssaultMissileAOECloudSizeCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1847]},
			}},
			{EffectID::shipHeavyMissileAOECloudSizeCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1848]},
			}},
			{EffectID::shipBonusDroneTrackingGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1849]},
			}},
			{EffectID::shipBonusDroneMWDboostGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1850]},
			}},
			{EffectID::baseMaxScanDeviationModifierModuleOnline2None, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1851]},
			}},
			{EffectID::systemScanDurationModuleModifier, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1852]},
			}},
			{EffectID::baseSensorStrengthModifierModule, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1853]},
			}},
			{EffectID::shipMissileHeavyAssaultVelocityABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1854]},
			}},
			{EffectID::shipMissileHeavyVelocityABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1855]},
			}},
			{EffectID::shipLaserCap1ABC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1856]},
			}},
			{EffectID::shipMissileVelocityCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1857]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1858]},
			}},
			{EffectID::shipBonusDroneArmorHitPointsAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1859]},
			}},
			{EffectID::shipBonusDroneShieldHitPointsAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1860]},
			}},
			{EffectID::shipBonusDroneStructureHitPointsAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1861]},
			}},
			{EffectID::shipBonusEnergyNeutRangeAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1862]},
			}},
			{EffectID::shipBonusEnergyVampireRangeAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1863]},
			}},
			{EffectID::shipLargeHybridTurretRofGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1864]},
			}},
			{EffectID::shipBonusDroneTrackingGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1865]},
			}},
			{EffectID::shipBonusDroneOptimalRangeGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1866]},
			}},
			{EffectID::shipBonusMissileAoeVelocityMB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1867]},
			}},
			{EffectID::shipBonusAoeVelocityCruiseMissilesMB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1868]},
			}},
			{EffectID::shipBonusLargeEnergyTurretTrackingAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1869]},
			}},
			{EffectID::hackingSkillVirusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1870]},
			}},
			{EffectID::dataMiningSkillLevelVirusCoherenceBonusModifier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1871]},
			}},
			{EffectID::archaeologySkillVirusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1872]},
			}},
			{EffectID::systemStandardMissileKineticDamage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[1873]},
			}},
			{EffectID::shipTorpedoAOECloudSize1CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1874]},
			}},
			{EffectID::shipCruiseMissileAOECloudSize1CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1875]},
			}},
			{EffectID::shipCruiseMissileROFCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1876]},
			}},
			{EffectID::shipTorpedoROFCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1877]},
			}},
			{EffectID::minigameVirusStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1878]},{modifiers[1879]},
			}},
			{EffectID::shieldOperationRechargeratebonusPostPercentOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[161]},
			}},
			{EffectID::shipBonusAgilityCI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1880]},
			}},
			{EffectID::shipBonusAgilityMI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1881]},
			}},
			{EffectID::shipBonusAgilityGI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1882]},
			}},
			{EffectID::shipBonusAgilityAI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1883]},
			}},
			{EffectID::shipBonusOreCapacityGI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1884]},
			}},
			{EffectID::shipBonusAmmoBayMI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1885]},
			}},
			{EffectID::shipBonusPICommoditiesHoldGI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1886]},
			}},
			{EffectID::shipBonusMineralBayGI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1887]},
			}},
			{EffectID::setBonusChristmasBonusVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1888]},
			}},
			{EffectID::setBonusChristmasAgilityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1889]},
			}},
			{EffectID::setBonusChristmasShieldCapacityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1890]},
			}},
			{EffectID::setBonusChristmasArmorHPBonus2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1891]},
			}},
			{EffectID::shipSPTOptimalBonusMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1892]},
			}},
			{EffectID::shipBonusProjectileDamageMBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1893]},
			}},
			{EffectID::eliteBonusCommandShipHAMRoFCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1894]},
			}},
			{EffectID::eliteBonusCommandShipHMRoFCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1895]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyAssaultMissileExplosionVelocityCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1896]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyAssaultMissileExplosionRadiusCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1897]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyMissileExplosionRadiusCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1898]},
			}},
			{EffectID::eliteBonusCommandShipMediumHybridDamageCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1899]},
			}},
			{EffectID::eliteBonusCommandShipMediumHybridTrackingCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1900]},
			}},
			{EffectID::eliteBonusCommandShipHeavyDroneTrackingCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1901]},
			}},
			{EffectID::eliteBonusCommandShipHeavyDroneVelocityCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1902]},
			}},
			{EffectID::eliteBonusCommandShipMediumHybridRoFCS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1903]},
			}},
			{EffectID::eliteBonusCommandShipHeavyAssaultMissileDamageCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1904]},{modifiers[1905]},{modifiers[1906]},{modifiers[1907]},
			}},
			{EffectID::eliteBonusCommandShipHeavyMissileDamageCS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1908]},{modifiers[1909]},{modifiers[1910]},{modifiers[1911]},
			}},
			{EffectID::skillJumpCloneCooldownReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1912]},
			}},
			{EffectID::shipBonusHMLKineticDamageAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1913]},
			}},
			{EffectID::shipBonusHMLEMDamageAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1914]},
			}},
			{EffectID::shipBonusHMLThermDamageAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1915]},
			}},
			{EffectID::shipBonusHMLExploDamageAC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1916]},
			}},
			{EffectID::shipBonusHMLVelocityEliteBonusHeavyGunship1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1917]},
			}},
			{EffectID::shipBonusHAMVelocityEliteBonusHeavyGunship1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1918]},
			}},
			{EffectID::shipBonusArmorRepAmountGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1919]},
			}},
			{EffectID::shipBonusHeavyDroneSpeedGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1920]},
			}},
			{EffectID::shipBonusHeavyDRoneTrackingGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1921]},
			}},
			{EffectID::shipBonusSentryDroneOptimalRangeEliteBonusHeavyGunship2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1922]},
			}},
			{EffectID::shipBonusSentryDroneTrackingEliteBonusHeavyGunship2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1923]},
			}},
			{EffectID::shipBonusShieldBoostAmountMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1924]},
			}},
			{EffectID::roleBonusMarauderMJDRReactivationDelayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1925]},
			}},
			{EffectID::subSystemBonusAmarrDefensiveInformationWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1926]},{modifiers[1927]},{modifiers[1928]},{modifiers[1929]},{modifiers[1930]},
			}},
			{EffectID::subSystemBonusAmarrDefensiveSkirmishWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1931]},{modifiers[1932]},{modifiers[1933]},{modifiers[1934]},{modifiers[1935]},
			}},
			{EffectID::subSystemBonusCaldariOffensiveCommandBursts, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1936]},{modifiers[1937]},{modifiers[1938]},{modifiers[1939]},{modifiers[1940]},{modifiers[1941]},{modifiers[1942]},{modifiers[1943]},{modifiers[1944]},{modifiers[1945]},{modifiers[1946]},{modifiers[1947]},{modifiers[1948]},{modifiers[1949]},{modifiers[1950]},
			}},
			{EffectID::subSystemBonusCaldariDefensiveSkirmishWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1951]},{modifiers[1952]},{modifiers[1953]},{modifiers[1954]},{modifiers[1955]},
			}},
			{EffectID::subSystemBonusGallenteDefensiveSkirmishWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1956]},{modifiers[1957]},{modifiers[1958]},{modifiers[1959]},{modifiers[1960]},
			}},
			{EffectID::subSystemBonusGallenteOffensiveCommandBursts, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1961]},{modifiers[1962]},{modifiers[1963]},{modifiers[1964]},{modifiers[1965]},{modifiers[1966]},{modifiers[1967]},{modifiers[1968]},{modifiers[1969]},{modifiers[1970]},{modifiers[1971]},{modifiers[1972]},{modifiers[1973]},{modifiers[1974]},{modifiers[1975]},
			}},
			{EffectID::subSystemBonusMinmatarDefensiveSiegeWarfare, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1976]},{modifiers[1977]},{modifiers[1978]},{modifiers[1979]},{modifiers[1980]},
			}},
			{EffectID::subSystemBonusMinmatarOffensiveCommandBursts, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1981]},{modifiers[1982]},{modifiers[1983]},{modifiers[1984]},{modifiers[1985]},{modifiers[1986]},{modifiers[1987]},{modifiers[1988]},{modifiers[1989]},{modifiers[1990]},{modifiers[1991]},{modifiers[1992]},{modifiers[1993]},{modifiers[1994]},{modifiers[1995]},
			}},
			{EffectID::commandShipSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1996]},
			}},
			{EffectID::eliteBonusCommandShipArmoredCS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[1997]},{modifiers[1998]},{modifiers[1999]},{modifiers[2000]},{modifiers[2001]},
			}},
			{EffectID::eliteBonusCommandShipSiegeCS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2002]},{modifiers[2003]},{modifiers[2004]},{modifiers[2005]},{modifiers[2006]},
			}},
			{EffectID::eliteBonusCommandShipSkirmishCS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2007]},{modifiers[2008]},{modifiers[2009]},{modifiers[2010]},{modifiers[2011]},
			}},
			{EffectID::eliteBonusCommandShipInformationCS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2012]},{modifiers[2013]},{modifiers[2014]},{modifiers[2015]},{modifiers[2016]},
			}},
			{EffectID::capacitorEmissionSystemskill, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2017]},
			}},
			{EffectID::shipBonusLargeEnergyTurretMaxRangeAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2018]},
			}},
			{EffectID::shipBonusHTFalloffGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2019]},
			}},
			{EffectID::piCustomsOfficeTaxReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2020]},
			}},
			{EffectID::piTaxReductionModifierSkillModifier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2021]},
			}},
			{EffectID::shipBonusRHMLROF2CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2022]},
			}},
			{EffectID::shipBonusRHMLROFCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2023]},
			}},
			{EffectID::shipBonusRHMLROFMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2024]},
			}},
			{EffectID::shipBonusCruiseROFMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2025]},
			}},
			{EffectID::shipBonusTorpedoROFMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2026]},
			}},
			{EffectID::shipBonusCruiseMissileEMDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2027]},
			}},
			{EffectID::shipBonusCruiseMissileThermDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2028]},
			}},
			{EffectID::shipBonusCruiseMissileKineticDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2029]},
			}},
			{EffectID::shipBonusCruiseMissileExploDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2030]},
			}},
			{EffectID::shipBonusTorpedoMissileExploDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2031]},
			}},
			{EffectID::shipBonusTorpedoMissileEMDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2032]},
			}},
			{EffectID::shipBonusTorpedoMissileThermDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2033]},
			}},
			{EffectID::shipBonusTorpedoMissileKineticDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2034]},
			}},
			{EffectID::shipBonusHeavyMissileEMDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2035]},
			}},
			{EffectID::shipBonusHeavyMissileThermDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2036]},
			}},
			{EffectID::shipBonusHeavyMissileKineticDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2037]},
			}},
			{EffectID::shipBonusHeavyMissileExploDmgMB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2038]},
			}},
			{EffectID::shipBonusMissileVelocityCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2039]},
			}},
			{EffectID::covertOpsCloakCPUPercentRoleBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2040]},
			}},
			{EffectID::shipArmorResistanceAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[531]},{modifiers[532]},{modifiers[533]},{modifiers[534]},
			}},
			{EffectID::interceptor2ShieldResist, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2041]},{modifiers[2042]},{modifiers[2043]},{modifiers[2044]},
			}},
			{EffectID::interceptor2ProjectileDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2045]},
			}},
			{EffectID::shipBonusSmallMissileExplosionRadiusCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2046]},{modifiers[2047]},
			}},
			{EffectID::shipBonusMissileVelocityAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2048]},
			}},
			{EffectID::eliteBonusInterdictorsArmorResist1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2049]},{modifiers[2050]},{modifiers[2051]},{modifiers[2052]},
			}},
			{EffectID::setWarpSpeedMultiplier, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2053]},
			}},
			{EffectID::implantSetWarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2054]},
			}},
			{EffectID::shipBonusMETOptimalRangePirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2055]},
			}},
			{EffectID::shipHybridOptimalGD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2056]},
			}},
			{EffectID::eliteBonusInterdictorsMWDSigRadius2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2057]},
			}},
			{EffectID::shipSHTOptimalBonusGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2058]},
			}},
			{EffectID::shipBonusRemoteRepairAmountPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2059]},
			}},
			{EffectID::shipBonusLETOptimalRangePirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2060]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageExpRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2061]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageKinRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2062]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageEMRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2063]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageThermRole1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2064]},
			}},
			{EffectID::shipScanProbeStrengthBonusPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2065]},
			}},
			{EffectID::shipBonusRemoteRepairRangePirateFaction2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2066]},{modifiers[2067]},
			}},
			{EffectID::overloadSelfTrackingModuleBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[2068]},{modifiers[2069]},{modifiers[2070]},
			}},
			{EffectID::overloadSelfSensorModuleBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[2071]},{modifiers[2072]},{modifiers[2073]},{modifiers[2074]},{modifiers[2075]},{modifiers[2076]},
			}},
			{EffectID::overloadSelfPainterBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[2077]},
			}},
			{EffectID::repairDroneHullBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2078]},
			}},
			{EffectID::shipMissileRoFMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2079]},
			}},
			{EffectID::shipBonusSPTFalloffMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2080]},
			}},
			{EffectID::miningAmountBonusBonusActivation, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[2081]},
			}},
			{EffectID::ewSkillTrackingDisruptionRangeDisruptionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2082]},{modifiers[2083]},
			}},
			{EffectID::shipBonusEwWeaponDisruptionStrengthRookie, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2084]},{modifiers[2085]},{modifiers[2086]},{modifiers[2087]},{modifiers[2088]},{modifiers[2089]},{modifiers[2090]},
			}},
			{EffectID::shipBonusAfterburnerSpeedFactor2CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2091]},
			}},
			{EffectID::shipBonusSentryDroneDamageMultiplierPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2092]},
			}},
			{EffectID::shipBonusHeavyDroneDamageMultiplierPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2093]},
			}},
			{EffectID::shipBonusSentryDroneHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2094]},
			}},
			{EffectID::shipBonusSentryDroneArmorHpPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2095]},
			}},
			{EffectID::shipBonusSentryDroneShieldHpPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2096]},
			}},
			{EffectID::shipBonusHeavyDroneShieldHpPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2097]},
			}},
			{EffectID::shipBonusHeavyDroneArmorHpPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2098]},
			}},
			{EffectID::shipBonusHeavyDroneHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2099]},
			}},
			{EffectID::shipBonusKineticMissileDamageGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2100]},
			}},
			{EffectID::shipBonusThermalMissileDamageGB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2101]},
			}},
			{EffectID::shipBonusAfterburnerSpeedFactorCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2102]},
			}},
			{EffectID::shipBonusKineticMissileDamageGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2103]},
			}},
			{EffectID::shipBonusThermalMissileDamageGF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2104]},
			}},
			{EffectID::shipBonusLightDroneDamageMultiplierPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2105]},
			}},
			{EffectID::shipBonusLightDroneHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2106]},
			}},
			{EffectID::shipBonusLightDroneArmorHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2107]},
			}},
			{EffectID::shipBonusLightDroneShieldHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2108]},
			}},
			{EffectID::shipBonusAfterburnerSpeedFactorCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2109]},
			}},
			{EffectID::shipBonusMediumDroneDamageMultiplierPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2110]},
			}},
			{EffectID::shipBonusMediumDroneHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2111]},
			}},
			{EffectID::shipBonusMediumDroneArmorHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2112]},
			}},
			{EffectID::shipBonusMediumDroneShieldHPPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2113]},
			}},
			{EffectID::shipBonusKineticMissileDamageGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2114]},
			}},
			{EffectID::shipBonusThermalMissileDamageGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2115]},
			}},
			{EffectID::shipBonusTDOptimalBonusAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2116]},
			}},
			{EffectID::shipBonusMiningDurationORE3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2117]},
			}},
			{EffectID::shipBonusMiningIceHarvestingRangeORE2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2118]},{modifiers[2119]},
			}},
			{EffectID::eliteBargeShieldResistance1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2120]},{modifiers[2121]},{modifiers[2122]},{modifiers[2123]},
			}},
			{EffectID::eliteBargeBonusMiningDurationBarge2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2124]},
			}},
			{EffectID::expeditionFrigateSkillLevelPostMulEliteBonusExpedition1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2125]},
			}},
			{EffectID::expeditionFrigateSkillLevelPostMulEliteBonusExpedition2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2126]},
			}},
			{EffectID::eliteBonusExpeditionMining1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2127]},
			}},
			{EffectID::eliteBonusExpeditionSigRadius2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2128]},
			}},
			{EffectID::shipBonusNosferatuOverride, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2129]},
			}},
			{EffectID::shipMissileEMDamageCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2130]},
			}},
			{EffectID::shipMissileKinDamageCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2131]},
			}},
			{EffectID::shipMissileThermDamageCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2132]},
			}},
			{EffectID::shipMissileExploDamageCB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2133]},
			}},
			{EffectID::shipBonusWarpScrambleMaxRangeGB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2134]},
			}},
			{EffectID::shipBonusMissileExplosionDelayPirateFaction2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2135]},
			}},
			{EffectID::drawbackCargoCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2136]},
			}},
			{EffectID::eliteIndustrialWarpSpeedBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2137]},
			}},
			{EffectID::shipBonusShieldBoostCI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2138]},
			}},
			{EffectID::shipBonusShieldBoostMI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2139]},
			}},
			{EffectID::shipBonusArmorRepairAI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2140]},
			}},
			{EffectID::shipBonusArmorRepairGI2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2141]},
			}},
			{EffectID::eliteIndustrialFleetCapacity1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2142]},
			}},
			{EffectID::eliteIndustrialShieldResists2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2143]},{modifiers[2144]},{modifiers[2145]},{modifiers[2146]},
			}},
			{EffectID::eliteIndustrialArmorResists2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2147]},{modifiers[2148]},{modifiers[2149]},{modifiers[2150]},
			}},
			{EffectID::eliteIndustrialABHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2151]},
			}},
			{EffectID::eliteIndustrialMWDHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2152]},
			}},
			{EffectID::eliteIndustrialArmorHardenerHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2153]},
			}},
			{EffectID::eliteIndustrialReactiveArmorHardenerHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2154]},
			}},
			{EffectID::eliteIndustrialShieldHardenerHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2155]},
			}},
			{EffectID::eliteIndustrialShieldBoosterHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2156]},{modifiers[2157]},
			}},
			{EffectID::eliteIndustrialArmorRepairHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2158]},{modifiers[2159]},
			}},
			{EffectID::warpSpeedAddition, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2160]},
			}},
			{EffectID::roleBonusBulkheadCPU, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2161]},
			}},
			{EffectID::advancedIndustryManufacturingTimeBonusPostPercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2162]},
			}},
			{EffectID::advancedIndustryCopyTimeBonusPostPercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2163]},
			}},
			{EffectID::advancedIndustryInventionTimeBonusPostPercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2164]},
			}},
			{EffectID::advancedIndustrySkillBoostAdvancedIndustrySkillIndustryJobTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2165]},
			}},
			{EffectID::advancedIndustryManufactureTimeResearchTimeBonusPostPercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2166]},
			}},
			{EffectID::advancedIndustryMaterialResearchTimeBonusPostPercent, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2167]},
			}},
			{EffectID::onlineJumpDriveConsumptionAmountBonusPercentage, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[1000]},
			}},
			{EffectID::systemRemoteCapTransmitterAmount, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2168]},
			}},
			{EffectID::systemArmorHP, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[19]},
			}},
			{EffectID::systemEnergyNeutMultiplier, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2169]},
			}},
			{EffectID::systemEnergyVampireMultiplier, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2170]},
			}},
			{EffectID::systemDamageExplosiveBombs, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2171]},
			}},
			{EffectID::systemDamageKineticBombs, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2172]},
			}},
			{EffectID::systemDamageThermalBombs, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2173]},
			}},
			{EffectID::systemDamageEMBombs, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2174]},
			}},
			{EffectID::systemAoeCloudSize, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2175]},
			}},
			{EffectID::systemTargetPainterMultiplier, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2176]},
			}},
			{EffectID::systemWebifierStrengthMultiplier, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2177]},
			}},
			{EffectID::systemNeutBombs, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2178]},
			}},
			{EffectID::systemGravimetricECMBomb, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2179]},
			}},
			{EffectID::systemLadarECMBomb, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2180]},
			}},
			{EffectID::systemMagnetrometricECMBomb, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2181]},
			}},
			{EffectID::systemRadarECMBomb, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2182]},
			}},
			{EffectID::systemDroneTracking, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[2183]},
			}},
			{EffectID::warpScrambleBlockMWDWithNPCEffect, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[8]},{modifiers[2184]},{modifiers[2185]},
			}},
			{EffectID::shipBonusSmallMissileExplosionRadiusCF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2186]},{modifiers[2187]},
			}},
			{EffectID::shipRocketRoFBonusAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2188]},
			}},
			{EffectID::eliteBonusInterdictorsSHTRoF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2189]},
			}},
			{EffectID::shipMissileLauncherRoFAD1Fixed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2190]},
			}},
			{EffectID::cloakingPrototype, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[214]},
			}},
			{EffectID::drawbackWarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2191]},
			}},
			{EffectID::shipMETDamageBonusAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2192]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsMETOptimal, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2193]},
			}},
			{EffectID::shipHybridTrackingGC, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2194]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsHybridOptimal1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2195]},
			}},
			{EffectID::resistanceKillerShieldAll, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2196]},{modifiers[2197]},{modifiers[2198]},{modifiers[2199]},
			}},
			{EffectID::resistanceKillerArmorAll, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2200]},{modifiers[2201]},{modifiers[2202]},{modifiers[2203]},
			}},
			{EffectID::resistanceKillerHullAll, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2204]},{modifiers[2205]},{modifiers[2206]},{modifiers[2207]},
			}},
			{EffectID::resistanceKillerShieldArmorAll, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2196]},{modifiers[2197]},{modifiers[2198]},{modifiers[2199]},{modifiers[2200]},{modifiers[2201]},{modifiers[2202]},{modifiers[2203]},
			}},
			{EffectID::freighterO1SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2208]},
			}},
			{EffectID::freighterO2SkillLevel, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2209]},
			}},
			{EffectID::freighterSMACapacityBonusO1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2210]},
			}},
			{EffectID::freighterAgilityBonus2O2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2211]},
			}},
			{EffectID::tacticalDestroyerAmarrSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2212]},
			}},
			{EffectID::tacticalDestroyerAmarrSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2213]},
			}},
			{EffectID::tacticalDestroyerAmarrSkillLevel3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2214]},
			}},
			{EffectID::shipSETDamageAmarrTacticalDestroyer1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2215]},
			}},
			{EffectID::shipSETCapNeedAmarrTacticalDestroyer2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2216]},
			}},
			{EffectID::shipHeatDamageAmarrTacticalDestroyer3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2217]},
			}},
			{EffectID::probeLauncherCPUPercentRoleBonusT3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2218]},
			}},
			{EffectID::shipModeMaxTargetRangePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2219]},
			}},
			{EffectID::shipModeSETOptimalRangePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2220]},
			}},
			{EffectID::shipModeScanStrengthPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2221]},{modifiers[2222]},{modifiers[2223]},{modifiers[2224]},
			}},
			{EffectID::modeSigRadiusPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2225]},
			}},
			{EffectID::modeArmorResonancePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2226]},{modifiers[2227]},{modifiers[2228]},{modifiers[2229]},
			}},
			{EffectID::modeAgilityPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2230]},
			}},
			{EffectID::modeVelocityPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2231]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalRS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2232]},
			}},
			{EffectID::shipBonusEnergyNosOptimalRS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2233]},
			}},
			{EffectID::reconShipSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2234]},
			}},
			{EffectID::eliteReconBonusMHTOptimalRange1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2235]},
			}},
			{EffectID::eliteReconBonusMPTdamage1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2236]},
			}},
			{EffectID::remoteCapacitorTransmitterPowerNeedBonusEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2237]},
			}},
			{EffectID::tacticalDestroyerMinmatarSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2238]},
			}},
			{EffectID::tacticalDestroyerMinmatarSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2239]},
			}},
			{EffectID::tacticalDestroyerMinmatarSkillLevel3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2240]},
			}},
			{EffectID::shipHeatDamageMinmatarTacticalDestroyer3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2241]},
			}},
			{EffectID::shipSPTDamageMinmatarTacticalDestroyer1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2242]},
			}},
			{EffectID::shipSPTOptimalMinmatarTacticalDestroyer2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2243]},
			}},
			{EffectID::shipModeSPTTrackingPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2244]},
			}},
			{EffectID::modeMWDSigRadiusPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2245]},
			}},
			{EffectID::modeShieldResonancePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2246]},{modifiers[2247]},{modifiers[2248]},{modifiers[2249]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldRechargeRate, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2250]},
			}},
			{EffectID::gallenteCruiserSkillLevelPreMulShipBonusGC3Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2251]},
			}},
			{EffectID::shipBonusSentryDamageMultiplierGC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2252]},
			}},
			{EffectID::shipBonusSentryHPGC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2253]},
			}},
			{EffectID::shipBonusSentryArmorHPGC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2254]},
			}},
			{EffectID::shipBonusSentryShieldHPGC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2255]},
			}},
			{EffectID::shipBonusLightDroneDamageMultiplierGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2256]},
			}},
			{EffectID::shipBonusMediumDroneDamageMultiplierGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2257]},
			}},
			{EffectID::shipBonusHeavyDroneDamageMultiplierGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2258]},
			}},
			{EffectID::shipBonusHeavyDroneHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2259]},
			}},
			{EffectID::shipBonusHeavyDroneArmorHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2260]},
			}},
			{EffectID::shipBonusHeavyDroneShieldHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2261]},
			}},
			{EffectID::shipBonusMediumDroneShieldHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2262]},
			}},
			{EffectID::shipBonusMediumDroneArmorHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2263]},
			}},
			{EffectID::shipBonusMediumDroneHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2264]},
			}},
			{EffectID::shipBonusLightDroneHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2265]},
			}},
			{EffectID::shipBonusLightDroneArmorHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2266]},
			}},
			{EffectID::shipBonusLightDroneShieldHPGC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2267]},
			}},
			{EffectID::entosisLink, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::shipModeMissileVelocityPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2268]},
			}},
			{EffectID::shipHeatDamageCaldariTacticalDestroyer3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2269]},
			}},
			{EffectID::tacticalDestroyerCaldariSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2270]},
			}},
			{EffectID::tacticalDestroyerCaldariSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2271]},
			}},
			{EffectID::tacticalDestroyerCaldariSkillLevel3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2272]},
			}},
			{EffectID::shipSmallMissileDmgPirateFaction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2273]},{modifiers[2274]},{modifiers[2275]},{modifiers[2276]},{modifiers[2277]},{modifiers[2278]},{modifiers[2279]},{modifiers[2280]},
			}},
			{EffectID::shipMissileRoFCaldariTacticalDestroyer1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2281]},
			}},
			{EffectID::shipBonusHeavyAssaultMissileAllDamageMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2282]},{modifiers[2283]},{modifiers[2284]},{modifiers[2285]},
			}},
			{EffectID::shipBonusHeavyMissileAllDamageMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2286]},{modifiers[2287]},{modifiers[2288]},{modifiers[2289]},
			}},
			{EffectID::shipBonusLightMissileAllDamageMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2290]},{modifiers[2291]},{modifiers[2292]},{modifiers[2293]},
			}},
			{EffectID::shipMissileReloadTimeCaldariTacticalDestroyer2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2294]},
			}},
			{EffectID::entosisDurationMultiply, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2295]},
			}},
			{EffectID::missileVelocityBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2296]},
			}},
			{EffectID::missileExplosionDelayBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2297]},
			}},
			{EffectID::missileAOECloudSizeBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2298]},
			}},
			{EffectID::missileAOEVelocityBonusOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2299]},
			}},
			{EffectID::scriptMissileGuidanceComputerAOECloudSizeBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2300]},
			}},
			{EffectID::scriptMissileGuidanceComputerAOEVelocityBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2301]},
			}},
			{EffectID::scriptMissileGuidanceComputerMissileVelocityBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2302]},
			}},
			{EffectID::scriptMissileGuidanceComputerExplosionDelayBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2303]},
			}},
			{EffectID::missileGuidanceComputerBonus4, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[2296]},{modifiers[2297]},{modifiers[2298]},{modifiers[2299]},
			}},
			{EffectID::overloadSelfMissileGuidanceBonus5, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[2304]},{modifiers[2305]},{modifiers[2306]},{modifiers[2307]},{modifiers[2308]},
			}},
			{EffectID::tacticalDestroyerGallenteSkillLevel1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2309]},
			}},
			{EffectID::tacticalDestroyerGallenteSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2310]},
			}},
			{EffectID::tacticalDestroyerGallenteSkillLevel3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2311]},
			}},
			{EffectID::shipHeatDamageGallenteTacticalDestroyer3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2312]},
			}},
			{EffectID::shipSHTRoFGallenteTacticalDestroyer1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2313]},
			}},
			{EffectID::shipSHTTrackingGallenteTacticalDestroyer2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2314]},
			}},
			{EffectID::modeHullResonancePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2315]},{modifiers[2316]},{modifiers[2317]},{modifiers[2318]},
			}},
			{EffectID::shipModeSHTOptimalRangePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2319]},
			}},
			{EffectID::modeMWDCapPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2320]},
			}},
			{EffectID::modeMWDBoostPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2321]},
			}},
			{EffectID::modeArmorRepDurationPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2322]},
			}},
			{EffectID::passiveSpeedLimit, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2323]},
			}},
			{EffectID::systemMaxVelocityPercentage, Effect::MetaInfo::Category::system, false, false, {
				{modifiers[617]},
			}},
			{EffectID::shipBonusWDFGnullPenalties, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2324]},{modifiers[2325]},{modifiers[2326]},
			}},
			{EffectID::entosisCPUPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2327]},
			}},
			{EffectID::entosisCPUAddition, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2328]},
			}},
			{EffectID::battlecruiserMETRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2329]},{modifiers[2330]},
			}},
			{EffectID::battlecruiserMHTRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2331]},{modifiers[2332]},
			}},
			{EffectID::battlecruiserMPTRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2333]},{modifiers[2334]},
			}},
			{EffectID::battlecruiserMissileRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2335]},
			}},
			{EffectID::battlecruiserDroneSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2336]},
			}},
			{EffectID::shipHybridDmg1CBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2337]},
			}},
			{EffectID::shipBonusProjectileTrackingMBC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2338]},
			}},
			{EffectID::shipModuleRemoteCapacitorTransmitter, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[2339]},
			}},
			{EffectID::shipModuleRemoteHullRepairer, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[2340]},
			}},
			{EffectID::shipModuleRemoteShieldBooster, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[3]},
			}},
			{EffectID::energyNeutralizerFalloff, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[2341]},
			}},
			{EffectID::shipModuleRemoteArmorRepairer, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[206]},
			}},
			{EffectID::expeditionFrigateShieldResistance1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2342]},{modifiers[2343]},{modifiers[2344]},{modifiers[2345]},
			}},
			{EffectID::expeditionFrigateBonusIceHarvestingCycleTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2346]},
			}},
			{EffectID::energyNosferatuFalloff, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[2341]},
			}},
			{EffectID::doomsdaySlash, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::microJumpPortalDrive, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::commandDestroyerSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2347]},
			}},
			{EffectID::commandDestroyerSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2348]},
			}},
			{EffectID::commandDestroyerSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2349]},
			}},
			{EffectID::roleBonusCDLinksPGReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2350]},
			}},
			{EffectID::structureEnergyNeutralizerFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::structureWarpScrambleBlockMWDWithNPCEffect, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[8]},{modifiers[2184]},{modifiers[2185]},
			}},
			{EffectID::structureTargetMaxTargetRangeAndScanResolutionBonusAssistance, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[2351]},{modifiers[2352]},
			}},
			{EffectID::structureTargetGunneryMaxRangeFalloffTrackingSpeedBonusAssistance, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[2353]},{modifiers[2354]},{modifiers[2355]},
			}},
			{EffectID::structureMissileGuidanceComputerBonus4, Effect::MetaInfo::Category::active, false, true, {
				{modifiers[2296]},{modifiers[2297]},{modifiers[2298]},{modifiers[2299]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalRS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2356]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffRS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2357]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffRS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2358]},
			}},
			{EffectID::shipBonusEnergyNosOptimalRS1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2359]},
			}},
			{EffectID::shipBonusEnergyNosFalloffRS2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2360]},
			}},
			{EffectID::shipBonusEnergyNosFalloffRS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2361]},
			}},
			{EffectID::miningFrigateBonusIceHarvestingCycleTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2362]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2363]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2364]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2365]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2366]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2367]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2368]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2369]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAB2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2370]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalEAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2371]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffEAF3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2372]},
			}},
			{EffectID::shipBonusEnergyNosOptimalEAF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2373]},
			}},
			{EffectID::shipBonusEnergyNosFalloffEAF3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2374]},
			}},
			{EffectID::electronicAttackShipsSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2375]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2376]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAF3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2377]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2378]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAF3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2379]},
			}},
			{EffectID::amarrCruiserSkillLevelPreMulShipBonusAC3Ship, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2380]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2381]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2382]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2383]},
			}},
			{EffectID::shipBonusNosOptimalFalloffAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2384]},{modifiers[2385]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2386]},
			}},
			{EffectID::serviceSlot, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::shipBonusThermMissileDmgMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2387]},
			}},
			{EffectID::shipBonusEMMissileDmgMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2388]},
			}},
			{EffectID::shipBonusKineticMissileDmgMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2389]},
			}},
			{EffectID::shipBonusExplosiveMissileDmgMD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2390]},
			}},
			{EffectID::eliteBonusCommandDestroyerSkirmish1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2391]},{modifiers[2392]},{modifiers[2393]},{modifiers[2394]},{modifiers[2395]},
			}},
			{EffectID::eliteBonusCommandDestroyerShield1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2396]},{modifiers[2397]},{modifiers[2398]},{modifiers[2399]},{modifiers[2400]},
			}},
			{EffectID::eliteBonusCommandDestroyerMJFGspool2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2401]},
			}},
			{EffectID::shipBonusEMShieldResistanceMD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2402]},
			}},
			{EffectID::shipBonusKineticShieldResistanceMD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2403]},
			}},
			{EffectID::shipBonusThermalShieldResistanceMD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2404]},
			}},
			{EffectID::shipBonusExplosiveShieldResistanceMD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2405]},
			}},
			{EffectID::scriptscanGravimetricStrengthBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2406]},
			}},
			{EffectID::scriptscanLadarStrengthBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2407]},
			}},
			{EffectID::scriptscanMagnetometricStrengthBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2408]},
			}},
			{EffectID::scriptscanRadarStrengthBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2409]},
			}},
			{EffectID::shipBonusThermalMissileDamageCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2410]},
			}},
			{EffectID::shipBonusEMMissileDamageCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2411]},
			}},
			{EffectID::shipBonusKineticMissileDamageCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2412]},
			}},
			{EffectID::shipBonusExplosiveMissileDamageCD1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2413]},
			}},
			{EffectID::shipBonusShieldEMResistanceCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2414]},
			}},
			{EffectID::shipBonusShieldThermalResistanceCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2415]},
			}},
			{EffectID::shipBonusShieldKineticResistanceCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2416]},
			}},
			{EffectID::shipBonusShieldExplosiveResistanceCD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2417]},
			}},
			{EffectID::eliteBonusCommandDestroyerInfo1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2418]},{modifiers[2419]},{modifiers[2420]},{modifiers[2421]},{modifiers[2422]},
			}},
			{EffectID::shipBonusKineticArmorResistanceAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2423]},
			}},
			{EffectID::shipBonusThermalArmorResistanceAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2424]},
			}},
			{EffectID::shipBonusEMArmorResistanceAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2425]},
			}},
			{EffectID::shipBonusExplosiveArmorResistanceAD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2426]},
			}},
			{EffectID::eliteBonusCommandDestroyerArmored1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2427]},{modifiers[2428]},{modifiers[2429]},{modifiers[2430]},{modifiers[2431]},
			}},
			{EffectID::shipBonusKineticArmorResistanceGD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2432]},
			}},
			{EffectID::shipBonusEMArmorResistanceGD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2433]},
			}},
			{EffectID::shipBonusThermalArmorResistanceGD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2434]},
			}},
			{EffectID::shipBonusExplosiveArmorResistanceGD2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2435]},
			}},
			{EffectID::setFixedResonance, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[2436]},{modifiers[2437]},{modifiers[2438]},{modifiers[2439]},{modifiers[2440]},{modifiers[2441]},{modifiers[2442]},{modifiers[2443]},{modifiers[2444]},{modifiers[2445]},{modifiers[2446]},{modifiers[2447]},
			}},
			{EffectID::shipSmallMissileKinDmgCF3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2448]},{modifiers[2449]},
			}},
			{EffectID::shipMissileKinDamageCC3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2450]},
			}},
			{EffectID::roleBonusWDRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2451]},{modifiers[2452]},
			}},
			{EffectID::roleBonusWDCapCPU, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2453]},{modifiers[2454]},
			}},
			{EffectID::shipBonusEwWeaponDisruptionStrengthAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2455]},{modifiers[2456]},{modifiers[2457]},{modifiers[2458]},{modifiers[2459]},{modifiers[2460]},{modifiers[2461]},
			}},
			{EffectID::roleBonusECMCapCPU, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2462]},{modifiers[2463]},
			}},
			{EffectID::roleBonusECMRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2464]},{modifiers[2465]},
			}},
			{EffectID::shipBonusJustScramblerRangeGF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2466]},
			}},
			{EffectID::roleBonusJustScramblerStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2467]},
			}},
			{EffectID::shipBonusAoeVelocityRocketsMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2468]},
			}},
			{EffectID::shipRocketEMThermKinDmgMF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2469]},{modifiers[2470]},{modifiers[2471]},
			}},
			{EffectID::shipRocketExpDmgMF3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2472]},
			}},
			{EffectID::roleBonusStasisRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2473]},
			}},
			{EffectID::shieldTransporterFalloffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2474]},{modifiers[2475]},
			}},
			{EffectID::shipShieldTransferFalloffMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2476]},
			}},
			{EffectID::shipShieldTransferFalloffCC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2477]},
			}},
			{EffectID::shipRemoteArmorFalloffGC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2478]},
			}},
			{EffectID::shipRemoteArmorFalloffAC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2479]},
			}},
			{EffectID::armorRepairProjectorFalloffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2480]},{modifiers[2481]},
			}},
			{EffectID::droneHullRepairBonusEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2482]},
			}},
			{EffectID::logiFrigSkillMultiplier1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2483]},
			}},
			{EffectID::logiFrigSkillMultiplier2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2484]},
			}},
			{EffectID::eliteBonusLogiFrigArmorRepSpeedCap1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2485]},{modifiers[2486]},
			}},
			{EffectID::eliteBonusLogiFrigShieldRepSpeedCap1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2487]},{modifiers[2488]},
			}},
			{EffectID::eliteBonusLogiFrigArmorHP2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2489]},
			}},
			{EffectID::eliteBonusLogiFrigShieldHP2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2490]},
			}},
			{EffectID::eliteBonusLogiFrigSignature2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2491]},
			}},
			{EffectID::overloadSelfMissileGuidanceModuleBonus, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[2305]},{modifiers[2306]},{modifiers[2307]},{modifiers[2308]},
			}},
			{EffectID::ignoreCloakVelocityPenalty, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2492]},
			}},
			{EffectID::ewSkillGuidanceDisruptionBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2493]},{modifiers[2494]},{modifiers[2495]},{modifiers[2496]},
			}},
			{EffectID::shipBonusEwWeaponDisruptionStrengthAC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2497]},{modifiers[2498]},{modifiers[2499]},{modifiers[2500]},{modifiers[2501]},{modifiers[2502]},{modifiers[2503]},
			}},
			{EffectID::skillStructureMissileDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2504]},{modifiers[2505]},{modifiers[2506]},{modifiers[2507]},{modifiers[2508]},{modifiers[2509]},{modifiers[2510]},{modifiers[2511]},{modifiers[2512]},{modifiers[2513]},{modifiers[2514]},{modifiers[2515]},
			}},
			{EffectID::skillStructureElectronicSystemsCapNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2516]},{modifiers[2517]},{modifiers[2518]},
			}},
			{EffectID::skillStructureEngineeringSystemsCapNeedBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2519]},{modifiers[2520]},
			}},
			{EffectID::structureRigAoeVelocityBonusSingleTargetMissiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2521]},{modifiers[2522]},
			}},
			{EffectID::structureRigVelocityBonusSingleTargetMissiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2523]},{modifiers[2524]},
			}},
			{EffectID::structureRigNeutralizerMaxRangeFalloffEffectiveness, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2525]},{modifiers[2526]},
			}},
			{EffectID::structureRigNeutralizerCapacitorNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2527]},
			}},
			{EffectID::structureRigEWMaxRangeFalloff, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2528]},{modifiers[2529]},{modifiers[2530]},{modifiers[2531]},{modifiers[2532]},{modifiers[2533]},
			}},
			{EffectID::structureRigEWCapacitorNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2534]},{modifiers[2535]},
			}},
			{EffectID::structureRigMaxTargets, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2536]},
			}},
			{EffectID::structureRigSensorResolution, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2537]},
			}},
			{EffectID::structureRigExplosionRadiusBonusAoEMissiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2538]},
			}},
			{EffectID::structureRigVelocityBonusAoeMissiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2539]},
			}},
			{EffectID::structureRigPDBmaxRange, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2540]},
			}},
			{EffectID::structureRigPDBCapacitorNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2541]},
			}},
			{EffectID::structureRigFighterHP, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2542]},{modifiers[2543]},{modifiers[2544]},{modifiers[2545]},{modifiers[2546]},{modifiers[2547]},
			}},
			{EffectID::structureRigFighterMaxVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2548]},{modifiers[2549]},
			}},
			{EffectID::structureRigDoomsdayDamageLoss, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2550]},
			}},
			{EffectID::remoteSensorDampFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::shipModuleGuidanceDisruptor, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::shipModuleTrackingDisruptor, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::remoteTargetPaintFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::remoteWebifierFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::remoteSensorBoostFalloff, Effect::MetaInfo::Category::target, false, true, {
				
			}},
			{EffectID::shipModuleRemoteTrackingComputer, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[2353]},{modifiers[2354]},{modifiers[2355]},
			}},
			{EffectID::fighterAbilityMissiles, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityEnergyNeutralizer, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityStasisWebifier, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityWarpDisruption, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityECM, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityEvasiveManeuvers, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::fighterAbilityAfterburner, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::fighterAbilityMicroWarpDrive, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::fighterAbilityMicroJumpDrive, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::pointDefense, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::tractorBeamShip, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::structureBumpingModule, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::lightningWeapon, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::structureMissileGuidanceEnhancer, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2551]},{modifiers[2552]},{modifiers[2553]},{modifiers[2554]},{modifiers[2555]},{modifiers[2556]},{modifiers[2557]},{modifiers[2558]},
			}},
			{EffectID::structureBallisticControlSystem, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2559]},{modifiers[2560]},{modifiers[2561]},{modifiers[2562]},{modifiers[2563]},{modifiers[2564]},{modifiers[2565]},{modifiers[2566]},{modifiers[2567]},{modifiers[2568]},
			}},
			{EffectID::structureMissileGuidanceComputerBonus5, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[2569]},{modifiers[2570]},{modifiers[2571]},{modifiers[2572]},
			}},
			{EffectID::structureScanResolutionActivePercentage, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[232]},
			}},
			{EffectID::fighterAbilityTackle, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityAttackM, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::remoteECMFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::doomsdayBeamDOT, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayConeDOT, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayHOG, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::structureRigDoomsdayTargetAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2573]},
			}},
			{EffectID::doomsdayAOEWeb, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOENeut, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEPaint, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOETrack, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEGuide, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEDamp, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEBubble, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::emergencyHullEnergizer, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::fighterAbilityLaunchBomb, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::modifyEnergyWarfareResistance, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2574]},
			}},
			{EffectID::scriptSensorBoosterSensorStrengthBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2575]},{modifiers[2576]},{modifiers[2577]},{modifiers[2578]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtAmarr, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2579]},{modifiers[2580]},{modifiers[2581]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtCaldari, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2582]},{modifiers[2583]},{modifiers[2584]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtGallente, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2585]},{modifiers[2586]},{modifiers[2587]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtMinmatar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2588]},{modifiers[2589]},{modifiers[2590]},
			}},
			{EffectID::shipBonusDreadnoughtA1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2591]},
			}},
			{EffectID::shipBonusDreadnoughtA2ArmorResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2592]},{modifiers[2593]},{modifiers[2594]},{modifiers[2595]},
			}},
			{EffectID::shipBonusDreadnoughtA3CapNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2596]},
			}},
			{EffectID::shipBonusDreadnoughtC1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2597]},{modifiers[2598]},{modifiers[2599]},{modifiers[2600]},{modifiers[2601]},{modifiers[2602]},{modifiers[2603]},{modifiers[2604]},{modifiers[2605]},{modifiers[2606]},{modifiers[2607]},{modifiers[2608]},
			}},
			{EffectID::shipBonusDreadnoughtC2ShieldResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2609]},{modifiers[2610]},{modifiers[2611]},{modifiers[2612]},
			}},
			{EffectID::shipBonusDreadnoughtG1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2613]},
			}},
			{EffectID::shipBonusDreadnoughtG2ROFBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2614]},
			}},
			{EffectID::shipBonusDreadnoughtG3RepairTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2615]},
			}},
			{EffectID::shipBonusDreadnoughtM1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2616]},
			}},
			{EffectID::shipBonusDreadnoughtM2ROFBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2617]},
			}},
			{EffectID::shipBonusDreadnoughtM3RepairTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2618]},
			}},
			{EffectID::doomsdayAOEECM, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryAmarr, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2619]},{modifiers[2620]},{modifiers[2621]},{modifiers[2622]},
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryCaldari, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2623]},{modifiers[2624]},{modifiers[2625]},{modifiers[2626]},
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryGallente, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2627]},{modifiers[2628]},{modifiers[2629]},{modifiers[2630]},
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryMinmatar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2631]},{modifiers[2632]},{modifiers[2633]},{modifiers[2634]},
			}},
			{EffectID::shipBonusForceAuxiliaryA1RemoteRepairAndCapAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2635]},{modifiers[2636]},
			}},
			{EffectID::shipBonusForceAuxiliaryA2ArmorResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2637]},{modifiers[2638]},{modifiers[2639]},{modifiers[2640]},
			}},
			{EffectID::shipBonusForceAuxiliaryA3CapCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2641]},
			}},
			{EffectID::shipBonusForceAuxiliaryA4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2642]},{modifiers[2643]},{modifiers[2644]},{modifiers[2645]},{modifiers[2646]},{modifiers[2647]},{modifiers[2648]},{modifiers[2649]},{modifiers[2650]},{modifiers[2651]},
			}},
			{EffectID::shipBonusForceAuxiliaryM4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2652]},{modifiers[2653]},{modifiers[2654]},{modifiers[2655]},{modifiers[2656]},{modifiers[2657]},{modifiers[2658]},{modifiers[2659]},{modifiers[2660]},{modifiers[2661]},
			}},
			{EffectID::shipBonusForceAuxiliaryG4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2662]},{modifiers[2663]},{modifiers[2664]},{modifiers[2665]},{modifiers[2666]},{modifiers[2667]},{modifiers[2668]},{modifiers[2669]},{modifiers[2670]},{modifiers[2671]},
			}},
			{EffectID::shipBonusForceAuxiliaryC4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2672]},{modifiers[2673]},{modifiers[2674]},{modifiers[2675]},{modifiers[2676]},{modifiers[2677]},{modifiers[2678]},{modifiers[2679]},{modifiers[2680]},{modifiers[2681]},
			}},
			{EffectID::shipBonusRole1CommandBurstCPUBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2682]},
			}},
			{EffectID::shipBonusForceAuxiliaryC1RemoteBoostAndCapAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2683]},{modifiers[2684]},
			}},
			{EffectID::shipBonusForceAuxiliaryC2ShieldResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2685]},{modifiers[2686]},{modifiers[2687]},{modifiers[2688]},
			}},
			{EffectID::shipBonusForceAuxiliaryC3CapCapacity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2689]},
			}},
			{EffectID::shipBonusForceAuxiliaryG1RemoteCycleTime, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2690]},{modifiers[2691]},
			}},
			{EffectID::shipBonusForceAuxiliaryG2LocalRepairAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2692]},{modifiers[2693]},
			}},
			{EffectID::shipBonusForceAuxiliaryG3CapBoosterStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2694]},
			}},
			{EffectID::shipBonusForceAuxiliaryM1RemoteDuration, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2695]},{modifiers[2696]},
			}},
			{EffectID::shipBonusForceAuxiliaryM2LocalBoostAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2697]},{modifiers[2698]},
			}},
			{EffectID::shipBonusForceAuxiliaryM3CapBoosterStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2699]},
			}},
			{EffectID::fighterAbilityKamikaze, Effect::MetaInfo::Category::target, false, false, {
				
			}},
			{EffectID::moduleBonusDroneNavigationComputer, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2700]},{modifiers[2701]},
			}},
			{EffectID::moduleBonusDroneDamageAmplifier, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2702]},{modifiers[2703]},{modifiers[2704]},{modifiers[2705]},
			}},
			{EffectID::moduleBonusOmnidirectionalTrackingLink, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[2706]},{modifiers[2707]},{modifiers[2708]},{modifiers[2709]},{modifiers[2710]},{modifiers[2711]},{modifiers[2712]},{modifiers[2713]},{modifiers[2714]},{modifiers[2715]},{modifiers[2716]},{modifiers[2717]},{modifiers[2718]},
			}},
			{EffectID::moduleBonusOmnidirectionalTrackingLinkOverload, Effect::MetaInfo::Category::overloaded, false, false, {
				{modifiers[2068]},{modifiers[2069]},{modifiers[2070]},{modifiers[2305]},{modifiers[2306]},
			}},
			{EffectID::moduleBonusOmnidirectionalTrackingEnhancer, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2706]},{modifiers[2707]},{modifiers[2708]},{modifiers[2709]},{modifiers[2710]},{modifiers[2711]},{modifiers[2712]},{modifiers[2713]},{modifiers[2714]},{modifiers[2715]},{modifiers[2716]},{modifiers[2717]},{modifiers[2718]},
			}},
			{EffectID::skillBonusFighters, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2719]},{modifiers[2720]},{modifiers[2721]},
			}},
			{EffectID::skillBonusLightFighters, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2722]},
			}},
			{EffectID::skillBonusSupportFightersShield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2723]},
			}},
			{EffectID::skillBonusHeavyFighters, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2724]},{modifiers[2725]},{modifiers[2726]},
			}},
			{EffectID::citadelRigBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2727]},{modifiers[2728]},{modifiers[2729]},{modifiers[2730]},{modifiers[2731]},{modifiers[2732]},{modifiers[2733]},{modifiers[2734]},{modifiers[2735]},{modifiers[2736]},
			}},
			{EffectID::moduleBonusFighterSupportUnit, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[2737]},{modifiers[2738]},{modifiers[2739]},{modifiers[2740]},{modifiers[2741]},{modifiers[2742]},
			}},
			{EffectID::moduleBonusNetworkedSensorArray, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[232]},{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},{modifiers[1476]},{modifiers[1477]},{modifiers[2743]},{modifiers[2744]},{modifiers[2745]},{modifiers[2746]},{modifiers[2747]},{modifiers[2748]},{modifiers[2749]},{modifiers[2750]},{modifiers[2751]},{modifiers[2752]},{modifiers[2753]},
			}},
			{EffectID::citadelServiceFuelBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2754]},{modifiers[2755]},
			}},
			{EffectID::skillMultiplierFighterHangarSize, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2756]},
			}},
			{EffectID::skillBonusFighterHangarManagement, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2757]},
			}},
			{EffectID::skillBonusCapitalAutocannonSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2758]},
			}},
			{EffectID::skillBonusCapitalArtillerySpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2759]},
			}},
			{EffectID::skillBonusCapitalBlasterSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2760]},
			}},
			{EffectID::skillBonusCapitalRailgunSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2761]},
			}},
			{EffectID::skillBonusCapitalPulseLaserSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2762]},
			}},
			{EffectID::skillBonusCapitalBeamLaserSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2763]},
			}},
			{EffectID::skillBonusXLCruiseMissileSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2764]},
			}},
			{EffectID::skillBonusXLTorpedoSpecialization, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2765]},
			}},
			{EffectID::shipBonusRole2LogisticDroneRepAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2766]},{modifiers[2767]},{modifiers[2768]},
			}},
			{EffectID::moduleBonusTriageModule, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[33]},{modifiers[616]},{modifiers[617]},{modifiers[1475]},{modifiers[1476]},{modifiers[1477]},{modifiers[1478]},{modifiers[1479]},{modifiers[1480]},{modifiers[1481]},{modifiers[1482]},{modifiers[1483]},{modifiers[2743]},{modifiers[2744]},{modifiers[2745]},{modifiers[2746]},{modifiers[2747]},{modifiers[2748]},{modifiers[2749]},{modifiers[2769]},{modifiers[2770]},{modifiers[2771]},{modifiers[2772]},{modifiers[2773]},{modifiers[2774]},{modifiers[2775]},{modifiers[2776]},{modifiers[2777]},{modifiers[2778]},{modifiers[2779]},{modifiers[2780]},{modifiers[2781]},{modifiers[2782]},{modifiers[2783]},{modifiers[2784]},{modifiers[2785]},{modifiers[2786]},{modifiers[2787]},{modifiers[2788]},{modifiers[2789]},{modifiers[2790]},{modifiers[2791]},{modifiers[2792]},
			}},
			{EffectID::moduleBonusSiegeModule, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[1475]},{modifiers[1476]},{modifiers[1477]},{modifiers[1478]},{modifiers[1479]},{modifiers[1480]},{modifiers[1481]},{modifiers[1482]},{modifiers[2789]},{modifiers[2790]},{modifiers[2791]},{modifiers[2792]},{modifiers[2793]},{modifiers[2794]},{modifiers[2795]},{modifiers[2796]},{modifiers[2797]},{modifiers[2798]},{modifiers[2799]},{modifiers[2800]},{modifiers[2801]},{modifiers[2802]},{modifiers[2803]},{modifiers[2804]},{modifiers[2805]},{modifiers[2806]},{modifiers[2807]},{modifiers[2808]},{modifiers[2809]},{modifiers[2810]},{modifiers[2811]},{modifiers[2812]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierAmarr, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2813]},{modifiers[2814]},{modifiers[2815]},{modifiers[2816]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierCaldari, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2817]},{modifiers[2818]},{modifiers[2819]},{modifiers[2820]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierGallente, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2821]},{modifiers[2822]},{modifiers[2823]},{modifiers[2824]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierMinmatar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2825]},{modifiers[2826]},{modifiers[2827]},{modifiers[2828]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierAmarr, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2829]},{modifiers[2830]},{modifiers[2831]},{modifiers[2832]},{modifiers[2833]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierCaldari, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2834]},{modifiers[2835]},{modifiers[2836]},{modifiers[2837]},{modifiers[2838]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierGallente, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2839]},{modifiers[2840]},{modifiers[2841]},{modifiers[2842]},{modifiers[2843]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierMinmatar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2844]},{modifiers[2845]},{modifiers[2846]},{modifiers[2847]},{modifiers[2848]},
			}},
			{EffectID::shipBonusSupercarrierA3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2849]},
			}},
			{EffectID::shipBonusSupercarrierC3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2850]},
			}},
			{EffectID::shipBonusSupercarrierG3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2851]},
			}},
			{EffectID::shipBonusSupercarrierM3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2852]},
			}},
			{EffectID::shipBonusCarrierA4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2853]},{modifiers[2854]},{modifiers[2855]},{modifiers[2856]},{modifiers[2857]},{modifiers[2858]},{modifiers[2859]},{modifiers[2860]},{modifiers[2861]},{modifiers[2862]},
			}},
			{EffectID::shipBonusCarrierC4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2863]},{modifiers[2864]},{modifiers[2865]},{modifiers[2866]},{modifiers[2867]},{modifiers[2868]},{modifiers[2869]},{modifiers[2870]},{modifiers[2871]},{modifiers[2872]},
			}},
			{EffectID::shipBonusCarrierG4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2873]},{modifiers[2874]},{modifiers[2875]},{modifiers[2876]},{modifiers[2877]},{modifiers[2878]},{modifiers[2879]},{modifiers[2880]},{modifiers[2881]},{modifiers[2882]},
			}},
			{EffectID::shipBonusCarrierM4WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2883]},{modifiers[2884]},{modifiers[2885]},{modifiers[2886]},{modifiers[2887]},{modifiers[2888]},{modifiers[2889]},{modifiers[2890]},{modifiers[2891]},{modifiers[2892]},
			}},
			{EffectID::shipBonusCarrierA1ArmorResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2893]},{modifiers[2894]},{modifiers[2895]},{modifiers[2896]},
			}},
			{EffectID::shipBonusCarrierC1ShieldResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2897]},{modifiers[2898]},{modifiers[2899]},{modifiers[2900]},
			}},
			{EffectID::shipBonusCarrierG1FighterDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2901]},{modifiers[2902]},{modifiers[2903]},
			}},
			{EffectID::shipBonusCarrierM1FighterDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2904]},{modifiers[2905]},{modifiers[2906]},
			}},
			{EffectID::shipBonusSupercarrierA1FighterDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2907]},{modifiers[2908]},{modifiers[2909]},
			}},
			{EffectID::shipBonusSupercarrierC1FighterDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2910]},{modifiers[2911]},{modifiers[2912]},
			}},
			{EffectID::shipBonusSupercarrierG1FighterDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2913]},{modifiers[2914]},{modifiers[2915]},
			}},
			{EffectID::shipBonusSupercarrierM1FighterDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2916]},{modifiers[2917]},{modifiers[2918]},
			}},
			{EffectID::shipBonusSupercarrierA5WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2919]},{modifiers[2920]},{modifiers[2921]},{modifiers[2922]},{modifiers[2923]},{modifiers[2924]},{modifiers[2925]},{modifiers[2926]},{modifiers[2927]},{modifiers[2928]},
			}},
			{EffectID::shipBonusSupercarrierC5WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2929]},{modifiers[2930]},{modifiers[2931]},{modifiers[2932]},{modifiers[2933]},{modifiers[2934]},{modifiers[2935]},{modifiers[2936]},{modifiers[2937]},{modifiers[2938]},
			}},
			{EffectID::shipBonusSupercarrierG5WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2939]},{modifiers[2940]},{modifiers[2941]},{modifiers[2942]},{modifiers[2943]},{modifiers[2944]},{modifiers[2945]},{modifiers[2946]},{modifiers[2947]},{modifiers[2948]},
			}},
			{EffectID::shipBonusSupercarrierM5WarfareLinksBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2949]},{modifiers[2950]},{modifiers[2951]},{modifiers[2952]},{modifiers[2953]},{modifiers[2954]},{modifiers[2955]},{modifiers[2956]},{modifiers[2957]},{modifiers[2958]},
			}},
			{EffectID::shipBonusSupercarrierC2AfterburnerBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2959]},
			}},
			{EffectID::shipBonusSupercarrierA2FighterApplicationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2960]},{modifiers[2961]},
			}},
			{EffectID::shipBonusSupercarrierRole1NumWarfareLinks, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2962]},{modifiers[2963]},
			}},
			{EffectID::shipBonusSupercarrierRole2ArmorShieldModuleBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2964]},{modifiers[2965]},
			}},
			{EffectID::shipBonusSupercarrierA4BurstProjectorBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2966]},
			}},
			{EffectID::shipBonusSupercarrierC4BurstProjectorBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2967]},
			}},
			{EffectID::shipBonusSupercarrierG4BurstProjectorBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2968]},
			}},
			{EffectID::shipBonusSupercarrierM4BurstProjectorBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2969]},
			}},
			{EffectID::shipBonusCarrierRole1NumWarfareLinks, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2962]},{modifiers[2963]},
			}},
			{EffectID::shipBonusDreadnoughtC3ReloadBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2970]},
			}},
			{EffectID::shipBonusSupercarrierA2ArmorResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2971]},{modifiers[2972]},{modifiers[2973]},{modifiers[2974]},
			}},
			{EffectID::shipBonusSupercarrierC2ShieldResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2975]},{modifiers[2976]},{modifiers[2977]},{modifiers[2978]},
			}},
			{EffectID::shipBonusSupercarrierG2FighterHitpoints, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2979]},
			}},
			{EffectID::shipBonusSupercarrierM2FighterVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2980]},
			}},
			{EffectID::shipBonusCarrierA2SupportFighterBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2981]},{modifiers[2982]},
			}},
			{EffectID::shipBonusCarrierC2SupportFighterBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2983]},{modifiers[2984]},
			}},
			{EffectID::shipBonusCarrierG2SupportFighterBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2985]},{modifiers[2986]},
			}},
			{EffectID::shipBonusCarrierM2SupportFighterBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2987]},{modifiers[2988]},
			}},
			{EffectID::scriptResistanceBonusBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2989]},{modifiers[2990]},{modifiers[2991]},{modifiers[2992]},
			}},
			{EffectID::skillMultiplierShipBonusTitanAmarr, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2993]},{modifiers[2994]},{modifiers[2995]},{modifiers[2996]},
			}},
			{EffectID::skillMultiplierShipBonusTitanCaldari, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2997]},{modifiers[2998]},{modifiers[2999]},{modifiers[3000]},{modifiers[3001]},
			}},
			{EffectID::skillMultiplierShipBonusTitanGallente, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3002]},{modifiers[3003]},{modifiers[3004]},{modifiers[3005]},
			}},
			{EffectID::skillMultiplierShipBonusTitanMinmatar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3006]},{modifiers[3007]},{modifiers[3008]},{modifiers[3009]},
			}},
			{EffectID::shipBonusTitanA1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3010]},
			}},
			{EffectID::shipBonusTitanC1KinDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3011]},{modifiers[3012]},{modifiers[3013]},
			}},
			{EffectID::shipBonusTitanG1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3014]},
			}},
			{EffectID::shipBonusTitanM1DamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3015]},
			}},
			{EffectID::shipBonusTitanC2ROFBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3016]},{modifiers[3017]},{modifiers[3018]},
			}},
			{EffectID::shipBonusSupercarrierA4FighterApplicationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3019]},{modifiers[3020]},
			}},
			{EffectID::shipBonusRole1NumWarfareLinks, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2962]},{modifiers[2963]},
			}},
			{EffectID::shipBonusRole2ArmorPlatesShieldExtendersBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2964]},{modifiers[2965]},
			}},
			{EffectID::skillBonusDoomsdayRapidFiring, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3021]},
			}},
			{EffectID::shipBonusTitanA3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3022]},
			}},
			{EffectID::shipBonusTitanC3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3023]},
			}},
			{EffectID::shipBonusTitanG3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3024]},
			}},
			{EffectID::shipBonusTitanM3WarpStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3025]},
			}},
			{EffectID::shipModuleAncillaryRemoteArmorRepairer, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[206]},
			}},
			{EffectID::shipModuleAncillaryRemoteShieldBooster, Effect::MetaInfo::Category::target, false, true, {
				{modifiers[3]},
			}},
			{EffectID::shipBonusTitanA2CapNeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3026]},
			}},
			{EffectID::shipBonusTitanG2ROFBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3027]},
			}},
			{EffectID::shipBonusTitanM2ROFBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3028]},
			}},
			{EffectID::shipBonusRole3XLTorpdeoVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3029]},
			}},
			{EffectID::shipBonusTitanC5AllDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3030]},{modifiers[3031]},{modifiers[3032]},{modifiers[3033]},{modifiers[3034]},{modifiers[3035]},{modifiers[3036]},{modifiers[3037]},{modifiers[3038]},
			}},
			{EffectID::moduleBonusBastionModule, Effect::MetaInfo::Category::active, true, false, {
				{modifiers[431]},{modifiers[616]},{modifiers[617]},{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},{modifiers[660]},{modifiers[661]},{modifiers[662]},{modifiers[663]},{modifiers[664]},{modifiers[665]},{modifiers[666]},{modifiers[667]},{modifiers[668]},{modifiers[669]},{modifiers[670]},{modifiers[671]},{modifiers[1476]},{modifiers[1477]},{modifiers[1479]},{modifiers[1480]},{modifiers[1481]},{modifiers[1482]},{modifiers[1831]},{modifiers[2793]},{modifiers[3039]},{modifiers[3040]},{modifiers[3041]},{modifiers[3042]},{modifiers[3043]},{modifiers[3044]},{modifiers[3045]},{modifiers[3046]},{modifiers[3047]},{modifiers[3048]},{modifiers[3049]},{modifiers[3050]},
			}},
			{EffectID::higgsWarpBubbleImmuneRemoval, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3051]},
			}},
			{EffectID::shipBonusCarrierM3FighterVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3052]},
			}},
			{EffectID::shipBonusCarrierG3FighterHitpoints, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3053]},
			}},
			{EffectID::skillBonusDroneInterfacing, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[216]},{modifiers[615]},{modifiers[2719]},{modifiers[2720]},{modifiers[2721]},
			}},
			{EffectID::skillBonusDroneSharpshooting, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[578]},{modifiers[3054]},{modifiers[3055]},{modifiers[3056]},
			}},
			{EffectID::skillBonusDroneDurability, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[581]},{modifiers[3057]},{modifiers[3058]},{modifiers[3059]},
			}},
			{EffectID::skillMultiplierMaxVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3060]},
			}},
			{EffectID::skillBonusDroneNavigation, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3061]},{modifiers[3062]},
			}},
			{EffectID::skillMultiplierShieldBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3063]},
			}},
			{EffectID::moduleBonusCapitalDroneDurabilityEnhancer, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[579]},{modifiers[580]},{modifiers[581]},{modifiers[738]},{modifiers[2544]},
			}},
			{EffectID::moduleBonusCapitalDroneScopeChip, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[578]},{modifiers[738]},{modifiers[3054]},{modifiers[3055]},{modifiers[3056]},
			}},
			{EffectID::moduleBonusCapitalDroneSpeedAugmentor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[577]},{modifiers[738]},{modifiers[2548]},
			}},
			{EffectID::structureCombatRigSecurityModification, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3064]},{modifiers[3065]},{modifiers[3066]},{modifiers[3067]},{modifiers[3068]},{modifiers[3069]},{modifiers[3070]},{modifiers[3071]},{modifiers[3072]},{modifiers[3073]},
			}},
			{EffectID::structureReprocessingRigSecurityModification, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3074]},
			}},
			{EffectID::structureRigAsteroidOreYield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3075]},
			}},
			{EffectID::structureRigMoonOreYield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3076]},
			}},
			{EffectID::structureRigCalAmarrIceYield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3077]},
			}},
			{EffectID::structureRigGalMinIceYield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3078]},
			}},
			{EffectID::structureRigIceYield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3079]},
			}},
			{EffectID::skillStructureDoomsdayDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3080]},
			}},
			{EffectID::shipBonusRole3NumWarfareLinks, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3081]},{modifiers[3082]},
			}},
			{EffectID::structureModuleEffectStasisWebifier, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectTargetPainter, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectRemoteSensorDampener, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectECM, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectWeaponDisruption, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::npcEntityRemoteArmorRepairer, Effect::MetaInfo::Category::target, false, true, {
				
			}},
			{EffectID::npcEntityRemoteShieldBooster, Effect::MetaInfo::Category::target, false, true, {
				
			}},
			{EffectID::npcEntityRemoteHullRepairer, Effect::MetaInfo::Category::target, false, true, {
				
			}},
			{EffectID::remoteWebifierEntity, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::entityEnergyNeutralizerFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::remoteTargetPaintEntity, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::remoteSensorDampEntity, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::npcEntityWeaponDisruptor, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::entityECMFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::starbaseEnergyNeutralizerFalloff, Effect::MetaInfo::Category::target, true, false, {
				
			}},
			{EffectID::rigDrawbackReductionArmor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3083]},{modifiers[3084]},
			}},
			{EffectID::rigDrawbackReductionAstronautics, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3085]},{modifiers[3086]},
			}},
			{EffectID::rigDrawbackReductionDrones, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3087]},
			}},
			{EffectID::rigDrawbackReductionElectronic, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3088]},{modifiers[3089]},{modifiers[3090]},
			}},
			{EffectID::rigDrawbackReductionProjectile, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3091]},
			}},
			{EffectID::rigDrawbackReductionEnergyWeapon, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3092]},
			}},
			{EffectID::rigDrawbackReductionHybrid, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3093]},
			}},
			{EffectID::rigDrawbackReductionLauncher, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3094]},
			}},
			{EffectID::rigDrawbackReductionShield, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3095]},
			}},
			{EffectID::setBonusAsklepian, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3096]},
			}},
			{EffectID::armorRepairAmountBonusSubcap, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3097]},
			}},
			{EffectID::shipBonusRole1CapitalHybridDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3098]},
			}},
			{EffectID::shipBonusDreadnoughtM1WebStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3099]},
			}},
			{EffectID::shipBonusRole3CapitalHybridDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3100]},
			}},
			{EffectID::shipBonusTitanM1WebStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3101]},
			}},
			{EffectID::shipBonusSupercarrierM1BurstProjectorWebBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3102]},
			}},
			{EffectID::ECMBurstJammer, Effect::MetaInfo::Category::active, true, false, {
				
			}},
			{EffectID::ECMBurstJammerQA, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::pacifierDebuffQA, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::roleBonusIceOreMiningDurationCap, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3103]},{modifiers[3104]},{modifiers[3105]},{modifiers[3106]},
			}},
			{EffectID::logisticSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3107]},
			}},
			{EffectID::moduleBonusIndustrialInvulnerability, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::shipBonusDroneRepairMC1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3108]},{modifiers[3109]},{modifiers[3110]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairOptimalFalloff1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3111]},{modifiers[3112]},
			}},
			{EffectID::roleBonusRemoteArmorRepairOptimalFalloff, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3113]},{modifiers[3114]},
			}},
			{EffectID::shipBonusCloakCpuMC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3115]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairDuration3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3116]},
			}},
			{EffectID::shipBonusSETFalloffAF2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3117]},
			}},
			{EffectID::shipBonusCloakCpuMF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3118]},
			}},
			{EffectID::eliteBonusCoverOpsNOSNeutFalloff1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3119]},{modifiers[3120]},
			}},
			{EffectID::moduleBonusMicrowarpdrive, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[380]},{modifiers[570]},{modifiers[3121]},
			}},
			{EffectID::moduleBonusAfterburner, Effect::MetaInfo::Category::active, false, false, {
				{modifiers[570]},{modifiers[3121]},
			}},
			{EffectID::moduleBonusWarfareLinkArmor, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkShield, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkSkirmish, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkInfo, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkMining, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::chargeBonusWarfareCharge, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3122]},{modifiers[3123]},{modifiers[3124]},{modifiers[3125]},{modifiers[3126]},{modifiers[3127]},{modifiers[3128]},{modifiers[3129]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3130]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS4, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3131]},
			}},
			{EffectID::moduleTitanEffectGenerator, Effect::MetaInfo::Category::active, false, false, {
				
			}},
			{EffectID::engComplexServiceFuelBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3132]},{modifiers[3133]},
			}},
			{EffectID::miningDroneSpecBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3134]},{modifiers[3135]},
			}},
			{EffectID::iceHarvestingDroneOperationDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3136]},
			}},
			{EffectID::iceHarvestingDroneSpecBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3137]},{modifiers[3138]},
			}},
			{EffectID::spatialPhenomenaGenerationDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3139]},
			}},
			{EffectID::commandProcessorEffect, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[455]},{modifiers[649]},
			}},
			{EffectID::areaOfEffectSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3140]},
			}},
			{EffectID::commandBurstAoEBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3141]},
			}},
			{EffectID::armoredCommandDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3142]},
			}},
			{EffectID::shieldCommandDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3143]},
			}},
			{EffectID::informationCommandDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3144]},
			}},
			{EffectID::skirmishCommandDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3145]},
			}},
			{EffectID::miningForemanDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3146]},
			}},
			{EffectID::commandBurstStrengthSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3147]},
			}},
			{EffectID::armoredCommandStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3148]},{modifiers[3149]},{modifiers[3150]},{modifiers[3151]},
			}},
			{EffectID::shieldCommandStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3152]},{modifiers[3153]},{modifiers[3154]},{modifiers[3155]},
			}},
			{EffectID::informationCommandStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3156]},{modifiers[3157]},{modifiers[3158]},{modifiers[3159]},
			}},
			{EffectID::skirmishCommandStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3160]},{modifiers[3161]},{modifiers[3162]},{modifiers[3163]},
			}},
			{EffectID::miningForemanStrengthBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3164]},{modifiers[3165]},{modifiers[3166]},{modifiers[3167]},
			}},
			{EffectID::reloadTimeSkillBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3168]},
			}},
			{EffectID::commandBurstReloadTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3169]},
			}},
			{EffectID::commandBurstAoERoleBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3170]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS5, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3171]},
			}},
			{EffectID::shieldCommandBurstBonusICS3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3172]},{modifiers[3173]},{modifiers[3174]},{modifiers[3175]},{modifiers[3176]},
			}},
			{EffectID::shipBonusDroneHPDamageMiningICS4, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3177]},{modifiers[3178]},{modifiers[3179]},{modifiers[3180]},{modifiers[3181]},
			}},
			{EffectID::shipBonusDroneIceHarvestingICS5, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3182]},
			}},
			{EffectID::industrialBonusDroneDamage, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3183]},
			}},
			{EffectID::shipBonusDroneIceHarvestingRole, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3184]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier5, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3185]},
			}},
			{EffectID::shipBonusDroneHPDamageMiningORECapital4, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[933]},{modifiers[934]},{modifiers[935]},{modifiers[936]},{modifiers[3186]},
			}},
			{EffectID::miningForemanBurstBonusORECapital2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3187]},{modifiers[3188]},{modifiers[3189]},{modifiers[3190]},{modifiers[3191]},
			}},
			{EffectID::shieldCommandBurstBonusORECapital3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3192]},{modifiers[3193]},{modifiers[3194]},{modifiers[3195]},{modifiers[3196]},
			}},
			{EffectID::shipBonusDroneIceHarvestingORECapital5, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3197]},
			}},
			{EffectID::shipModeSHTDamagePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3198]},
			}},
			{EffectID::shipModeSPTDamagePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3199]},
			}},
			{EffectID::shipModeSETDamagePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3200]},
			}},
			{EffectID::shipModeSmallMissileDamagePostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3201]},{modifiers[3202]},{modifiers[3203]},{modifiers[3204]},{modifiers[3205]},{modifiers[3206]},{modifiers[3207]},{modifiers[3208]},
			}},
			{EffectID::modeDampTDResistsPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3209]},{modifiers[3210]},
			}},
			{EffectID::modeMWDandABBoostPostDiv, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3211]},{modifiers[3212]},
			}},
			{EffectID::rigEquipmentManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3213]},
			}},
			{EffectID::rigEquipmentManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3214]},
			}},
			{EffectID::invulnerabilityCoreDurationBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3215]},{modifiers[3216]},
			}},
			{EffectID::rigAmmoManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3217]},
			}},
			{EffectID::rigAmmoManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3218]},
			}},
			{EffectID::rigDroneManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3219]},
			}},
			{EffectID::rigDroneManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3220]},
			}},
			{EffectID::rigSmallshipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3221]},
			}},
			{EffectID::rigSmallshipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3222]},
			}},
			{EffectID::rigMediumshipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3223]},
			}},
			{EffectID::rigMediumshipsManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3224]},
			}},
			{EffectID::rigLargeshipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3225]},
			}},
			{EffectID::rigLargeshipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3226]},
			}},
			{EffectID::rigAdvSmshipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3227]},
			}},
			{EffectID::rigAdvSmshipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3228]},
			}},
			{EffectID::rigAdvMedShipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3229]},
			}},
			{EffectID::rigAdvMedShipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3230]},
			}},
			{EffectID::rigAdvLarShipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3231]},
			}},
			{EffectID::rigAdvLarShipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3232]},
			}},
			{EffectID::rigAdvComponentManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3233]},
			}},
			{EffectID::rigAdvComponentManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3234]},
			}},
			{EffectID::rigBasCapCompManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3235]},
			}},
			{EffectID::rigBasCapCompManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3236]},
			}},
			{EffectID::rigStructureManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3237]},
			}},
			{EffectID::rigStructureManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3238]},
			}},
			{EffectID::rigInventionCostBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3239]},
			}},
			{EffectID::rigInventionTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3240]},
			}},
			{EffectID::rigMEResearchCostBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3241]},
			}},
			{EffectID::rigMEResearchTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3242]},
			}},
			{EffectID::rigTEResearchCostBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3243]},
			}},
			{EffectID::rigTEResearchTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3244]},
			}},
			{EffectID::rigCopyCostBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3245]},
			}},
			{EffectID::rigCopyTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3246]},
			}},
			{EffectID::rigCapShipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3247]},
			}},
			{EffectID::rigCapShipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3248]},
			}},
			{EffectID::rigAllShipManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3249]},
			}},
			{EffectID::rigAllShipManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3250]},
			}},
			{EffectID::structureEngineeringRigSecurityModification, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3251]},{modifiers[3252]},{modifiers[3253]},{modifiers[3254]},
			}},
			{EffectID::skillMultiplierMissileVelocityBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3255]},
			}},
			{EffectID::skillMultiplierDefenderMissileVelocity, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3256]},
			}},
			{EffectID::shipBonusCommandDestroyerRole1DefenderBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3257]},
			}},
			{EffectID::shipModuleFocusedWarpScramblingScript, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[8]},{modifiers[2184]},{modifiers[2185]},{modifiers[3258]},{modifiers[3259]},
			}},
			{EffectID::shipModuleFocusedWarpDisruptionScript, Effect::MetaInfo::Category::target, true, false, {
				{modifiers[8]},{modifiers[2185]},{modifiers[3259]},
			}},
			{EffectID::chargeRateStructureModulesMultiply, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3260]},
			}},
			{EffectID::shipBonusRole3CapitalEnergyDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3261]},
			}},
			{EffectID::shipBonusTitanM1WebRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3262]},
			}},
			{EffectID::shipBonusTitanA1EnergyWarfareAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3263]},{modifiers[3264]},
			}},
			{EffectID::shipBonusDreadnoughtA1EnergyWarfareAmountBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3265]},{modifiers[3266]},
			}},
			{EffectID::shipBonusDreadnoughtM1WebRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3267]},
			}},
			{EffectID::shipBonusForceAuxiliaryA1NosferatuRangeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3268]},{modifiers[3269]},
			}},
			{EffectID::shipBonusForceAuxiliaryA1NosferatuDrainAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3270]},
			}},
			{EffectID::shipBonusRole4NosferatuCPUBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3271]},
			}},
			{EffectID::shipBonusRole5RemoteArmorRepairPowergridBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3272]},
			}},
			{EffectID::shipBonusRole5CapitalRemoteArmorRepairPowergridBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3273]},
			}},
			{EffectID::shipBonusForceAuxiliaryM1RemoteArmorRepairDuration, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2696]},
			}},
			{EffectID::eliteBonusCoverOpsWarpVelocity1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3274]},
			}},
			{EffectID::shipBonusSmallMissileFlightTimeCF1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3275]},{modifiers[3276]},
			}},
			{EffectID::shipBonusSPTRoFMF, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3277]},
			}},
			{EffectID::roleBonusConcordSecGain, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3278]},
			}},
			{EffectID::concordIntermediateSecStatus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3279]},
			}},
			{EffectID::concordAssignTankBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3280]},
			}},
			{EffectID::concordSecStatusTankBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3281]},{modifiers[3282]},
			}},
			{EffectID::eliteReconStasisWebBonus1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3283]},
			}},
			{EffectID::eliteBonusReconWarpVelocity3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3284]},
			}},
			{EffectID::shipBonusMedMissileFlightTimeCC2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3285]},{modifiers[3286]},
			}},
			{EffectID::blackOpsSkillMultiplier3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3287]},
			}},
			{EffectID::blackOpsSkillMultiplier4, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3288]},
			}},
			{EffectID::eliteBonusBlackOpsWarpVelocity1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3289]},
			}},
			{EffectID::eliteBonusBlackOpsScramblerRange4, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3290]},
			}},
			{EffectID::eliteBonusBlackOpsWebRange3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3291]},
			}},
			{EffectID::shipBonusLauncherRoF2CB, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[555]},{modifiers[556]},{modifiers[2022]},
			}},
			{EffectID::shipBonusLargeMissileFlightTimeCB1, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3292]},{modifiers[3293]},
			}},
			{EffectID::shipBonusForceAuxiliaryM2LocalRepairAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3294]},{modifiers[3295]},
			}},
			{EffectID::rigThukkerBasCapCompManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3296]},
			}},
			{EffectID::rigAdvCapComponentManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3297]},
			}},
			{EffectID::rigAdvCapComponentManufactureTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3298]},
			}},
			{EffectID::rigThukkerAdvCapCompManufactureMaterialBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3299]},
			}},
			{EffectID::reactionTimeBonusPostPercentManufactureTimeMultiplierChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3300]},
			}},
			{EffectID::reactionSkillBoostManufacturingTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3301]},
			}},
			{EffectID::massReactionSkillLevelModAddReactionSlotLimitChar, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3302]},
			}},
			{EffectID::subsystemEnergyNeutFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3303]},{modifiers[3304]},{modifiers[3305]},{modifiers[3306]},
			}},
			{EffectID::subsystemMETFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3307]},{modifiers[3308]},
			}},
			{EffectID::subsystemMHTFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3309]},{modifiers[3310]},
			}},
			{EffectID::subsystemMPTFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3311]},{modifiers[3312]},
			}},
			{EffectID::subsystemMRARFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3313]},
			}},
			{EffectID::subsystemMRSBFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3314]},
			}},
			{EffectID::subsystemMMissileFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3315]},{modifiers[3316]},{modifiers[3317]},{modifiers[3318]},{modifiers[3319]},{modifiers[3320]},
			}},
			{EffectID::shipModuleNonRepeatingShieldHardener, Effect::MetaInfo::Category::active, true, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::shipModuleNonRepeatingArmorHardener, Effect::MetaInfo::Category::active, true, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::strategicCruiserMinmatarSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3321]},
			}},
			{EffectID::strategicCruiserAmarrSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3322]},
			}},
			{EffectID::strategicCruiserCaldariSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3323]},
			}},
			{EffectID::strategicCruiserGallenteSkillLevel2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3324]},
			}},
			{EffectID::shipBonusStrategicCruiserCaldariNaniteRepairTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3325]},
			}},
			{EffectID::shipBonusStrategicCruiserAmarrNaniteRepairTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3326]},
			}},
			{EffectID::shipBonusStrategicCruiserGallenteNaniteRepairTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3327]},
			}},
			{EffectID::shipBonusStrategicCruiserMinmatarNaniteRepairTime2, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3328]},
			}},
			{EffectID::subsystemSkillLevelAmarrDefensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3329]},
			}},
			{EffectID::subsystemSkillLevelAmarrEngineering3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3330]},
			}},
			{EffectID::subsystemSkillLevelCaldariEngineering3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3331]},
			}},
			{EffectID::subsystemSkillLevelCaldariDefensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3332]},
			}},
			{EffectID::subsystemSkillLevelGallenteEngineering3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3333]},
			}},
			{EffectID::subsystemSkillLevelGallenteDefensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3334]},
			}},
			{EffectID::subsystemSkillLevelMinmatarEngineering3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3335]},
			}},
			{EffectID::subsystemSkillLevelMinmatarDefensive3, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3336]},
			}},
			{EffectID::structureHPBonusAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3337]},
			}},
			{EffectID::subSystemBonusAmarrDefensive2ScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3338]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive1HMLHAMVelo, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3339]},{modifiers[3340]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive3MissileExpVelo, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3341]},
			}},
			{EffectID::subsystemBonusGallenteOffensive2DroneVeloTracking, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3342]},{modifiers[3343]},
			}},
			{EffectID::subsystemBonusAmarrPropulsionWarpCapacitor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3344]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsionWarpCapacitor, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3345]},
			}},
			{EffectID::subsystemBonusCaldariPropulsion2PropModHeatBenefit, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3346]},{modifiers[3347]},
			}},
			{EffectID::subsystemBonusGallentePropulsion2PropModHeatBenefit, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3348]},{modifiers[3349]},
			}},
			{EffectID::subsystemBonusAmarrCore2EnergyResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3350]},
			}},
			{EffectID::subsystemBonusMinmatarCore2EnergyResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3351]},
			}},
			{EffectID::subsystemBonusGallenteCore2EnergyResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3352]},
			}},
			{EffectID::subsystemBonusCaldariCore2EnergyResistance, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3353]},
			}},
			{EffectID::shipMaxLockedTargetsBonusAddPassive, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[33]},
			}},
			{EffectID::subsystemBonusAmarrCore3EnergyWarHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3354]},{modifiers[3355]},
			}},
			{EffectID::subsystemBonusMinmatarCore3StasisWebHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3356]},
			}},
			{EffectID::subsystemBonusGallenteCore3WarpScramHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3357]},
			}},
			{EffectID::subsystemBonusCaldariCore3ECMHeatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3358]},
			}},
			{EffectID::subsystemBonusAmarrDefensive2HardenerHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3359]},{modifiers[3360]},
			}},
			{EffectID::subsystemBonusGallenteDefensive2HardenerHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3361]},{modifiers[3362]},
			}},
			{EffectID::subsystemBonusCaldariDefensive2HardenerHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3363]},
			}},
			{EffectID::subsystemBonusMinmatarDefensive2HardenerHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3364]},{modifiers[3365]},{modifiers[3366]},
			}},
			{EffectID::subsystemBonusAmarrDefensive3ArmorRepHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3367]},{modifiers[3368]},
			}},
			{EffectID::subsystemBonusGallenteDefensive3ArmorRepHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3369]},{modifiers[3370]},
			}},
			{EffectID::subsystemBonusCaldariDefensive3ShieldBoostHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3371]},{modifiers[3372]},
			}},
			{EffectID::subsystemBonusMinmatarDefensive3LocalRepHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3373]},{modifiers[3374]},{modifiers[3375]},{modifiers[3376]},
			}},
			{EffectID::subSystemBonusCaldariDefensive2ScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3377]},
			}},
			{EffectID::subSystemBonusGallenteDefensive2ScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3378]},
			}},
			{EffectID::subSystemBonusMinmatarDefensive2ScanProbeStrength, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3379]},
			}},
			{EffectID::mediumRemoteRepFittingAdjustment, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3380]},{modifiers[3381]},
			}},
			{EffectID::subsystemBonusCommandBurstFittingReduction, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3382]},{modifiers[3383]},
			}},
			{EffectID::subsystemRemoteShieldBoostFalloffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3384]},{modifiers[3385]},
			}},
			{EffectID::subsystemRemoteArmorRepairerOptimalBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3386]},{modifiers[3387]},
			}},
			{EffectID::subsystemRemoteArmorRepairerFalloffBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3388]},{modifiers[3389]},
			}},
			{EffectID::subsystemBonusAmarrOffensive3RemoteArmorRepairHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3390]},
			}},
			{EffectID::subsystemBonusGallenteOffensive3RemoteArmorRepairHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3391]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3RemoteShieldBoosterHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3392]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive3RemoteRepHeat, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3393]},{modifiers[3394]},
			}},
			{EffectID::subsystemBonusAmarrPropulsion2WarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3395]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsion2WarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3396]},
			}},
			{EffectID::subsystemBonusGallentePropulsionWarpSpeed, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3397]},
			}},
			{EffectID::surveyProbeExplosionDelayOnline, Effect::MetaInfo::Category::passive, false, false, {
				{modifiers[3398]},
			}},
			{EffectID::rigReactionHybTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3399]},
			}},
			{EffectID::rigReactionHybMatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3400]},
			}},
			{EffectID::rigReactionCompTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3401]},
			}},
			{EffectID::rigReactionCompMatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3402]},
			}},
			{EffectID::rigReactionBioTimeBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3403]},
			}},
			{EffectID::rigReactionBioMatBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3404]},
			}},
			{EffectID::structureReactionRigSecurityModification, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3405]},{modifiers[3406]},
			}},
			{EffectID::rigMoonSpewVolBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3407]},
			}},
			{EffectID::rigMoonSpewRadBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3408]},
			}},
			{EffectID::rigMoonFractureDelay, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3409]},
			}},
			{EffectID::rigMoonAsteroidDecayBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3410]},
			}},
			{EffectID::shipBonusTitanG1KinThermDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3411]},{modifiers[3412]},{modifiers[3413]},{modifiers[3414]},{modifiers[3415]},{modifiers[3416]},
			}},
			{EffectID::shipBonusTitanG2AllDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3417]},{modifiers[3418]},{modifiers[3419]},{modifiers[3420]},{modifiers[3421]},{modifiers[3422]},{modifiers[3423]},{modifiers[3424]},{modifiers[3425]},
			}},
			{EffectID::shipBonusTitanC1ShieldResists, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3426]},{modifiers[3427]},{modifiers[3428]},{modifiers[3429]},
			}},
			{EffectID::shipBonusRole4FighterDamageAndHitpoints, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3430]},{modifiers[3431]},{modifiers[3432]},{modifiers[3433]},
			}},
			{EffectID::shipBonusDreadnoughtG1KinThermDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3434]},{modifiers[3435]},{modifiers[3436]},{modifiers[3437]},{modifiers[3438]},{modifiers[3439]},
			}},
			{EffectID::shipBonusForceAuxiliaryG1RemoteShieldBoostAmount, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3440]},
			}},
			{EffectID::shipBonusRole2LogisticDroneRepAmountAndHitpointBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[2766]},{modifiers[2767]},{modifiers[2768]},{modifiers[3441]},{modifiers[3442]},{modifiers[3443]},
			}},
			{EffectID::refineryServiceFuelBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3444]},{modifiers[3445]},
			}},
			{EffectID::refineryRefiningYieldBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3446]},{modifiers[3447]},{modifiers[3448]},
			}},
			{EffectID::asteroidDecayTimeDisplayUpdate, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3449]},
			}},
			{EffectID::characterDamageMissiles, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3450]},{modifiers[3451]},{modifiers[3452]},{modifiers[3453]},
			}},
			{EffectID::naniteRepairPasteArmorDamageBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3454]},
			}},
			{EffectID::tacticalMode, Effect::MetaInfo::Category::generic, false, false, {
				
			}},
			{EffectID::fueledArmorRepairBonus, Effect::MetaInfo::Category::generic, false, false, {
				{modifiers[3455]},{modifiers[3456]},
			}},
			{EffectID::gangBoost, Effect::MetaInfo::Category::active, false, false, {
				
			}},
		};
	}
}
