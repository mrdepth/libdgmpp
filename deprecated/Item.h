#pragma once
#include "types.h"
#include <stdexcept>
#include <iostream>
#include "Effect.h"
#include "Environment.h"
#include "Engine.h"

namespace dgmpp {

	class Item: public Environment, public std::enable_shared_from_this<Item>
	{
	public:
		
        typedef std::invalid_argument AttributeDidNotFoundException;
        typedef std::invalid_argument UnknownTypeIDException;
        typedef std::invalid_argument EffectDidNotFoundException;
        typedef std::runtime_error NoOwnerException;


		Item(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner = std::shared_ptr<Item>(nullptr));
		virtual ~Item(void);
		std::shared_ptr<Engine> getEngine();
		std::shared_ptr<Item> getOwner() const;

		virtual TypeID getTypeID();
		virtual GroupID getGroupID();
		virtual CategoryID getCategoryID();
		virtual std::shared_ptr<Attribute> getAttribute(AttributeID attributeID);
		const AttributesMap &getAttributes();
		bool hasAttribute(AttributeID attributeID);
		std::shared_ptr<Effect> getEffect(EffectID effectID);
		
		
		virtual bool requireSkill(TypeID skillID);
		const std::vector<TypeID>& requiredSkills();

		bool hasEffect(EffectID effectID);
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);
		const EffectsList& getEffects();

		virtual void reset();
		
		virtual void addItemModifier(std::shared_ptr<Modifier> const& modifier);
		virtual void addLocationModifier(std::shared_ptr<Modifier> const& modifier);
		virtual void addLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier);
		virtual void addLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier);

		virtual void removeItemModifier(std::shared_ptr<Modifier> const& modifier);
		virtual void removeLocationModifier(std::shared_ptr<Modifier> const& modifier);
		virtual void removeLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier);
		virtual void removeLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier);
		
		virtual const char* getTypeName();
		virtual const char* getGroupName();
		
		std::set<std::shared_ptr<Item>> getAffectors();
		friend std::ostream& operator<<(std::ostream& os, Item& item);

		virtual std::insert_iterator<ModifiersList> getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		
		virtual Item* self();
		virtual Item* gang();
		virtual Item* area();
		
	protected:
		std::weak_ptr<Engine> engine_;
		AttributesMap attributes_;
		TypeID typeID_;
		GroupID groupID_;
		CategoryID categoryID_;
		EffectsList effects_;
		std::weak_ptr<Item> owner_;
		
		ItemModifiers itemModifiers_;
		LocationModifiers locationModifiers_;
		
		LocationGroupModifiers locationGroupModifiers_;
		LocationRequiredSkillModifiers locationRequiredSkillModifiers_;
		
		virtual void lazyLoad();
		void loadIfNeeded() {
			if (!loaded_)
				lazyLoad();
		}
		std::shared_ptr<Attribute> addExtraAttribute(AttributeID attributeID, Float value);

		
	private:
		bool loaded_;
		std::vector<TypeID> requiredSkills_;
		
		std::string typeName_;
		std::string groupName_;
	};
}
