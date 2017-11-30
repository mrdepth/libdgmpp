//
//  Commodity.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 28.11.2017.
//

#pragma once
#include "Type.hpp"
#include "Errors.hpp"

namespace dgmpp2 {
	class Commodity {
	public:
		Commodity(TypeID typeID, size_t quantity = 0);
		Commodity(const MetaInfo::Commodity& metaInfo, size_t quantity = 0)
		: metaInfo_(metaInfo), quantity_(quantity) {}

		const MetaInfo::Commodity& metaInfo() const noexcept { return metaInfo_; }
		size_t quantity() const noexcept { return quantity_; }
		CubicMeter volume() const noexcept { return metaInfo_.volume * quantity_; }
		bool empty() const { return quantity_ == 0; }

		Commodity operator+ (size_t value) const noexcept {
			auto other = Commodity(*this);
			other.quantity_ += value;
			return other;
		}
		
		Commodity operator- (size_t value) const {
			if (quantity_ < value)
				throw NotEnoughCommodities(quantity_ - value);
			auto other = Commodity(*this);
			other.quantity_ -= value;
			return other;
		}

		Commodity& operator+= (size_t value) noexcept {
			quantity_ += value;
			return *this;
		}
		
		Commodity& operator-= (size_t value) {
			if (quantity_ < value)
				throw NotEnoughCommodities(quantity_ - value);
			quantity_ -= value;
			return *this;
		}
		
		Commodity& operator= (size_t value) noexcept {
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
                throw NotEnoughCommodities(quantity_ - other.quantity_);
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
				throw NotEnoughCommodities(quantity_ - other.quantity_);
			quantity_ -= other.quantity_;
			return *this;
		}

		bool operator== (const Commodity& other) const noexcept {
			return metaInfo_.typeID == other.metaInfo_.typeID && quantity_ == other.quantity_;
		}
		
		bool operator!= (const Commodity& other) const noexcept {
			return !operator==(other);
		}

	private:
		friend class std::hash<Commodity>;
		const MetaInfo::Commodity& metaInfo_;
		size_t quantity_;
	};
}

namespace std {
	template<>
	struct hash<dgmpp2::Commodity> {
		typedef dgmpp2::Commodity argument_type;
		typedef size_t result_type;
		
		constexpr result_type operator()(const argument_type& value) const noexcept {
			return dgmpp2::hashValue(value.quantity_, value.metaInfo_.typeID);
		}
		
	};
};

