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

		Modifier(TypeID attributeID, Association association, Attribute* modifier, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~Modifier(void);
		virtual bool isMatch(Item* item) const {return true;}
		TypeID getAttributeID() const {return attributeID_;}
		Attribute* getModifier() const {return modifier_;}
		Association getAssociation() const {return association_;}
		float getValue() const;
		bool isStackable() const;
		Character* getCharacter();
		bool isOffensive();
		bool isAssistance();

		
#if _DEBUG
		std::string getAssociationName();
		friend std::ostream& operator<<(std::ostream& os, Modifier& modifier);
#endif

	private:
		TypeID attributeID_;
		Attribute* modifier_;
		Association association_;
		Character* character_;
		bool isOffensive_;
		bool isAssistance_;
	};
	
}