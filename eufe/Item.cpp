#include "Item.h"

#include "Attribute.h"
#include "Effect.h"
#include "Engine.h"
//#include <boost/lexical_cast.hpp>
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
const TypeID eufe::CONTROL_TOWER_GROUP_ID = 365;
const TypeID eufe::CAPACITOR_BOOSTER_CHARGE_GROUP_ID = 87;
const TypeID eufe::NANITE_REPAIR_PASTE_GROUP_ID = 916;

const TypeID eufe::MODULE_CATEGORY_ID = 7;
const TypeID eufe::CHARGE_CATEGORY_ID = 8;
const TypeID eufe::DRONE_CATEGORY_ID = 18;
const TypeID eufe::SUBSYSTEM_CATEGORY_ID = 32;
const TypeID eufe::STRUCTURE_CATEGORY_ID = 23;

const TypeID eufe::MISSILE_LAUNCHER_OPERATION_TYPE_ID = 3319;

class ModifierMatchFunction : public std::unary_function<Modifier*, bool>
{
public:
	ModifierMatchFunction(TypeID attributeID) : attributeID_(attributeID) {}
	bool operator() (Modifier* modifier)
	{
		return !(modifier->getAttributeID() == attributeID_);
	}
private:
	TypeID attributeID_;
};

class LocationGroupModifierMatchFunction : public std::unary_function<Modifier*, bool>
{
public:
	LocationGroupModifierMatchFunction(TypeID attributeID, TypeID groupID) : attributeID_(attributeID), groupID_(groupID) {}
	bool operator() (Modifier* modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && dynamic_cast<LocationGroupModifier*>(modifier)->getGroupID() == groupID_);
	}
private:
	TypeID attributeID_;
	TypeID groupID_;
};

class LocationRequiredSkillModifierMatchFunction : public std::unary_function<Modifier*, bool>
{
public:
	LocationRequiredSkillModifierMatchFunction(TypeID attributeID, Item* item) : attributeID_(attributeID), item_(item) {}
	bool operator() (Modifier* modifier)
	{
		return !(modifier->getAttributeID() == attributeID_ && item_->requireSkill(dynamic_cast<LocationRequiredSkillModifier*>(modifier)->getSkillID()));
	}
private:
	TypeID attributeID_;
	Item* item_;
};

class ModifiersFindFunction : public std::unary_function<Modifier*, bool>
{
public:
	ModifiersFindFunction(Modifier* modifier) : attributeID_(modifier->getAttributeID()), modifier_(modifier->getModifier()), association_(modifier->getAssociation())	{};
	bool operator() (Modifier* modifier)
	{
		return modifier->getAttributeID() == attributeID_ && modifier->getAssociation() == association_ && modifier->getModifier() == modifier_;
	}
private:
	TypeID attributeID_;
	Attribute* modifier_;
	Modifier::Association association_;
};


Item::Item(void) : owner_(NULL), typeID_(0), context_(NULL), engine_(NULL)
{
}

Item::Item(Engine* engine, TypeID typeID, Item* owner) : engine_(engine), owner_(owner), typeID_(typeID), groupID_(0), context_(NULL)
{
	if (typeID == 0)
		return;
	Engine::ScopedLock lock(*engine_);
	
	std::stringstream sql;
#if _DEBUG
	sql << "SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID, typeName FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = " << typeID;
#else
	sql << "SELECT invTypes.groupID, radius, mass, volume, capacity, raceID, categoryID FROM invTypes, invGroups WHERE invTypes.groupID=invGroups.groupID AND typeID = " << typeID;
#endif

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
		
#if _DEBUG
		typeName_ = result->getText(7);
		attributes_[RADIUS_ATTRIBUTE_ID]    = new Attribute(engine, RADIUS_ATTRIBUTE_ID,    0, radius,   true,  true, this, "radius");
		attributes_[MASS_ATTRIBUTE_ID]      = new Attribute(engine, MASS_ATTRIBUTE_ID,      0, mass,     false, true, this, "mass");
		attributes_[VOLUME_ATTRIBUTE_ID]    = new Attribute(engine, VOLUME_ATTRIBUTE_ID,    0, volume,   true,  true, this, "volume");
		attributes_[CAPACITY_ATTRIBUTE_ID]  = new Attribute(engine, CAPACITY_ATTRIBUTE_ID,  0, capacity, true,  true, this, "capacity");
		attributes_[RACE_ID_ATTRIBUTE_ID]   = new Attribute(engine, RACE_ID_ATTRIBUTE_ID,   0, static_cast<float>(raceID), true, true, this, "raceID");
#else
		attributes_[RADIUS_ATTRIBUTE_ID]    = new Attribute(engine, RADIUS_ATTRIBUTE_ID,    0, radius,   true,  true, this);
		attributes_[MASS_ATTRIBUTE_ID]      = new Attribute(engine, MASS_ATTRIBUTE_ID,      0, mass,     false, true, this);
		attributes_[VOLUME_ATTRIBUTE_ID]    = new Attribute(engine, VOLUME_ATTRIBUTE_ID,    0, volume,   true,  true, this);
		attributes_[CAPACITY_ATTRIBUTE_ID]  = new Attribute(engine, CAPACITY_ATTRIBUTE_ID,  0, capacity, true,  true, this);
		attributes_[RACE_ID_ATTRIBUTE_ID]   = new Attribute(engine, RACE_ID_ATTRIBUTE_ID,   0, static_cast<float>(raceID), true, true, this);
#endif

		sql.str(std::string());
#if _DEBUG
		sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood, attributeName FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
			<< typeID;
#else
		sql << "SELECT dgmTypeAttributes.attributeID, maxAttributeID, stackable, value, highIsGood FROM dgmTypeAttributes INNER JOIN dgmAttributeTypes ON dgmTypeAttributes.attributeID = dgmAttributeTypes.attributeID WHERE typeID = "
			<< typeID;
#endif
		result = engine->getSqlConnector()->exec(sql.str().c_str());
		while (result->next())
		{
			TypeID attributeID = static_cast<TypeID>(result->getInt(0));
			TypeID maxAttributeID = static_cast<TypeID>(result->getInt(1));
			bool isStackable = result->getInt(2) != 0;
			float value = static_cast<float>(result->getDouble(3));
			bool highIsGood = result->getInt(4) != 0;
#if _DEBUG
			std::string attributeName = result->getText(5);
			attributes_[attributeID] = new Attribute(engine, attributeID, maxAttributeID, value, isStackable, highIsGood, this, attributeName.c_str());
#else
			attributes_[attributeID] = new Attribute(engine, attributeID, maxAttributeID, value, isStackable, highIsGood, this);
#endif
		}
		
		sql.str(std::string());
		sql << "SELECT effectID FROM dgmTypeEffects WHERE dgmTypeEffects.typeID = " << typeID;
		result = engine->getSqlConnector()->exec(sql.str().c_str());
		while (result->next())
		{
			TypeID effectID = static_cast<TypeID>(result->getInt(0));
			effects_.push_back(Effect::getEffect(engine_, effectID));
		}
	}
	else
	{
        throw UnknownTypeIDException(std::to_string(typeID));
	}
}

