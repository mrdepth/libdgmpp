#include "GangBoost.h"
#include "Attribute.h"
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "Item.h"

using namespace dgmpp;

GangBoost::GangBoost(std::shared_ptr<Engine> const& engine, std::shared_ptr<Attribute> bufID, std::shared_ptr<Attribute> value): engine_(engine), bufID_(bufID), value_(value) {
}

std::list<std::shared_ptr<Modifier>> GangBoost::modifiers() {
	
	std::list<std::shared_ptr<Modifier>> modifiers;
	
	switch (static_cast<BufID>(bufID_->getValue())) {
		case BufID::shieldBurstShieldHarmonizingShieldResistance:
			
			for (auto i: {AttributeID::shieldEmDamageResonance, AttributeID::shieldKineticDamageResonance, AttributeID::shieldThermalDamageResonance, AttributeID::shieldExplosiveDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;
		
		case BufID::shieldBurstActiveShieldingRepairDurationCapacitor:
			for (auto i: {AttributeID::capacitorNeed, AttributeID::duration}) {
				
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, TypeID::shieldOperation, false, false));
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, TypeID::shieldEmissionSystems, false, false));
			}
			break;
		
		case BufID::shieldBurstShieldExtensionShieldHP:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::shieldCapacity, Modifier::Association::postPercent, value_, false, false));
			break;
		
			
		case BufID::armorBurstArmorEnergizingArmorResistance:
			for (auto i: {AttributeID::armorEmDamageResonance, AttributeID::armorKineticDamageResonance, AttributeID::armorThermalDamageResonance, AttributeID::armorExplosiveDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;
		
		case BufID::armorBurstRapidRepairRepairDurationCapacitor:
			for (auto i: {AttributeID::capacitorNeed, AttributeID::duration}) {
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, TypeID::repairSystems, false, false));
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, TypeID::remoteArmorRepairSystems, false, false));
			}
			break;
		
		case BufID::armorBurstArmorReinforcementArmorHP:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::armorHP, Modifier::Association::postPercent, value_, false, false));
			break;
		
		case BufID::informationBurstSensorOptimizationScanResolution:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::scanResolution, Modifier::Association::postPercent, value_, false, false));
			break;
			
		case BufID::informationBurstElectronicSuperiorityEwarRangeAndStrength:
			for (auto i: {GroupID::eCM, GroupID::sensorDampener, GroupID::weaponDisruptor, GroupID::targetPainter}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, AttributeID::maxRange, Modifier::Association::postPercent, value_, i, false, false));
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, AttributeID::falloffEffectiveness, Modifier::Association::postPercent, value_, i, false, false));
			}
			
			for (auto i: {AttributeID::scanGravimetricStrengthBonus, AttributeID::scanLadarStrengthBonus, AttributeID::scanMagnetometricStrengthBonus, AttributeID::scanRadarStrengthBonus}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, GroupID::eCM, false, false));
			}

			for (auto i: {AttributeID::missileVelocityBonus, AttributeID::explosionDelayBonus, AttributeID::aoeVelocityBonus, AttributeID::falloffBonus, AttributeID::maxRangeBonus, AttributeID::aoeCloudSizeBonus, AttributeID::trackingSpeedBonus}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, GroupID::weaponDisruptor, false, false));
			}

			for (auto i: {AttributeID::maxTargetRangeBonus, AttributeID::scanResolutionBonus}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, GroupID::sensorDampener, false, false));
			}

			modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, AttributeID::signatureRadiusBonus, Modifier::Association::postPercent, value_, GroupID::targetPainter, false, false));
			break;

		case BufID::informationBurstElectronicHardeningScanStrength:
			for (auto i: {AttributeID::scanGravimetricStrength, AttributeID::scanRadarStrength, AttributeID::scanLadarStrength, AttributeID::scanMagnetometricStrength}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::informationBurstElectronicHardeningRsdRwdResistance:
			for (auto i: {AttributeID::sensorDampenerResistance, AttributeID::weaponDisruptionResistance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::informationBurstSensorOptimizationTargetingRange:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::maxTargetRange, Modifier::Association::postPercent, value_, false, false));
			break;
		
		case BufID::skirmishBurstEvasiveManeuversSignatureRadius:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::signatureRadius, Modifier::Association::postPercent, value_, false, false));
			break;
		
		case BufID::skirmishBurstInterdictionManeuversTackleRange:
			for (auto i: {GroupID::stasisWeb, GroupID::warpScrambler}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, AttributeID::maxRange, Modifier::Association::postPercent, value_, i, false, false));
			}
			break;
			
		case BufID::skirmishBurstRapidDeploymentAbMwdSpeedIncrease:
			for (auto i: {TypeID::afterburner, TypeID::highSpeedManeuvering}) {
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::speedFactor, Modifier::Association::postPercent, value_, i, false, false));
			}
			break;

		case BufID::miningBurstMiningLaserFieldEnhancementMiningSurveyRange:
			for (auto i: {TypeID::mining, TypeID::iceHarvesting, TypeID::gasCloudHarvesting}) {
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::maxRange, Modifier::Association::postPercent, value_, i, false, false));
			}
			modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::surveyScanRange, Modifier::Association::postPercent, value_, TypeID::cPUManagement, false, false));
			break;

		case BufID::miningBurstMiningLaserOptimizationMiningCapacitorDuration:
			for (auto i: {TypeID::mining, TypeID::iceHarvesting, TypeID::gasCloudHarvesting}) {
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::capacitorNeed, Modifier::Association::postPercent, value_, i, false, false));
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::duration, Modifier::Association::postPercent, value_, i, false, false));
			}
			break;
		
		case BufID::miningBurstMiningEquipmentPreservationCrystalVolatility:
			modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::crystalVolatilityChance, Modifier::Association::postPercent, value_, TypeID::mining, false, false));
			break;

		case BufID::skirmishBurstEvasiveManeuversAgility:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::agility, Modifier::Association::postPercent, value_, false, false));
			break;

		case BufID::avatarEffectGeneratorCapacitorRechargeBonus:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::rechargeRate, Modifier::Association::postPercent, value_, false, false));
			break;
		
		case BufID::avatarEffectGeneratorKineticResistanceBonus:
			for (auto i: {AttributeID::armorKineticDamageResonance, AttributeID::shieldKineticDamageResonance, AttributeID::kineticDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::avatarEffectGeneratorEmResistancePenalty:
			for (auto i: {AttributeID::armorEmDamageResonance, AttributeID::shieldEmDamageResonance, AttributeID::emDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::erebusEffectGeneratorArmorHpBonus:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::armorHP, Modifier::Association::postPercent, value_, false, false));
			break;

		case BufID::erebusEffectGeneratorExplosiveResistanceBonus:
			for (auto i: {AttributeID::armorExplosiveDamageResonance, AttributeID::shieldExplosiveDamageResonance, AttributeID::explosiveDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::erebusEffectGeneratorThermalResistancePenalty:
			for (auto i: {AttributeID::armorThermalDamageResonance, AttributeID::shieldThermalDamageResonance, AttributeID::thermalDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::ragnarokEffectGeneratorSignatureRadiusBonus:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::signatureRadius, Modifier::Association::postPercent, value_, false, false));
			break;

		case BufID::ragnarokEffectGeneratorThermalResistanceBonus:
			for (auto i: {AttributeID::armorThermalDamageResonance, AttributeID::shieldThermalDamageResonance, AttributeID::thermalDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::ragnarokEffectGeneratorExplosiveResistancePenaly:
			for (auto i: {AttributeID::armorExplosiveDamageResonance, AttributeID::shieldExplosiveDamageResonance, AttributeID::explosiveDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::leviathanEffectGeneratorShieldHpBonus:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::shieldCapacity, Modifier::Association::postPercent, value_, false, false));
			break;

		case BufID::leviathanEffectGeneratorEmResistanceBonus:
			for (auto i: {AttributeID::armorEmDamageResonance, AttributeID::shieldEmDamageResonance, AttributeID::emDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::leviathanEffectGeneratorKineticResistancePenalty:
			for (auto i: {AttributeID::armorKineticDamageResonance, AttributeID::shieldKineticDamageResonance, AttributeID::kineticDamageResonance}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, i, Modifier::Association::postPercent, value_, false, false));
			}
			break;

		case BufID::avatarEffectGeneratorVelocityPenalty:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::ship, AttributeID::maxVelocity, Modifier::Association::postPercent, value_, false, false));
			break;

		case BufID::erebusEffectGeneratorShieldRrPenalty:
			modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::shieldBonus, Modifier::Association::postPercent, value_, TypeID::shieldEmissionSystems, false, false));
			break;
		
		case BufID::leviathanEffectGeneratorArmorRrPenalty:
			modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::ship, AttributeID::armorDamageAmount, Modifier::Association::postPercent, value_, TypeID::remoteArmorRepairSystems, false, false));
			break;
			
		case BufID::ragnarokEffectGeneratorLaserAndHybridOptimalPenalty:
			for (auto i: {GroupID::energyWeapon, GroupID::hybridWeapon}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::ship, AttributeID::maxRange, Modifier::Association::postPercent, value_, i, false, false));
			}
			break;
	}
	
	return modifiers;
}

std::shared_ptr<Attribute> GangBoost::getBufID() const {
	return bufID_;
}

std::shared_ptr<Attribute> GangBoost::getValue() const {
	return value_;
}
