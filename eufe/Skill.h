#pragma once
#include "types.h"
#include "Item.h"

namespace eufe {
	
	class Skill : public Item
	{
	public:
		Skill(std::shared_ptr<Engine> engine, TypeID typeID, int skillLevel, bool isLearned, std::shared_ptr<Character> owner);
		virtual ~Skill(void);
		std::shared_ptr<Skill> shared_from_this() {
			return std::static_pointer_cast<Skill>(Item::shared_from_this());
		}

		bool isLearned() const;
		int getSkillLevel();
		void setSkillLevel(int level);
		//virtual Attribute getAttribute(TypeID attributeID);

		virtual Environment getEnvironment();
		
	protected:
		virtual void lazyLoad();
	private:
		bool isLearned_;
		int skillLevel_;
	};
	
}