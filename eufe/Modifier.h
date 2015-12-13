#pragma once
#include "types.h"

namespace eufe {
	
	class Modifier
	{
	public:
		
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

		Modifier(TypeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~Modifier(void);
		virtual bool isMatch(std::shared_ptr<Item> const& item) const;
		TypeID getAttributeID() const;
		std::shared_ptr<Attribute> getModifier() const;
		Association getAssociation() const;
		float getValue() const;
		bool isStackable() const;
		Character* getCharacter();
		bool isOffensive();
		bool isAssistance();

		std::string getAssociationName();
		friend std::ostream& operator<<(std::ostream& os, Modifier& modifier);

	private:
		TypeID attributeID_;
		std::weak_ptr<Attribute> modifier_;
		Association association_;
		Character* character_;
		bool isOffensive_;
		bool isAssistance_;
	};
	
}