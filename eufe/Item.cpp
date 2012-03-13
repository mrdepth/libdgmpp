#include "Item.h"

#include "Attribute.h"
#include "Effect.h"
#include "Engine.h"
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <functional>
#include <limits>
#include "Modifier.h"
#include "LocationGroupModifier.h"
#include "LocationRequiredSkillModifier.h"
#include "Ship.h"
#include "Character.h"
#include "Gang.h"
#include "Area.h"

using namespace eufe;

const TypeID eufe::ANY_GROUP_ID = std::numeric_limits<TypeID>::max();
const TypeID eufe::CHARACTER_GROUP_ID = 1;
const TypeID eufe::WARP_DISRUPT_FIELD_GENERATOR_GROUP_ID = 899;
const TypeID eufe::CAPACITOR_BOOSTER_GROUP_ID = 76;

const TypeID eufe::MODULE_CATEGORY_ID = 7;
const TypeID eufe::CHARGE_CATEGORY_ID = 8;
const TypeID eufe::DRONE_CATEGORY_ID = 18;
const TypeID eufe::SUBSYSTEM_CATEGORY_ID = 32;

class ModifierMatchFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	ModifierMatchFunction(TypeID attributeID) : attributeID_(attributeID) {}
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		return !(modifier->getAttributeID() == attributeID_);
	}
private:
	TypeID attributeID_;
};

class LocationGroupModifierMatchFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	LocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID) : attributeID_(attributeID), groupID_(groupID) {}
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && boost::dynamic_pointer_cast<LocationGroupModifier>(modifier)->getGroupID() == groupID_);
	}
private:
	TypeID attributeID_;
	TypeID groupID_;
};

class LocationRequiredSkillModifierMatchFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	LocationRequiredSkillModifierMatchFunction(TypeID attributeID, Item* item) : attributeID_(attributeID), item_(item) {}
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && item_->requireSkill(boost::dynamic_pointer_cast<LocationRequiredSkillModifier>(modifier)->getSkillID()));
	}
private:
	TypeID attributeID_;
	Item* item_;
};

