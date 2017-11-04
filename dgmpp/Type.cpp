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
		bool operator() (const std::unique_ptr<Effect>& lhs, Effect::MetaInfo::Category rhs) {
			return lhs->metaInfo().category < rhs;
		}
		
		bool operator() (Effect::MetaInfo::Category lhs, const std::unique_ptr<Effect>& rhs) {
			return lhs < rhs->metaInfo().category;
		}
	};
	
	Type::Type (TypeID typeID) : Type (SDE::get(typeID)) {}

	Type::Type(const MetaInfo& metaInfo): metaInfo_(metaInfo) {
		for (const auto& i: metaInfo.attributes) {
			attributes_.emplace(i.first.attributeID, new Attribute(i.first, i.second, *this));
		}
		
		effects_.reserve(metaInfo.effects.size());
		
		for (const auto& i: metaInfo.effects) {
			effects_.push_back(std::unique_ptr<Effect>(new Effect(i, *this)));
		}
	}
	
	bool Type::hasAttribute(AttributeID attributeID) {
		return attributes_.find(attributeID) != attributes_.end();
	}
	
	Attribute::Proxy Type::operator[](AttributeID attributeID) {
		return {*this, attributes_.emplace(attributeID, nullptr).first};
	}

	void Type::add(std::unique_ptr<Type> child) {
		if (auto oldParent = child->parent()) {
			oldParent->remove(child.get());
		}
		child->parent(this);
		auto i = std::upper_bound(children_.begin(), children_.end(), child);
		assert(i == children_.end() || *i != child);
		children_.insert(i, std::move(child));
	}
	
	void Type::remove(Type* child) {
		assert(child->parent() == this);
		child->parent(nullptr);
		auto i = std::lower_bound(children_.begin(), children_.end(), child, [=](const auto& a, const auto& b) -> bool {
			return a.get() < b;
		});
		
		assert(i->get() == child);
		children_.erase(i);
	}
	
	Type* Type::operator[](Modifier::MetaInfo::Domain domain) {
		switch (domain) {
			case Modifier::MetaInfo::Domain::self:
				return this;
			default:
				return nullptr;
		}
		return nullptr;
	}
	
	void Type::addModifier(const Modifier* modifier) {
		switch (modifier->metaInfo().type) {
			case Modifier::MetaInfo::ModifierType::item: {
				auto i = std::upper_bound(itemModifiers_.begin(), itemModifiers_.end(), modifier->metaInfo().modifiedAttributeID, ModifierComparator());
				assert(i == itemModifiers_.end() || *i != modifier);
				itemModifiers_.insert(i, modifier);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::location: {
				auto i = std::upper_bound(locationModifiers_.begin(), locationModifiers_.end(), modifier->metaInfo().modifiedAttributeID, ModifierComparator());
				assert(i == locationModifiers_.end() || *i != modifier);
				locationModifiers_.insert(i, modifier);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::locationGroup: {
				auto what = std::make_pair(modifier->metaInfo().modifiedAttributeID, modifier->metaInfo().require.groupID);
				auto i = std::upper_bound(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), what, ModifierComparator());
				assert(i == locationGroupModifiers_.end() || *i != modifier);
				locationGroupModifiers_.insert(i, modifier);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::locationRequiredSkill:
			case Modifier::MetaInfo::ModifierType::ownerRequiredSkill: {
				auto skillID = modifier->metaInfo().require.typeID;
				auto what = std::make_pair(modifier->metaInfo().modifiedAttributeID, skillID);
				auto i = std::upper_bound(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), what, ModifierComparator());
				assert(i == locationRequiredSkillModifiers_.end() || i->second != modifier);
				locationRequiredSkillModifiers_.insert(i, std::make_pair(skillID, modifier));
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::locationRequiredDomainSkill: {
				auto skillID = modifier->owner()[modifier->metaInfo().require.domain]->metaInfo().typeID;
				auto what = std::make_pair(modifier->metaInfo().modifiedAttributeID, skillID);
				auto i = std::upper_bound(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), what, ModifierComparator());
				assert(i == locationRequiredSkillModifiers_.end() || i->second != modifier);
				locationRequiredSkillModifiers_.insert(i, std::make_pair(skillID, modifier));
				break;
			}
				
			default:
				assert(!"Invalid Modifier::MetaInfo::ModifierType value");
		}
	}
	
	void Type::removeModifier(const Modifier* modifier) {
		switch (modifier->metaInfo().type) {
			case Modifier::MetaInfo::ModifierType::item: {
				auto i = std::upper_bound(itemModifiers_.begin(), itemModifiers_.end(), modifier->metaInfo().modifiedAttributeID, ModifierComparator());
				assert(*i == modifier);
				itemModifiers_.erase(i);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::location: {
				auto i = std::upper_bound(locationModifiers_.begin(), locationModifiers_.end(), modifier->metaInfo().modifiedAttributeID, ModifierComparator());
				assert(*i == modifier);
				locationModifiers_.erase(i);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::locationGroup: {
				auto what = std::make_pair(modifier->metaInfo().modifiedAttributeID, modifier->metaInfo().require.groupID);
				auto i = std::upper_bound(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), what, ModifierComparator());
				assert(*i == modifier);
				locationGroupModifiers_.erase(i);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::locationRequiredSkill:
			case Modifier::MetaInfo::ModifierType::ownerRequiredSkill: {
				auto skillID = modifier->metaInfo().require.typeID;
				auto what = std::make_pair(modifier->metaInfo().modifiedAttributeID, skillID);
				auto i = std::upper_bound(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), what, ModifierComparator());
				assert(i->second == modifier);
				locationRequiredSkillModifiers_.erase(i);
				break;
			}
				
			case Modifier::MetaInfo::ModifierType::locationRequiredDomainSkill: {
				auto skillID = modifier->owner()[modifier->metaInfo().require.domain]->metaInfo().typeID;
				auto what = std::make_pair(modifier->metaInfo().modifiedAttributeID, skillID);
				auto i = std::upper_bound(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), what, ModifierComparator());
				assert(i->second == modifier);
				locationRequiredSkillModifiers_.erase(i);
				break;
			}
				
			default:
				assert(!"Invalid Modifier::MetaInfo::ModifierType value");
		}
	}

	std::list<const Modifier*> Type::itemModifiers(const Attribute& attribute) const {
		auto what = attribute.metaInfo().attributeID;
		auto range = std::equal_range(itemModifiers_.begin(), itemModifiers_.end(), what, ModifierComparator());
		return {range.first, range.second};
	}

	std::list<const Modifier*> Type::locationModifiers(const Attribute& attribute) const {
		auto what = attribute.metaInfo().attributeID;
		auto range = std::equal_range(locationModifiers_.begin(), locationModifiers_.end(), what, ModifierComparator());
		return {range.first, range.second};
	}
	
	std::list<const Modifier*> Type::locationGroupModifiers(const Attribute& attribute, const Type& type) const {
		auto what = std::make_pair(attribute.metaInfo().attributeID, type.metaInfo().groupID);
		auto range = std::equal_range(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), what, ModifierComparator());
		return {range.first, range.second};
	}
	
	std::list<const Modifier*> Type::locationRequiredSkillModifiers(const Attribute& attribute, const Type& type) const {
		auto attributeID = attribute.metaInfo().attributeID;
		auto range = std::equal_range(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), attributeID, ModifierComparator());
		
		if (range.first < range.second) {
			for (auto skillID: type.metaInfo().requiredSkills) {
				auto what = std::make_pair(attributeID, skillID);
				auto result = std::equal_range(range.first, range.second, what, ModifierComparator());
				
				if (result.first < result.second) {
					std::list<const Modifier*> list;
					std::transform(result.first, result.second, std::back_inserter(list), [](const auto& i) {return i.second;});
					return list;
				}
			}
		}
		return {};
	}
	
	std::list<const Modifier*> Type::modifiers(const Attribute& attribute) const {
		std::list<const Modifier*> result;
		result.splice(result.end(), itemModifiers(attribute));
		if (auto parent = this->parent()) {
			result.splice(result.end(), parent->locationModifiers(attribute));
			result.splice(result.end(), parent->modifiersMatchingType(attribute, *this));
		}
		return result;
	}
	
	std::list<const Modifier*> Type::modifiersMatchingType(const Attribute& attribute, const Type& type) const {
		std::list<const Modifier*> result;
		result.splice(result.end(), locationGroupModifiers(attribute, type));
		result.splice(result.end(), locationRequiredSkillModifiers(attribute, type));
		if (auto parent = this->parent()) {
			result.splice(result.end(), parent->modifiersMatchingType(attribute, *this));
		}
		return result;
	}
	
	void Type::addEffects(Effect::MetaInfo::Category category) {
		auto range = std::equal_range(effects_.begin(), effects_.end(), category, EffectComparator());
		std::for_each(range.first, range.second, [&](const auto& i) {
			for (const auto& modifier: i->modifiers()) {
				if (auto type = modifier.owner()[modifier.metaInfo().domain]) {
					type->addModifier(&modifier);
				}
			}
		});
	}
	
	void Type::removeEffects(Effect::MetaInfo::Category category) {
		asdfsf
	}

}
