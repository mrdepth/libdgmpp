//
//  Type.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 30.10.2017.
//

#pragma once
#include "types.h"
#include "Effect.h"
#include "Effect.h"
//#include <utility>
#include <mutex>

#include <sqlite3.h>

#include "Attribute.h"
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace dgmpp2 {
	
	class Type {
	public:
		struct MetaInfo;

		Type(const Type& other) = delete;
		Type(Type&& other) = delete;
		Type& operator=(const Type& other) = delete;
		Type& operator=(Type&& other) = delete;

		const MetaInfo& metaInfo() const {return metaInfo_;}
		Type* parent() const {return parent_;}
		
		bool hasAttribute(AttributeID attributeID);
		Attribute::Proxy operator[](AttributeID attributeID);
		Effect* operator[](EffectID effectID);
		
		virtual bool isDisallowedAssistance() const {
			if (auto parent = this->parent())
				return parent->isDisallowedAssistance();
			else
				return false;
		}
		virtual bool isDisallowedOffense() const {
			if (auto parent = this->parent())
				return parent->isDisallowedOffense();
			else
				return false;
		}
		
		bool isDescendant(Type& parent) const {
			if (this == &parent) {
				return true;
			}
			else if (auto myParent = this->parent()) {
				myParent->isDescendant(parent);
			}
			return false;
		}
		
	protected:
		Type(TypeID typeID);
		
		template<typename T>
		T* add(std::unique_ptr<T> child) {
			assert(child != nullptr);
			auto ptr = child.release();
			auto type = std::unique_ptr<Type>(ptr);
			if (auto oldParent = type->parent()) {
				oldParent->remove(type.get());
			}
			type->parent(this);
			auto i = std::upper_bound(children_.begin(), children_.end(), type);
			assert(i == children_.end() || *i != type);
			children_.insert(i, std::move(type));
			
			for (auto i: activeEffectCategories_)
				ptr->activateEffects(i);
			return ptr;
		}

		void remove(Type* child);
		const std::vector<std::unique_ptr<Type>>& children() const {return children_;}
		
		friend class Modifier;
//		virtual Type* operator[](Modifier::MetaInfo::Domain domain) = 0;
		virtual Type* domain(Modifier::MetaInfo::Domain domain) = 0;
		
		std::list<const Modifier*> itemModifiers(const Attribute::MetaInfo& attribute) const;
		std::list<const Modifier*> locationModifiers(const Attribute::MetaInfo& attribute) const;
		std::list<const Modifier*> locationGroupModifiers(const Attribute::MetaInfo& attribute, const Type& type) const;
		std::list<const Modifier*> locationRequiredSkillModifiers(const Attribute::MetaInfo& attribute, const Type& type) const;
		
		virtual std::list<const Modifier*> modifiers(const Attribute::MetaInfo& attribute) const;
		virtual std::list<const Modifier*> modifiersMatchingType(const Attribute::MetaInfo& attribute, const Type& type) const;
		
		void activateEffects(Effect::MetaInfo::Category category);
		void deactivateEffects(Effect::MetaInfo::Category category);
		
	private:
		friend class AttributeProxy;
		friend class Attribute;
		friend class Effect;
		
		const MetaInfo& metaInfo_;
		Type* parent_ = nullptr;
		AttributesMap attributes_;
		std::vector<std::unique_ptr<Effect>> effects_;
		std::vector<std::unique_ptr<Type>> children_;
		mutable bool isReset_ = true;
		std::unordered_set<Effect::MetaInfo::Category> activeEffectCategories_;

		std::vector<const Modifier*> itemModifiers_;
		std::vector<const Modifier*> locationModifiers_;
		std::vector<const Modifier*> locationGroupModifiers_;
		std::vector<std::pair<TypeID, const Modifier*>> locationRequiredSkillModifiers_;

		Type(const MetaInfo& metaInfo);
		void parent(Type* parent);
		
		void addModifier(const Modifier* modifier);
		void removeModifier(const Modifier* modifier);
		std::vector<Effect*> activeEffects() const;
		void reset();
		void reset(AttributeID modifyingAttribute);
	};
	
	struct Type::MetaInfo {
		TypeID typeID;
		GroupID groupID;
		CategoryID categoryID;
		std::initializer_list<std::pair<const Attribute::MetaInfo&, Float>> attributes;
		std::initializer_list<ref<const Effect::MetaInfo>> effects;
		std::initializer_list<const TypeID> requiredSkills;

		MetaInfo(const MetaInfo& other) = delete;
		MetaInfo(MetaInfo&& other) = delete;
		MetaInfo& operator=(const MetaInfo& other) = delete;
		MetaInfo& operator=(MetaInfo&& other) = delete;
		~MetaInfo() = default;
		
		bool requireSkill(TypeID skillID) const {
			return std::find(requiredSkills.begin(), requiredSkills.end(), skillID) != requiredSkills.end();
		}
	};
	
}
