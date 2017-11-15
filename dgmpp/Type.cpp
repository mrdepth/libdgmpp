//
//  Type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 30.10.2017.
//

#include "Type.hpp"
#include "Attribute.h"
#include "Effect.h"
#include <utility>
#include "SDE.hpp"


namespace dgmpp2 {
	
	/*(struct Type::AttributeIDComparator {
		bool operator()(const Modifier* a, const Modifier* b) const {
			return a->metaInfo().modifiedAttributeID < b->metaInfo().modifiedAttributeID;
		}
		
		bool operator()(const Modifier* a, AttributeID b) const {
			return a->metaInfo().modifiedAttributeID < b;
		}
		
		bool operator()(AttributeID a, const Modifier* b) const {
			return a < b->metaInfo().modifiedAttributeID;
		}
		
	};*/
	
	struct ModifierComparator {
		
		bool operator() (const Modifier* lhs, AttributeID rhs) {
			return lhs->metaInfo().modifiedAttributeID < rhs;
		}

		bool operator() (AttributeID lhs, const Modifier* rhs) {
			return lhs < rhs->metaInfo().modifiedAttributeID;
		}

		bool operator() (const Modifier* lhs, const std::pair<AttributeID, GroupID>& rhs) {
			const auto& l = lhs->metaInfo();
			if (l.modifiedAttributeID == rhs.first)
				return l.require.groupID < rhs.second;
			else
				return l.modifiedAttributeID < rhs.first;
		}

		bool operator() (const std::pair<AttributeID, GroupID>& lhs, const Modifier* rhs) {
			const auto& r = rhs->metaInfo();
			if (r.modifiedAttributeID == lhs.first)
				return lhs.second < r.require.groupID;
			else
				return lhs.first < r.modifiedAttributeID;
		}

		bool operator() (const std::pair<TypeID, const Modifier*>& lhs, const std::pair<AttributeID, TypeID>& rhs) {
			const auto& l = lhs.second->metaInfo();
			if (l.modifiedAttributeID == rhs.first)
				return lhs.first < rhs.second;
			else
				return l.modifiedAttributeID < rhs.first;
		}

		bool operator() (const std::pair<AttributeID, TypeID>& lhs, const std::pair<TypeID, const Modifier*>& rhs) {
			const auto& r = rhs.second->metaInfo();
			if (r.modifiedAttributeID == lhs.first)
				return lhs.second < rhs.first;
			else
				return lhs.first < r.modifiedAttributeID;
		}

		bool operator() (const std::pair<TypeID, const Modifier*>& lhs, AttributeID rhs) {
			return lhs.second->metaInfo().modifiedAttributeID < rhs;
		}
		
		bool operator() (AttributeID lhs, const std::pair<TypeID, const Modifier*>& rhs) {
			return lhs < rhs.second->metaInfo().modifiedAttributeID;
		}

	};
	
	struct EffectComparator {
		
		bool operator() (const std::unique_ptr<Effect>& lhs, MetaInfo::Effect::Category rhs) {
			return lhs->metaInfo().category < rhs;
		}
		
		bool operator() (MetaInfo::Effect::Category lhs, const std::unique_ptr<Effect>& rhs) {
			return lhs < rhs->metaInfo().category;
		}
	};
	
	
	Type::Type (TypeID typeID) : Type (SDE::get(typeID)) {}

	Type::Type (const MetaInfo::Type& metaInfo): metaInfo_(metaInfo) {
		
		for (const auto& i: metaInfo.attributes)
			attributes_.emplace(i.first.attributeID, new Attribute(i.first, i.second, *this));
		
		effects_.reserve(metaInfo.effects.size());
		
		for (const auto& i: metaInfo.effects)
			effects_.push_back(std::unique_ptr<Effect>(new Effect(i, *this)));
	}
	
	Attribute::Proxy Type::operator[] (AttributeID attributeID) {
		return {*this, attributes_.emplace(attributeID, nullptr).first};
	}

	Effect* Type::operator[] (EffectID effectID) const {
		auto i = std::find_if(effects_.begin(), effects_.end(), [=](const auto& a) {
			return a->metaInfo().effectID == effectID;
		});
		return i != effects_.end() ? i->get() : nullptr;
//		auto i = std::lower_bound(effects_.begin(), effects_.end(), effectID, [] (const auto& a, auto b) {
//			return a->metaInfo().effectID < b;
//		});
//		return i != effects_.end() && (*i)->metaInfo().effectID == effectID ? i->get() : nullptr;
	}
	
