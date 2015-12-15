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

class ModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	ModifierMatchFunction(TypeID attributeID) : attributeID_(attributeID) {}
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		return !(modifier->getAttributeID() == attributeID_);
	}
private:
	TypeID attributeID_;
};

class LocationGroupModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	LocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID) : attributeID_(attributeID), groupID_(groupID) {}
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && std::dynamic_pointer_cast<LocationGroupModifier>(modifier)->getGroupID() == groupID_);
	}
private:
	TypeID attributeID_;
	TypeID groupID_;
};

class LocationRequiredSkillModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	LocationRequiredSkillModifierMatchFunction(TypeID attributeID, Item* item) : attributeID_(attributeID), item_(item) {}
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && item_->requireSkill(std::dynamic_pointer_cast<LocationRequiredSkillModifier>(modifier)->getSkillID()));
	}
private:
	TypeID attributeID_;
	Item* item_;
};

class ModifiersFindFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
{
public:
	ModifiersFindFunction(std::shared_ptr<Modifier> const& modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (std::shared_ptr<Modifier> const& modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	std::shared_ptr<Attribute> modifier_;
	Modifier::Association association_;
};


Item::Item(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner) : engine_(engine), owner_(owner), typeID_(typeID), groupID_(0), context_(nullptr), loaded_(false)
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

const std::shared_ptr<Attribute>& Item::getAttribute(TypeID attributeID)
{
	loadIfNeeded();
	auto engine = getEngine();
//	if (!engine)
//		return nullptr;

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
	for (const auto& i: effects_)
		if (i->getEffectID() == effectID)
			return i;
    throw EffectDidNotFoundException(std::to_string(effectID));
}


bool Item::requireSkill(TypeID skillID)
{
	loadIfNeeded();
	try
	{
		/*if (getAttribute(REQUIRED_SKILL1_ATTRIBUTE_ID)->getInitialValue() == skillID)
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
			return true;*/
		return std::find(requiredSkills_.begin(), requiredSkills_.end(), skillID) != requiredSkills_.end();
	}
	catch (AttributeDidNotFoundException&)
	{
	}
	return false;
}

const std::vector<TypeID>& Item::requiredSkills() {
	loadIfNeeded();
	return requiredSkills_;
}


bool Item::hasEffect(TypeID effectID)
{
	loadIfNeeded();
	for (const auto& i: effects_)
		if (i->getEffectID() == effectID)
			return true;
	return false;
}

TypeID Item::getTypeID()
{
	loadIfNeeded();
	return typeID_;
}

TypeID Item::getGroupID()
{
	loadIfNeeded();
	return groupID_;
}

TypeID Item::getCategoryID()
{
	loadIfNeeded();
	return categoryID_;
}

void Item::addEffects(Effect::Category category)
{
	loadIfNeeded();
	Environment environment = getEnvironment();
	for (const auto& i: effects_)
		if (i->getCategory() == category)
			i->addEffect(environment);
}

void Item::removeEffects(Effect::Category category)
{
	loadIfNeeded();
	Environment environment = getEnvironment();
	for (const auto& i: effects_)
		if (i->getCategory() == category)
			i->removeEffect(environment);
}

const EffectsList& Item::getEffects() {
	return effects_;
}

void Item::reset()
{
	loadIfNeeded();
//	for (const auto& i: attributes_)
//		i.second->reset();
}

std::insert_iterator<ModifiersList> Item::getModifiers(std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator)
{
	auto i = itemModifiers_.find(attribute->getAttributeID());
	if (i != itemModifiers_.end()) {
		outIterator = std::copy(i->second.begin(), i->second.end(), outIterator);
	}
	auto owner = getOwner();
	if (owner)
	{
		outIterator = owner->getLocationModifiers(attribute, outIterator);
		outIterator = owner->getModifiersMatchingItem(this, attribute, outIterator);
	}
	return outIterator;
}

std::insert_iterator<ModifiersList> Item::getLocationModifiers(std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator)
{
	auto i = locationModifiers_.find(attribute->getAttributeID());
	if (i != locationModifiers_.end())
		outIterator = std::copy(i->second.begin(), i->second.end(), outIterator);
	return outIterator;
}

std::insert_iterator<ModifiersList> Item::getModifiersMatchingItem(Item* item, std::shared_ptr<Attribute> const& attribute, std::insert_iterator<ModifiersList> outIterator)
{

	auto i = locationGroupModifiers_.find(item->getGroupID());
	if (i != locationGroupModifiers_.end()) {
		auto j = i->second.find(attribute->getAttributeID());
		if (j != i->second.end())
			outIterator = std::copy(j->second.begin(), j->second.end(), outIterator);
	}
	
	for (auto skillID: item->requiredSkills()) {
		auto i = locationRequiredSkillModifiers_.find(skillID);
		if (i != locationRequiredSkillModifiers_.end()) {
			auto j = i->second.find(attribute->getAttributeID());
			if (j != i->second.end())
				outIterator = std::copy(j->second.begin(), j->second.end(), outIterator);
		}
	}
	
	
	auto owner = getOwner();
	if (owner)
		outIterator = owner->getModifiersMatchingItem(item, attribute, outIterator);
	return outIterator;
}

void Item::addItemModifier(std::shared_ptr<Modifier> const& modifier)
{
	itemModifiers_[modifier->getAttributeID()].push_back(modifier);
}

void Item::addLocationModifier(std::shared_ptr<Modifier> const& modifier)
{
	locationModifiers_[modifier->getAttributeID()].push_back(modifier);
}

void Item::addLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier)
{
	locationGroupModifiers_[modifier->getGroupID()][modifier->getAttributeID()].push_back(modifier);
}

void Item::addLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier)
{
	locationRequiredSkillModifiers_[modifier->getSkillID()][modifier->getAttributeID()].push_back(modifier);
}

