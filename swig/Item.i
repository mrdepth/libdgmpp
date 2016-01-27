%include "types.i"
%include "Attribute.i"

%shared_ptr(dgmpp::Item);

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
		std::shared_ptr<dgmpp::Engine> getEngine();
		
		std::shared_ptr<dgmpp::Item> getOwner() const;
		
		virtual dgmpp::TypeID getTypeID();
		virtual dgmpp::TypeID getGroupID();
		virtual dgmpp::TypeID getCategoryID();
		virtual std::shared_ptr<dgmpp::Attribute> getAttribute(dgmpp::TypeID attributeID);
		const dgmpp::AttributesMap &getAttributes();
		bool hasAttribute(dgmpp::TypeID attributeID);
		std::shared_ptr<dgmpp::Effect> getEffect(dgmpp::TypeID effectID);
		
		virtual bool requireSkill(dgmpp::TypeID skillID);
		
		bool hasEffect(dgmpp::TypeID effectID);
		
		virtual const char* getTypeName();
	};
}