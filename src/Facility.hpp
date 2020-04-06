//
//  Facility.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "MetaInfo.hpp"
#include "Route.hpp"
#include "ProductionState.hpp"
#include <unordered_set>

namespace dgmpp {
	class Planet;
	
	class Facility: public std::enable_shared_from_this<Facility> {
	public:
		typedef int64_t Identifier;
		virtual ~Facility() = default;
		
		const MetaInfo::Facility& metaInfo() const noexcept { return metaInfo_; }
		Planet& planet() const noexcept { return planet_; }
		Identifier identifier() const noexcept { return identifier_; }
		
		CubicMeter capacity() const noexcept { return metaInfo_.capacity; }
		CubicMeter freeVolume() const noexcept { return capacity() - usedVolume(); }
		CubicMeter usedVolume() const noexcept;
		virtual Commodity free(const Commodity& key) noexcept;
		
        void add (const Commodity& commodity);
        void extract (const Commodity& commodity);
        std::vector<Commodity> commodities();
		
//		std::optional<Commodity> commodity	(TypeID typeID) const;
		Commodity& operator[] (TypeID typeID);
		Commodity& operator[] (const Commodity& key);
		Commodity income (TypeID typeID) const;
		
		const std::string& name() const noexcept { return name_; }
		const std::unordered_set<Route>& inputs() const noexcept { return inputs_; }
		const std::unordered_set<Route>& outputs() const noexcept { return inputs_; }
		
		virtual bool configured() const { return true; };

	protected:
		Facility(const MetaInfo::Facility& metaInfo, Planet& planet, Identifier identifier);

		virtual std::optional<std::chrono::seconds> nextUpdateTime_() const noexcept { return std::nullopt; }
		virtual int priority_() const noexcept { return 0; }
        virtual void update_ (std::chrono::seconds time);

		std::unordered_set<Route> inputs_;
		std::unordered_set<Route> outputs_;
		std::map<TypeID, Commodity> commodities_;
		std::map<TypeID, Commodity> income_;
		
	private:
		friend class Planet;
		friend class Factory;
		friend struct Route;
		const MetaInfo::Facility& metaInfo_;
		Planet& planet_;
		Identifier identifier_;
		std::string name_;
	};

}
