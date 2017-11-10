#pragma once
#include "MetaInfo.hpp"
#include "Modifiers.hpp"

namespace dgmpp2 {
	namespace SDE {
		constexpr const MetaInfo::Effect effects[] {
			{EffectID::shieldBoosting, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[0]},
			}},
			{EffectID::missileLaunching, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::targetAttack, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::loPower, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::hiPower, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::medPower, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::online, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1]},{modifiers[2]},
			}},
			{EffectID::mining, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::shieldTransfer, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[3]},
			}},
			{EffectID::shieldCapacityBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[4]},
			}},
			{EffectID::capacitorCapacityBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[5]},
			}},
			{EffectID::structureRepair, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[6]},
			}},
			{EffectID::armorRepair, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[7]},
			}},
			{EffectID::projectileFired, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::empWave, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::warpScramble, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[8]},
			}},
			{EffectID::launcherFitted, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[9]},
			}},
			{EffectID::turretFitted, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[10]},
			}},
			{EffectID::shipScan, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::cargoScan, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::powerBooster, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::modifyShieldRechargeRate, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[11]},
			}},
			{EffectID::modifyPowerRechargeRate, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[12]},
			}},
			{EffectID::targetPassively, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::targetHostiles, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::powerOutputMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[13]},
			}},
			{EffectID::shieldCapacityMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[14]},
			}},
			{EffectID::capacitorCapacityMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[15]},
			}},
			{EffectID::cargoCapacityMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[16]},
			}},
			{EffectID::structureHPMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[17]},
			}},
			{EffectID::agilityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[18]},
			}},
			{EffectID::armorHPMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[19]},
			}},
			{EffectID::miningLaser, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::surveyScan, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::corporationMemberLimitBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[20]},
			}},
			{EffectID::projectileWeaponSpeedMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[21]},
			}},
			{EffectID::energyWeaponDamageMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[22]},
			}},
			{EffectID::projectileWeaponDamageMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[23]},
			}},
			{EffectID::hybridWeaponDamageMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[24]},
			}},
			{EffectID::energyWeaponSpeedMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[25]},
			}},
			{EffectID::hybridWeaponSpeedMultiply, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[26]},
			}},
			{EffectID::useMissiles, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::mineLaying, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::defenderMissileLaunching, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::fofMissileLaunching, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::shieldResonanceMultiplyOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[27]},{modifiers[28]},{modifiers[29]},{modifiers[30]},
			}},
			{EffectID::electronicAttributeModifyOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[31]},{modifiers[32]},{modifiers[33]},
			}},
			{EffectID::torpedoLaunching, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::skillEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[34]},{modifiers[35]},
			}},
			{EffectID::damageMultiplierSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[36]},
			}},
			{EffectID::skillBoostDamageMultiplierBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[36]},
			}},
			{EffectID::largeHybridTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringLargeHybridTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[37]},
			}},
			{EffectID::mediumEnergyTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringMediumEnergyTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[38]},
			}},
			{EffectID::mediumHybridTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringMediumHybridTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[39]},
			}},
			{EffectID::mediumProjectileTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringMediumProjectileTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[40]},
			}},
			{EffectID::largeEnergyTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringLargeEnergyTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[41]},
			}},
			{EffectID::rapidFiringSkillBoostRofBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[42]},
			}},
			{EffectID::sharpshooterSkillBoostRangeSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[43]},
			}},
			{EffectID::smallEnergyTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringSmallEnergyTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[44]},
			}},
			{EffectID::smallHybridTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringSmallHybridTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[45]},
			}},
			{EffectID::smallProjectileTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringSmallProjectileTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[46]},
			}},
			{EffectID::caldariCruiserSkillBoostCcTRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[47]},
			}},
			{EffectID::caldariFrigateSkillBoostCfTRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[48]},
			}},
			{EffectID::signatureAnalysisSkillBoostScanspeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[49]},
			}},
			{EffectID::signatureAnalysisScanspeedBonusPostPercentScanSpeedLocationShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[50]},
			}},
			{EffectID::longRangeTargetingSkillBoostMaxTargetRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[51]},
			}},
			{EffectID::propulsionJammingSkillBoostDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[52]},
			}},
			{EffectID::sensorUpgradesSkillBoostCpuNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[53]},
			}},
			{EffectID::sensorUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringSensorUpgrades, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[54]},
			}},
			{EffectID::targetingSkillBoostMaxTargetBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[55]},
			}},
			{EffectID::targetingMaxTargetBonusModAddMaxLockedTargetsLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[56]},
			}},
			{EffectID::electronicWarfareSkillBoostDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[57]},
			}},
			{EffectID::engineeringSkillBoostPowerOutputBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[58]},
			}},
			{EffectID::energyManagementSkillBoostCapRechargeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[59]},
			}},
			{EffectID::navigationSkillBoostVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[60]},
			}},
			{EffectID::navigationVelocityBonusPostPercentMaxVelocityLocationShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[61]},
			}},
			{EffectID::accerationControlSkillBoostCapNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[62]},
			}},
			{EffectID::accerationControlCapNeedBonusPostPercentCapacitorNeedLocationShipGroupAfterburner, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[63]},
			}},
			{EffectID::accerationControlSkillBoostSpeedFBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[64]},
			}},
			{EffectID::afterburnerDurationBonusPostPercentDurationLocationShipModulesRequiringAfterburner, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[65]},
			}},
			{EffectID::evasiveManuveringSkillBoostAgilityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[66]},
			}},
			{EffectID::warpdriveoperationSkillBoostWarpCapacitorNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[67]},
			}},
			{EffectID::warpdriveoperationWarpCapacitorNeedBonusPostPercentWarpCapacitorNeedLocationShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[68]},
			}},
			{EffectID::corporationManagementSkillBoostCorporationMemberBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[69]},
			}},
			{EffectID::accerationControlSpeedFBonusPostPercentSpeedFactorLocationShipGroupAfterburner, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[70]},
			}},
			{EffectID::highSpeedManuveringSkillBoostCapacitorNeedMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[71]},
			}},
			{EffectID::highSpeedManuveringCapacitorNeedMultiplierPostPercentCapacitorNeedLocationShipModulesRequiringHighSpeedManuvering, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[72]},
			}},
			{EffectID::sensorUpgradesSkillBoostPowerNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[73]},
			}},
			{EffectID::hullUpgradesSkillBoostHullHpBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[74]},
			}},
			{EffectID::shadowBarrageDmgMultiplierWithDamageMultiplierPostPercentBarrageDmgMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[75]},{modifiers[76]},
			}},
			{EffectID::shadowBarrageFalloffWithFalloffPostPercentBarrageFalloffMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[77]},{modifiers[78]},
			}},
			{EffectID::barrage, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::amarrCruiserSkillBoostPowerOutputBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[79]},
			}},
			{EffectID::hullUpgradesSkillBoostArmorHpBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[80]},
			}},
			{EffectID::hullUpgradesArmorHpBonusPostPercentHpLocationShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[81]},
			}},
			{EffectID::repairSystemsDurationBonusPostPercentDurationLocationShipModulesRequiringRepairSystems, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[82]},
			}},
			{EffectID::shieldUpgradesPowerNeedBonusPostPercentPowerLocationShipModulesRequiringShieldUpgrades, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[83]},
			}},
			{EffectID::tacticalshieldManipulationSkillBoostUniformityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[84]},
			}},
			{EffectID::shieldEmmisionSystemsCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringShieldEmmisionSystems, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[85]},
			}},
			{EffectID::shieldManagementSkillBoostShieldCapacityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[86]},
			}},
			{EffectID::shieldoperationSkillBoostRechargeratebonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[87]},
			}},
			{EffectID::controlledBurstsCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[88]},
			}},
			{EffectID::motionPredictionTrackingSpeedMultiplierPostPercentTrackingSpeedLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[89]},
			}},
			{EffectID::sharpshooterRangeSkillBonusPostPercentMaxRangeLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[90]},
			}},
			{EffectID::skillBoostFalloffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[91]},
			}},
			{EffectID::surgicalStrikeFalloffBonusPostPercentFalloffLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[92]},
			}},
			{EffectID::empathyCharismaBonusModAddCharismaLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[93]},
			}},
			{EffectID::instantRecallMemoryBonusModAddMemoryLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[94]},
			}},
			{EffectID::analyticalMindIntelligenceBonusModAddIntelligenceLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[95]},
			}},
			{EffectID::ironWillWillpowerBonusModAddWillpowerLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[96]},
			}},
			{EffectID::spatialAwarenessPerceptionBonusModAddPerceptionLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[97]},
			}},
			{EffectID::dronesSkillBoostMaxActiveDroneBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[98]},
			}},
			{EffectID::dronesMaxActiveDroneBonusModAddMaxActiveLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[99]},
			}},
			{EffectID::amarrTechSkillBoostAmarrTechMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[100]},
			}},
			{EffectID::amarrTechAmarrTechMutatorPostPercentAmarrTechTimePercentLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[101]},
			}},
			{EffectID::caldariTechSkillBoostCaldariTechMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[102]},
			}},
			{EffectID::caldariTechCaldariTechMutatorPostPercentCaldariTechTimePercentLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[103]},
			}},
			{EffectID::gallenteTechSkillBoostGallenteTechMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[104]},
			}},
			{EffectID::gallenteTechGallenteTechMutatorPostPercentGallenteTechTimePercentLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[105]},
			}},
			{EffectID::refineryEfficiencySkillBoostRefiningYieldMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[106]},
			}},
			{EffectID::cSOTrainingSkillBoostResearchGangSizeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[107]},
			}},
			{EffectID::cSOTrainingResearchGangSizeBonusModAddMaxResearchGangSizeShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[108]},
			}},
			{EffectID::battleshipConstructionSkillBoostBattleshipConstructionTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[109]},
			}},
			{EffectID::battleshipConstructionBattleshipConstructionTimeBonusPostPercentBattleshipConstructionTimeChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[110]},
			}},
			{EffectID::cruiserConstructionSkillBoostCruiserConstructionTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[111]},
			}},
			{EffectID::cruiserConstructionCruiserConstructionTimeBonusPostPercentCruiserConstructionTimeChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[112]},
			}},
			{EffectID::frigateConstructionSkillBoostFrigateConstructionTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[113]},
			}},
			{EffectID::frigateConstructionFrigateConstructionTimeBonusPostPercentFrigateConstructionTimeChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[114]},
			}},
			{EffectID::industrialConstructionSkillBoostIndustrialConstructionTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[115]},
			}},
			{EffectID::industrialConstructionIndustrialConstructionTimeBonusPostPercentIndustrialConstructionTimeChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[116]},
			}},
			{EffectID::connectionsSkillBoostConnectionBonusMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[117]},
			}},
			{EffectID::criminalConnectionsSkillBoostCriminalConnectionsMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[118]},
			}},
			{EffectID::diplomacySkillBoostDiplomacyMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[119]},
			}},
			{EffectID::diplomacyDiplomacyMutatorModAddDiplomacyBonusChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[120]},
			}},
			{EffectID::fasttalkSkillBoostFastTalkMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[121]},
			}},
			{EffectID::fasttalkFastTalkMutatorPostPercentFastTalkPercentageChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[122]},
			}},
			{EffectID::gallenteFrigateSkillBoostCpuOutputBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[123]},
			}},
			{EffectID::astrogeologySkillBoostMiningAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[124]},
			}},
			{EffectID::astrogeologyMiningAmountBonusPostPercentMiningAmountLocationShipModulesRequiringMining, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[125]},
			}},
			{EffectID::mechanicHullHpBonusPostPercentHpShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[126]},
			}},
			{EffectID::navigationVelocityBonusPostPercentMaxVelocityShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[61]},
			}},
			{EffectID::evasiveManeuveringAgilityBonusPostPercentAgilityShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[127]},
			}},
			{EffectID::energyGridUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringEnergyGridUpgrades, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[128]},
			}},
			{EffectID::electronicsCpuOutputBonusPostPercentCpuOutputLocationShipGroupComputer, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[129]},
			}},
			{EffectID::connectionsConnectionBonusMutatorModAddConnectionsBonusChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[130]},
			}},
			{EffectID::criminalConnectionsCriminalConnectionsMutatorModAddCriminalConnectionsBonusChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[131]},
			}},
			{EffectID::negotiationSkillBoostNegotiationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[132]},
			}},
			{EffectID::negotiationNegotiationBonusPostPercentNegotiationPercentageChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[133]},
			}},
			{EffectID::socialSkillBoostSocialMutator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[134]},
			}},
			{EffectID::socialSocialMutatorPostPercentSocialBonusChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[135]},
			}},
			{EffectID::largeProjectileTurretDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringLargeProjectileTurret, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[136]},
			}},
			{EffectID::industrySkillBoostManufacturingTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[137]},
			}},
			{EffectID::gunnerySkillBoostTurretSpeeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[138]},
			}},
			{EffectID::gunneryTurretSpeeBonusPostPercentSpeedLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[139]},
			}},
			{EffectID::tradeSkillBoostTradePremiumBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[140]},
			}},
			{EffectID::tradeTradePremiumBonusPostPercentTradePremiumChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[141]},
			}},
			{EffectID::smugglingSkillBoostSmugglingChanceBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[142]},
			}},
			{EffectID::industryManufacturingTimeBonusPostPercentManufactureTimeMultiplierChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[143]},
			}},
			{EffectID::scienceSkillBoostCopySpeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[144]},
			}},
			{EffectID::scienceCopySpeedBonusPostPercentCopySpeedPercentChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[145]},
			}},
			{EffectID::researchSkillBoostBlueprintmanufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[146]},
			}},
			{EffectID::researchBlueprintmanufactureTimeBonusPostPercentProductionTimeResearchSpeedChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[147]},
			}},
			{EffectID::refineryEfficiencyRefiningYieldMutatorPostPercentRefiningYieldPercentageChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[148]},
			}},
			{EffectID::missileLauncherOperationSpeedBonusPostPercentSpeedLocationShipModulesRequiringMissileLauncherOperation, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[149]},
			}},
			{EffectID::energyManagementCapacitorBonusPostPercentCapacityLocationShipGroupCapacitor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[150]},
			}},
			{EffectID::shieldManagementShieldCapacityBonusPostPercentCapacityLocationShipGroupShield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[151]},
			}},
			{EffectID::scoutDroneOperationSkillBoostDroneRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[152]},
			}},
			{EffectID::minmatarFrigateSkillLevelPreMulShipBonusMFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[153]},
			}},
			{EffectID::shipTargetRangeBonusMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[154]},
			}},
			{EffectID::caldariFrigateSkillLevelPreMulShipBonusCFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[155]},
			}},
			{EffectID::shipShieldCapBonusCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[156]},
			}},
			{EffectID::gallenteFrigateSkillLevelPreMulShipBonusGFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[157]},
			}},
			{EffectID::amarrFrigateSkillLevelPreMulShipBonusAFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[158]},
			}},
			{EffectID::metallurgySkillBoostMineralNeedResearchBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[159]},
			}},
			{EffectID::energysystemsoperationCapRechargeBonusPostPercentRechargeRateLocationShipGroupCapacitor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[160]},
			}},
			{EffectID::shieldOperationRechargeratebonusPostPercentRechargeRateLocationShipGroupShield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[161]},
			}},
			{EffectID::engineeringPowerEngineeringOutputBonusPostPercentPowerOutputLocationShipGroupPowerCore, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[162]},
			}},
			{EffectID::warpDriveOperationWarpCapacitorNeedBonusPostPercentWarpCapacitorNeedLocationShipGroupPropulsion, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[68]},
			}},
			{EffectID::inventionSkillBoostInventionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[163]},
			}},
			{EffectID::amarrCruiserSkillLevelPreMulShipBonusACShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[164]},
			}},
			{EffectID::scoutDroneOperationDroneRangeBonusModAddDroneControlDistanceChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[165]},
			}},
			{EffectID::fuelConservationCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringAfterburner, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[166]},
			}},
			{EffectID::longRangeTargetingMaxTargetRangeBonusPostPercentMaxTargetRangeLocationShipGroupElectronic, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[167]},
			}},
			{EffectID::shipPDmgBonusMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[168]},
			}},
			{EffectID::amarrFrigateSkillLevelPreMulShipBonus2AFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[169]},
			}},
			{EffectID::shipEnergyTCapNeedBonusAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[170]},
			}},
			{EffectID::shipSHTDmgBonusGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[171]},
			}},
			{EffectID::shipSETDmgBonusAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[172]},
			}},
			{EffectID::shipTCapNeedBonusAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[173]},
			}},
			{EffectID::gallenteCruiserSkillLevelPreMulShipBonusGCShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[174]},
			}},
			{EffectID::caldariCruiserSkillLevelPreMulShipBonusCCShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[175]},
			}},
			{EffectID::shipHRangeBonusCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[176]},
			}},
			{EffectID::minmatarCruiserSkillLevelPreMulShipBonusMCShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[177]},
			}},
			{EffectID::minmatarIndustrialSkillLevelPreMulShipBonusMIShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[178]},
			}},
			{EffectID::shipVelocityBonusMI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[179]},
			}},
			{EffectID::shipCargoBonusAI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[180]},
			}},
			{EffectID::caldariIndustrialSkillLevelPreMulShipBonusCIShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[181]},
			}},
			{EffectID::gallenteIndustrialSkillLevelPreMulShipBonusGIShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[182]},
			}},
			{EffectID::cpuMultiplierPostMulCpuOutputShip, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[183]},
			}},
			{EffectID::amarrBattleshipSkillLevelPostMulShipBonusABShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[184]},
			}},
			{EffectID::caldariBattleshipSkillLevelPreMulShipBonusCBShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[185]},
			}},
			{EffectID::shipCapNeedBonusAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[186]},
			}},
			{EffectID::minmatarBattleshipSkillLevelPreMulShipBonusMBShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[187]},
			}},
			{EffectID::shipPTDmgBonusMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[188]},
			}},
			{EffectID::shipHTDmgBonusGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[189]},
			}},
			{EffectID::shipHTTrackingBonusGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[190]},
			}},
			{EffectID::caldariBattleshipSkillLevelPreMulShipBonus2CBShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[191]},
			}},
			{EffectID::metallurgyMineralNeedResearchBonusPostPercentMineralNeedResearchSpeedChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[192]},
			}},
			{EffectID::shipHTDmgBonusfixedGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[193]},
			}},
			{EffectID::laboratoryOperationSkillLevelModAddMaxLaborotorySlotsChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[194]},
			}},
			{EffectID::massProductionSkillLevelModAddManufactureSlotLimitChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[195]},
			}},
			{EffectID::missileLaunchingForEntity, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::reverseEngineeringInventionBonusModAddReverseEngineeringChanceLocationChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[196]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[197]},
			}},
			{EffectID::rapidFiringRofBonusPostPercentSpeedLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[198]},
			}},
			{EffectID::amarrIndustrialSkillLevelPreMulShipBonusAI2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[199]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipModulesRequiringGunnery, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[200]},
			}},
			{EffectID::decreaseTargetSpeed, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[201]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipGroupEnergyWeapon, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[202]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipGroupProjectileWeapon, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[203]},
			}},
			{EffectID::surgicalStrikeDamageMultiplierBonusPostPercentDamageMultiplierLocationShipGroupHybridWeapon, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[204]},
			}},
			{EffectID::energyPulseWeaponsDurationBonusPostPercentDurationLocationShipModulesRequiringEnergyPulseWeapons, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[205]},
			}},
			{EffectID::targetArmorRepair, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[206]},
			}},
			{EffectID::ammoInfluenceRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[207]},
			}},
			{EffectID::ammoSpeedMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[208]},
			}},
			{EffectID::ammoFallofMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[209]},
			}},
			{EffectID::ammoTrackingMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[210]},
			}},
			{EffectID::shipPTurretSpeedBonusMC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[211]},
			}},
			{EffectID::shipPTspeedBonusMB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[212]},
			}},
			{EffectID::minmatarBattleshipSkillLevelPreMulShipBonusMB2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[213]},
			}},
			{EffectID::cloaking, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[214]},
			}},
			{EffectID::gallenteBattleshipSkillLevelPreMulShipBonusGBShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[215]},
			}},
			{EffectID::miningDroneOperationMiningAmountBonusPostPercentMiningDroneAmountPercentChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[216]},
			}},
			{EffectID::powerIncrease, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[217]},
			}},
			{EffectID::shipSpecialityMining, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[218]},
			}},
			{EffectID::anchorDrop, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::anchorLift, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::cloakingSkillBoostCloakVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[219]},
			}},
			{EffectID::agilityMultiplierEffect, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[220]},
			}},
			{EffectID::missileEMDmgBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[221]},
			}},
			{EffectID::missileExplosiveDmgBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[222]},
			}},
			{EffectID::missileThermalDmgBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[223]},
			}},
			{EffectID::heavyMissilesSkillBoostMaxflightTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[224]},
			}},
			{EffectID::missileKineticDmgBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[225]},
			}},
			{EffectID::antiWarpScramblingPassive, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[226]},
			}},
			{EffectID::weaponUpgradesSkillBoostCpu, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[227]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringEnergyPulseWeapons, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[228]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringMissileLauncherOperation, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[229]},
			}},
			{EffectID::gallenteBattleshipSkillLevelPreMulShipBonusGB2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[230]},
			}},
			{EffectID::signatureAnalysisSkillLevelPreMulScanResolutionBonusSelf, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[231]},
			}},
			{EffectID::signatureAnalysisScanResolutionBonusPostPercentScanResolutionShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[232]},
			}},
			{EffectID::interceptorsSkillLevelPreMulEliteBonusInterceptorShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[233]},
			}},
			{EffectID::covertOpsSkillLevelPreMulEliteBonusCoverOpsShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[234]},
			}},
			{EffectID::covertOpsWarpResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[235]},
			}},
			{EffectID::bomberRocketRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[236]},
			}},
			{EffectID::bomberLightsRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[237]},
			}},
			{EffectID::interceptorSignatoreRadiusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[238]},
			}},
			{EffectID::speedBoostFactorCalculator, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[239]},{modifiers[240]},
			}},
			{EffectID::speedBoostFactorCalculator2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[241]},
			}},
			{EffectID::stealthActive, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[242]},
			}},
			{EffectID::shipBonusCargo2GI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[243]},
			}},
			{EffectID::shipBonusCargoCI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[244]},
			}},
			{EffectID::shipBonusCargoMI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[245]},
			}},
			{EffectID::shipBonusVelocityGI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[246]},
			}},
			{EffectID::shipBonusVelocityCI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[247]},
			}},
			{EffectID::shipVelocityBonusAI, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[248]},
			}},
			{EffectID::amarrBattleshipSkillLevelPreMulShipBonusAB2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[249]},
			}},
			{EffectID::shipBonusCapCapAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[250]},
			}},
			{EffectID::surveyScanspeedBonusPostPercentDurationLocationShipModulesRequiringElectronics, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[251]},
			}},
			{EffectID::gallenteFrigateSkillLevelPreMulShipBonusGF2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[252]},
			}},
			{EffectID::shipHybridDamageBonusCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[253]},
			}},
			{EffectID::shipETDamageAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[172]},
			}},
			{EffectID::shipBonusSmallMissileRoFCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[254]},{modifiers[255]},
			}},
			{EffectID::caldariFrigateSkillLevelPreMulShipBonusCF2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[256]},
			}},
			{EffectID::minmatarFrigateSkillLevelPreMulShipBonusMF2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[257]},
			}},
			{EffectID::missileDMGBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[258]},
			}},
			{EffectID::hypereuclideanNavigationCloakVelocityBonusModAddSpeedFactorLocationShipModulesRequiringCloaking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[259]},
			}},
			{EffectID::missileBombardmentMaxFlightTimeBonusPostPercentExplosionDelayOwnerCharModulesRequiringMissileLauncherOperation, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[260]},
			}},
			{EffectID::escortHullUpgradeCpuBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[261]},
			}},
			{EffectID::escortShieldUpgradeCpuBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[262]},
			}},
			{EffectID::caldariBattleshipSkillLevelPreMulShipBonusCB3Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[263]},
			}},
			{EffectID::ammoInfluenceCapNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[264]},
			}},
			{EffectID::ammoInfluenceCapRecharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[12]},
			}},
			{EffectID::freightSkillBoostCargoCapacityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[265]},
			}},
			{EffectID::skillFreightBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[266]},
			}},
			{EffectID::ammoInfluenceShipVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[214]},
			}},
			{EffectID::cloakingTargetingDelayBonusPostPercentCloakingTargetingDelayBonusForShipModulesRequiringCloaking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[267]},
			}},
			{EffectID::cloakingSkillBoostCloakingTargetingDelayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[268]},
			}},
			{EffectID::cloakingScanResolutionMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[269]},
			}},
			{EffectID::warpSkillSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[270]},
			}},
			{EffectID::bountyHuntingSkillBoostBountySkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[271]},
			}},
			{EffectID::bountyhunterskill, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[272]},
			}},
			{EffectID::shipProjectileOptimalBonuseMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[273]},
			}},
			{EffectID::shipHybridRangeBonusCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[274]},
			}},
			{EffectID::shipETspeedBonusAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[275]},
			}},
			{EffectID::missileLauncherSpeedMultiplier, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[276]},
			}},
			{EffectID::shipCruiseMissileVelocityBonusCB3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[277]},
			}},
			{EffectID::shipTorpedosVelocityBonusCB3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[278]},
			}},
			{EffectID::covertOpsCpuBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[279]},
			}},
			{EffectID::shipMissileKineticDamageCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[280]},
			}},
			{EffectID::shipMissileKineticDamageCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[281]},
			}},
			{EffectID::shipDroneScoutThermalDamageGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[282]},
			}},
			{EffectID::onlineForStructures, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::ammoInfluenceSignatureRadius, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[283]},
			}},
			{EffectID::ammoInfluenceShieldCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[14]},
			}},
			{EffectID::shipLaserRofAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[284]},
			}},
			{EffectID::shipArmorHpAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[285]},
			}},
			{EffectID::shipMissileLauncherRofCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[286]},
			}},
			{EffectID::shipDronesMaxGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[287]},
			}},
			{EffectID::shipHybridTrackingGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[288]},
			}},
			{EffectID::amarrCruiserSkillLevelPreMulShipBonusAC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[289]},
			}},
			{EffectID::caldariCruiserSkillLevelPreMulShipBonusCC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[290]},
			}},
			{EffectID::gallenteCruiserSkillLevelPreMulShipBonusGC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[291]},
			}},
			{EffectID::minmatarCruiserSkillLevelPreMulShipBonusMC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[292]},
			}},
			{EffectID::shipArmorEmResistanceAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[293]},
			}},
			{EffectID::shipArmorExplosiveResistanceAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[294]},
			}},
			{EffectID::shipArmorKineticResistanceAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[295]},
			}},
			{EffectID::shipArmorThermalResistanceAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[296]},
			}},
			{EffectID::shipProjectileDmgMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[297]},
			}},
			{EffectID::cloakingWarpSafe, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[214]},
			}},
			{EffectID::gunshipSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[298]},
			}},
			{EffectID::gunshipSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[299]},
			}},
			{EffectID::eliteBonusGunshipHybridOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[300]},
			}},
			{EffectID::eliteBonusGunshipProjectileOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[301]},
			}},
			{EffectID::eliteBonusGunshipLaserOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[302]},
			}},
			{EffectID::eliteBonusGunshipHybridTracking2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[303]},
			}},
			{EffectID::eliteBonusGunshipProjectileFalloff2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[304]},
			}},
			{EffectID::eliteBonusGunshipShieldBoost2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[305]},
			}},
			{EffectID::eliteBonusGunshipCapRecharge2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[306]},
			}},
			{EffectID::eliteBonusGunshipDroneCapacity2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[307]},
			}},
			{EffectID::selfT2SmallLaserPulseDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[308]},
			}},
			{EffectID::selfT2SmallLaserBeamDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[309]},
			}},
			{EffectID::selfT2SmallHybridBlasterDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[310]},
			}},
			{EffectID::selfT2SmallHybridRailDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[311]},
			}},
			{EffectID::selfT2SmallProjectileACDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[312]},
			}},
			{EffectID::selfT2SmallProjectileArtyDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[313]},
			}},
			{EffectID::selfT2MediumLaserPulseDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[314]},
			}},
			{EffectID::selfT2MediumLaserBeamDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[315]},
			}},
			{EffectID::selfT2MediumHybridBlasterDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[316]},
			}},
			{EffectID::selfT2MediumHybridRailDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[317]},
			}},
			{EffectID::selfT2MediumProjectileACDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[318]},
			}},
			{EffectID::selfT2MediumProjectileArtyDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[319]},
			}},
			{EffectID::selfT2LargeLaserPulseDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[320]},
			}},
			{EffectID::selfT2LargeLaserBeamDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[321]},
			}},
			{EffectID::selfT2LargeHybridBlasterDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[322]},
			}},
			{EffectID::selfT2LargeHybridRailDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[323]},
			}},
			{EffectID::selfT2LargeProjectileACDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[324]},
			}},
			{EffectID::selfT2LargeProjectileArtyDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[325]},
			}},
			{EffectID::eliteBonusGunshipHybridDmg2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[326]},
			}},
			{EffectID::anchorDropForStructures, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::anchorLiftForStructures, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::shipMissileHeavyVelocityBonusCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[327]},
			}},
			{EffectID::shipMissileLightVelocityBonusCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[328]},
			}},
			{EffectID::remoteArmorSystemsCapNeedBonusPostPercentCapacitorNeedLocationShipModulesRequiringRemoteArmorSystems, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[329]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairCapNeed1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[330]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairCapNeed2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[331]},
			}},
			{EffectID::eliteBonusLogisticShieldTransferCapNeed2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[332]},
			}},
			{EffectID::eliteBonusLogisticShieldTransferCapNeed1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[333]},
			}},
			{EffectID::shipRemoteArmorRangeGC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[334]},
			}},
			{EffectID::shipRemoteArmorRangeAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[335]},
			}},
			{EffectID::shipShieldTransferRangeCC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[336]},
			}},
			{EffectID::shipShieldTransferRangeMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[337]},
			}},
			{EffectID::logisticSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[338]},
			}},
			{EffectID::logisticSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[339]},
			}},
			{EffectID::eliteBonusHeavyGunshipHybridOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[340]},
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[341]},
			}},
			{EffectID::eliteBonusHeavyGunshipLaserOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[342]},
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileFallOff1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[343]},
			}},
			{EffectID::eliteBonusHeavyGunshipHybridDmg2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[344]},
			}},
			{EffectID::eliteBonusHeavyGunshipLaserDmg2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[345]},
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileTracking2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[346]},
			}},
			{EffectID::warshipSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[347]},
			}},
			{EffectID::warshipSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[348]},
			}},
			{EffectID::eliteBonusHeavyGunshipHybridFallOff1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[349]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyMissileFlightTime1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[350]},
			}},
			{EffectID::eliteBonusHeavyGunshipLightMissileFlightTime1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[351]},
			}},
			{EffectID::eliteBonusHeavyGunshipDroneControlRange1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[352]},
			}},
			{EffectID::projectileFiredForEntities, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::eliteBonusHeavyGunshipProjectileDmg2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[353]},
			}},
			{EffectID::shipProjectileTrackingMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[354]},
			}},
			{EffectID::controlTowerAmarrLaserDMGBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[355]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[356]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[357]},
			}},
			{EffectID::structureUnanchorForced, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::controlTowerAmarrLaserOptimalBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[358]},
			}},
			{EffectID::controlTowerSiloCapacityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[359]},
			}},
			{EffectID::controlTowerMinmatarProjectileOptimalBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[360]},
			}},
			{EffectID::controlTowerMinmatarProjectileFallOffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[361]},
			}},
			{EffectID::controlTowerMinmatarProjectileRofBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[362]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusDF2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[363]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusDF1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[364]},
			}},
			{EffectID::controlTowerGallenteHybridDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[365]},
			}},
			{EffectID::controlTowerTrackingArrayHybridOptimalBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[366]},
			}},
			{EffectID::controlTowerTrackingArrayLaserOptimalBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[367]},
			}},
			{EffectID::controlTowerTrackingArrayProjectileOptimalBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[368]},
			}},
			{EffectID::controlTowerTrackingArrayProjectileTrackingBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[369]},
			}},
			{EffectID::controlTowerTrackingArrayHybridTrackingBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[370]},
			}},
			{EffectID::controlTowerTrackingArrayLaserTrackingBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[371]},
			}},
			{EffectID::massFactor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[372]},
			}},
			{EffectID::ammoInfluenceEntityFlyRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[373]},
			}},
			{EffectID::accerationControlSkillAbMwdSpeedBoost, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[70]},{modifiers[374]},
			}},
			{EffectID::eliteBonusGunshipLaserDamage2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[375]},
			}},
			{EffectID::eliteBonusLogisticEnergyTransferCapNeed1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[376]},
			}},
			{EffectID::shipEnergyTransferRange1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[377]},
			}},
			{EffectID::eliteBonusLogisticEnergyTransferCapNeed2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[378]},
			}},
			{EffectID::shipEnergyTransferRange2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[379]},
			}},
			{EffectID::structureStealthEmitterArraySigDecrease, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[380]},
			}},
			{EffectID::miningBargeSkillLevelPostMulShipBonusORE2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[381]},
			}},
			{EffectID::iceHarvestCycleTimeModulesRequiringIceHarvesting, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[382]},
			}},
			{EffectID::iceHarvestCycleTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[383]},
			}},
			{EffectID::controlTowerCaldariEwTargetSwitchDelayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[384]},
			}},
			{EffectID::targetAttackForStructures, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::miningInfoMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[385]},
			}},
			{EffectID::controlTowerCaldariMissileVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[386]},
			}},
			{EffectID::controlTowerCaldariMissileRofBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[387]},
			}},
			{EffectID::crystalMiningamountInfo2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[388]},
			}},
			{EffectID::shipEnergyDrainAmountAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[389]},
			}},
			{EffectID::shipBonusPirateSmallHybridDmg, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[390]},
			}},
			{EffectID::shipEnergyVampireTransferAmountBonusAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[391]},
			}},
			{EffectID::shipEnergyVampireTransferAmountBonusAc, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[392]},
			}},
			{EffectID::shipStasisWebRangeBonusMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[393]},
			}},
			{EffectID::shipStasisWebRangeBonusMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[394]},
			}},
			{EffectID::shipProjectileTrackingGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[395]},
			}},
			{EffectID::shipMissileVelocityPirateFactionFrigate, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[396]},
			}},
			{EffectID::shipProjectileRofPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[397]},
			}},
			{EffectID::shipHybridDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[398]},
			}},
			{EffectID::shipMissileVelocityPirateFactionLight, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[399]},
			}},
			{EffectID::shipProjectileRofPirateBattleship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[400]},
			}},
			{EffectID::shipHybridDmgPirateBattleship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[401]},
			}},
			{EffectID::smugglingModifier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[402]},
			}},
			{EffectID::setBonusBloodraider, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[403]},
			}},
			{EffectID::setBonusBloodraiderNosferatu, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[404]},
			}},
			{EffectID::blackMarketTradingSkillBoostContrabandDetectionChanceBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[405]},
			}},
			{EffectID::skillBoostContrabandDetectionChanceBonusEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[406]},
			}},
			{EffectID::setBonusSerpentis, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[407]},
			}},
			{EffectID::setBonusSerpentis2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[408]},
			}},
			{EffectID::interceptor2HybridTracking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[409]},
			}},
			{EffectID::interceptor2LaserTracking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[410]},
			}},
			{EffectID::interceptors2SkillLevelPreMulEliteBonusInterceptorShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[411]},
			}},
			{EffectID::structuralAnalysisEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[412]},
			}},
			{EffectID::eliteIndustrial1SkillLevelPreMulEliteBonusEliteIndustrialShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[413]},
			}},
			{EffectID::eliteIndustrial2SkillLevelPreMulEliteBonusEliteIndustrialShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[414]},
			}},
			{EffectID::amarrIndustrialSkillLevelPreMulShipBonusAI22Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[415]},
			}},
			{EffectID::caldariIndustrialSkillLevelPreMulShipBonusCI2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[416]},
			}},
			{EffectID::gallenteIndustrialSkillLevelPreMulShipBonusGI2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[417]},
			}},
			{EffectID::minmatarIndustrialSkillLevelPreMulShipBonusMI2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[418]},
			}},
			{EffectID::ewSkillScanStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[419]},{modifiers[420]},{modifiers[421]},{modifiers[422]},
			}},
			{EffectID::ewSkillScanStrengthBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[423]},
			}},
			{EffectID::propulsionSkillPropulsionStrengthBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[424]},
			}},
			{EffectID::ewSkillRsdCapNeedBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[425]},
			}},
			{EffectID::ewSkillTdCapNeedBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[426]},
			}},
			{EffectID::ewSkillTpCapNeedBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[427]},
			}},
			{EffectID::ewSkillEwCapNeedSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[428]},
			}},
			{EffectID::ewSkillTargetPaintingStrengthBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[429]},
			}},
			{EffectID::leadershipCpuBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[430]},
			}},
			{EffectID::shieldBoostAmplifierPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[431]},
			}},
			{EffectID::setBonusGuristas, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[432]},
			}},
			{EffectID::covertOpsSkillLevelPreMulEliteBonusCoverOpsShip2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[433]},
			}},
			{EffectID::systemScanDurationSkillAstrometrics, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[434]},
			}},
			{EffectID::propulsionSkillCapNeedBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[435]},
			}},
			{EffectID::shipBonusHybridOptimalCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[436]},
			}},
			{EffectID::caldariShipEwStrengthCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[437]},{modifiers[438]},{modifiers[439]},{modifiers[440]},
			}},
			{EffectID::caldariShipEwOptimalRangeCB3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[441]},
			}},
			{EffectID::caldariShipEwOptimalRangeCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[442]},
			}},
			{EffectID::caldariShipEwCapacitorNeedCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[443]},
			}},
			{EffectID::ewSkillRsdMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[444]},
			}},
			{EffectID::ewSkillTpMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[445]},
			}},
			{EffectID::ewSkillTdMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[446]},
			}},
			{EffectID::ewSkillRsdFallOffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[447]},
			}},
			{EffectID::ewSkillTpFallOffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[448]},
			}},
			{EffectID::ewSkillTdFallOffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[449]},
			}},
			{EffectID::ewSkillEwMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[450]},
			}},
			{EffectID::ewSkillEwFallOffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[451]},
			}},
			{EffectID::missileSkillAoeVelocityBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[452]},
			}},
			{EffectID::missileSkillAoeCloudSizeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[453]},
			}},
			{EffectID::missileSkillAoeCloudSizeBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[454]},
			}},
			{EffectID::contrabandMasking, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[242]},{modifiers[406]},
			}},
			{EffectID::flagshipmultiRelayEffect, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[455]},
			}},
			{EffectID::shieldOperationSkillBoostCapacitorNeedBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[456]},
			}},
			{EffectID::shieldOperationSkillBoostCapacitorNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[457]},
			}},
			{EffectID::ewTargetPaint, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[458]},
			}},
			{EffectID::ewSkillTargetPaintingStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[459]},
			}},
			{EffectID::minmatarShipEwTargetPainterMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[460]},
			}},
			{EffectID::angelsetbonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[461]},
			}},
			{EffectID::setBonusSansha, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[462]},
			}},
			{EffectID::jumpDriveSkillsRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[463]},
			}},
			{EffectID::jumpDriveSkillsRangeBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[464]},
			}},
			{EffectID::capitalTurretSkillLaserDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[465]},
			}},
			{EffectID::capitalTurretSkillProjectileDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[466]},
			}},
			{EffectID::capitalTurretSkillHybridDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[467]},
			}},
			{EffectID::capitalLauncherSkillCitadelKineticDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[468]},
			}},
			{EffectID::missileSkillAoeVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[469]},
			}},
			{EffectID::capitalLauncherSkillCitadelEmDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[470]},
			}},
			{EffectID::capitalLauncherSkillCitadelExplosiveDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[471]},
			}},
			{EffectID::capitalLauncherSkillCitadelThermalDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[472]},
			}},
			{EffectID::missileSkillWarheadUpgradesEmDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[473]},
			}},
			{EffectID::missileSkillWarheadUpgradesExplosiveDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[474]},
			}},
			{EffectID::missileSkillWarheadUpgradesKineticDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[475]},
			}},
			{EffectID::skillAdvancedSpaceshipAgilityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[476]},
			}},
			{EffectID::shipAdvancedSpaceshipCommandAgilityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[477]},
			}},
			{EffectID::skillCapitalShipsAdvancedAgility, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[478]},
			}},
			{EffectID::shipCapitalAgilityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[479]},
			}},
			{EffectID::capitalShieldOperationSkillCapacitorNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[480]},
			}},
			{EffectID::capitalRepairSystemsSkillDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[481]},
			}},
			{EffectID::skillAdvancedWeaponUpgradesPowerNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[482]},{modifiers[483]},
			}},
			{EffectID::armoredCommandMindlink, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[484]},{modifiers[485]},{modifiers[486]},{modifiers[487]},{modifiers[488]},
			}},
			{EffectID::skirmishCommandMindlink, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[489]},{modifiers[490]},{modifiers[491]},{modifiers[492]},{modifiers[493]},
			}},
			{EffectID::shieldCommandMindlink, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[494]},{modifiers[495]},{modifiers[496]},{modifiers[497]},{modifiers[498]},
			}},
			{EffectID::informationCommandMindlink, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[499]},{modifiers[500]},{modifiers[501]},{modifiers[502]},{modifiers[503]},
			}},
			{EffectID::skillSiegeModuleConsumptionQuantityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[504]},
			}},
			{EffectID::skillCynosuralSiegeConsumQuantityBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[505]},
			}},
			{EffectID::missileSkillWarheadUpgradesThermalDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[506]},
			}},
			{EffectID::freighterA1SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[507]},
			}},
			{EffectID::freighterA2SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[508]},
			}},
			{EffectID::freighterC1SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[509]},
			}},
			{EffectID::freighterC2SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[510]},
			}},
			{EffectID::freighterG1SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[511]},
			}},
			{EffectID::freighterG2SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[512]},
			}},
			{EffectID::freighterM1SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[513]},
			}},
			{EffectID::freighterM2SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[514]},
			}},
			{EffectID::freighterCargoBonusA2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[515]},
			}},
			{EffectID::freighterCargoBonusC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[516]},
			}},
			{EffectID::freighterCargoBonusG2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[517]},
			}},
			{EffectID::freighterCargoBonusM2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[518]},
			}},
			{EffectID::freighterMaxVelocityBonusA1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[519]},
			}},
			{EffectID::freighterMaxVelocityBonusC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[520]},
			}},
			{EffectID::freighterMaxVelocityBonusG1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[521]},
			}},
			{EffectID::freighterMaxVelocityBonusM1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[522]},
			}},
			{EffectID::shieldBoostAmplifier, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[431]},{modifiers[523]},
			}},
			{EffectID::jumpDriveSkillsCapacitorNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[524]},
			}},
			{EffectID::jumpDriveSkillsCapacitorNeedBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[525]},
			}},
			{EffectID::droneDmgBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[526]},
			}},
			{EffectID::doHacking, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::missileSkillRapidLauncherRoF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[527]},
			}},
			{EffectID::missileSkillMissileProjectileVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[528]},
			}},
			{EffectID::missileSkillMissileProjectileVelocityBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[529]},
			}},
			{EffectID::shipFalloffBonusGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[530]},
			}},
			{EffectID::shipArmorEMResistanceAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[531]},
			}},
			{EffectID::shipArmorTHResistanceAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[532]},
			}},
			{EffectID::shipArmorKNResistanceAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[533]},
			}},
			{EffectID::shipArmorEXResistanceAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[534]},
			}},
			{EffectID::shipShieldEMResistanceCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[535]},
			}},
			{EffectID::shipShieldThermalResistanceCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[536]},
			}},
			{EffectID::shipShieldKineticResistanceCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[537]},
			}},
			{EffectID::shipShieldExplosiveResistanceCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[538]},
			}},
			{EffectID::shipShieldEMResistanceCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[539]},
			}},
			{EffectID::shipShieldThermalResistanceCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[540]},
			}},
			{EffectID::shipShieldKineticResistanceCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[541]},
			}},
			{EffectID::shipShieldExplosiveResistanceCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[542]},
			}},
			{EffectID::eliteBargeSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[543]},
			}},
			{EffectID::eliteBargeSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[544]},
			}},
			{EffectID::miningForemanMindlink, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[545]},{modifiers[546]},{modifiers[547]},{modifiers[548]},{modifiers[549]},
			}},
			{EffectID::miningBargeSkillLevelPostMulShipBonusORE3Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[550]},
			}},
			{EffectID::selfRof, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[551]},
			}},
			{EffectID::shipMissileEMDamageCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[552]},
			}},
			{EffectID::shipMissileThermalDamageCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[553]},
			}},
			{EffectID::shipMissileExplosiveDamageCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[554]},
			}},
			{EffectID::miningYieldMultiplyPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[125]},
			}},
			{EffectID::shipCruiseLauncherROFBonus2CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[555]},
			}},
			{EffectID::shipSiegeLauncherROFBonus2CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[556]},
			}},
			{EffectID::miningUpgradeCPUReductionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[557]},
			}},
			{EffectID::eliteBargeBonusIceHarvestingCycleTimeBarge3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[558]},
			}},
			{EffectID::shieldCompensationSkillBoostHardeningBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[559]},
			}},
			{EffectID::reconShipSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[560]},
			}},
			{EffectID::reconShipSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[561]},
			}},
			{EffectID::eliteBonusVampireDrainAmount2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[562]},
			}},
			{EffectID::eliteReconBonusGravimetricStrength2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[563]},
			}},
			{EffectID::eliteReconBonusMagnetometricStrength2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[564]},
			}},
			{EffectID::eliteReconBonusRadarStrength2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[565]},
			}},
			{EffectID::eliteReconBonusLadarStrength2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[566]},
			}},
			{EffectID::eliteReconStasisWebBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[567]},
			}},
			{EffectID::eliteReconScramblerRangeBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[568]},
			}},
			{EffectID::ammoEMResistOther, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[569]},
			}},
			{EffectID::armorReinforcerMassAdd, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[570]},
			}},
			{EffectID::signatureRadiusBonus, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[571]},
			}},
			{EffectID::shipBonusShieldTransferCapneed1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[572]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedGC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[573]},
			}},
			{EffectID::caldariShipEwCapacitorNeedCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[574]},
			}},
			{EffectID::droneRangeBonusAdd, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[165]},
			}},
			{EffectID::cynosuralDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[575]},
			}},
			{EffectID::propulsionDroneJammingStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[576]},
			}},
			{EffectID::droneMaxVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[577]},
			}},
			{EffectID::droneMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[578]},
			}},
			{EffectID::droneDurabilityShieldCapBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[579]},
			}},
			{EffectID::droneDurabilityArmorHPBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[580]},
			}},
			{EffectID::droneDurabilityHPBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[581]},
			}},
			{EffectID::damageRepairedSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[582]},
			}},
			{EffectID::repairDroneShieldBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[583]},
			}},
			{EffectID::repairDroneArmorDamageAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[584]},
			}},
			{EffectID::addToSignatureRadius2, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[585]},
			}},
			{EffectID::modifyArmorResonancePostPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::modifyShieldResonancePostPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::emShieldCompensationHardeningBonusGroupShieldAmp, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[594]},
			}},
			{EffectID::explosiveShieldCompensationHardeningBonusGroupShieldAmp, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[595]},
			}},
			{EffectID::kineticShieldCompensationHardeningBonusGroupShieldAmp, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[596]},
			}},
			{EffectID::thermalShieldCompensationHardeningBonusGroupShieldAmp, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[597]},
			}},
			{EffectID::emArmorCompensationHardeningBonusGroupArmorCoating, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[598]},
			}},
			{EffectID::explosiveArmorCompensationHardeningBonusGroupArmorCoating, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[599]},
			}},
			{EffectID::kineticArmorCompensationHardeningBonusGroupArmorCoating, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[600]},
			}},
			{EffectID::thermicArmorCompensationHardeningBonusGroupArmorCoating, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[601]},
			}},
			{EffectID::emArmorCompensationHardeningBonusGroupEnergized, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[602]},
			}},
			{EffectID::explosiveArmorCompensationHardeningBonusGroupEnergized, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[603]},
			}},
			{EffectID::kineticArmorCompensationHardeningBonusGroupEnergized, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[604]},
			}},
			{EffectID::thermicArmorCompensationHardeningBonusGroupEnergized, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[605]},
			}},
			{EffectID::smallHybridMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[606]},
			}},
			{EffectID::smallEnergyMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[607]},
			}},
			{EffectID::smallProjectileMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[608]},
			}},
			{EffectID::energyTransferArrayMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[609]},
			}},
			{EffectID::shieldTransporterMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[610]},{modifiers[611]},
			}},
			{EffectID::armorRepairProjectorMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[612]},{modifiers[613]},
			}},
			{EffectID::minmatarShipEwTargetPainterMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[614]},
			}},
			{EffectID::droneDamageBonusRequringDrones, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[615]},
			}},
			{EffectID::jumpPortalGeneration, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},
			}},
			{EffectID::eliteBonusCommandShipProjectileDamageCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[618]},
			}},
			{EffectID::eliteBonusCommandShipProjectileFalloffCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[619]},
			}},
			{EffectID::eliteBonusCommandShipLaserDamageCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[620]},
			}},
			{EffectID::eliteBonusCommandShipLaserROFCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[621]},
			}},
			{EffectID::eliteBonusCommandShipHybridFalloffCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[622]},
			}},
			{EffectID::eliteBonusCommandShipHybridOptimalCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[623]},
			}},
			{EffectID::shipBonusDroneHitpointsGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[624]},{modifiers[625]},{modifiers[626]},
			}},
			{EffectID::shipBonusDroneHitpointsFixedAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[627]},{modifiers[628]},{modifiers[629]},
			}},
			{EffectID::shipBonusDroneHitpointsGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[630]},{modifiers[631]},{modifiers[632]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[633]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[634]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[635]},
			}},
			{EffectID::eliteBonusInterdictorsMissileKineticDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[636]},
			}},
			{EffectID::eliteBonusInterdictorsProjectileFalloff1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[637]},
			}},
			{EffectID::shipBonusPirateFrigateProjDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[638]},
			}},
			{EffectID::scanStrengthBonusPercentActivate, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::scanStrengthBonusPercentOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::scanStrengthTargetPercentBonus, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[643]},{modifiers[644]},{modifiers[645]},{modifiers[646]},
			}},
			{EffectID::shipBonusDroneMiningAmountAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[647]},
			}},
			{EffectID::shipBonusDroneMiningAmountGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[648]},
			}},
			{EffectID::commandshipMultiRelayEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[455]},{modifiers[649]},
			}},
			{EffectID::covertOpsAndReconOpsCloakModuleDelayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[650]},
			}},
			{EffectID::covertOpsStealthBomberTargettingDelayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[651]},
			}},
			{EffectID::tractorBeamCan, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::modifyArmorResonancePassivePostPercentPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[652]},{modifiers[653]},{modifiers[654]},{modifiers[655]},
			}},
			{EffectID::modifyShieldResonancePassivePostPercentPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[656]},{modifiers[657]},{modifiers[658]},{modifiers[659]},
			}},
			{EffectID::scanStrengthBonusPercentPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::damageControl, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[660]},{modifiers[661]},{modifiers[662]},{modifiers[663]},{modifiers[664]},{modifiers[665]},{modifiers[666]},{modifiers[667]},{modifiers[668]},{modifiers[669]},{modifiers[670]},{modifiers[671]},
			}},
			{EffectID::eliteReconBonusEnergyNeutAmount2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[672]},
			}},
			{EffectID::skillADDmaxJumpClones, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[673]},
			}},
			{EffectID::disallowOffensiveActChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[674]},
			}},
			{EffectID::capitalRemoteArmorRepairerCapNeedBonusSkill, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[675]},
			}},
			{EffectID::capitalRemoteShieldTransferCapNeedBonusSkill, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[676]},
			}},
			{EffectID::capitalRemoteEnergyTransferCapNeedBonusSkill, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[677]},
			}},
			{EffectID::skillSuperWeaponDmgBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[678]},{modifiers[679]},{modifiers[680]},{modifiers[681]},
			}},
			{EffectID::cloneVatMaxJumpCloneBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[682]},
			}},
			{EffectID::snowBallLaunching, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::implantVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[683]},
			}},
			{EffectID::skillInterdictorEliteBonus1SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[684]},
			}},
			{EffectID::skillInterdictorEliteBonus2SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[685]},
			}},
			{EffectID::energyManagementSkillBoostCapacitorCapacityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[686]},
			}},
			{EffectID::energyManagementCapacitorBonusPostPercentCapacityLocationShipGroupCapacitorCapacityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[687]},
			}},
			{EffectID::minerCpuUsageMultiplyPercent2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[688]},
			}},
			{EffectID::iceMinerCpuUsagePercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[689]},
			}},
			{EffectID::commandShipSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[690]},
			}},
			{EffectID::commandShipSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[691]},
			}},
			{EffectID::miningUpgradeCPUPenaltyReductionModulesRequiringMiningUpgradePercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[692]},
			}},
			{EffectID::shipBonusArmorResistAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[693]},{modifiers[694]},{modifiers[695]},{modifiers[696]},
			}},
			{EffectID::iceHarvestCycleTimeModulesRequiringIceHarvestingOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[382]},
			}},
			{EffectID::warpScrambleForStructure, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[8]},
			}},
			{EffectID::implantArmorHpBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[697]},
			}},
			{EffectID::implantVelocityBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[698]},
			}},
			{EffectID::shipBonusRemoteTrackingComputerFalloffMC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[699]},
			}},
			{EffectID::shipBonusRemoteTrackingComputerFalloffGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[700]},
			}},
			{EffectID::ewSkillEcmBurstRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[701]},
			}},
			{EffectID::ewSkillEcmBurstCapNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[702]},
			}},
			{EffectID::shipHTTrackingBonusGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[703]},
			}},
			{EffectID::shipBonusHybridTrackingGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[704]},
			}},
			{EffectID::eliteBonusAssaultShipMissileVelocity1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[705]},
			}},
			{EffectID::neurotoxinRecoverySkillBoostChanceBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[706]},
			}},
			{EffectID::modifyBoosterEffectChanceWithBoosterChanceBonusPostPercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[707]},{modifiers[708]},{modifiers[709]},{modifiers[710]},{modifiers[711]},
			}},
			{EffectID::naniteControlSkillBoostBoosterAttributeModifier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[712]},
			}},
			{EffectID::shipBonusEmShieldResistanceCB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[713]},
			}},
			{EffectID::shipBonusExplosiveShieldResistanceCB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[714]},
			}},
			{EffectID::shipBonusKineticShieldResistanceCB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[715]},
			}},
			{EffectID::shipBonusThermicShieldResistanceCB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[716]},
			}},
			{EffectID::eliteBonusGunshipProjectileDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[717]},
			}},
			{EffectID::eliteBonusGunshipProjectileDamage2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[718]},
			}},
			{EffectID::increaseSignatureRadiusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[380]},
			}},
			{EffectID::scanResolutionMultiplierOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[269]},
			}},
			{EffectID::maxTargetRangeBonus, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[167]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyMissileLaunhcerRof2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[719]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyAssaultMissileLaunhcerRof2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[720]},
			}},
			{EffectID::eliteBonusHeavyGunshipAssaultMissileLaunhcerRof2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[721]},
			}},
			{EffectID::scanStrengthBonusSkillLevelIncrease, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[722]},
			}},
			{EffectID::rigSlot, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::sensorBoosterActivePercentage, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[167]},{modifiers[232]},{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},
			}},
			{EffectID::capNeedBonusEffectLasers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[723]},
			}},
			{EffectID::capNeedBonusEffectHybrids, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[724]},
			}},
			{EffectID::cpuNeedBonusEffectLasers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[725]},
			}},
			{EffectID::cpuNeedBonusEffectHybrid, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[726]},
			}},
			{EffectID::cpuNeedBonusEffectProjectile, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[727]},
			}},
			{EffectID::falloffBonusEffectLasers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[728]},
			}},
			{EffectID::falloffBonusEffectHybrids, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[729]},
			}},
			{EffectID::falloffBonusEffectProjectiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[730]},
			}},
			{EffectID::maxRangeBonusEffectLasers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[731]},
			}},
			{EffectID::maxRangeBonusEffectHybrids, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[732]},
			}},
			{EffectID::maxRangeBonusEffectProjectiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[733]},
			}},
			{EffectID::drawbackPowerNeedLasers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[734]},
			}},
			{EffectID::drawbackPowerNeedHybrids, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[735]},
			}},
			{EffectID::drawbackPowerNeedProjectiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[736]},
			}},
			{EffectID::drawbackArmorHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[737]},
			}},
			{EffectID::drawbackCPUOutput, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[738]},
			}},
			{EffectID::drawbackCPUNeedLaunchers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[739]},
			}},
			{EffectID::drawbackSigRad, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[740]},
			}},
			{EffectID::drawbackMaxVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[741]},
			}},
			{EffectID::drawbackShieldCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[742]},
			}},
			{EffectID::rigDrawbackSkillEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[743]},
			}},
			{EffectID::miningClouds, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::gasCloudHarvestingMaxGroupSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[744]},
			}},
			{EffectID::shipECMScanStrengthBonusCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[745]},{modifiers[746]},{modifiers[747]},{modifiers[748]},
			}},
			{EffectID::boosterArmorHpPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[749]},
			}},
			{EffectID::boosterArmorRepairAmountPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[750]},
			}},
			{EffectID::boosterShieldCapacityPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[751]},
			}},
			{EffectID::boosterTurretOptimalRangePenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[752]},
			}},
			{EffectID::boosterTurretFalloffPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[753]},
			}},
			{EffectID::boosterCapacitorCapacityPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[754]},
			}},
			{EffectID::boosterMaxVelocityPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[755]},
			}},
			{EffectID::boosterTurretTrackingPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[756]},
			}},
			{EffectID::boosterMissileVelocityPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[757]},
			}},
			{EffectID::boosterMissileExplosionVelocityPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[758]},
			}},
			{EffectID::shipBonusECMStrengthBonusCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[759]},{modifiers[760]},{modifiers[761]},{modifiers[762]},
			}},
			{EffectID::salvaging, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::boosterModifyBoosterArmorPenalties, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[763]},{modifiers[764]},
			}},
			{EffectID::boosterModifyBoosterShieldPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[765]},{modifiers[766]},
			}},
			{EffectID::boosterModifyBoosterMaxVelocityAndCapacitorPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[767]},{modifiers[768]},
			}},
			{EffectID::boosterModifyBoosterMissilePenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[769]},{modifiers[770]},{modifiers[771]},
			}},
			{EffectID::boosterModifyBoosterTurretPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[772]},{modifiers[773]},{modifiers[774]},
			}},
			{EffectID::boosterMissileExplosionCloudPenaltyFixed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[775]},
			}},
			{EffectID::modifyArmorResonancePostPercentPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::salvagingAccessDifficultyBonusEffectPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[776]},
			}},
			{EffectID::modifyShieldResonancePostPercentPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::massReductionBonusPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[777]},
			}},
			{EffectID::projectileWeaponSpeedMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[21]},
			}},
			{EffectID::projectileWeaponDamageMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[23]},
			}},
			{EffectID::missileLauncherSpeedMultiplierPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[276]},
			}},
			{EffectID::energyWeaponSpeedMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[25]},
			}},
			{EffectID::hybridWeaponDamageMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[24]},
			}},
			{EffectID::energyWeaponDamageMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[22]},
			}},
			{EffectID::hybridWeaponSpeedMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[26]},
			}},
			{EffectID::shipBonusLargeEnergyWeaponDamageAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[778]},
			}},
			{EffectID::shipMissileAssaultMissileVelocityBonusCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[779]},
			}},
			{EffectID::eliteBonusHeavyGunshipAssaultMissileFlightTime1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[780]},
			}},
			{EffectID::caldariShipECMBurstOptimalRangeCB3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[781]},
			}},
			{EffectID::maxScanDeviationSelfSkillModifier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[782]},
			}},
			{EffectID::armorHPBonusAdd, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[783]},
			}},
			{EffectID::skillBoostTrackingSpeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[784]},
			}},
			{EffectID::trackingSpeedBonusPassiveRequiringGunneryTrackingSpeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[785]},
			}},
			{EffectID::accessDifficultyBonusModifierRequiringArchaelogy, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[786]},
			}},
			{EffectID::accessDifficultyBonusModifierRequiringHacking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[787]},
			}},
			{EffectID::durationBonusForGroupAfterburner, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[788]},
			}},
			{EffectID::missileDMGBonusPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[258]},
			}},
			{EffectID::maxTargetingRangeBonusPremulPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[31]},
			}},
			{EffectID::cloakingTargetingDelayBonusLRSMCloakingPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[789]},
			}},
			{EffectID::cynosuralGeneration, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[790]},
			}},
			{EffectID::cloneJumpAccepting, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[790]},
			}},
			{EffectID::velocityBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[683]},
			}},
			{EffectID::biologyTimeBonusFixed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[791]},
			}},
			{EffectID::sentryDroneDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[792]},
			}},
			{EffectID::armorDamageAmountBonusCapitalArmorRepairers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[793]},
			}},
			{EffectID::missileVelocityBonusDefender, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[794]},
			}},
			{EffectID::missileEMDmgBonusCruise3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[795]},
			}},
			{EffectID::missileExplosiveDmgBonusCruise3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[796]},
			}},
			{EffectID::missileKineticDmgBonusCruise3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[797]},
			}},
			{EffectID::missileThermalDmgBonusCruise3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[798]},
			}},
			{EffectID::gasHarvestingCycleTimeModulesRequiringGasCloudHarvesting, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[799]},
			}},
			{EffectID::setMaxLockedTargets, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[800]},
			}},
			{EffectID::missileEMDmgBonusRocket, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[801]},
			}},
			{EffectID::missileExplosiveDmgBonusRocket, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[802]},
			}},
			{EffectID::missileKineticDmgBonusRocket, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[803]},
			}},
			{EffectID::missileThermalDmgBonusRocket, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[804]},
			}},
			{EffectID::missileEMDmgBonusStandard, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[805]},
			}},
			{EffectID::missileExplosiveDmgBonusStandard, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[806]},
			}},
			{EffectID::missileKineticDmgBonusStandard, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[807]},
			}},
			{EffectID::missileThermalDmgBonusStandard, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[808]},
			}},
			{EffectID::missileEMDmgBonusHeavy, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[809]},
			}},
			{EffectID::missileExplosiveDmgBonusHeavy, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[810]},
			}},
			{EffectID::missileKineticDmgBonusHeavy, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[811]},
			}},
			{EffectID::missileThermalDmgBonusHeavy, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[812]},
			}},
			{EffectID::missileEMDmgBonusHAM, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[813]},
			}},
			{EffectID::missileExplosiveDmgBonusHAM, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[814]},
			}},
			{EffectID::missileKineticDmgBonusHAM, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[815]},
			}},
			{EffectID::missileThermalDmgBonusHAM, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[816]},
			}},
			{EffectID::missileEMDmgBonusTorpedo, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[817]},
			}},
			{EffectID::missileExplosiveDmgBonusTorpedo, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[818]},
			}},
			{EffectID::missileKineticDmgBonusTorpedo, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[819]},
			}},
			{EffectID::missileThermalDmgBonusTorpedo, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[820]},
			}},
			{EffectID::dataminerModuleDurationReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[821]},
			}},
			{EffectID::posStructureControlAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[822]},
			}},
			{EffectID::skillTriageModuleConsumptionQuantityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[823]},
			}},
			{EffectID::bombLaunching, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::skillRemoteECMDurationBonusSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[824]},
			}},
			{EffectID::tskillRemoteHullRepairSystemsCapNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[825]},
			}},
			{EffectID::skillCapitalRemoteHullRepairSystemsCapNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[826]},
			}},
			{EffectID::skillRemoteECMDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[827]},{modifiers[828]},{modifiers[829]},{modifiers[830]},{modifiers[831]},
			}},
			{EffectID::overloadRofBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[832]},
			}},
			{EffectID::overloadSelfDurationBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[833]},
			}},
			{EffectID::eliteBonusCoverOpsBombExplosiveDmg1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[834]},
			}},
			{EffectID::overloadSelfDamageBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[835]},
			}},
			{EffectID::eliteBonusCoverOpsBombKineticDmg1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[836]},
			}},
			{EffectID::eliteBonusCoverOpsBombThermalDmg1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[837]},
			}},
			{EffectID::eliteBonusCoverOpsBombEmDmg1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[838]},
			}},
			{EffectID::overloadSelfEmHardeningBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[839]},
			}},
			{EffectID::overloadSelfThermalHardeningBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[840]},
			}},
			{EffectID::overloadSelfExplosiveHardeningBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[841]},
			}},
			{EffectID::overloadSelfKineticHardeningBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[842]},
			}},
			{EffectID::overloadSelfHardeningInvulnerabilityBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[839]},{modifiers[840]},{modifiers[841]},{modifiers[842]},
			}},
			{EffectID::skillBombDeploymentModuleReactivationDelayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[843]},
			}},
			{EffectID::modifyMaxVelocityOfShipPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[214]},
			}},
			{EffectID::structureHPMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[17]},
			}},
			{EffectID::heatDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[844]},
			}},
			{EffectID::controlTowerGenericHullResistanceBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[845]},{modifiers[846]},{modifiers[847]},{modifiers[848]},{modifiers[849]},{modifiers[850]},{modifiers[851]},{modifiers[852]},{modifiers[853]},{modifiers[854]},{modifiers[855]},{modifiers[856]},{modifiers[857]},{modifiers[858]},{modifiers[859]},{modifiers[860]},{modifiers[861]},{modifiers[862]},{modifiers[863]},{modifiers[864]},{modifiers[865]},{modifiers[866]},{modifiers[867]},{modifiers[868]},{modifiers[869]},{modifiers[870]},{modifiers[871]},{modifiers[872]},{modifiers[873]},{modifiers[874]},{modifiers[875]},{modifiers[876]},{modifiers[877]},{modifiers[878]},{modifiers[879]},{modifiers[880]},{modifiers[881]},{modifiers[882]},{modifiers[883]},{modifiers[884]},{modifiers[885]},{modifiers[886]},{modifiers[887]},{modifiers[888]},{modifiers[889]},{modifiers[890]},{modifiers[891]},{modifiers[892]},
			}},
			{EffectID::shieldTransportCpuNeedBonusEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[893]},
			}},
			{EffectID::droneArmorDamageBonusEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[894]},
			}},
			{EffectID::droneShieldBonusBonusEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[895]},
			}},
			{EffectID::overloadSelfRangeBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[896]},
			}},
			{EffectID::overloadSelfSpeedBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[897]},
			}},
			{EffectID::overloadSelfECMStrenghtBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[898]},{modifiers[899]},{modifiers[900]},{modifiers[901]},
			}},
			{EffectID::overloadSelfECCMStrenghtBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[902]},{modifiers[903]},{modifiers[904]},{modifiers[905]},
			}},
			{EffectID::thermodynamicsSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[906]},
			}},
			{EffectID::thermodynamicsSkillDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[907]},
			}},
			{EffectID::overloadSelfArmorDamageAmountDurationBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[833]},{modifiers[908]},
			}},
			{EffectID::overloadSelfShieldBonusDurationBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[833]},{modifiers[909]},
			}},
			{EffectID::missileSkillFoFAoeCloudSizeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[910]},
			}},
			{EffectID::shipRocketExplosiveDmgAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[911]},
			}},
			{EffectID::shipRocketKineticDmgAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[912]},
			}},
			{EffectID::shipRocketThermalDmgAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[913]},
			}},
			{EffectID::shipRocketEmDmgAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[914]},
			}},
			{EffectID::eliteBonusGunshipArmorEmResistance1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[915]},
			}},
			{EffectID::eliteBonusGunshipArmorThermalResistance1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[916]},
			}},
			{EffectID::eliteBonusGunshipArmorKineticResistance1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[917]},
			}},
			{EffectID::eliteBonusGunshipArmorExplosiveResistance1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[918]},
			}},
			{EffectID::shipCapRecharge2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[919]},
			}},
			{EffectID::tacticalShieldManipulationBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[920]},
			}},
			{EffectID::shipCommandBonusEffectiveMultiplierOreCapital2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[921]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[922]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[923]},
			}},
			{EffectID::skillIndustrialReconfigurationConsumptionQuantityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[924]},
			}},
			{EffectID::shipConsumptionQuantityBonusIndustrialReconfigurationORECapital1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[925]},
			}},
			{EffectID::miningDirectorBonusCommandBonusEffective, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[926]},
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[927]},
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[928]},
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[929]},
			}},
			{EffectID::oreCapitalShipShieldTransferRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[930]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[931]},
			}},
			{EffectID::cloneVatMaxJumpCloneBonusSkillNew, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[932]},
			}},
			{EffectID::shipBonusORECapShipDroneDmgBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[933]},
			}},
			{EffectID::shipBonusORECapShipDroneArmorHPAndShieldHPAndHpBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[934]},{modifiers[935]},{modifiers[936]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier4, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[937]},
			}},
			{EffectID::eliteBonusCommandShipArmorHP1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[938]},
			}},
			{EffectID::shipArmorEmResistanceMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[939]},
			}},
			{EffectID::shipArmorExplosiveResistanceMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[940]},
			}},
			{EffectID::shipArmorKineticResistanceMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[941]},
			}},
			{EffectID::shipArmorThermalResistanceMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[942]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsProjectileFalloff1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[943]},
			}},
			{EffectID::heavyInterdictorsSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[944]},
			}},
			{EffectID::heavyInterdictorsSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[945]},
			}},
			{EffectID::eliteBonusHeavyInterdictorHeavyMissileVelocityBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[946]},
			}},
			{EffectID::eliteBonusHeavyInterdictorHeavyAssaultMissileVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[947]},
			}},
			{EffectID::eliteBonusHeavyInterdictorLightMissileVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[948]},
			}},
			{EffectID::electronicAttackShipsSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[949]},
			}},
			{EffectID::electronicAttackShipsSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[950]},
			}},
			{EffectID::shipRemoteSensorDampenerCapNeedGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[951]},
			}},
			{EffectID::eliteBonusElectronicAttackShipWarpScramblerMaxRange1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[952]},
			}},
			{EffectID::eliteBonusElectronicAttackShipECMOptimalRange1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[953]},
			}},
			{EffectID::eliteBonusElectronicAttackShipStasisWebMaxRange1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[954]},
			}},
			{EffectID::eliteBonusElectronicAttackShipWarpScramblerCapNeed2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[955]},
			}},
			{EffectID::eliteBonusElectronicAttackShipSignatureRadius2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[956]},
			}},
			{EffectID::implantHardwiringABcapacitorNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[166]},
			}},
			{EffectID::warpDisruptSphere, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::eliteBonusBlackOpsLargeEnergyTurretTracking1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[957]},
			}},
			{EffectID::eliteBonusBlackOpsCloakVelocity2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[958]},
			}},
			{EffectID::blackOpsSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[959]},
			}},
			{EffectID::blackOpsSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[960]},
			}},
			{EffectID::eliteBonusBlackOpsMaxVelocity1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[961]},
			}},
			{EffectID::violatorsSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[962]},
			}},
			{EffectID::violatorsSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[963]},
			}},
			{EffectID::eliteBonusViolatorsLargeEnergyTurretDamageRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[964]},
			}},
			{EffectID::eliteBonusViolatorsLargeHybridTurretDamageRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[965]},
			}},
			{EffectID::eliteBonusViolatorsLargeProjectileTurretDamageRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[966]},
			}},
			{EffectID::eliteBonusViolatorsLargeHybridTurretTracking1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[967]},
			}},
			{EffectID::eliteBonusViolatorsLargeProjectileTurretTracking1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[968]},
			}},
			{EffectID::eliteBonusViolatorsTractorBeamMaxRangeRole2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[969]},
			}},
			{EffectID::eliteBonusViolatorsEwTargetPainting1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[970]},
			}},
			{EffectID::shipBonusPTFalloffMB1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[971]},
			}},
			{EffectID::eliteBonusElectronicAttackShipRechargeRate2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[972]},
			}},
			{EffectID::eliteBonusElectronicAttackShipCapacitorCapacity2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[973]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsWarpDisruptFieldGeneratorWarpScrambleRange2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[974]},
			}},
			{EffectID::eliteBonusViolatorsTractorBeamMaxTractorVelocityRole3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[975]},
			}},
			{EffectID::shipLaserDamagePirateBattleship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[976]},
			}},
			{EffectID::shipTrackingBonusAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[977]},
			}},
			{EffectID::shipBonusMediumEnergyTurretDamagePirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[978]},
			}},
			{EffectID::shipBonusMediumEnergyTurretTrackingAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[979]},
			}},
			{EffectID::shipBonusSmallEnergyTurretDamagePirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[980]},
			}},
			{EffectID::shipBonusSmallEnergyTurretTracking2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[981]},
			}},
			{EffectID::rorqualCargoScanRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[982]},
			}},
			{EffectID::rorqualSurveyScannerRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[983]},
			}},
			{EffectID::shipCapPropulsionJamming, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[984]},
			}},
			{EffectID::setBonusThukker, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[985]},
			}},
			{EffectID::setBonusSisters, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[986]},
			}},
			{EffectID::setBonusSyndicate, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[987]},
			}},
			{EffectID::miningLaserMaxRangeMultBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[988]},
			}},
			{EffectID::setBonusMordus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[989]},
			}},
			{EffectID::interceptor2WarpScrambleRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[990]},
			}},
			{EffectID::weaponUpgradesCpuNeedBonusPostPercentCpuLocationShipModulesRequiringBombLauncher, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[991]},
			}},
			{EffectID::skillAdvancedWeaponUpgradesPowerNeedBonusBombLaunchers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[992]},
			}},
			{EffectID::skillNaniteOperationRepairCost, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[993]},
			}},
			{EffectID::skillNaniteOperationRepairCostLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[994]},
			}},
			{EffectID::skillNaniteInterfacingRepairTimeLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[995]},
			}},
			{EffectID::cynosuralTheoryConsumptionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[996]},
			}},
			{EffectID::skillConsumptionQuantityBonusPercentageSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[997]},
			}},
			{EffectID::drawbackCapacitorRecharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[998]},
			}},
			{EffectID::eliteBonusBlackOpsAgiliy1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[999]},
			}},
			{EffectID::skillJumpDriveConsumptionAmountBonusPercentage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1000]},
			}},
			{EffectID::gunneryMaxRangeBonus, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[1001]},
			}},
			{EffectID::ewSkillTrackingDisruptionTrackingSpeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1002]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkMaxRangeBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1003]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkMaxRangeBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1004]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkTrackingSpeedBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1005]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkTrackingSpeedBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1006]},
			}},
			{EffectID::ewSkillSignalSuppressionScanResolutionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1007]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerMaxTargetRangeBonusGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1008]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerMaxTargetRangeBonusGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1009]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerScanResolutionBonusGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1010]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerScanResolutionBonusGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1011]},
			}},
			{EffectID::ewSkillSignalSuppressionMaxTargetRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1012]},
			}},
			{EffectID::eliteBonusJumpFreighterHullHP1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1013]},
			}},
			{EffectID::eliteBonusJumpFreighterJumpDriveConsumptionAmount2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1014]},
			}},
			{EffectID::jumpFreightersSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1015]},
			}},
			{EffectID::jumpFreightersSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1016]},
			}},
			{EffectID::scriptSensorBoosterScanResolutionBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1017]},
			}},
			{EffectID::scriptSensorBoosterMaxTargetRangeBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1018]},
			}},
			{EffectID::scriptTrackingComputerTrackingSpeedBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1019]},
			}},
			{EffectID::scriptTrackingComputerMaxRangeBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1020]},
			}},
			{EffectID::scriptWarpDisruptionFieldGeneratorSetDisallowInEmpireSpace, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1021]},
			}},
			{EffectID::scriptDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1022]},
			}},
			{EffectID::scriptWarpDisruptionFieldGeneratorSetScriptCapacitorNeedHidden, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1023]},
			}},
			{EffectID::scriptSignatureRadiusBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1024]},
			}},
			{EffectID::scriptMassBonusPercentageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1025]},
			}},
			{EffectID::scriptSpeedBoostFactorBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1026]},
			}},
			{EffectID::scriptSpeedFactorBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1027]},
			}},
			{EffectID::scriptWarpScrambleRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1028]},
			}},
			{EffectID::eliteBonusViolatorsLargeEnergyTurretDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1029]},
			}},
			{EffectID::ewGroupRsdMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1030]},
			}},
			{EffectID::ewGroupTpMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1031]},
			}},
			{EffectID::ewGroupTdMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1032]},
			}},
			{EffectID::ewGroupEcmBurstMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1033]},
			}},
			{EffectID::gunneryMaxRangeBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1001]},
			}},
			{EffectID::gunneryTrackingSpeedBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[785]},
			}},
			{EffectID::shipScanResolutionBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[232]},
			}},
			{EffectID::shipMaxTargetRangeBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[167]},
			}},
			{EffectID::shipMaxLockedTargetsBonusAddOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[33]},
			}},
			{EffectID::miningLaserRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1034]},
			}},
			{EffectID::frequencyMiningLaserMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1035]},
			}},
			{EffectID::stripMinerMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1036]},
			}},
			{EffectID::gasHarvesterMaxRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1037]},
			}},
			{EffectID::setBonusOre, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1038]},
			}},
			{EffectID::jumpPortalGenerationBO, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},
			}},
			{EffectID::shipBonusLargeEnergyTurretMaxRangeAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1039]},
			}},
			{EffectID::eliteBonusJumpFreighterShieldHP1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1040]},
			}},
			{EffectID::eliteBonusJumpFreighterArmorHP1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1041]},
			}},
			{EffectID::freighterAgilityBonusC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1042]},
			}},
			{EffectID::freighterAgilityBonusM1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1043]},
			}},
			{EffectID::freighterAgilityBonusG1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1044]},
			}},
			{EffectID::freighterAgilityBonusA1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1045]},
			}},
			{EffectID::scriptTrackingComputerFalloffBonusBonus, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1046]},
			}},
			{EffectID::shipMissileLauncherSpeedBonusMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1047]},{modifiers[1048]},{modifiers[1049]},
			}},
			{EffectID::shipHybridTurretROFBonusGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1050]},
			}},
			{EffectID::shipBonusProjectileTrackingMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1051]},
			}},
			{EffectID::skillNaniteInterfacingRepairTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1052]},
			}},
			{EffectID::agilityMultiplierEffectPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[220]},
			}},
			{EffectID::velocityBonusPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[683]},
			}},
			{EffectID::zColinOrcaTractorRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1053]},
			}},
			{EffectID::zColinOrcaTractorVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1054]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1055]},
			}},
			{EffectID::cargoAndOreHoldCapacityBonusICS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1056]},{modifiers[1057]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1058]},
			}},
			{EffectID::miningForemanBurstBonusICS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1059]},{modifiers[1060]},{modifiers[1061]},{modifiers[1062]},{modifiers[1063]},
			}},
			{EffectID::zColinOrcaSurveyScannerBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1064]},
			}},
			{EffectID::eliteIndustrialExtenderSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1065]},
			}},
			{EffectID::zColinSkillTransportCovertCloakMod, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1066]},
			}},
			{EffectID::covertOpsStealthBomberSiegeMissileLauncerPowerNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1067]},
			}},
			{EffectID::interceptorMWDSignatureRadiusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1068]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyMissileExplosionVelocityCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1069]},
			}},
			{EffectID::armorHPBonusAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[783]},
			}},
			{EffectID::subSystem, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::hardPointModifierEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1070]},{modifiers[1071]},
			}},
			{EffectID::slotModifier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1072]},{modifiers[1073]},{modifiers[1074]},
			}},
			{EffectID::powerOutputAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1075]},
			}},
			{EffectID::cpuOutputAddCpuOutputPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1076]},
			}},
			{EffectID::maxVelocityAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1077]},
			}},
			{EffectID::modifyHullResonancePostPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1078]},{modifiers[1079]},{modifiers[1080]},{modifiers[1081]},
			}},
			{EffectID::probeLaunching, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::droneBandwidthAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1082]},
			}},
			{EffectID::droneCapacityAdddroneCapacityPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1083]},
			}},
			{EffectID::scanStrengthAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1084]},{modifiers[1085]},{modifiers[1086]},{modifiers[1087]},
			}},
			{EffectID::maxTargetRangeAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1088]},
			}},
			{EffectID::signatureRadiusAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1089]},
			}},
			{EffectID::scanResolutionAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1090]},
			}},
			{EffectID::capacityAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1091]},
			}},
			{EffectID::capacitorCapacityAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1092]},
			}},
			{EffectID::shieldCapacityAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1093]},
			}},
			{EffectID::subsystemSkillLevelAmarrDefensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1094]},
			}},
			{EffectID::subsystemSkillLevelCaldariDefensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1095]},
			}},
			{EffectID::subsystemSkillLevelGallenteDefensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1096]},
			}},
			{EffectID::subsystemSkillLevelMinmatarDefensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1097]},
			}},
			{EffectID::subsystemSkillLevelMinmatarElectronic, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1098]},
			}},
			{EffectID::subsystemSkillLevelGallenteElectronic, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1099]},
			}},
			{EffectID::subsystemSkillLevelCaldariElectronic, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1100]},
			}},
			{EffectID::subsystemSkillLevelAmarrElectronic, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1101]},
			}},
			{EffectID::subsystemSkillLevelAmarrEngineering, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1102]},
			}},
			{EffectID::subsystemSkillLevelCaldariEngineering, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1103]},
			}},
			{EffectID::subsystemSkillLevelGallenteEngineering, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1104]},
			}},
			{EffectID::subsystemSkillLevelMinmatarEngineering, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1105]},
			}},
			{EffectID::subsystemSkillLevelMinmatarOffensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1106]},
			}},
			{EffectID::subsystemSkillLevelGallenteOffensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1107]},
			}},
			{EffectID::subsystemSkillLevelCaldariOffensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1108]},
			}},
			{EffectID::subsystemSkillLevelAmarrOffensive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1109]},
			}},
			{EffectID::subsystemSkillLevelAmarrPropulsion, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1110]},
			}},
			{EffectID::subsystemSkillLevelCaldariPropulsion, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1111]},
			}},
			{EffectID::subsystemSkillLevelGallentePropulsion, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1112]},
			}},
			{EffectID::subsystemSkillLevelMinmatarPropulsion, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1113]},
			}},
			{EffectID::rechargeRateAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1114]},
			}},
			{EffectID::shieldRechargeRateAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1115]},
			}},
			{EffectID::subsystemBonusAmarrPropulsionMaxVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1116]},
			}},
			{EffectID::subsystemBonusCaldariPropulsionMaxVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1117]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsionMaxVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1118]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsionAfterburnerSpeedFactor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1119]},
			}},
			{EffectID::subsystemBonusCaldariPropulsionAfterburnerSpeedFactor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1120]},
			}},
			{EffectID::subsystemBonusAmarrPropulsionAfterburnerSpeedFactor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1121]},
			}},
			{EffectID::subsystemBonusAmarrPropulsion2Agility, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1122]},
			}},
			{EffectID::subsystemBonusCaldariPropulsion2Agility, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1123]},
			}},
			{EffectID::subsystemBonusGallentePropulsion2Agility, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1124]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsion2Agility, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1125]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsion2MWDPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1126]},
			}},
			{EffectID::subsystemBonusGallentePropulsionMWDPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1127]},
			}},
			{EffectID::subsystemBonusAmarrPropulsion2MWDPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1128]},
			}},
			{EffectID::subsystemBonusGallentePropulsionABMWDCapNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1129]},
			}},
			{EffectID::subsystemBonusGallenteElectronicCPU, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1130]},
			}},
			{EffectID::subsystemBonusCaldariElectronicCPU, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1131]},
			}},
			{EffectID::subsystemBonusMinmatarCoreScanStrengthLADAR, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1132]},
			}},
			{EffectID::subsystemBonusGallenteCoreScanStrengthMagnetometric, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1133]},
			}},
			{EffectID::subsystemBonusCaldariCoreScanStrengthGravimetric, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1134]},
			}},
			{EffectID::subsystemBonusAmarrCoreScanStrengthRADAR, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1135]},
			}},
			{EffectID::subsystemBonusAmarrDefensiveArmorResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1136]},{modifiers[1137]},{modifiers[1138]},{modifiers[1139]},
			}},
			{EffectID::subsystemBonusGallenteDefensiveArmorResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1140]},{modifiers[1141]},{modifiers[1142]},{modifiers[1143]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveArmorResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1144]},{modifiers[1145]},{modifiers[1146]},{modifiers[1147]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveShieldResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1148]},{modifiers[1149]},{modifiers[1150]},{modifiers[1151]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1152]},{modifiers[1153]},{modifiers[1154]},{modifiers[1155]},
			}},
			{EffectID::subsystemBonusAmarrDefensiveArmorRepairAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1156]},
			}},
			{EffectID::subsystemBonusGallenteDefensiveArmorRepairAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1157]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveShieldArmorRepairAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1158]},{modifiers[1159]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldBoostAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1160]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1161]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveShieldArmorHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1162]},{modifiers[1163]},
			}},
			{EffectID::subsystemBonusGallenteDefensiveArmorHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1164]},
			}},
			{EffectID::subsystemBonusAmarrDefensiveArmorHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1165]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveEnergyWeaponDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1166]},
			}},
			{EffectID::subsystemBonusCaldariOffensiveHybridWeaponMaxRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1167]},
			}},
			{EffectID::subsystemBonusGallenteOffensiveHybridWeaponFalloff, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1168]},
			}},
			{EffectID::subsystemBonusGallenteOffensiveHybridWeaponDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1169]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveProjectileWeaponROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1170]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveProjectileWeaponFalloff, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1171]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveProjectileWeaponMaxRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1172]},
			}},
			{EffectID::subsystemBonusCaldariOffensiveHeavyMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1173]},
			}},
			{EffectID::subsystemBonusCaldariOffensiveHeavyAssaultMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1174]},
			}},
			{EffectID::subsystemBonusCaldariOffensive1LauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1173]},{modifiers[1174]},{modifiers[1175]},
			}},
			{EffectID::subsystemBonusAmarrEngineeringHeatDamageReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1176]},
			}},
			{EffectID::subsystemBonusCaldariEngineeringHeatDamageReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1177]},
			}},
			{EffectID::subsystemBonusGallenteEngineeringHeatDamageReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1178]},
			}},
			{EffectID::subsystemBonusMinmatarEngineeringHeatDamageReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1179]},
			}},
			{EffectID::subsystemBonusMinmatarEngineeringCapacitorCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1180]},
			}},
			{EffectID::subsystemBonusCaldariCoreCapacitorCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1181]},
			}},
			{EffectID::subsystemBonusAmarrCoreCapacitorCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1182]},
			}},
			{EffectID::massAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1183]},
			}},
			{EffectID::baseMaxScanDeviationModifierRequiringAstrometrics, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1184]},
			}},
			{EffectID::baseSensorStrengthModifierRequiringAstrometrics, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1185]},
			}},
			{EffectID::shipBonusScanProbeStrengthCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1186]},
			}},
			{EffectID::shipBonusScanProbeStrengthMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1187]},
			}},
			{EffectID::shipBonusScanProbeStrengthGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1188]},
			}},
			{EffectID::eliteBonusCoverOpsScanProbeStrength2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1189]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveEnergyWeaponCapacitorNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1190]},
			}},
			{EffectID::shipBonusStrategicCruiserAmarrHeatDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1191]},
			}},
			{EffectID::shipBonusStrategicCruiserCaldariHeatDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1192]},
			}},
			{EffectID::shipBonusStrategicCruiserGallenteHeatDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1193]},
			}},
			{EffectID::shipBonusStrategicCruiserMinmatarHeatDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1194]},
			}},
			{EffectID::strategicCruiserAmarrSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1195]},
			}},
			{EffectID::strategicCruiserCaldariSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1196]},
			}},
			{EffectID::strategicCruiserGallenteSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1197]},
			}},
			{EffectID::strategicCruiserMinmatarSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1198]},
			}},
			{EffectID::subsystemSkillLevelAmarrDefensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1199]},
			}},
			{EffectID::subsystemSkillLevelCaldariDefensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1200]},
			}},
			{EffectID::subsystemSkillLevelGallenteDefensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1201]},
			}},
			{EffectID::subsystemSkillLevelMinmatarDefensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1202]},
			}},
			{EffectID::subsystemSkillLevelMinmatarElectronic2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1203]},
			}},
			{EffectID::subsystemSkillLevelGallenteElectronic2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1204]},
			}},
			{EffectID::subsystemSkillLevelCaldariElectronic2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1205]},
			}},
			{EffectID::subsystemSkillLevelAmarrElectronic2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1206]},
			}},
			{EffectID::subsystemSkillLevelAmarrEngineering2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1207]},
			}},
			{EffectID::subsystemSkillLevelCaldariEngineering2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1208]},
			}},
			{EffectID::subsystemSkillLevelGallenteEngineering2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1209]},
			}},
			{EffectID::subsystemSkillLevelMinmatarEngineering2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1210]},
			}},
			{EffectID::subsystemSkillLevelMinmatarOffensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1211]},
			}},
			{EffectID::subsystemSkillLevelGallenteOffensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1212]},
			}},
			{EffectID::subsystemSkillLevelCaldariOffensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1213]},
			}},
			{EffectID::subsystemSkillLevelAmarrOffensive2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1214]},
			}},
			{EffectID::subsystemSkillLevelAmarrPropulsion2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1215]},
			}},
			{EffectID::subsystemSkillLevelCaldariPropulsion2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1216]},
			}},
			{EffectID::subsystemSkillLevelGallentePropulsion2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1217]},
			}},
			{EffectID::subsystemSkillLevelMinmatarPropulsion2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1218]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2EnergyWeaponCapacitorNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1219]},
			}},
			{EffectID::subsystemBonusAmarrCore2EnergyVampireAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1220]},
			}},
			{EffectID::subsystemBonusAmarrCore2EnergyDestabilizerAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1221]},
			}},
			{EffectID::modifyArmorResonancePassivePreAssignment, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1222]},{modifiers[1223]},{modifiers[1224]},{modifiers[1225]},
			}},
			{EffectID::modifyShieldResonancePassivePreAssignment, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1226]},{modifiers[1227]},{modifiers[1228]},{modifiers[1229]},
			}},
			{EffectID::subsystemBonusCaldariOffensive2MissileLauncherKineticDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1230]},{modifiers[1231]},{modifiers[1232]},
			}},
			{EffectID::subsystemBonusGallenteOffensiveDroneDamageHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1233]},{modifiers[1234]},{modifiers[1235]},{modifiers[1236]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2ProjectileWeaponDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1237]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2ProjectileWeaponROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1238]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2MissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1239]},{modifiers[1240]},{modifiers[1241]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveAssaultMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1242]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveHeavyMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1243]},
			}},
			{EffectID::subsystemBonusMinmatarOffensiveHeavyAssaultMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1244]},
			}},
			{EffectID::subsystemBonusAmarrEngineeringPowerOutput, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1245]},
			}},
			{EffectID::subsystemBonusCaldariEngineeringPowerOutput, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1246]},
			}},
			{EffectID::subsystemBonusGallenteEngineeringPowerOutput, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1247]},
			}},
			{EffectID::subsystemBonusMinmatarEngineeringPowerOutput, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1248]},
			}},
			{EffectID::subsystemBonusMinmatarCoreCapacitorRecharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1249]},
			}},
			{EffectID::subsystemBonusGallenteCoreCapacitorRecharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1250]},
			}},
			{EffectID::subsystemBonusCaldariEngineeringCapacitorRecharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1251]},
			}},
			{EffectID::subsystemBonusAmarrEngineeringCapacitorRecharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1252]},
			}},
			{EffectID::subsystemBonusAmarrCore3ScanResolution, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1253]},
			}},
			{EffectID::subsystemBonusMinmatarCore3ScanResolution, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1254]},
			}},
			{EffectID::subsystemBonusCaldariCore2MaxTargetingRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1255]},
			}},
			{EffectID::subsystemBonusGallenteCore2MaxTargetingRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1256]},
			}},
			{EffectID::subsystemBonusGallenteCore2WarpScrambleRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1257]},
			}},
			{EffectID::subsystemBonusMinmatarCore2StasisWebifierRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1258]},
			}},
			{EffectID::subsystemBonusCaldariPropulsion2WarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1259]},
			}},
			{EffectID::subsystemBonusGallentePropulsionWarpCapacitor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1260]},
			}},
			{EffectID::subsystemBonusGallentePropulsion2WarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1261]},
			}},
			{EffectID::modifyShipAgilityPassivePreAssignment, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1262]},
			}},
			{EffectID::subsystemBonusGallenteOffensive2HybridWeaponDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1263]},
			}},
			{EffectID::subsystemBonusCaldariOffensive2HybridWeaponDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1264]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2RemoteArmorRepairCapUse, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1265]},
			}},
			{EffectID::subsystemBonusGallenteOffensive2RemoteArmorRepairCapUse, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1266]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive2RemoteRepCapUse, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1267]},{modifiers[1268]},
			}},
			{EffectID::subsystemBonusCaldariOffensive2RemoteShieldBoosterCapUse, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1269]},
			}},
			{EffectID::subsystemBonusGallenteEngineeringDroneHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1270]},{modifiers[1271]},{modifiers[1272]},
			}},
			{EffectID::subsystemBonusGallenteEngineering2DroneMWD, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1273]},
			}},
			{EffectID::subsystemBonusCaldariCore2ECMStrengthRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1274]},{modifiers[1275]},{modifiers[1276]},{modifiers[1277]},{modifiers[1278]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveDroneDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1279]},
			}},
			{EffectID::subsystemBonusAmarrOffensive3DroneDamageHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1280]},{modifiers[1281]},{modifiers[1282]},{modifiers[1283]},
			}},
			{EffectID::subsystemBonusGallenteOffensive3DroneDamageMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1284]},
			}},
			{EffectID::subsystemBonusAmarrOffensive3EnergyWeaponMaxRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1285]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3HMLHAMVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1286]},{modifiers[1287]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3HeavyMissileVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1287]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthGrav, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1288]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthLadar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1289]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthMagn, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1290]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3EwStrengthRadar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1291]},
			}},
			{EffectID::subsystemSkillLevelAmarrOffensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1292]},
			}},
			{EffectID::subsystemSkillLevelCaldariOffensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1293]},
			}},
			{EffectID::subsystemSkillLevelGallenteOffensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1294]},
			}},
			{EffectID::subsystemBonusMinmatarCore2MaxTargetingRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1295]},
			}},
			{EffectID::subsystemBonusAmarrCore2MaxTargetingRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1296]},
			}},
			{EffectID::subsystemBonusMinmatarDefensiveSignatureRadius, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1297]},
			}},
			{EffectID::subsystemBonusGallenteOffensive3TurretTracking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1298]},
			}},
			{EffectID::subsystemSkillLevelMinmatarOffensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1299]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive3TurretTracking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1300]},
			}},
			{EffectID::caldariCruiserSkillLevelPreMulShipBonusCC3Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1301]},
			}},
			{EffectID::ecmRangeBonusModuleEffect, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1302]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveHeavyMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1303]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1303]},{modifiers[1304]},{modifiers[1305]},
			}},
			{EffectID::subsystemBonusAmarrOffensiveHeavyAssaultMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1305]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2MissileDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1306]},{modifiers[1307]},{modifiers[1308]},{modifiers[1309]},{modifiers[1310]},{modifiers[1311]},{modifiers[1312]},{modifiers[1313]},{modifiers[1314]},{modifiers[1315]},{modifiers[1316]},{modifiers[1317]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2HAMThermalDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1318]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2HAMKineticDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1319]},
			}},
			{EffectID::subsystemBonusAmarrOffensive2HAMExplosiveDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1320]},
			}},
			{EffectID::shipBonusMediumHybridDmgCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1321]},
			}},
			{EffectID::subsystemBonusWarpBubbleImmune, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1322]},
			}},
			{EffectID::caldariShipEwFalloffRangeCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1323]},
			}},
			{EffectID::caldariShipEwFalloffRangeCB3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1324]},
			}},
			{EffectID::subSystemBonusAmarrOffensiveCommandBursts, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1325]},{modifiers[1326]},{modifiers[1327]},{modifiers[1328]},{modifiers[1329]},{modifiers[1330]},{modifiers[1331]},{modifiers[1332]},{modifiers[1333]},{modifiers[1334]},{modifiers[1335]},{modifiers[1336]},{modifiers[1337]},{modifiers[1338]},{modifiers[1339]},
			}},
			{EffectID::subSystemBonusCaldariDefensiveSiegeWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1340]},{modifiers[1341]},{modifiers[1342]},{modifiers[1343]},{modifiers[1344]},
			}},
			{EffectID::subSystemBonusGallenteDefensiveInformationWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1345]},{modifiers[1346]},{modifiers[1347]},{modifiers[1348]},{modifiers[1349]},
			}},
			{EffectID::subSystemBonusMinmatarDefensiveSkirmishWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1350]},{modifiers[1351]},{modifiers[1352]},{modifiers[1353]},{modifiers[1354]},
			}},
			{EffectID::shipBonusTorpedoVelocityGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1355]},
			}},
			{EffectID::shipBonusTorpedoVelocityMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1356]},
			}},
			{EffectID::shipBonusTorpedoVelocity2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1357]},
			}},
			{EffectID::shipBonusTorpedoVelocityCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1358]},
			}},
			{EffectID::eliteReconBonusHeavyMissileVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1359]},
			}},
			{EffectID::eliteReconBonusHeavyAssaultMissileVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1360]},
			}},
			{EffectID::subSystemBonusAmarrElectronicScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1361]},
			}},
			{EffectID::subSystemBonusCaldariElectronicScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1362]},
			}},
			{EffectID::subSystemBonusGallenteElectronicScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1363]},
			}},
			{EffectID::subSystemBonusMinmatarElectronicScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1364]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoThermalDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1365]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoEMDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1366]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoExplosiveDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1367]},
			}},
			{EffectID::shipBonusEliteCover2TorpedoKineticDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1368]},
			}},
			{EffectID::shipBonusGFTorpedoExplosionVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1369]},
			}},
			{EffectID::shipBonusMF1TorpedoExplosionVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1370]},
			}},
			{EffectID::shipBonusCF1TorpedoExplosionVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1371]},
			}},
			{EffectID::shipBonusAF1TorpedoExplosionVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1372]},
			}},
			{EffectID::subSystemBonusAmarrElectronic2TractorBeamVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1373]},
			}},
			{EffectID::subSystemBonusCaldariElectronic2TractorBeamVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1374]},
			}},
			{EffectID::subSystemBonusGallenteElectronic2TractorBeamVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1375]},
			}},
			{EffectID::subSystemBonusMinmatarElectronic2TractorBeamVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1376]},
			}},
			{EffectID::subSystemBonusMinmatarElectronic2TractorBeamRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1377]},
			}},
			{EffectID::subSystemBonusGallenteElectronic2TractorBeamRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1378]},
			}},
			{EffectID::subSystemBonusCaldariElectronic2TractorBeamRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1379]},
			}},
			{EffectID::subSystemBonusAmarrElectronic2TractorBeamRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1380]},
			}},
			{EffectID::signatureRadiusPreAssignment, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1381]},
			}},
			{EffectID::subsystemBonusScanProbeLauncherCPU, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1382]},
			}},
			{EffectID::subsystemBonusJumpHarmonics, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1383]},
			}},
			{EffectID::shipBonusGF1TorpedoFlightTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1384]},
			}},
			{EffectID::shipBonusMF1TorpedoFlightTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1385]},
			}},
			{EffectID::shipBonusCF1TorpedoFlightTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1386]},
			}},
			{EffectID::shipBonusAF1TorpedoFlightTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1387]},
			}},
			{EffectID::scanRadarStrengthModifierEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1388]},
			}},
			{EffectID::scanLadarStrengthModifierEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1389]},
			}},
			{EffectID::scanGravimetricStrengthModifierEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1390]},
			}},
			{EffectID::scanMagnetometricStrengthModifierEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1391]},
			}},
			{EffectID::federationsetbonus3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1392]},
			}},
			{EffectID::imperialsetbonus3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1393]},
			}},
			{EffectID::republicsetbonus3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1394]},
			}},
			{EffectID::caldarisetbonus3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1395]},
			}},
			{EffectID::imperialsetLGbonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1396]},
			}},
			{EffectID::federationsetLGbonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1397]},
			}},
			{EffectID::caldarisetLGbonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1398]},
			}},
			{EffectID::republicsetLGbonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1399]},
			}},
			{EffectID::shipBonusStasisMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1400]},
			}},
			{EffectID::shipProjectileDmgMC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1401]},
			}},
			{EffectID::shipVelocityBonusATC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1402]},
			}},
			{EffectID::shipMTMaxRangeBonusATC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1403]},
			}},
			{EffectID::shipMTFalloffBonusATC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1404]},
			}},
			{EffectID::shipMTFalloffBonusATF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1405]},
			}},
			{EffectID::shipMTMaxRangeBonusATF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1406]},
			}},
			{EffectID::shipBonusAfterburnerCapNeedATF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1407]},
			}},
			{EffectID::shipBonusSurveyProbeExplosionDelaySkillSurveyCovertOps3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1408]},
			}},
			{EffectID::covertOpsSkillLevelPreMulEliteBonusCoverOpsShip3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1409]},
			}},
			{EffectID::shipETOptimalRange2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1410]},
			}},
			{EffectID::shipPTurretFalloffBonusGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1411]},
			}},
			{EffectID::shipBonusStasisWebSpeedFactorMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1412]},
			}},
			{EffectID::superWeaponAmarr, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::superWeaponCaldari, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::superWeaponGallente, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::superWeaponMinmatar, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::shipStasisWebStrengthBonusMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1413]},
			}},
			{EffectID::shipPTurretFalloffBonusGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1414]},
			}},
			{EffectID::shipStasisWebStrengthBonusMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1415]},
			}},
			{EffectID::shipFalloffBonusMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1416]},
			}},
			{EffectID::shipHTurretFalloffBonusGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1417]},
			}},
			{EffectID::gunneryFalloffBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[92]},
			}},
			{EffectID::tcapitalLauncherSkillCruiseCitadelEmDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1418]},
			}},
			{EffectID::capitalLauncherSkillCruiseCitadelExplosiveDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1419]},
			}},
			{EffectID::capitalLauncherSkillCruiseCitadelKineticDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1420]},
			}},
			{EffectID::capitalLauncherSkillCruiseCitadelThermalDamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1421]},
			}},
			{EffectID::gunneryMaxRangeFalloffTrackingSpeedBonus, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[92]},{modifiers[785]},{modifiers[1001]},
			}},
			{EffectID::industrialCoreEffect2, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[1422]},{modifiers[1423]},{modifiers[1424]},{modifiers[1425]},{modifiers[1426]},{modifiers[1427]},{modifiers[1428]},{modifiers[1429]},{modifiers[1430]},{modifiers[1431]},{modifiers[1432]},{modifiers[1433]},{modifiers[1434]},{modifiers[1435]},{modifiers[1436]},{modifiers[1437]},{modifiers[1438]},{modifiers[1439]},{modifiers[1440]},{modifiers[1441]},{modifiers[1442]},{modifiers[1443]},{modifiers[1444]},{modifiers[1445]},{modifiers[1446]},{modifiers[1447]},{modifiers[1448]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkFalloffBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1449]},
			}},
			{EffectID::eliteBonusLogisticsTrackingLinkFalloffBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1450]},
			}},
			{EffectID::droneRigStasisWebSpeedFactorBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1451]},
			}},
			{EffectID::amarrFrigateSkillLevelPreMulShipBonus3AFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1452]},
			}},
			{EffectID::caldariFrigateSkillLevelPreMulShipBonus3CFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1453]},
			}},
			{EffectID::gallenteFrigateSkillLevelPreMulShipBonus3GFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1454]},
			}},
			{EffectID::minmatarFrigateSkillLevelPreMulShipBonus3MFShip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1455]},
			}},
			{EffectID::shipBonusDroneDamageGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1456]},
			}},
			{EffectID::shipBonusWarpScramblerMaxRangeGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1457]},
			}},
			{EffectID::shipBonusHeatDamageATF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1458]},
			}},
			{EffectID::shipBonusSmallHybridMaxRangeATF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1459]},
			}},
			{EffectID::shipBonusSmallHybridTrackingSpeedATF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1460]},
			}},
			{EffectID::shipBonusHybridTrackingATC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1461]},
			}},
			{EffectID::shipBonusHybridFalloffATC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1462]},
			}},
			{EffectID::shipBonusWarpScramblerMaxRangeGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1463]},
			}},
			{EffectID::eliteBonusMaraudersCruiseAndTorpedoDamageRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1464]},{modifiers[1465]},{modifiers[1466]},{modifiers[1467]},{modifiers[1468]},{modifiers[1469]},{modifiers[1470]},{modifiers[1471]},
			}},
			{EffectID::shipBonusAoeVelocityCruiseAndTorpedoCB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1472]},{modifiers[1473]},
			}},
			{EffectID::shipCruiseAndTorpedoVelocityBonusCB3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[277]},{modifiers[278]},
			}},
			{EffectID::shipArmorEMAndExpAndkinAndThmResistanceAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[293]},{modifiers[294]},{modifiers[295]},{modifiers[296]},
			}},
			{EffectID::shipHeavyAssaultMissileEMAndExpAndKinAndThmDmgAC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1474]},{modifiers[1475]},{modifiers[1476]},{modifiers[1477]},
			}},
			{EffectID::eliteBonusHeavyGunshipHeavyAndHeavyAssaultAndAssaultMissileLauncherROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[719]},{modifiers[720]},{modifiers[721]},
			}},
			{EffectID::eliteBonusBlackOpsECMGravAndLadarAndMagnetometricAndRadarStrength1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1478]},{modifiers[1479]},{modifiers[1480]},{modifiers[1481]},
			}},
			{EffectID::shipCruiseAndSiegeLauncherROFBonus2CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[555]},{modifiers[556]},
			}},
			{EffectID::oreIndustrialSkillLevelPostMulShipBonusOreIndustrial1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1482]},
			}},
			{EffectID::oreIndustrialSkillLevelPostMulShipBonusOreIndustrial2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1483]},
			}},
			{EffectID::shipBonusNoctisSalvageCycle, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1484]},
			}},
			{EffectID::shipBonusNoctisTractorCycle, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1485]},
			}},
			{EffectID::shipBonusNoctisTractorVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1486]},
			}},
			{EffectID::shipBonusNoctisTractorRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1487]},
			}},
			{EffectID::subsystemBonusCaldariPropulsionWarpCapacitor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1488]},
			}},
			{EffectID::hackOrbital, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::shipEnergyNeutralizerTransferAmountBonusAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1489]},
			}},
			{EffectID::shipBonusSmallEnergyWeaponOptimalRangeATF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1490]},
			}},
			{EffectID::shipBonusSmallEnergyTurretDamageATF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1491]},
			}},
			{EffectID::shipBonusMissileLauncherHeavyROFATC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1492]},
			}},
			{EffectID::shipBonusMissileLauncherAssaultROFATC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1493]},
			}},
			{EffectID::shipBonusMissileLauncherHeavyAssaultROFATC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1494]},
			}},
			{EffectID::eliteBonusBlackOpsECMBurstGravAndLadarAndMagnetoAndRadar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1495]},{modifiers[1496]},{modifiers[1497]},{modifiers[1498]},
			}},
			{EffectID::salvagingAccessDifficultyBonusMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1499]},
			}},
			{EffectID::hackingAccessDifficultyBonusMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1500]},
			}},
			{EffectID::archaeologyAccessDifficultyBonusMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1501]},
			}},
			{EffectID::dataMiningSkillBoostAccessDifficultyBonusAbsolutePercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1502]},
			}},
			{EffectID::ecmGravimetricStrengthBonusPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1503]},
			}},
			{EffectID::ecmLadarStrengthBonusPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1504]},
			}},
			{EffectID::ecmMagnetometricStrengthBonusPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1505]},
			}},
			{EffectID::ecmRadarStrengthBonusPercent, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1506]},
			}},
			{EffectID::skillConsumptionQuantityBonusPercentSkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1507]},
			}},
			{EffectID::jumpPortalConsumptionBonusPercentSkill, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1508]},
			}},
			{EffectID::salvagerModuleDurationReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1509]},
			}},
			{EffectID::bcLargeEnergyTurretPowerNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1510]},
			}},
			{EffectID::bcLargeHybridTurretPowerNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1511]},
			}},
			{EffectID::bcLargeProjectileTurretPowerNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1512]},
			}},
			{EffectID::bcLargeEnergyTurretCPUNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1513]},
			}},
			{EffectID::bcLargeHybridTurretCPUNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1514]},
			}},
			{EffectID::bcLargeProjectileTurretCPUNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1515]},
			}},
			{EffectID::bcLargeEnergyTurretCapacitorNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1516]},
			}},
			{EffectID::bcLargeHybridTurretCapacitorNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1517]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC3Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1518]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusBC4Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1519]},
			}},
			{EffectID::setBonusChristmasPowergrid, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1520]},
			}},
			{EffectID::setBonusChristmasCapacitorCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1521]},
			}},
			{EffectID::setBonusChristmasCPUOutput, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1522]},
			}},
			{EffectID::setBonusChristmasCapacitorRecharge2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1523]},
			}},
			{EffectID::maxRangeHiddenPreAssignmentWarpScrambleRange, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1524]},
			}},
			{EffectID::shipBonusDroneHitpointsGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1525]},
			}},
			{EffectID::shipBonusDroneArmorHitpointsGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1526]},
			}},
			{EffectID::shipBonusDroneShieldHitpointsGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1527]},
			}},
			{EffectID::shipSETTrackingBonusAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1528]},
			}},
			{EffectID::shipMissileSpeedBonusAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1529]},
			}},
			{EffectID::MWDSignatureRadiusRoleBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1530]},
			}},
			{EffectID::modifyShieldArmorHullResonancePostPercent, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},{modifiers[1078]},{modifiers[1079]},{modifiers[1080]},{modifiers[1081]},
			}},
			{EffectID::setWeaponSpeedToValue, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1531]},
			}},
			{EffectID::modifyShieldRechargeRatePassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[11]},
			}},
			{EffectID::damageMultiplierMultiplierActivation, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[1532]},
			}},
			{EffectID::missileDamageMultiplier, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1533]},
			}},
			{EffectID::setMassAndAgilityAndSpeed, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[1534]},{modifiers[1535]},{modifiers[1536]},
			}},
			{EffectID::microJumpDrive, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::skillMJDdurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1537]},
			}},
			{EffectID::adaptiveArmorHardener, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[1538]},{modifiers[1539]},{modifiers[1540]},{modifiers[1541]},
			}},
			{EffectID::scriptConsumptionQuantityBonus, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1542]},
			}},
			{EffectID::shipSETDmgBonus2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1543]},
			}},
			{EffectID::shipArmorRepairingGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1544]},
			}},
			{EffectID::fueledShieldBoosting, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[0]},
			}},
			{EffectID::shipHybridDamageBonusCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1545]},
			}},
			{EffectID::targetBreaker, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::skillTargetBreakerDurationBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1546]},
			}},
			{EffectID::skillTargetBreakerCapNeedBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1547]},
			}},
			{EffectID::shipBonusShieldBoosterMB1a, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1548]},
			}},
			{EffectID::shieldBoostAmplifierPassiveBooster, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[431]},{modifiers[523]},
			}},
			{EffectID::shieldBoosterDurationBonusShieldSkills, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1549]},{modifiers[1550]},
			}},
			{EffectID::boosterShieldBoostAmountPenaltyShieldSkills, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1551]},{modifiers[1552]},
			}},
			{EffectID::eliteBonusAssaultShipLightMissileROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1553]},
			}},
			{EffectID::eliteBonusAssaultShipRocketROF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1554]},
			}},
			{EffectID::eliteBonusMarauderShieldBonus2a, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1555]},
			}},
			{EffectID::shipBonusMissileKineticlATF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1556]},
			}},
			{EffectID::skillReactiveArmorHardenerDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1557]},{modifiers[1558]},
			}},
			{EffectID::skillWarAllyCostModifier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1559]},
			}},
			{EffectID::relationsAllyCostSkillBoost, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1560]},
			}},
			{EffectID::missileSkillAoeCloudSizeBonusAllIncludingCapitals, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[453]},
			}},
			{EffectID::shipEnergyTCapNeedBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1561]},
			}},
			{EffectID::shipSETDmgBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1562]},
			}},
			{EffectID::shipArmorEMResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1563]},
			}},
			{EffectID::shipArmorEXResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1564]},
			}},
			{EffectID::shipArmorKNResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1565]},
			}},
			{EffectID::shipArmorTHResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1566]},
			}},
			{EffectID::shipHybridRangeBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1567]},
			}},
			{EffectID::shipMissileKineticDamageRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1568]},
			}},
			{EffectID::shipShieldEMResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1569]},
			}},
			{EffectID::shipShieldExplosiveResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1570]},
			}},
			{EffectID::shipShieldKineticResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1571]},
			}},
			{EffectID::shipShieldThermalResistanceRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1572]},
			}},
			{EffectID::shipSHTDmgBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1573]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1574]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerMaxTargetRangeBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1575]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerScanResolutionBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1576]},
			}},
			{EffectID::shipArmorRepairingRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1577]},
			}},
			{EffectID::shipVelocityBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1578]},
			}},
			{EffectID::minmatarShipEwTargetPainterRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1579]},
			}},
			{EffectID::shipSPTDmgBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1580]},
			}},
			{EffectID::shipShieldBoostRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1581]},
			}},
			{EffectID::shipECMScanStrengthBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1582]},{modifiers[1583]},{modifiers[1584]},{modifiers[1585]},
			}},
			{EffectID::shipBonusDroneMiningAmountRole, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1586]},
			}},
			{EffectID::shipBonusMiningDroneAmountPercentRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1587]},
			}},
			{EffectID::shipBonusDroneHitpointsRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1588]},{modifiers[1589]},{modifiers[1590]},
			}},
			{EffectID::shipBonusSalvageCycleAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1591]},
			}},
			{EffectID::shipBonusSalvageCycleCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1592]},
			}},
			{EffectID::shipBonusSalvageCycleGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1593]},
			}},
			{EffectID::shipBonusSalvageCycleMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1594]},
			}},
			{EffectID::baseDefenderAllyCostCharAssignment, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1595]},
			}},
			{EffectID::iceHarvesterDurationMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1596]},
			}},
			{EffectID::iceHarvesterCapacitorNeedMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1597]},
			}},
			{EffectID::miningYieldMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1598]},
			}},
			{EffectID::shipBonusIceHarvesterDurationORE3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1599]},
			}},
			{EffectID::shipBonusTargetPainterOptimalMF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1600]},
			}},
			{EffectID::shipBonusOreHoldORE2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1601]},
			}},
			{EffectID::shipBonusShieldCapacityORE2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1602]},
			}},
			{EffectID::mercoxitCrystalBonus, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1603]},
			}},
			{EffectID::shipMissileKineticDamageCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1604]},
			}},
			{EffectID::shipMissileVelocityCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1605]},
			}},
			{EffectID::maxTargetingRangeBonusPostPercentPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[167]},
			}},
			{EffectID::shipBonusDroneHitpointsGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1606]},{modifiers[1607]},{modifiers[1608]},
			}},
			{EffectID::shipShieldBoostMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1609]},
			}},
			{EffectID::shipBonusShieldTransferCapNeedCF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1610]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1611]},
			}},
			{EffectID::shipBonusShieldTransferCapNeedMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1612]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1613]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1614]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmountGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1615]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedAF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1616]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmount2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1617]},
			}},
			{EffectID::shipBonusDroneTrackingGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1618]},
			}},
			{EffectID::shipBonusScanProbeStrength2AF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1619]},
			}},
			{EffectID::energyTransferArrayTransferAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1620]},
			}},
			{EffectID::shipBonusShieldTransferCapneedMC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1621]},
			}},
			{EffectID::shipBonusRemoteArmorRepairCapNeedAC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1622]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmountAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1623]},
			}},
			{EffectID::shipBonusRemoteArmorRepairAmountGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1624]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1625]},
			}},
			{EffectID::shipBonusShieldTransferBoostAmountMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1626]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerOptimalBonusGC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1627]},
			}},
			{EffectID::minmatarShipEwTargetPainterMC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1628]},
			}},
			{EffectID::shipMissileRofCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1629]},{modifiers[1630]},{modifiers[1631]},
			}},
			{EffectID::shipPTurretFalloffBonusMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1632]},
			}},
			{EffectID::shipHTDamageBonusCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1633]},
			}},
			{EffectID::shipMETCDamageBonusAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1634]},
			}},
			{EffectID::miningFrigateSkillLevelPostMulShipBonusORE1frig, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1635]},
			}},
			{EffectID::miningFrigateSkillLevelPostMulShipBonusORE2frig, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1636]},
			}},
			{EffectID::shipMiningBonusOREfrig1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1637]},
			}},
			{EffectID::GCHYieldMultiplyPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1638]},
			}},
			{EffectID::shipMissileVelocityPirateFactionRocket, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1639]},
			}},
			{EffectID::shipGCHYieldBonusOREfrig2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1640]},
			}},
			{EffectID::skillReactiveArmorHardenerCapNeedBonus, MetaInfo::Effect::Category::generic, true, true, {
				{modifiers[1641]},{modifiers[1642]},
			}},
			{EffectID::salvageDroneEffect, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::shipBonusDroneMWDboostrole, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1643]},
			}},
			{EffectID::droneSalvageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1644]},
			}},
			{EffectID::droneSalvageSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1645]},
			}},
			{EffectID::sensorIntegritySkillLevelPreMulSensorStrengthBonusSelf, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1646]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusGravimetric, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1647]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusLadar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1648]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusMagnetometric, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1649]},
			}},
			{EffectID::sensorCompensationSensorStrengthBonusRadar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1650]},
			}},
			{EffectID::shipEnergyVampireAmountBonusFixedAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1651]},
			}},
			{EffectID::shipBonusEwRemoteSensorDampenerFalloffBonusGC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1652]},
			}},
			{EffectID::trackingSpeedBonusEffectHybrids, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1653]},
			}},
			{EffectID::trackingSpeedBonusEffectLasers, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1654]},
			}},
			{EffectID::trackingSpeedBonusEffectProjectiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1655]},
			}},
			{EffectID::spaceAnchorEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1656]},
			}},
			{EffectID::armorUpgradesSkillBoostMassPenaltyReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1657]},
			}},
			{EffectID::armorUpgradesMassPenaltyReductionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1658]},
			}},
			{EffectID::shipSETTrackingBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1659]},
			}},
			{EffectID::shipSETOptimalBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1660]},
			}},
			{EffectID::shipNOSTransferAmountBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1661]},
			}},
			{EffectID::shipNeutDestabilizationAmountBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1662]},
			}},
			{EffectID::shipWebVelocityBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1663]},
			}},
			{EffectID::shipDroneMWDSpeedBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1664]},
			}},
			{EffectID::shipRocketMaxVelocityBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1665]},
			}},
			{EffectID::shipLightMissileMaxVelocityBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1666]},
			}},
			{EffectID::shipSHTTrackingSpeedBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1667]},
			}},
			{EffectID::shipSHTFalloffBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1668]},
			}},
			{EffectID::shipSPTTrackingSpeedBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1669]},
			}},
			{EffectID::shipSPTFalloffBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1670]},
			}},
			{EffectID::shipSPTOptimalRangeBonusRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1671]},
			}},
			{EffectID::shipProjectileDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1672]},
			}},
			{EffectID::shipHeavyAssaultMissileEMDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1673]},
			}},
			{EffectID::shipHeavyAssaultMissileKinDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1674]},
			}},
			{EffectID::shipHeavyAssaultMissileThermDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1675]},
			}},
			{EffectID::shipHeavyAssaultMissileExpDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1676]},
			}},
			{EffectID::shipHeavyMissileEMDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1677]},
			}},
			{EffectID::shipHeavyMissileExpDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1678]},
			}},
			{EffectID::shipHeavyMissileKinDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1679]},
			}},
			{EffectID::shipHeavyMissileThermDmgPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1680]},
			}},
			{EffectID::shipScanProbeStrengthBonusPirateCruiser, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1681]},
			}},
			{EffectID::modifyActiveShieldResonancePostPercent, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::modifyActiveArmorResonancePostPercent, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::shipSmallMissileExpDmgCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1682]},{modifiers[1683]},
			}},
			{EffectID::shipSmallMissileKinDmgCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1684]},{modifiers[1685]},
			}},
			{EffectID::shipSmallMissileThermDmgCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1686]},{modifiers[1687]},
			}},
			{EffectID::shipSmallMissileEMDmgCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1688]},{modifiers[1689]},
			}},
			{EffectID::reconShipCloakCpuBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1690]},
			}},
			{EffectID::covertOpsCloakCpuPercentBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1691]},
			}},
			{EffectID::covertCloakCPUAddition, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1692]},
			}},
			{EffectID::covertOpsCloakCpuPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1693]},
			}},
			{EffectID::covertCynoCpuPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1694]},
			}},
			{EffectID::warfareLinkCPUAddition, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1695]},
			}},
			{EffectID::warfareLinkCpuPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1696]},
			}},
			{EffectID::blockadeRunnerCloakCpuPercentBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1697]},
			}},
			{EffectID::drawbackRepairSystemsPGNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1698]},
			}},
			{EffectID::drawbackCapRepPGNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1699]},
			}},
			{EffectID::fueledArmorRepair, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[7]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusAD1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1700]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusAD2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1701]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusCD1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1702]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusCD2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1703]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusGD1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1704]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusGD2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1705]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusMD1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1706]},
			}},
			{EffectID::destroyerSkillLevelPreMulShipBonusMD2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1707]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusABC1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1708]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusABC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1709]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusCBC1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1710]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusCBC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1711]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusGBC1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1712]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusGBC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1713]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusMBC1Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1714]},
			}},
			{EffectID::battlecruiserSkillLevelPreMulShipBonusMBC2Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1715]},
			}},
			{EffectID::shipLaserCapNeed2AD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1716]},
			}},
			{EffectID::shipLaserTracking2AD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1717]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierAD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1718]},
			}},
			{EffectID::shipBonusDroneHitpointsAD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1719]},{modifiers[1720]},{modifiers[1721]},
			}},
			{EffectID::shipHybridRange1CD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1722]},
			}},
			{EffectID::shipHybridTrackingCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1723]},
			}},
			{EffectID::shipBonusFrigateSizedMissileKineticDamageCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1724]},
			}},
			{EffectID::shipRocketKineticDmgCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1725]},
			}},
			{EffectID::shipBonusAoeVelocityRocketsCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1726]},
			}},
			{EffectID::shipBonusAoeVelocityStandardMissilesCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1727]},
			}},
			{EffectID::shipHybridFallOff1GD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1728]},
			}},
			{EffectID::shipHybridTracking1GD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1729]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1730]},
			}},
			{EffectID::shipBonusDroneHitpointsGD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1731]},{modifiers[1732]},{modifiers[1733]},
			}},
			{EffectID::shipProjectileDamageMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1734]},
			}},
			{EffectID::shipProjectileTracking1MD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1735]},
			}},
			{EffectID::shipBonusFrigateSizedLightMissileExplosiveDamageMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1736]},
			}},
			{EffectID::shipRocketExplosiveDmgMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1737]},
			}},
			{EffectID::shipBonusMWDSignatureRadiusMD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1738]},
			}},
			{EffectID::shipArmorEMResistance1ABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1739]},
			}},
			{EffectID::shipArmorExplosiveResistance1ABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1740]},
			}},
			{EffectID::shipArmorKineticResistance1ABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1741]},
			}},
			{EffectID::shipArmorThermResistance1ABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1742]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1743]},
			}},
			{EffectID::shipBonusDroneHitpointsABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1744]},{modifiers[1745]},{modifiers[1746]},
			}},
			{EffectID::shipLaserCapABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1747]},
			}},
			{EffectID::shipLaserDamageBonusABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1748]},
			}},
			{EffectID::shipHybridOptimal1CBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1749]},
			}},
			{EffectID::shipShieldEmResistance1CBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1750]},
			}},
			{EffectID::shipShieldExplosiveResistance1CBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1751]},
			}},
			{EffectID::shipShieldKineticResistance1CBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1752]},
			}},
			{EffectID::shipShieldThermalResistance1CBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1753]},
			}},
			{EffectID::shipBonusHeavyAssaultMissileKineticDamageCBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1754]},
			}},
			{EffectID::shipBonusHeavyMissileKineticDamageCBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1755]},
			}},
			{EffectID::shipHybridDmg1GBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1756]},
			}},
			{EffectID::shipArmorRepairing1GBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1757]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierGBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1758]},
			}},
			{EffectID::shipBonusDroneHitpointsGBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1759]},{modifiers[1760]},{modifiers[1761]},
			}},
			{EffectID::shipBonusHeavyMissileLauncherRofMBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1762]},
			}},
			{EffectID::shipBonusHeavyAssaultMissileLauncherRofMBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1763]},
			}},
			{EffectID::shipShieldBoost1MBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1764]},
			}},
			{EffectID::shipBonusProjectileDamageMBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1765]},
			}},
			{EffectID::shipProjectileRof1MBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1766]},
			}},
			{EffectID::shipLargeLaserCapABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1767]},
			}},
			{EffectID::shipLargeLaserDamageBonusABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1768]},
			}},
			{EffectID::shipHybridRangeBonusCBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1769]},
			}},
			{EffectID::shipHybridDamageBonusCBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1770]},
			}},
			{EffectID::shipLargeHybridTrackingBonusGBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1771]},
			}},
			{EffectID::shipHybridDamageBonusGBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1772]},
			}},
			{EffectID::shipProjectileRofBonusMBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1773]},
			}},
			{EffectID::shipProjectileFalloffBonusMBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1774]},
			}},
			{EffectID::armorAllRepairSystemsAmountBonusPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1775]},{modifiers[1776]},
			}},
			{EffectID::eliteBonusViolatorsRepairSystemsArmorDamageAmount2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1777]},
			}},
			{EffectID::shipBonusRepairSystemsBonusATC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1778]},
			}},
			{EffectID::shipBonusRepairSystemsArmorRepairAmountGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1779]},
			}},
			{EffectID::damageCloudChanceReductionFixed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1780]},
			}},
			{EffectID::deepCoreMiningSkillBoostDamageCloudChanceReductionMul, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1781]},
			}},
			{EffectID::shipHeavyMissileAOECloudSizeCBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1782]},
			}},
			{EffectID::shipHeavyAssaultMissileAOECloudSizeCBC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1783]},
			}},
			{EffectID::shipHybridTrackingGBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1784]},
			}},
			{EffectID::shipEnergyTrackingABC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1785]},
			}},
			{EffectID::shipBonusMETOptimalAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1786]},
			}},
			{EffectID::shipMissileEMDamageCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1787]},
			}},
			{EffectID::shipMissileThermDamageCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1788]},
			}},
			{EffectID::shipMissileExpDamageCC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1789]},
			}},
			{EffectID::shipMissileKinDamageCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1790]},
			}},
			{EffectID::shipHeavyAssaultMissileAOECloudSizeCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1791]},
			}},
			{EffectID::shipHeavyMissileAOECloudSizeCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1792]},
			}},
			{EffectID::shipBonusDroneTrackingGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1793]},
			}},
			{EffectID::shipBonusDroneMWDboostGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1794]},
			}},
			{EffectID::baseMaxScanDeviationModifierModuleOnline2None, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1795]},
			}},
			{EffectID::systemScanDurationModuleModifier, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1796]},
			}},
			{EffectID::baseSensorStrengthModifierModule, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1797]},
			}},
			{EffectID::shipMissileHeavyAssaultVelocityABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1798]},
			}},
			{EffectID::shipMissileHeavyVelocityABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1799]},
			}},
			{EffectID::shipLaserCap1ABC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1800]},
			}},
			{EffectID::shipMissileVelocityCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1801]},
			}},
			{EffectID::shipBonusDroneDamageMultiplierAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1802]},
			}},
			{EffectID::shipBonusDroneArmorHitPointsAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1803]},
			}},
			{EffectID::shipBonusDroneShieldHitPointsAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1804]},
			}},
			{EffectID::shipBonusDroneStructureHitPointsAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1805]},
			}},
			{EffectID::shipBonusEnergyNeutRangeAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1806]},
			}},
			{EffectID::shipBonusEnergyVampireRangeAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1807]},
			}},
			{EffectID::shipLargeHybridTurretRofGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1808]},
			}},
			{EffectID::shipBonusDroneTrackingGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1809]},
			}},
			{EffectID::shipBonusDroneOptimalRangeGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1810]},
			}},
			{EffectID::shipBonusMissileAoeVelocityMB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1811]},
			}},
			{EffectID::shipBonusAoeVelocityCruiseMissilesMB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1812]},
			}},
			{EffectID::shipBonusLargeEnergyTurretTrackingAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1813]},
			}},
			{EffectID::hackingSkillVirusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1814]},
			}},
			{EffectID::dataMiningSkillLevelVirusCoherenceBonusModifier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1815]},
			}},
			{EffectID::archaeologySkillVirusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1816]},
			}},
			{EffectID::shipTorpedoAOECloudSize1CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1817]},
			}},
			{EffectID::shipCruiseMissileAOECloudSize1CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1818]},
			}},
			{EffectID::shipCruiseMissileROFCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1819]},
			}},
			{EffectID::shipTorpedoROFCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1820]},
			}},
			{EffectID::minigameVirusStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1821]},{modifiers[1822]},
			}},
			{EffectID::shieldOperationRechargeratebonusPostPercentOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[161]},
			}},
			{EffectID::shipBonusAgilityCI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1823]},
			}},
			{EffectID::shipBonusAgilityMI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1824]},
			}},
			{EffectID::shipBonusAgilityGI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1825]},
			}},
			{EffectID::shipBonusAgilityAI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1826]},
			}},
			{EffectID::shipBonusOreCapacityGI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1827]},
			}},
			{EffectID::shipBonusAmmoBayMI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1828]},
			}},
			{EffectID::shipBonusPICommoditiesHoldGI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1829]},
			}},
			{EffectID::shipBonusMineralBayGI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1830]},
			}},
			{EffectID::setBonusChristmasBonusVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1831]},
			}},
			{EffectID::setBonusChristmasAgilityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1832]},
			}},
			{EffectID::setBonusChristmasShieldCapacityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1833]},
			}},
			{EffectID::setBonusChristmasArmorHPBonus2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1834]},
			}},
			{EffectID::shipSPTOptimalBonusMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1835]},
			}},
			{EffectID::shipBonusProjectileDamageMBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1836]},
			}},
			{EffectID::eliteBonusCommandShipHAMRoFCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1837]},
			}},
			{EffectID::eliteBonusCommandShipHMRoFCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1838]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyAssaultMissileExplosionVelocityCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1839]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyAssaultMissileExplosionRadiusCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1840]},
			}},
			{EffectID::eliteBonusCommandShipsHeavyMissileExplosionRadiusCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1841]},
			}},
			{EffectID::eliteBonusCommandShipMediumHybridDamageCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1842]},
			}},
			{EffectID::eliteBonusCommandShipMediumHybridTrackingCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1843]},
			}},
			{EffectID::eliteBonusCommandShipHeavyDroneTrackingCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1844]},
			}},
			{EffectID::eliteBonusCommandShipHeavyDroneVelocityCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1845]},
			}},
			{EffectID::eliteBonusCommandShipMediumHybridRoFCS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1846]},
			}},
			{EffectID::eliteBonusCommandShipHeavyAssaultMissileDamageCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1847]},{modifiers[1848]},{modifiers[1849]},{modifiers[1850]},
			}},
			{EffectID::eliteBonusCommandShipHeavyMissileDamageCS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1851]},{modifiers[1852]},{modifiers[1853]},{modifiers[1854]},
			}},
			{EffectID::skillJumpCloneCooldownReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1855]},
			}},
			{EffectID::shipBonusHMLKineticDamageAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1856]},
			}},
			{EffectID::shipBonusHMLEMDamageAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1857]},
			}},
			{EffectID::shipBonusHMLThermDamageAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1858]},
			}},
			{EffectID::shipBonusHMLExploDamageAC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1859]},
			}},
			{EffectID::shipBonusHMLVelocityEliteBonusHeavyGunship1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1860]},
			}},
			{EffectID::shipBonusHAMVelocityEliteBonusHeavyGunship1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1861]},
			}},
			{EffectID::shipBonusArmorRepAmountGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1862]},
			}},
			{EffectID::shipBonusHeavyDroneSpeedGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1863]},
			}},
			{EffectID::shipBonusHeavyDRoneTrackingGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1864]},
			}},
			{EffectID::shipBonusSentryDroneOptimalRangeEliteBonusHeavyGunship2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1865]},
			}},
			{EffectID::shipBonusSentryDroneTrackingEliteBonusHeavyGunship2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1866]},
			}},
			{EffectID::shipBonusShieldBoostAmountMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1867]},
			}},
			{EffectID::roleBonusMarauderMJDRReactivationDelayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1868]},
			}},
			{EffectID::subSystemBonusAmarrDefensiveInformationWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1869]},{modifiers[1870]},{modifiers[1871]},{modifiers[1872]},{modifiers[1873]},
			}},
			{EffectID::subSystemBonusAmarrDefensiveSkirmishWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1874]},{modifiers[1875]},{modifiers[1876]},{modifiers[1877]},{modifiers[1878]},
			}},
			{EffectID::subSystemBonusCaldariOffensiveCommandBursts, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1879]},{modifiers[1880]},{modifiers[1881]},{modifiers[1882]},{modifiers[1883]},{modifiers[1884]},{modifiers[1885]},{modifiers[1886]},{modifiers[1887]},{modifiers[1888]},{modifiers[1889]},{modifiers[1890]},{modifiers[1891]},{modifiers[1892]},{modifiers[1893]},
			}},
			{EffectID::subSystemBonusCaldariDefensiveSkirmishWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1894]},{modifiers[1895]},{modifiers[1896]},{modifiers[1897]},{modifiers[1898]},
			}},
			{EffectID::subSystemBonusGallenteDefensiveSkirmishWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1899]},{modifiers[1900]},{modifiers[1901]},{modifiers[1902]},{modifiers[1903]},
			}},
			{EffectID::subSystemBonusGallenteOffensiveCommandBursts, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1904]},{modifiers[1905]},{modifiers[1906]},{modifiers[1907]},{modifiers[1908]},{modifiers[1909]},{modifiers[1910]},{modifiers[1911]},{modifiers[1912]},{modifiers[1913]},{modifiers[1914]},{modifiers[1915]},{modifiers[1916]},{modifiers[1917]},{modifiers[1918]},
			}},
			{EffectID::subSystemBonusMinmatarDefensiveSiegeWarfare, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1919]},{modifiers[1920]},{modifiers[1921]},{modifiers[1922]},{modifiers[1923]},
			}},
			{EffectID::subSystemBonusMinmatarOffensiveCommandBursts, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1924]},{modifiers[1925]},{modifiers[1926]},{modifiers[1927]},{modifiers[1928]},{modifiers[1929]},{modifiers[1930]},{modifiers[1931]},{modifiers[1932]},{modifiers[1933]},{modifiers[1934]},{modifiers[1935]},{modifiers[1936]},{modifiers[1937]},{modifiers[1938]},
			}},
			{EffectID::commandShipSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1939]},
			}},
			{EffectID::eliteBonusCommandShipArmoredCS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1940]},{modifiers[1941]},{modifiers[1942]},{modifiers[1943]},{modifiers[1944]},
			}},
			{EffectID::eliteBonusCommandShipSiegeCS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1945]},{modifiers[1946]},{modifiers[1947]},{modifiers[1948]},{modifiers[1949]},
			}},
			{EffectID::eliteBonusCommandShipSkirmishCS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1950]},{modifiers[1951]},{modifiers[1952]},{modifiers[1953]},{modifiers[1954]},
			}},
			{EffectID::eliteBonusCommandShipInformationCS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1955]},{modifiers[1956]},{modifiers[1957]},{modifiers[1958]},{modifiers[1959]},
			}},
			{EffectID::capacitorEmissionSystemskill, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1960]},
			}},
			{EffectID::shipBonusLargeEnergyTurretMaxRangeAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1961]},
			}},
			{EffectID::shipBonusHTFalloffGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1962]},
			}},
			{EffectID::piCustomsOfficeTaxReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1963]},
			}},
			{EffectID::piTaxReductionModifierSkillModifier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1964]},
			}},
			{EffectID::shipBonusRHMLROF2CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1965]},
			}},
			{EffectID::shipBonusRHMLROFCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1966]},
			}},
			{EffectID::shipBonusRHMLROFMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1967]},
			}},
			{EffectID::shipBonusCruiseROFMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1968]},
			}},
			{EffectID::shipBonusTorpedoROFMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1969]},
			}},
			{EffectID::shipBonusCruiseMissileEMDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1970]},
			}},
			{EffectID::shipBonusCruiseMissileThermDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1971]},
			}},
			{EffectID::shipBonusCruiseMissileKineticDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1972]},
			}},
			{EffectID::shipBonusCruiseMissileExploDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1973]},
			}},
			{EffectID::shipBonusTorpedoMissileExploDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1974]},
			}},
			{EffectID::shipBonusTorpedoMissileEMDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1975]},
			}},
			{EffectID::shipBonusTorpedoMissileThermDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1976]},
			}},
			{EffectID::shipBonusTorpedoMissileKineticDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1977]},
			}},
			{EffectID::shipBonusHeavyMissileEMDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1978]},
			}},
			{EffectID::shipBonusHeavyMissileThermDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1979]},
			}},
			{EffectID::shipBonusHeavyMissileKineticDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1980]},
			}},
			{EffectID::shipBonusHeavyMissileExploDmgMB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1981]},
			}},
			{EffectID::shipBonusMissileVelocityCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1982]},
			}},
			{EffectID::covertOpsCloakCPUPercentRoleBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1983]},
			}},
			{EffectID::shipArmorResistanceAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[531]},{modifiers[532]},{modifiers[533]},{modifiers[534]},
			}},
			{EffectID::interceptor2ShieldResist, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1984]},{modifiers[1985]},{modifiers[1986]},{modifiers[1987]},
			}},
			{EffectID::interceptor2ProjectileDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1988]},
			}},
			{EffectID::shipBonusSmallMissileExplosionRadiusCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1989]},{modifiers[1990]},
			}},
			{EffectID::shipBonusMissileVelocityAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1991]},
			}},
			{EffectID::eliteBonusInterdictorsArmorResist1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1992]},{modifiers[1993]},{modifiers[1994]},{modifiers[1995]},
			}},
			{EffectID::setWarpSpeedMultiplier, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1996]},
			}},
			{EffectID::implantSetWarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1997]},
			}},
			{EffectID::shipBonusMETOptimalRangePirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1998]},
			}},
			{EffectID::shipHybridOptimalGD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[1999]},
			}},
			{EffectID::eliteBonusInterdictorsMWDSigRadius2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2000]},
			}},
			{EffectID::shipSHTOptimalBonusGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2001]},
			}},
			{EffectID::shipBonusRemoteRepairAmountPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2002]},
			}},
			{EffectID::shipBonusLETOptimalRangePirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2003]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageExpRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2004]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageKinRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2005]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageEMRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2006]},
			}},
			{EffectID::eliteBonusMaraudersHeavyMissileDamageThermRole1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2007]},
			}},
			{EffectID::shipScanProbeStrengthBonusPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2008]},
			}},
			{EffectID::shipBonusRemoteRepairRangePirateFaction2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2009]},{modifiers[2010]},
			}},
			{EffectID::overloadSelfTrackingModuleBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[2011]},{modifiers[2012]},{modifiers[2013]},
			}},
			{EffectID::overloadSelfSensorModuleBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[2014]},{modifiers[2015]},{modifiers[2016]},{modifiers[2017]},{modifiers[2018]},{modifiers[2019]},
			}},
			{EffectID::overloadSelfPainterBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[2020]},
			}},
			{EffectID::repairDroneHullBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2021]},
			}},
			{EffectID::shipMissileRoFMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2022]},
			}},
			{EffectID::shipBonusSPTFalloffMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2023]},
			}},
			{EffectID::miningAmountBonusBonusActivation, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[2024]},
			}},
			{EffectID::ewSkillTrackingDisruptionRangeDisruptionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2025]},{modifiers[2026]},
			}},
			{EffectID::shipBonusEwWeaponDisruptionStrengthRookie, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2027]},{modifiers[2028]},{modifiers[2029]},{modifiers[2030]},{modifiers[2031]},{modifiers[2032]},{modifiers[2033]},
			}},
			{EffectID::shipBonusAfterburnerSpeedFactor2CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2034]},
			}},
			{EffectID::shipBonusSentryDroneDamageMultiplierPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2035]},
			}},
			{EffectID::shipBonusHeavyDroneDamageMultiplierPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2036]},
			}},
			{EffectID::shipBonusSentryDroneHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2037]},
			}},
			{EffectID::shipBonusSentryDroneArmorHpPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2038]},
			}},
			{EffectID::shipBonusSentryDroneShieldHpPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2039]},
			}},
			{EffectID::shipBonusHeavyDroneShieldHpPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2040]},
			}},
			{EffectID::shipBonusHeavyDroneArmorHpPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2041]},
			}},
			{EffectID::shipBonusHeavyDroneHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2042]},
			}},
			{EffectID::shipBonusKineticMissileDamageGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2043]},
			}},
			{EffectID::shipBonusThermalMissileDamageGB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2044]},
			}},
			{EffectID::shipBonusAfterburnerSpeedFactorCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2045]},
			}},
			{EffectID::shipBonusKineticMissileDamageGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2046]},
			}},
			{EffectID::shipBonusThermalMissileDamageGF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2047]},
			}},
			{EffectID::shipBonusLightDroneDamageMultiplierPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2048]},
			}},
			{EffectID::shipBonusLightDroneHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2049]},
			}},
			{EffectID::shipBonusLightDroneArmorHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2050]},
			}},
			{EffectID::shipBonusLightDroneShieldHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2051]},
			}},
			{EffectID::shipBonusAfterburnerSpeedFactorCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2052]},
			}},
			{EffectID::shipBonusMediumDroneDamageMultiplierPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2053]},
			}},
			{EffectID::shipBonusMediumDroneHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2054]},
			}},
			{EffectID::shipBonusMediumDroneArmorHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2055]},
			}},
			{EffectID::shipBonusMediumDroneShieldHPPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2056]},
			}},
			{EffectID::shipBonusKineticMissileDamageGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2057]},
			}},
			{EffectID::shipBonusThermalMissileDamageGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2058]},
			}},
			{EffectID::shipBonusTDOptimalBonusAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2059]},
			}},
			{EffectID::shipBonusMiningDurationORE3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2060]},
			}},
			{EffectID::shipBonusMiningIceHarvestingRangeORE2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2061]},{modifiers[2062]},
			}},
			{EffectID::eliteBargeShieldResistance1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2063]},{modifiers[2064]},{modifiers[2065]},{modifiers[2066]},
			}},
			{EffectID::eliteBargeBonusMiningDurationBarge2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2067]},
			}},
			{EffectID::expeditionFrigateSkillLevelPostMulEliteBonusExpedition1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2068]},
			}},
			{EffectID::expeditionFrigateSkillLevelPostMulEliteBonusExpedition2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2069]},
			}},
			{EffectID::eliteBonusExpeditionMining1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2070]},
			}},
			{EffectID::eliteBonusExpeditionSigRadius2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2071]},
			}},
			{EffectID::shipBonusNosferatuOverride, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2072]},
			}},
			{EffectID::shipMissileEMDamageCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2073]},
			}},
			{EffectID::shipMissileKinDamageCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2074]},
			}},
			{EffectID::shipMissileThermDamageCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2075]},
			}},
			{EffectID::shipMissileExploDamageCB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2076]},
			}},
			{EffectID::shipBonusWarpScrambleMaxRangeGB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2077]},
			}},
			{EffectID::shipBonusMissileExplosionDelayPirateFaction2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2078]},
			}},
			{EffectID::drawbackCargoCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2079]},
			}},
			{EffectID::eliteIndustrialWarpSpeedBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2080]},
			}},
			{EffectID::shipBonusShieldBoostCI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2081]},
			}},
			{EffectID::shipBonusShieldBoostMI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2082]},
			}},
			{EffectID::shipBonusArmorRepairAI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2083]},
			}},
			{EffectID::shipBonusArmorRepairGI2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2084]},
			}},
			{EffectID::eliteIndustrialFleetCapacity1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2085]},
			}},
			{EffectID::eliteIndustrialShieldResists2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2086]},{modifiers[2087]},{modifiers[2088]},{modifiers[2089]},
			}},
			{EffectID::eliteIndustrialArmorResists2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2090]},{modifiers[2091]},{modifiers[2092]},{modifiers[2093]},
			}},
			{EffectID::eliteIndustrialABHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2094]},
			}},
			{EffectID::eliteIndustrialMWDHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2095]},
			}},
			{EffectID::eliteIndustrialArmorHardenerHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2096]},
			}},
			{EffectID::eliteIndustrialReactiveArmorHardenerHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2097]},
			}},
			{EffectID::eliteIndustrialShieldHardenerHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2098]},
			}},
			{EffectID::eliteIndustrialShieldBoosterHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2099]},{modifiers[2100]},
			}},
			{EffectID::eliteIndustrialArmorRepairHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2101]},{modifiers[2102]},
			}},
			{EffectID::warpSpeedAddition, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2103]},
			}},
			{EffectID::roleBonusBulkheadCPU, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2104]},
			}},
			{EffectID::advancedIndustryManufacturingTimeBonusPostPercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2105]},
			}},
			{EffectID::advancedIndustryCopyTimeBonusPostPercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2106]},
			}},
			{EffectID::advancedIndustryInventionTimeBonusPostPercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2107]},
			}},
			{EffectID::advancedIndustrySkillBoostAdvancedIndustrySkillIndustryJobTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2108]},
			}},
			{EffectID::advancedIndustryManufactureTimeResearchTimeBonusPostPercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2109]},
			}},
			{EffectID::advancedIndustryMaterialResearchTimeBonusPostPercent, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2110]},
			}},
			{EffectID::onlineJumpDriveConsumptionAmountBonusPercentage, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[1000]},
			}},
			{EffectID::warpScrambleBlockMWDWithNPCEffect, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[8]},{modifiers[2111]},{modifiers[2112]},
			}},
			{EffectID::shipBonusSmallMissileExplosionRadiusCF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2113]},{modifiers[2114]},
			}},
			{EffectID::shipRocketRoFBonusAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2115]},
			}},
			{EffectID::eliteBonusInterdictorsSHTRoF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2116]},
			}},
			{EffectID::shipMissileLauncherRoFAD1Fixed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2117]},
			}},
			{EffectID::cloakingPrototype, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[214]},
			}},
			{EffectID::drawbackWarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2118]},
			}},
			{EffectID::shipMETDamageBonusAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2119]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsMETOptimal, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2120]},
			}},
			{EffectID::shipHybridTrackingGC, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2121]},
			}},
			{EffectID::eliteBonusHeavyInterdictorsHybridOptimal1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2122]},
			}},
			{EffectID::resistanceKillerShieldAll, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2123]},{modifiers[2124]},{modifiers[2125]},{modifiers[2126]},
			}},
			{EffectID::resistanceKillerArmorAll, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2127]},{modifiers[2128]},{modifiers[2129]},{modifiers[2130]},
			}},
			{EffectID::resistanceKillerHullAll, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2131]},{modifiers[2132]},{modifiers[2133]},{modifiers[2134]},
			}},
			{EffectID::resistanceKillerShieldArmorAll, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2123]},{modifiers[2124]},{modifiers[2125]},{modifiers[2126]},{modifiers[2127]},{modifiers[2128]},{modifiers[2129]},{modifiers[2130]},
			}},
			{EffectID::freighterO1SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2135]},
			}},
			{EffectID::freighterO2SkillLevel, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2136]},
			}},
			{EffectID::freighterSMACapacityBonusO1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2137]},
			}},
			{EffectID::freighterAgilityBonus2O2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2138]},
			}},
			{EffectID::tacticalDestroyerAmarrSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2139]},
			}},
			{EffectID::tacticalDestroyerAmarrSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2140]},
			}},
			{EffectID::tacticalDestroyerAmarrSkillLevel3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2141]},
			}},
			{EffectID::shipSETDamageAmarrTacticalDestroyer1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2142]},
			}},
			{EffectID::shipSETCapNeedAmarrTacticalDestroyer2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2143]},
			}},
			{EffectID::shipHeatDamageAmarrTacticalDestroyer3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2144]},
			}},
			{EffectID::probeLauncherCPUPercentRoleBonusT3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2145]},
			}},
			{EffectID::shipModeMaxTargetRangePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2146]},
			}},
			{EffectID::shipModeSETOptimalRangePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2147]},
			}},
			{EffectID::shipModeScanStrengthPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2148]},{modifiers[2149]},{modifiers[2150]},{modifiers[2151]},
			}},
			{EffectID::modeSigRadiusPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2152]},
			}},
			{EffectID::modeArmorResonancePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2153]},{modifiers[2154]},{modifiers[2155]},{modifiers[2156]},
			}},
			{EffectID::modeAgilityPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2157]},
			}},
			{EffectID::modeVelocityPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2158]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalRS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2159]},
			}},
			{EffectID::shipBonusEnergyNosOptimalRS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2160]},
			}},
			{EffectID::reconShipSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2161]},
			}},
			{EffectID::eliteReconBonusMHTOptimalRange1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2162]},
			}},
			{EffectID::eliteReconBonusMPTdamage1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2163]},
			}},
			{EffectID::remoteCapacitorTransmitterPowerNeedBonusEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2164]},
			}},
			{EffectID::tacticalDestroyerMinmatarSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2165]},
			}},
			{EffectID::tacticalDestroyerMinmatarSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2166]},
			}},
			{EffectID::tacticalDestroyerMinmatarSkillLevel3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2167]},
			}},
			{EffectID::shipHeatDamageMinmatarTacticalDestroyer3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2168]},
			}},
			{EffectID::shipSPTDamageMinmatarTacticalDestroyer1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2169]},
			}},
			{EffectID::shipSPTOptimalMinmatarTacticalDestroyer2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2170]},
			}},
			{EffectID::shipModeSPTTrackingPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2171]},
			}},
			{EffectID::modeMWDSigRadiusPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2172]},
			}},
			{EffectID::modeShieldResonancePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2173]},{modifiers[2174]},{modifiers[2175]},{modifiers[2176]},
			}},
			{EffectID::subsystemBonusCaldariDefensiveShieldRechargeRate, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2177]},
			}},
			{EffectID::gallenteCruiserSkillLevelPreMulShipBonusGC3Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2178]},
			}},
			{EffectID::shipBonusSentryDamageMultiplierGC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2179]},
			}},
			{EffectID::shipBonusSentryHPGC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2180]},
			}},
			{EffectID::shipBonusSentryArmorHPGC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2181]},
			}},
			{EffectID::shipBonusSentryShieldHPGC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2182]},
			}},
			{EffectID::shipBonusLightDroneDamageMultiplierGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2183]},
			}},
			{EffectID::shipBonusMediumDroneDamageMultiplierGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2184]},
			}},
			{EffectID::shipBonusHeavyDroneDamageMultiplierGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2185]},
			}},
			{EffectID::shipBonusHeavyDroneHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2186]},
			}},
			{EffectID::shipBonusHeavyDroneArmorHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2187]},
			}},
			{EffectID::shipBonusHeavyDroneShieldHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2188]},
			}},
			{EffectID::shipBonusMediumDroneShieldHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2189]},
			}},
			{EffectID::shipBonusMediumDroneArmorHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2190]},
			}},
			{EffectID::shipBonusMediumDroneHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2191]},
			}},
			{EffectID::shipBonusLightDroneHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2192]},
			}},
			{EffectID::shipBonusLightDroneArmorHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2193]},
			}},
			{EffectID::shipBonusLightDroneShieldHPGC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2194]},
			}},
			{EffectID::entosisLink, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::shipModeMissileVelocityPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2195]},
			}},
			{EffectID::shipHeatDamageCaldariTacticalDestroyer3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2196]},
			}},
			{EffectID::tacticalDestroyerCaldariSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2197]},
			}},
			{EffectID::tacticalDestroyerCaldariSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2198]},
			}},
			{EffectID::tacticalDestroyerCaldariSkillLevel3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2199]},
			}},
			{EffectID::shipSmallMissileDmgPirateFaction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2200]},{modifiers[2201]},{modifiers[2202]},{modifiers[2203]},{modifiers[2204]},{modifiers[2205]},{modifiers[2206]},{modifiers[2207]},
			}},
			{EffectID::shipMissileRoFCaldariTacticalDestroyer1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2208]},
			}},
			{EffectID::shipBonusHeavyAssaultMissileAllDamageMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2209]},{modifiers[2210]},{modifiers[2211]},{modifiers[2212]},
			}},
			{EffectID::shipBonusHeavyMissileAllDamageMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2213]},{modifiers[2214]},{modifiers[2215]},{modifiers[2216]},
			}},
			{EffectID::shipBonusLightMissileAllDamageMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2217]},{modifiers[2218]},{modifiers[2219]},{modifiers[2220]},
			}},
			{EffectID::shipMissileReloadTimeCaldariTacticalDestroyer2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2221]},
			}},
			{EffectID::entosisDurationMultiply, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2222]},
			}},
			{EffectID::missileVelocityBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2223]},
			}},
			{EffectID::missileExplosionDelayBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2224]},
			}},
			{EffectID::missileAOECloudSizeBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2225]},
			}},
			{EffectID::missileAOEVelocityBonusOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2226]},
			}},
			{EffectID::scriptMissileGuidanceComputerAOECloudSizeBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2227]},
			}},
			{EffectID::scriptMissileGuidanceComputerAOEVelocityBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2228]},
			}},
			{EffectID::scriptMissileGuidanceComputerMissileVelocityBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2229]},
			}},
			{EffectID::scriptMissileGuidanceComputerExplosionDelayBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2230]},
			}},
			{EffectID::missileGuidanceComputerBonus4, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[2223]},{modifiers[2224]},{modifiers[2225]},{modifiers[2226]},
			}},
			{EffectID::overloadSelfMissileGuidanceBonus5, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[2231]},{modifiers[2232]},{modifiers[2233]},{modifiers[2234]},{modifiers[2235]},
			}},
			{EffectID::tacticalDestroyerGallenteSkillLevel1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2236]},
			}},
			{EffectID::tacticalDestroyerGallenteSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2237]},
			}},
			{EffectID::tacticalDestroyerGallenteSkillLevel3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2238]},
			}},
			{EffectID::shipHeatDamageGallenteTacticalDestroyer3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2239]},
			}},
			{EffectID::shipSHTRoFGallenteTacticalDestroyer1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2240]},
			}},
			{EffectID::shipSHTTrackingGallenteTacticalDestroyer2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2241]},
			}},
			{EffectID::modeHullResonancePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2242]},{modifiers[2243]},{modifiers[2244]},{modifiers[2245]},
			}},
			{EffectID::shipModeSHTOptimalRangePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2246]},
			}},
			{EffectID::modeMWDCapPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2247]},
			}},
			{EffectID::modeMWDBoostPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2248]},
			}},
			{EffectID::modeArmorRepDurationPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2249]},
			}},
			{EffectID::passiveSpeedLimit, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2250]},
			}},
			{EffectID::shipBonusWDFGnullPenalties, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2251]},{modifiers[2252]},{modifiers[2253]},
			}},
			{EffectID::entosisCPUPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2254]},
			}},
			{EffectID::entosisCPUAddition, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2255]},
			}},
			{EffectID::battlecruiserMETRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2256]},{modifiers[2257]},
			}},
			{EffectID::battlecruiserMHTRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2258]},{modifiers[2259]},
			}},
			{EffectID::battlecruiserMPTRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2260]},{modifiers[2261]},
			}},
			{EffectID::battlecruiserMissileRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2262]},
			}},
			{EffectID::battlecruiserDroneSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2263]},
			}},
			{EffectID::shipHybridDmg1CBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2264]},
			}},
			{EffectID::shipBonusProjectileTrackingMBC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2265]},
			}},
			{EffectID::shipModuleRemoteCapacitorTransmitter, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[2266]},
			}},
			{EffectID::shipModuleRemoteHullRepairer, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[2267]},
			}},
			{EffectID::shipModuleRemoteShieldBooster, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[3]},
			}},
			{EffectID::energyNeutralizerFalloff, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[2268]},
			}},
			{EffectID::shipModuleRemoteArmorRepairer, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[206]},
			}},
			{EffectID::expeditionFrigateShieldResistance1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2269]},{modifiers[2270]},{modifiers[2271]},{modifiers[2272]},
			}},
			{EffectID::expeditionFrigateBonusIceHarvestingCycleTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2273]},
			}},
			{EffectID::energyNosferatuFalloff, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[2268]},
			}},
			{EffectID::doomsdaySlash, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::microJumpPortalDrive, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::commandDestroyerSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2274]},
			}},
			{EffectID::commandDestroyerSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2275]},
			}},
			{EffectID::commandDestroyerSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2276]},
			}},
			{EffectID::roleBonusCDLinksPGReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2277]},
			}},
			{EffectID::structureEnergyNeutralizerFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::structureWarpScrambleBlockMWDWithNPCEffect, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[8]},{modifiers[2111]},{modifiers[2112]},
			}},
			{EffectID::structureTargetMaxTargetRangeAndScanResolutionBonusAssistance, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[2278]},{modifiers[2279]},
			}},
			{EffectID::structureTargetGunneryMaxRangeFalloffTrackingSpeedBonusAssistance, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[2280]},{modifiers[2281]},{modifiers[2282]},
			}},
			{EffectID::structureMissileGuidanceComputerBonus4, MetaInfo::Effect::Category::active, false, true, {
				{modifiers[2223]},{modifiers[2224]},{modifiers[2225]},{modifiers[2226]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalRS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2283]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffRS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2284]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffRS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2285]},
			}},
			{EffectID::shipBonusEnergyNosOptimalRS1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2286]},
			}},
			{EffectID::shipBonusEnergyNosFalloffRS2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2287]},
			}},
			{EffectID::shipBonusEnergyNosFalloffRS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2288]},
			}},
			{EffectID::miningFrigateBonusIceHarvestingCycleTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2289]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2290]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2291]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2292]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2293]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2294]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2295]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2296]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAB2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2297]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalEAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2298]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffEAF3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2299]},
			}},
			{EffectID::shipBonusEnergyNosOptimalEAF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2300]},
			}},
			{EffectID::shipBonusEnergyNosFalloffEAF3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2301]},
			}},
			{EffectID::electronicAttackShipsSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2302]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2303]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAF3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2304]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2305]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAF3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2306]},
			}},
			{EffectID::amarrCruiserSkillLevelPreMulShipBonusAC3Ship, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2307]},
			}},
			{EffectID::shipBonusEnergyNeutOptimalAC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2308]},
			}},
			{EffectID::shipBonusEnergyNeutFalloffAC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2309]},
			}},
			{EffectID::shipBonusEnergyNosOptimalAC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2310]},
			}},
			{EffectID::shipBonusNosOptimalFalloffAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2311]},{modifiers[2312]},
			}},
			{EffectID::shipBonusEnergyNosFalloffAC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2313]},
			}},
			{EffectID::serviceSlot, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::shipBonusThermMissileDmgMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2314]},
			}},
			{EffectID::shipBonusEMMissileDmgMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2315]},
			}},
			{EffectID::shipBonusKineticMissileDmgMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2316]},
			}},
			{EffectID::shipBonusExplosiveMissileDmgMD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2317]},
			}},
			{EffectID::eliteBonusCommandDestroyerSkirmish1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2318]},{modifiers[2319]},{modifiers[2320]},{modifiers[2321]},{modifiers[2322]},
			}},
			{EffectID::eliteBonusCommandDestroyerShield1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2323]},{modifiers[2324]},{modifiers[2325]},{modifiers[2326]},{modifiers[2327]},
			}},
			{EffectID::eliteBonusCommandDestroyerMJFGspool2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2328]},
			}},
			{EffectID::shipBonusEMShieldResistanceMD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2329]},
			}},
			{EffectID::shipBonusKineticShieldResistanceMD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2330]},
			}},
			{EffectID::shipBonusThermalShieldResistanceMD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2331]},
			}},
			{EffectID::shipBonusExplosiveShieldResistanceMD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2332]},
			}},
			{EffectID::scriptscanGravimetricStrengthBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2333]},
			}},
			{EffectID::scriptscanLadarStrengthBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2334]},
			}},
			{EffectID::scriptscanMagnetometricStrengthBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2335]},
			}},
			{EffectID::scriptscanRadarStrengthBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2336]},
			}},
			{EffectID::shipBonusThermalMissileDamageCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2337]},
			}},
			{EffectID::shipBonusEMMissileDamageCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2338]},
			}},
			{EffectID::shipBonusKineticMissileDamageCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2339]},
			}},
			{EffectID::shipBonusExplosiveMissileDamageCD1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2340]},
			}},
			{EffectID::shipBonusShieldEMResistanceCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2341]},
			}},
			{EffectID::shipBonusShieldThermalResistanceCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2342]},
			}},
			{EffectID::shipBonusShieldKineticResistanceCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2343]},
			}},
			{EffectID::shipBonusShieldExplosiveResistanceCD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2344]},
			}},
			{EffectID::eliteBonusCommandDestroyerInfo1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2345]},{modifiers[2346]},{modifiers[2347]},{modifiers[2348]},{modifiers[2349]},
			}},
			{EffectID::shipBonusKineticArmorResistanceAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2350]},
			}},
			{EffectID::shipBonusThermalArmorResistanceAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2351]},
			}},
			{EffectID::shipBonusEMArmorResistanceAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2352]},
			}},
			{EffectID::shipBonusExplosiveArmorResistanceAD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2353]},
			}},
			{EffectID::eliteBonusCommandDestroyerArmored1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2354]},{modifiers[2355]},{modifiers[2356]},{modifiers[2357]},{modifiers[2358]},
			}},
			{EffectID::shipBonusKineticArmorResistanceGD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2359]},
			}},
			{EffectID::shipBonusEMArmorResistanceGD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2360]},
			}},
			{EffectID::shipBonusThermalArmorResistanceGD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2361]},
			}},
			{EffectID::shipBonusExplosiveArmorResistanceGD2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2362]},
			}},
			{EffectID::setFixedResonance, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[2363]},{modifiers[2364]},{modifiers[2365]},{modifiers[2366]},{modifiers[2367]},{modifiers[2368]},{modifiers[2369]},{modifiers[2370]},{modifiers[2371]},{modifiers[2372]},{modifiers[2373]},{modifiers[2374]},
			}},
			{EffectID::shipSmallMissileKinDmgCF3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2375]},{modifiers[2376]},
			}},
			{EffectID::shipMissileKinDamageCC3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2377]},
			}},
			{EffectID::roleBonusWDRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2378]},{modifiers[2379]},
			}},
			{EffectID::roleBonusWDCapCPU, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2380]},{modifiers[2381]},
			}},
			{EffectID::shipBonusEwWeaponDisruptionStrengthAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2382]},{modifiers[2383]},{modifiers[2384]},{modifiers[2385]},{modifiers[2386]},{modifiers[2387]},{modifiers[2388]},
			}},
			{EffectID::roleBonusECMCapCPU, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2389]},{modifiers[2390]},
			}},
			{EffectID::roleBonusECMRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2391]},{modifiers[2392]},
			}},
			{EffectID::shipBonusJustScramblerRangeGF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2393]},
			}},
			{EffectID::roleBonusJustScramblerStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2394]},
			}},
			{EffectID::shipBonusAoeVelocityRocketsMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2395]},
			}},
			{EffectID::shipRocketEMThermKinDmgMF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2396]},{modifiers[2397]},{modifiers[2398]},
			}},
			{EffectID::shipRocketExpDmgMF3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2399]},
			}},
			{EffectID::roleBonusStasisRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2400]},
			}},
			{EffectID::shieldTransporterFalloffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2401]},{modifiers[2402]},
			}},
			{EffectID::shipShieldTransferFalloffMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2403]},
			}},
			{EffectID::shipShieldTransferFalloffCC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2404]},
			}},
			{EffectID::shipRemoteArmorFalloffGC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2405]},
			}},
			{EffectID::shipRemoteArmorFalloffAC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2406]},
			}},
			{EffectID::armorRepairProjectorFalloffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2407]},{modifiers[2408]},
			}},
			{EffectID::droneHullRepairBonusEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2409]},
			}},
			{EffectID::logiFrigSkillMultiplier1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2410]},
			}},
			{EffectID::logiFrigSkillMultiplier2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2411]},
			}},
			{EffectID::eliteBonusLogiFrigArmorRepSpeedCap1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2412]},{modifiers[2413]},
			}},
			{EffectID::eliteBonusLogiFrigShieldRepSpeedCap1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2414]},{modifiers[2415]},
			}},
			{EffectID::eliteBonusLogiFrigArmorHP2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2416]},
			}},
			{EffectID::eliteBonusLogiFrigShieldHP2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2417]},
			}},
			{EffectID::eliteBonusLogiFrigSignature2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2418]},
			}},
			{EffectID::overloadSelfMissileGuidanceModuleBonus, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[2232]},{modifiers[2233]},{modifiers[2234]},{modifiers[2235]},
			}},
			{EffectID::ignoreCloakVelocityPenalty, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2419]},
			}},
			{EffectID::ewSkillGuidanceDisruptionBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2420]},{modifiers[2421]},{modifiers[2422]},{modifiers[2423]},
			}},
			{EffectID::shipBonusEwWeaponDisruptionStrengthAC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2424]},{modifiers[2425]},{modifiers[2426]},{modifiers[2427]},{modifiers[2428]},{modifiers[2429]},{modifiers[2430]},
			}},
			{EffectID::skillStructureMissileDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2431]},{modifiers[2432]},{modifiers[2433]},{modifiers[2434]},{modifiers[2435]},{modifiers[2436]},{modifiers[2437]},{modifiers[2438]},{modifiers[2439]},{modifiers[2440]},{modifiers[2441]},{modifiers[2442]},
			}},
			{EffectID::skillStructureElectronicSystemsCapNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2443]},{modifiers[2444]},{modifiers[2445]},
			}},
			{EffectID::skillStructureEngineeringSystemsCapNeedBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2446]},{modifiers[2447]},
			}},
			{EffectID::structureRigAoeVelocityBonusSingleTargetMissiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2448]},{modifiers[2449]},
			}},
			{EffectID::structureRigVelocityBonusSingleTargetMissiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2450]},{modifiers[2451]},
			}},
			{EffectID::structureRigNeutralizerMaxRangeFalloffEffectiveness, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2452]},{modifiers[2453]},
			}},
			{EffectID::structureRigNeutralizerCapacitorNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2454]},
			}},
			{EffectID::structureRigEWMaxRangeFalloff, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2455]},{modifiers[2456]},{modifiers[2457]},{modifiers[2458]},{modifiers[2459]},{modifiers[2460]},
			}},
			{EffectID::structureRigEWCapacitorNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2461]},{modifiers[2462]},
			}},
			{EffectID::structureRigMaxTargets, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2463]},
			}},
			{EffectID::structureRigSensorResolution, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2464]},
			}},
			{EffectID::structureRigExplosionRadiusBonusAoEMissiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2465]},
			}},
			{EffectID::structureRigVelocityBonusAoeMissiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2466]},
			}},
			{EffectID::structureRigPDBmaxRange, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2467]},
			}},
			{EffectID::structureRigPDBCapacitorNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2468]},
			}},
			{EffectID::structureRigFighterHP, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2469]},{modifiers[2470]},{modifiers[2471]},{modifiers[2472]},{modifiers[2473]},{modifiers[2474]},
			}},
			{EffectID::structureRigFighterMaxVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2475]},{modifiers[2476]},
			}},
			{EffectID::structureRigDoomsdayDamageLoss, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2477]},
			}},
			{EffectID::remoteSensorDampFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::shipModuleGuidanceDisruptor, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::shipModuleTrackingDisruptor, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::remoteTargetPaintFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::remoteWebifierFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::remoteSensorBoostFalloff, MetaInfo::Effect::Category::target, false, true, {
				
			}},
			{EffectID::shipModuleRemoteTrackingComputer, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[2280]},{modifiers[2281]},{modifiers[2282]},
			}},
			{EffectID::fighterAbilityMissiles, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityEnergyNeutralizer, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityStasisWebifier, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityWarpDisruption, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityECM, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityEvasiveManeuvers, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::fighterAbilityAfterburner, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::fighterAbilityMicroWarpDrive, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::fighterAbilityMicroJumpDrive, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::pointDefense, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::tractorBeamShip, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::structureBumpingModule, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::lightningWeapon, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::structureMissileGuidanceEnhancer, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2478]},{modifiers[2479]},{modifiers[2480]},{modifiers[2481]},{modifiers[2482]},{modifiers[2483]},{modifiers[2484]},{modifiers[2485]},
			}},
			{EffectID::structureBallisticControlSystem, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2486]},{modifiers[2487]},{modifiers[2488]},{modifiers[2489]},{modifiers[2490]},{modifiers[2491]},{modifiers[2492]},{modifiers[2493]},{modifiers[2494]},{modifiers[2495]},
			}},
			{EffectID::structureMissileGuidanceComputerBonus5, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[2496]},{modifiers[2497]},{modifiers[2498]},{modifiers[2499]},
			}},
			{EffectID::structureScanResolutionActivePercentage, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[232]},
			}},
			{EffectID::fighterAbilityTackle, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::fighterAbilityAttackM, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::remoteECMFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::doomsdayBeamDOT, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayConeDOT, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayHOG, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::structureRigDoomsdayTargetAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2500]},
			}},
			{EffectID::doomsdayAOEWeb, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOENeut, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEPaint, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOETrack, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEGuide, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEDamp, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::doomsdayAOEBubble, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::emergencyHullEnergizer, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::fighterAbilityLaunchBomb, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::modifyEnergyWarfareResistance, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2501]},
			}},
			{EffectID::scriptSensorBoosterSensorStrengthBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2502]},{modifiers[2503]},{modifiers[2504]},{modifiers[2505]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtAmarr, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2506]},{modifiers[2507]},{modifiers[2508]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtCaldari, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2509]},{modifiers[2510]},{modifiers[2511]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtGallente, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2512]},{modifiers[2513]},{modifiers[2514]},
			}},
			{EffectID::skillMultiplierShipBonusDreadnoughtMinmatar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2515]},{modifiers[2516]},{modifiers[2517]},
			}},
			{EffectID::shipBonusDreadnoughtA1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2518]},
			}},
			{EffectID::shipBonusDreadnoughtA2ArmorResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2519]},{modifiers[2520]},{modifiers[2521]},{modifiers[2522]},
			}},
			{EffectID::shipBonusDreadnoughtA3CapNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2523]},
			}},
			{EffectID::shipBonusDreadnoughtC1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2524]},{modifiers[2525]},{modifiers[2526]},{modifiers[2527]},{modifiers[2528]},{modifiers[2529]},{modifiers[2530]},{modifiers[2531]},{modifiers[2532]},{modifiers[2533]},{modifiers[2534]},{modifiers[2535]},
			}},
			{EffectID::shipBonusDreadnoughtC2ShieldResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2536]},{modifiers[2537]},{modifiers[2538]},{modifiers[2539]},
			}},
			{EffectID::shipBonusDreadnoughtG1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2540]},
			}},
			{EffectID::shipBonusDreadnoughtG2ROFBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2541]},
			}},
			{EffectID::shipBonusDreadnoughtG3RepairTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2542]},
			}},
			{EffectID::shipBonusDreadnoughtM1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2543]},
			}},
			{EffectID::shipBonusDreadnoughtM2ROFBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2544]},
			}},
			{EffectID::shipBonusDreadnoughtM3RepairTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2545]},
			}},
			{EffectID::doomsdayAOEECM, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryAmarr, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2546]},{modifiers[2547]},{modifiers[2548]},{modifiers[2549]},
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryCaldari, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2550]},{modifiers[2551]},{modifiers[2552]},{modifiers[2553]},
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryGallente, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2554]},{modifiers[2555]},{modifiers[2556]},{modifiers[2557]},
			}},
			{EffectID::skillMultiplierShipBonusForceAuxiliaryMinmatar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2558]},{modifiers[2559]},{modifiers[2560]},{modifiers[2561]},
			}},
			{EffectID::shipBonusForceAuxiliaryA1RemoteRepairAndCapAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2562]},{modifiers[2563]},
			}},
			{EffectID::shipBonusForceAuxiliaryA2ArmorResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2564]},{modifiers[2565]},{modifiers[2566]},{modifiers[2567]},
			}},
			{EffectID::shipBonusForceAuxiliaryA3CapCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2568]},
			}},
			{EffectID::shipBonusForceAuxiliaryA4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2569]},{modifiers[2570]},{modifiers[2571]},{modifiers[2572]},{modifiers[2573]},{modifiers[2574]},{modifiers[2575]},{modifiers[2576]},{modifiers[2577]},{modifiers[2578]},
			}},
			{EffectID::shipBonusForceAuxiliaryM4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2579]},{modifiers[2580]},{modifiers[2581]},{modifiers[2582]},{modifiers[2583]},{modifiers[2584]},{modifiers[2585]},{modifiers[2586]},{modifiers[2587]},{modifiers[2588]},
			}},
			{EffectID::shipBonusForceAuxiliaryG4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2589]},{modifiers[2590]},{modifiers[2591]},{modifiers[2592]},{modifiers[2593]},{modifiers[2594]},{modifiers[2595]},{modifiers[2596]},{modifiers[2597]},{modifiers[2598]},
			}},
			{EffectID::shipBonusForceAuxiliaryC4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2599]},{modifiers[2600]},{modifiers[2601]},{modifiers[2602]},{modifiers[2603]},{modifiers[2604]},{modifiers[2605]},{modifiers[2606]},{modifiers[2607]},{modifiers[2608]},
			}},
			{EffectID::shipBonusRole1CommandBurstCPUBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2609]},
			}},
			{EffectID::shipBonusForceAuxiliaryC1RemoteBoostAndCapAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2610]},{modifiers[2611]},
			}},
			{EffectID::shipBonusForceAuxiliaryC2ShieldResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2612]},{modifiers[2613]},{modifiers[2614]},{modifiers[2615]},
			}},
			{EffectID::shipBonusForceAuxiliaryC3CapCapacity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2616]},
			}},
			{EffectID::shipBonusForceAuxiliaryG1RemoteCycleTime, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2617]},{modifiers[2618]},
			}},
			{EffectID::shipBonusForceAuxiliaryG2LocalRepairAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2619]},{modifiers[2620]},
			}},
			{EffectID::shipBonusForceAuxiliaryG3CapBoosterStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2621]},
			}},
			{EffectID::shipBonusForceAuxiliaryM1RemoteDuration, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2622]},{modifiers[2623]},
			}},
			{EffectID::shipBonusForceAuxiliaryM2LocalBoostAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2624]},{modifiers[2625]},
			}},
			{EffectID::shipBonusForceAuxiliaryM3CapBoosterStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2626]},
			}},
			{EffectID::fighterAbilityKamikaze, MetaInfo::Effect::Category::target, false, false, {
				
			}},
			{EffectID::moduleBonusDroneNavigationComputer, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2627]},{modifiers[2628]},
			}},
			{EffectID::moduleBonusDroneDamageAmplifier, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2629]},{modifiers[2630]},{modifiers[2631]},{modifiers[2632]},
			}},
			{EffectID::moduleBonusOmnidirectionalTrackingLink, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[2633]},{modifiers[2634]},{modifiers[2635]},{modifiers[2636]},{modifiers[2637]},{modifiers[2638]},{modifiers[2639]},{modifiers[2640]},{modifiers[2641]},{modifiers[2642]},{modifiers[2643]},{modifiers[2644]},{modifiers[2645]},
			}},
			{EffectID::moduleBonusOmnidirectionalTrackingLinkOverload, MetaInfo::Effect::Category::overloaded, false, false, {
				{modifiers[2011]},{modifiers[2012]},{modifiers[2013]},{modifiers[2232]},{modifiers[2233]},
			}},
			{EffectID::moduleBonusOmnidirectionalTrackingEnhancer, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2633]},{modifiers[2634]},{modifiers[2635]},{modifiers[2636]},{modifiers[2637]},{modifiers[2638]},{modifiers[2639]},{modifiers[2640]},{modifiers[2641]},{modifiers[2642]},{modifiers[2643]},{modifiers[2644]},{modifiers[2645]},
			}},
			{EffectID::skillBonusFighters, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2646]},{modifiers[2647]},{modifiers[2648]},
			}},
			{EffectID::skillBonusLightFighters, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2649]},
			}},
			{EffectID::skillBonusSupportFightersShield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2650]},
			}},
			{EffectID::skillBonusHeavyFighters, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2651]},{modifiers[2652]},{modifiers[2653]},
			}},
			{EffectID::citadelRigBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2654]},{modifiers[2655]},{modifiers[2656]},{modifiers[2657]},{modifiers[2658]},{modifiers[2659]},{modifiers[2660]},{modifiers[2661]},{modifiers[2662]},{modifiers[2663]},
			}},
			{EffectID::moduleBonusFighterSupportUnit, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[2664]},{modifiers[2665]},{modifiers[2666]},{modifiers[2667]},{modifiers[2668]},{modifiers[2669]},
			}},
			{EffectID::moduleBonusNetworkedSensorArray, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[232]},{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},{modifiers[1423]},{modifiers[1424]},{modifiers[2670]},{modifiers[2671]},{modifiers[2672]},{modifiers[2673]},{modifiers[2674]},{modifiers[2675]},{modifiers[2676]},{modifiers[2677]},{modifiers[2678]},{modifiers[2679]},{modifiers[2680]},
			}},
			{EffectID::citadelServiceFuelBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2681]},{modifiers[2682]},
			}},
			{EffectID::skillMultiplierFighterHangarSize, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2683]},
			}},
			{EffectID::skillBonusFighterHangarManagement, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2684]},
			}},
			{EffectID::skillBonusCapitalAutocannonSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2685]},
			}},
			{EffectID::skillBonusCapitalArtillerySpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2686]},
			}},
			{EffectID::skillBonusCapitalBlasterSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2687]},
			}},
			{EffectID::skillBonusCapitalRailgunSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2688]},
			}},
			{EffectID::skillBonusCapitalPulseLaserSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2689]},
			}},
			{EffectID::skillBonusCapitalBeamLaserSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2690]},
			}},
			{EffectID::skillBonusXLCruiseMissileSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2691]},
			}},
			{EffectID::skillBonusXLTorpedoSpecialization, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2692]},
			}},
			{EffectID::shipBonusRole2LogisticDroneRepAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2693]},{modifiers[2694]},{modifiers[2695]},
			}},
			{EffectID::moduleBonusTriageModule, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[33]},{modifiers[616]},{modifiers[617]},{modifiers[1422]},{modifiers[1423]},{modifiers[1424]},{modifiers[1425]},{modifiers[1426]},{modifiers[1427]},{modifiers[1428]},{modifiers[1429]},{modifiers[1430]},{modifiers[2670]},{modifiers[2671]},{modifiers[2672]},{modifiers[2673]},{modifiers[2674]},{modifiers[2675]},{modifiers[2676]},{modifiers[2696]},{modifiers[2697]},{modifiers[2698]},{modifiers[2699]},{modifiers[2700]},{modifiers[2701]},{modifiers[2702]},{modifiers[2703]},{modifiers[2704]},{modifiers[2705]},{modifiers[2706]},{modifiers[2707]},{modifiers[2708]},{modifiers[2709]},{modifiers[2710]},{modifiers[2711]},{modifiers[2712]},{modifiers[2713]},{modifiers[2714]},{modifiers[2715]},{modifiers[2716]},{modifiers[2717]},{modifiers[2718]},{modifiers[2719]},
			}},
			{EffectID::moduleBonusSiegeModule, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[616]},{modifiers[617]},{modifiers[1422]},{modifiers[1423]},{modifiers[1424]},{modifiers[1425]},{modifiers[1426]},{modifiers[1427]},{modifiers[1428]},{modifiers[1429]},{modifiers[2716]},{modifiers[2717]},{modifiers[2718]},{modifiers[2719]},{modifiers[2720]},{modifiers[2721]},{modifiers[2722]},{modifiers[2723]},{modifiers[2724]},{modifiers[2725]},{modifiers[2726]},{modifiers[2727]},{modifiers[2728]},{modifiers[2729]},{modifiers[2730]},{modifiers[2731]},{modifiers[2732]},{modifiers[2733]},{modifiers[2734]},{modifiers[2735]},{modifiers[2736]},{modifiers[2737]},{modifiers[2738]},{modifiers[2739]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierAmarr, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2740]},{modifiers[2741]},{modifiers[2742]},{modifiers[2743]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierCaldari, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2744]},{modifiers[2745]},{modifiers[2746]},{modifiers[2747]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierGallente, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2748]},{modifiers[2749]},{modifiers[2750]},{modifiers[2751]},
			}},
			{EffectID::skillMultiplierShipBonusCarrierMinmatar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2752]},{modifiers[2753]},{modifiers[2754]},{modifiers[2755]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierAmarr, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2756]},{modifiers[2757]},{modifiers[2758]},{modifiers[2759]},{modifiers[2760]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierCaldari, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2761]},{modifiers[2762]},{modifiers[2763]},{modifiers[2764]},{modifiers[2765]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierGallente, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2766]},{modifiers[2767]},{modifiers[2768]},{modifiers[2769]},{modifiers[2770]},
			}},
			{EffectID::skillMultiplierShipBonusSupercarrierMinmatar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2771]},{modifiers[2772]},{modifiers[2773]},{modifiers[2774]},{modifiers[2775]},
			}},
			{EffectID::shipBonusSupercarrierA3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2776]},
			}},
			{EffectID::shipBonusSupercarrierC3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2777]},
			}},
			{EffectID::shipBonusSupercarrierG3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2778]},
			}},
			{EffectID::shipBonusSupercarrierM3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2779]},
			}},
			{EffectID::shipBonusCarrierA4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2780]},{modifiers[2781]},{modifiers[2782]},{modifiers[2783]},{modifiers[2784]},{modifiers[2785]},{modifiers[2786]},{modifiers[2787]},{modifiers[2788]},{modifiers[2789]},
			}},
			{EffectID::shipBonusCarrierC4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2790]},{modifiers[2791]},{modifiers[2792]},{modifiers[2793]},{modifiers[2794]},{modifiers[2795]},{modifiers[2796]},{modifiers[2797]},{modifiers[2798]},{modifiers[2799]},
			}},
			{EffectID::shipBonusCarrierG4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2800]},{modifiers[2801]},{modifiers[2802]},{modifiers[2803]},{modifiers[2804]},{modifiers[2805]},{modifiers[2806]},{modifiers[2807]},{modifiers[2808]},{modifiers[2809]},
			}},
			{EffectID::shipBonusCarrierM4WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2810]},{modifiers[2811]},{modifiers[2812]},{modifiers[2813]},{modifiers[2814]},{modifiers[2815]},{modifiers[2816]},{modifiers[2817]},{modifiers[2818]},{modifiers[2819]},
			}},
			{EffectID::shipBonusCarrierA1ArmorResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2820]},{modifiers[2821]},{modifiers[2822]},{modifiers[2823]},
			}},
			{EffectID::shipBonusCarrierC1ShieldResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2824]},{modifiers[2825]},{modifiers[2826]},{modifiers[2827]},
			}},
			{EffectID::shipBonusCarrierG1FighterDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2828]},{modifiers[2829]},{modifiers[2830]},
			}},
			{EffectID::shipBonusCarrierM1FighterDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2831]},{modifiers[2832]},{modifiers[2833]},
			}},
			{EffectID::shipBonusSupercarrierA1FighterDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2834]},{modifiers[2835]},{modifiers[2836]},
			}},
			{EffectID::shipBonusSupercarrierC1FighterDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2837]},{modifiers[2838]},{modifiers[2839]},
			}},
			{EffectID::shipBonusSupercarrierG1FighterDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2840]},{modifiers[2841]},{modifiers[2842]},
			}},
			{EffectID::shipBonusSupercarrierM1FighterDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2843]},{modifiers[2844]},{modifiers[2845]},
			}},
			{EffectID::shipBonusSupercarrierA5WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2846]},{modifiers[2847]},{modifiers[2848]},{modifiers[2849]},{modifiers[2850]},{modifiers[2851]},{modifiers[2852]},{modifiers[2853]},{modifiers[2854]},{modifiers[2855]},
			}},
			{EffectID::shipBonusSupercarrierC5WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2856]},{modifiers[2857]},{modifiers[2858]},{modifiers[2859]},{modifiers[2860]},{modifiers[2861]},{modifiers[2862]},{modifiers[2863]},{modifiers[2864]},{modifiers[2865]},
			}},
			{EffectID::shipBonusSupercarrierG5WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2866]},{modifiers[2867]},{modifiers[2868]},{modifiers[2869]},{modifiers[2870]},{modifiers[2871]},{modifiers[2872]},{modifiers[2873]},{modifiers[2874]},{modifiers[2875]},
			}},
			{EffectID::shipBonusSupercarrierM5WarfareLinksBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2876]},{modifiers[2877]},{modifiers[2878]},{modifiers[2879]},{modifiers[2880]},{modifiers[2881]},{modifiers[2882]},{modifiers[2883]},{modifiers[2884]},{modifiers[2885]},
			}},
			{EffectID::shipBonusSupercarrierC2AfterburnerBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2886]},
			}},
			{EffectID::shipBonusSupercarrierA2FighterApplicationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2887]},{modifiers[2888]},
			}},
			{EffectID::shipBonusSupercarrierRole1NumWarfareLinks, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2889]},{modifiers[2890]},
			}},
			{EffectID::shipBonusSupercarrierRole2ArmorShieldModuleBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2891]},{modifiers[2892]},
			}},
			{EffectID::shipBonusSupercarrierA4BurstProjectorBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2893]},
			}},
			{EffectID::shipBonusSupercarrierC4BurstProjectorBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2894]},
			}},
			{EffectID::shipBonusSupercarrierG4BurstProjectorBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2895]},
			}},
			{EffectID::shipBonusSupercarrierM4BurstProjectorBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2896]},
			}},
			{EffectID::shipBonusCarrierRole1NumWarfareLinks, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2889]},{modifiers[2890]},
			}},
			{EffectID::shipBonusDreadnoughtC3ReloadBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2897]},
			}},
			{EffectID::shipBonusSupercarrierA2ArmorResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2898]},{modifiers[2899]},{modifiers[2900]},{modifiers[2901]},
			}},
			{EffectID::shipBonusSupercarrierC2ShieldResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2902]},{modifiers[2903]},{modifiers[2904]},{modifiers[2905]},
			}},
			{EffectID::shipBonusSupercarrierG2FighterHitpoints, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2906]},
			}},
			{EffectID::shipBonusSupercarrierM2FighterVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2907]},
			}},
			{EffectID::shipBonusCarrierA2SupportFighterBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2908]},{modifiers[2909]},
			}},
			{EffectID::shipBonusCarrierC2SupportFighterBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2910]},{modifiers[2911]},
			}},
			{EffectID::shipBonusCarrierG2SupportFighterBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2912]},{modifiers[2913]},
			}},
			{EffectID::shipBonusCarrierM2SupportFighterBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2914]},{modifiers[2915]},
			}},
			{EffectID::scriptResistanceBonusBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2916]},{modifiers[2917]},{modifiers[2918]},{modifiers[2919]},
			}},
			{EffectID::skillMultiplierShipBonusTitanAmarr, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2920]},{modifiers[2921]},{modifiers[2922]},{modifiers[2923]},
			}},
			{EffectID::skillMultiplierShipBonusTitanCaldari, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2924]},{modifiers[2925]},{modifiers[2926]},{modifiers[2927]},{modifiers[2928]},
			}},
			{EffectID::skillMultiplierShipBonusTitanGallente, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2929]},{modifiers[2930]},{modifiers[2931]},{modifiers[2932]},
			}},
			{EffectID::skillMultiplierShipBonusTitanMinmatar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2933]},{modifiers[2934]},{modifiers[2935]},{modifiers[2936]},
			}},
			{EffectID::shipBonusTitanA1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2937]},
			}},
			{EffectID::shipBonusTitanC1KinDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2938]},{modifiers[2939]},{modifiers[2940]},
			}},
			{EffectID::shipBonusTitanG1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2941]},
			}},
			{EffectID::shipBonusTitanM1DamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2942]},
			}},
			{EffectID::shipBonusTitanC2ROFBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2943]},{modifiers[2944]},{modifiers[2945]},
			}},
			{EffectID::shipBonusSupercarrierA4FighterApplicationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2946]},{modifiers[2947]},
			}},
			{EffectID::shipBonusRole1NumWarfareLinks, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2889]},{modifiers[2890]},
			}},
			{EffectID::shipBonusRole2ArmorPlatesShieldExtendersBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2891]},{modifiers[2892]},
			}},
			{EffectID::skillBonusDoomsdayRapidFiring, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2948]},
			}},
			{EffectID::shipBonusTitanA3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2949]},
			}},
			{EffectID::shipBonusTitanC3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2950]},
			}},
			{EffectID::shipBonusTitanG3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2951]},
			}},
			{EffectID::shipBonusTitanM3WarpStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2952]},
			}},
			{EffectID::shipModuleAncillaryRemoteArmorRepairer, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[206]},
			}},
			{EffectID::shipModuleAncillaryRemoteShieldBooster, MetaInfo::Effect::Category::target, false, true, {
				{modifiers[3]},
			}},
			{EffectID::shipBonusTitanA2CapNeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2953]},
			}},
			{EffectID::shipBonusTitanG2ROFBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2954]},
			}},
			{EffectID::shipBonusTitanM2ROFBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2955]},
			}},
			{EffectID::shipBonusRole3XLTorpdeoVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2956]},
			}},
			{EffectID::shipBonusTitanC5AllDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2957]},{modifiers[2958]},{modifiers[2959]},{modifiers[2960]},{modifiers[2961]},{modifiers[2962]},{modifiers[2963]},{modifiers[2964]},{modifiers[2965]},
			}},
			{EffectID::moduleBonusBastionModule, MetaInfo::Effect::Category::active, true, false, {
				{modifiers[431]},{modifiers[616]},{modifiers[617]},{modifiers[639]},{modifiers[640]},{modifiers[641]},{modifiers[642]},{modifiers[660]},{modifiers[661]},{modifiers[662]},{modifiers[663]},{modifiers[664]},{modifiers[665]},{modifiers[666]},{modifiers[667]},{modifiers[668]},{modifiers[669]},{modifiers[670]},{modifiers[671]},{modifiers[1423]},{modifiers[1424]},{modifiers[1426]},{modifiers[1427]},{modifiers[1428]},{modifiers[1429]},{modifiers[1775]},{modifiers[2720]},{modifiers[2966]},{modifiers[2967]},{modifiers[2968]},{modifiers[2969]},{modifiers[2970]},{modifiers[2971]},{modifiers[2972]},{modifiers[2973]},{modifiers[2974]},{modifiers[2975]},{modifiers[2976]},{modifiers[2977]},
			}},
			{EffectID::higgsWarpBubbleImmuneRemoval, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2978]},
			}},
			{EffectID::shipBonusCarrierM3FighterVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2979]},
			}},
			{EffectID::shipBonusCarrierG3FighterHitpoints, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2980]},
			}},
			{EffectID::skillBonusDroneInterfacing, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[216]},{modifiers[615]},{modifiers[2646]},{modifiers[2647]},{modifiers[2648]},
			}},
			{EffectID::skillBonusDroneSharpshooting, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[578]},{modifiers[2981]},{modifiers[2982]},{modifiers[2983]},
			}},
			{EffectID::skillBonusDroneDurability, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[581]},{modifiers[2984]},{modifiers[2985]},{modifiers[2986]},
			}},
			{EffectID::skillMultiplierMaxVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2987]},
			}},
			{EffectID::skillBonusDroneNavigation, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2988]},{modifiers[2989]},
			}},
			{EffectID::skillMultiplierShieldBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2990]},
			}},
			{EffectID::moduleBonusCapitalDroneDurabilityEnhancer, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[579]},{modifiers[580]},{modifiers[581]},{modifiers[738]},{modifiers[2471]},
			}},
			{EffectID::moduleBonusCapitalDroneScopeChip, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[578]},{modifiers[738]},{modifiers[2981]},{modifiers[2982]},{modifiers[2983]},
			}},
			{EffectID::moduleBonusCapitalDroneSpeedAugmentor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[577]},{modifiers[738]},{modifiers[2475]},
			}},
			{EffectID::structureCombatRigSecurityModification, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2991]},{modifiers[2992]},{modifiers[2993]},{modifiers[2994]},{modifiers[2995]},{modifiers[2996]},{modifiers[2997]},{modifiers[2998]},{modifiers[2999]},{modifiers[3000]},
			}},
			{EffectID::structureReprocessingRigSecurityModification, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3001]},
			}},
			{EffectID::structureRigAsteroidOreYield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3002]},
			}},
			{EffectID::structureRigMoonOreYield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3003]},
			}},
			{EffectID::structureRigCalAmarrIceYield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3004]},
			}},
			{EffectID::structureRigGalMinIceYield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3005]},
			}},
			{EffectID::structureRigIceYield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3006]},
			}},
			{EffectID::skillStructureDoomsdayDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3007]},
			}},
			{EffectID::shipBonusRole3NumWarfareLinks, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3008]},{modifiers[3009]},
			}},
			{EffectID::structureModuleEffectStasisWebifier, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectTargetPainter, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectRemoteSensorDampener, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectECM, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::structureModuleEffectWeaponDisruption, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::npcEntityRemoteArmorRepairer, MetaInfo::Effect::Category::target, false, true, {
				
			}},
			{EffectID::npcEntityRemoteShieldBooster, MetaInfo::Effect::Category::target, false, true, {
				
			}},
			{EffectID::npcEntityRemoteHullRepairer, MetaInfo::Effect::Category::target, false, true, {
				
			}},
			{EffectID::remoteWebifierEntity, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::entityEnergyNeutralizerFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::remoteTargetPaintEntity, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::remoteSensorDampEntity, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::npcEntityWeaponDisruptor, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::entityECMFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::starbaseEnergyNeutralizerFalloff, MetaInfo::Effect::Category::target, true, false, {
				
			}},
			{EffectID::rigDrawbackReductionArmor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3010]},{modifiers[3011]},
			}},
			{EffectID::rigDrawbackReductionAstronautics, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3012]},{modifiers[3013]},
			}},
			{EffectID::rigDrawbackReductionDrones, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3014]},
			}},
			{EffectID::rigDrawbackReductionElectronic, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3015]},{modifiers[3016]},{modifiers[3017]},
			}},
			{EffectID::rigDrawbackReductionProjectile, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3018]},
			}},
			{EffectID::rigDrawbackReductionEnergyWeapon, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3019]},
			}},
			{EffectID::rigDrawbackReductionHybrid, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3020]},
			}},
			{EffectID::rigDrawbackReductionLauncher, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3021]},
			}},
			{EffectID::rigDrawbackReductionShield, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3022]},
			}},
			{EffectID::setBonusAsklepian, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3023]},
			}},
			{EffectID::armorRepairAmountBonusSubcap, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3024]},
			}},
			{EffectID::shipBonusRole1CapitalHybridDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3025]},
			}},
			{EffectID::shipBonusDreadnoughtM1WebStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3026]},
			}},
			{EffectID::shipBonusRole3CapitalHybridDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3027]},
			}},
			{EffectID::shipBonusTitanM1WebStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3028]},
			}},
			{EffectID::shipBonusSupercarrierM1BurstProjectorWebBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3029]},
			}},
			{EffectID::ECMBurstJammer, MetaInfo::Effect::Category::active, true, false, {
				
			}},
			{EffectID::ECMBurstJammerQA, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::pacifierDebuffQA, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::roleBonusIceOreMiningDurationCap, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3030]},{modifiers[3031]},{modifiers[3032]},{modifiers[3033]},
			}},
			{EffectID::logisticSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3034]},
			}},
			{EffectID::moduleBonusIndustrialInvulnerability, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::shipBonusDroneRepairMC1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3035]},{modifiers[3036]},{modifiers[3037]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairOptimalFalloff1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3038]},{modifiers[3039]},
			}},
			{EffectID::roleBonusRemoteArmorRepairOptimalFalloff, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3040]},{modifiers[3041]},
			}},
			{EffectID::shipBonusCloakCpuMC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3042]},
			}},
			{EffectID::eliteBonusLogisticRemoteArmorRepairDuration3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3043]},
			}},
			{EffectID::shipBonusSETFalloffAF2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3044]},
			}},
			{EffectID::shipBonusCloakCpuMF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3045]},
			}},
			{EffectID::eliteBonusCoverOpsNOSNeutFalloff1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3046]},{modifiers[3047]},
			}},
			{EffectID::moduleBonusMicrowarpdrive, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[380]},{modifiers[570]},{modifiers[3048]},
			}},
			{EffectID::moduleBonusAfterburner, MetaInfo::Effect::Category::active, false, false, {
				{modifiers[570]},{modifiers[3048]},
			}},
			{EffectID::moduleBonusWarfareLinkArmor, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkShield, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkSkirmish, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkInfo, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::moduleBonusWarfareLinkMining, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::chargeBonusWarfareCharge, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3049]},{modifiers[3050]},{modifiers[3051]},{modifiers[3052]},{modifiers[3053]},{modifiers[3054]},{modifiers[3055]},{modifiers[3056]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3057]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS4, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3058]},
			}},
			{EffectID::moduleTitanEffectGenerator, MetaInfo::Effect::Category::active, false, false, {
				
			}},
			{EffectID::engComplexServiceFuelBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3059]},{modifiers[3060]},
			}},
			{EffectID::miningDroneSpecBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3061]},{modifiers[3062]},
			}},
			{EffectID::iceHarvestingDroneOperationDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3063]},
			}},
			{EffectID::iceHarvestingDroneSpecBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3064]},{modifiers[3065]},
			}},
			{EffectID::spatialPhenomenaGenerationDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3066]},
			}},
			{EffectID::commandProcessorEffect, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[455]},{modifiers[649]},
			}},
			{EffectID::areaOfEffectSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3067]},
			}},
			{EffectID::commandBurstAoEBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3068]},
			}},
			{EffectID::armoredCommandDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3069]},
			}},
			{EffectID::shieldCommandDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3070]},
			}},
			{EffectID::informationCommandDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3071]},
			}},
			{EffectID::skirmishCommandDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3072]},
			}},
			{EffectID::miningForemanDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3073]},
			}},
			{EffectID::commandBurstStrengthSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3074]},
			}},
			{EffectID::armoredCommandStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3075]},{modifiers[3076]},{modifiers[3077]},{modifiers[3078]},
			}},
			{EffectID::shieldCommandStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3079]},{modifiers[3080]},{modifiers[3081]},{modifiers[3082]},
			}},
			{EffectID::informationCommandStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3083]},{modifiers[3084]},{modifiers[3085]},{modifiers[3086]},
			}},
			{EffectID::skirmishCommandStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3087]},{modifiers[3088]},{modifiers[3089]},{modifiers[3090]},
			}},
			{EffectID::miningForemanStrengthBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3091]},{modifiers[3092]},{modifiers[3093]},{modifiers[3094]},
			}},
			{EffectID::reloadTimeSkillBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3095]},
			}},
			{EffectID::commandBurstReloadTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3096]},
			}},
			{EffectID::commandBurstAoERoleBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3097]},
			}},
			{EffectID::industrialCommandShipSkillLevelMultiplierICS5, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3098]},
			}},
			{EffectID::shieldCommandBurstBonusICS3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3099]},{modifiers[3100]},{modifiers[3101]},{modifiers[3102]},{modifiers[3103]},
			}},
			{EffectID::shipBonusDroneHPDamageMiningICS4, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3104]},{modifiers[3105]},{modifiers[3106]},{modifiers[3107]},{modifiers[3108]},
			}},
			{EffectID::shipBonusDroneIceHarvestingICS5, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3109]},
			}},
			{EffectID::industrialBonusDroneDamage, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3110]},
			}},
			{EffectID::shipBonusDroneIceHarvestingRole, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3111]},
			}},
			{EffectID::oreCapitalShipSkillMultiplier5, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3112]},
			}},
			{EffectID::shipBonusDroneHPDamageMiningORECapital4, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[933]},{modifiers[934]},{modifiers[935]},{modifiers[936]},{modifiers[3113]},
			}},
			{EffectID::miningForemanBurstBonusORECapital2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3114]},{modifiers[3115]},{modifiers[3116]},{modifiers[3117]},{modifiers[3118]},
			}},
			{EffectID::shieldCommandBurstBonusORECapital3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3119]},{modifiers[3120]},{modifiers[3121]},{modifiers[3122]},{modifiers[3123]},
			}},
			{EffectID::shipBonusDroneIceHarvestingORECapital5, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3124]},
			}},
			{EffectID::shipModeSHTDamagePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3125]},
			}},
			{EffectID::shipModeSPTDamagePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3126]},
			}},
			{EffectID::shipModeSETDamagePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3127]},
			}},
			{EffectID::shipModeSmallMissileDamagePostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3128]},{modifiers[3129]},{modifiers[3130]},{modifiers[3131]},{modifiers[3132]},{modifiers[3133]},{modifiers[3134]},{modifiers[3135]},
			}},
			{EffectID::modeDampTDResistsPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3136]},{modifiers[3137]},
			}},
			{EffectID::modeMWDandABBoostPostDiv, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3138]},{modifiers[3139]},
			}},
			{EffectID::rigEquipmentManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3140]},
			}},
			{EffectID::rigEquipmentManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3141]},
			}},
			{EffectID::invulnerabilityCoreDurationBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3142]},{modifiers[3143]},
			}},
			{EffectID::rigAmmoManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3144]},
			}},
			{EffectID::rigAmmoManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3145]},
			}},
			{EffectID::rigDroneManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3146]},
			}},
			{EffectID::rigDroneManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3147]},
			}},
			{EffectID::rigSmallshipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3148]},
			}},
			{EffectID::rigSmallshipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3149]},
			}},
			{EffectID::rigMediumshipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3150]},
			}},
			{EffectID::rigMediumshipsManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3151]},
			}},
			{EffectID::rigLargeshipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3152]},
			}},
			{EffectID::rigLargeshipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3153]},
			}},
			{EffectID::rigAdvSmshipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3154]},
			}},
			{EffectID::rigAdvSmshipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3155]},
			}},
			{EffectID::rigAdvMedShipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3156]},
			}},
			{EffectID::rigAdvMedShipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3157]},
			}},
			{EffectID::rigAdvLarShipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3158]},
			}},
			{EffectID::rigAdvLarShipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3159]},
			}},
			{EffectID::rigAdvComponentManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3160]},
			}},
			{EffectID::rigAdvComponentManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3161]},
			}},
			{EffectID::rigBasCapCompManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3162]},
			}},
			{EffectID::rigBasCapCompManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3163]},
			}},
			{EffectID::rigStructureManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3164]},
			}},
			{EffectID::rigStructureManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3165]},
			}},
			{EffectID::rigInventionCostBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3166]},
			}},
			{EffectID::rigInventionTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3167]},
			}},
			{EffectID::rigMEResearchCostBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3168]},
			}},
			{EffectID::rigMEResearchTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3169]},
			}},
			{EffectID::rigTEResearchCostBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3170]},
			}},
			{EffectID::rigTEResearchTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3171]},
			}},
			{EffectID::rigCopyCostBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3172]},
			}},
			{EffectID::rigCopyTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3173]},
			}},
			{EffectID::rigCapShipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3174]},
			}},
			{EffectID::rigCapShipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3175]},
			}},
			{EffectID::rigAllShipManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3176]},
			}},
			{EffectID::rigAllShipManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3177]},
			}},
			{EffectID::structureEngineeringRigSecurityModification, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3178]},{modifiers[3179]},{modifiers[3180]},{modifiers[3181]},
			}},
			{EffectID::skillMultiplierMissileVelocityBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3182]},
			}},
			{EffectID::skillMultiplierDefenderMissileVelocity, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3183]},
			}},
			{EffectID::shipBonusCommandDestroyerRole1DefenderBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3184]},
			}},
			{EffectID::shipModuleFocusedWarpScramblingScript, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[8]},{modifiers[2111]},{modifiers[2112]},{modifiers[3185]},{modifiers[3186]},
			}},
			{EffectID::shipModuleFocusedWarpDisruptionScript, MetaInfo::Effect::Category::target, true, false, {
				{modifiers[8]},{modifiers[2112]},{modifiers[3186]},
			}},
			{EffectID::chargeRateStructureModulesMultiply, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3187]},
			}},
			{EffectID::shipBonusRole3CapitalEnergyDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3188]},
			}},
			{EffectID::shipBonusTitanM1WebRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3189]},
			}},
			{EffectID::shipBonusTitanA1EnergyWarfareAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3190]},{modifiers[3191]},
			}},
			{EffectID::shipBonusDreadnoughtA1EnergyWarfareAmountBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3192]},{modifiers[3193]},
			}},
			{EffectID::shipBonusDreadnoughtM1WebRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3194]},
			}},
			{EffectID::shipBonusForceAuxiliaryA1NosferatuRangeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3195]},{modifiers[3196]},
			}},
			{EffectID::shipBonusForceAuxiliaryA1NosferatuDrainAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3197]},
			}},
			{EffectID::shipBonusRole4NosferatuCPUBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3198]},
			}},
			{EffectID::shipBonusRole5RemoteArmorRepairPowergridBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3199]},
			}},
			{EffectID::shipBonusRole5CapitalRemoteArmorRepairPowergridBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3200]},
			}},
			{EffectID::shipBonusForceAuxiliaryM1RemoteArmorRepairDuration, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2623]},
			}},
			{EffectID::eliteBonusCoverOpsWarpVelocity1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3201]},
			}},
			{EffectID::shipBonusSmallMissileFlightTimeCF1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3202]},{modifiers[3203]},
			}},
			{EffectID::shipBonusSPTRoFMF, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3204]},
			}},
			{EffectID::roleBonusConcordSecGain, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3205]},
			}},
			{EffectID::concordIntermediateSecStatus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3206]},
			}},
			{EffectID::concordAssignTankBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3207]},
			}},
			{EffectID::concordSecStatusTankBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3208]},{modifiers[3209]},
			}},
			{EffectID::eliteReconStasisWebBonus1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3210]},
			}},
			{EffectID::eliteBonusReconWarpVelocity3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3211]},
			}},
			{EffectID::shipBonusMedMissileFlightTimeCC2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3212]},{modifiers[3213]},
			}},
			{EffectID::blackOpsSkillMultiplier3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3214]},
			}},
			{EffectID::blackOpsSkillMultiplier4, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3215]},
			}},
			{EffectID::eliteBonusBlackOpsWarpVelocity1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3216]},
			}},
			{EffectID::eliteBonusBlackOpsScramblerRange4, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3217]},
			}},
			{EffectID::eliteBonusBlackOpsWebRange3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3218]},
			}},
			{EffectID::shipBonusLauncherRoF2CB, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[555]},{modifiers[556]},{modifiers[1965]},
			}},
			{EffectID::shipBonusLargeMissileFlightTimeCB1, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3219]},{modifiers[3220]},
			}},
			{EffectID::shipBonusForceAuxiliaryM2LocalRepairAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3221]},{modifiers[3222]},
			}},
			{EffectID::rigThukkerBasCapCompManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3223]},
			}},
			{EffectID::rigAdvCapComponentManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3224]},
			}},
			{EffectID::rigAdvCapComponentManufactureTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3225]},
			}},
			{EffectID::rigThukkerAdvCapCompManufactureMaterialBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3226]},
			}},
			{EffectID::reactionTimeBonusPostPercentManufactureTimeMultiplierChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3227]},
			}},
			{EffectID::reactionSkillBoostManufacturingTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3228]},
			}},
			{EffectID::massReactionSkillLevelModAddReactionSlotLimitChar, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3229]},
			}},
			{EffectID::subsystemEnergyNeutFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3230]},{modifiers[3231]},{modifiers[3232]},{modifiers[3233]},
			}},
			{EffectID::subsystemMETFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3234]},{modifiers[3235]},
			}},
			{EffectID::subsystemMHTFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3236]},{modifiers[3237]},
			}},
			{EffectID::subsystemMPTFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3238]},{modifiers[3239]},
			}},
			{EffectID::subsystemMRARFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3240]},
			}},
			{EffectID::subsystemMRSBFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3241]},
			}},
			{EffectID::subsystemMMissileFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3242]},{modifiers[3243]},{modifiers[3244]},{modifiers[3245]},{modifiers[3246]},{modifiers[3247]},
			}},
			{EffectID::shipModuleNonRepeatingShieldHardener, MetaInfo::Effect::Category::active, true, false, {
				{modifiers[590]},{modifiers[591]},{modifiers[592]},{modifiers[593]},
			}},
			{EffectID::shipModuleNonRepeatingArmorHardener, MetaInfo::Effect::Category::active, true, false, {
				{modifiers[586]},{modifiers[587]},{modifiers[588]},{modifiers[589]},
			}},
			{EffectID::strategicCruiserMinmatarSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3248]},
			}},
			{EffectID::strategicCruiserAmarrSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3249]},
			}},
			{EffectID::strategicCruiserCaldariSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3250]},
			}},
			{EffectID::strategicCruiserGallenteSkillLevel2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3251]},
			}},
			{EffectID::shipBonusStrategicCruiserCaldariNaniteRepairTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3252]},
			}},
			{EffectID::shipBonusStrategicCruiserAmarrNaniteRepairTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3253]},
			}},
			{EffectID::shipBonusStrategicCruiserGallenteNaniteRepairTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3254]},
			}},
			{EffectID::shipBonusStrategicCruiserMinmatarNaniteRepairTime2, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3255]},
			}},
			{EffectID::subsystemSkillLevelAmarrDefensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3256]},
			}},
			{EffectID::subsystemSkillLevelAmarrEngineering3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3257]},
			}},
			{EffectID::subsystemSkillLevelCaldariEngineering3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3258]},
			}},
			{EffectID::subsystemSkillLevelCaldariDefensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3259]},
			}},
			{EffectID::subsystemSkillLevelGallenteEngineering3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3260]},
			}},
			{EffectID::subsystemSkillLevelGallenteDefensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3261]},
			}},
			{EffectID::subsystemSkillLevelMinmatarEngineering3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3262]},
			}},
			{EffectID::subsystemSkillLevelMinmatarDefensive3, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3263]},
			}},
			{EffectID::structureHPBonusAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3264]},
			}},
			{EffectID::subSystemBonusAmarrDefensive2ScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3265]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive1HMLHAMVelo, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3266]},{modifiers[3267]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive3MissileExpVelo, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3268]},
			}},
			{EffectID::subsystemBonusGallenteOffensive2DroneVeloTracking, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3269]},{modifiers[3270]},
			}},
			{EffectID::subsystemBonusAmarrPropulsionWarpCapacitor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3271]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsionWarpCapacitor, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3272]},
			}},
			{EffectID::subsystemBonusCaldariPropulsion2PropModHeatBenefit, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3273]},{modifiers[3274]},
			}},
			{EffectID::subsystemBonusGallentePropulsion2PropModHeatBenefit, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3275]},{modifiers[3276]},
			}},
			{EffectID::subsystemBonusAmarrCore2EnergyResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3277]},
			}},
			{EffectID::subsystemBonusMinmatarCore2EnergyResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3278]},
			}},
			{EffectID::subsystemBonusGallenteCore2EnergyResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3279]},
			}},
			{EffectID::subsystemBonusCaldariCore2EnergyResistance, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3280]},
			}},
			{EffectID::shipMaxLockedTargetsBonusAddPassive, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[33]},
			}},
			{EffectID::subsystemBonusAmarrCore3EnergyWarHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3281]},{modifiers[3282]},
			}},
			{EffectID::subsystemBonusMinmatarCore3StasisWebHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3283]},
			}},
			{EffectID::subsystemBonusGallenteCore3WarpScramHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3284]},
			}},
			{EffectID::subsystemBonusCaldariCore3ECMHeatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3285]},
			}},
			{EffectID::subsystemBonusAmarrDefensive2HardenerHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3286]},{modifiers[3287]},
			}},
			{EffectID::subsystemBonusGallenteDefensive2HardenerHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3288]},{modifiers[3289]},
			}},
			{EffectID::subsystemBonusCaldariDefensive2HardenerHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3290]},
			}},
			{EffectID::subsystemBonusMinmatarDefensive2HardenerHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3291]},{modifiers[3292]},{modifiers[3293]},
			}},
			{EffectID::subsystemBonusAmarrDefensive3ArmorRepHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3294]},{modifiers[3295]},
			}},
			{EffectID::subsystemBonusGallenteDefensive3ArmorRepHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3296]},{modifiers[3297]},
			}},
			{EffectID::subsystemBonusCaldariDefensive3ShieldBoostHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3298]},{modifiers[3299]},
			}},
			{EffectID::subsystemBonusMinmatarDefensive3LocalRepHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3300]},{modifiers[3301]},{modifiers[3302]},{modifiers[3303]},
			}},
			{EffectID::subSystemBonusCaldariDefensive2ScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3304]},
			}},
			{EffectID::subSystemBonusGallenteDefensive2ScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3305]},
			}},
			{EffectID::subSystemBonusMinmatarDefensive2ScanProbeStrength, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3306]},
			}},
			{EffectID::mediumRemoteRepFittingAdjustment, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3307]},{modifiers[3308]},
			}},
			{EffectID::subsystemBonusCommandBurstFittingReduction, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3309]},{modifiers[3310]},
			}},
			{EffectID::subsystemRemoteShieldBoostFalloffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3311]},{modifiers[3312]},
			}},
			{EffectID::subsystemRemoteArmorRepairerOptimalBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3313]},{modifiers[3314]},
			}},
			{EffectID::subsystemRemoteArmorRepairerFalloffBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3315]},{modifiers[3316]},
			}},
			{EffectID::subsystemBonusAmarrOffensive3RemoteArmorRepairHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3317]},
			}},
			{EffectID::subsystemBonusGallenteOffensive3RemoteArmorRepairHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3318]},
			}},
			{EffectID::subsystemBonusCaldariOffensive3RemoteShieldBoosterHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3319]},
			}},
			{EffectID::subsystemBonusMinmatarOffensive3RemoteRepHeat, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3320]},{modifiers[3321]},
			}},
			{EffectID::subsystemBonusAmarrPropulsion2WarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3322]},
			}},
			{EffectID::subsystemBonusMinmatarPropulsion2WarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3323]},
			}},
			{EffectID::subsystemBonusGallentePropulsionWarpSpeed, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3324]},
			}},
			{EffectID::surveyProbeExplosionDelayOnline, MetaInfo::Effect::Category::passive, false, false, {
				{modifiers[3325]},
			}},
			{EffectID::rigReactionHybTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3326]},
			}},
			{EffectID::rigReactionHybMatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3327]},
			}},
			{EffectID::rigReactionCompTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3328]},
			}},
			{EffectID::rigReactionCompMatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3329]},
			}},
			{EffectID::rigReactionBioTimeBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3330]},
			}},
			{EffectID::rigReactionBioMatBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3331]},
			}},
			{EffectID::structureReactionRigSecurityModification, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3332]},{modifiers[3333]},
			}},
			{EffectID::rigMoonSpewVolBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3334]},
			}},
			{EffectID::rigMoonSpewRadBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3335]},
			}},
			{EffectID::rigMoonFractureDelay, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3336]},
			}},
			{EffectID::rigMoonAsteroidDecayBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3337]},
			}},
			{EffectID::shipBonusTitanG1KinThermDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3338]},{modifiers[3339]},{modifiers[3340]},{modifiers[3341]},{modifiers[3342]},{modifiers[3343]},
			}},
			{EffectID::shipBonusTitanG2AllDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3344]},{modifiers[3345]},{modifiers[3346]},{modifiers[3347]},{modifiers[3348]},{modifiers[3349]},{modifiers[3350]},{modifiers[3351]},{modifiers[3352]},
			}},
			{EffectID::shipBonusTitanC1ShieldResists, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3353]},{modifiers[3354]},{modifiers[3355]},{modifiers[3356]},
			}},
			{EffectID::shipBonusRole4FighterDamageAndHitpoints, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3357]},{modifiers[3358]},{modifiers[3359]},{modifiers[3360]},
			}},
			{EffectID::shipBonusDreadnoughtG1KinThermDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3361]},{modifiers[3362]},{modifiers[3363]},{modifiers[3364]},{modifiers[3365]},{modifiers[3366]},
			}},
			{EffectID::shipBonusForceAuxiliaryG1RemoteShieldBoostAmount, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3367]},
			}},
			{EffectID::shipBonusRole2LogisticDroneRepAmountAndHitpointBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[2693]},{modifiers[2694]},{modifiers[2695]},{modifiers[3368]},{modifiers[3369]},{modifiers[3370]},
			}},
			{EffectID::refineryServiceFuelBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3371]},{modifiers[3372]},
			}},
			{EffectID::refineryRefiningYieldBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3373]},{modifiers[3374]},{modifiers[3375]},
			}},
			{EffectID::asteroidDecayTimeDisplayUpdate, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3376]},
			}},
			{EffectID::characterDamageMissiles, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3377]},{modifiers[3378]},{modifiers[3379]},{modifiers[3380]},
			}},
			{EffectID::naniteRepairPasteArmorDamageBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3381]},
			}},
			{EffectID::tacticalMode, MetaInfo::Effect::Category::generic, false, false, {
				
			}},
			{EffectID::fueledArmorRepairBonus, MetaInfo::Effect::Category::generic, false, false, {
				{modifiers[3382]},{modifiers[3383]},
			}},
			{EffectID::gangBoost, MetaInfo::Effect::Category::active, false, false, {
				
			}},
		};
	}
}
