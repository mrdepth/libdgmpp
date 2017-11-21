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
		for (size_t i = 0; i < SDE::skillsCount; i++) {
			auto metaInfo = SDE::skills[i];
//			auto skill = Type::add(Skill::Create(*metaInfo));
			auto skill = Skill::Create(*metaInfo);
			skill->parent(this);
			skills_.emplace(metaInfo->typeID, std::move(skill));
		}
	}
	
	Ship* Character::setShip(std::unique_ptr<Ship> ship) {
		if (ship_)
			ship_->parent(nullptr);
		
		if (ship != nullptr) {
			ship->parent(this);
			ship_ = std::move(ship);
		}
		else
			ship_ = nullptr;
		return ship_.get();
	}
	
	Type* Character::domain(MetaInfo::Modifier::Domain domain) {
		switch (domain) {
			case MetaInfo::Modifier::Domain::character:
				return this;
			case MetaInfo::Modifier::Domain::ship:
				return ship_.get();
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
