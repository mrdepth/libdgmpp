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
		eufe::Engine* getEngine();
		
		eufe::Item* getOwner() const;
		void setOwner(eufe::Item *owner);
		
		virtual eufe::TypeID getTypeID() const;
		virtual eufe::TypeID getGroupID() const;
		virtual eufe::TypeID getCategoryID() const;
		virtual eufe::Attribute* getAttribute(eufe::TypeID attributeID);
		const eufe::AttributesMap &getAttributes();
		bool hasAttribute(eufe::TypeID attributeID);
		eufe::Effect* getEffect(eufe::TypeID effectID);
		
		virtual bool requireSkill(eufe::TypeID skillID);
		
		bool hasEffect(eufe::TypeID effectID);
		
		virtual const char* getTypeName() const;
	};
}