class ModifiersFindFunction : public std::unary_function<const boost::shared_ptr<Modifier>&, bool>
{
public:
	ModifiersFindFunction(const boost::shared_ptr<Modifier>& modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (const boost::shared_ptr<Modifier>& modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	Attribute* modifier_;
	Modifier::Association association_;
};


Item::Item(void) : owner_(NULL), typeID_(0)
{
}

Item::Item(Engine* engine, TypeID typeID, Item* owner) : engine_(engine), owner_(owner), typeID_(typeID), groupID_(0)
{
	if (typeID == 0)
		return;
	Engine::scoped_lock lock(*engine);
	
	sqlite3* db = engine->getDb();
	std::stringstream sql;
#if _DEBUG
	sql << "SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID, typeName FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = " << typeID;
#else
	sql << "SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = " << typeID;
#endif

	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
	int result = sqlite3_step(stmt);
	
	if (result == SQLITE_ROW)
	{
		groupID_ = sqlite3_column_int(stmt, 0);
		float radius = static_cast<float>(sqlite3_column_double(stmt, 1));
		float mass = static_cast<float>(sqlite3_column_double(stmt, 2));
		float volume = static_cast<float>(sqlite3_column_double(stmt, 3));
		float capacity = static_cast<float>(sqlite3_column_double(stmt, 4));
		int raceID = sqlite3_column_int(stmt, 5);
		categoryID_ = sqlite3_column_int(stmt, 6);
		
#if _DEBUG
		typeName_ = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
		attributes_[RADIUS_ATTRIBUTE_ID]    = boost::shared_ptr<Attribute>(new Attribute(engine, RADIUS_ATTRIBUTE_ID,    0, radius,   true,  true, this, "radius"));
		attributes_[MASS_ATTRIBUTE_ID]      = boost::shared_ptr<Attribute>(new Attribute(engine, MASS_ATTRIBUTE_ID,      0, mass,     false, true, this, "mass"));
		attributes_[VOLUME_ATTRIBUTE_ID]    = boost::shared_ptr<Attribute>(new Attribute(engine, VOLUME_ATTRIBUTE_ID,    0, volume,   true,  true, this, "volume"));
		attributes_[CAPACITY_ATTRIBUTE_ID]  = boost::shared_ptr<Attribute>(new Attribute(engine, CAPACITY_ATTRIBUTE_ID,  0, capacity, true,  true, this, "capacity"));
		attributes_[RACE_ID_ATTRIBUTE_ID]   = boost::shared_ptr<Attribute>(new Attribute(engine, RACE_ID_ATTRIBUTE_ID,   0, static_cast<float>(raceID), true, true, this, "raceID"));
#else
		attributes_[RADIUS_ATTRIBUTE_ID]    = boost::shared_ptr<Attribute>(new Attribute(engine, RADIUS_ATTRIBUTE_ID,    0, radius,   true,  true, this));
		attributes_[MASS_ATTRIBUTE_ID]      = boost::shared_ptr<Attribute>(new Attribute(engine, MASS_ATTRIBUTE_ID,      0, mass,     false, true, this));
		attributes_[VOLUME_ATTRIBUTE_ID]    = boost::shared_ptr<Attribute>(new Attribute(engine, VOLUME_ATTRIBUTE_ID,    0, volume,   true,  true, this));
		attributes_[CAPACITY_ATTRIBUTE_ID]  = boost::shared_ptr<Attribute>(new Attribute(engine, CAPACITY_ATTRIBUTE_ID,  0, capacity, true,  true, this));
		attributes_[RACE_ID_ATTRIBUTE_ID]   = boost::shared_ptr<Attribute>(new Attribute(engine, RACE_ID_ATTRIBUTE_ID,   0, static_cast<float>(raceID), true, true, this));
#endif

		sqlite3_finalize(stmt);
		sql.str(std::string());
#if _DEBUG
		sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood, attributeName FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
			<< typeID;
#else
		sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
			<< typeID;
#endif
		stmt = NULL;
		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			TypeID attributeID = static_cast<TypeID>(sqlite3_column_int(stmt, 0));
			TypeID maxAttributeID = static_cast<TypeID>(sqlite3_column_int(stmt, 1));
			bool isStackable = sqlite3_column_int(stmt, 2) != 0;
			float value = static_cast<float>(sqlite3_column_double(stmt, 3));
			bool highIsGood = sqlite3_column_int(stmt, 4) != 0;
#if _DEBUG
			const char* attributeName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
			attributes_[attributeID] = boost::shared_ptr<Attribute>(new Attribute(engine, attributeID, maxAttributeID, value, isStackable, highIsGood, this, attributeName));
#else
			attributes_[attributeID] = boost::shared_ptr<Attribute>(new Attribute(engine, attributeID, maxAttributeID, value, isStackable, highIsGood, this));
#endif
		}
		sqlite3_finalize(stmt);
		
		sql.str(std::string());
#if _DEBUG
		sql << "SELECT dgmCompiledEffects.effectID, dgmCompiledEffects.effectCategory, dgmCompiledEffects.isAssistance, dgmCompiledEffects.isOffensive, byteCode, effectName FROM dgmCompiledEffects INNER JOIN dgmTypeEffects ON dgmCompiledEffects.effectID = dgmTypeEffects.effectID WHERE dgmTypeEffects.typeID = " << typeID;
#else
		sql << "SELECT dgmCompiledEffects.effectID, dgmCompiledEffects.effectCategory, dgmCompiledEffects.isAssistance, dgmCompiledEffects.isOffensive, byteCode FROM dgmCompiledEffects INNER JOIN dgmTypeEffects ON dgmCompiledEffects.effectID = dgmTypeEffects.effectID WHERE dgmTypeEffects.typeID = " << typeID;
#endif		
		stmt = NULL;
		sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, NULL);
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			TypeID effectID = static_cast<TypeID>(sqlite3_column_int(stmt, 0));
			Effect::Category category = static_cast<Effect::Category>(sqlite3_column_int(stmt, 1));
			bool isAssistance = sqlite3_column_int(stmt, 2) != 0;
			bool isOffensive = sqlite3_column_int(stmt, 3) != 0;
			size_t bytes = sqlite3_column_bytes(stmt, 4);
			const void* byteCode = sqlite3_column_blob(stmt, 4);
#if _DEBUG
			const char* effectName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
			effects_.push_back(boost::shared_ptr<Effect>(new Effect(engine_, effectID, category, byteCode, bytes, isAssistance, isOffensive, effectName)));
#else
			effects_.push_back(boost::shared_ptr<Effect>(new Effect(engine_, effectID, category, byteCode, bytes, isAssistance, isOffensive)));
#endif
		}
		sqlite3_finalize(stmt);
		
	}
	else
	{
		sqlite3_finalize(stmt);
		throw UnknownTypeIDException() << TypeIDExceptionInfo(typeID);
	}
}

Item::Item(Item* owner) : owner_(owner)
{
}

Item::Item(const Item& from) : engine_(from.engine_), typeID_(from.typeID_), groupID_(from.groupID_), categoryID_(from.categoryID_), owner_(NULL), effects_(from.effects_)
{
	AttributesMap::const_iterator i, end = from.attributes_.end();
	for (i = from.attributes_.begin(); i != end; i++)
	{
		boost::shared_ptr<Attribute> attribute(new Attribute(*i->second.get()));
		attribute->setOwner(this);
		attributes_[i->first] = attribute;
	}
	
#if _DEBUG
	typeName_ = from.typeName_;
#endif
}

