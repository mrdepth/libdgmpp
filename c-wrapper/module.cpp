//
//  module.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "module.h"
#include "internal.h"

dgmpp_type dgmpp_module_create (dgmpp_type_id type_id) {
	try {
        return new_handle(std::make_shared<Module>(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

dgmpp_type dgmpp_module_copy (dgmpp_type module) {
	try {
        return new_handle(std::make_shared<Module>(*get<Module>(module)));
	}
	catch (...) {
		return nullptr;
	}
}

DGMPP_MODULE_SLOT dgmpp_module_get_slot (dgmpp_type module) {
    return static_cast<DGMPP_MODULE_SLOT>(get<Module>(module)->slot());
}

DGMPP_MODULE_HARDPOINT dgmpp_module_get_hardpoint (dgmpp_type module) {
    return static_cast<DGMPP_MODULE_HARDPOINT>(get<Module>(module)->hardpoint());
}

size_t dgmpp_module_get_socket (dgmpp_type module) {
    return get<Module>(module)->socket();
}

DGMPP_MODULE_STATE dgmpp_module_get_state (dgmpp_type module) {
    return static_cast<DGMPP_MODULE_STATE>(get<Module>(module)->state());
}

void dgmpp_module_set_state (dgmpp_type module, DGMPP_MODULE_STATE state) {
    return get<Module>(module)->state(static_cast<Module::State>(state));
}

DGMPP_MODULE_STATE dgmpp_module_get_preferred_state (dgmpp_type module) {
    return static_cast<DGMPP_MODULE_STATE>(get<Module>(module)->preferredState());
}

dgmpp_array dgmpp_module_copy_available_states (dgmpp_type module) {
    auto states = get<Module>(module)->availableStates();
    std::vector<DGMPP_MODULE_STATE> result;
    std::transform(states.begin(), states.end(), std::back_inserter(result), [](const auto& i) {
        return static_cast<DGMPP_MODULE_STATE>(i);
    });
    return dgmpp_make_array<DGMPP_MODULE_STATE>(std::move(result));
}

dgmpp_type dgmpp_module_copy_target (dgmpp_type module) {
    return new_handle(get<Module>(module)->target());
}

dgmpp_bool dgmpp_module_set_target (dgmpp_type module, dgmpp_type target) {
	try {
		get<Module>(module)->target(get<Ship>(target));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_type dgmpp_module_copy_charge (dgmpp_type module) {
	return new_handle(get<Module>(module)->charge());
}

dgmpp_bool dgmpp_module_set_charge (dgmpp_type module, dgmpp_type charge) {
	try {
        get<Module>(module)->charge(get<Charge>(charge));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_array dgmpp_module_copy_charge_groups (dgmpp_type module) {
    auto groups = get<Module>(module)->chargeGroups();
    std::vector<dgmpp_group_id> result;
    std::transform(groups.begin(), groups.end(), std::back_inserter(result), [](const auto& i) {
        return static_cast<dgmpp_group_id>(i);
    });
    return dgmpp_make_array<dgmpp_group_id>(std::move(result));
}

DGMPP_CHARGE_SIZE dgmpp_module_get_charge_size (dgmpp_type module) {
    return static_cast<DGMPP_CHARGE_SIZE>(get<Module>(module)->chargeSize());
}

dgmpp_bool dgmpp_module_is_fail (dgmpp_type module) {
    return get<Module>(module)->fail();
}

dgmpp_bool dgmpp_module_require_target (dgmpp_type module) {
    return get<Module>(module)->requireTarget();
}

dgmpp_bool dgmpp_module_can_have_state (dgmpp_type module, DGMPP_MODULE_STATE state) {
    return get<Module>(module)->canHaveState(static_cast<Module::State>(state));
}

dgmpp_bool dgmpp_module_can_fit_charge (dgmpp_type module, dgmpp_type charge) {
    return get<Module>(module)->canFit(get<Charge>(charge).get());
}

dgmpp_seconds dgmpp_module_get_reload_time (dgmpp_type module) {
    return dgmpp_make_seconds(get<Module>(module)->reloadTime());
}

dgmpp_seconds dgmpp_module_get_cycle_time (dgmpp_type module) {
    return dgmpp_make_seconds(get<Module>(module)->cycleTime());
}

dgmpp_seconds dgmpp_module_get_raw_cycle_time (dgmpp_type module) {
    return dgmpp_make_seconds(get<Module>(module)->rawCycleTime());
}

size_t dgmpp_module_get_charges (dgmpp_type module) {
    return get<Module>(module)->charges();
}

size_t dgmpp_module_get_shots (dgmpp_type module) {
    return get<Module>(module)->shots();
}

dgmpp_giga_joule_per_second dgmpp_module_get_cap_use (dgmpp_type module) {
    return get<Module>(module)->capUse() * 1s;
}

dgmpp_teraflops dgmpp_module_get_cpu_use (dgmpp_type module) {
    return get<Module>(module)->cpuUse();
}

dgmpp_mega_watts dgmpp_module_get_power_grid_use (dgmpp_type module) {
    return get<Module>(module)->powerGridUse();
}

dgmpp_calibration_points dgmpp_module_get_calibration_use (dgmpp_type module) {
    return get<Module>(module)->calibrationUse();
}

dgmpp_points dgmpp_module_get_accuracy_score (dgmpp_type module) {
    return get<Module>(module)->accuracyScore();
}

dgmpp_meter dgmpp_module_get_signature_resolution (dgmpp_type module) {
    return get<Module>(module)->signatureResolution();
}

dgmpp_cubic_meter_per_second dgmpp_module_get_mining_yield (dgmpp_type module) {
    return get<Module>(module)->miningYield() * 1s;
}

dgmpp_damage_vector dgmpp_module_get_volley (dgmpp_type module) {
    return dgmpp_damage_vector_make(get<Module>(module)->volley());
}

dgmpp_damage_per_second dgmpp_module_get_dps (dgmpp_type module) {
	return dgmpp_module_get_dps_v2(module, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_module_get_dps_v2 (dgmpp_type module, dgmpp_hostile_target target) {
    return dgmpp_damage_per_second_make(get<Module>(module)->dps(hostile_target_make(target)));
}

dgmpp_meter dgmpp_module_get_optimal (dgmpp_type module) {
    return get<Module>(module)->optimal();
}

dgmpp_meter dgmpp_module_get_falloff (dgmpp_type module) {
    return get<Module>(module)->falloff();
}

dgmpp_seconds dgmpp_module_get_life_time (dgmpp_type module) {
	if (auto lifeTime = get<Module>(module)->lifeTime())
		return dgmpp_make_seconds(*lifeTime);
	else
		return -1;
}

dgmpp_radians_per_second dgmpp_module_get_angular_velocity (dgmpp_type module, dgmpp_meter target_signature, dgmpp_percent hit_chance) {
	return get<Module>(module)->angularVelocity(target_signature, hit_chance) * 1s;
}
