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

using namespace dgmpp;

const TypeID dgmpp::ANY_GROUP_ID = std::numeric_limits<TypeID>::max();
const TypeID dgmpp::CHARACTER_GROUP_ID = 1;
const TypeID dgmpp::WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID = 899;
const TypeID dgmpp::CAPACITOR_BOOSTER_GROUP_ID = 76;
const TypeID dgmpp::CONTROL_TOWER_GROUP_ID = 365;
const TypeID dgmpp::CAPACITOR_BOOSTER_CHARGE_GROUP_ID = 87;
const TypeID dgmpp::NANITE_REPAIR_PASTE_GROUP_ID = 916;

const TypeID dgmpp::MODULE_CATEGORY_ID = 7;
const TypeID dgmpp::CHARGE_CATEGORY_ID = 8;
const TypeID dgmpp::DRONE_CATEGORY_ID = 18;
const TypeID dgmpp::SUBSYSTEM_CATEGORY_ID = 32;
const TypeID dgmpp::STARBASE_CATEGORY_ID = 23;
const TypeID dgmpp::STRUCTURE_MODULE_CATEGORY_ID = 66;
const TypeID dgmpp::FIGHTER_CATEGORY_ID = 87;

const TypeID dgmpp::MISSILE_LAUNCHER_OPERATION_TYPE_ID = 3319;

const TypeID dgmpp::CALDARI_RACE_ID = 1;
const TypeID dgmpp::MINMATAR_RACE_ID = 2;
const TypeID dgmpp::AMARR_RACE_ID = 4;
const TypeID dgmpp::GALLENTE_RACE_ID = 8;

const TypeID dgmpp::NITROGEN_FUEL_BLOCK_TYPE_ID = 4051;
const TypeID dgmpp::HYDROGEN_FUEL_BLOCK_TYPE_ID = 4246;
const TypeID dgmpp::HELIUM_FUEL_BLOCK_TYPE_ID = 4247;
const TypeID dgmpp::OXYGEN_FUEL_BLOCK_TYPE_ID = 4312;

const TypeID dgmpp::SHIELD_OPERATION_TYPE_ID = 3416;
const TypeID dgmpp::SHIELD_EMISSION_SYSTEMS_TYPE_ID = 3422;
const TypeID dgmpp::REPAIR_SYSTEMS_TYPE_ID = 3393;
const TypeID dgmpp::REMOTE_ARMOR_REPAIR_SYSTEMS_TYPE_ID = 16069;
const TypeID dgmpp::ECM_GROUP_ID = 201;
const TypeID dgmpp::SENSOR_DAMPENER_GROUP_ID = 208;
const TypeID dgmpp::WEAPON_DISRUPTOR_GROUP_ID = 291;
const TypeID dgmpp::TARGET_PAINTER_GROUP_ID = 379;


/*class ModifierMatchFunction : public std::unary_function<std::shared_ptr<Modifier> const&, bool>
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
};*/


Item::Item(std::shared_ptr<Engine> const& engine, TypeID typeID, std::shared_ptr<Item> const& owner) : engine_(engine), owner_(owner), typeID_(typeID), groupID_(0), loaded_(false)
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
	if (typeID_ == 0)
		return nullptr;
	
	loadIfNeeded();
	auto engine = getEngine();
	if (!engine)
		return nullptr;

	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return i->second;
	else
		return attributes_[attributeID] = Attribute::getAttribute(engine, attributeID, shared_from_this(), true);
		//return attributes_[attributeID] = std::make_shared<Attribute>(engine, attributeID, shared_from_this(), true);
		//throw AttributeDidNotFoundException() << TypeIDExceptionInfo(attributeID);
}

const AttributesMap &Item::getAttributes()
{
	loadIfNeeded();
	return attributes_;
}

bool Item::hasAttribute(TypeID attributeID)
{
	if (typeID_ == 0)
		return false;
	
	loadIfNeeded();
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return !i->second->isFakeAttribute();
	else
		return false;
}

std::shared_ptr<Effect> Item::getEffect(TypeID effectID)
{
	if (typeID_ == 0)
		return nullptr;

	loadIfNeeded();
	for (const auto& i: effects_)
		if (i->getEffectID() == effectID)
			return i;
    throw EffectDidNotFoundException(std::to_string(effectID));
}

bool Item::requireSkill(TypeID skillID)
{
	if (typeID_ == 0)
		return false;

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
	if (typeID_ == 0)
		return false;

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
	for (const auto& i: effects_)
		if (i->getCategory() == category)
			i->addEffect(this);
}

void Item::removeEffects(Effect::Category category)
{
	loadIfNeeded();
	for (const auto& i: effects_)
		if (i->getCategory() == category)
			i->removeEffect(this);
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

std::insert_iterator<ModifiersList> Item::getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	if (typeID_ == 0)
		return outIterator;

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

std::insert_iterator<ModifiersList> Item::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	if (typeID_ == 0)
		return outIterator;

	auto i = locationModifiers_.find(attribute->getAttributeID());
	if (i != locationModifiers_.end())
		outIterator = std::copy(i->second.begin(), i->second.end(), outIterator);
	return outIterator;
}

std::insert_iterator<ModifiersList> Item::getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	if (typeID_ == 0)
		return outIterator;

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
	if (typeID_ == 0)
		return;
	itemModifiers_[modifier->getAttributeID()].push_back(modifier);
}

void Item::addLocationModifier(std::shared_ptr<Modifier> const& modifier)
{
	if (typeID_ == 0)
		return;
	locationModifiers_[modifier->getAttributeID()].push_back(modifier);
}

void Item::addLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier)
{
	if (typeID_ == 0)
		return;
	locationGroupModifiers_[modifier->getGroupID()][modifier->getAttributeID()].push_back(modifier);
}

