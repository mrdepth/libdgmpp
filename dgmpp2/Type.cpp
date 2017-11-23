//
//  Type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 30.10.2017.
//

#include <utility>
#include "Type.hpp"
#include "SDE.hpp"


namespace dgmpp2 {
	
	struct EffectComparator {
		
		bool operator() (const std::unique_ptr<Effect>& lhs, MetaInfo::Effect::Category rhs) {
			return lhs->metaInfo().category < rhs;
		}
		
		bool operator() (MetaInfo::Effect::Category lhs, const std::unique_ptr<Effect>& rhs) {
			return lhs < rhs->metaInfo().category;
		}
	};
	
	Type::~Type() {
	}
	
	Type::Type (TypeID typeID) : Type (SDE::get(typeID)) {
//		children_.reserve(410);
	}

	Type::Type (const MetaInfo::Type& metaInfo): metaInfo_(metaInfo) {
		
		for (const auto& i: metaInfo.attributes())
			attributes_.emplace(i.first->attributeID, new Attribute(*i.first, i.second, *this));
		
		effects_.reserve(metaInfo.effects().size());
		
		for (const auto& i: metaInfo.effects())
			effects_.push_back(std::unique_ptr<Effect>(new Effect(*i, *this)));
	}
	
	void Type::parent (Type* parent) {
		if (isEnabled())
			setEnabled(false);
		
		if (parent_)
			cache_ = cache().extract(this);
		
		if (parent && cache_) {
			parent->cache().splice(std::move(*cache_));
			cache_ = nullptr;
		}

		parent_ = parent;
		
		if (parent && parent->isEnabled())
			setEnabled(true);
	}
	
	void Type::batchUpdates(std::function<void()> updates) {
		cache().batchUpdates(updates);
	}
	
	Attribute::Proxy Type::operator[] (AttributeID attributeID) {
		return {*this, attributes_.emplace(attributeID, nullptr).first};
	}

	Effect* Type::operator[] (EffectID effectID) const {
		auto i = std::find_if(effects_.begin(), effects_.end(), [=](const auto& a) {
			return a->metaInfo().effectID == effectID;
		});
		return i != effects_.end() ? i->get() : nullptr;
	}
	
	void Type::setEnabled (bool enabled) {
		if (enabled == enabled_)
			return;

		enabled_ = enabled;

		if (enabled)
			activateEffects(MetaInfo::Effect::Category::generic);
		else
			deactivateEffects(MetaInfo::Effect::Category::generic);

		if (enabled)
			reset();
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
		auto range = equal_range(locationRequiredSkillModifiers_, key);

		if (range.first != range.second) {
			auto subset = decltype(locationRequiredSkillModifiers_)(range.first, range.second);
//			auto &subset = locationRequiredSkillModifiers_;
			
			std::list<const Modifier*> list;
			for (auto skillID: type.metaInfo().requiredSkills()) {
				auto key = std::make_tuple(attributeID, skillID);
				auto result = equal_range(subset, key);
				
				if (result.first != result.second) {
					std::transform(result.first, result.second, std::back_inserter(list), [](const auto& i) { return std::get<const Modifier*>(i); });
				}
			}
			return list;
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
		batchUpdates([&]() {
			auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
			std::for_each(range.first, range.second, [&](const auto& i) {
				if (!i->active()) {
					activate(i.get());
				}
			});
		});
	}
	
	void Type::deactivateEffects (MetaInfo::Effect::Category category) {
		batchUpdates([&]() {
			auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
			std::for_each(range.first, range.second, [&](const auto& i) {
				if (i->active()) {
					deactivate(i.get());
				}
			});
		});
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
