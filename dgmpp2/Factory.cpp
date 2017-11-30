//
//  Factory.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 29.11.2017.
//

#include "Factory.hpp"
#include "SDE.hpp"
#include "Planet.hpp"

namespace dgmpp2 {
	
	bool Factory::configured() const {
		if (!startTime_)
			return false;
		
		if (auto product = output()) {
			auto isOutputRouted = std::any_of(outputs_.begin(), outputs_.end(), [typeID = product->metaInfo().typeID](const auto& i) {
				return i.commodity.metaInfo().typeID == typeID;
			});
			if (isOutputRouted) {
				auto required = schematic_->inputs();
				return std::all_of(required.begin(), required.end(), [&](const auto& i) {
					return std::any_of(inputs_.begin(), inputs_.end(), [typeID = i.first->typeID](const auto& j) {
						return j.commodity.metaInfo().typeID == typeID;
					});
				});
			}
		}
		return false;
	}
	
	std::optional<Commodity> Factory::output() const {
		if (schematic_)
			return {Commodity(*schematic_->output.first, schematic_->output.second)};
		else
			return std::nullopt;
	}
	
	void Factory::schematic(SchematicID schematicID) {
		schematic_ = &SDE::get(schematicID);
	}
	
	int Factory::priority() const {
		return schematic_ ? static_cast<int>(schematic_->output.first->tier) : 0;
	}
	
	std::optional<std::chrono::seconds> Factory::cycleTime() const {
		if (schematic_)
			return schematic_->cycleTime;
		else
			return std::nullopt;
	}
	
	std::optional<std::chrono::seconds> Factory::nextUpdateTime() const {
		if (!configured())
			return std::nullopt;
		
		if (productionCycle_)
			return productionCycle_->end();
		else if (launchTime_ && (*launchTime_ + *cycleTime()) < planet().lastUpdate())
			return planet().lastUpdate();
		else
			return launchTime_;
	}
	
	void Factory::update(std::chrono::seconds time) {
		if (updating_ || !configured())
			return;
		updating_ = true;
		
		if (productionCycle_) {
			const auto isCycleFinished = productionCycle_->end() == time;
			if (isCycleFinished)
				finishCycle(time);
		}
		
		if (!productionCycle_)
			startCycle(time);
		
		auto materials = commodities();
		ProductionState* currentState = nullptr;
		
		if (!states_.empty()) {
			currentState = dynamic_cast<ProductionState*>(states_.back().get());
			if (currentState->timestamp < time && (currentState->cycle.get() != productionCycle_ || currentState->commodities != materials))
				currentState = nullptr;
		}
		
		if (!currentState) {
			currentState = new ProductionState(time, productionCycle_, 0);
			states_.emplace_back(currentState);
		}
		
		currentState->commodities.swap(materials);
		
		if (startTime_->count() > 0) {
			auto duration = time - *startTime_;
			if (duration.count() > 0)
				currentState->efficiency = productionTime_ / duration;
		}
		
		updating_ = false;
	}
	
	void Factory::finishCycle(std::chrono::seconds time) {
		auto product = *output();
		
		add(product);
		Facility::update(time);
		auto left = (*this)[product];
		productionCycle_->yield = product - left;
		productionCycle_->waste = left;
		if (left.quantity() > 0)
			extract(left);

		productionTime_ += productionCycle_->duration;
		productionCycle_ = nullptr;
		launchTime_ = std::nullopt;
		
		states_.emplace_back(new ProductionState(time, nullptr, productionTime_ / (time - *startTime_)));
	}
	
	void Factory::startCycle(std::chrono::seconds time) {
		if (launchTime_) {
			if (*launchTime_ + *cycleTime() < planet().lastUpdate()) {
				if (time != planet().lastUpdate())
					return;
			}
			else if (time != *launchTime_)
				return;
		}
		if (launchTime_->count() < 0) {
			launchTime_ = std::nullopt;
			auto product = *output();
			productionCycle_ = new ProductionCycle{time, *cycleTime(), product, product};
		}
		else {
			launchTime_ = std::nullopt;
			auto required = schematic_->inputs();
			auto available = commodities();
			
			auto equal = required.size() == available.size() && std::equal(required.begin(), required.end(), available.begin(), [](const auto& a, const auto& b) {
				return a.first->typeID == b.metaInfo().typeID && a.second == b.quantity();
			});
			
			if (equal) {
				auto product = *output();
				productionCycle_ = new ProductionCycle{time, *cycleTime(), product, product};
				commodities_.clear();
//				for (const auto& i: inputs_)
//					i.from->update(time);
			}
		}
	}

}
