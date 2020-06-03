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

extern std::map<void*, std::shared_ptr<struct dgmpp_handle_store>> handles;

struct dgmpp_handle_store {
    virtual ~dgmpp_handle_store() {};
	virtual void* ptr() = 0;

	dgmpp_handle_store* retain() {
		ref_count++;
		return this;
	}
	
	void release() {
		ref_count--;
		if (ref_count == 0) {
            handles.erase(ptr());
		}
	}

private:
	size_t ref_count{ 1 };
};


template <typename Wrapped>
struct dgmpp_handle_store_impl: dgmpp_handle_store {
    virtual ~dgmpp_handle_store_impl() {}
    
    std::shared_ptr<Wrapped> store;
    dgmpp_handle_store_impl(const std::shared_ptr<Wrapped>& ptr): store(ptr) {};
	dgmpp_handle_store_impl(std::shared_ptr<Wrapped>&& ptr) : store(std::move(ptr)) {};

	virtual void* ptr() override {
		return store.get();
	}
};

template <typename T, std::enable_if_t<!std::is_base_of_v<Type, typename std::decay<T>::type::element_type> && !std::is_base_of_v<Facility, typename std::decay<T>::type::element_type>, int> = 0>
dgmpp_handle new_handle(T&& ptr) {
    auto key = ptr.get();
	if (auto i = handles.find(key); i != handles.end()) {
		return i->second->retain();
	}
	return handles.emplace(key, new dgmpp_handle_store_impl<typename std::decay<T>::type::element_type>{ std::forward<T>(ptr) }).first->second.get();
}

template <typename T, std::enable_if_t<std::is_base_of_v<Type, T>, int> = 0>
dgmpp_handle new_handle(const std::shared_ptr<T>& ptr) {
    if (ptr == nullptr) {
        return nullptr;
    }
    
    if (auto i = handles.find(ptr.get()); i != handles.end()) {
        return i->second->retain();
    }
    return handles.emplace(ptr.get(), new dgmpp_handle_store_impl<Type>{ std::static_pointer_cast<Type>(ptr) }).first->second.get();
}

template <typename T, std::enable_if_t<std::is_base_of_v<Facility, T>, int> = 0>
dgmpp_handle new_handle(const std::shared_ptr<T>& ptr) {
    if (ptr == nullptr) {
        return nullptr;
    }
    
    if (auto i = handles.find(ptr.get()); i != handles.end()) {
        return i->second->retain();
    }
    return handles.emplace(ptr.get(), new dgmpp_handle_store_impl<Facility>{ std::static_pointer_cast<Facility>(ptr) }).first->second.get();
}


template <typename T, std::enable_if_t<!std::is_base_of_v<Type, T> && !std::is_base_of_v<Facility, T>, int> = 0>
std::shared_ptr<T> get(dgmpp_handle handle) {
	auto baseHandle = reinterpret_cast<dgmpp_handle_store*>(handle);
	if (auto h = dynamic_cast<dgmpp_handle_store_impl<T>*>(baseHandle)) {
		return h->store;
	}
	else {
		return nullptr;
	}
}

template <typename T, std::enable_if_t<std::is_base_of_v<Type, T>, int> = 0>
std::shared_ptr<T> get(dgmpp_handle handle) {
    if (handle == nullptr) {
        return nullptr;
    }
	auto baseHandle = reinterpret_cast<dgmpp_handle_store*>(handle);
	if (auto h = dynamic_cast<dgmpp_handle_store_impl<Type>* >(baseHandle)) {
		return std::dynamic_pointer_cast<T>(h->store);
	}
	else {
		return nullptr;
	}
}

template <typename T, std::enable_if_t<std::is_base_of_v<Facility, T>, int> = 0>
std::shared_ptr<T> get(dgmpp_handle handle) {
    if (handle == nullptr) {
        return nullptr;
    }
    auto baseHandle = reinterpret_cast<dgmpp_handle_store*>(handle);
    if (auto h = dynamic_cast<dgmpp_handle_store_impl<Facility>* >(baseHandle)) {
        return std::dynamic_pointer_cast<T>(h->store);
    }
    else {
        return nullptr;
    }
}


