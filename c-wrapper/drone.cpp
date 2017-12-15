//
//  drone.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "drone.h"
#include "internal.h"

dgmpp_type_ptr dgmpp_drone_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_drone_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

BOOL dgmpp_drone_is_active (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->active();
}

void dgmpp_drone_set_active (dgmpp_type_ptr drone, BOOL active) {
	type_cast<Drone*>(drone)->active(active);
}

dgmpp_type_ptr dgmpp_drone_get_charge (dgmpp_type_ptr drone) {
	return dgmpp_make_type(type_cast<Drone*>(drone)->charge());
}

DGMPP_DRONE_SQUADRON dgmpp_drone_get_squadron (dgmpp_type_ptr drone) {
	return static_cast<DGMPP_DRONE_SQUADRON>(type_cast<Drone*>(drone)->squadron());
}

size_t dgmpp_drone_get_squadron_size (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->squadronSize();
}

int dgmpp_drone_get_squadron_tag (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->squadronTag();
}

dgmpp_type_ptr dgmpp_drone_get_target (dgmpp_type_ptr drone) {
	return dgmpp_make_type(type_cast<Drone*>(drone)->target());
}

BOOL dgmpp_drone_set_target (dgmpp_type_ptr drone, dgmpp_type_ptr target) {
	try {
		type_cast<Drone*>(drone)->target(type_cast<Ship*>(target));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_seconds dgmpp_drone_get_cycle_time (dgmpp_type_ptr drone) {
	return  dgmpp_make_seconds(type_cast<Drone*>(drone)->cycleTime());
}

dgmpp_damage_vector dgmpp_drone_get_volley (dgmpp_type_ptr drone) {
	return dgmpp_damage_vector_make(type_cast<Drone*>(drone)->volley());
}

dgmpp_damage_per_second dgmpp_drone_get_dps (dgmpp_type_ptr drone) {
	return dgmpp_drone_get_dps_v2(drone, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_drone_get_dps_v2 (dgmpp_type_ptr drone, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(type_cast<Drone*>(drone)->dps(hostile_target_make(target)));
}

dgmpp_meter dgmpp_drone_get_optimal (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->optimal();
}

dgmpp_meter dgmpp_drone_get_falloff (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->falloff();
}

dgmpp_points dgmpp_drone_get_accuracy_score (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->accuracyScore();
}

dgmpp_cubic_meter_per_second dgmpp_drone_get_mining_yield (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->miningYield() * 1s;
}

dgmpp_meters_per_second dgmpp_drone_get_velocity (dgmpp_type_ptr drone) {
	return type_cast<Drone*>(drone)->velocity() * 1s;
}

