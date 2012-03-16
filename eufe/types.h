#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <map>
#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

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
	
	typedef std::map<eufe::TypeID, boost::shared_ptr<Attribute> > AttributesMap;
	typedef std::list<boost::shared_ptr<Attribute> > AttributesList;
	typedef std::list<boost::shared_ptr<Association> > AssociationsList;
	typedef std::list<boost::shared_ptr<Effect> > EffectsList;
	typedef std::map<std::string, boost::shared_ptr<Association> > AssociationsMap;
	typedef std::map<std::string, Item*> Environment;
	typedef std::list<boost::shared_ptr<Module> > ModulesList;
	typedef std::list<Module*> ProjectedModulesList;
	typedef std::list<boost::shared_ptr<Drone> > DronesList;
	typedef std::list<Drone*> ProjectedDronesList;
	typedef std::list<boost::shared_ptr<Character> > CharactersList;
	typedef std::map<eufe::TypeID, boost::shared_ptr<Skill> > SkillsMap;
	typedef std::list<boost::shared_ptr<Implant> > ImplantsList;
	typedef std::list<boost::shared_ptr<Booster> > BoostersList;
	typedef std::list<boost::shared_ptr<Modifier> > ModifiersList;
	typedef std::list<boost::shared_ptr<Structure> > StructuresList;
	
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
