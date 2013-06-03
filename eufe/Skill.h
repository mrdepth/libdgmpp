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
		
		Skill(Decoder& decoder, Engine* engine, Character* owner = NULL);
		virtual void encode(Encoder& encoder)  const;
	private:
		bool isLearned_;
	};
	
}