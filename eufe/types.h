#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <map>
#include <list>

namespace eufe {
	class Item;
	class Attribute;
	class Association;
	class Effect;
	class Ship;
	class Module;
	class Gang;
	class Engine;
	class Character;
	class Area;
	class Skill;
	class Implant;
	class Booster;
	class Modifier;
	class LocationGroupModifier;
	class LocationRequiredSkillModifier;
	class Charge;
	class Drone;
	class EffectInterpreter;
	class ControlTower;
	class Structure;

	typedef unsigned char Byte;
	typedef int TypeID;
	
	typedef std::map<eufe::TypeID, Attribute*> AttributesMap;
	typedef std::list<Attribute*> AttributesList;
	typedef std::list<Association*> AssociationsList;
	typedef std::list<Effect*> EffectsList;
	typedef std::map<std::string, Association*> AssociationsMap;
	typedef std::map<std::string, Item*> Environment;
	typedef std::list<Module*> ModulesList;
	typedef std::list<Drone*> DronesList;
	typedef std::list<Character*> CharactersList;
	typedef std::map<eufe::TypeID, Skill*> SkillsMap;
	typedef std::list<Implant*> ImplantsList;
	typedef std::list<Booster*> BoostersList;
	typedef std::list<Modifier*> ModifiersList;
	typedef std::list<Structure*> StructuresList;
	
	struct Tank
	{
		float armorRepair;
		float hullRepair;
		float shieldRepair;
		float passiveShield;
	};
	
	struct HitPoints
	{
		float armor;
		float hull;
		float shield;
	};
	
	struct Resistances
	{
		struct Layer
		{
			float em;
			float explosive;
			float kinetic;
			float thermal;
		} armor, hull, shield;
	};
}