Item::~Item(void)
{
}

void Item::setContext(const boost::shared_ptr<Context>& context)
{
	context_ = context;
}

boost::shared_ptr<Item::Context> Item::getContext()
{
	return context_;
}

Engine* Item::getEngine()
{
	return engine_;
}

Item* Item::getOwner() const
{
	return owner_;
}

void Item::setOwner(Item* owner)
{
	owner_ = owner;
}


boost::shared_ptr<Attribute> Item::getAttribute(TypeID attributeID)
{
	Item::scoped_lock lock(*this);
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return i->second;
	else
		return attributes_[attributeID] = boost::shared_ptr<Attribute>(new Attribute(engine_, attributeID, this, true));
		//throw AttributeDidNotFoundException() << TypeIDExceptionInfo(attributeID);
}

const AttributesMap &Item::getAttributes()
{
	return attributes_;
}

bool Item::hasAttribute(TypeID attributeID)
{
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return !i->second->isFakeAttribute();
	else
		return false;
}

boost::shared_ptr<Effect> Item::getEffect(TypeID effectID)
{
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getEffectID() == effectID)
			return (*i);
	throw EffectDidNotFoundException() << TypeIDExceptionInfo(effectID);
}


bool Item::requireSkill(TypeID skillID)
{
	try
	{
		if (getAttribute(REQUIRED_SKILL1_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL2_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
		else if (getAttribute(REQUIRED_SKILL3_ATTRIBUTE_ID)->getInitialValue() == skillID)
			return true;
	}
	catch (AttributeDidNotFoundException&)
	{
	}
	return false;
}

bool Item::hasEffect(TypeID effectID)
{
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getEffectID() == effectID)
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
	boost::shared_ptr<Environment> environment = getEnvironment();
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == category)
			(*i)->addEffect(environment.get());
}

void Item::removeEffects(Effect::Category category)
{
	boost::shared_ptr<Environment> environment = getEnvironment();
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == category)
			(*i)->removeEffect(environment.get());
}

void Item::reset()
{
	AttributesMap::iterator i, end = attributes_.end();
	for (i = attributes_.begin(); i != end; i++)
		i->second->reset();
}

std::insert_iterator<ModifiersList> Item::getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Item::scoped_lock lock(*this);
	outIterator = std::remove_copy_if(itemModifiers_.begin(), itemModifiers_.end(), outIterator, ModifierMatchFunction(attribute->getAttributeID()));
	if (owner_)
	{
		outIterator = owner_->getLocationModifiers(attribute, outIterator);
		outIterator = owner_->getModifiersMatchingItem(this, attribute, outIterator);
	}
	return outIterator;
}

std::insert_iterator<ModifiersList> Item::getLocationModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Item::scoped_lock lock(*this);
	outIterator = std::remove_copy_if(locationModifiers_.begin(), locationModifiers_.end(), outIterator, ModifierMatchFunction(attribute->getAttributeID()));
//	if (owner_)
//		outIterator = owner_->getLocationModifiers(attribute, outIterator);
	return outIterator;

}

std::insert_iterator<ModifiersList> Item::getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Item::scoped_lock lock(*this);
	outIterator = std::remove_copy_if(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), outIterator, LocationGroupModifierMatchFunction(attribute->getAttributeID(), item->getGroupID()));
	outIterator = std::remove_copy_if(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), outIterator, LocationRequiredSkillModifierMatchFunction(attribute->getAttributeID(), item));
	if (owner_)
		outIterator = owner_->getModifiersMatchingItem(item, attribute, outIterator);
	return outIterator;
}

void Item::addItemModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	itemModifiers_.push_back(modifier);
}

void Item::addLocationModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	locationModifiers_.push_back(modifier);
}

void Item::addLocationGroupModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	locationGroupModifiers_.push_back(modifier);
}

void Item::addLocationRequiredSkillModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	locationRequiredSkillModifiers_.push_back(modifier);
}

void Item::removeItemModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	ModifiersList::iterator i = std::find_if(itemModifiers_.begin(), itemModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != itemModifiers_.end())
		itemModifiers_.erase(i);
}

void Item::removeLocationModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	ModifiersList::iterator i = std::find_if(locationModifiers_.begin(), locationModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationModifiers_.end())
		locationModifiers_.erase(i);
}

void Item::removeLocationGroupModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	ModifiersList::iterator i = std::find_if(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationGroupModifiers_.end())
		locationGroupModifiers_.erase(i);
}

