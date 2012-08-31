#pragma once
#include <boost/thread/recursive_mutex.hpp>
#include "types.h"

namespace eufe {

	extern const TypeID IS_ONLINE_ATTRIBUTE_ID;
	extern const TypeID MASS_ATTRIBUTE_ID;
	extern const TypeID CAPACITY_ATTRIBUTE_ID;
	extern const TypeID VOLUME_ATTRIBUTE_ID;
	extern const TypeID RADIUS_ATTRIBUTE_ID;
	extern const TypeID REQUIRED_SKILL1_ATTRIBUTE_ID;
	extern const TypeID REQUIRED_SKILL2_ATTRIBUTE_ID;
	extern const TypeID REQUIRED_SKILL3_ATTRIBUTE_ID;
	extern const TypeID RACE_ID_ATTRIBUTE_ID;
	extern const TypeID SKILL_LEVEL_ATTRIBUTE_ID;
	extern const TypeID IMPLANTNESS_ATTRIBUTE_ID;
	extern const TypeID BOOSTERNESS_ATTRIBUTE_ID;
	
	extern const TypeID LOW_SLOTS_ATTRIBUTE_ID;
	extern const TypeID MED_SLOTS_ATTRIBUTE_ID;
	extern const TypeID HI_SLOTS_ATTRIBUTE_ID;
	extern const TypeID RIG_SLOTS_ATTRIBUTE_ID;
	extern const TypeID MAX_SUBSYSTEMS_SLOTS_ATTRIBUTE_ID;
	
	extern const TypeID LAUNCHER_SLOTS_LEFT_ATTRIBUTE_ID;
	extern const TypeID TURRET_SLOTS_LEFT_ATTRIBUTE_ID;
	
	extern const TypeID FITS_TO_SHIP_TYPE_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_TYPE1_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_TYPE2_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_TYPE3_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_TYPE4_ATTRIBUTE_ID;

	extern const TypeID CAN_FIT_SHIP_GROUP1_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_GROUP2_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_GROUP3_ATTRIBUTE_ID;
	extern const TypeID CAN_FIT_SHIP_GROUP4_ATTRIBUTE_ID;
	
	extern const TypeID SUBSYSTEM_SLOT_ATTRIBUTE_ID;
	extern const TypeID RIG_SIZE_ATTRIBUTE_ID;
	extern const TypeID MAX_GROUP_FITTED_ATTRIBUTE_ID;
	
	extern const TypeID CHARGE_SIZE_ATTRIBUTE_ID;
	extern const TypeID CHARGE_GROUP1_ATTRIBUTE_ID;
	extern const TypeID CHARGE_GROUP2_ATTRIBUTE_ID;
	extern const TypeID CHARGE_GROUP3_ATTRIBUTE_ID;
	extern const TypeID CHARGE_GROUP4_ATTRIBUTE_ID;
	extern const TypeID CHARGE_GROUP5_ATTRIBUTE_ID;

	extern const TypeID MAX_GROUP_ACTIVE_ATTRIBUTE_ID;
	
	extern const TypeID SPEED_ATTRIBUTE_ID;
	extern const TypeID DURATION_ATTRIBUTE_ID;
	extern const TypeID MISSILE_LAUNCH_DURATION_ATTRIBUTE_ID;
	extern const TypeID RELOAD_TIME_ATTRIBUTE_ID;
	extern const TypeID MODULE_REACTIVATION_DELAY_ATTRIBUTE_ID;
	
	extern const TypeID CHARGE_RATE_ATTRIBUTE_ID;
	extern const TypeID CRYSTALS_GET_DAMAGED_ATTRIBUTE_ID;

	extern const TypeID HP_ATTRIBUTE_ID;
	extern const TypeID CRYSTAL_VOLATILITY_CHANCE_ATTRIBUTE_ID;
	extern const TypeID CRYSTAL_VOLATILITY_DAMAGE_ATTRIBUTE_ID;
	extern const TypeID CAPACITOR_NEED_ATTRIBUTE_ID;
	extern const TypeID CAPACITOR_BONUS_ATTRIBUTE_ID;
	extern const TypeID POWER_TRANSFER_AMOUNT_ATTRIBUTE_ID;
	extern const TypeID ENERGY_DESTABILIZATION_AMOUNT_ATTRIBUTE_ID;
	
	extern const TypeID CAPACITOR_CAPACITY_ATTRIBUTE_ID;
	extern const TypeID CHARGE_ATTRIBUTE_ID;
	extern const TypeID RECHARGE_RATE_ATTRIBUTE_ID;
	
