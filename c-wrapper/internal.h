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

using namespace dgmpp;

struct dgmpp_type_impl {
	Type* type;
	BOOL owned = true;
	dgmpp_type_impl (Type* type) : type(type) {}
	virtual ~dgmpp_type_impl() {}
};

inline dgmpp_type_ptr dgmpp_make_type(Type* type) {
	return type ? reinterpret_cast<dgmpp_type_ptr>(new dgmpp_type_impl{type}) : nullptr;
}

struct dgmpp_attribute_impl {
	Attribute* attribute;
	BOOL owned = true;
};

struct dgmpp_planet_impl {
	std::unique_ptr<Planet> planet;
};

struct dgmpp_facility_impl {
	Facility* facility;
	BOOL owned = true;
};


struct dgmpp_types_array_impl : public dgmpp_types_array {
	template <typename C>
	dgmpp_types_array_impl(const C& container) {
		count = std::size(container);
		if (count > 0) {
			types = new dgmpp_type_ptr[count];
			auto ptr = types;
			for (auto i: container) {
				*ptr++ = dgmpp_make_type(i);
			}
		}
		else
			types = nullptr;
	}
	
	~dgmpp_types_array_impl() {
		if (types) {
			auto ptr = types;
			for (int i = 0; i < count; i++, ptr++) {
				if (auto type = reinterpret_cast<dgmpp_type_impl*>(*ptr); type->owned)
					delete type;
			}
			delete[] types;
		}
	}
};

struct dgmpp_attributes_array_impl : public dgmpp_attributes_array {
	template <typename C>
	dgmpp_attributes_array_impl(const C& container) {
		count = std::size(container);
		if (count > 0) {
			attributes = new dgmpp_attribute_ptr[count];
			auto ptr = attributes;
			for (auto i: container) {
				*ptr++ = reinterpret_cast<dgmpp_attribute_ptr>(new dgmpp_attribute_impl{i});
			}
		}
		else
			attributes = nullptr;
	}

	~dgmpp_attributes_array_impl() {
		if (attributes) {
			auto ptr = attributes;
			for (int i = 0; i < count; i++, ptr++) {
				if (auto attribute = reinterpret_cast<dgmpp_attribute_impl*>(*ptr); attribute->owned)
					delete attribute;
			}
			delete[] attributes;
		}
	}
};

struct dgmpp_ints_array_impl : public dgmpp_ints_array {
	template <typename C>
	dgmpp_ints_array_impl(const C& container) {
		count = std::size(container);
		if (count > 0) {
			values = new int[count];
			auto ptr = values;
			for (auto i: container) {
				*ptr++ = static_cast<int>(i);
			}
		}
		else
			values = nullptr;
	}
	
	~dgmpp_ints_array_impl() {
		if (values) {
			delete[] values;
		}
	}
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

struct dgmpp_capacitor_impl {
	Capacitor* capacitor;
};

template <typename T> T type_cast(dgmpp_type_ptr type) {
	return type ? reinterpret_cast<T>(reinterpret_cast<dgmpp_type_impl*>(type)->type) : nullptr;
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