void Item::removeLocationRequiredSkillModifier(boost::shared_ptr<Modifier> modifier)
{
	Item::scoped_lock lock(*this);
	ModifiersList::iterator i = std::find_if(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationRequiredSkillModifiers_.end())
		locationRequiredSkillModifiers_.erase(i);
}

#if _DEBUG

const char* Item::getTypeName() const
{
	return typeName_.c_str();
}

std::ostream& eufe::operator<<(std::ostream& os, eufe::Item& item)
{
	os << "{\"typeName\":\"" << item.getTypeName() << "\", \"typeID\":\"" << item.typeID_ << "\", \"groupID\":\"" << item.groupID_ << "\", \"attributes\":[";
	
	if (item.attributes_.size() > 0)
	{
		AttributesMap::const_iterator i, end = item.attributes_.end();
		bool isFirst = true;
		for (i = item.attributes_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *i->second;
		}
	}
	
	os << "], \"effects\":[";
	
	if (item.effects_.size() > 0)
	{
		EffectsList::const_iterator i, end = item.effects_.end();
		bool isFirst = true;
		for (i = item.effects_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}
	
	os << "], \"itemModifiers\":[";
	
	if (item.itemModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = item.itemModifiers_.end();
		bool isFirst = true;
		for (i = item.itemModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}

	os << "], \"locationModifiers\":[";
	
	if (item.locationModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = item.locationModifiers_.end();
		bool isFirst = true;
		for (i = item.locationModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << **i;
		}
	}

	os << "], \"locationGroupModifiers\":[";
	
	if (item.locationGroupModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = item.locationGroupModifiers_.end();
		bool isFirst = true;
		for (i = item.locationGroupModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationGroupModifier*>((*i).get());
		}
	}

	os << "], \"locationRequiredSkillModifiers\":[";
	
	if (item.locationRequiredSkillModifiers_.size() > 0)
	{
		ModifiersList::const_iterator i, end = item.locationRequiredSkillModifiers_.end();
		bool isFirst = true;
		for (i = item.locationRequiredSkillModifiers_.begin(); i != end; i++)
		{
			if (isFirst)
				isFirst = false;
			else
				os << ',';
			os << *dynamic_cast<LocationRequiredSkillModifier*>((*i).get());
		}
	}

	os << "]}";
	return os;
}

#endif
/*

{"typeName":"Minmatar Propulsion Systems", "typeID":"30554", "groupID":"989", "attributes":
	[
	 {"attributeName":"mass", "typeName":"Minmatar Propulsion Systems", "attributeID":"4", "value":"0", "initialValue":"0", "stackable":"0"},
	 {"attributeName":"capacity", "typeName":"Minmatar Propulsion Systems", "attributeID":"38", "value":"0", "initialValue":"0", "stackable":"1"},
	 {"attributeName":"volume", "typeName":"Minmatar Propulsion Systems", "attributeID":"161", "value":"0.01", "initialValue":"0.01", "stackable":"1"},
	 {"attributeName":"radius", "typeName":"Minmatar Propulsion Systems", "attributeID":"162", "value":"0", "initialValue":"0", "stackable":"1"},
	 {"attributeName":"primaryAttribute", "typeName":"Minmatar Propulsion Systems", "attributeID":"180", "value":"167", "initialValue":"167", "stackable":"1"},
	 {"attributeName":"secondaryAttribute", "typeName":"Minmatar Propulsion Systems", "attributeID":"181", "value":"168", "initialValue":"168", "stackable":"1"},
	 {"attributeName":"requiredSkill1", "typeName":"Minmatar Propulsion Systems", "attributeID":"182", "value":"3449", "initialValue":"3449", "stackable":"1"},
	 {"attributeName":"raceID", "typeName":"Minmatar Propulsion Systems", "attributeID":"195", "value":"0", "initialValue":"0", "stackable":"1"},
	 {"attributeName":"skillTimeConstant", "typeName":"Minmatar Propulsion Systems", "attributeID":"275", "value":"1", "initialValue":"1", "stackable":"1"},
	 {"attributeName":"skillPoints", "typeName":"Minmatar Propulsion Systems", "attributeID":"276", "value":"0", "initialValue":"0", "stackable":"1"},
	 {"attributeName":"requiredSkill1Level", "typeName":"Minmatar Propulsion Systems", "attributeID":"277", "value":"5", "initialValue":"5", "stackable":"1"},
	 {"attributeName":"skillLevel", "typeName":"Minmatar Propulsion Systems", "attributeID":"280", "value":"0", "initialValue":"0", "stackable":"1"}
	],
	"effects":
	[
	 {"effectName":"skillEffect", "effectID":"132"},
	 {"effectName":"subsystemSkillLevelMinmatarPropulsion", "effectID":"3851"},
	 {"effectName":"subsystemSkillLevelMinmatarPropulsion2", "effectID":"4214"}
	]
}*/