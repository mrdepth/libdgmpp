//
//  utility.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#ifndef utility_h
#define utility_h

#include <stdlib.h>

#ifdef __cplusplus
#define DGMPP_EXTERN extern "C"
#else
#define DGMPP_EXTERN
#endif

typedef int8_t dgmpp_bool;

typedef int dgmpp_type_id;
typedef int dgmpp_group_id;
typedef int dgmpp_category_id;
typedef int dgmpp_attribute_id;
typedef int dgmpp_schematic_id;
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

typedef struct dgmpp_t dgmpp_t;
typedef void* dgmpp_handle;

//typedef struct {
//	void* handle;
//	char tag;
//} dgmpp_handle;

typedef dgmpp_handle dgmpp_type;
typedef dgmpp_handle dgmpp_attribute;
typedef dgmpp_handle dgmpp_planet;
typedef dgmpp_handle dgmpp_facility;
typedef dgmpp_handle dgmpp_state;
typedef dgmpp_handle dgmpp_array;
typedef dgmpp_handle dgmpp_capacitor;

DGMPP_EXTERN void 	dgmpp_free		(dgmpp_handle handle);
//DGMPP_EXTERN size_t	dgmpp_get_hash	(dgmpp_handle handle);

DGMPP_EXTERN size_t			dgmpp_array_get_size	(dgmpp_array array);
DGMPP_EXTERN const void*	dgmpp_array_get_values	(dgmpp_array array);

typedef enum {
	DGMPP_TYPE_NONE,
	DGMPP_TYPE_GANG,
	DGMPP_TYPE_CHARACTER,
	DGMPP_TYPE_SKILL,
	DGMPP_TYPE_BOOSTER,
	DGMPP_TYPE_IMPLANT,
	DGMPP_TYPE_SHIP,
	DGMPP_TYPE_STRUCTURE,
	DGMPP_TYPE_MODULE,
	DGMPP_TYPE_DRONE,
	DGMPP_TYPE_CHARGE
} DGMPP_TYPE;

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
	DGMPP_DRONE_SQUADRON_SUPPORT,
	DGMPP_DRONE_SQUADRON_STANDUP_HEAVY,
	DGMPP_DRONE_SQUADRON_STANDUP_LIGHT,
	DGMPP_DRONE_SQUADRON_STANDUP_SUPPORT

} DGMPP_DRONE_SQUADRON;

typedef enum {
	DGMPP_CHARGE_SIZE_NONE = 0,
	DGMPP_CHARGE_SIZE_SMALL = 1,
	DGMPP_CHARGE_SIZE_MEDIUM = 2,
	DGMPP_CHARGE_SIZE_LARGE = 3,
	DGMPP_CHARGE_SIZE_X_LARGE = 4
} DGMPP_CHARGE_SIZE;

typedef enum {
	DGMPP_RIG_SIZE_NONE = 0,
	DGMPP_RIG_SIZE_SMALL = 1,
	DGMPP_RIG_SIZE_MEDIUM = 2,
	DGMPP_RIG_SIZE_LARGE = 3,
	DGMPP_RIG_SIZE_X_LARGE = 4
} DGMPP_RIG_SIZE;

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

DGMPP_EXTERN const dgmpp_hostile_target dgmpp_hostile_target_default;

typedef struct {
	dgmpp_type_id type_id;
	DGMPP_COMMODITY_TIER tier;
	dgmpp_cubic_meter volume;
	size_t quantity;
} dgmpp_commodity;

DGMPP_EXTERN dgmpp_bool dgmpp_commodity_create(dgmpp_type_id type_id, size_t quantity, dgmpp_commodity* commodity);

typedef struct {
	dgmpp_seconds start;
	dgmpp_seconds duration;
	dgmpp_commodity yield;
	dgmpp_commodity waste;
} dgmpp_production_cycle;

typedef struct {
	dgmpp_facility from;
	dgmpp_facility to;
	dgmpp_commodity commodity;
} dgmpp_route;

typedef enum {
	DGMPP_FACILITY_CATEGORY_NONE,
	DGMPP_FACILITY_CATEGORY_ECU,
	DGMPP_FACILITY_CATEGORY_FACTORY,
	DGMPP_FACILITY_CATEGORY_STORAGE,
	DGMPP_FACILITY_CATEGORY_COMMAND_CENTER,
	DGMPP_FACILITY_CATEGORY_SPACEPORT
} DGMPP_FACILITY_CATEGORY;

typedef struct {
	size_t build;
	const char* version;
} dgmpp_sde_version;

typedef struct {
	size_t major;
	size_t minor;
	dgmpp_sde_version sde;
} dgmpp_version;


DGMPP_EXTERN dgmpp_version dgmpp_get_version ();

#endif /* utility_h */
