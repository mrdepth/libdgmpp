%include <std_map.i>
%include <std_vector.i>
%include <std_string.i>

namespace dgmpp {
	typedef int TypeID;
}

namespace std {
	%template(TypesList) vector<dgmpp::TypeID>;
	%template(AttributesMap) map<dgmpp::TypeID, dgmpp::Attribute*>;
	%template(ModulesList) vector<dgmpp::Module*>;
	%template(DronesList) vector<dgmpp::Drone*>;
	%template(CharactersList) vector<dgmpp::Character*>;
	%template(SkillsMap) map<dgmpp::TypeID, dgmpp::Skill*>;
	%template(ImplantsList) vector<dgmpp::Implant*>;
	%template(BoostersList) vector<dgmpp::Booster*>;
	%template(StructuresList) vector<dgmpp::Structure*>;
}
namespace dgmpp {
	
	using namespace std;
	
	typedef map<dgmpp::TypeID, dgmpp::Attribute*> AttributesMap;
	typedef map<dgmpp::TypeID, dgmpp::Skill*> SkillsMap;
	
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