void Item::removeItemModifier(std::shared_ptr<Modifier> const& modifier)
{
	auto& list = itemModifiers_[modifier->getAttributeID()];
	auto i = std::find_if(list.begin(), list.end(), ModifiersFindFunction(modifier));
	if (i != list.end())
		list.erase(i);
	if (list.size() == 0)
		itemModifiers_.erase(modifier->getAttributeID());
}

void Item::removeLocationModifier(std::shared_ptr<Modifier> const& modifier)
{
	auto& list = locationModifiers_[modifier->getAttributeID()];
	auto i = std::find_if(list.begin(), list.end(), ModifiersFindFunction(modifier));
	if (i != list.end())
		list.erase(i);
	if (list.size() == 0)
		locationModifiers_.erase(modifier->getAttributeID());
}

void Item::removeLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier)
{
	auto& map = locationGroupModifiers_[modifier->getGroupID()];
	auto& list = map[modifier->getAttributeID()];
	auto i = std::find_if(list.begin(), list.end(), ModifiersFindFunction(modifier));
	if (i != list.end())
		list.erase(i);

	if (list.size() == 0) {
		map.erase(modifier->getAttributeID());
		if (map.size() == 0)
			locationGroupModifiers_.erase(modifier->getGroupID());
	}
}

void Item::removeLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier)
{
	auto& map = locationRequiredSkillModifiers_[modifier->getSkillID()];
	auto& list = map[modifier->getAttributeID()];
	auto i = std::find_if(list.begin(), list.end(), ModifiersFindFunction(modifier));
	if (i != list.end())
		list.erase(i);

	if (list.size() == 0) {
		map.erase(modifier->getAttributeID());
		if (map.size() == 0)
			locationGroupModifiers_.erase(modifier->getSkillID());
	}
}

