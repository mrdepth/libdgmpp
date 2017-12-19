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

using namespace dgmpp;

struct dgmpp_t_impl {
	virtual ~dgmpp_t_impl() {}
	int ref_count = 1;
	void retain() { ref_count++; }
	void release() {
		if (--ref_count == 0)
			delete this;
	}
};

struct dgmpp_type_impl: public dgmpp_t_impl {
	Type* type;
	dgmpp_type_impl (Type* type) : type(type) {}
};

inline dgmpp_type_ptr dgmpp_make_type(Type* type) {
	return type ? reinterpret_cast<dgmpp_type_ptr>(new dgmpp_type_impl{type}) : nullptr;
}

struct dgmpp_attribute_impl: public dgmpp_t_impl {
	Attribute* attribute;
	dgmpp_attribute_impl (Attribute* attribute) : attribute(attribute) {};
};

struct dgmpp_gang_impl : public dgmpp_type_impl {
	std::unique_ptr<Gang> gang;
	dgmpp_gang_impl() : dgmpp_type_impl(nullptr), gang(Gang::Create()) {
		type = gang.get();
	}
};

struct dgmpp_character_impl : public dgmpp_type_impl {
	std::unique_ptr<Character> character;
	dgmpp_character_impl() : dgmpp_type_impl(nullptr), character(Character::Create()) {
		type = character.get();
	}
};

struct dgmpp_implant_impl : public dgmpp_type_impl {
	std::unique_ptr<Implant> implant;
	dgmpp_implant_impl(TypeID typeID) : dgmpp_type_impl(nullptr), implant(Implant::Create(typeID)) {
		type = implant.get();
	}
};

struct dgmpp_booster_impl : public dgmpp_type_impl {
	std::unique_ptr<Booster> booster;
	dgmpp_booster_impl(TypeID typeID) : dgmpp_type_impl(nullptr), booster(Booster::Create(typeID)) {
		type = booster.get();
	}
};

struct dgmpp_ship_impl : public dgmpp_type_impl {
	std::unique_ptr<Ship> ship;
	dgmpp_ship_impl(TypeID typeID) : dgmpp_type_impl(nullptr), ship(Ship::Create(typeID)) {
		type = ship.get();
	}
};

struct dgmpp_structure_impl : public dgmpp_type_impl {
	std::unique_ptr<Structure> structure;
	dgmpp_structure_impl(TypeID typeID) : dgmpp_type_impl(nullptr), structure(Structure::Create(typeID)) {
		type = structure.get();
	}
};

struct dgmpp_module_impl : public dgmpp_type_impl {
	std::unique_ptr<Module> module;
	dgmpp_module_impl(TypeID typeID) : dgmpp_type_impl(nullptr), module(Module::Create(typeID)) {
		type = module.get();
	}
};

struct dgmpp_charge_impl : public dgmpp_type_impl {
	std::unique_ptr<Charge> charge;
	dgmpp_charge_impl(TypeID typeID) : dgmpp_type_impl(nullptr), charge(Charge::Create(typeID)) {
		type = charge.get();
	}
};

struct dgmpp_drone_impl : public dgmpp_type_impl {
	std::unique_ptr<Drone> drone;
	dgmpp_drone_impl(TypeID typeID) : dgmpp_type_impl(nullptr), drone(Drone::Create(typeID)) {
		type = drone.get();
	}
};

struct dgmpp_area_impl : public dgmpp_type_impl {
	std::unique_ptr<Area> area;
	dgmpp_area_impl(TypeID typeID) : dgmpp_type_impl(nullptr), area(Area::Create(typeID)) {
		type = area.get();
	}
};

struct dgmpp_capacitor_impl: public dgmpp_t_impl {
	Capacitor* capacitor;
	dgmpp_capacitor_impl (Capacitor* capacitor) : capacitor(capacitor) {}
};

struct dgmpp_planet_impl: public dgmpp_t_impl {
	Planet planet;
};

struct dgmpp_facility_impl: public dgmpp_t_impl {
	Facility* facility;
	dgmpp_facility_impl (Facility* facility) : facility(facility) {}
};

struct dgmpp_state_impl: public dgmpp_t_impl {
	State* state;
	template<typename T>
	dgmpp_state_impl (const T& state) : state(remove_unique_ptr(state)) {}
};

struct dgmpp_array_impl_base: public dgmpp_t_impl {
	size_t size;
	dgmpp_array_impl_base (size_t size): size(size) {}
	virtual const void* ptr() = 0;
};

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
	
	virtual const void* ptr() override {
		return reinterpret_cast<const void*>(&values[0]);
	}
};

template <typename T>
struct dgmpp_array_impl<T, std::enable_if_t<std::is_pointer_v<T>>>: public dgmpp_array_impl_base {
	std::vector<T> values;
	
	template <typename C>
	dgmpp_array_impl(const C& c): dgmpp_array_impl_base (std::size(c)) {
		values.reserve(size);
		std::transform(c.begin(), c.end(), std::back_inserter(values), [](const auto& i) {
			return new std::remove_pointer_t<T>(i);
		});
	}
	
	virtual const void* ptr() override {
		return reinterpret_cast<const void*>(&values[0]);
	}
	
	virtual ~dgmpp_array_impl<T>() {
		for (auto i: values)
			dgmpp_release(reinterpret_cast<dgmpp_ptr>(i));
	}
};


//template<typename T>
//struct dgmpp_array_destroyer<T, std::enable_if_t<std::is_pointer_v<typename T::value_type>>> {
//	static void destroy(T& arr) {
//		for (auto i: arr.values)
//			dgmpp_release(i);
//	}
//};



template<typename T, typename C>
dgmpp_array_ptr dgmpp_make_array(const C& c) {
	return reinterpret_cast<dgmpp_array_ptr>(new dgmpp_array_impl<T>(c));
}

template <typename T> T type_cast(dgmpp_type_ptr type) {
	return type ? reinterpret_cast<T>(reinterpret_cast<dgmpp_type_impl*>(type)->type) : nullptr;
}

template <typename T> T facility_cast(dgmpp_facility_ptr facility) {
	return facility ? reinterpret_cast<T>(reinterpret_cast<dgmpp_facility_impl*>(facility)->facility) : nullptr;
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

	
	dgmpp_production_cycle_impl(const std::unique_ptr<ProductionCycle>& c)
	: dgmpp_production_cycle_impl(*c) {}
};


inline dgmpp_facility_ptr dgmpp_make_facility(Facility* facility) {
	return facility ? reinterpret_cast<dgmpp_facility_ptr>(new dgmpp_facility_impl{facility}) : nullptr;
}
