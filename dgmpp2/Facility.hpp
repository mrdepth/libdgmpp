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

namespace dgmpp2 {
	class Planet;
	
	class Facility {
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
		
		virtual bool configured() const { return true; };

	protected:
		Facility(const MetaInfo::Facility& metaInfo, Planet& planet, Identifier identifier)
		: metaInfo_(metaInfo), planet_(planet), identifier_(identifier) {}

		virtual std::optional<std::chrono::seconds> nextUpdateTime() const { return std::nullopt; }
		virtual int priority() const { return 0; }
        virtual void update (std::chrono::seconds time);

		std::unordered_set<Route> inputs_;
		std::unordered_set<Route> outputs_;
		std::map<TypeID, Commodity> commodities_;
		std::map<TypeID, Commodity> income_;
		
	private:
		friend class Planet;
		friend class Factory;
		friend class Route;
		const MetaInfo::Facility& metaInfo_;
		Planet& planet_;
		Identifier identifier_;
	};

}
