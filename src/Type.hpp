//
//  Type.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 30.10.2017.
//

#pragma once
#include "MetaInfo.hpp"
#include "Attribute.hpp"
#include "Effect.hpp"
#include <unordered_set>

namespace dgmpp {
	class Effect;
	class Modifier;
	
	class Type {
	public:
		virtual ~Type();

		Type (Type&& other) = delete;
		Type& operator= (const Type& other) = delete;
		Type& operator= (Type&& other) = delete;

		const MetaInfo::Type& metaInfo() const { return metaInfo_; }
		Type* parent() const noexcept { return parent_(); }
		
		Attribute* operator[] (AttributeID attributeID) {
			auto i = attributes_.find(attributeID);
			return i != attributes_.end() ? i->second.get() : nullptr;
		}
		
		Effect* operator[] (EffectID effectID) const { return effect(effectID); }
		
		std::unordered_set<Type*> affectors() const;
		std::list<Attribute*> attributes() const;
		
		std::size_t identifier() const noexcept { return identifier_; }
		void identifier (std::size_t identifier) noexcept { identifier_ = identifier; }
		
	protected:
		
		Type (TypeID typeID);
		Type (const MetaInfo::Type& metaInfo);
		Type (const Type& other);

		virtual Type* domain (MetaInfo::Modifier::Domain domain) noexcept;
		
		std::list<const Modifier*> itemModifiers					(const MetaInfo::Attribute& attribute) const;
		std::list<const Modifier*> locationModifiers				(const MetaInfo::Attribute& attribute) const;
		std::list<const Modifier*> locationGroupModifiers			(const MetaInfo::Attribute& attribute, const Type& type) const;
		std::list<const Modifier*> locationRequiredSkillModifiers	(const MetaInfo::Attribute& attribute, const Type& type) const;
		
		virtual std::list<const Modifier*> modifiers (const MetaInfo::Attribute& attribute) const;
		virtual std::list<const Modifier*> modifiersMatchingType (const MetaInfo::Attribute& attribute, const Type& type) const;
		
		void activateEffects (MetaInfo::Effect::Category category);
		void deactivateEffects (MetaInfo::Effect::Category category);
		const std::vector<std::unique_ptr<Effect>>& effects() const noexcept { return effects_; }
		
		virtual void reset();
		Type* parent_() const noexcept { return parentType_; }
		void parent_ (Type* parent);
		void batchUpdates(std::function<void()> updates);
		void resetCache ();
		
		Attribute::Proxy attribute (AttributeID attributeID);
		Effect* effect (EffectID effectID) const;

		virtual bool isDisallowedAssistance() {
			if (auto parent = parent_())
				return parent->isDisallowedAssistance();
			else
				return false;
		}
		
		virtual bool isDisallowedOffense() {
			if (auto parent = parent_())
				return parent->isDisallowedOffense();
			else
				return false;
		}
		
		bool isDescendant (Type& parent) const noexcept {
			if (this == &parent)
				return true;
			else if (auto myParent = parent_())
				return myParent->isDescendant(parent);
				return false;
		}

		virtual bool isEnabled() const noexcept { return enabled_; }
		virtual void setEnabled (bool enabled);


	private:
		class AttributesCache;
		
		friend class AttributeProxy;
		friend class Attribute;
		friend class Effect;
		friend class Modifier;
		friend class WarfareBuff;
		friend class WarfareBuffEffect;
		friend class Drone;
		friend class HeatSimulator;
		friend class Capacitor;
		friend class Ship;
		friend class Module;
		friend class Structure;
		
		const MetaInfo::Type&					metaInfo_;
		Type*									parentType_ = nullptr;
		AttributesMap							attributes_;
		std::vector<std::unique_ptr<Effect>>	effects_;
//		TypesContainer							children_;
		bool									enabled_ = false;
		bool									resetFlag_ = false;


		TuplesSet<AttributeID, const Modifier*> itemModifiers_;
		TuplesSet<AttributeID, const Modifier*> locationModifiers_;
		TuplesSet<AttributeID, GroupID, const Modifier*> locationGroupModifiers_;
		TuplesSet<AttributeID, TypeID, const Modifier*> locationRequiredSkillModifiers_;
		
		std::unique_ptr<AttributesCache> cache_;
		std::size_t identifier_ = std::hash<Type*>()(this);

		void addModifier	(const Modifier* modifier);
		void removeModifier (const Modifier* modifier);
		std::vector<Effect*> activeEffects() const;
		
		void activate	(Effect* effect);
		void deactivate	(Effect* effect);
		
		AttributesCache& cache();

		TuplesSet<WarfareBuffID, const WarfareBuff*> buffs_;
		
		void addBuff	(const WarfareBuff* buff);
		void removeBuff	(const WarfareBuff* buff);

	};
	
	class Type::AttributesCache {
	public:
		void add(Attribute* attribute) {
			attributes_.push_back(attribute);
		}
		std::unique_ptr<AttributesCache> extract(Type* type) {
			auto i = std::partition(attributes_.begin(), attributes_.end(), [=](auto i) {
				return !i->owner().isDescendant(*type);
			});
			auto result = std::unique_ptr<AttributesCache>(new AttributesCache);
			
			result->attributes_.splice(result->attributes_.begin(), attributes_, i, attributes_.end());
			return result;
		}
		void splice(AttributesCache&& other) {
			attributes_.splice(attributes_.end(), other.attributes_);
		}
		
		void reset() {
			if (batchCounter_ > 0)
				return;
			
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
				if (type->isEnabled())
					type->reset();
				type->resetFlag_ = false;
			}
		}
		
		void batchUpdates(std::function<void()> updates) {
			batchCounter_++;
			updates();
			batchCounter_--;
			if (batchCounter_ == 0)
				reset();
		}
		
	private:
		std::list<Attribute*> attributes_;
		std::size_t batchCounter_ = 0;
	};
	
}
