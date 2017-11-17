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

#include "AttributeID.hpp"
#include "CategoryID.hpp"
#include "GroupID.hpp"
#include "TypeID.hpp"
#include "EffectID.hpp"

namespace dgmpp2 {
	using Float = double;
	using TypeID = dgmpp::TypeID;
	using GroupID = dgmpp::GroupID;
	using CategoryID = dgmpp::CategoryID;
	using AttributeID = dgmpp::AttributeID;
	using EffectID = dgmpp::EffectID;
	using ModifierID = int;
	using SchematicID = int;
	using GigaJoule = Float;
	using Percent = Float;
	
	namespace config {
		const Percent capacitorPeakRecharge = 0.5; //sqrt(0.25)
		const Percent shieldPeakRecharge = 0.5; //sqrt(0.25)
		const std::chrono::milliseconds capacitorSimulationMaxTime = std::chrono::hours(6);
	}

	template <typename... Args>
	struct KeyComparator {
		using Key = std::tuple<Args...>;
		
		bool operator()(const Key& lhs, const Key& rhs) const {
			return lhs < rhs;
		}
		
		template <typename... Args2, size_t... Is>
		std::tuple<Args2...> get(const Key& lhs, std::index_sequence<Is...>) const {
			return std::make_tuple(std::get<Is>(lhs)...);
		}
		
		template <typename... Args2>
		bool operator()(const Key& lhs, const std::tuple<Args2...>& rhs) const {
			return get<Args2...>(lhs, std::index_sequence_for<Args2...>{}) < rhs;
		}
		
		template <typename... Args2>
		bool operator()(const std::tuple<Args2...>& lhs, const Key& rhs) const {
			return lhs < get<Args2...>(rhs, std::index_sequence_for<Args2...>{});
		}
		
		typedef void is_transparent;
	};
	
	template <typename... Args>
	using TuplesSet = std::set<std::tuple<Args...>, KeyComparator<Args...>>;
	
	template<typename C, typename K> static std::pair<typename C::iterator, typename C::iterator> equal_range (const C& c, const K& k) {
		return std::make_pair(c.lower_bound(k), c.upper_bound(k));
	}

	template <typename T> struct optional {
		optional(T* ptr) : value_(ptr) {}
		optional(const T& value) : value_(new T(value)) {}
		optional(optional&& other) = default;
		optional(const optional& other) = delete;
		optional& operator=(optional&& other) = default;
		optional& operator=(const optional& other) = delete;
		
		optional& operator=(const T& value) {
			value_ = std::unique_ptr<T>(new T(value));
			return *this;
		}
		
		optional& operator=(std::nullptr_t) {
			value_ = nullptr;
			return *this;
		}
		
		operator bool() const {return value_ != nullptr;}
		
		T& value() {
			if (value_ == nullptr) {
				throw std::runtime_error("Dereferencing empty optional");
			}
			return *value_;
		}
		
		T& operator*() {
			return value();
		}
		
		T& operator->() {
			return value();
		}
		
		const T& value() const {
			if (value_ == nullptr) {
				throw std::runtime_error("Dereferencing empty optional");
			}
			return *value_;
		}
		
		const T& operator*() const {
			return value();
		}
		
		const T& operator->() const {
			return value();
		}
		
		
	private:
		std::unique_ptr<T> value_;
	};
	
	static auto nullopt = nullptr;
	
	template <typename T> optional<T> make_optional(T&& t) {
		return optional<T>(std::forward<T>(t));
	}
	
	template <typename T> class ref {
	public:
		constexpr ref(T& ref) : ref_(ref) {}
		
		constexpr operator T&() const noexcept {
			return ref_;
		}
		
		constexpr T& get() const noexcept {
			return ref_;
		}
	private:
		T& ref_;
	};
	
	template <typename Iter> class slice {
	public:
		
		template <typename I>
		slice(I&& from, I&& to) : from_(std::forward<I>(from)), to_(std::forward<I>(to)) {}
		
		Iter begin() {
			return from_;
		}
		Iter end() {
			return to_;
		}
		
		size_t size() const {
			return std::distance(from_, to_);
		}
		
	private:
		Iter from_;
		Iter to_;
	};
	
	template <typename Iter> slice<Iter> make_slice(Iter&& from, Iter&& to) {
		return slice<Iter>(std::forward<Iter>(from), std::forward<Iter>(to));
	}

	template<typename Rep, typename Period = std::chrono::seconds>
	class rate {
	public:
		using rep = Rep;
		using period = Period;
		
		rate() {};
		constexpr explicit rate(const Rep& value) : rep_(value) {}
		
		template<typename Period2>
		constexpr operator rate<Rep, Period2> () {
			using r = std::ratio_divide<typename Period::period::ratio, typename Period2::period::ratio>;
			return rate<Rep, Period2>{rep_ * r::den / r::num};
		};
		
		Rep count() const {return rep_;}
		
		auto operator+ (const rate<Rep, Period>& other) const {
			return rate<Rep, Period>(rep_ + other.rep_);
		}
		
		auto operator- (const rate<Rep, Period>& other) const {
			return rate<Rep, Period>(rep_ + other.rep_);
		}
		
		auto operator* (const rate<Rep, Period>& other) const {
			return rate<Rep, Period>(rep_ * other.rep_);
		}

		template<typename Period2>
		Rep operator* (const Period2& p) const {
			return rep_ * std::chrono::duration_cast<Period>(p).count();
		}

		auto operator/ (const rate<Rep, Period>& other) const {
			return rate<Rep, Period>(rep_ / other.rep_);
		}
		
		rate<Rep, Period>& operator+= (const rate<Rep, Period>& other) {
			rep_ += other.rep_;
			return *this;
		}
		
		rate<Rep, Period>& operator-= (const rate<Rep, Period>& other) {
			rep_ -= other.rep_;
			return *this;
		}
		
		rate<Rep, Period>& operator*= (const rate<Rep, Period>& other) {
			rep_ *= other.rep_;
			return *this;
		}
		
		rate<Rep, Period>& operator/= (const rate<Rep, Period>& other) {
			rep_ /= other.rep_;
			return *this;
		}
		
	private:
		Rep rep_ = 0;
	};
	
	template<typename Rep, typename Period>
	auto make_rate(const Rep& value, const Period& period) {
		auto c = period.count();
		return rate<Rep, Period> (c > 0 ? value / c : 0);
	}
};