	void Type::setEnabled (bool enabled) {
		if (enabled == enabled_)
			return;

		enabled_ = enabled;

		if (enabled)
			activateEffects(MetaInfo::Effect::Category::generic);
		else
			deactivateEffects(MetaInfo::Effect::Category::generic);

		for (const auto& child: children_) {
			if (child->isEnabled() != enabled)
				child->setEnabled(enabled);
		}
	}

	void Type::remove (Type* child) {
		assert(child->parent() == this);
		
		if (child->isEnabled())
			child->setEnabled(false);
		
		child->parent(nullptr);
		
		auto i = std::find_if(children_.begin(), children_.end(), [=](const auto& i) { return i.get() == child; });
		assert(i != children_.end());
		children_.erase(i);
	}
	
	void Type::addModifier(const Modifier* modifier) {
		switch (modifier->metaInfo().type) {
			case MetaInfo::Modifier::ModifierType::item : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (itemModifiers_.find(key) == itemModifiers_.end());
				itemModifiers_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::location : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (locationModifiers_.find(key) == locationModifiers_.end());
				locationModifiers_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationGroup : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier->metaInfo().require.groupID, modifier);
				assert (locationGroupModifiers_.find(key) == locationGroupModifiers_.end());
				locationGroupModifiers_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredSkill :
			case MetaInfo::Modifier::ModifierType::ownerRequiredSkill : {
				auto skillID = modifier->metaInfo().require.typeID;
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
				assert (locationRequiredSkillModifiers_.find(key) == locationRequiredSkillModifiers_.end());
				locationRequiredSkillModifiers_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredDomainSkill : {
				if (auto type = modifier->owner().domain(modifier->metaInfo().require.domain)) {
					auto skillID = type->metaInfo().typeID;
					auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
					assert (locationRequiredSkillModifiers_.find(key) == locationRequiredSkillModifiers_.end());
					locationRequiredSkillModifiers_.insert(key);
					break;
				}
				break;
			}
				
			default:
				assert(!"Invalid MetaInfo::Modifier::ModifierType value");
		}
		resetCache();
	}
	
	void Type::removeModifier (const Modifier* modifier) {
		
		switch (modifier->metaInfo().type) {
			case MetaInfo::Modifier::ModifierType::item : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (itemModifiers_.find(key) != itemModifiers_.end());
				itemModifiers_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::location : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (locationModifiers_.find(key) != locationModifiers_.end());
				locationModifiers_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationGroup : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier->metaInfo().require.groupID, modifier);
				assert (locationGroupModifiers_.find(key) != locationGroupModifiers_.end());
				locationGroupModifiers_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredSkill :
			case MetaInfo::Modifier::ModifierType::ownerRequiredSkill : {
				auto skillID = modifier->metaInfo().require.typeID;
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
				assert (locationRequiredSkillModifiers_.find(key) != locationRequiredSkillModifiers_.end());
				locationRequiredSkillModifiers_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredDomainSkill : {
				if (auto type = modifier->owner().domain(modifier->metaInfo().require.domain)) {
					auto skillID = type->metaInfo().typeID;
					auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
					assert (locationRequiredSkillModifiers_.find(key) != locationRequiredSkillModifiers_.end());
					locationRequiredSkillModifiers_.erase(key);
					break;
				}
				break;
			}
				
			default:
				assert(!"Invalid MetaInfo::Modifier::ModifierType value");
		}
		resetCache();
	}

	std::list<const Modifier*> Type::itemModifiers (const MetaInfo::Attribute& attribute) const {
		auto key = std::make_tuple(attribute.attributeID);
		auto range = equal_range(itemModifiers_, key);
		std::list<const Modifier*> result;
		std::transform(range.first, range.second, std::back_inserter(result), [](const auto& i) { return std::get<const Modifier*>(i); });
		return result;
	}

	std::list<const Modifier*> Type::locationModifiers (const MetaInfo::Attribute& attribute) const {
		auto key = std::make_tuple(attribute.attributeID);
		auto range = equal_range(locationModifiers_, key);
		std::list<const Modifier*> result;
		std::transform(range.first, range.second, std::back_inserter(result), [](const auto& i) { return std::get<const Modifier*>(i); });
		return result;
	}
	
