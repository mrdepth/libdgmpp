#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Skill : public Item
	{
	public:
		Skill(Engine* engine, TypeID typeID, int skillLevel, bool isLearned, Character* owner);
		virtual ~Skill(void);
		bool isLearned() const;
		int getSkillLevel();
		void setSkillLevel(int level);
		//virtual Attribute getAttribute(TypeID attributeID);

		virtual Environment getEnvironment();
		
	private:
		bool isLearned_;
	};
	
}