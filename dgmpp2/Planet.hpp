//
//  Planet.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Facility.hpp"
#include "Route.hpp"

namespace dgmpp2 {
	class Planet {
	public:
		Facility* add(TypeID typeID, Facility::Identifier identifier = 0);
		void remove(Facility* facility);
		std::vector<Facility*> facilities() const;
		Facility* operator[] (Facility::Identifier key) const;
		
		void add(const Route& route);
		void remove(const Route& route);
		
		
		std::chrono::seconds lastUpdate() const { return lastUpdate_; }
		void lastUpdate(std::chrono::seconds lastUpdate) { lastUpdate_ = lastUpdate; }
		
		std::chrono::seconds run();
		
	private:
		
		struct FacilityCompare {
			template <typename A, typename B>
			bool operator() (const A& a, const B& b) const noexcept {
				return std::make_pair(a->priority(), remove_unique_ptr(a)) < std::make_pair(b->priority(), remove_unique_ptr(b));
			}
			
			typedef void is_transparent;
		};
		
		std::set<std::unique_ptr<Facility>, FacilityCompare> facilities_;
		std::chrono::seconds lastUpdate_ = std::chrono::seconds::zero();
		std::chrono::seconds timestamp_ = std::chrono::seconds::zero();
		
		std::optional<std::chrono::seconds> nextCycleTime(const std::vector<Facility*>& facilities);
//		void runCycle(std::chrono::seconds cycleTime);

	};
}
