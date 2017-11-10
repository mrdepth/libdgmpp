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
		Effect* operator[] (EffectID effectID);
		
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
		
		Type(TypeID typeID);
		
		template<typename T>
		T* add (std::unique_ptr<T> child) {
			assert(child != nullptr);
			assert(child->parent() == nullptr);
			
			auto ptr = child.release();
			auto type = std::unique_ptr<Type>(ptr);
			
			if (type->isEnabled())
				type->setEnabled(false);
			
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
		
	private:
		friend class AttributeProxy;
		friend class Attribute;
		friend class Modifier;
		
		
		const MetaInfo::Type&					metaInfo_;
		Type*									parent_ = nullptr;
		AttributesMap							attributes_;
		std::vector<std::unique_ptr<Effect>>	effects_;
		TypesContainer							children_;
		mutable bool							isReset_ = true;
		bool									enabled_ = false;

		std::vector<const Modifier*> itemModifiers_;
		std::vector<const Modifier*> locationModifiers_;
		std::vector<const Modifier*> locationGroupModifiers_;
		std::vector<std::pair<TypeID, const Modifier*>> locationRequiredSkillModifiers_;

		
		Type (const MetaInfo::Type& metaInfo);
		void parent (Type* parent) { parent_ = parent; }
		
		void addModifier (const Modifier* modifier);
		void removeModifier (const Modifier* modifier);
		std::vector<Effect*> activeEffects() const;
		void reset();
		void reset (AttributeID modifyingAttribute);
		
		void activate	(Effect* effect);
		void deactivate	(Effect* effect);

	};
	
}
