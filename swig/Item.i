%include "types.i"
%include "Attribute.i"

namespace dgmpp {
	
	extern const TypeID ANY_GROUP_ID;
	extern const TypeID CHARACTER_GROUP_ID;
	extern const TypeID WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID;
	extern const TypeID CAPACITOR_BOOSTER_GROUP_ID;
	extern const TypeID CONTROL_TOWER_GROUP_ID;
	
	extern const TypeID MODULE_CATEGORY_ID;
	extern const TypeID CHARGE_CATEGORY_ID;
	extern const TypeID DRONE_CATEGORY_ID;
	extern const TypeID SUBSYSTEM_CATEGORY_ID;
	extern const TypeID STRUCTURE_CATEGORY_ID;
	
	%nodefaultctor Item;

	class Item
	{
		public:
		dgmpp::Engine* getEngine();
		
		dgmpp::Item* getOwner() const;
		void setOwner(dgmpp::Item *owner);
		
		virtual dgmpp::TypeID getTypeID() const;
		virtual dgmpp::TypeID getGroupID() const;
		virtual dgmpp::TypeID getCategoryID() const;
		virtual dgmpp::Attribute* getAttribute(dgmpp::TypeID attributeID);
		const dgmpp::AttributesMap &getAttributes();
		bool hasAttribute(dgmpp::TypeID attributeID);
		dgmpp::Effect* getEffect(dgmpp::TypeID effectID);
		
		virtual bool requireSkill(dgmpp::TypeID skillID);
		
		bool hasEffect(dgmpp::TypeID effectID);
		
		virtual const char* getTypeName() const;
	};
}