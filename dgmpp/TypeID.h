#pragma once

//SELECT lower(substr(typeName, 1, 1)) || substr(replace(replace(typeName, '-', ''), ' ', ''), 2) || ' = ' || typeID || ','  FROM invTypes WHERE typeID IN (3319, 4051, 4246, 4247, 4312, 3416, 3422, 3393, 16069, 3450, 3454, 3386, 16281, 25544, 3426, 1381) order by typeID

namespace dgmpp {
	enum class TypeID: int {
		none = 0,
		
		characterStatic = 1381,
		missileLauncherOperation = 3319,
		mining = 3386,
		repairSystems = 3393,
		shieldOperation = 3416,
		shieldEmissionSystems = 3422,
		cPUManagement = 3426,
		afterburner = 3450,
		highSpeedManeuvering = 3454,
		nitrogenFuelBlock = 4051,
		hydrogenFuelBlock = 4246,
		heliumFuelBlock = 4247,
		oxygenFuelBlock = 4312,
		remoteArmorRepairSystems = 16069,
		iceHarvesting = 16281,
		gasCloudHarvesting = 25544
		
		/*
		 const TypeID dgmpp::MISSILE_LAUNCHER_OPERATION_TYPE_ID = 3319;
		 
		 const TypeID dgmpp::CALDARI_RACE_ID = 1;
		 const TypeID dgmpp::MINMATAR_RACE_ID = 2;
		 const TypeID dgmpp::AMARR_RACE_ID = 4;
		 const TypeID dgmpp::GALLENTE_RACE_ID = 8;
		 
		 const TypeID dgmpp::NITROGEN_FUEL_BLOCK_TYPE_ID = 4051;
		 const TypeID dgmpp::HYDROGEN_FUEL_BLOCK_TYPE_ID = 4246;
		 const TypeID dgmpp::HELIUM_FUEL_BLOCK_TYPE_ID = 4247;
		 const TypeID dgmpp::OXYGEN_FUEL_BLOCK_TYPE_ID = 4312;
		 
		 const TypeID dgmpp::SHIELD_OPERATION_TYPE_ID = 3416;
		 const TypeID dgmpp::SHIELD_EMISSION_SYSTEMS_TYPE_ID = 3422;
		 const TypeID dgmpp::REPAIR_SYSTEMS_TYPE_ID = 3393;
		 const TypeID dgmpp::REMOTE_ARMOR_REPAIR_SYSTEMS_TYPE_ID = 16069;
		 const TypeID dgmpp::ECM_GROUP_ID = 201;
		 const TypeID dgmpp::SENSOR_DAMPENER_GROUP_ID = 208;
		 const TypeID dgmpp::WEAPON_DISRUPTOR_GROUP_ID = 291;
		 const TypeID dgmpp::TARGET_PAINTER_GROUP_ID = 379;
		 const TypeID dgmpp::STASIS_WEB_GROUP_ID = 65;
		 const TypeID dgmpp::WARP_SCRAMBLER_GROUP_ID = 52;
		 const TypeID dgmpp::AFTERBURNER_TYPE_ID = 3450;
		 const TypeID dgmpp::HIGH_SPEED_MANEUVERING_TYPE_ID = 3454;
		 const TypeID dgmpp::MINING_TYPE_ID = 3386;
		 const TypeID dgmpp::ICE_HARVESTING_TYPE_ID = 16281;
		 const TypeID dgmpp::GAS_CLOUD_HARVESTING_TYPE_ID = 25544;
		 const TypeID dgmpp::CPU_MANAGEMENT_TYPE_ID = 3426;
		 const TypeID dgmpp::ENERGY_WEAPON_GROUP_ID = 53;
		 const TypeID dgmpp::HYBRID_WEAPON_GROUP_ID = 74;*/
		
		};
	}
	

