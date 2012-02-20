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
		//virtual boost::shared_ptr<Attribute> getAttribute(TypeID attributeID);

		virtual boost::shared_ptr<Environment> getEnvironment();
		
	private:
		bool isLearned_;
	};
	
}