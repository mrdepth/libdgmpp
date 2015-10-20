#include "Item.h"

#include "Attribute.h"
#include "Effect.h"
#include "Engine.h"
#include <sstream>
#include <functional>
#include <algorithm>
#include <limits>
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "Ship.h"
#include "Character.h"
#include "Gang.h"
#include "Area.h"
#include <cassert>

using namespace eufe;

const TypeID eufe::ANY_GROUP_ID = std::numeric_limits<TypeID>::max();
const TypeID eufe::CHARACTER_GROUP_ID = 1;
const TypeID eufe::WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID = 899;
const TypeID eufe::CAPACITOR_BOOSTER_GROUP_ID = 76;
const TypeID eufe::CONTROL_TOWER_GROUP_ID = 365;
const TypeID eufe::CAPACITOR_BOOSTER_CHARGE_GROUP_ID = 87;
const TypeID eufe::NANITE_REPAIR_PASTE_GROUP_ID = 916;

const TypeID eufe::MODULE_CATEGORY_ID = 7;
const TypeID eufe::CHARGE_CATEGORY_ID = 8;
const TypeID eufe::DRONE_CATEGORY_ID = 18;
const TypeID eufe::SUBSYSTEM_CATEGORY_ID = 32;
const TypeID eufe::STRUCTURE_CATEGORY_ID = 23;

const TypeID eufe::MISSILE_LAUNCHER_OPERATION_TYPE_ID = 3319;

class ModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	ModifierMatchFunction(TypeID attributeID) : attributeID_(attributeID) {}
	bool operator() (std::shared_ptr<Modifier> modifier)
	{
		return !(modifier->getAttributeID() == attributeID_);
	}
private:
	TypeID attributeID_;
};

class LocationGroupModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	LocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID) : attributeID_(attributeID), groupID_(groupID) {}
	bool operator() (std::shared_ptr<Modifier> modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && std::dynamic_pointer_cast<LocationGroupModifier>(modifier)->getGroupID() == groupID_);
	}
private:
	TypeID attributeID_;
	TypeID groupID_;
};

class LocationRequiredSkillModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	LocationRequiredSkillModifierMatchFunction(TypeID attributeID, Item* item) : attributeID_(attributeID), item_(item) {}
	bool operator() (std::shared_ptr<Modifier> modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && item_->requireSkill(std::dynamic_pointer_cast<LocationRequiredSkillModifier>(modifier)->getSkillID()));
	}
private:
	TypeID attributeID_;
	Item* item_;
};

