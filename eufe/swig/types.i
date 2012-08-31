%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>
%include <std_list.i>

namespace eufe {

	typedef int TypeID;
	
	%template(AttributesMap) std::map<eufe::TypeID, Attribute*>;
	%template(EffectsList) std::list<Effect*>;
	%template(ModulesList) std::list<Module*>;
	%template(DronesList) std::list<Drone*>;
	%template(CharactersList) std::list<Character*>;
	%template(SkillsMap) std::map<eufe::TypeID, Skill*>;
	%template(ImplantsList) std::list<Implant*>;
	%template(BoostersList) std::list<Booster*>;
	%template(StructuresList) std::list<Structure*>;
	
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
}
