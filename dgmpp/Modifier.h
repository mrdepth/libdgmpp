#pragma once
#include "types.h"
#include "MetaInfo.hpp"

namespace dgmpp {
	
	class Modifier
	{
	public:
		
		enum class Domain {
			self,
			character,
			ship,
			gang,
			area,
			target,
			other,
			structure
		};
		
		enum class Association {
			preAssignment,
			modAdd,
			modSub,
			preDiv,
			preMul,
			postPercent,
			postDiv,
			postMul,
			postAssignment,
			skillTime,
			addRate,
			subRate
		};
		
		enum Type {
			item,
			location,
			locationGroup,
			locationRequiredSkill,
			ownerRequiredSkill,
			locationRequiredDomainSkill,
		};
		
		Modifier(Domain domain, AttributeID attributeID, Association association, std::shared_ptr<Attribute> const& modifier, bool isAssistance, bool isOffensive, Character* character = nullptr);
		virtual ~Modifier(void);
		virtual bool isMatch(Item* item) const;
		Domain getDomain();
		AttributeID getAttributeID() const;
		std::shared_ptr<Attribute> getModifier() const;
		Association getAssociation() const;
		Float getValue() const;
		//		bool isStackable() const;
		Character* getCharacter();
		bool isOffensive();
		bool isAssistance();
		
		std::string getAssociationName();
		friend std::ostream& operator<<(std::ostream& os, Modifier& modifier);
		
		virtual std::string print();
		
	private:
		AttributeID attributeID_;
		Domain domain_;
		std::weak_ptr<Attribute> modifier_;
		Association association_;
		Character* character_;
		bool isOffensive_;
		bool isAssistance_;
	};
	
}

