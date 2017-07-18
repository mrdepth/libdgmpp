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
	
	switch (static_cast<int>(bufID_->getValue())) {
		case SHIELD_BURST_SHIELD_HARMONIZING_SHIELD_RESISTANCE_BUF_ID:
			for (auto i: {SHIELD_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID, SHIELD_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID, SHIELD_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID, SHIELD_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, false, false));
			}
			break;
		case SHIELD_BURST_ACTIVE_SHIELDING_REPAIR_DURATION_CAPACITOR_BUF_ID:
			for (auto i: {CAPACITOR_NEED_ATTRIBUTE_ID, DURATION_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, SHIELD_OPERATION_TYPE_ID, false, false));
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, SHIELD_EMISSION_SYSTEMS_TYPE_ID, false, false));
			}
			break;
		case SHIELD_BURST_SHIELD_EXTENSION_SHIELD_HP_BUF_ID:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::DOMAIN_SHIP, SHIELD_CAPACITY_ATTRIBUTE_ID, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, false, false));
			break;
		case ARMOR_BURST_ARMOR_ENERGIZING_ARMOR_RESISTANCE_BUF_ID:
			for (auto i: {ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID, ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID, ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID, ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, false, false));
			}
			break;
		case ARMOR_BURST_RAPID_REPAIR_REPAIR_DURATION_CAPACITOR_BUF_ID:
			for (auto i: {CAPACITOR_NEED_ATTRIBUTE_ID, DURATION_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, REPAIR_SYSTEMS_TYPE_ID, false, false));
				modifiers.push_back(std::make_shared<LocationRequiredSkillModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, REMOTE_ARMOR_REPAIR_SYSTEMS_TYPE_ID, false, false));
			}
			break;
		case ARMOR_BURST_ARMOR_REINFORCEMENT_ARMOR_HP_BUF_ID:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::DOMAIN_SHIP, ARMOR_HP_ATTRIBUTE_ID, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, false, false));
			break;
		case INFORMATION_BURST_SENSOR_OPTIMIZATION_SCAN_RESOLUTION_BUF_ID:
			modifiers.push_back(std::make_shared<Modifier>(Modifier::Domain::DOMAIN_SHIP, SCAN_RESOLUTION_ATTRIBUTE_ID, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, false, false));
			break;
		case INFORMATION_BURST_ELECTRONIC_SUPERIORITY_EWAR_RANGE_AND_STRENGTH_BUF_ID:
			for (auto i: {ECM_GROUP_ID, SENSOR_DAMPENER_GROUP_ID, WEAPON_DISRUPTOR_GROUP_ID, TARGET_PAINTER_GROUP_ID}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::DOMAIN_SHIP, MAX_RANGE_ATTRIBUTE_ID, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, i, false, false));
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::DOMAIN_SHIP, FALLOFF_EFFECTIVENESS_ATTRIBUTE_ID, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, i, false, false));
			}
			
			for (auto i: {SCAN_GRAVIMETRIC_STRENGTH_BONUS_ATTRIBUTE_ID, SCAN_LADAR_STRENGTH_BONUS_ATTRIBUTE_ID, SCAN_MAGNETOMETRIC_STRENGTH_BONUS_ATTRIBUTE_ID, SCAN_RADAR_STRENGTH_BONUS_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, ECM_GROUP_ID, false, false));
			}

			for (auto i: {MISSILE_VELOCITY_BONUS_ATTRIBUTE_ID, EXPLOSION_DELAY_BONUS_ATTRIBUTE_ID, AOE_VELOCITY_BONUS_ATTRIBUTE_ID, FALLOFF_BONUS_ATTRIBUTE_ID, MAX_RANGE_BONUS_ATTRIBUTE_ID, AOE_CLOUD_SIZE_BONUS_ATTRIBUTE_ID, TRACKING_SPEED_BONUS_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, WEAPON_DISRUPTOR_GROUP_ID, false, false));
			}

			for (auto i: {MAX_TARGET_RANGE_BONUS_ATTRIBUTE_ID, SCAN_RESOLUTION_BONUS_ATTRIBUTE_ID}) {
				modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::DOMAIN_SHIP, i, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, SENSOR_DAMPENER_GROUP_ID, false, false));
			}

			modifiers.push_back(std::make_shared<LocationGroupModifier>(Modifier::Domain::DOMAIN_SHIP, SIGNATURE_RADIUS_BONUS_ATTRIBUTE_ID, Modifier::Association::ASSOCIATION_POST_PERCENT, value_, TARGET_PAINTER_GROUP_ID, false, false));
			break;

		case INFORMATION_BURST_ELECTRONIC_HARDENING_SCAN_STRENGTH_BUF_ID:
		case INFORMATION_BURST_ELECTRONIC_HARDENING_RSD_RWD_RESISTANCE_BUF_ID:
		case INFORMATION_BURST_SENSOR_OPTIMIZATION_TARGETING_RANGE_BUF_ID:
		case SKIRMISH_BURST_EVASIVE_MANEUVERS_SIGNATURE_RADIUS_BUF_ID:
		case SKIRMISH_BURST_INTERDICTION_MANEUVERS_TACKLE_RANGE_BUF_ID:
		case SKIRMISH_BURST_RAPID_DEPLOYMENT_AB_MWD_SPEED_INCREASE_BUF_ID:
		case MINING_BURST_MINING_LASER_FIELD_ENHANCEMENT_MINING_SURVEY_RANGE_BUF_ID:
		case MINING_BURST_MINING_LASER_OPTIMIZATION_MINING_CAPACITOR_DURATION_BUF_ID:
		case MINING_BURST_MINING_EQUIPMENT_PRESERVATION_CRYSTAL_VOLATILITY_BUF_ID:
		case SKIRMISH_BURST_EVASIVE_MANEUVERS_AGILITY_BUF_ID:
		case AVATAR_EFFECT_GENERATOR_CAPACITOR_RECHARGE_BONUS_BUF_ID:
		case AVATAR_EFFECT_GENERATOR_KINETIC_RESISTANCE_BONUS_BUF_ID:
		case AVATAR_EFFECT_GENERATOR_EM_RESISTANCE_PENALTY_BUF_ID:
		case EREBUS_EFFECT_GENERATOR_ARMOR_HP_BONUS_BUF_ID:
		case EREBUS_EFFECT_GENERATOR_EXPLOSIVE_RESISTANCE_BONUS_BUF_ID:
		case EREBUS_EFFECT_GENERATOR_THERMAL_RESISTANCE_PENALTY_BUF_ID:
		case RAGNAROK_EFFECT_GENERATOR_SIGNATURE_RADIUS_BONUS_BUF_ID:
		case RAGNAROK_EFFECT_GENERATOR_THERMAL_RESISTANCE_BONUS_BUF_ID:
		case RAGNAROK_EFFECT_GENERATOR_EXPLOSIVE_RESISTANCE_PENALY_BUF_ID:
		case LEVIATHAN_EFFECT_GENERATOR_SHIELD_HP_BONUS_BUF_ID:
		case LEVIATHAN_EFFECT_GENERATOR_EM_RESISTANCE_BONUS_BUF_ID:
		case LEVIATHAN_EFFECT_GENERATOR_KINETIC_RESISTANCE_PENALTY_BUF_ID:
		case AVATAR_EFFECT_GENERATOR_VELOCITY_PENALTY_BUF_ID:
		case EREBUS_EFFECT_GENERATOR_SHIELD_RR_PENALTY_BUF_ID:
		case LEVIATHAN_EFFECT_GENERATOR_ARMOR_RR_PENALTY_BUF_ID:
		case RAGNAROK_EFFECT_GENERATOR_LASER_AND_HYBRID_OPTIMAL_PENALTY_BUF_ID:
			break;
	}
	return modifiers;
}