Item::Item(Item* owner) : owner_(owner), context_(NULL), engine_(NULL)
{
}

Item::Item(const Item& from) : engine_(from.engine_), typeID_(from.typeID_), groupID_(from.groupID_), categoryID_(from.categoryID_), owner_(NULL), context_(NULL), effects_(from.effects_)
{
	AttributesMap::const_iterator i, end = from.attributes_.end();
	for (i = from.attributes_.begin(); i!= end; i++)
	{
		Attribute* attribute = new Attribute(*(i->second));
		attribute->setOwner(this);
		attributes_[i->first] = attribute;
	}
	
#if _DEBUG
	typeName_ = from.typeName_;
#endif
}

Item::~Item(void)
{
	AttributesMap::iterator i, end = attributes_.end();
	for (i = attributes_.begin(); i!= end; i++)
		delete i->second;
	attributes_.clear();
	
	ModifiersList* lists[] = {&itemModifiers_, &locationModifiers_, &locationGroupModifiers_, &locationRequiredSkillModifiers_};
	for (int i = 0; i < 4; i++) {
		ModifiersList& list = *lists[i];
		ModifiersList::iterator j, endj = list.end();
		for (j = list.begin(); j != endj; j++)
			delete *j;
		list.clear();
	}
	
	setContext(NULL);
}

void Item::setContext(const Context* context)
{
	if (context_)
		delete context_;
	context_ = context;
}

const Item::Context* Item::getContext()
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


Attribute* Item::getAttribute(TypeID attributeID)
{
	Engine::ScopedLock lock(*engine_);
	AttributesMap::iterator i = attributes_.find(attributeID);
	if (i != attributes_.end())
		return i->second;
	else
		return attributes_[attributeID] = new Attribute(engine_, attributeID, this, true);
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

Effect* Item::getEffect(TypeID effectID)
{
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getEffectID() == effectID)
			return i->get();
    throw EffectDidNotFoundException(std::to_string(effectID));
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
	Environment environment = getEnvironment();
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == category)
			(*i)->addEffect(environment);
}

void Item::removeEffects(Effect::Category category)
{
	Environment environment = getEnvironment();
	EffectsList::iterator i, end = effects_.end();
	for (i = effects_.begin(); i != end; i++)
		if ((*i)->getCategory() == category)
			(*i)->removeEffect(environment);
}

void Item::reset()
{
	AttributesMap::iterator i, end = attributes_.end();
	for (i = attributes_.begin(); i != end; i++)
		i->second->reset();
}

std::insert_iterator<ModifiersList> Item::getModifiers(Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Engine::ScopedLock lock(*engine_);
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
	Engine::ScopedLock lock(*engine_);
	outIterator = std::remove_copy_if(locationModifiers_.begin(), locationModifiers_.end(), outIterator, ModifierMatchFunction(attribute->getAttributeID()));
//	if (owner_)
//		outIterator = owner_->getLocationModifiers(attribute, outIterator);
	return outIterator;

}

