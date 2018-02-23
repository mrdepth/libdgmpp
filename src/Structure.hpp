//
//  Structure.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Ship.hpp"

namespace dgmpp {
	class Structure: public Ship {
	public:
		Structure(TypeID typeID) : Ship(typeID) { setEnabled_(true); }
		Structure(const Structure& other) : Ship(other) { setEnabled_(other.isEnabled_()); }

		static std::unique_ptr<Structure> Create (TypeID typeID) { return std::unique_ptr<Structure>(new Structure(typeID)); }
		static std::unique_ptr<Structure> Create (const Structure& other) { return std::unique_ptr<Structure>(new Structure(other)); }
		
		TypeID fuelBlockTypeID() { return fuelBlockTypeID_; }
		rate<Float, std::chrono::hours> fuelUse() { LOCK(this); return fuelUse_(); }
		
		Area* area() const noexcept { LOCK(this); return area_(); }
		Area* area(std::unique_ptr<Area>&& area) { LOCK(this); return area_(std::move(area)); }
		Area* area(TypeID typeID) { return area(Area::Create(typeID)); }
	protected:
		virtual Type* domain_ (MetaInfo::Modifier::Domain domain) noexcept override;
	private:
		
		
		const TypeID fuelBlockTypeID_ {[this]() {
			switch (raceID_) {
				case RaceID::caldari:
					return TypeID::nitrogenFuelBlock;
				case RaceID::minmatar:
					return TypeID::hydrogenFuelBlock;
				case RaceID::amarr:
					return TypeID::heliumFuelBlock;
				case RaceID::gallente:
					return TypeID::oxygenFuelBlock;
				default:
					return TypeID::none;
			}
		}()};
		
		rate<Float, std::chrono::hours> fuelUse_();
	};
}
