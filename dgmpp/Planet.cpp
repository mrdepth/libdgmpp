//
//  Planet.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 13.01.16.
//
//

#include "Planet.h"
#include "Engine.h"
#include "Item.h"
#include "CommandCenter.h"
#include "ExtractorControlUnit.h"
#include "IndustryFacility.h"
#include "StorageFacility.h"
#include "Spaceport.h"
#include <cmath>
#include <sstream>

using namespace dgmpp;

Planet::Planet(std::shared_ptr<Engine> const& engine, TypeID typeID): engine_(engine) {
}

std::shared_ptr<Engine> Planet::getEngine() const {
	return engine_.lock();
}

std::shared_ptr<Facility> Planet::addFacility(TypeID typeID, int64_t identifier) {
	auto engine = getEngine();
	auto stmt = engine->getSqlConnector()->getReusableFetchRequest("SELECT groupID, capacity, typeName FROM invTypes WHERE typeID = ? LIMIT 1");
	
	stmt->bindInt(1, typeID);
	std::shared_ptr<FetchResult> result = engine->getSqlConnector()->exec(stmt);
	if (result->next()) {
		TypeID groupID = result->getInt(0);
		double capacity = result->getDouble(1);
		std::string typeName = result->getText(2);
		std::shared_ptr<Facility> facility;
		
		switch (groupID) {
			case CommandCenter::GROUP_ID:
				facility = std::make_shared<CommandCenter>(typeID, typeName, capacity, shared_from_this(), identifier);
				break;
			case IndustryFacility::GROUP_ID:
				facility = std::make_shared<IndustryFacility>(typeID, typeName, capacity, shared_from_this(), identifier);
				break;
			case StorageFacility::GROUP_ID:
				facility = std::make_shared<StorageFacility>(typeID, typeName, capacity, shared_from_this(), identifier);
				break;
			case Spaceport::GROUP_ID:
				facility = std::make_shared<Spaceport>(typeID, typeName, capacity, shared_from_this(), identifier);
				break;
			case ExtractorControlUnit::GROUP_ID:
				facility = std::make_shared<ExtractorControlUnit>(typeID, typeName, capacity, shared_from_this(), identifier);
				break;
			default:
				facility = std::make_shared<Facility>(typeID, typeName, capacity, shared_from_this(), identifier);
				break;
		}
		facilities_.push_back(facility);
		return facility;
	}
	else {
		throw Item::UnknownTypeIDException(std::to_string(typeID));
	}

}

void Planet::removeFacility(std::shared_ptr<Facility> const& facility) {
	RoutesList routes;
	for (auto route: routes_) {
		if (route->getSource() == facility)
			route->getDestination()->removeInput(route.get());
		else if (route->getDestination() == facility)
			route->getSource()->removeOutput(route.get());
		else
			routes.push_back(route);
	}
	routes_ = routes;
	facilities_.remove(facility);
}

std::shared_ptr<Route> Planet::addRoute(std::shared_ptr<Facility> const& source, std::shared_ptr<Facility> const& destination, TypeID contentTypeID, int64_t identifier) {
	auto route = std::make_shared<Route>(source, destination, contentTypeID, identifier);
	source->addOutput(route.get());
	destination->addInput(route.get());
	routes_.push_back(route);
	return route;
}

void Planet::removeRoute(std::shared_ptr<Route> const& route) {
	route->getSource()->removeOutput(route.get());
	route->getDestination()->removeInput(route.get());
	routes_.remove(route);
}

std::shared_ptr<Facility> Planet::findFacility(int64_t identifier) {
	for (auto facility: facilities_)
		if (facility->getIdentifier() == identifier)
			return facility;
	return nullptr;
}

void Planet::setLastUpdate(double lastUpdate) {
	lastUpdate_ = lastUpdate;
}

double Planet::getLastUpdate() {
	return lastUpdate_;
}

double Planet::getNextCycleTime() {
	double nextCycleTime = std::numeric_limits<double>::infinity();
	for (auto facility: facilities_) {
		double time = facility->getCycleEndTime();
		if (time > lastUpdate_)
			nextCycleTime = std::min(time, nextCycleTime);
	}
	return nextCycleTime > lastUpdate_ && !std::isinf(nextCycleTime) ? nextCycleTime : 0;
}

void Planet::runCycle(double cycleTime) {
	for (auto facility: facilities_) {
		double cycleEndTime = facility->getCycleEndTime();
		if (cycleEndTime > 0 && std::fabs(cycleEndTime - cycleEndTime) < 0.5) {
			facility->finishCycle(cycleTime);
		}
	}
	for (auto facility: facilities_) {
		double launchTime = facility->getLaunchTime();
		if (launchTime == 0)
			facility->startCycle(cycleTime);
	}
}

double Planet::simulate() {
	double endTime = getLastUpdate();
	while (1) {
		double nextCycleTime = getNextCycleTime();
		if (nextCycleTime > 0) {
			runCycle(nextCycleTime);
			endTime = nextCycleTime;
		}
		else
			break;
	}
	return endTime;
}

std::string Planet::toJSONString() const {
	std::stringstream os;
	bool isFirst = true;
	os << "\"facilities\":[";
	for (const auto& facility: facilities_) {
		if (isFirst)
			isFirst = false;
		else
			os << "," << std::endl;;
		os << *facility;
	}
	os << "]" << std::endl;
	return os.str();
}

std::ostream& dgmpp::operator<<(std::ostream& os, const Planet& planet) {
	return os << "{" << planet.toJSONString() << "}" << std::endl;
}