class ModifiersFindFunction : public std::unary_function<std::shared_ptr<Modifier>, bool>
{
public:
	ModifiersFindFunction(std::shared_ptr<Modifier> modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (std::shared_ptr<Modifier> modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	std::shared_ptr<Attribute> modifier_;
	Modifier::Association association_;
};


Item::Item(void) : owner_(), typeID_(0), context_(nullptr), engine_(), loaded_(false)
{
}

Item::Item(std::shared_ptr<Engine> engine, TypeID typeID, std::shared_ptr<Item> owner) : engine_(engine), owner_(owner), typeID_(typeID), groupID_(0), context_(nullptr), loaded_(false)
{
}

Item::Item(std::shared_ptr<Item> owner) : owner_(owner), context_(), engine_(), loaded_(false)
{
}

Item::~Item(void)
{
}

std::shared_ptr<Engine> Item::getEngine()
{
	return engine_.lock();
}

std::shared_ptr<Item> Item::getOwner() const
{
	return owner_.lock();
}

std::shared_ptr<Attribute> Item::getAttribute(TypeID attributeID)
{
	loadIfNeeded();
	auto engine = getEngine();
	if (!engine)
		return nullptr;

	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return i->second;
	else
		return attributes_[attributeID] = std::make_shared<Attribute>(engine, attributeID, shared_from_this(), true);
		//throw AttributeDidNotFoundException() << TypeIDExceptionInfo(attributeID);
}

const AttributesMap &Item::getAttributes()
{
	loadIfNeeded();
	return attributes_;
}

bool Item::hasAttribute(TypeID attributeID)
{
	loadIfNeeded();
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return !i->second->isFakeAttribute();
	else
		return false;
}

std::shared_ptr<Effect> Item::getEffect(TypeID effectID)
{
	loadIfNeeded();
	for (auto i: effects_)
		if (i->getEffectID() == effectID)
			return i;
    throw EffectDidNotFoundException(std::to_string(effectID));
}


bool Item::requireSkill(TypeID skillID)
{
	loadIfNeeded();
	try
	{
		if (getAttribute(REQUIRED_SKILL1_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL2_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL3_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL4_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL5_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL6_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
	}
	catch (AttributeDidNotFoundException&)
	{
	}
	return false;
}

bool Item::hasEffect(TypeID effectID)
{
	loadIfNeeded();
	for (auto i: effects_)
		if (i->getEffectID() == effectID)
			return true;
	return false;
}

TypeID Item::getTypeID() const
{
	return typeID_;
}

TypeID Item::getGroupID() const
{
	return groupID_;
}

TypeID Item::getCategoryID() const
{
	return categoryID_;
}

void Item::addEffects(Effect::Category category)
{
	loadIfNeeded();
	Environment environment = getEnvironment();
	for (auto i: effects_)
		if (i->getCategory() == category)
			i->addEffect(environment);
}

void Item::removeEffects(Effect::Category category)
{
	loadIfNeeded();
	Environment environment = getEnvironment();
	for (auto i: effects_)
		if (i->getCategory() == category)
			i->removeEffect(environment);
}

void Item::reset()
{
	loadIfNeeded();
	for (auto i: attributes_)
		i.second->reset();
}

std::insert_iterator<ModifiersList> Item::getModifiers(std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = std::remove_copy_if(itemModifiers_.begin(), itemModifiers_.end(), outIterator, ModifierMatchFunction(attribute->getAttributeID()));
	auto owner = getOwner();
	if (owner)
	{
		outIterator = owner->getLocationModifiers(attribute, outIterator);
		outIterator = owner->getModifiersMatchingItem(this, attribute, outIterator);
	}
	return outIterator;
}

std::insert_iterator<ModifiersList> Item::getLocationModifiers(std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = std::remove_copy_if(locationModifiers_.begin(), locationModifiers_.end(), outIterator, ModifierMatchFunction(attribute->getAttributeID()));
//	if (owner_)
//		outIterator = owner_->getLocationModifiers(attribute, outIterator);
	return outIterator;

}

std::insert_iterator<ModifiersList> Item::getModifiersMatchingItem(Item* item, std::shared_ptr<Attribute> attribute, std::insert_iterator<ModifiersList> outIterator)
{
	outIterator = std::remove_copy_if(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), outIterator, LocationGroupModifierMatchFunction(attribute->getAttributeID(), item->getGroupID()));
	outIterator = std::remove_copy_if(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), outIterator, LocationRequiredSkillModifierMatchFunction(attribute->getAttributeID(), item));
	auto owner = getOwner();
	if (owner)
		outIterator = owner->getModifiersMatchingItem(item, attribute, outIterator);
	return outIterator;
}

void Item::addItemModifier(std::shared_ptr<Modifier> modifier)
{
	itemModifiers_.push_back(modifier);
}

void Item::addLocationModifier(std::shared_ptr<Modifier> modifier)
{
	locationModifiers_.push_back(modifier);
}

void Item::addLocationGroupModifier(std::shared_ptr<Modifier> modifier)
{
	locationGroupModifiers_.push_back(modifier);
}

void Item::addLocationRequiredSkillModifier(std::shared_ptr<Modifier> modifier)
{
	locationRequiredSkillModifiers_.push_back(modifier);
}

void Item::removeItemModifier(std::shared_ptr<Modifier> modifier)
{
	ModifiersList::iterator i = std::find_if(itemModifiers_.begin(), itemModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != itemModifiers_.end())
	{
		itemModifiers_.erase(i);
	}
}

void Item::removeLocationModifier(std::shared_ptr<Modifier> modifier)
{
	ModifiersList::iterator i = std::find_if(locationModifiers_.begin(), locationModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationModifiers_.end())
	{
		locationModifiers_.erase(i);
	}
}

void Item::removeLocationGroupModifier(std::shared_ptr<Modifier> modifier)
{
	ModifiersList::iterator i = std::find_if(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationGroupModifiers_.end())
	{
		locationGroupModifiers_.erase(i);
	}
}

void Item::removeLocationRequiredSkillModifier(std::shared_ptr<Modifier> modifier)
{
	ModifiersList::iterator i = std::find_if(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationRequiredSkillModifiers_.end())
	{
		locationRequiredSkillModifiers_.erase(i);
	}
}

const char* Item::getTypeName()
{
	loadIfNeeded();
	if (typeName_.size() == 0)
	{
		std::stringstream sql;
		sql << "SELECT typeName FROM invTypes WHERE typeID = " << typeID_;

		auto engine = getEngine();
		if (engine) {
			std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(sql.str().c_str());
			if (result->next()) {
				typeName_ = result->getText(0);
			}
		}
	}
	return typeName_.c_str();
}

const char* Item::getGroupName()
{
	loadIfNeeded();
	if (groupName_.size() == 0)
	{
		std::stringstream sql;
		sql << "SELECT groupName FROM invTypes AS A, invGroups AS B WHERE A.groupID=B.groupID AND typeID = " << typeID_;
		auto engine = getEngine();
		if (engine) {
			std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(sql.str().c_str());
			if (result->next()) {
				groupName_ = result->getText(0);
			}
		}
	}
	return groupName_.c_str();
}

std::shared_ptr<Attribute> Item::addExtraAttribute(TypeID attributeID, TypeID maxAttributeID, float value, bool isStackable, bool highIsGood, const char* attributeName) {
	auto engine = getEngine();
	if (!engine)
		return nullptr;

	return attributes_[attributeID] = std::make_shared<Attribute>(engine, attributeID, maxAttributeID, value, isStackable, highIsGood, shared_from_this(), attributeName, false);
}

void Item::lazyLoad() {
//	assert(loaded_ == false);
	loaded_ = true;
	if (typeID_ == 0)
		return;
	auto engine = getEngine();
	if (!engine)
		return;
	
	std::stringstream sql;
	sql << "SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID, typeName FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = " << typeID_;
	
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(sql.str().c_str());
	if (result->next())
	{
		groupID_ = result->getInt(0);
		float radius = static_cast<float>(result->getDouble(1));
		float mass = static_cast<float>(result->getDouble(2));
		float volume = static_cast<float>(result->getDouble(3));
		float capacity = static_cast<float>(result->getDouble(4));
		int raceID = result->getInt(5);
		categoryID_ = result->getInt(6);
		
		typeName_ = result->getText(7);
		attributes_[RADIUS_ATTRIBUTE_ID]    = std::make_shared<Attribute>(engine, RADIUS_ATTRIBUTE_ID,    0, radius,   true,  true, shared_from_this(), "radius");
		attributes_[MASS_ATTRIBUTE_ID]      = std::make_shared<Attribute>(engine, MASS_ATTRIBUTE_ID,      0, mass,     false, true, shared_from_this(), "mass");
		attributes_[VOLUME_ATTRIBUTE_ID]    = std::make_shared<Attribute>(engine, VOLUME_ATTRIBUTE_ID,    0, volume,   true,  true, shared_from_this(), "volume");
		attributes_[CAPACITY_ATTRIBUTE_ID]  = std::make_shared<Attribute>(engine, CAPACITY_ATTRIBUTE_ID,  0, capacity, true,  true, shared_from_this(), "capacity");
		attributes_[RACE_ID_ATTRIBUTE_ID]   = std::make_shared<Attribute>(engine, RACE_ID_ATTRIBUTE_ID,   0, static_cast<float>(raceID), true, true, shared_from_this(), "raceID");
		
		sql.str(std::string());
		sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood, attributeName FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
		<< typeID_;
		result = engine->getSqlConnector()->exec(sql.str().c_str());
		while (result->next())
		{
			TypeID attributeID = static_cast<TypeID>(result->getInt(0));
			TypeID maxAttributeID = static_cast<TypeID>(result->getInt(1));
			bool isStackable = result->getInt(2) != 0;
			float value = static_cast<float>(result->getDouble(3));
			bool highIsGood = result->getInt(4) != 0;
			std::string attributeName = result->getText(5);
			attributes_[attributeID] = std::make_shared<Attribute>(engine, attributeID, maxAttributeID, value, isStackable, highIsGood, shared_from_this(), attributeName.c_str());
		}
		
		sql.str(std::string());
		sql << "SELECT effectID FROM dgmTypeEffects WHERE dgmTypeEffects.typeID = " << typeID_;
		result = engine->getSqlConnector()->exec(sql.str().c_str());
		while (result->next())
		{
			TypeID effectID = static_cast<TypeID>(result->getInt(0));
			effects_.push_back(Effect::getEffect(engine, effectID));
		}
	}
	else
	{
		throw UnknownTypeIDException(std::to_string(typeID_));
	}
}


std::set<std::shared_ptr<Item>> Item::getAffectors() {
	ModifiersList modifiers;
	{
		for (auto i: getAttributes())
			getModifiers(i.second, std::inserter(modifiers, modifiers.begin()));
		}
	
	std::set<std::shared_ptr<Item>> items;
	{
		for (auto i: modifiers) {
			std::shared_ptr<Item> item = i->getModifier()->getOwner();
			if (item.get() != this)
				items.insert(i->getModifier()->getOwner());
		}
	}
	
	return items;
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::Item& item)
{
	os << "{\"typeName\":\"" << item.getTypeName() << "\", \"typeID\":\"" << item.typeID_ << "\", \"groupID\":\"" << item.groupID_ << "\", \"attributes\":[";
	
	if (item.attributes_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: item.attributes_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i.second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (item.effects_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: item.effects_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}
	
	os << "], \"itemModifiers\":[";
	
	if (item.itemModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: item.itemModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	os << "], \"locationModifiers\":[";
	
	if (item.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: item.locationModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i;
		}
	}

	os << "], \"locationGroupModifiers\":[";
	
	if (item.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: item.locationGroupModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationGroupModifier>(i);
		}
	}

	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (item.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (auto i: item.locationRequiredSkillModifiers_)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *std::dynamic_pointer_cast<LocationRequiredSkillModifier>(i);
		}
	}

	os << "]}";
	return os;
}
