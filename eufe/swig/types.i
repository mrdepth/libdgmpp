%include <std_map.i>
%include <std_vector.i>
%include <std_string.i>

namespace eufe {
	typedef int TypeID;
}

namespace std {
	%template(TypesList) vector<eufe::TypeID>;
	%template(AttributesMap) map<eufe::TypeID, eufe::Attribute*>;
	%template(ModulesList) vector<eufe::Module*>;
	%template(DronesList) vector<eufe::Drone*>;
	%template(CharactersList) vector<eufe::Character*>;
	%template(SkillsMap) map<eufe::TypeID, eufe::Skill*>;
	%template(ImplantsList) vector<eufe::Implant*>;
	%template(BoostersList) vector<eufe::Booster*>;
	%template(StructuresList) vector<eufe::Structure*>;
}
namespace eufe {
	
	using namespace std;
	
	typedef map<eufe::TypeID, eufe::Attribute*> AttributesMap;
	typedef map<eufe::TypeID, eufe::Skill*> SkillsMap;
	
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