	extern const TypeID DISALLOW_ASSISTANCE_ATTRIBUTE_ID;
	extern const TypeID DISALLOW_OFFENSIVE_MODIFIERS_ATTRIBUTE_ID;
	
	extern const TypeID EM_DAMAGE_ATTRIBUTE_ID;
	extern const TypeID KINETIC_DAMAGE_ATTRIBUTE_ID;
	extern const TypeID EXPLOSIVE_DAMAGE_ATTRIBUTE_ID;
	extern const TypeID THERMAL_DAMAGE_ATTRIBUTE_ID;
	extern const TypeID DAMAGE_MULTIPLIER_ATTRIBUTE_ID;
	extern const TypeID MISSILE_DAMAGE_MULTIPLIER_ATTRIBUTE_ID;
	
	extern const TypeID MAX_RANGE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_TRANSFER_RANGE_ATTRIBUTE_ID;
	extern const TypeID POWER_TRANSFER_RANGE_ATTRIBUTE_ID;
	extern const TypeID ENERGY_DESTABILIZATION_RANGE_ATTRIBUTE_ID;
	extern const TypeID EMP_FIELD_RANGE_ATTRIBUTE_ID;
	extern const TypeID ECM_BURST_RANGE_ATTRIBUTE_ID;
	extern const TypeID WARP_SCRAMBLE_RANGE_ATTRIBUTE_ID;
	extern const TypeID CARGO_SCAN_RANGE_ATTRIBUTE_ID;
	extern const TypeID SHIP_SCAN_RANGE_ATTRIBUTE_ID;
	extern const TypeID SURVEY_SCAN_RANGE_ATTRIBUTE_ID;
	extern const TypeID FALLOFF_ATTRIBUTE_ID;
	extern const TypeID SHIP_SCAN_FALLOFF_ATTRIBUTE_ID;
	extern const TypeID TRACKING_SPEED_ATTRIBUTE_ID;
	
	extern const TypeID MAX_VELOCITY_ATTRIBUTE_ID;
	extern const TypeID EXPLOSION_DELAY_ATTRIBUTE_ID;
	extern const TypeID AGILITY_ATTRIBUTE_ID;
	
	extern const TypeID ARMOR_DAMAGE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_CHARGE_ATTRIBUTE_ID;
	extern const TypeID DAMAGE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_CAPACITY_ATTRIBUTE_ID;
	extern const TypeID ARMOR_HP_ATTRIBUTE_ID;
	extern const TypeID SHIELD_RECHARGE_RATE_ATTRIBUTE_ID;
	extern const TypeID ARMOR_DAMAGE_AMOUNT_ATTRIBUTE_ID;
	extern const TypeID SHIELD_BONUS_ATTRIBUTE_ID;
	extern const TypeID STRUCTURE_DAMAGE_AMOUNT_ATTRIBUTE_ID;
	
	extern const TypeID KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID EM_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID ARMOR_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID ARMOR_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID ARMOR_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID ARMOR_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID SHIELD_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	
	extern const TypeID ENTITY_MISSILE_TYPE_ID_ATTRIBUTE_ID;
	extern const TypeID ACTIVATION_BLOCKED_ATTRIBUTE_ID;
	
	extern const TypeID UPGRADE_COST_ATTRIBUTE_ID;
	extern const TypeID UPGRADE_CAPACITY_ATTRIBUTE_ID;
	extern const TypeID CPU_LOAD_ATTRIBUTE_ID;
	extern const TypeID POWER_LOAD_ATTRIBUTE_ID;
	extern const TypeID POWER_OUTPUT_ATTRIBUTE_ID;
	extern const TypeID CPU_OUTPUT_ATTRIBUTE_ID;
	extern const TypeID DRONE_BANDWIDTH_USED_ATTRIBUTE_ID;
	extern const TypeID DRONE_BANDWIDTH_ATTRIBUTE_ID;
	extern const TypeID DRONE_CAPACITY_ATTRIBUTE_ID;
	extern const TypeID BASE_WARP_SPEED_ATTRIBUTE_ID;
	extern const TypeID WARP_SPEED_MULTIPLIER_ATTRIBUTE_ID;
	extern const TypeID SIGNATURE_RADIUS_ATTRIBUTE_ID;
	extern const TypeID WARP_CAPACITOR_NEED_ATTRIBUTE_ID;
	extern const TypeID MAX_LOCKED_TARGETS_ATTRIBUTE_ID;
	extern const TypeID MAX_TARGET_RANGE_ATTRIBUTE_ID;
	extern const TypeID SCAN_RADAR_STRENGTH_ATTRIBUTE_ID;
	extern const TypeID SCAN_LADAR_STRENGTH_ATTRIBUTE_ID;
	extern const TypeID SCAN_MAGNETOMETRIC_STRENGTH_ATTRIBUTE_ID;
	extern const TypeID SCAN_GRAVIMETRIC_STRENGTH_ATTRIBUTE_ID;
	extern const TypeID MAX_ACTIVE_DRONES_ATTRIBUTE_ID;
	extern const TypeID SCAN_RESOLUTION_ATTRIBUTE_ID;
	