const char* Item::getTypeName()
{
	loadIfNeeded();
	if (typeName_.size() == 0)
	{
		//std::stringstream sql;
		//sql << "SELECT typeName FROM invTypes WHERE typeID = " << typeID_;
		auto engine = getEngine();
		if (engine) {
			auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT typeName FROM invTypes WHERE typeID = ?");
			stmt->bindInt(1, typeID_);

			std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
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
//		std::stringstream sql;
//		sql << "SELECT groupName FROM invTypes AS A, invGroups AS B WHERE A.groupID=B.groupID AND typeID = " << typeID_;
		auto engine = getEngine();
		if (engine) {
			auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT groupName FROM invTypes AS A, invGroups AS B WHERE A.groupID=B.groupID AND typeID = ?");
			stmt->bindInt(1, typeID_);

			std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
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
	
	//std::stringstream sql;
	//sql << "SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID, typeName FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = " << typeID_;
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID, typeName FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = ?");
	stmt->bindInt(1, typeID_);
	
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
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
		
		//sql.str(std::string());
		//sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood, attributeName FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
		//<< typeID_;
		stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood, attributeName FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = ?");
		stmt->bindInt(1, typeID_);
		result = engine->getSqlConnector()->exec(stmt);
		
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
		
		//sql.str(std::string());
		//sql << "SELECT effectID FROM dgmTypeEffects WHERE dgmTypeEffects.typeID = " << typeID_;
		stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT effectID FROM dgmTypeEffects WHERE dgmTypeEffects.typeID = ?");
		stmt->bindInt(1, typeID_);
		result = engine->getSqlConnector()->exec(stmt);

		while (result->next())
		{
			TypeID effectID = static_cast<TypeID>(result->getInt(0));
			effects_.push_back(Effect::getEffect(engine, effectID));
		}
		result = nullptr;
		
		static const auto requirements = {
			REQUIRED_SKILL1_ATTRIBUTE_ID,
			REQUIRED_SKILL2_ATTRIBUTE_ID,
			REQUIRED_SKILL3_ATTRIBUTE_ID,
			REQUIRED_SKILL4_ATTRIBUTE_ID,
			REQUIRED_SKILL5_ATTRIBUTE_ID,
			REQUIRED_SKILL6_ATTRIBUTE_ID};
		
		for (TypeID attributeID: requirements)
		{
			TypeID skillID = static_cast<TypeID>(getAttribute(attributeID)->getInitialValue());
			if (skillID > 0)
				requiredSkills_.push_back(skillID);
		}
		requiredSkills_.shrink_to_fit();
	}
	else
	{
		throw UnknownTypeIDException(std::to_string(typeID_));
	}
}


std::set<std::shared_ptr<Item>> Item::getAffectors() {
	ModifiersList modifiers;
	auto outIterator = std::inserter(modifiers, modifiers.end());
	{
		for (const auto& i: getAttributes())
			outIterator = getModifiers(i.second, outIterator);
		}
	
	std::set<std::shared_ptr<Item>> items;
	{
		for (const auto& i: modifiers)
		{
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
		for (const auto& i: item.attributes_)
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
		for (const auto& i: item.effects_)
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
		for (const auto& list: item.itemModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}

	os << "], \"locationModifiers\":[";
	
	if (item.locationModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& list: item.locationModifiers_) {
			for (const auto& i: list.second)
			{
				if (isFirst)
					isFirst = false;
				else
					os << ',';
				os << *i;
			}
		}
	}

	os << "], \"locationGroupModifiers\":[";
	
	if (item.locationGroupModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: item.locationGroupModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}

	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (item.locationRequiredSkillModifiers_.size() > 0)
	{
		bool isFirst = true;
		for (const auto& map: item.locationRequiredSkillModifiers_) {
			for (const auto& list: map.second) {
				for (const auto& i: list.second)
				{
					if (isFirst)
						isFirst = false;
					else
						os << ',';
					os << *i;
				}
			}
		}
	}

	os << "]}";
	return os;
}
