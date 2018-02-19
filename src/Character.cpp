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
			skillsMap_.emplace(metaInfo->typeID, std::move(skill));
			ptr->parent_(this);
		}
	}
	
	Character::Character (const Character& other): Type(other) {
		for (const auto& i: other.skillsMap_) {
			auto skill = Skill::Create(*i.second);
			auto ptr = skill.get();
			skillsMap_.emplace(ptr->metaInfo().typeID, std::move(skill));
			ptr->parent_(this);
		}
		
		for (const auto& i: other.implantsSet_) {
			auto implant = Implant::Create(*i);
			auto ptr = implant.get();
			implantsSet_.emplace(std::move(implant));
			ptr->parent_(this);
		}

		for (const auto& i: other.boostersSet_) {
			auto booster = Booster::Create(*i);
			auto ptr = booster.get();
			boostersSet_.emplace(std::move(booster));
			ptr->parent_(this);
		}

		/*if (auto structure = other.structure_()) {
			shipValue_ = Structure::Create(*structure);
			shipValue_->parent_(this);
		}
		else */if (auto ship = other.ship_()) {
			shipValue_ = Ship::Create(*ship);
			shipValue_->parent_(this);
		}
		nameValue_ = other.nameValue_;
	}
	
	Ship* Character::ship_(std::unique_ptr<Ship>&& ship) {
		batchUpdates_([&]() {
			auto enabled = isEnabled_();
			if (enabled)
				setEnabled_(false);
			
			if (shipValue_) {
				shipValue_->parent_(nullptr);
				shipValue_ = nullptr;
			}
			
			if (ship != nullptr) {
				shipValue_ = std::move(ship);
				shipValue_->parent_(this);
			}
			
			if (enabled)
				setEnabled_(true);
		});
		
		return shipValue_.get();
	}
	
//	Structure* Character::structure_ (std::unique_ptr<Structure>&& structure) {
//		return dynamic_cast<Structure*>(ship_(std::move(structure)));
//	}
	
	Type* Character::domain_(MetaInfo::Modifier::Domain domain) noexcept {
		switch (domain) {
			case MetaInfo::Modifier::Domain::character:
				return this;
			case MetaInfo::Modifier::Domain::ship:
				return shipValue_.get();
			default:
				return Type::domain_(domain);
		}
	}
	
	void Character::reset_() {
		if (shipValue_) {
			shipValue_->reset_();
		}
	}
	
	void Character::setSkillLevels_(int level) {
		if (level >= 0 && level <= 5) {
			batchUpdates_([&]() {
				for (const auto& i: skillsMap_) {
					i.second->level_(level);
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
	
	Implant* Character::add_(std::unique_ptr<Implant>&& implant, bool replace) {
		auto old = implantsSet_.find(implant->slot());
		if (old != implantsSet_.end()) {
			if (replace) {
				(*old)->parent_(nullptr);
				implantsSet_.erase(old);
			}
			else
				throw CannotFit<Implant>(std::move(implant));
		}

		auto ptr = implant.get();
		implantsSet_.insert(std::move(implant));
		ptr->parent_(this);
		
		return ptr;
	}
	
	Booster* Character::add_(std::unique_ptr<Booster>&& booster, bool replace) {
		auto old = boostersSet_.find(booster->slot());
		if (old != boostersSet_.end()) {
			if (replace) {
				(*old)->parent_(nullptr);
				boostersSet_.erase(old);
			}
			else
				throw CannotFit<Booster>(std::move(booster));
		}
		
		auto ptr = booster.get();
		boostersSet_.insert(std::move(booster));
		ptr->parent_(this);
		
		return ptr;
	}
	
	void Character::remove_(Implant* implant) {
		auto i = implantsSet_.find(implant);
		assert(i != implantsSet_.end());
		(*i)->parent_(nullptr);
		implantsSet_.erase(i);
	}
	
	void Character::remove_(Booster* booster) {
		auto i = boostersSet_.find(booster);
		assert(i != boostersSet_.end());
		(*i)->parent_(nullptr);
		boostersSet_.erase(i);
	}
	
	std::vector<Skill*> Character::skills_() const {
		std::vector<Skill*> result;
		result.reserve(skillsMap_.size());
		std::transform(skillsMap_.begin(), skillsMap_.end(), std::back_inserter(result), [](const auto& i) { return i.second.get(); });
		return result;
	}

	std::vector<Implant*> Character::implants_() const {
		std::vector<Implant*> result;
		result.reserve(implantsSet_.size());
		std::transform(implantsSet_.begin(), implantsSet_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}
	
	std::vector<Booster*> Character::boosters_() const {
		std::vector<Booster*> result;
		result.reserve(boostersSet_.size());
		std::transform(boostersSet_.begin(), boostersSet_.end(), std::back_inserter(result), [](const auto& i) { return i.get(); });
		return result;
	}

	Implant* Character::implant_ (Implant::Slot slot) const noexcept {
		auto i = implantsSet_.find(slot);
		return i != implantsSet_.end() ? i->get() : nullptr;
	}
	
	Booster* Character::booster_ (Booster::Slot slot) const noexcept {
		auto i = boostersSet_.find(slot);
		return i != boostersSet_.end() ? i->get() : nullptr;
	}
	
	Meter Character::droneControlDistance_() {
		return attribute_(AttributeID::droneControlDistance)->value_();
	}

	
	void Character::setEnabled_ (bool enabled) {
		if (isEnabled_() == enabled)
			return Type::setEnabled_(enabled);
		else
			Type::setEnabled_(enabled);
	
		batchUpdates_([=]() {
			std::for_each(skillsMap_.begin(), skillsMap_.end(), [enabled](auto& i) {
				i.second->setEnabled_(enabled);
			});
			std::for_each(implantsSet_.begin(), implantsSet_.end(), [enabled](auto& i) {
				i->setEnabled_(enabled);
			});
			std::for_each(boostersSet_.begin(), boostersSet_.end(), [enabled](auto& i) {
				i->setEnabled_(enabled);
			});
			if (shipValue_)
				shipValue_->setEnabled_(enabled);
		});
	}
}
