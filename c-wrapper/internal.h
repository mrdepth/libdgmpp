//
//  internal.h
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#pragma once

#include "dgmpp.hpp"
#include "type.h"
#include "attribute.h"
#include <type_traits>
#include <functional>

using namespace dgmpp;

struct unique_ptr_wrapper_base {
	virtual ~unique_ptr_wrapper_base() {}
};

template <typename T>
struct unique_ptr_wrapper: public unique_ptr_wrapper_base {
	std::unique_ptr<T> ptr;
	unique_ptr_wrapper(std::unique_ptr<T>&& ptr): ptr(std::move(ptr)) {}
	virtual ~unique_ptr_wrapper() {}
};

extern std::map<dgmpp_handle, std::unique_ptr<unique_ptr_wrapper_base>> unique_pointers;

template <typename T>
T* add_unique_ptr_wrapper(std::unique_ptr<T>&& ptr) {
	auto key = ptr.get();
	unique_pointers.emplace(key, std::unique_ptr<unique_ptr_wrapper<T>>{new unique_ptr_wrapper<T>{std::move(ptr)}});
	return key;
}

template <typename T>
std::unique_ptr<T> get_unique_ptr(dgmpp_handle h) {
	auto i = unique_pointers.find(h);
	if (i == unique_pointers.end())
		return nullptr;
	return std::move(dynamic_cast<unique_ptr_wrapper<T>*>(i->second.get())->ptr);
}


enum class dgmpp_handle_tag: char {
	invalid = -1,
	ptr,
	unique_ptr_gang,
	unique_ptr_character,
	unique_ptr_booster,
	unique_ptr_implant,
	unique_ptr_ship,
	unique_ptr_structure,
	unique_ptr_module,
	unique_ptr_drone,
	unique_ptr_charge,
	unique_ptr_area,
	unique_ptr_planet,
	unique_ptr_array
};
	
struct dgmpp_array_impl_base {
	size_t size;
	dgmpp_array_impl_base (size_t size): size(size) {}
	virtual const void* ptr() const = 0;
};


/*struct dgmpp_handle_impl: public dgmpp_handle {
	void destroy() {
		switch (static_cast<dgmpp_handle_tag>(tag)) {
			case dgmpp_handle_tag::unique_ptr_gang:
				delete reinterpret_cast<std::unique_ptr<Gang>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_character:
				delete reinterpret_cast<std::unique_ptr<Character>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_booster:
				delete reinterpret_cast<std::unique_ptr<Booster>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_implant:
				delete reinterpret_cast<std::unique_ptr<Implant>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_ship:
				delete reinterpret_cast<std::unique_ptr<Ship>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_structure:
				delete reinterpret_cast<std::unique_ptr<Structure>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_module:
				delete reinterpret_cast<std::unique_ptr<Module>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_drone:
				delete reinterpret_cast<std::unique_ptr<Drone>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_charge:
				delete reinterpret_cast<std::unique_ptr<Charge>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_area:
				delete reinterpret_cast<std::unique_ptr<Area>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_planet:
				delete reinterpret_cast<std::unique_ptr<Planet>*>(handle);
				break;
			case dgmpp_handle_tag::unique_ptr_array:
				delete reinterpret_cast<std::unique_ptr<dgmpp_array_impl_base>*>(handle);
				break;
			default:
				break;
		}
		tag = static_cast<char>(dgmpp_handle_tag::invalid);
	}
	
	template<typename T> T* get() const {
		if (static_cast<dgmpp_handle_tag>(tag) == dgmpp_handle_tag::ptr)
			return reinterpret_cast<T*>(handle);
		else
			return reinterpret_cast<std::unique_ptr<T>*>(handle)->get();
	};
	
	template<typename T> std::unique_ptr<T>&& move() {
		return std::move(*reinterpret_cast<std::unique_ptr<T>*>(handle));
	}

	
	template<typename T> operator T* () const {
		return get<T>();
	};
	
	template<typename T> dgmpp_handle_impl(std::unique_ptr<T>&& ptr, dgmpp_handle_tag tag) : dgmpp_handle{static_cast<char>(tag), nullptr} {
		*reinterpret_cast<std::unique_ptr<T>**>(&handle) = new std::unique_ptr<T>(std::move(ptr));
	}
	
	template<typename T> dgmpp_handle_impl(T* ptr) : dgmpp_handle{static_cast<char>(dgmpp_handle_tag::ptr), ptr} {}
	
	template<typename T>
	void reset(T ptr) {
		switch (static_cast<dgmpp_handle_tag>(tag)) {
			case dgmpp_handle_tag::invalid:
			case dgmpp_handle_tag::ptr:
				break;
			default:
				destroy();
				break;
		}
		handle = reinterpret_cast<void*>(ptr);
		tag = static_cast<char>(dgmpp_handle_tag::ptr);
	}

	void reset(std::nullptr_t) {
		switch (static_cast<dgmpp_handle_tag>(tag)) {
			case dgmpp_handle_tag::invalid:
			case dgmpp_handle_tag::ptr:
				break;
			default:
				destroy();
				break;
		}
		handle = nullptr;
		tag = static_cast<char>(dgmpp_handle_tag::ptr);
	}

};*/


