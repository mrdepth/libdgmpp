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
            auto skill = std::shared_ptr<Skill>(new Skill(*metaInfo));
			skillsMap_.emplace(metaInfo->typeID, skill);
			skill->parent_(this);
		}
	}
	
	Character::Character (const Character& other): Type(other) {
		for (const auto& i: other.skillsMap_) {
            auto skill = std::shared_ptr<Skill>(new Skill(*i.second));
			skillsMap_.emplace(skill->metaInfo().typeID, skill);
			skill->parent_(this);
		}
		
		for (const auto& i: other.implantsSet_) {
            auto implant = std::make_shared<Implant>(*i);
			implantsSet_.emplace(implant);
			implant->parent_(this);
		}

		for (const auto& i: other.boostersSet_) {
			auto booster = std::make_shared<Booster>(*i);
			boostersSet_.emplace(booster);
			booster->parent_(this);
		}

        if (auto ship = other.ship_()) {
			shipValue_ = std::make_shared<Ship>(*ship);
			shipValue_->parent_(this);
		}
		nameValue_ = other.nameValue_;
	}

    Character::~Character() {
        if (shipValue_ != nullptr) {
            shipValue_->parent_(nullptr);
        }
        for (const auto& i: skillsMap_) {
            i.second->parent_(nullptr);
        }
        for (const auto& i: implantsSet_) {
            i->parent_(nullptr);
        }
        for (const auto& i: boostersSet_) {
            i->parent_(nullptr);
        }

    }

	void Character::ship_(const std::shared_ptr<Ship>& ship) {
        assert(ship == nullptr || ship->parent() == nullptr);
        
		batchUpdates_([&]() {
			auto enabled = isEnabled_();
			if (enabled)
				setEnabled_(false);
			
			if (shipValue_) {
				shipValue_->parent_(nullptr);
				shipValue_ = nullptr;
			}
			
			if (ship != nullptr) {
				shipValue_ = ship;
				shipValue_->parent_(this);
			}
			
			if (enabled)
				setEnabled_(true);
		});
	}
	
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
	
	void Character::add_(const std::shared_ptr<Implant>& implant, bool replace) {
        assert(implant != nullptr && implant->parent() == nullptr);
            
		auto old = implantsSet_.find(implant->slot());
		if (old != implantsSet_.end()) {
			if (replace) {
				(*old)->parent_(nullptr);
				implantsSet_.erase(old);
			}
			else
				throw CannotFit<Implant>(implant);
		}

		implantsSet_.insert(implant);
		implant->parent_(this);
	}
	
	void Character::add_(const std::shared_ptr<Booster>& booster, bool replace) {
        assert(booster != nullptr && booster->parent() == nullptr);

        auto old = boostersSet_.find(booster->slot());
		if (old != boostersSet_.end()) {
			if (replace) {
				(*old)->parent_(nullptr);
				boostersSet_.erase(old);
			}
			else
				throw CannotFit<Booster>(booster);
		}
		
		boostersSet_.insert(booster);
		booster->parent_(this);
	}
	
	void Character::remove_(Implant* implant) {
        assert(implant != nullptr && implant->parent() == this);
		auto i = implantsSet_.find(implant);
		assert(i != implantsSet_.end());
		(*i)->parent_(nullptr);
		implantsSet_.erase(i);
	}
	
	void Character::remove_(Booster* booster) {
        assert(booster != nullptr && booster->parent() == this);
		auto i = boostersSet_.find(booster);
		assert(i != boostersSet_.end());
		(*i)->parent_(nullptr);
		boostersSet_.erase(i);
	}
	
	std::vector<std::shared_ptr<Skill>> Character::skills_() const {
		std::vector<std::shared_ptr<Skill>> result;
		result.reserve(skillsMap_.size());
		std::transform(skillsMap_.begin(), skillsMap_.end(), std::back_inserter(result), [](const auto& i) { return i.second; });
		return result;
	}

	std::vector<std::shared_ptr<Implant>> Character::implants_() const {
		std::vector<std::shared_ptr<Implant>> result;
		result.reserve(implantsSet_.size());
		std::transform(implantsSet_.begin(), implantsSet_.end(), std::back_inserter(result), [](const auto& i) { return i; });
		return result;
	}
	
	std::vector<std::shared_ptr<Booster>> Character::boosters_() const {
		std::vector<std::shared_ptr<Booster>> result;
		result.reserve(boostersSet_.size());
		std::transform(boostersSet_.begin(), boostersSet_.end(), std::back_inserter(result), [](const auto& i) { return i; });
		return result;
	}

	std::shared_ptr<Implant> Character::implant_ (Implant::Slot slot) const noexcept {
		auto i = implantsSet_.find(slot);
		return i != implantsSet_.end() ? *i : nullptr;
	}
	
	std::shared_ptr<Booster> Character::booster_ (Booster::Slot slot) const noexcept {
		auto i = boostersSet_.find(slot);
		return i != boostersSet_.end() ? *i : nullptr;
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
