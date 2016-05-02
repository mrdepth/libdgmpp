#pragma once
#include "types.h"
#include <stdexcept>
#include <iostream>
#include "Effect.h"
#include "Environment.h"
#include "Engine.h"

namespace dgmpp {
	
	extern const TypeID ANY_GROUP_ID;
	extern const TypeID CHARACTER_GROUP_ID;
	extern const TypeID WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID;
	extern const TypeID CAPACITOR_BOOSTER_GROUP_ID;
	extern const TypeID CONTROL_TOWER_GROUP_ID;
	extern const TypeID CAPACITOR_BOOSTER_CHARGE_GROUP_ID;
	extern const TypeID NANITE_REPAIR_PASTE_GROUP_ID;

	extern const TypeID MODULE_CATEGORY_ID;
	extern const TypeID CHARGE_CATEGORY_ID;
	extern const TypeID DRONE_CATEGORY_ID;
	extern const TypeID SUBSYSTEM_CATEGORY_ID;
	extern const TypeID STARBASE_CATEGORY_ID;
	extern const TypeID STRUCTURE_MODULE_CATEGORY_ID;
	extern const TypeID FIGHTER_CATEGORY_ID;

	extern const TypeID MISSILE_LAUNCHER_OPERATION_TYPE_ID;
	
	extern const TypeID CALDARI_RACE_ID;
	extern const TypeID MINMATAR_RACE_ID;
	extern const TypeID AMARR_RACE_ID;
	extern const TypeID GALLENTE_RACE_ID;

	extern const TypeID NITROGEN_FUEL_BLOCK_TYPE_ID;
	extern const TypeID HYDROGEN_FUEL_BLOCK_TYPE_ID;
	extern const TypeID HELIUM_FUEL_BLOCK_TYPE_ID;
	extern const TypeID OXYGEN_FUEL_BLOCK_TYPE_ID;


	
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
		virtual TypeID getGroupID();
		virtual TypeID getCategoryID();
		virtual const std::shared_ptr<Attribute>& getAttribute(TypeID attributeID);
		const AttributesMap &getAttributes();
		bool hasAttribute(TypeID attributeID);
		std::shared_ptr<Effect> getEffect(TypeID effectID);
		
		
		virtual bool requireSkill(TypeID skillID);
		const std::vector<TypeID>& requiredSkills();

		bool hasEffect(TypeID effectID);
		
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
		TypeID groupID_;
		TypeID categoryID_;
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
		std::shared_ptr<Attribute> addExtraAttribute(TypeID attributeID, float value);

		
	private:
		bool loaded_;
		std::vector<TypeID> requiredSkills_;
		
		std::string typeName_;
		std::string groupName_;
	};
}