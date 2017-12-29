//
//  Type.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 30.10.2017.
//

#include <utility>
#include "Type.hpp"
#include "SDE.hpp"
#include <numeric>

namespace dgmpp {
	
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
	}

	Type::Type (const MetaInfo::Type& metaInfo): metaInfo_(metaInfo) {
		
		for (const auto& i: metaInfo.attributes())
			attributes_.emplace(i.first->attributeID, new Attribute(*i.first, i.second, *this));
		
		effects_.reserve(metaInfo.effects().size());
		
		for (auto i: metaInfo.effects()) {
			if (i->effectID == EffectID::gangBoost)
				effects_.push_back(std::unique_ptr<Effect>(new WarfareBuffEffect(*i, *this)));
			else
				effects_.push_back(std::unique_ptr<Effect>(new Effect(*i, *this)));
		}
	}
	
	Type::Type (const Type& other): Type(other.metaInfo_) {
		for (const auto& i: other.attributes_) {
			if (i.second && i.second->forcedValue_) {
				*attribute(i.second->metaInfo_.attributeID) = *i.second->forcedValue_;
			}
		}
		identifier_ = other.identifier_;
	}
	
	void Type::parent_ (Type* parent) {
		if (isEnabled())
			setEnabled(false);
		
		if (parentType_)
			cache_ = cache().extract(this);
		
		if (parent && cache_) {
			parent->cache().splice(std::move(*cache_));
			cache_ = nullptr;
		}

		parentType_ = parent;
		
		if (parent && parent->isEnabled())
			setEnabled(true);
	}
	
	void Type::batchUpdates(std::function<void()> updates) {
		cache().batchUpdates(updates);
	}
	
	Attribute::Proxy Type::attribute (AttributeID attributeID) {
		return {*this, attributes_.emplace(attributeID, nullptr).first};
	}

	Effect* Type::effect (EffectID effectID) const {
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
			resetCache();
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
		if (auto parent = parent_()) {
			result.splice(result.end(), parent->locationModifiers(attribute));
			result.splice(result.end(), parent->modifiersMatchingType(attribute, *this));
		}
		return result;
	}
	
	std::list<const Modifier*> Type::modifiersMatchingType (const MetaInfo::Attribute& attribute, const Type& type) const {
		std::list<const Modifier*> result;
		result.splice(result.end(), locationGroupModifiers(attribute, type));
		result.splice(result.end(), locationRequiredSkillModifiers(attribute, type));
		if (auto parent = parent_()) {
			result.splice(result.end(), parent->modifiersMatchingType(attribute, *this));
		}
		
		
		if (!buffs_.empty()) {
			
			std::map<std::pair<WarfareBuffID, AttributeID>, std::pair<Float, const Modifier*>> modifiers;
			
			for (const auto& buff: buffs_) {
				for (const auto& modifier: std::get<const WarfareBuff*>(buff)->modifiers()) {
					if (modifier.metaInfo().modifiedAttributeID == attribute.attributeID && modifier.match(&type)) {
						auto key = std::make_pair(std::get<WarfareBuffID>(buff), modifier.metaInfo().modifyingAttributeID);
						auto v = std::abs(modifier.value());

						auto i = modifiers.find(key);
						if (i == modifiers.end() || i->second.first < v) {
							modifiers[key] = std::make_pair(v, &modifier);
						}
					}
				}
			}
			std::transform(modifiers.begin(), modifiers.end(), std::back_inserter(result), [](const auto& i) { return i.second.second; });

			/*std::vector<std::tuple<Float, WarfareBuffID, const WarfareBuff*>> v;
			v.reserve(buffs_.size());
			std::transform(buffs_.begin(), buffs_.end(), std::back_inserter(v), [](const auto& i) {
				return std::tuple_cat(std::make_tuple(std::abs(std::get<const WarfareBuff*>(i)->value_())), i);
			});
			
			auto i = v.begin();
			while (i != v.end()) {
				auto j =std::upper_bound(i, v.end(), std::get<WarfareBuffID>(*i), [](auto id, const auto& v) {
					return id < std::get<WarfareBuffID>(v);
				});
				auto max = std::max_element(i, j, [](const auto& a, const auto& b) {
					return std::get<Float>(a) < std::get<Float>(b);
				});
				
				for (const auto& m: std::get<const WarfareBuff*>(*max)->modifiers()) {
					if (m.metaInfo().modifiedAttributeID == attribute.attributeID && m.match(&type))
						result.push_back(&m);
				}
				
				i = j;
			}*/
		}
		return result;
	}
	
	void Type::activateEffects (MetaInfo::Effect::Category category) {
		batchUpdates([&]() {
			auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
			std::for_each(range.first, range.second, [&](const auto& i) {
				if (!i->isActive()) {
					activate(i.get());
				}
			});
		});
	}
	
	void Type::deactivateEffects (MetaInfo::Effect::Category category) {
		batchUpdates([&]() {
			auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
			std::for_each(range.first, range.second, [&](const auto& i) {
				if (i->isActive()) {
					deactivate(i.get());
				}
			});
		});
	}
	
	void Type::activate (Effect* effect) {
		effect->setActive(true);
		for (const auto& modifier: effect->modifiers()) {
			if (auto type = modifier.domain())
				type->addModifier(&modifier);
		}
		if (auto warfareBuffEffect = dynamic_cast<WarfareBuffEffect*>(effect)) {
			if (auto gang = domain(MetaInfo::Modifier::Domain::gang)) {
				for (const auto& buff: warfareBuffEffect->warfareBuffs())
					gang->addBuff(&buff);
			}
		}
	}
	
	void Type::deactivate (Effect* effect) {
		if (auto warfareBuffEffect = dynamic_cast<WarfareBuffEffect*>(effect)) {
			if (auto gang = domain(MetaInfo::Modifier::Domain::gang)) {
				for (const auto& buff: warfareBuffEffect->warfareBuffs())
					gang->removeBuff(&buff);
			}
		}
		effect->setActive(false);
		for (const auto& modifier: effect->modifiers()) {
			if (auto type = modifier.domain())
				type->removeModifier(&modifier);
		}
	}

	std::vector<Effect*> Type::activeEffects() const {
		std::vector<Effect*> effects;
		effects.reserve(effects_.size());
		
		for (const auto& effect: effects_) {
			if (effect->isActive())
				effects.push_back(effect.get());
		}
		return effects;
	}
	
	void Type::reset() {
	}
	
	void Type::resetCache() {
		cache().reset();
	}
	
	Type* Type::domain (MetaInfo::Modifier::Domain domain) noexcept {
		if (domain == MetaInfo::Modifier::Domain::self)
			return this;
		else if (auto parent = parent_())
			return parent->domain(domain);
		else
			return nullptr;
	}
	
	Type::AttributesCache& Type::cache() {
		if (cache_ != nullptr)
			return *cache_;
		else if (auto parent = parent_()) {
			return parent->cache();
		}
		else {
			cache_ = std::unique_ptr<Type::AttributesCache>(new Type::AttributesCache);
			return *cache_;
		}
	}
	
	void Type::addBuff (const WarfareBuff* buff) {
		auto key = std::make_tuple(buff->metaInfo().warfareBuffID, buff);
		assert (buffs_.find(key) == buffs_.end());
		buffs_.insert(key);
	}
	
	void Type::removeBuff (const WarfareBuff* buff) {
		auto key = std::make_tuple(buff->metaInfo().warfareBuffID, buff);
		assert (buffs_.find(key) != buffs_.end());
		buffs_.erase(key);
	}

	std::unordered_set<Type*> Type::affectors() const {
		std::unordered_set<Type*> types;
		for (const auto& i: attributes_) {
			for (const auto& j: modifiers(i.second->metaInfo())) {
				types.insert(&j->owner());
			}
		}
		return types;
	}
	
	std::list<Attribute*> Type::attributes() const {
		std::list<Attribute*> attributes;
		for (const auto& i: attributes_) {
			if (i.second) {
				attributes.push_back(i.second.get());
			}
		}
		return attributes;
	}
}