std::insert_iterator<ModifiersList> Item::getModifiersMatchingItem(Item* item, Attribute* attribute, std::insert_iterator<ModifiersList> outIterator)
{
	Engine::ScopedLock lock(*engine_);
	outIterator = std::remove_copy_if(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), outIterator, LocationGroupModifierMatchFunction(attribute->getAttributeID(), item->getGroupID()));
	outIterator = std::remove_copy_if(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), outIterator, LocationRequiredSkillModifierMatchFunction(attribute->getAttributeID(), item));
	if (owner_)
		outIterator = owner_->getModifiersMatchingItem(item, attribute, outIterator);
	return outIterator;
}

Item::Item(Decoder& decoder, Engine* engine, Item* owner) : engine_(engine), owner_(owner)
{
	decoder.decode(typeID_);
	decoder.decode(groupID_);
	decoder.decode(categoryID_);

	{
		AttributesMap::size_type size;
		decoder.decode(size);
		for (AttributesMap::size_type i = 0; i < size; i++)
		{
			Attribute* attribute = new Attribute(decoder, engine, this);
			attributes_[attribute->getAttributeID()] = attribute;
		}
	}
	{
		EffectsList::size_type size;
		decoder.decode(size);
		for (EffectsList::size_type i = 0; i < size; i++)
		{
			TypeID effectID;
			decoder.decode(effectID);
			effects_.push_back(Effect::getEffect(engine_, effectID));
		}
	}
}

void Item::encode(Encoder& encoder) const
{
	encoder.encode(typeID_);
	encoder.encode(groupID_);
	encoder.encode(categoryID_);
	
	{
		AttributesMap::const_iterator i, end = attributes_.end();
		encoder.encode(attributes_.size());
		for (i = attributes_.begin(); i != end; i++)
			i->second->encode(encoder);
	}
	{
		EffectsList::const_iterator i, end = effects_.end();
		encoder.encode(effects_.size());
		for (i = effects_.begin(); i != end; i++)
			encoder.encode((*i)->getEffectID());
	}

}

void Item::addItemModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	itemModifiers_.push_back(modifier);
}

void Item::addLocationModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	locationModifiers_.push_back(modifier);
}

void Item::addLocationGroupModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	locationGroupModifiers_.push_back(modifier);
}

void Item::addLocationRequiredSkillModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	locationRequiredSkillModifiers_.push_back(modifier);
}

void Item::removeItemModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	ModifiersList::iterator i = std::find_if(itemModifiers_.begin(), itemModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != itemModifiers_.end())
	{
		delete *i;
		itemModifiers_.erase(i);
	}
}

void Item::removeLocationModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	ModifiersList::iterator i = std::find_if(locationModifiers_.begin(), locationModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationModifiers_.end())
	{
		delete *i;
		locationModifiers_.erase(i);
	}
}

void Item::removeLocationGroupModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	ModifiersList::iterator i = std::find_if(locationGroupModifiers_.begin(), locationGroupModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationGroupModifiers_.end())
	{
		delete *i;
		locationGroupModifiers_.erase(i);
	}
}

void Item::removeLocationRequiredSkillModifier(Modifier* modifier)
{
	Engine::ScopedLock lock(*engine_);
	ModifiersList::iterator i = std::find_if(locationRequiredSkillModifiers_.begin(), locationRequiredSkillModifiers_.end(), ModifiersFindFunction(modifier));
	if (i != locationRequiredSkillModifiers_.end())
	{
		delete *i;
		locationRequiredSkillModifiers_.erase(i);
	}
}

const char* Item::getTypeName()
{
	if (typeName_.size() == 0)
	{
		std::stringstream sql;
		sql << "SELECT typeName FROM invTypes WHERE typeID = " << typeID_;

		std::shared_ptr<FetchResult> result = engine_->getSqlConnector()->exec(sql.str().c_str());
		if (result->next()) {
			typeName_ = result->getText(0);
		}
	}
	return typeName_.c_str();
}

const char* Item::getGroupName()
{
	if (groupName_.size() == 0)
	{
		std::stringstream sql;
		sql << "SELECT groupName FROM invTypes AS A, invGroups AS B WHERE A.groupID=B.groupID AND typeID = " << typeID_;

		std::shared_ptr<FetchResult> result = engine_->getSqlConnector()->exec(sql.str().c_str());
		if (result->next()) {
			groupName_ = result->getText(0);
		}
	}
	return groupName_.c_str();
}

std::set<Item*> Item::getAffectors() {
	ModifiersList modifiers;
	{
		auto attributes = getAttributes();
		auto attribute = attributes.begin(), end = attributes.end();
		for (;attribute != end; attribute++)
			getModifiers(attribute->second, std::inserter(modifiers, modifiers.begin()));
		}
	
	std::set<Item*> items;
	{
		auto modifier = modifiers.begin(), end = modifiers.end();
		for (; modifier != end; modifier++) {
			Item* item = (*modifier)->getModifier()->getOwner();
			if (item != this)
				items.insert((*modifier)->getModifier()->getOwner());
		}
	}
	
	return items;
}

#if _DEBUG

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
			os << *dynamic_cast<LocationGroupModifier*>((*i));
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
			os << *dynamic_cast<LocationRequiredSkillModifier*>((*i));
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