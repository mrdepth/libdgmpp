//
//  drone.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "drone.h"
#include "internal.h"

dgmpp_type dgmpp_drone_create (dgmpp_type_id type_id) {
	try {
        return new_handle(std::make_shared<Drone>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_drone_copy (dgmpp_type drone) {
	try {
        return new_handle(std::make_shared<Drone>(*get<Drone>(drone)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_bool dgmpp_drone_is_active (dgmpp_type drone) {
    return get<Drone>(drone)->active();
}

void dgmpp_drone_set_active (dgmpp_type drone, dgmpp_bool active) {
    get<Drone>(drone)->active(active);
}

dgmpp_bool dgmpp_drone_has_kamikaze_ability (dgmpp_type drone) {
    return get<Drone>(drone)->hasKamikazeAbility();
}

dgmpp_bool dgmpp_drone_is_kamikaze (dgmpp_type drone) {
    return get<Drone>(drone)->kamikaze();
}

void dgmpp_drone_set_kamikaze (dgmpp_type drone, dgmpp_bool kamikaze) {
    get<Drone>(drone)->kamikaze(kamikaze);
}

dgmpp_type dgmpp_drone_copy_charge (dgmpp_type drone) {
    return new_handle(get<Drone>(drone)->charge());
}

DGMPP_DRONE_SQUADRON dgmpp_drone_get_squadron (dgmpp_type drone) {
    return static_cast<DGMPP_DRONE_SQUADRON>(get<Drone>(drone)->squadron());
}

size_t dgmpp_drone_get_squadron_size (dgmpp_type drone) {
    return get<Drone>(drone)->squadronSize();
}

int dgmpp_drone_get_squadron_tag (dgmpp_type drone) {
    return get<Drone>(drone)->squadronTag();
}

dgmpp_type dgmpp_drone_copy_target (dgmpp_type drone) {
    return new_handle(get<Drone>(drone)->target());
}

dgmpp_bool dgmpp_drone_set_target (dgmpp_type drone, dgmpp_type target) {
	try {
		get<Drone>(drone)->target(get<Ship>(target));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_seconds dgmpp_drone_get_cycle_time (dgmpp_type drone) {
	return dgmpp_make_seconds(get<Drone>(drone)->cycleTime());
}

dgmpp_damage_vector dgmpp_drone_get_volley (dgmpp_type drone) {
    return dgmpp_damage_vector_make(get<Drone>(drone)->volley());
}

dgmpp_damage_per_second dgmpp_drone_get_dps (dgmpp_type drone) {
	return dgmpp_drone_get_dps_v2(drone, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_drone_get_dps_v2 (dgmpp_type drone, dgmpp_hostile_target target) {
    return dgmpp_damage_per_second_make(get<Drone>(drone)->dps(hostile_target_make(target)));
}

dgmpp_meter dgmpp_drone_get_optimal (dgmpp_type drone) {
    return get<Drone>(drone)->optimal();
}

dgmpp_meter dgmpp_drone_get_falloff (dgmpp_type drone) {
    return get<Drone>(drone)->falloff();
}

dgmpp_points dgmpp_drone_get_accuracy_score (dgmpp_type drone) {
    return get<Drone>(drone)->accuracyScore();
}

dgmpp_cubic_meter_per_second dgmpp_drone_get_mining_yield (dgmpp_type drone) {
    return get<Drone>(drone)->miningYield() * 1s;
}

dgmpp_meters_per_second dgmpp_drone_get_velocity (dgmpp_type drone) {
    return get<Drone>(drone)->velocity() * 1s;
}

