%include "types.i"
%include "Attribute.i"

namespace eufe {
	
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
		Engine* getEngine();
		
		Item* getOwner() const;
		void setOwner(Item *owner);
		
		virtual TypeID getTypeID() const;
		virtual TypeID getGroupID() const;
		virtual TypeID getCategoryID() const;
		virtual Attribute* getAttribute(TypeID attributeID);
		const AttributesMap &getAttributes();
		bool hasAttribute(TypeID attributeID);
		Effect* getEffect(TypeID effectID);
		
		virtual bool requireSkill(TypeID skillID);
		
		bool hasEffect(TypeID effectID);
		
		virtual const char* getTypeName() const;
	};
}