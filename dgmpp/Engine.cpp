#include "Engine.h"
#include "Gang.h"
#include "Area.h"
#include "ControlTower.h"
#include "Planet.h"
#include <cmath>
#include "Attribute.h"
#include "SpaceStructure.h"

using namespace dgmpp;

Engine::Engine(std::shared_ptr<SqlConnector> const& sqlConnector) : sqlConnector_(sqlConnector), gang_(nullptr), area_(nullptr), controlTower_(nullptr), generation_(), updatesCounter_(0), decayFactor_(std::numeric_limits<float>::quiet_NaN()), noiseFactor_(std::numeric_limits<float>::quiet_NaN())
{
}

Engine::~Engine(void)
{
}

std::shared_ptr<SqlConnector> Engine::getSqlConnector() const
{
	return sqlConnector_;
}

std::shared_ptr<Gang> Engine::getGang()
{
	if (!gang_)
		gang_ = std::make_shared<Gang>(shared_from_this());
	return gang_;
}

std::shared_ptr<Area> Engine::setArea(TypeID typeID)
{
	try
	{
		std::shared_ptr<Area> area = std::make_shared<Area>(shared_from_this(), typeID);
		if (area_) {
			area_->removeEffects(Effect::CATEGORY_SYSTEM);
		}
		area_ = area;
		if (area_)
			area_->addEffects(Effect::CATEGORY_SYSTEM);
		reset();
		
		return area_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

std::shared_ptr<ControlTower> Engine::setControlTower(TypeID typeID)
{
	try
	{
		std::shared_ptr<ControlTower> controlTower = std::make_shared<ControlTower>(shared_from_this(), typeID);
		if (controlTower_)
		{
			controlTower_->removeEffects(Effect::CATEGORY_GENERIC);
			controlTower_->removeEffects(Effect::CATEGORY_ACTIVE);
		}
		controlTower_ = controlTower;
		if (controlTower_)
		{
			controlTower_->addEffects(Effect::CATEGORY_GENERIC);
			controlTower_->addEffects(Effect::CATEGORY_ACTIVE);
		}
		
		reset();
		return controlTower_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

void Engine::clearArea()
{
	if (area_) {
		area_->removeEffects(Effect::CATEGORY_SYSTEM);
		reset();
	}
	area_ = nullptr;
}

std::shared_ptr<Area> Engine::getArea()
{
	return area_;
}

std::shared_ptr<ControlTower> Engine::getControlTower()
{
	return controlTower_;
}

std::shared_ptr<Planet> Engine::setPlanet(TypeID typeID) {
	planet_ = std::make_shared<Planet>(shared_from_this(), typeID);
	return planet_;
}

std::shared_ptr<Planet> Engine::getPlanet() {
	return planet_;
}

std::shared_ptr<SpaceStructure> Engine::setSpaceStructure(TypeID typeID)
{
	try
	{
		std::shared_ptr<SpaceStructure> spaceStructure = std::make_shared<SpaceStructure>(shared_from_this(), typeID);
		if (spaceStructure_)
		{
			spaceStructure_->removeEffects(Effect::CATEGORY_GENERIC);
			spaceStructure_->removeEffects(Effect::CATEGORY_ACTIVE);
		}
		spaceStructure_ = spaceStructure;
		if (spaceStructure_)
		{
			spaceStructure_->addEffects(Effect::CATEGORY_GENERIC);
			spaceStructure_->addEffects(Effect::CATEGORY_ACTIVE);
		}
		
		reset();
		return spaceStructure_;
	}
	catch(Item::UnknownTypeIDException)
	{
		return nullptr;
	}
}

std::shared_ptr<SpaceStructure> Engine::getSpaceStructure()
{
	return spaceStructure_;
}


void Engine::reset()
{
	if (updatesCounter_ > 0)
		return;
	generation_++;
	if (gang_)
		gang_->reset();
	if (controlTower_)
		controlTower_->reset();
	if (spaceStructure_)
		spaceStructure_->reset();
}

void Engine::beginUpdates() {
	updatesCounter_++;
}

void Engine::commitUpdates() {
	updatesCounter_--;
	if (updatesCounter_ <= 0) {
		updatesCounter_ = 0;
		reset();
	}
}

float Engine::decayFactor() const {
	if (std::isnan(decayFactor_)) {
		auto stmt = getSqlConnector()->getReusableFetchRequest("SELECT defaultValue FROM dgmAttributeTypes WHERE attributeID = ? LIMIT 1");
		stmt->bindInt(1, ECU_DECAY_FACTOR_ATTRIBUTE_ID);
		auto result = getSqlConnector()->exec(stmt);
		decayFactor_ = result->next()  ? result->getDouble(0) : 0;
	}
	return decayFactor_;
}

float Engine::noiseFactor() const {
	if (std::isnan(noiseFactor_)) {
		auto stmt = getSqlConnector()->getReusableFetchRequest("SELECT defaultValue FROM dgmAttributeTypes WHERE attributeID = ? LIMIT 1");
		stmt->bindInt(1, ECU_NOISE_FACTOR_ATTRIBUTE_ID);
		auto result = getSqlConnector()->exec(stmt);
		noiseFactor_ = result->next()  ? result->getDouble(0) : 1;
	}
	return noiseFactor_;
}

const std::map<TypeID, CommodityTier>& Engine::getCommodityTiers() const {
	if (commodityTiers_.size() == 0) {
		auto stmt = getSqlConnector()->getReusableFetchRequest("CREATE TEMP TABLE temp.tiers as SELECT typeID, 0 as \"tier\" FROM planetSchematicsTypeMap WHERE typeID not in (SELECT typeID FROM planetSchematicsTypeMap WHERE isInput = 0 GROUP BY typeID);");
		getSqlConnector()->exec(stmt)->next();
		for (int i = 1; i <= 4; i++) {
			stmt = getSqlConnector()->getReusableFetchRequest("INSERT INTO temp.tiers SELECT typeID, ? AS \"tier\" FROM planetSchematicsTypeMap WHERE schematicID in (SELECT schematicID FROM planetSchematicsTypeMap WHERE typeID in (SELECT typeID FROM tiers WHERE tier=?) AND isInput=1) AND isInput = 0;");
			stmt->bindInt(1, i);
			stmt->bindInt(2, i - 1);
			getSqlConnector()->exec(stmt)->next();
		};
		stmt = getSqlConnector()->getReusableFetchRequest("SELECT * FROM temp.tiers");
		auto result = getSqlConnector()->exec(stmt);
		while (result->next()) {
			TypeID typeID = result->getInt(0);
			CommodityTier tier = static_cast<CommodityTier>(result->getInt(1));
			commodityTiers_[typeID] = tier;
		}
	}
	return commodityTiers_;
}


//std::lock_guard<std::recursive_mutex> Engine::lock() {
//	return std::lock_guard<std::recursive_mutex>(mutex_);
//}


std::ostream& dgmpp::operator<<(std::ostream& os, dgmpp::Engine& engine)
{
	os << "{\"gang\":" << *engine.getGang();
	if (engine.getControlTower())
		os << ", \"controlTower\":" << *engine.getControlTower();
	if (engine.getSpaceStructure())
		os << ", \"spaceStructure\":" << *engine.getSpaceStructure();
	os << '}';
	return os;
}
