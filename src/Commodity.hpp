//
//  Commodity.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Type.hpp"
#include "Errors.hpp"

namespace dgmpp {
	class Commodity {
	public:
		Commodity(TypeID typeID, std::size_t quantity = 0);
		Commodity(const MetaInfo::Commodity& metaInfo, std::size_t quantity = 0)
		: metaInfo_(metaInfo), quantity_(quantity) {}

		const MetaInfo::Commodity& metaInfo() const noexcept { return metaInfo_; }
		std::size_t quantity() const noexcept { return quantity_; }
		CubicMeter volume() const noexcept { return metaInfo_.volume * quantity_; }
		bool empty() const { return quantity_ == 0; }

		Commodity operator+ (std::size_t value) const noexcept {
			auto other = Commodity(*this);
			other.quantity_ += value;
			return other;
		}
		
		Commodity operator- (std::size_t value) const {
			if (quantity_ < value)
				throw NotEnoughCommodities(value - quantity_);
			auto other = Commodity(*this);
			other.quantity_ -= value;
			return other;
		}

		Commodity& operator+= (std::size_t value) noexcept {
			quantity_ += value;
			return *this;
		}
		
		Commodity& operator-= (std::size_t value) {
			if (quantity_ < value)
				throw NotEnoughCommodities(value - quantity_);
			quantity_ -= value;
			return *this;
		}
		
		Commodity& operator= (std::size_t value) noexcept {
			quantity_ = value;
			return *this;
		}

        Commodity& operator= (const Commodity& other) noexcept {
            assert(metaInfo_.typeID == other.metaInfo_.typeID);
            quantity_ = other.quantity_;
            return *this;
        }


        Commodity operator+ (const Commodity& other) const noexcept {
            assert(metaInfo_.typeID == other.metaInfo_.typeID);
            auto result = Commodity(*this);
            result.quantity_ += other.quantity_;
            return result;
        }

        Commodity operator- (const Commodity& other) const {
            assert(metaInfo_.typeID == other.metaInfo_.typeID);

            if (quantity_ < other.quantity_)
                throw NotEnoughCommodities(other.quantity_ - quantity_);
            auto result = Commodity(*this);
            result.quantity_ -= other.quantity_;
            return result;
        }

		Commodity& operator+= (const Commodity& other) noexcept {
			assert(metaInfo_.typeID == other.metaInfo_.typeID);
			quantity_ += other.quantity_;
			return *this;
		}
		
		Commodity& operator-= (const Commodity& other) {
			assert(metaInfo_.typeID == other.metaInfo_.typeID);
			
			if (quantity_ < other.quantity_)
				throw NotEnoughCommodities(other.quantity_ - quantity_);
			quantity_ -= other.quantity_;
			return *this;
		}

		bool operator== (const Commodity& other) const noexcept {
			return metaInfo_.typeID == other.metaInfo_.typeID && quantity_ == other.quantity_;
		}
		
		bool operator!= (const Commodity& other) const noexcept {
			return !operator==(other);
		}
		
		bool operator< (const Commodity& other) const noexcept {
			assert(metaInfo_.typeID == other.metaInfo_.typeID);
			return quantity_ < other.quantity_;
		}

		bool operator> (const Commodity& other) const noexcept {
			assert(metaInfo_.typeID == other.metaInfo_.typeID);
			return quantity_ > other.quantity_;
		}

		bool operator<= (const Commodity& other) const noexcept {
			assert(metaInfo_.typeID == other.metaInfo_.typeID);
			return quantity_ <= other.quantity_;
		}
				
		bool operator>= (const Commodity& other) const noexcept {
			assert(metaInfo_.typeID == other.metaInfo_.typeID);
			return quantity_ >= other.quantity_;
		}


	private:
		friend class std::hash<Commodity>;
		const MetaInfo::Commodity& metaInfo_;
		std::size_t quantity_;
	};
}

namespace std {
	template<>
	struct hash<dgmpp::Commodity> {
		typedef dgmpp::Commodity argument_type;
		typedef size_t result_type;
		
		constexpr result_type operator()(const argument_type& value) const noexcept {
			return dgmpp::hashValue(value.quantity_, value.metaInfo_.typeID);
		}
		
	};
};

