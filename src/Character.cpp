//
//  Character.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 16.11.2017.
//

#include "Character.hpp"
#include "SDE.hpp"
#include "Errors.hpp"
#include "Gang.hpp"

namespace dgmpp {
	
	Character::Character() : Type(TypeID::characterGallente) {
		for (std::size_t i = 0; i < SDE::skillsCount; i++) {
			auto metaInfo = SDE::skills[i];
			auto skill = Skill::Create(*metaInfo);
			auto ptr = skill.get();
			skills_.emplace(metaInfo->typeID, std::move(skill));
			ptr->parent_(this);
		}
	}
	
	Character::Character (const Character& other): Type(other) {
		for (const auto& i: other.skills_) {
			auto skill = Skill::Create(*i.second);
			auto ptr = skill.get();
			skills_.emplace(ptr->metaInfo().typeID, std::move(skill));
			ptr->parent_(this);
		}
		
		for (const auto& i: other.implants_) {
			auto implant = Implant::Create(*i);
			auto ptr = implant.get();
			implants_.emplace(std::move(implant));
			ptr->parent_(this);
		}

		for (const auto& i: other.boosters_) {
			auto booster = Booster::Create(*i);
			auto ptr = booster.get();
			boosters_.emplace(std::move(booster));
			ptr->parent_(this);
		}

		if (auto structure = other.structure()) {
			shipValue_ = Structure::Create(*structure);
			shipValue_->parent_(this);
		}
		else if (auto ship = other.ship_()) {
			shipValue_ = Ship::Create(*ship);
			shipValue_->parent_(this);
		}
		name_ = other.name_;
	}
	
	Ship* Character::ship_(std::unique_ptr<Ship>&& ship) {
		batchUpdates([&]() {
			auto enabled = isEnabled();
			if (enabled)
				setEnabled(false);
			
			if (shipValue_) {
				shipValue_->parent_(nullptr);
				shipValue_ = nullptr;
			}
			
			if (ship != nullptr) {
				shipValue_ = std::move(ship);
				shipValue_->parent_(this);
			}
			
			if (enabled)
				setEnabled(true);
		});
		
		return shipValue_.get();
	}
	
	Structure* Character::structure_ (std::unique_ptr<Structure>&& structure) {
		return dynamic_cast<Structure*>(ship(std::move(structure)));
	}
	
	Type* Character::domain(MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::character:
				return this;
			case MetaInfo::Modifier::Domain::ship:
				return shipValue_.get();
			default:
				return Type::domain(domain);
		}
	}
	
	void Character::reset() {
		if (shipValue_) {
			shipValue_->reset();
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
	
	bool Character::factorReload_() const noexcept {
		if (auto gang = dynamic_cast<Gang*>(parent_()))
			return gang->factorReload_();
		else
			return false;
	}
	
	Implant* Character::add(std::unique_ptr<Implant>&& implant, bool replace) {
		auto old = implants_.find(implant->slot());
		if (old != implants_.end()) {
			if (replace) {
				(*old)->parent_(nullptr);
				implants_.erase(old);
			}
			else
				throw CannotFit<Implant>(std::move(implant));
		}

		auto ptr = implant.get();
		implants_.insert(std::move(implant));
		ptr->parent_(this);
		
		return ptr;
	}
	
	Booster* Character::add(std::unique_ptr<Booster>&& booster, bool replace) {
		auto old = boosters_.find(booster->slot());
		if (old != boosters_.end()) {
			if (replace) {
				(*old)->parent_(nullptr);
				boosters_.erase(old);
			}
			else
				throw CannotFit<Booster>(std::move(booster));
		}
		
		auto ptr = booster.get();
		boosters_.insert(std::move(booster));
		ptr->parent_(this);
		
		return ptr;
	}
	
	void Character::remove(Implant* implant) {
		auto i = implants_.find(implant);
		assert(i != implants_.end());
		(*i)->parent_(nullptr);
		implants_.erase(i);
	}
	
	void Character::remove(Booster* booster) {
		auto i = boosters_.find(booster);
		assert(i != boosters_.end());
		(*i)->parent_(nullptr);
		boosters_.erase(i);
	}
	
	std::vector<Skill*> Character::skills() const {
		std::vector<Skill*> result;
		result.reserve(skills_.size());
		std::transform(skills_.begin(), skills_.end(), std::back_inserter(result), [](const auto& i) { return i.second.get(); });
		return result;
	}

	std::vector<Implant*> Character::implants() const {
		std::vector<Implant*> result;
		result.reserve(implants_.size());
		std::transform(implants_.begin(), implants_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	std::vector<Booster*> Character::boosters() const {
		std::vector<Booster*> result;
		result.reserve(boosters_.size());
		std::transform(boosters_.begin(), boosters_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}

	Implant* Character::implant (Implant::Slot slot) const noexcept {
		auto i = implants_.find(slot);
		return i != implants_.end() ? i->get() : nullptr;
	}
	
	Booster* Character::booster (Booster::Slot slot) const noexcept {
		auto i = boosters_.find(slot);
		return i != boosters_.end() ? i->get() : nullptr;
	}
	
	Meter Character::droneControlDistance() {
		return attribute(AttributeID::droneControlDistance)->value_();
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
			std::for_each(implants_.begin(), implants_.end(), [enabled](auto& i) {
				i->setEnabled(enabled);
			});
			std::for_each(boosters_.begin(), boosters_.end(), [enabled](auto& i) {
				i->setEnabled(enabled);
			});
			if (shipValue_)
				shipValue_->setEnabled(enabled);
		});
	}
}
