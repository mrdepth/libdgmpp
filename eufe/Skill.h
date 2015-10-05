#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Skill : public Item
	{
	public:
		bool isLearned() const;
		int getSkillLevel();
		void setSkillLevel(int level);
		//virtual Attribute getAttribute(TypeID attributeID);

		virtual Environment getEnvironment();
		
	protected:
		friend class Character;
		Skill(std::shared_ptr<Engine> engine, TypeID typeID, int skillLevel, bool isLearned, std::shared_ptr<Character> owner);
		virtual ~Skill(void);
	private:
		bool isLearned_;
	};
	
}