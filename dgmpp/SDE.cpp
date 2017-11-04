//
//  SDE.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 01.11.2017.
//

#include "SDE.hpp"
#include "Types.hpp"

namespace dgmpp2 {
	namespace SDE {
		template <typename Key, typename Value> Key getKey(const Value& value);
		
		template <typename Key, typename Value, std::size_t N, const Value (&array)[N]>
		const Value& get(Key key) {
			auto first = array;
			auto last = array + N;
			
			first = std::lower_bound(first, last, key, [=](const auto& a, const auto& b) -> bool {
				return getKey<Key, Value>(a) < b;
			});
			
			if (first != last && getKey<Key, Value>(*first) == key) {
				return *first;
			}
			else {
				throw NotFound<Key>(key);
			}
			
			/*std::size_t r = N;
			std::size_t l = 0;
			int i = static_cast<int>(key);
			int n = 0;
			while (l < r) {
				n++;
				const auto c = (l + r) / 2;
				const auto& v = array[c];
				const auto j = getKey(v);
				if (i < j)
					r = c;
				else if (i > j)
					l = c + 1;
				else
					return v;
			}
			if (i == getKey(array[r])) {
				return array[r];
			}
			else {
				throw NotFound<Key>(key);
			}*/
		}
		
		template<> AttributeID getKey<AttributeID, Attribute::MetaInfo>(const Attribute::MetaInfo& value) {
			return value.attributeID;
		}

		template<> TypeID getKey<TypeID, Type::MetaInfo>(const Type::MetaInfo& value) {
			return value.typeID;
		}

		const Attribute::MetaInfo& get(AttributeID attributeID) {
			return get<AttributeID, Attribute::MetaInfo, sizeof(attributes) / sizeof(decltype(*attributes)), attributes>(attributeID);
		}
		
		const Type::MetaInfo& get(TypeID typeID) {
			return get<TypeID, Type::MetaInfo, sizeof(types) / sizeof(decltype(*types)), types>(typeID);
		}
	}
}