void Item::addLocationRequiredSkillModifier(std::shared_ptr<LocationRequiredSkillModifier> const& modifier)
{
	if (typeID_ == 0)
		return;
	locationRequiredSkillModifiers_[modifier->getSkillID()][modifier->getAttributeID()].push_back(modifier);
}

void Item::removeItemModifier(std::shared_ptr<Modifier> const& modifier)
{
	if (typeID_ == 0)
		return;
	auto& list = itemModifiers_[modifier->getAttributeID()];
	auto i = std::find(list.begin(), list.end(), modifier);
	if (i != list.end())
		list.erase(i);
	if (list.size() == 0)
		itemModifiers_.erase(modifier->getAttributeID());
}

void Item::removeLocationModifier(std::shared_ptr<Modifier> const& modifier)
{
	if (typeID_ == 0)
		return;
	auto& list = locationModifiers_[modifier->getAttributeID()];
	auto i = std::find(list.begin(), list.end(), modifier);
	if (i != list.end())
		list.erase(i);
	if (list.size() == 0)
		locationModifiers_.erase(modifier->getAttributeID());
}

void Item::removeLocationGroupModifier(std::shared_ptr<LocationGroupModifier> const& modifier)
{
	if (typeID_ == 0)
		return;
	auto& map = locationGroupModifiers_[modifier->getGroupID()];
	auto& list = map[modifier->getAttributeID()];
	auto i = std::find(list.begin(), list.end(), modifier);
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
	if (typeID_ == 0)
		return;
	auto& map = locationRequiredSkillModifiers_[modifier->getSkillID()];
	auto& list = map[modifier->getAttributeID()];
	auto i = std::find(list.begin(), list.end(), modifier);
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
	if (typeID_ == 0)
		return "<dummy>";
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
	if (typeID_ == 0)
		return "<dummy>";

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

std::shared_ptr<Attribute> Item::addExtraAttribute(TypeID attributeID, Float value) {
	if (typeID_ == 0)
		return nullptr;

	auto engine = getEngine();
	if (!engine)
		return nullptr;

	return attributes_[attributeID] = Attribute::getAttribute(engine, attributeID, shared_from_this(), false, value);
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
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID, typeName FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = ? LIMIT 1");
	stmt->bindInt(1, typeID_);
	
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	if (result->next())
	{
		groupID_ = result->getInt(0);
		Float radius = static_cast<Float>(result->getDouble(1));
		Float mass = static_cast<Float>(result->getDouble(2));
		Float volume = static_cast<Float>(result->getDouble(3));
		Float capacity = static_cast<Float>(result->getDouble(4));
		int raceID = result->getInt(5);
		categoryID_ = result->getInt(6);
		
		typeName_ = result->getText(7);
		attributes_[RADIUS_ATTRIBUTE_ID] = Attribute::getAttribute(engine, RADIUS_ATTRIBUTE_ID,  shared_from_this(), false, radius);
		attributes_[MASS_ATTRIBUTE_ID] = Attribute::getAttribute(engine, MASS_ATTRIBUTE_ID,  shared_from_this(), false, mass);
		attributes_[VOLUME_ATTRIBUTE_ID] = Attribute::getAttribute(engine, VOLUME_ATTRIBUTE_ID,  shared_from_this(), false, volume);
		attributes_[CAPACITY_ATTRIBUTE_ID] = Attribute::getAttribute(engine, CAPACITY_ATTRIBUTE_ID,  shared_from_this(), false, capacity);
		attributes_[RACE_ID_ATTRIBUTE_ID] = Attribute::getAttribute(engine, RACE_ID_ATTRIBUTE_ID,  shared_from_this(), false, static_cast<Float>(raceID));
		
		//sql.str(std::string());
		//sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood, attributeName FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
		//<< typeID_;
		stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT attributeID, value FROM dgmTypeAttributes WHERE typeID = ?");
		stmt->bindInt(1, typeID_);
		result = engine->getSqlConnector()->exec(stmt);
		
		while (result->next())
		{
			TypeID attributeID = static_cast<TypeID>(result->getInt(0));
			Float value = static_cast<Float>(result->getDouble(1));
			attributes_[attributeID] = Attribute::getAttribute(engine, attributeID, shared_from_this(), false, value);
		}
		
		//sql.str(std::string());
		//sql << "SELECT effectID FROM dgmTypeEffects WHERE dgmTypeEffects.typeID = " << typeID_;
		stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT effectID FROM dgmTypeEffects WHERE dgmTypeEffects.typeID = ?");
		stmt->bindInt(1, typeID_);
		result = engine->getSqlConnector()->exec(stmt);

		while (result->next())
		{
			TypeID effectID = static_cast<TypeID>(result->getInt(0));
			effects_.push_back(Effect::getEffect(engine, effectID, shared_from_this()));
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
			auto i = attributes_.find(attributeID);
			if (i != attributes_.end()) {
				TypeID skillID = i->second->getInitialValue();
				if (skillID > 0)
					requiredSkills_.push_back(skillID);
			}

		}
		requiredSkills_.shrink_to_fit();
	}
	else
	{
		throw UnknownTypeIDException(std::to_string(typeID_));
	}
}


std::set<std::shared_ptr<Item>> Item::getAffectors() {
	if (typeID_ == 0)
		return std::set<std::shared_ptr<Item>>();
	
	ModifiersList modifiers;

	auto outIterator = std::inserter(modifiers, modifiers.end());
	{
		for (const auto& i: getAttributes())
			outIterator = getModifiers(i.second.get(), outIterator);
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

Item* Item::self() {
	return this;
}

Item* Item::gang() {
	return getEngine()->getGang().get();
}

Item* Item::area() {
	return getEngine()->getArea().get();
}

std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Item& item)
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
