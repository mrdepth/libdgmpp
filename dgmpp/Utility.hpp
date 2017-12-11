//
//  Utility.hpp
//  dgmpp
//
//  Created by Artem Shimanski on 15.11.2017.
//

#pragma once
#include <utility>
#include <memory>
#include <string>
#include <set>
#include <map>
#include <tuple>
#include <list>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include <experimental/optional>

#include "AttributeID.hpp"
#include "CategoryID.hpp"
#include "GroupID.hpp"
#include "TypeID.hpp"
#include "EffectID.hpp"
#include "WarfareBuffID.hpp"
#include "Rate.hpp"
#include "SchematicID.hpp"

namespace std {
	template<typename T>
	using optional = std::experimental::optional<T>;
	constexpr auto nullopt = std::experimental::nullopt;
}

namespace dgmpp {
	using Float = double;
	using TypeID = dgmpp::TypeID;
	using GroupID = dgmpp::GroupID;
	using CategoryID = dgmpp::CategoryID;
	using AttributeID = dgmpp::AttributeID;
	using EffectID = dgmpp::EffectID;
	using WarfareBuffID = dgmpp::WarfareBuffID;
	using SchematicID = dgmpp::SchematicID;
	using ModifierID = int;
	using GigaJoule = Float;
	using Teraflops = Float;
	using MegaWatts = Float;
	using CalibrationPoints = Float;
//	using MeterPerSecond = Float;
	using CubicMeter = Float;
	using Meter = Float;
	using Millimeter = Float;
	using MegabitsPerSecond = Float;
	using Kilogram = Float;
	using Points = Float;
	using HP = Float;
	using Radians = Float;
	using AstronomicalUnit = Float;
	using Percent = Float;
	using Multiplier = Float;
	using GigaJoulePerSecond	= rate<GigaJoule, std::chrono::seconds>;
	using CubicMeterPerSecond	= rate<CubicMeter, std::chrono::seconds>;
	using RadiansPerSecond		= rate<Radians, std::chrono::seconds>;
	using MetersPerSecond		= rate<Meter, std::chrono::seconds>;
	using AstronomicalUnitsPerSecond = rate<Meter, std::chrono::seconds>;
	
	namespace config {
		const Percent capacitorPeakRecharge = 0.5; //sqrt(0.25)
		const Percent shieldPeakRecharge = 0.5; //sqrt(0.25)
		const std::chrono::milliseconds capacitorSimulationMaxTime = std::chrono::hours(6);
	}
	
	enum class RaceID {
		none = 0,
		caldari = 1,
		minmatar = 2,
		amarr = 4,
		gallente = 8
	};

	template <typename T>
	T* remove_unique_ptr(const std::unique_ptr<T>& ptr) noexcept {
		return ptr.get();
	}
	
	template<typename T>
	T remove_unique_ptr(const T& t) noexcept {
		return t;
	}
	
	template <typename... Args>
	struct KeyComparator {
		using Key = std::tuple<Args...>;
		
		bool operator()(const Key& lhs, const Key& rhs) const noexcept {
			return lhs < rhs;
		}
		
		template <typename... Args2, size_t... Is>
		std::tuple<Args2...> get(const Key& lhs, std::index_sequence<Is...>) const noexcept {
			return std::make_tuple(remove_unique_ptr(std::get<Is>(lhs))...);
		}
		
		template <typename... Args2>
		bool operator()(const Key& lhs, const std::tuple<Args2...>& rhs) const noexcept {
			return get<Args2...>(lhs, std::index_sequence_for<Args2...>{}) < rhs;
		}
		
		template <typename... Args2>
		bool operator()(const std::tuple<Args2...>& lhs, const Key& rhs) const noexcept {
			return lhs < get<Args2...>(rhs, std::index_sequence_for<Args2...>{});
		}
		
		typedef void is_transparent;
	};
	
	template <typename... Args>
	using TuplesSet = std::set<std::tuple<Args...>, KeyComparator<Args...>>;
	
