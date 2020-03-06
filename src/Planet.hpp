//
//  Planet.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Facility.hpp"
#include "Route.hpp"

namespace dgmpp {
	class Planet {
	public:
		std::shared_ptr<Facility> add(TypeID typeID, Facility::Identifier identifier = 0);
		void remove(Facility* facility);
		const std::list<std::shared_ptr<Facility>>& facilities() const;
		std::shared_ptr<Facility> operator[] (Facility::Identifier key) const;
		
		void add(const Route& route);
		void remove(const Route& route);
		
		
		std::chrono::seconds lastUpdate() const noexcept { return lastUpdate_; }
		void lastUpdate(std::chrono::seconds lastUpdate) noexcept { lastUpdate_ = lastUpdate; }
		
		std::chrono::seconds run();
		
	private:
		
		struct FacilityCompare {
			template <typename A, typename B>
			bool operator() (const A& a, const B& b) const noexcept {
				return std::make_pair(a->priority_(), remove_ptr(a)) < std::make_pair(b->priority_(), remove_ptr(b));
			}
			
			typedef void is_transparent;
		};
		
		std::list<std::shared_ptr<Facility>> facilities_;
		std::chrono::seconds lastUpdate_ = std::chrono::seconds::zero();
		std::chrono::seconds timestamp_ = std::chrono::seconds::zero();
		
		std::optional<std::chrono::seconds> nextCycleTime_ (const std::set<Facility*, FacilityCompare>& facilities) const noexcept;

	};
}