	extern const TypeID HI_SLOT_MODIFIER_ATTRIBUTE_ID;
	extern const TypeID MED_SLOT_MODIFIER_ATTRIBUTE_ID;
	extern const TypeID LOW_SLOT_MODIFIER_ATTRIBUTE_ID;
	extern const TypeID TURRET_HARD_POINT_MODIFIER_ATTRIBUTE_ID;
	extern const TypeID LAUNCHER_HARD_POINT_MODIFIER_ATTRIBUTE_ID;
	
	extern const TypeID HEAT_ATTENUATION_HI_ATTRIBUTE_ID;
	extern const TypeID HEAT_ATTENUATION_LOW_ATTRIBUTE_ID;
	extern const TypeID HEAT_ATTENUATION_MED_ATTRIBUTE_ID;
	extern const TypeID HEAT_CAPACITY_HI_ATTRIBUTE_ID;
	extern const TypeID HEAT_CAPACITY_LOW_ATTRIBUTE_ID;
	extern const TypeID HEAT_CAPACITY_MED_ATTRIBUTE_ID;
	extern const TypeID HEAT_DISSIPATION_RATE_HI_ATTRIBUTE_ID;
	extern const TypeID HEAT_DISSIPATION_RATE_LOW_ATTRIBUTE_ID;
	extern const TypeID HEAT_DISSIPATION_RATE_MED_ATTRIBUTE_ID;
	extern const TypeID HEAT_GENERATION_MULTIPLIER_ATTRIBUTE_ID;
	extern const TypeID HEAT_ABSORBTION_RATE_MODIFIER_ATTRIBUTE_ID;
	extern const TypeID HEAT_DAMAGE_ATTRIBUTE_ID;

	extern const TypeID POWER_ATTRIBUTE_ID;
	extern const TypeID CPU_ATTRIBUTE_ID;
	
	extern const TypeID HULL_KINETIC_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID HULL_THERMAL_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID HULL_EXPLOSIVE_DAMAGE_RESONANCE_ATTRIBUTE_ID;
	extern const TypeID HULL_EM_DAMAGE_RESONANCE_ATTRIBUTE_ID;

	extern const TypeID MISSILE_ENTITY_VELOCITY_MULTIPLIER_ATTRIBUTE_ID;
	extern const TypeID MISSILE_ENTITY_FLIGHT_TIME_MULTIPLIER_ATTRIBUTE_ID;

	extern const TypeID DRONE_CONTROL_DISTANCE_ATTRIBUTE_ID;

	class Attribute : public boost::recursive_mutex
	{
	public:
		Attribute();
		Attribute(Attribute& attribute);
#if _DEBUG
		Attribute(Engine* engine, TypeID attributeID, TypeID maxAttributeID, float value, bool isStackable, bool highIsGood, Item* owner = nullptr, const char* attributeName = "", bool isFakeAttribute = false);
#else
		Attribute(Engine* engine, TypeID attributeID, TypeID maxAttributeID, float value, bool isStackable, bool highIsGood, Item* owner = nullptr, bool isFakeAttribute = false);
#endif
		Attribute(Engine* engine, TypeID attributeID, Item* owner = nullptr, bool isFakeAttribute = false);
		virtual ~Attribute(void);

		Item* getOwner() const;
		void setOwner(Item* owner);
		TypeID getAttributeID() const;
		bool isFakeAttribute() const;

		virtual float getValue();
		virtual float getInitialValue() const;
		bool isStackable() const;
		bool highIsGood() const;

		virtual void setValue(float value);
		virtual float dec(float value);
		virtual float inc(float value);
		
		void reset();
		
#if _DEBUG
		const char* getAttributeName() const;
		friend std::ostream& operator<<(std::ostream& os, Attribute& attribute);
#endif

	private:
		Engine* engine_;
		TypeID attributeID_;
		TypeID maxAttributeID_;
		float value_;
		float initialValue_;
		float forcedValue_;
		bool isStackable_;
		bool calculated_;
		bool highIsGood_;
		bool isFakeAttribute_;
		
		Item* owner_;
		
		void calculate();

		bool sync;
#if _DEBUG
		std::string attributeName_;
#endif
	};

}