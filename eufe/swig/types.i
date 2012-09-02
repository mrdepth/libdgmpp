%include <std_map.i>
%include "std_list.i"
%include "std_string.i"

namespace eufe {
	typedef int TypeID;
}

namespace std {
	%template(TypesList) list<eufe::TypeID>;
	%template(AttributesMap) map<eufe::TypeID, eufe::Attribute*>;
	%template(EffectsList) list<eufe::Effect*>;
	%template(ModulesList) list<eufe::Module*>;
	%template(DronesList) list<eufe::Drone*>;
	%template(CharactersList) list<eufe::Character*>;
	%template(SkillsMap) map<eufe::TypeID, eufe::Skill*>;
	%template(ImplantsList) list<eufe::Implant*>;
	%template(BoostersList) list<eufe::Booster*>;
	%template(StructuresList) list<eufe::Structure*>;
}
namespace eufe {
	
	using namespace std;
	
	typedef map<eufe::TypeID, eufe::Attribute*> AttributesMap;
	typedef list<eufe::Effect*> EffectsList;
	typedef list<eufe::Module*> ModulesList;
	typedef list<eufe::Drone*> DronesList;
	typedef list<eufe::Character*> CharactersList;
	typedef map<eufe::TypeID, eufe::Skill*> SkillsMap;
	typedef list<eufe::Implant*> ImplantsList;
	typedef list<eufe::Booster*> BoostersList;
	typedef list<eufe::Structure*> StructuresList;
	
//	%template(AttributesMap) std::map<eufe::TypeID, eufe::Attribute*>;
//	%template(EffectsList) std::list<eufe::Effect*>;
//	%template(ModulesList) std::list<eufe::Module*>;
//	%template(DronesList) std::list<eufe::Drone*>;
//	%template(CharactersList) std::list<eufe::Character*>;
//	%template(SkillsMap) std::map<eufe::TypeID, eufe::Skill*>;
//	%template(ImplantsList) std::list<eufe::Implant*>;
//	%template(BoostersList) std::list<eufe::Booster*>;
//	%template(StructuresList) std::list<eufe::Structure*>;
	
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
