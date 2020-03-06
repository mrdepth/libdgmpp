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

struct dgmpp_handle_base {
    virtual ~dgmpp_handle_base() {}
private:
    virtual void* get_value() = 0;
};

template <typename Wrapped>
struct dgmpp_handle_impl: dgmpp_handle_base {
    Wrapped value;
    template <typename T>
    dgmpp_handle_impl(T&& v): value(std::forward<T>(v)) {};
    
    virtual void* get_value() override {
        return reinterpret_cast<void*>(&value);
    }
};

template <typename T>
dgmpp_handle new_handle(T&& value) {
    return reinterpret_cast<dgmpp_handle>(new dgmpp_handle_impl<T>{std::forward<T>(value)});
}

template <typename T, typename = void>
struct get {
    dgmpp_handle handle;
    get(dgmpp_handle h): handle(h) {}
    T& operator -> () {
        return operator*();
    }
    
    T& operator*() {
        auto baseHandle = reinterpret_cast<dgmpp_handle_base*>(handle);
        auto h = dynamic_cast<dgmpp_handle_impl<T>>(baseHandle);
        assert(h);
        return h->value;
    }
};

template<typename T>
struct get<std::shared_ptr<T>, std::enable_if_t<std::is_base_of_v<Type, T>>> {
    dgmpp_handle handle;
    get(dgmpp_handle h): handle(h) {}
    
    std::shared_ptr<T> operator -> () {
        return operator*();
    }
    
    std::shared_ptr<T> operator*() {
        auto baseHandle = reinterpret_cast<dgmpp_handle_base*>(handle);
        
        if (auto h = dynamic_cast<dgmpp_handle_impl<std::shared_ptr<Type>>*>(baseHandle))
            return std::dynamic_pointer_cast<T>(h->value);
        else
            return nullptr;
    }
};

/*template <typename T>
T* get(dgmpp_handle handle) {
    if (auto h = dynamic_cast<dgmpp_handle_impl<T>>(handle)) {
        return &h->value;
    }
    else {
        return nullptr;
    }
}


template <typename T, typename = std::enable_if_t<is_shared_ptr<T>::value>>
T* get(dgmpp_handle handle) {
    if (auto h = dynamic_cast<dgmpp_handle_impl<T>>(handle)) {
        return &h->value;
    }
    else {
        return nullptr;
    }
}*/


/*
struct shared_ptr_wrapper_base {
	virtual ~shared_ptr_wrapper_base() {}
};

template <typename T>
struct shared_ptr_wrapper: public shared_ptr_wrapper_base {
	std::shared_ptr<T> ptr;
	shared_ptr_wrapper(std::shared_ptr<T>&& ptr): ptr(std::move(ptr)) {}
    shared_ptr_wrapper(const std::shared_ptr<T>& ptr): ptr(ptr) {}
	virtual ~shared_ptr_wrapper() {}
};

extern std::set<std::unique_ptr<shared_ptr_wrapper_base>> shared_pointers;

template <typename T>
dgmpp_handle add_shared_ptr_wrapper(const std::shared_ptr<T>& ptr) {
    auto i = shared_pointers.emplace(std::make_unique<shared_ptr_wrapper<T>>(ptr));
    return i.first;
}

template <typename T>
std::shared_ptr<T> get_shared_ptr(dgmpp_handle h) {
    auto i = std::find_if(shared_pointers.begin(), shared_pointers.end(), [=](const auto& i) {
        return static_cast<void*>(i.get()) == h;
    });
	if (i == shared_pointers.end())
		return nullptr;
    else if (auto ptr = dynamic_cast<shared_ptr_wrapper<T>*>(i->second)) {
        return ptr->ptr;
    }
}


//enum class dgmpp_handle_tag: char {
//	invalid = -1,
//	ptr,
//	unique_ptr_gang,
//	unique_ptr_character,
//	unique_ptr_booster,
//	unique_ptr_implant,
//	unique_ptr_ship,
//	unique_ptr_structure,
//	unique_ptr_module,
//	unique_ptr_drone,
//	unique_ptr_charge,
//	unique_ptr_area,
//	unique_ptr_planet,
//	unique_ptr_array
//};
	*/

struct dgmpp_array_impl_base {
	size_t size;
	dgmpp_array_impl_base (size_t size): size(size) {}
	virtual const void* ptr() const = 0;
};

//template<typename T> dgmpp_handle dgmpp_make_handle(T* ptr) {
//	return dgmpp_handle{dgmpp_handle_tag::ptr, ptr};
//}

template <typename T, typename = void>
struct dgmpp_array_impl: public dgmpp_array_impl_base {
	std::vector<T> values;
	
	template <typename C, typename Constructor = T>
	dgmpp_array_impl(const C& c): dgmpp_array_impl_base (std::size(c)) {
		values.reserve(size);
		std::transform(c.begin(), c.end(), std::back_inserter(values), [](const auto& i) {
			return Constructor(i);
		});
	}
	
	virtual const void* ptr() const override {
		return reinterpret_cast<const void*>(&values[0]);
	}
};


template<typename T, typename C>
dgmpp_handle dgmpp_make_array(const C& c) {
    return new_handle(dgmpp_array_impl<T>(c));
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


