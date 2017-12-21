%include "Type.i"
%include "Structure.i"

namespace std {
	%template(Characters) vector<dgmpp::Character*>;
	%template(Implants) vector<dgmpp::Implant*>;
	%template(Boosters) vector<dgmpp::Booster*>;
	%template(Skills) vector<dgmpp::Skill*>;
}

namespace dgmpp {
	class Implant: public Type {
	public:
		typedef int Slot;
		Slot slot() const noexcept;
	};

	class Booster: public Type {
	public:
		typedef int Slot;
		Slot slot() const noexcept;
	};

	class Skill: public Type {
	public:
		int level();
		void level (int level);
	};

	class Character : public Type {
	public:
		Ship* ship() const;
		Ship* ship (TypeID typeID);
		Structure* structure();
		Structure* structure (TypeID typeID);
		
		void setSkillLevels (int level);
		
		Implant* addImplant(TypeID typeID, bool replace = false);
		Booster* addBooster(TypeID typeID, bool replace = false);
		void remove(Implant* implant);
		void remove(Booster* booster);
		
		std::vector<Skill*> skills() const;
		std::vector<Implant*> implants() const;
		std::vector<Booster*> boosters() const;
		
		Implant* implant (Implant::Slot slot) const noexcept;
		Booster* booster (Booster::Slot slot) const noexcept;
		
		Meter droneControlDistance();
	};
}