template<typename T>
struct array_deleter {
	void operator()(std::vector<T>& elements) const {
	}
};

template<>
struct array_deleter<dgmpp_handle> {
	void operator()(std::vector<dgmpp_handle>& elements) const {
		for (auto& i : elements) {
			reinterpret_cast<dgmpp_handle_store*>(i)->release();
		}
	}
};

struct dgmpp_array_impl_base {
	virtual ~dgmpp_array_impl_base() {};
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
	
	template <typename C>
	dgmpp_array_impl(C&& container): dgmpp_array_impl_base (std::size(container)), values(std::forward<C>(container)) {
		//values.reserve(size);
		//std::transform(c.begin(), c.end(), std::back_inserter(values), [](const auto& i) {
		//	return Constructor(i);
		//});
	}

	virtual ~dgmpp_array_impl() {
		array_deleter<T>()(values);
	}
	
	virtual const void* ptr() const override {
		return reinterpret_cast<const void*>(&values[0]);
	}
};


template<typename T, typename C>
dgmpp_handle dgmpp_make_array(C&& container) {
    return new_handle(std::shared_ptr<dgmpp_array_impl_base>(new dgmpp_array_impl<T>(std::forward<C>(container))));
}

struct dgmpp_route_impl {
    std::shared_ptr<Facility> from;
    std::shared_ptr<Facility> to;
    const dgmpp_commodity commodity;
    
    dgmpp_route_impl(const std::shared_ptr<Facility>& from, const std::shared_ptr<Facility>& to, const dgmpp_commodity& commodity):
        from(from), to(to), commodity(commodity) {}
};

template<typename Rep, typename Ratio>
inline dgmpp_seconds  dgmpp_make_seconds(const std::chrono::duration<Rep, Ratio>& v) {
	return static_cast<dgmpp_seconds>(std::chrono::duration_cast<std::chrono::seconds>(v).count());
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

inline dgmpp_commodity dgmpp_commodity_make(const Commodity& c) {
    return dgmpp_commodity{
        static_cast<dgmpp_type_id>(c.metaInfo().typeID),
        static_cast<DGMPP_COMMODITY_TIER>(c.metaInfo().tier),
        c.metaInfo().volume,
        c.quantity()};
}

inline dgmpp_production_cycle dgmpp_production_cycle_make(const ProductionCycle& c) {
    return dgmpp_production_cycle{
        dgmpp_make_seconds(c.start),
        dgmpp_make_seconds(c.duration),
        dgmpp_commodity_make(c.yield),
        dgmpp_commodity_make(c.waste)};
}

//inline dgmpp_route dgmpp_route_make(const Route& route) {
//    return dgmpp_route{
//        route.from,
//        route.to,
//        dgmpp_commodity_make(route.commodity)};
//}

//struct dgmpp_commodity_impl: public dgmpp_commodity {
//	dgmpp_commodity_impl(const Commodity& c)
//	: dgmpp_commodity{
//		static_cast<dgmpp_type_id>(c.metaInfo().typeID),
//		static_cast<DGMPP_COMMODITY_TIER>(c.metaInfo().tier),
//		c.metaInfo().volume,
//		c.quantity()} {}
//};
//
//struct dgmpp_production_cycle_impl: public dgmpp_production_cycle {
//	dgmpp_production_cycle_impl(const ProductionCycle& c)
//	: dgmpp_production_cycle{
//		dgmpp_make_seconds(c.start),
//		dgmpp_make_seconds(c.duration),
//		dgmpp_commodity_impl(c.yield),
//		dgmpp_commodity_impl(c.waste)} {}
//
//
//	dgmpp_production_cycle_impl(const ProductionCycle* c)
//	: dgmpp_production_cycle_impl(*c) {}
//};
//
//
//struct dgmpp_route_impl: public dgmpp_route {
//	dgmpp_route_impl (const Route& route)
//	: dgmpp_route{
//		route.from,
//		route.to,
//		dgmpp_commodity_impl(route.commodity)} {}
//};
//
//