template<typename T> dgmpp_handle dgmpp_make_handle(T* ptr) {
	return dgmpp_handle{dgmpp_handle_tag::ptr, ptr};
}

/*template<typename T>
T& dgmpp_cast(dgmpp_handle handle) {
	return *reinterpret_cast<dgmpp_handle_impl*>(&handle)->get<T>();
}

template<typename T>
std::unique_ptr<T>&& dgmpp_move(dgmpp_handle& handle) {
	return reinterpret_cast<dgmpp_handle_impl*>(&handle)->move<T>();
}

template<typename T>
void dgmpp_reset(dgmpp_handle& handle, T value) {
	reinterpret_cast<dgmpp_handle_impl*>(&handle)->reset<T>(value);
}

template<>
void dgmpp_reset<std::nullptr_t>(dgmpp_handle& handle, std::nullptr_t) {
	reinterpret_cast<dgmpp_handle_impl*>(&handle)->reset<void*>(nullptr);
}*/

template <typename T, typename = void>
struct dgmpp_array_impl: public dgmpp_array_impl_base {
	std::vector<T> values;
	
	template <typename C, typename Constructor = T>
	dgmpp_array_impl(const C& c): dgmpp_array_impl_base (std::size(c)) {
		values.reserve(size);
		std::transform(c.begin(), c.end(), std::back_inserter(values), [](const auto& i) {
			return Constructor(remove_unique_ptr(i));
		});
	}
	
	virtual const void* ptr() const override {
		return reinterpret_cast<const void*>(&values[0]);
	}
};


template<typename T, typename C>
dgmpp_array dgmpp_make_array(const C& c) {
	return add_unique_ptr_wrapper(std::unique_ptr<dgmpp_array_impl<T>>(new dgmpp_array_impl<T>(c)));
}

template<typename Rep, typename Ratio>
inline dgmpp_seconds  dgmpp_make_seconds(const std::chrono::duration<Rep, Ratio>& v) {
	return std::chrono::duration_cast<std::chrono::seconds>(v).count();
}

inline dgmpp_damage_vector dgmpp_damage_vector_make(const DamageVector& v) {
	return {v.em, v.thermal, v.kinetic, v.explosive};
}

inline DamageVector damage_vector_make(const dgmpp_damage_vector& v) {
	return {v.em, v.thermal, v.kinetic, v.explosive};
}

inline dgmpp_damage_per_second dgmpp_damage_per_second_make(const DamagePerSecond& v) {
	return dgmpp_damage_vector_make(v * 1s);
}


inline dgmpp_hit_points dgmpp_hit_points_make(const HitPoints& v) {
	return {v.shield, v.armor, v.hull};
}

inline dgmpp_tank dgmpp_tank_make(const Tank& v) {
	return {v.passiveShield * 1s, v.shieldRepair * 1s, v.armorRepair * 1s, v.hullRepair * 1s};
}

inline dgmpp_resistances dgmpp_resistances_make(const Resistances& v) {
	return {
		v.shield.em, v.shield.thermal, v.shield.kinetic, v.shield.explosive,
		v.armor.em, v.armor.thermal, v.armor.kinetic, v.armor.explosive,
		v.hull.em, v.hull.thermal, v.hull.kinetic, v.hull.explosive};
}

inline HostileTarget hostile_target_make(const dgmpp_hostile_target& v) {
	return {make_rate(v.angular_velocity, 1s), make_rate(v.velocity, 1s), v.signature, v.range};
}

struct dgmpp_commodity_impl: public dgmpp_commodity {
	dgmpp_commodity_impl(const Commodity& c)
	: dgmpp_commodity{
		static_cast<dgmpp_type_id>(c.metaInfo().typeID),
		static_cast<DGMPP_COMMODITY_TIER>(c.metaInfo().tier),
		c.metaInfo().volume,
		c.quantity()} {}
};

struct dgmpp_production_cycle_impl: public dgmpp_production_cycle {
	dgmpp_production_cycle_impl(const ProductionCycle& c)
	: dgmpp_production_cycle{
		dgmpp_make_seconds(c.start),
		dgmpp_make_seconds(c.duration),
		dgmpp_commodity_impl(c.yield),
		dgmpp_commodity_impl(c.waste)} {}

	
	dgmpp_production_cycle_impl(const ProductionCycle* c)
	: dgmpp_production_cycle_impl(*c) {}
};


struct dgmpp_route_impl: public dgmpp_route {
	dgmpp_route_impl (const Route& route)
	: dgmpp_route{
		route.from,
		route.to,
		dgmpp_commodity_impl(route.commodity)} {}
};

