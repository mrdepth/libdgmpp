//
//  drone.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "drone.h"
#include "internal.h"

BOOL dgmpp_drone_create (dgmpp_type_id type_id, dgmpp_type* drone) {
	try {
		*drone = dgmpp_handle_impl(Drone::Create(static_cast<TypeID>(type_id)), dgmpp_handle_tag::unique_ptr_drone);
		return true;
	}
	catch (...) {
		return false;
	}
}

BOOL dgmpp_drone_is_active (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).active();
}

void dgmpp_drone_set_active (dgmpp_type drone, BOOL active) {
	dgmpp_cast<Drone>(drone).active(active);
}

BOOL dgmpp_drone_get_charge (dgmpp_type drone, dgmpp_type* charge) {
	if (auto type = dgmpp_cast<Drone>(drone).charge()) {
		*charge = dgmpp_handle_impl(type);
		return true;
	}
	else
		return false;
}

DGMPP_DRONE_SQUADRON dgmpp_drone_get_squadron (dgmpp_type drone) {
	return static_cast<DGMPP_DRONE_SQUADRON>(dgmpp_cast<Drone>(drone).squadron());
}

size_t dgmpp_drone_get_squadron_size (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).squadronSize();
}

int dgmpp_drone_get_squadron_tag (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).squadronTag();
}

BOOL dgmpp_drone_get_target	(dgmpp_type drone, dgmpp_type* target) {
	if (auto type = dgmpp_cast<Drone>(drone).target()) {
		*target = dgmpp_handle_impl(type);
		return true;
	}
	else
		return false;
}

BOOL dgmpp_drone_set_target (dgmpp_type drone, dgmpp_type* target) {
	try {
		if (target)
			dgmpp_cast<Drone>(drone).target(&dgmpp_cast<Ship>(*target));
		else
			dgmpp_cast<Drone>(drone).target(nullptr);
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_seconds dgmpp_drone_get_cycle_time (dgmpp_type drone) {
	return  dgmpp_make_seconds(dgmpp_cast<Drone>(drone).cycleTime());
}

dgmpp_damage_vector dgmpp_drone_get_volley (dgmpp_type drone) {
	return dgmpp_damage_vector_make(dgmpp_cast<Drone>(drone).volley());
}

dgmpp_damage_per_second dgmpp_drone_get_dps (dgmpp_type drone) {
	return dgmpp_drone_get_dps_v2(drone, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_drone_get_dps_v2 (dgmpp_type drone, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(dgmpp_cast<Drone>(drone).dps(hostile_target_make(target)));
}

dgmpp_meter dgmpp_drone_get_optimal (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).optimal();
}

dgmpp_meter dgmpp_drone_get_falloff (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).falloff();
}

dgmpp_points dgmpp_drone_get_accuracy_score (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).accuracyScore();
}

dgmpp_cubic_meter_per_second dgmpp_drone_get_mining_yield (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).miningYield() * 1s;
}

dgmpp_meters_per_second dgmpp_drone_get_velocity (dgmpp_type drone) {
	return dgmpp_cast<Drone>(drone).velocity() * 1s;
}

