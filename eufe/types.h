#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <string>
#include <map>
#include <list>
#include <iterator>
#include <set>
#include <memory>
#include <cassert>
#include <vector>

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
	typedef std::list<std::shared_ptr<Effect> > EffectsList;
	//typedef std::map<std::string, std::shared_ptr<Item>> Environment;
	typedef std::list<std::shared_ptr<Module>> ModulesList;
	typedef std::list<std::shared_ptr<Drone>> DronesList;
	typedef std::list<std::shared_ptr<Character>> CharactersList;
	typedef std::map<eufe::TypeID, std::shared_ptr<Skill>> SkillsMap;
	typedef std::list<std::shared_ptr<Implant>> ImplantsList;
	typedef std::list<std::shared_ptr<Booster>> BoostersList;
	typedef std::list<std::shared_ptr<Modifier>> ModifiersList;
	typedef std::list<std::shared_ptr<Structure>> StructuresList;
	
	typedef eufe::TypeID AttributeID;
	typedef eufe::TypeID GroupID;
	typedef eufe::TypeID SkillID;

	typedef std::map<AttributeID, ModifiersList> ItemModifiers;
	typedef ItemModifiers LocationModifiers;
	typedef std::map<SkillID, ItemModifiers> LocationRequiredSkillModifiers;
	typedef std::map<GroupID, ItemModifiers> LocationGroupModifiers;
	
	typedef std::vector<const ModifiersList*> ModifiersListVector;
	
	struct Environment {
		Environment() : character(nullptr), ship(nullptr), gang(nullptr), self(nullptr), area(nullptr), target(nullptr), other(nullptr) {};
		Item* character;
		Item* ship;
		Item* gang;
		Item* self;
		Item* area;
		Item* target;
		Item* other;
		Item* operator[](const std::string& s) {
			if (s == "Self")
				return self;
			else if (s == "Ship")
				return ship;
			else if (s == "Char")
				return character;
			else if (s == "Other")
				return other;
			else if (s == "Target")
				return target;
			else if (s == "Area")
				return area;
			else if (s == "Gang")
				return gang;
			else {
				assert(nullptr);
				return nullptr;
			}
		}
	};
	
	struct Tank
	{
		union {
			struct {
				float passiveShield;
				float shieldRepair;
				float armorRepair;
				float hullRepair;
			};
			float layers[4];
		};
	};
	
	struct HitPoints
	{
		union {
			struct {
				float shield;
				float armor;
				float hull;
			};
			float layers[3];
		};
	};

	struct ResistancesLayer
	{
		union {
			struct {
				float em;
				float thermal;
				float kinetic;
				float explosive;
			};
			float resistances[4];
		};
	};
	
	struct Resistances
	{
		union {
			struct {
				ResistancesLayer shield, armor, hull;
			};
			ResistancesLayer layers[3];
		};
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
