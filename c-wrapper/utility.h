//
//  utility.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef utility_h
#define utility_h

#include <stdlib.h>

typedef signed char BOOL;
typedef int dgmpp_type_id;
typedef int dgmpp_group_id;
typedef int dgmpp_category_id;
typedef int dgmpp_attribute_id;
//typedef int dgmpp_effect_id;
//typedef int dgmpp_warfare_buff_id;
typedef int dgmpp_schematic_id;
//typedef int dgmpp_modifier_id;
typedef double dgmpp_giga_joule;
typedef double dgmpp_teraflops;
typedef double dgmpp_mega_watts;
typedef double dgmpp_calibration_points;
typedef double dgmpp_cubic_meter;
typedef double dgmpp_meter;
typedef double dgmpp_millimeter;
typedef double dgmpp_megabits_per_second;
typedef double dgmpp_kilogram;
typedef double dgmpp_points;
typedef double dgmpp_hp;
typedef double dgmpp_radians;
typedef double dgmpp_astronomical_unit;
typedef double dgmpp_percent;
typedef double dgmpp_multiplier;
typedef double dgmpp_giga_joule_per_second;
typedef double dgmpp_cubic_meter_per_second;
typedef double dgmpp_radians_per_second;
typedef double dgmpp_meters_per_second;
typedef double dgmpp_astronomical_units_per_second;
typedef double dgmpp_hp_per_second;
typedef double dgmpp_fuel_units_per_hour;
typedef double dgmpp_seconds;

typedef struct dgmpp_attribute dgmpp_attribute;
typedef dgmpp_attribute* dgmpp_attribute_ptr;
typedef struct dgmpp_type dgmpp_type;
typedef dgmpp_type* dgmpp_type_ptr;

typedef struct {
	size_t count;
	dgmpp_type_ptr* types;
} dgmpp_types_array;
typedef dgmpp_types_array* dgmpp_types_array_ptr;
void dgmpp_types_array_free (dgmpp_types_array_ptr array);

typedef struct {
	size_t count;
	dgmpp_attribute_ptr* attributes;
} dgmpp_attributes_array;
typedef dgmpp_attributes_array* dgmpp_attributes_array_ptr;
void dgmpp_attributes_array_free (dgmpp_attributes_array_ptr array);

typedef struct {
	size_t count;
	int* values;
} dgmpp_ints_array;
typedef dgmpp_ints_array* dgmpp_ints_array_ptr;
void dgmpp_ints_array_free (dgmpp_ints_array_ptr array);


typedef enum {
	DGMPP_RACE_ID_NONE = 0,
	DGMPP_RACE_ID_CALDARI = 1,
	DGMPP_RACE_ID_MINMATAR = 2,
	DGMPP_RACE_ID_AMARR = 4,
	DGMPP_RACE_ID_GALLENTE = 8
} DGMPP_RACE_ID;

typedef enum {
	DGMPP_SCAN_TYPE_RADAR,
	DGMPP_SCAN_TYPE_LADAR,
	DGMPP_SCAN_TYPE_MAGNETOMETRIC,
	DGMPP_SCAN_TYPE_GRAVIMETRIC,
	DGMPP_SCAN_TYPE_MULTISPECTRAL
} DGMPP_SCAN_TYPE;

typedef enum {
	DGMPP_MODULE_SLOT_UNKNOWN = -1,
	DGMPP_MODULE_SLOT_NONE = 0,
	DGMPP_MODULE_SLOT_HI,
	DGMPP_MODULE_SLOT_MED,
	DGMPP_MODULE_SLOT_LOW,
	DGMPP_MODULE_SLOT_RIG,
	DGMPP_MODULE_SLOT_SUBSYSTEM,
	DGMPP_MODULE_SLOT_MODE,
	DGMPP_MODULE_SLOT_SERVICE,
	DGMPP_MODULE_SLOT_STARBASE_STRUCTURE
} DGMPP_MODULE_SLOT;

typedef enum {
	DGMPP_MODULE_HARDPOINT_NONE = 0,
	DGMPP_MODULE_HARDPOINT_LAUNCHER,
	DGMPP_MODULE_HARDPOINT_TURRET,
} DGMPP_MODULE_HARDPOINT;

typedef enum {
	DGMPP_MODULE_STATE_UNKNOWN = -1,
	DGMPP_MODULE_STATE_OFFLINE,
	DGMPP_MODULE_STATE_ONLINE,
	DGMPP_MODULE_STATE_ACTIVE,
	DGMPP_MODULE_STATE_OVERLOADED
} DGMPP_MODULE_STATE;

typedef enum {
	DGMPP_DRONE_SQUADRON_NONE = 0,
	DGMPP_DRONE_SQUADRON_HEAVY,
	DGMPP_DRONE_SQUADRON_LIGHT,
	DGMPP_DRONE_SQUADRON_SUPPORT
} DGMPP_DRONE_SQUADRON;

typedef enum {
	DGMPP_CHARGE_SIZE_NONE = 0,
	DGMPP_CHARGE_SIZE_SMALL = 1,
	DGMPP_CHARGE_SIZE_MEDIUM = 2,
	DGMPP_CHARGE_SIZE_LARGE = 3,
	DGMPP_CHARGE_SIZE_X_LARGE = 4
} DGMPP_CHARGE_SIZE;

typedef enum {
	DGMPP_COMMODITY_TIER_UNKNOWN = -1,
	DGMPP_COMMODITY_TIER_RAW,
	DGMPP_COMMODITY_TIER_TIER1,
	DGMPP_COMMODITY_TIER_TIER2,
	DGMPP_COMMODITY_TIER_TIER3,
	DGMPP_COMMODITY_TIER_TIER4
} DGMPP_COMMODITY_TIER;

typedef struct {
	dgmpp_percent em;
	dgmpp_percent thermal;
	dgmpp_percent kinetic;
	dgmpp_percent explosive;
} dgmpp_resistances_layer;

typedef struct {
	dgmpp_resistances_layer shield;
	dgmpp_resistances_layer armor;
	dgmpp_resistances_layer hull;
} dgmpp_resistances;

typedef struct {
	dgmpp_hp em;
	dgmpp_hp thermal;
	dgmpp_hp kinetic;
	dgmpp_hp explosive;
} dgmpp_damage_vector;

typedef dgmpp_damage_vector dgmpp_damage_per_second;

typedef struct {
	dgmpp_hp shield;
	dgmpp_hp armor;
	dgmpp_hp hull;
} dgmpp_hit_points;

typedef struct {
	dgmpp_hp_per_second passive_shield;
	dgmpp_hp_per_second shield_repair;
	dgmpp_hp_per_second armor_repair;
	dgmpp_hp_per_second hull_repair;
} dgmpp_tank;

typedef struct {
	dgmpp_radians_per_second angular_velocity;
	dgmpp_meters_per_second velocity;
	dgmpp_meter signature;
	dgmpp_meter range;
} dgmpp_hostile_target;

extern const dgmpp_hostile_target dgmpp_hostile_target_default;

#endif /* utility_h */
