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

namespace dgmpp {
	class Item;
	class Attribute;
	class Effect;
	class EffectPrototype;
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
	class Environment;
	
	class Planet;
	class Facility;
	class CommandCenter;
	class Route;
	class Commodity;

	typedef int TypeID;
	
	typedef std::map<dgmpp::TypeID, std::shared_ptr<Attribute>> AttributesMap;
	typedef std::list<std::shared_ptr<Effect> > EffectsList;
	typedef std::list<std::shared_ptr<Module>> ModulesList;
	typedef std::list<std::shared_ptr<Drone>> DronesList;
	typedef std::list<std::shared_ptr<Character>> CharactersList;
	typedef std::map<dgmpp::TypeID, std::shared_ptr<Skill>> SkillsMap;
	typedef std::list<std::shared_ptr<Implant>> ImplantsList;
	typedef std::list<std::shared_ptr<Booster>> BoostersList;
	typedef std::list<std::shared_ptr<Modifier>> ModifiersList;
	typedef std::list<std::shared_ptr<Structure>> StructuresList;
	
	typedef dgmpp::TypeID AttributeID;
	typedef dgmpp::TypeID GroupID;
	typedef dgmpp::TypeID SkillID;

	typedef std::map<AttributeID, ModifiersList> ItemModifiers;
	typedef ItemModifiers LocationModifiers;
	typedef std::map<SkillID, ItemModifiers> LocationRequiredSkillModifiers;
	typedef std::map<GroupID, ItemModifiers> LocationGroupModifiers;
	
	typedef std::list<std::shared_ptr<Facility>> FacilitiesList;
	typedef std::list<std::shared_ptr<const Route>> RoutesList;

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
}
