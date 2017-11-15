#pragma once
#include "types.h"
#include "Item.h"
#include "Type.hpp"

namespace dgmpp {
	
	class Skill : public Item
	{
	public:
		Skill(std::shared_ptr<Engine> const& engine, TypeID typeID, int skillLevel, bool isLearned, std::shared_ptr<Character> const& owner);
		virtual ~Skill(void);
		std::shared_ptr<Skill> shared_from_this() {
			return std::static_pointer_cast<Skill>(Item::shared_from_this());
		}

		bool isLearned() const;
		int getSkillLevel();
		//virtual Attribute getAttribute(TypeID attributeID);

		virtual Item* character();
		virtual Item* ship();
		virtual Item* structure();
		
	protected:
		virtual void lazyLoad();
		friend class Character;
		void setSkillLevel(int level);
	private:
		bool isLearned_;
		int skillLevel_;
	};
	
}

namespace dgmpp2 {
	
	class Skill: public Type {
	public:
		int level() {return static_cast<int>((*this)[AttributeID::skillLevel]->value());}
		void level(int level) {*(*this)[AttributeID::skillLevel] = static_cast<Float>(level);}
	protected:
	private:
		friend class Character;
		static std::unique_ptr<Skill> Create (const MetaInfo::Type& metaInfo) { return std::unique_ptr<Skill>(new Skill(metaInfo)); }
		Skill(const MetaInfo::Type& metaInfo) : Type(metaInfo) {};
	};
}