	template<typename C, typename K> static std::pair<typename C::iterator, typename C::iterator> equal_range (const C& c, const K& k) noexcept {
		return std::make_pair(c.lower_bound(k), c.upper_bound(k));
	}
	
	template <typename Iter> class slice {
	public:
		
		template <typename I>
		slice(I&& from, I&& to) : from_(std::forward<I>(from)), to_(std::forward<I>(to)) {}
		
		template <typename I>
		slice(std::pair<I, I>&& p) : from_(std::forward<I>(p.first)), to_(std::forward<I>(p.second)) {}
		
		Iter begin() const noexcept {
			return from_;
		}
		Iter end() const noexcept {
			return to_;
		}
		
		size_t size() const noexcept {
			return std::distance(from_, to_);
		}
		
	private:
		Iter from_;
		Iter to_;
	};
	
	template <typename Iter> slice<Iter> make_slice(Iter&& from, Iter&& to) noexcept {
		return slice<Iter>(std::forward<Iter>(from), std::forward<Iter>(to));
	}

	
	struct Resistances {
		struct Layer {
			union {
				struct {
					Percent em;
					Percent thermal;
					Percent kinetic;
					Percent explosive;
				};
				Percent resistances[4];
			};
		};

		union {
			struct {
				Layer shield, armor, hull;
			};
			Layer layers[3];
		};
	};
	
	struct HostileTarget {
		rate<Radians, std::chrono::seconds> angularVelocity = rate<Radians, std::chrono::seconds>(0);
		rate<Meter, std::chrono::seconds> velocity = rate<Meter, std::chrono::seconds>(0);
		Meter signature = 0;
		Meter range = 0;
		static HostileTarget Default() noexcept { return HostileTarget(); }
//		const static HostileTarget defaultTarget;
	};
	
	template<typename T, typename... Tail>
	struct HashCombine {
		constexpr static std::size_t value(const T& t, const Tail&... args) noexcept {
			auto seed = HashCombine<Tail...>::value(args...);
			return seed ^ (std::hash<T>()(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
		}
	};
	
	
	template<typename T>
	struct HashCombine<T> {
		constexpr static std::size_t value(const T& t) noexcept {
			return (std::hash<T>()(t) + 0x9e3779b9);
		}
	};
	
	template<typename... Args>
	constexpr std::size_t hashValue(const Args&... args) noexcept {
		return HashCombine<Args...>::value(args...);
	}
	
	template <typename T1, typename T2, typename = std::enable_if_t<std::is_scalar_v<T1> && std::is_scalar_v<T2>>>
	constexpr Percent percentage(T1 value, T2 sum) noexcept {
		return sum > 0 ? static_cast<Percent>(value) / static_cast<Percent>(sum) : 0;
	}

	template <typename Rep, typename Rate>
	constexpr Percent percentage(std::chrono::duration<Rep, Rate> value, std::chrono::duration<Rep, Rate> sum) noexcept {
		return sum.count() > 0 ? static_cast<Percent>(value.count()) / static_cast<Percent>(sum.count()) : 0;
	}

//	template <typename T>
//	constexpr T sum(T first) noexcept {
//		return first;
//	}
//
//	template <typename T, typename... Tail>
//	constexpr T sum(T first, Tail... args) noexcept {
//		return first + sum(args...);
//	}
//
//	template<typename T, typename... Tail>
//	constexpr Percent percentage(T first, Tail... args) noexcept {
//		auto s = static_cast<Percent> (sum(first, args...));
//		return s > 0 ? first / s : 0;
//	}

};

namespace std {
	template<typename... Args>
	struct hash<tuple<Args...>> {
		typedef tuple<Args...> argument_type;
		typedef size_t result_type;
		
		template<size_t... I>
		constexpr result_type hashValue(const argument_type& value, std::index_sequence<I...>) const noexcept {
			return dgmpp::hashValue(std::get<I>(value)...);
//			return dgmpp::hash_combine<Args...>::value(std::get<I>(value)...);
		}
		
		constexpr result_type operator()(const argument_type& value) const noexcept {
			return hashValue(value, std::make_index_sequence<sizeof...(Args)>{});
		}
		
	};
};

