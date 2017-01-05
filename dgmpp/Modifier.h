#pragma once
#include "types.h"

namespace dgmpp {
	
	class Modifier
	{
	public:
		
		enum Domain {
			DOMAIN_SELF,
			DOMAIN_CHAR,
			DOMAIN_SHIP,
			DOMAIN_GANG,
			DOMAIN_AREA,
			DOMAIN_TARGET,
			DOMAIN_OTHER,
			DOMAIN_STRUCTURE,
		};

		enum Association {
			ASSOCIATION_PRE_ASSIGNMENT,
			ASSOCIATION_MOD_ADD,
			ASSOCIATION_MOD_SUB,
			ASSOCIATION_PRE_DIV,
			ASSOCIATION_PRE_MUL,
			ASSOCIATION_POST_PERCENT,
			ASSOCIATION_POST_DIV,
			ASSOCIATION_POST_MUL,
			ASSOCIATION_POST_ASSIGNMENT,
			ASSOCIATION_SKILL_TIME,
			ASSOCIATION_ADD_RATE,
			ASSOCIATION_SUB_RATE
		};
		
		enum Type {
			ITEM_MODIFIER,
			LOCATION_MODIFIER,
			LOCATION_GROUP_MODIFIER,
			LOCATION_REQUIRED_SKILL_MODIFIER,
			OWNER_REQUIRED_SKILL_MODIFIER,
			LOCATION_REQUIRED_DOMAIN_SKILL_MODIFIER,
		};
		
		Modifier(Domain domain, TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~Modifier(void);
		virtual bool isMatch(std::shared_ptr<Item> const& item) const;
		Domain getDomain();
		TypeID getAttributeID() const;
		std::shared_ptr<Attribute> getModifier() const;
		Association getAssociation() const;
		Float getValue() const;
		bool isStackable() const;
		Character* getCharacter();
		bool isOffensive();
		bool isAssistance();

		std::string getAssociationName();
		friend std::ostream& operator<<(std::ostream& os, Modifier& modifier);
		
		virtual std::string print();
		
	private:
		TypeID attributeID_;
		Domain domain_;
		std::weak_ptr<Attribute> modifier_;
		Association association_;
		Character* character_;
		bool isOffensive_;
		bool isAssistance_;
	};
	
}
