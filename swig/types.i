%include <std_map.i>
%include <std_vector.i>
%include <std_string.i>
%include <std_shared_ptr.i>

namespace dgmpp {
	typedef int TypeID;
}

namespace std {
	%template(TypesList) vector<dgmpp::TypeID>;
	%template(AttributesMap) map<dgmpp::TypeID, dgmpp::Attribute*>;
	%template(ModulesList) vector<std::shared_ptr<dgmpp::Module>>;
	%template(DronesList) vector<std::shared_ptr<dgmpp::Drone>>;
	%template(CharactersList) vector<std::shared_ptr<dgmpp::Character>>;
	%template(SkillsMap) map<dgmpp::TypeID, std::shared_ptr<dgmpp::Skill>>;
	%template(ImplantsList) vector<std::shared_ptr<dgmpp::Implant>>;
	%template(BoostersList) vector<std::shared_ptr<dgmpp::Booster>>;
	%template(StructuresList) vector<std::shared_ptr<dgmpp::Structure>>;
}
namespace dgmpp {
	
	using namespace std;
	
	typedef map<dgmpp::TypeID, std::shared_ptr<dgmpp::Attribute>> AttributesMap;
	typedef map<dgmpp::TypeID, std::shared_ptr<dgmpp::Skill>> SkillsMap;
	
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
