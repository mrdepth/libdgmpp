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
#include "MetaInfo.hpp"
#include "Utility.hpp"

namespace dgmpp2 {
	
	class Type {
	public:
		Type (const Type& other) = delete;
		Type (Type&& other) = delete;
		Type& operator= (const Type& other) = delete;
		Type& operator= (Type&& other) = delete;

		const MetaInfo::Type& metaInfo() const { return metaInfo_; }
		Type* parent() const { return parent_; }
		
		Attribute::Proxy operator[] (AttributeID attributeID);
		Effect* operator[] (EffectID effectID) const;
		
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
		
		bool isDescendant (Type& parent) const {
			if (this == &parent)
				return true;
			else if (auto myParent = this->parent())
				return myParent->isDescendant(parent);
			return false;
		}
		
		virtual bool isEnabled() const { return enabled_; }
		virtual void setEnabled (bool enabled);
		
	protected:
		using TypesContainer = std::list<std::unique_ptr<Type>>;
		
		Type (TypeID typeID);
		Type (const MetaInfo::Type& metaInfo);

		template<typename T>
		T* add (std::unique_ptr<T> child) {
			assert(child != nullptr);
			assert(child->parent() == nullptr);
			
			auto ptr = child.release();
			auto type = std::unique_ptr<Type>(ptr);
			
			if (type->isEnabled())
				type->setEnabled(false);
			
			if (type->cache_ != nullptr) {
				if (cache_ == nullptr)
					cache_ = std::move(type->cache_);
				else
					cache_ = nullptr;
			}
			type->parent(this);
			
			assert(std::find(children_.begin(), children_.end(), type) == children_.end());
			children_.push_back(std::move(type));
			
			if (isEnabled())
				ptr->setEnabled(true);
			
			return ptr;
		}

		void remove (Type* child);
		const TypesContainer& children() const { return children_; }
		
		virtual Type* domain (MetaInfo::Modifier::Domain domain) ;
		
		std::list<const Modifier*> itemModifiers					(const MetaInfo::Attribute& attribute) const;
		std::list<const Modifier*> locationModifiers				(const MetaInfo::Attribute& attribute) const;
		std::list<const Modifier*> locationGroupModifiers			(const MetaInfo::Attribute& attribute, const Type& type) const;
		std::list<const Modifier*> locationRequiredSkillModifiers	(const MetaInfo::Attribute& attribute, const Type& type) const;
		
		virtual std::list<const Modifier*> modifiers (const MetaInfo::Attribute& attribute) const;
		virtual std::list<const Modifier*> modifiersMatchingType (const MetaInfo::Attribute& attribute, const Type& type) const;
		
		void activateEffects (MetaInfo::Effect::Category category);
		void deactivateEffects (MetaInfo::Effect::Category category);
		const std::vector<std::unique_ptr<Effect>>& effects() const { return effects_; }
		
		virtual void reset();
		
	private:
		struct AttributesCache;
		
		friend class AttributeProxy;
		friend class Attribute;
		friend class Modifier;
		
		const MetaInfo::Type&					metaInfo_;
		Type*									parent_ = nullptr;
		AttributesMap							attributes_;
		std::vector<std::unique_ptr<Effect>>	effects_;
		TypesContainer							children_;
		bool									enabled_ = false;
		bool									resetFlag_ = false;


		ModifiersContainer<AttributeID, const Modifier*> itemModifiers_;
		ModifiersContainer<AttributeID, const Modifier*> locationModifiers_;
		ModifiersContainer<AttributeID, GroupID, const Modifier*> locationGroupModifiers_;
		ModifiersContainer<AttributeID, TypeID, const Modifier*> locationRequiredSkillModifiers_;
		
		std::unique_ptr<AttributesCache> cache_;
		
		void parent (Type* parent) { parent_ = parent; }
		
		void addModifier (const Modifier* modifier);
		void removeModifier (const Modifier* modifier);
		std::vector<Effect*> activeEffects() const;
		void resetCache ();
		
		void activate	(Effect* effect);
		void deactivate	(Effect* effect);
		
		AttributesCache& cache();

	};
	
	class Type::AttributesCache {
	public:
		void add(Attribute* attribute) {
			attributes_.push_back(attribute);
		}
		
		void reset() {
			std::list<Type*> types;
			for (auto attribute: attributes_) {
				attribute->reset();
				auto type = &attribute->owner();
				if (!type->resetFlag_) {
					type->resetFlag_ = true;
					types.push_back(type);
				}
			}
			attributes_.clear();
			for (auto type: types) {
				type->reset();
				type->resetFlag_ = false;
			}
		}
		
	private:
		std::list<Attribute*> attributes_;
	};
	
}
