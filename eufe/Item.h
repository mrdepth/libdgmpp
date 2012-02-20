#pragma once
#include "types.h"
#include <boost/exception/all.hpp>
#include "ThirdParty/sqlite3.h"
#include <iostream>
#include "Effect.h"

namespace eufe {
	
	extern const TypeID ANY_GROUP_ID;
	extern const TypeID CHARACTER_GROUP_ID;
	extern const TypeID WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID;
	extern const TypeID CAPACITOR_BOOSTER_GROUP_ID;

	extern const TypeID MODULE_CATEGORY_ID;
	extern const TypeID CHARGE_CATEGORY_ID;
	extern const TypeID DRONE_CATEGORY_ID;
	extern const TypeID SUBSYSTEM_CATEGORY_ID;

	class Item
	{
	public:
		
		class Context
		{
		public:
			virtual ~Context() {};
		};
		
		typedef boost::error_info<struct TypeIDExceptionInfoTag, TypeID> TypeIDExceptionInfo;
		struct AttributeDidNotFoundException : virtual boost::exception {};
		struct UnknownTypeIDException : virtual boost::exception {};
		struct EffectDidNotFoundException : virtual boost::exception {};

		struct NoOwnerException : virtual boost::exception {};

		Item();
		Item(Engine* engine, TypeID typeID, Item* owner = NULL);
		Item(Item* owner);
		Item(const Item& from);
		virtual ~Item(void);
		void setContext(const boost::shared_ptr<Context>& context);
		boost::shared_ptr<Context> getContext();
		Engine* getEngine();

		Item* getOwner() const;
		void setOwner(Item *owner);

		virtual TypeID getTypeID() const;
		virtual TypeID getGroupID() const;
		virtual TypeID getCategoryID() const;
		virtual boost::shared_ptr<Attribute> getAttribute(TypeID attributeID);
		bool hasAttribute(TypeID attributeID);
		boost::shared_ptr<Effect> getEffect(TypeID effectID);
		
		
		virtual bool requireSkill(TypeID skillID);

		bool hasEffect(TypeID effectID);
		
		virtual void addEffects(Effect::Category category);
		virtual void removeEffects(Effect::Category category);

		virtual boost::shared_ptr<Environment> getEnvironment() = 0;
		
		virtual void reset();
		
		virtual std::insert_iterator<ModifiersList> getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		
		virtual void addItemModifier(boost::shared_ptr<Modifier> modifier);
		virtual void addLocationModifier(boost::shared_ptr<Modifier> modifier);
		virtual void addLocationGroupModifier(boost::shared_ptr<Modifier> modifier);
		virtual void addLocationRequiredSkillModifier(boost::shared_ptr<Modifier> modifier);

		virtual void removeItemModifier(boost::shared_ptr<Modifier> modifier);
		virtual void removeLocationModifier(boost::shared_ptr<Modifier> modifier);
		virtual void removeLocationGroupModifier(boost::shared_ptr<Modifier> modifier);
		virtual void removeLocationRequiredSkillModifier(boost::shared_ptr<Modifier> modifier);
		
#if _DEBUG
		virtual const char* getTypeName() const;
		friend std::ostream& operator<<(std::ostream& os, Item& item);
#endif
		virtual std::insert_iterator<ModifiersList> getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);
		virtual std::insert_iterator<ModifiersList> getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator);

	protected:
		Engine* engine_;
		AttributesMap attributes_;
		TypeID typeID_;
		TypeID groupID_;
		TypeID categoryID_;
		EffectsList effects_;
		Item* owner_;

		ModifiersList itemModifiers_;
		ModifiersList locationModifiers_;
		ModifiersList locationGroupModifiers_;
		ModifiersList locationRequiredSkillModifiers_;
		

		
	private:
		boost::shared_ptr<Context> context_;
		
#if _DEBUG
		std::string typeName_;
#endif
	};
}