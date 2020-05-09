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
			attributesMap_.emplace(i.first->attributeID, new Attribute(*i.first, i.second, *this));
		
		effects_.reserve(metaInfo.effects().size());
		
		for (auto i: metaInfo.effects()) {
			if (i->effectID == EffectID::gangBoost)
				effects_.push_back(std::unique_ptr<Effect>(new WarfareBuffEffect(*i, *this)));
			else
				effects_.push_back(std::unique_ptr<Effect>(new Effect(*i, *this)));
		}
	}
	
	Type::Type (const Type& other): Type(other.metaInfo_) {
		for (const auto& i: other.attributesMap_) {
			if (i.second && i.second->forcedValue_) {
				*attribute_(i.second->metaInfo_.attributeID) = *i.second->forcedValue_;
			}
		}
		identifierValue_ = other.identifierValue_;
	}
	
	void Type::parent_ (Type* parent) {
		if (isEnabled_())
			setEnabled_(false);
		
		if (parentType_)
			cacheValue_ = cache_().extract(this);
		
		if (parent) {
			if (cacheValue_) {
				parent->cache_().splice(std::move(*cacheValue_));
				cacheValue_ = nullptr;
			}
#if DGMPP_THREADSAFE
			if (mutexValue_)
				mutexValue_ = nullptr;
#endif
		}

		parentType_ = parent;
		
		if (parent && parent->isEnabled_())
			setEnabled_(true);
	}
	
	void Type::batchUpdates_(std::function<void()> updates) {
		cache_().batchUpdates(updates);
	}
	
	Attribute::Proxy Type::attribute_ (AttributeID attributeID) {
		return {*this, attributesMap_.emplace(attributeID, nullptr).first};
	}

	Effect* Type::effect_ (EffectID effectID) const {
		auto i = std::find_if(effects_.begin(), effects_.end(), [=](const auto& a) {
			return a->metaInfo().effectID == effectID;
		});
		return i != effects_.end() ? i->get() : nullptr;
	}
	
	void Type::setEnabled_ (bool enabled) {
		if (enabled == enabled_)
			return;

		enabled_ = enabled;

		if (enabled)
			activateEffects_(MetaInfo::Effect::Category::passive);
		else
			deactivateEffects_(MetaInfo::Effect::Category::passive);

		if (enabled)
			resetCache_();
	}

	void Type::addModifier_(const Modifier* modifier) {
		switch (modifier->metaInfo().type) {
			case MetaInfo::Modifier::ModifierType::item : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (itemModifiersSet_.find(key) == itemModifiersSet_.end());
				itemModifiersSet_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::location : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (locationModifiersSet_.find(key) == locationModifiersSet_.end());
				locationModifiersSet_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationGroup : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier->metaInfo().require.groupID, modifier);
				assert (locationGroupModifiersSet_.find(key) == locationGroupModifiersSet_.end());
				locationGroupModifiersSet_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredSkill :
			case MetaInfo::Modifier::ModifierType::ownerRequiredSkill : {
				auto skillID = modifier->metaInfo().require.typeID;
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
				assert (locationRequiredSkillModifiersSet_.find(key) == locationRequiredSkillModifiersSet_.end());
				locationRequiredSkillModifiersSet_.insert(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredDomainSkill : {
				if (auto type = modifier->owner().domain_(modifier->metaInfo().require.domain)) {
					auto skillID = type->metaInfo().typeID;
					auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
					assert (locationRequiredSkillModifiersSet_.find(key) == locationRequiredSkillModifiersSet_.end());
					locationRequiredSkillModifiersSet_.insert(key);
					break;
				}
				break;
			}
				
			default:
				assert(!"Invalid MetaInfo::Modifier::ModifierType value");
		}
		resetCache_();
	}
	
	void Type::removeModifier_ (const Modifier* modifier) {
		
		switch (modifier->metaInfo().type) {
			case MetaInfo::Modifier::ModifierType::item : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (itemModifiersSet_.find(key) != itemModifiersSet_.end());
				itemModifiersSet_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::location : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier);
				assert (locationModifiersSet_.find(key) != locationModifiersSet_.end());
				locationModifiersSet_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationGroup : {
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, modifier->metaInfo().require.groupID, modifier);
				assert (locationGroupModifiersSet_.find(key) != locationGroupModifiersSet_.end());
				locationGroupModifiersSet_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredSkill :
			case MetaInfo::Modifier::ModifierType::ownerRequiredSkill : {
				auto skillID = modifier->metaInfo().require.typeID;
				auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
				assert (locationRequiredSkillModifiersSet_.find(key) != locationRequiredSkillModifiersSet_.end());
				locationRequiredSkillModifiersSet_.erase(key);
				break;
			}
				
			case MetaInfo::Modifier::ModifierType::locationRequiredDomainSkill : {
				if (auto type = modifier->owner().domain_(modifier->metaInfo().require.domain)) {
					auto skillID = type->metaInfo().typeID;
					auto key = std::make_tuple(modifier->metaInfo().modifiedAttributeID, skillID, modifier);
					assert (locationRequiredSkillModifiersSet_.find(key) != locationRequiredSkillModifiersSet_.end());
					locationRequiredSkillModifiersSet_.erase(key);
					break;
				}
				break;
			}
				
			default:
				assert(!"Invalid MetaInfo::Modifier::ModifierType value");
		}
		resetCache_();
	}

	std::list<const Modifier*> Type::itemModifiers_ (const MetaInfo::Attribute& attribute) {
		auto key = std::make_tuple(attribute.attributeID);
		auto range = equal_range(itemModifiersSet_, key);
		std::list<const Modifier*> result;
		std::transform(range.first, range.second, std::back_inserter(result), [](const auto& i) { return std::get<const Modifier*>(i); });
		return result;
	}

	std::list<const Modifier*> Type::locationModifiers_ (const MetaInfo::Attribute& attribute) {
		auto key = std::make_tuple(attribute.attributeID);
		auto range = equal_range(locationModifiersSet_, key);
		std::list<const Modifier*> result;
		std::transform(range.first, range.second, std::back_inserter(result), [](const auto& i) { return std::get<const Modifier*>(i); });
		return result;
	}
	
	std::list<const Modifier*> Type::locationGroupModifiers_ (const MetaInfo::Attribute& attribute, Type& type) {
		auto key = std::make_tuple(attribute.attributeID, type.metaInfo().groupID);
		auto range = equal_range(locationGroupModifiersSet_, key);

		std::list<const Modifier*> result;
		std::transform(range.first, range.second, std::back_inserter(result), [](const auto& i) { return std::get<const Modifier*>(i); });
		return result;
	}
	
	std::list<const Modifier*> Type::locationRequiredSkillModifiers_ (const MetaInfo::Attribute& attribute, Type& type) {
		auto attributeID = attribute.attributeID;
		auto key = std::make_tuple(attributeID);
		auto range = equal_range(locationRequiredSkillModifiersSet_, key);

		if (range.first != range.second) {
			auto subset = decltype(locationRequiredSkillModifiersSet_)(range.first, range.second);
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
	
	std::list<const Modifier*> Type::modifiers_ (const MetaInfo::Attribute& attribute) {
		std::list<const Modifier*> result;
		result.splice(result.end(), itemModifiers_(attribute));
		if (auto parent = owner_()) {
			result.splice(result.end(), parent->locationModifiers_(attribute));
			result.splice(result.end(), parent->modifiersMatchingType_(attribute, *this));
		}
		return result;
	}
	
	std::list<const Modifier*> Type::modifiersMatchingType_ (const MetaInfo::Attribute& attribute, Type& type) {
		std::list<const Modifier*> result;
		result.splice(result.end(), locationGroupModifiers_(attribute, type));
		result.splice(result.end(), locationRequiredSkillModifiers_(attribute, type));
		if (auto parent = parent_()) {
			result.splice(result.end(), parent->modifiersMatchingType_(attribute, type));
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
	
	void Type::activateEffects_ (MetaInfo::Effect::Category category) {
		batchUpdates_([&]() {
			auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
			std::for_each(range.first, range.second, [&](const auto& i) {
				if (!i->isActive()) {
					activate_(i.get());
				}
			});
		});
	}
	
	void Type::deactivateEffects_ (MetaInfo::Effect::Category category) {
		batchUpdates_([&]() {
			auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
			std::for_each(range.first, range.second, [&](const auto& i) {
				if (i->isActive()) {
					deactivate_(i.get());
				}
			});
		});
	}
	
	void Type::activate_ (Effect* effect) {
		effect->setActive_(true);
		for (const auto& modifier: effect->modifiers()) {
			if (auto type = modifier.domain())
				type->addModifier_(&modifier);
		}
		if (auto warfareBuffEffect = dynamic_cast<WarfareBuffEffect*>(effect)) {
			if (auto gang = domain_(MetaInfo::Modifier::Domain::gang)) {
				for (const auto& buff: warfareBuffEffect->warfareBuffs())
					gang->addBuff_(&buff);
			}
		}
	}
	
	void Type::deactivate_ (Effect* effect) {
		if (auto warfareBuffEffect = dynamic_cast<WarfareBuffEffect*>(effect)) {
			if (auto gang = domain_(MetaInfo::Modifier::Domain::gang)) {
				for (const auto& buff: warfareBuffEffect->warfareBuffs())
					gang->removeBuff_(&buff);
			}
		}
		effect->setActive_(false);
		for (const auto& modifier: effect->modifiers()) {
			if (auto type = modifier.domain())
				type->removeModifier_(&modifier);
		}
	}

	std::vector<Effect*> Type::activeEffects_() const {
		std::vector<Effect*> effects;
		effects.reserve(effects_.size());
		
		for (const auto& effect: effects_) {
			if (effect->isActive())
				effects.push_back(effect.get());
		}
		return effects;
	}
	
	void Type::resetCache_() {
		cache_().reset();
	}
	
	Type* Type::domain_ (MetaInfo::Modifier::Domain domain) noexcept {
		if (domain == MetaInfo::Modifier::Domain::self)
			return this;
		else if (auto parent = parent_())
			return parent->domain_(domain);
		else
			return nullptr;
	}
	
	Type::AttributesCache& Type::cache_() {
		if (cacheValue_ != nullptr)
			return *cacheValue_;
		else if (auto parent = parent_()) {
			return parent->cache_();
		}
		else {
			cacheValue_ = std::unique_ptr<Type::AttributesCache>(new Type::AttributesCache);
			return *cacheValue_;
		}
	}
	
	void Type::addBuff_ (const WarfareBuff* buff) {
		auto key = std::make_tuple(buff->metaInfo().warfareBuffID, buff);
		assert (buffs_.find(key) == buffs_.end());
		buffs_.insert(key);
	}
	
	void Type::removeBuff_ (const WarfareBuff* buff) {
		auto key = std::make_tuple(buff->metaInfo().warfareBuffID, buff);
		assert (buffs_.find(key) != buffs_.end());
		buffs_.erase(key);
	}

	std::unordered_set<Type*> Type::affectors_() {
		std::unordered_set<Type*> types;
		for (const auto& i: attributesMap_) {
			if (i.second) {
				for (const auto& j: modifiers_(i.second->metaInfo())) {
					types.insert(&j->owner());
				}
			}
		}
		return types;
	}
	
	std::list<Attribute*> Type::attributes_() const {
		std::list<Attribute*> attributes;
		for (const auto& i: attributesMap_) {
			if (i.second) {
				attributes.push_back(i.second.get());
			}
		}
		return attributes;
	}
	
#if DGMPP_THREADSAFE
	std::mutex& Type::mutex_() const noexcept {
		if (mutexValue_ != nullptr)
			return *mutexValue_;
		else if (auto parent = parent_())
			return parent->mutex_();
		else {
			mutexValue_ = std::unique_ptr<std::mutex>(new std::mutex);
			return *mutexValue_;
		}
	}
#endif
}
