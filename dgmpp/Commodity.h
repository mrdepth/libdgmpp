#pragma once
#include "types.h"

namespace dgmpp {
	class Commodity {
	public:
		typedef std::runtime_error NotEnoughCommodities;

		Commodity(std::shared_ptr<Engine> const& engine, TypeID typeID, int32_t quantity = 0);
		Commodity(const Commodity& other, int32_t quantity = -1);
		void add(int32_t quantity);
		void extract(int32_t quantity);
		void setQuantity(int32_t quantity) {quantity_ = quantity;};
		
		TypeID getTypeID() const {return typeID_;};
		const std::string& getTypeName() const  {return *typeName_;};
		int32_t getQuantity() const {return quantity_;};
		double getItemVolume() const {return volume_;};
		double getVolume() const {return volume_ * quantity_;};
		
		friend std::ostream& operator<<(std::ostream& os, const Commodity& commodity);
	private:
		TypeID typeID_;
		std::shared_ptr<std::string> typeName_;
		int32_t quantity_;
		double volume_;
	};
}