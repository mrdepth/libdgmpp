#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <memory>

namespace eufe {
	class Item;
	class Attribute;
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
	
	typedef std::map<eufe::TypeID, std::shared_ptr<Attribute>> AttributesMap;
	typedef std::list<std::shared_ptr<Attribute>> AttributesList;
	typedef std::list<std::shared_ptr<Effect> > EffectsList;
	typedef std::map<std::string, std::shared_ptr<Item>> Environment;
	typedef std::list<std::shared_ptr<Module>> ModulesList;
	typedef std::list<std::shared_ptr<Drone>> DronesList;
	typedef std::list<std::shared_ptr<Character>> CharactersList;
	typedef std::map<eufe::TypeID, std::shared_ptr<Skill>> SkillsMap;
	typedef std::list<std::shared_ptr<Implant>> ImplantsList;
	typedef std::list<std::shared_ptr<Booster>> BoostersList;
	typedef std::list<std::shared_ptr<Modifier>> ModifiersList;
	typedef std::list<std::shared_ptr<Structure>> StructuresList;
	
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

	struct ResistancesLayer
	{
		float em;
		float explosive;
		float kinetic;
		float thermal;
	};
	
	struct Resistances
	{
		ResistancesLayer armor, hull, shield;
	};
	
	enum Opcode
	{
		OPCODE_ARGUMENT = 0,
		OPCODE_OPERAND = 1
	};
	
	enum ArgumentType
	{
		ARGUMENT_TYPE_INT = 0,
		ARGUMENT_TYPE_STRING = 1,
		ARGUMENT_TYPE_EXPRESSION = 2
	};

}
