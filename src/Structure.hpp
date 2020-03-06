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

		TypeID fuelBlockTypeID() { return fuelBlockTypeID_; }
		rate<Float, std::chrono::hours> fuelUse() { LOCK(this); return fuelUse_(); }
		
		std::shared_ptr<Area> area() const noexcept { LOCK(this); return area_(); }
		void area(const std::shared_ptr<Area>& area) { LOCK(this); return area_(area); }
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
