//
//  Character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Character.hpp"
#include "SDE.hpp"
#include "Errors.hpp"

namespace dgmpp2 {
	
	Character::Character() : Type(TypeID::characterGallente) {
		for (size_t i = 0; i < SDE::skillsCount; i++) {
			auto metaInfo = SDE::skills[i];
//			auto skill = Type::add(Skill::Create(*metaInfo));
			auto skill = Skill::Create(*metaInfo);
			auto ptr = skill.get();
			skills_.emplace(metaInfo->typeID, std::move(skill));
			ptr->parent(this);
		}
	}
	
	Ship* Character::setShip(std::unique_ptr<Ship> ship) {
		auto enabled = isEnabled();
		if (enabled)
			setEnabled(false);
		
		if (ship_) {
			ship_->parent(nullptr);
			ship_ = nullptr;
		}
		
		if (ship != nullptr) {
			ship_ = std::move(ship);
			ship_->parent(this);
		}
		
		if (enabled)
			setEnabled(true);
		
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
			batchUpdates([&]() {
				for (const auto& i: skills_) {
					i.second->level(level);
				}
			});
		}
		else
			throw InvalidSkillLevel();
	}
	
	Implant* Character::add(std::unique_ptr<Implant> implant, bool replace) {
		auto old = implants_.find(implant->slot());
		if (old != implants_.end() && !replace)
			throw CannotFit<Implant>(std::move(implant));

		auto enabled = isEnabled();
		if (enabled)
			setEnabled(false);

		if (old != implants_.end()) {
			(*old)->parent(nullptr);
			implants_.erase(old);
		}
		
		auto ptr = implant.get();
		implants_.insert(std::move(implant));
		ptr->parent(this);
		
		if (enabled)
			setEnabled(true);
		return ptr;

	}
	
	Booster* Character::add(std::unique_ptr<Booster> booster, bool replace) {
		auto old = boosters_.find(booster->slot());
		if (old != boosters_.end() && !replace)
			throw CannotFit<Booster>(std::move(booster));
		
		auto enabled = isEnabled();
		if (enabled)
			setEnabled(false);
		
		if (old != boosters_.end()) {
			(*old)->parent(nullptr);
			boosters_.erase(old);
		}
		
		auto ptr = booster.get();
		boosters_.insert(std::move(booster));
		ptr->parent(this);
		
		if (enabled)
			setEnabled(true);
		return ptr;
	}
	
	void Character::remove(Implant* implant) {
		
	}
	
	void Character::remove(Booster* booster) {
		
	}

	Implant* Character::implant (Implant::Slot slot) const {
		auto i = implants_.find(slot);
		return i != implants_.end() ? i->get() : nullptr;
	}
	
	Booster* Character::booster (Booster::Slot slot) const {
		auto i = boosters_.find(slot);
		return i != boosters_.end() ? i->get() : nullptr;
	}

	
	void Character::setEnabled (bool enabled) {
		if (isEnabled() == enabled)
			return Type::setEnabled(enabled);
		else
			Type::setEnabled(enabled);
	
		batchUpdates([=]() {
			std::for_each(skills_.begin(), skills_.end(), [enabled](auto& i) {
				i.second->setEnabled(enabled);
			});
			if (ship_)
				ship_->setEnabled(enabled);
		});
	}
}
