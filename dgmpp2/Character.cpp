//
//  Character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Character.hpp"
#include "SDE.hpp"

namespace dgmpp2 {
	
	Character::Character() : Type(TypeID::characterGallente) {
		for (const auto& metaInfo: SDE::skills) {
			auto skill = Type::add(Skill::Create(metaInfo.get()));
			skills_.emplace(metaInfo.get().typeID, skill);
		}
	}
	
	Ship* Character::setShip(std::unique_ptr<Ship> ship) {
		auto enabled = isEnabled();
		if (enabled)
			setEnabled(false);
		if (ship_)
			remove(ship_);
		
		if (ship != nullptr)
			ship_ = Type::add(std::move(ship));
		else
			ship_ = nullptr;
		if (enabled)
			setEnabled(enabled);
		return ship_;
	}
	
	Type* Character::domain(MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::character:
				return this;
			case MetaInfo::Modifier::Domain::ship:
				return ship_;
			default:
				return Type::domain(domain);
		}
	}
	
	void Character::reset() {
		if (ship_) {
			ship_->reset();
		}
	}
	
	void Character::setSkillLevels(int level) {
		if (level >= 0 && level <= 5) {
			for (const auto& i: skills_) {
				i.second->level(level);
			}
		}
		else
			throw InvalidSkillLevel();
	}
}