	std::list<const Modifier*> Type::locationGroupModifiers (const MetaInfo::Attribute& attribute, const Type& type) const {
		auto key = std::make_tuple(attribute.attributeID, type.metaInfo().groupID);
		auto range = equal_range(locationGroupModifiers_, key);

		std::list<const Modifier*> result;
		std::transform(range.first, range.second, std::back_inserter(result), [](const auto& i) { return std::get<const Modifier*>(i); });
		return result;
	}
	
	std::list<const Modifier*> Type::locationRequiredSkillModifiers (const MetaInfo::Attribute& attribute, const Type& type) const {
		auto attributeID = attribute.attributeID;
		auto key = std::make_tuple(attributeID);
		auto range = locationRequiredSkillModifiers_.equal_range(key);

		if (range.first != range.second) {
//			auto subset = decltype(locationRequiredSkillModifiers_)(range.first, range.second);
			auto &subset = locationRequiredSkillModifiers_;
			
			for (auto skillID: type.metaInfo().requiredSkills) {
				auto key = std::make_tuple(attributeID, skillID);
				auto result = subset.equal_range(key);
				
				if (result.first != result.second) {
					std::list<const Modifier*> list;
					std::transform(range.first, range.second, std::back_inserter(list), [](const auto& i) { return std::get<const Modifier*>(i); });
					return list;
				}
			}
		}
		return {};
	}
	
	std::list<const Modifier*> Type::modifiers (const MetaInfo::Attribute& attribute) const {
		std::list<const Modifier*> result;
		result.splice(result.end(), itemModifiers(attribute));
		if (auto parent = this->parent()) {
			result.splice(result.end(), parent->locationModifiers(attribute));
			result.splice(result.end(), parent->modifiersMatchingType(attribute, *this));
		}
		return result;
	}
	
	std::list<const Modifier*> Type::modifiersMatchingType (const MetaInfo::Attribute& attribute, const Type& type) const {
		std::list<const Modifier*> result;
		result.splice(result.end(), locationGroupModifiers(attribute, type));
		result.splice(result.end(), locationRequiredSkillModifiers(attribute, type));
		if (auto parent = this->parent()) {
			result.splice(result.end(), parent->modifiersMatchingType(attribute, *this));
		}
		return result;
	}
	
	void Type::activateEffects (MetaInfo::Effect::Category category) {
		auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
		std::for_each(range.first, range.second, [&](const auto& i) {
			if (!i->active()) {
				activate(i.get());
			}
		});

		if (category != MetaInfo::Effect::Category::generic) {
			for (const auto& child: children_)
				child->activateEffects(category);
		}
	}
	
	void Type::deactivateEffects (MetaInfo::Effect::Category category) {
		auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
		std::for_each(range.first, range.second, [&](const auto& i) {
			if (i->active()) {
				deactivate(i.get());
			}
		});
		
		if (category != MetaInfo::Effect::Category::generic) {
			for (const auto& child: children_)
				child->deactivateEffects(category);
		}
	}
	
	void Type::activate (Effect* effect) {
		effect->active(true);
		for (const auto& modifier: effect->modifiers()) {
			if (auto type = modifier.domain())
				type->addModifier(&modifier);
		}
	}
	
	void Type::deactivate (Effect* effect) {
		effect->active(false);
		for (const auto& modifier: effect->modifiers()) {
			if (auto type = modifier.domain())
				type->removeModifier(&modifier);
		}
	}

	std::vector<Effect*> Type::activeEffects() const {
		std::vector<Effect*> effects;
		effects.reserve(effects_.size());
		
		for (const auto& effect: effects_) {
			if (effect->active())
				effects.push_back(effect.get());
		}
		return effects;
	}
	
	void Type::reset() {
//		for (const auto& child: children_) {
//			child->reset();
//		}
	}
	
	void Type::resetCache() {
		cache().reset();
	}
	
	Type* Type::domain (MetaInfo::Modifier::Domain domain) {
		if (domain == MetaInfo::Modifier::Domain::self)
			return this;
		else if (auto parent = this->parent())
			return parent->domain(domain);
		else
			return nullptr;
	}
	
	Type::AttributesCache& Type::cache() {
		if (cache_ != nullptr)
			return *cache_;
		else if (auto parent = this->parent()) {
			return parent->cache();
		}
		else {
			cache_ = std::unique_ptr<Type::AttributesCache>(new Type::AttributesCache);
			return *cache_;
		}
	}
}
