#pragma once
#include "types.h"

namespace dgmpp {
	class Commodity {
	public:
		typedef std::runtime_error NotEnoughCommodities;
		typedef std::runtime_error DifferentCommoditiesTypeIDs;
		static Commodity InvalidCommodity();
		Commodity(std::shared_ptr<Engine> const& engine, TypeID typeID, uint32_t quantity = 0);
		Commodity(const Commodity& other, uint32_t quantity);
		Commodity(const Commodity& other);
		void add(uint32_t quantity);
		void extract(uint32_t quantity);
		void setQuantity(uint32_t quantity) {quantity_ = quantity;};
		
		TypeID getTypeID() const {return typeID_;};
		const std::string& getTypeName() const  {return *typeName_;};
		uint32_t getQuantity() const {return quantity_;};
		double getItemVolume() const {return volume_;};
		double getVolume() const {return volume_ * quantity_;};
		CommodityTier getTier() const {return tier_;};
		
		friend std::ostream& operator<<(std::ostream& os, const Commodity& commodity);
		
		bool operator==(const Commodity& other) const;
		bool operator!=(const Commodity& other) const;
		
		Commodity operator+(const Commodity& other);
		Commodity operator-(const Commodity& other);
	private:
		TypeID typeID_;
		std::shared_ptr<std::string> typeName_;
		uint32_t quantity_;
		double volume_;
		CommodityTier tier_;
	};
}