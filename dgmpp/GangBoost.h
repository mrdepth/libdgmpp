#pragma once
#include "types.h"

namespace dgmpp {
	class GangBoost {
	public:
		enum class BufID {
			shieldBurstShieldHarmonizingShieldResistance = 10,
			shieldBurstActiveShieldingRepairDurationCapacitor = 11,
			shieldBurstShieldExtensionShieldHP = 12,
			armorBurstArmorEnergizingArmorResistance = 13,
			armorBurstRapidRepairRepairDurationCapacitor = 14,
			armorBurstArmorReinforcementArmorHP = 15,
			informationBurstSensorOptimizationScanResolution = 16,
			informationBurstElectronicSuperiorityEwarRangeAndStrength = 17,
			informationBurstElectronicHardeningScanStrength = 18,
			informationBurstElectronicHardeningRsdRwdResistance = 19,
			informationBurstSensorOptimizationTargetingRange = 26,
			skirmishBurstEvasiveManeuversSignatureRadius = 20,
			skirmishBurstInterdictionManeuversTackleRange = 21,
			skirmishBurstRapidDeploymentAbMwdSpeedIncrease = 22,
			miningBurstMiningLaserFieldEnhancementMiningSurveyRange = 23,
			miningBurstMiningLaserOptimizationMiningCapacitorDuration = 24,
			miningBurstMiningEquipmentPreservationCrystalVolatility = 25,
			skirmishBurstEvasiveManeuversAgility = 60,
			avatarEffectGeneratorCapacitorRechargeBonus = 39,
			avatarEffectGeneratorKineticResistanceBonus = 40,
			avatarEffectGeneratorEmResistancePenalty = 41,
			erebusEffectGeneratorArmorHpBonus = 42,
			erebusEffectGeneratorExplosiveResistanceBonus = 43,
			erebusEffectGeneratorThermalResistancePenalty = 44,
			ragnarokEffectGeneratorSignatureRadiusBonus = 45,
			ragnarokEffectGeneratorThermalResistanceBonus = 46,
			ragnarokEffectGeneratorExplosiveResistancePenaly = 47,
			leviathanEffectGeneratorShieldHpBonus = 48,
			leviathanEffectGeneratorEmResistanceBonus = 49,
			leviathanEffectGeneratorKineticResistancePenalty = 50,
			avatarEffectGeneratorVelocityPenalty = 51,
			erebusEffectGeneratorShieldRrPenalty = 52,
			leviathanEffectGeneratorArmorRrPenalty = 53,
			ragnarokEffectGeneratorLaserAndHybridOptimalPenalty = 54
		};
		
		GangBoost(std::shared_ptr<Engine> const& engine, std::shared_ptr<Attribute> bufID, std::shared_ptr<Attribute> value);
		
		std::list<std::shared_ptr<Modifier>> modifiers();
		
		std::shared_ptr<Attribute> getBufID() const;
		std::shared_ptr<Attribute> getValue() const;
	private:
		std::weak_ptr<Engine> engine_;
		std::shared_ptr<Attribute> bufID_;
		std::shared_ptr<Attribute> value_;
	};
}
