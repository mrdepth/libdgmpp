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

#if DGMPP_THREADSAFE
#define LOCK(what) std::lock_guard<std::mutex> lock((what)->mutex_());
#else
#define LOCK(what)
#endif

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
		Type* parent() const noexcept { LOCK(this); return parent_(); }
		
		Attribute* operator[] (AttributeID attributeID) {
			LOCK(this);
			auto i = attributesMap_.find(attributeID);
			return i != attributesMap_.end() ? i->second.get() : nullptr;
		}
		
		std::unordered_set<Type*> affectors() { LOCK(this); return affectors_(); }
		std::list<Attribute*> attributes() const { LOCK(this); return attributes_(); }
		
		std::size_t identifier() const noexcept { LOCK(this); return identifier_(); }
		void identifier (std::size_t identifier) noexcept { LOCK(this); identifier_(identifier); }
		
	protected:
		
		Type (TypeID typeID);
		Type (const MetaInfo::Type& metaInfo);
		Type (const Type& other);

		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept;
		
		std::list<const Modifier*> itemModifiers_					(const MetaInfo::Attribute& attribute);
		std::list<const Modifier*> locationModifiers_				(const MetaInfo::Attribute& attribute);
		std::list<const Modifier*> locationGroupModifiers_			(const MetaInfo::Attribute& attribute, Type& type);
		std::list<const Modifier*> locationRequiredSkillModifiers_	(const MetaInfo::Attribute& attribute, Type& type);
		std::vector<std::unique_ptr<Effect>> effects_;

		std::list<const Modifier*> modifiers_ (const MetaInfo::Attribute& attribute);
		std::list<const Modifier*> modifiersMatchingType_ (const MetaInfo::Attribute& attribute, Type& type);
		
		void activateEffects_ (MetaInfo::Effect::Category category);
		void deactivateEffects_ (MetaInfo::Effect::Category category);
		
		virtual void reset_() {}
		Type* parent_() const noexcept { return parentType_; }
		void parent_ (Type* parent);
		void batchUpdates_ (std::function<void()> updates);
		void resetCache_ ();
		virtual Type* owner_() const noexcept { return parent_(); }
		
		Attribute::Proxy attribute_ (AttributeID attributeID);
		Effect* effect_ (EffectID effectID) const;

		virtual bool isDisallowedAssistance_() {
			if (auto parent = parent_())
				return parent->isDisallowedAssistance_();
			else
				return false;
		}
		
		virtual bool isDisallowedOffense_() {
			if (auto parent = parent_())
				return parent->isDisallowedOffense_();
			else
				return false;
		}
		
		bool isDescendant_ (const Type& parent) const noexcept {
			if (this == &parent)
				return true;
			else if (auto myParent = parent_())
				return myParent->isDescendant_(parent);
			else
				return false;
		}

		virtual bool isEnabled_() const noexcept { return enabled_; }
		virtual void setEnabled_ (bool enabled);

#if DGMPP_THREADSAFE
		mutable std::unique_ptr<std::mutex> mutexValue_;
		std::mutex& mutex_() const noexcept;
#endif

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
		AttributesMap							attributesMap_;
		bool									enabled_ = false;
		bool									resetFlag_ = false;


		TuplesSet<AttributeID, const Modifier*> itemModifiersSet_;
		TuplesSet<AttributeID, const Modifier*> locationModifiersSet_;
		TuplesSet<AttributeID, GroupID, const Modifier*> locationGroupModifiersSet_;
		TuplesSet<AttributeID, TypeID, const Modifier*> locationRequiredSkillModifiersSet_;
		
		std::unique_ptr<AttributesCache> cacheValue_;
		std::size_t identifierValue_ = std::hash<Type*>()(this);

		void addModifier_	(const Modifier* modifier);
		void removeModifier_ (const Modifier* modifier);
		std::vector<Effect*> activeEffects_() const;
		
		void activate_		(Effect* effect);
		void deactivate_	(Effect* effect);
		
		AttributesCache& cache_();
		

		TuplesSet<WarfareBuffID, const WarfareBuff*> buffs_;
		
		void addBuff_		(const WarfareBuff* buff);
		void removeBuff_	(const WarfareBuff* buff);

		std::unordered_set<Type*> affectors_();
		std::list<Attribute*> attributes_() const;
		
		std::size_t identifier_() const noexcept { return identifierValue_; }
		void identifier_ (std::size_t identifier) noexcept { identifierValue_ = identifier; }

	};
	
	class Type::AttributesCache {
	public:
		
		void add(Attribute* attribute) {
			attributes_.push_back(attribute);
		}
		
		std::unique_ptr<AttributesCache> extract(Type* type) {
			auto i = std::partition(attributes_.begin(), attributes_.end(), [=](auto i) {
				return !i->owner().isDescendant_(*type);
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
				attribute->reset_();
				auto type = &attribute->owner();
				if (!type->resetFlag_) {
					type->resetFlag_ = true;
					types.push_back(type);
				}
			}
			attributes_.clear();
			for (auto type: types) {
				if (type->isEnabled_())
					type->reset_();
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
