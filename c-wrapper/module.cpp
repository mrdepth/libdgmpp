//
//  module.cpp
//  dgmpp
//
//  Created by Artem Shimanski on 14.12.2017.
//

#include "module.h"
#include "internal.h"

dgmpp_type_ptr dgmpp_module_create (dgmpp_type_id type_id) {
	try {
		return reinterpret_cast<dgmpp_type_ptr>(new dgmpp_module_impl(static_cast<TypeID>(type_id)));
	}
	catch (...) {
		return nullptr;
	}
}

DGMPP_MODULE_SLOT dgmpp_module_get_slot (dgmpp_type_ptr module) {
	return static_cast<DGMPP_MODULE_SLOT>(type_cast<Module*>(module)->slot());
}

DGMPP_MODULE_HARDPOINT dgmpp_module_get_hardpoint (dgmpp_type_ptr module) {
	return static_cast<DGMPP_MODULE_HARDPOINT>(type_cast<Module*>(module)->hardpoint());
}

size_t dgmpp_module_get_socket (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->socket();
}

DGMPP_MODULE_STATE dgmpp_module_get_state (dgmpp_type_ptr module) {
	return static_cast<DGMPP_MODULE_STATE>(type_cast<Module*>(module)->state());
}

void dgmpp_module_set_state (dgmpp_type_ptr module, DGMPP_MODULE_STATE state) {
	type_cast<Module*>(module)->state(static_cast<Module::State>(state));
}

DGMPP_MODULE_STATE dgmpp_module_get_preferred_state (dgmpp_type_ptr module) {
	return static_cast<DGMPP_MODULE_STATE>(type_cast<Module*>(module)->preferredState());
}

dgmpp_array_ptr dgmpp_module_get_available_states (dgmpp_type_ptr module) {
	return dgmpp_make_array<int>(type_cast<Module*>(module)->availableStates());
}

dgmpp_type_ptr dgmpp_module_get_target (dgmpp_type_ptr module) {
	return dgmpp_make_type(type_cast<Module*>(module)->target());
}

BOOL dgmpp_module_set_target (dgmpp_type_ptr module, dgmpp_type_ptr target) {
	try {
		type_cast<Module*>(module)->target(type_cast<Ship*>(target));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_type_ptr dgmpp_module_get_charge (dgmpp_type_ptr module) {
	return dgmpp_make_type(type_cast<Module*>(module)->charge());
}

BOOL dgmpp_module_set_charge (dgmpp_type_ptr module, dgmpp_type_ptr charge) {
	try {
		type_cast<Module*>(module)->charge(std::move(reinterpret_cast<dgmpp_charge_impl*>(charge)->charge));
		return true;
	}
	catch(...) {
		return false;
	}
}

dgmpp_array_ptr dgmpp_module_get_charge_groups (dgmpp_type_ptr module) {
	return dgmpp_make_array<int>(type_cast<Module*>(module)->chargeGroups());
}

DGMPP_CHARGE_SIZE dgmpp_module_get_charge_size (dgmpp_type_ptr module) {
	return static_cast<DGMPP_CHARGE_SIZE>(type_cast<Module*>(module)->chargeSize());
}

BOOL dgmpp_module_is_fail (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->fail();
}

BOOL dgmpp_module_require_target (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->requireTarget();
}

BOOL dgmpp_module_can_have_state (dgmpp_type_ptr module, DGMPP_MODULE_STATE state) {
	return type_cast<Module*>(module)->canHaveState(static_cast<Module::State>(state));
}

BOOL dgmpp_module_can_fit_charge (dgmpp_type_ptr module, dgmpp_type_ptr charge) {
	return type_cast<Module*>(module)->canFit(type_cast<Charge*>(charge));
}

dgmpp_seconds dgmpp_module_get_reload_time (dgmpp_type_ptr module) {
	return  dgmpp_make_seconds(type_cast<Module*>(module)->reloadTime());
}

dgmpp_seconds dgmpp_module_get_cycle_time (dgmpp_type_ptr module) {
	return  dgmpp_make_seconds(type_cast<Module*>(module)->cycleTime());
}

dgmpp_seconds dgmpp_module_get_raw_cycle_time (dgmpp_type_ptr module) {
	return  dgmpp_make_seconds(type_cast<Module*>(module)->rawCycleTime());
}

size_t dgmpp_module_get_charges (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->charges();
}

size_t dgmpp_module_get_shots (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->shots();
}

dgmpp_giga_joule_per_second dgmpp_module_get_cap_use (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->capUse() * 1s;
}

dgmpp_teraflops dgmpp_module_get_cpu_use (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->cpuUse();
}

dgmpp_mega_watts dgmpp_module_get_power_grid_use (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->powerGridUse();
}

dgmpp_calibration_points dgmpp_module_get_calibration_use (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->calibrationUse();
}

dgmpp_points dgmpp_module_get_accuracy_score (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->accuracyScore();
}

dgmpp_meter dgmpp_module_get_signature_resolution (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->signatureResolution();
}

dgmpp_cubic_meter_per_second dgmpp_module_get_mining_yield (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->miningYield() * 1s;
}

dgmpp_damage_vector dgmpp_module_get_volley (dgmpp_type_ptr module) {
	return dgmpp_damage_vector_make(type_cast<Module*>(module)->volley());
}

dgmpp_damage_per_second dgmpp_module_get_dps (dgmpp_type_ptr module) {
	return dgmpp_module_get_dps_v2(module, dgmpp_hostile_target_default);
}

dgmpp_damage_per_second dgmpp_module_get_dps_v2 (dgmpp_type_ptr module, dgmpp_hostile_target target) {
	return dgmpp_damage_per_second_make(type_cast<Module*>(module)->dps(hostile_target_make(target)));
}

dgmpp_meter dgmpp_module_get_optimal (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->optimal();
}

dgmpp_meter dgmpp_module_get_falloff (dgmpp_type_ptr module) {
	return type_cast<Module*>(module)->falloff();
}

dgmpp_seconds dgmpp_module_get_life_time (dgmpp_type_ptr module) {
	if (auto lifeTime = type_cast<Module*>(module)->lifeTime())
		return  dgmpp_make_seconds(*lifeTime);
	else
		return -1;
}

dgmpp_radians_per_second dgmpp_module_get_angular_velocity (dgmpp_type_ptr module, dgmpp_meter target_signature, dgmpp_percent hit_chance) {
	return type_cast<Module*>(module)->angularVelocity(target_signature, hit_chance) * 1s;
}
