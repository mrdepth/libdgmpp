/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class dgmppJNI {
  public final static native void DamageVector_em_set(long jarg1, DamageVector jarg1_, double jarg2);
  public final static native double DamageVector_em_get(long jarg1, DamageVector jarg1_);
  public final static native void DamageVector_thermal_set(long jarg1, DamageVector jarg1_, double jarg2);
  public final static native double DamageVector_thermal_get(long jarg1, DamageVector jarg1_);
  public final static native void DamageVector_kinetic_set(long jarg1, DamageVector jarg1_, double jarg2);
  public final static native double DamageVector_kinetic_get(long jarg1, DamageVector jarg1_);
  public final static native void DamageVector_explosive_set(long jarg1, DamageVector jarg1_, double jarg2);
  public final static native double DamageVector_explosive_get(long jarg1, DamageVector jarg1_);
  public final static native long new_DamageVector();
  public final static native void delete_DamageVector(long jarg1);
  public final static native long DamagePerSecond_count(long jarg1, DamagePerSecond jarg1_);
  public final static native long new_DamagePerSecond();
  public final static native void delete_DamagePerSecond(long jarg1);
  public final static native double UnitsPerSecond_count(long jarg1, UnitsPerSecond jarg1_);
  public final static native long new_UnitsPerSecond();
  public final static native void delete_UnitsPerSecond(long jarg1);
  public final static native double UnitsPerHour_count(long jarg1, UnitsPerHour jarg1_);
  public final static native long new_UnitsPerHour();
  public final static native void delete_UnitsPerHour(long jarg1);
  public final static native void Tank_passiveShield_set(long jarg1, Tank jarg1_, long jarg2, UnitsPerSecond jarg2_);
  public final static native long Tank_passiveShield_get(long jarg1, Tank jarg1_);
  public final static native void Tank_shieldRepair_set(long jarg1, Tank jarg1_, long jarg2, UnitsPerSecond jarg2_);
  public final static native long Tank_shieldRepair_get(long jarg1, Tank jarg1_);
  public final static native void Tank_armorRepair_set(long jarg1, Tank jarg1_, long jarg2, UnitsPerSecond jarg2_);
  public final static native long Tank_armorRepair_get(long jarg1, Tank jarg1_);
  public final static native void Tank_hullRepair_set(long jarg1, Tank jarg1_, long jarg2, UnitsPerSecond jarg2_);
  public final static native long Tank_hullRepair_get(long jarg1, Tank jarg1_);
  public final static native long new_Tank();
  public final static native void delete_Tank(long jarg1);
  public final static native void Resistances_Layer_em_set(long jarg1, Resistances.Layer jarg1_, double jarg2);
  public final static native double Resistances_Layer_em_get(long jarg1, Resistances.Layer jarg1_);
  public final static native void Resistances_Layer_thermal_set(long jarg1, Resistances.Layer jarg1_, double jarg2);
  public final static native double Resistances_Layer_thermal_get(long jarg1, Resistances.Layer jarg1_);
  public final static native void Resistances_Layer_kinetic_set(long jarg1, Resistances.Layer jarg1_, double jarg2);
  public final static native double Resistances_Layer_kinetic_get(long jarg1, Resistances.Layer jarg1_);
  public final static native void Resistances_Layer_explosive_set(long jarg1, Resistances.Layer jarg1_, double jarg2);
  public final static native double Resistances_Layer_explosive_get(long jarg1, Resistances.Layer jarg1_);
  public final static native long new_Resistances_Layer();
  public final static native void delete_Resistances_Layer(long jarg1);
  public final static native void Resistances_shield_set(long jarg1, Resistances jarg1_, long jarg2, Resistances.Layer jarg2_);
  public final static native long Resistances_shield_get(long jarg1, Resistances jarg1_);
  public final static native void Resistances_armor_set(long jarg1, Resistances jarg1_, long jarg2, Resistances.Layer jarg2_);
  public final static native long Resistances_armor_get(long jarg1, Resistances jarg1_);
  public final static native void Resistances_hull_set(long jarg1, Resistances jarg1_, long jarg2, Resistances.Layer jarg2_);
  public final static native long Resistances_hull_get(long jarg1, Resistances jarg1_);
  public final static native long new_Resistances();
  public final static native void delete_Resistances(long jarg1);
  public final static native void HitPoints_shield_set(long jarg1, HitPoints jarg1_, double jarg2);
  public final static native double HitPoints_shield_get(long jarg1, HitPoints jarg1_);
  public final static native void HitPoints_armor_set(long jarg1, HitPoints jarg1_, double jarg2);
  public final static native double HitPoints_armor_get(long jarg1, HitPoints jarg1_);
  public final static native void HitPoints_hull_set(long jarg1, HitPoints jarg1_, double jarg2);
  public final static native double HitPoints_hull_get(long jarg1, HitPoints jarg1_);
  public final static native long new_HitPoints();
  public final static native void delete_HitPoints(long jarg1);
  public final static native long new_Attributes__SWIG_0();
  public final static native long new_Attributes__SWIG_1(long jarg1);
  public final static native long Attributes_size(long jarg1, Attributes jarg1_);
  public final static native long Attributes_capacity(long jarg1, Attributes jarg1_);
  public final static native void Attributes_reserve(long jarg1, Attributes jarg1_, long jarg2);
  public final static native boolean Attributes_isEmpty(long jarg1, Attributes jarg1_);
  public final static native void Attributes_clear(long jarg1, Attributes jarg1_);
  public final static native void Attributes_add(long jarg1, Attributes jarg1_, long jarg2, Attribute jarg2_);
  public final static native long Attributes_get(long jarg1, Attributes jarg1_, int jarg2);
  public final static native void Attributes_set(long jarg1, Attributes jarg1_, int jarg2, long jarg3, Attribute jarg3_);
  public final static native void delete_Attributes(long jarg1);
  public final static native int Attribute_attributeID(long jarg1, Attribute jarg1_);
  public final static native long Attribute_owner(long jarg1, Attribute jarg1_);
  public final static native double Attribute_value(long jarg1, Attribute jarg1_);
  public final static native double Attribute_initialValue(long jarg1, Attribute jarg1_);
  public final static native void delete_Attribute(long jarg1);
  public final static native long new_Types__SWIG_0();
  public final static native long new_Types__SWIG_1(long jarg1);
  public final static native long Types_size(long jarg1, Types jarg1_);
  public final static native long Types_capacity(long jarg1, Types jarg1_);
  public final static native void Types_reserve(long jarg1, Types jarg1_, long jarg2);
  public final static native boolean Types_isEmpty(long jarg1, Types jarg1_);
  public final static native void Types_clear(long jarg1, Types jarg1_);
  public final static native void Types_add(long jarg1, Types jarg1_, long jarg2, Type jarg2_);
  public final static native long Types_get(long jarg1, Types jarg1_, int jarg2);
  public final static native void Types_set(long jarg1, Types jarg1_, int jarg2, long jarg3, Type jarg3_);
  public final static native void delete_Types(long jarg1);
  public final static native void delete_Type(long jarg1);
  public final static native int Type_typeID(long jarg1, Type jarg1_);
  public final static native int Type_groupID(long jarg1, Type jarg1_);
  public final static native int Type_categoryID(long jarg1, Type jarg1_);
  public final static native long Type_attribute(long jarg1, Type jarg1_, int jarg2);
  public final static native long Type_affectors(long jarg1, Type jarg1_);
  public final static native long Type_attributes(long jarg1, Type jarg1_);
  public final static native long Type_parent(long jarg1, Type jarg1_);
  public final static native int Charge_size(long jarg1, Charge jarg1_);
  public final static native void delete_Charge(long jarg1);
  public final static native int Module_anySocket_get();
  public final static native boolean Module_canHaveState(long jarg1, Module jarg1_, int jarg2);
  public final static native long Module_availableStates(long jarg1, Module jarg1_);
  public final static native int Module_state__SWIG_0(long jarg1, Module jarg1_);
  public final static native int Module_preferredState(long jarg1, Module jarg1_);
  public final static native void Module_state__SWIG_1(long jarg1, Module jarg1_, int jarg2);
  public final static native long Module_target__SWIG_0(long jarg1, Module jarg1_);
  public final static native void Module_target__SWIG_1(long jarg1, Module jarg1_, long jarg2, Ship jarg2_);
  public final static native int Module_slot(long jarg1, Module jarg1_);
  public final static native int Module_hardpoint(long jarg1, Module jarg1_);
  public final static native int Module_socket(long jarg1, Module jarg1_);
  public final static native long Module_charge__SWIG_0(long jarg1, Module jarg1_);
  public final static native long Module_charge__SWIG_1(long jarg1, Module jarg1_, int jarg2);
  public final static native void Module_clearCharge(long jarg1, Module jarg1_);
  public final static native boolean Module_canFit(long jarg1, Module jarg1_, long jarg2, Charge jarg2_);
  public final static native long Module_chargeGroups(long jarg1, Module jarg1_);
  public final static native int Module_chargeSize(long jarg1, Module jarg1_);
  public final static native boolean Module_requireTarget(long jarg1, Module jarg1_);
  public final static native boolean Module_fail(long jarg1, Module jarg1_);
  public final static native long Module_charges(long jarg1, Module jarg1_);
  public final static native long Module_shots(long jarg1, Module jarg1_);
  public final static native long Module_capUse(long jarg1, Module jarg1_);
  public final static native double Module_cpuUse(long jarg1, Module jarg1_);
  public final static native double Module_powerGridUse(long jarg1, Module jarg1_);
  public final static native double Module_calibrationUse(long jarg1, Module jarg1_);
  public final static native double Module_accuracyScore(long jarg1, Module jarg1_);
  public final static native double Module_signatureResolution(long jarg1, Module jarg1_);
  public final static native long Module_miningYield(long jarg1, Module jarg1_);
  public final static native long Module_volley(long jarg1, Module jarg1_);
  public final static native long Module_dps(long jarg1, Module jarg1_);
  public final static native double Module_optimal(long jarg1, Module jarg1_);
  public final static native double Module_falloff(long jarg1, Module jarg1_);
  public final static native double Module_reloadTime(long jarg1, Module jarg1_);
  public final static native double Module_cycleTime(long jarg1, Module jarg1_);
  public final static native double Module_rawCycleTime(long jarg1, Module jarg1_);
  public final static native double Module_lifeTime(long jarg1, Module jarg1_);
  public final static native void delete_Module(long jarg1);
  public final static native long new_GroupIDs__SWIG_0();
  public final static native long new_GroupIDs__SWIG_1(long jarg1);
  public final static native long GroupIDs_size(long jarg1, GroupIDs jarg1_);
  public final static native long GroupIDs_capacity(long jarg1, GroupIDs jarg1_);
  public final static native void GroupIDs_reserve(long jarg1, GroupIDs jarg1_, long jarg2);
  public final static native boolean GroupIDs_isEmpty(long jarg1, GroupIDs jarg1_);
  public final static native void GroupIDs_clear(long jarg1, GroupIDs jarg1_);
  public final static native void GroupIDs_add(long jarg1, GroupIDs jarg1_, int jarg2);
  public final static native int GroupIDs_get(long jarg1, GroupIDs jarg1_, int jarg2);
  public final static native void GroupIDs_set(long jarg1, GroupIDs jarg1_, int jarg2, int jarg3);
  public final static native void delete_GroupIDs(long jarg1);
  public final static native long new_States__SWIG_0();
  public final static native long new_States__SWIG_1(long jarg1);
  public final static native long States_size(long jarg1, States jarg1_);
  public final static native long States_capacity(long jarg1, States jarg1_);
  public final static native void States_reserve(long jarg1, States jarg1_, long jarg2);
  public final static native boolean States_isEmpty(long jarg1, States jarg1_);
  public final static native void States_clear(long jarg1, States jarg1_);
  public final static native void States_add(long jarg1, States jarg1_, int jarg2);
  public final static native int States_get(long jarg1, States jarg1_, int jarg2);
  public final static native void States_set(long jarg1, States jarg1_, int jarg2, int jarg3);
  public final static native void delete_States(long jarg1);
  public final static native int Drone_anySquadronTag_get();
  public final static native void Drone_active__SWIG_0(long jarg1, Drone jarg1_, boolean jarg2);
  public final static native boolean Drone_active__SWIG_1(long jarg1, Drone jarg1_);
  public final static native boolean Drone_hasKamikazeAbility(long jarg1, Drone jarg1_);
  public final static native void Drone_kamikaze__SWIG_0(long jarg1, Drone jarg1_, boolean jarg2);
  public final static native boolean Drone_kamikaze__SWIG_1(long jarg1, Drone jarg1_);
  public final static native long Drone_charge(long jarg1, Drone jarg1_);
  public final static native int Drone_squadron(long jarg1, Drone jarg1_);
  public final static native long Drone_squadronSize(long jarg1, Drone jarg1_);
  public final static native int Drone_squadronTag(long jarg1, Drone jarg1_);
  public final static native long Drone_target__SWIG_0(long jarg1, Drone jarg1_);
  public final static native void Drone_target__SWIG_1(long jarg1, Drone jarg1_, long jarg2, Ship jarg2_);
  public final static native long Drone_volley(long jarg1, Drone jarg1_);
  public final static native long Drone_dps(long jarg1, Drone jarg1_);
  public final static native double Drone_optimal(long jarg1, Drone jarg1_);
  public final static native double Drone_falloff(long jarg1, Drone jarg1_);
  public final static native double Drone_accuracyScore(long jarg1, Drone jarg1_);
  public final static native long Drone_miningYield(long jarg1, Drone jarg1_);
  public final static native long Drone_velocity(long jarg1, Drone jarg1_);
  public final static native double Drone_cycleTime(long jarg1, Drone jarg1_);
  public final static native void delete_Drone(long jarg1);
  public final static native void delete_Area(long jarg1);
  public final static native long new_CategoryIDs__SWIG_0();
  public final static native long new_CategoryIDs__SWIG_1(long jarg1);
  public final static native long CategoryIDs_size(long jarg1, CategoryIDs jarg1_);
  public final static native long CategoryIDs_capacity(long jarg1, CategoryIDs jarg1_);
  public final static native void CategoryIDs_reserve(long jarg1, CategoryIDs jarg1_, long jarg2);
  public final static native boolean CategoryIDs_isEmpty(long jarg1, CategoryIDs jarg1_);
  public final static native void CategoryIDs_clear(long jarg1, CategoryIDs jarg1_);
  public final static native void CategoryIDs_add(long jarg1, CategoryIDs jarg1_, int jarg2);
  public final static native int CategoryIDs_get(long jarg1, CategoryIDs jarg1_, int jarg2);
  public final static native void CategoryIDs_set(long jarg1, CategoryIDs jarg1_, int jarg2, int jarg3);
  public final static native void delete_CategoryIDs(long jarg1);
  public final static native long new_Modules__SWIG_0();
  public final static native long new_Modules__SWIG_1(long jarg1);
  public final static native long Modules_size(long jarg1, Modules jarg1_);
  public final static native long Modules_capacity(long jarg1, Modules jarg1_);
  public final static native void Modules_reserve(long jarg1, Modules jarg1_, long jarg2);
  public final static native boolean Modules_isEmpty(long jarg1, Modules jarg1_);
  public final static native void Modules_clear(long jarg1, Modules jarg1_);
  public final static native void Modules_add(long jarg1, Modules jarg1_, long jarg2, Module jarg2_);
  public final static native long Modules_get(long jarg1, Modules jarg1_, int jarg2);
  public final static native void Modules_set(long jarg1, Modules jarg1_, int jarg2, long jarg3, Module jarg3_);
  public final static native void delete_Modules(long jarg1);
  public final static native long new_Drones__SWIG_0();
  public final static native long new_Drones__SWIG_1(long jarg1);
  public final static native long Drones_size(long jarg1, Drones jarg1_);
  public final static native long Drones_capacity(long jarg1, Drones jarg1_);
  public final static native void Drones_reserve(long jarg1, Drones jarg1_, long jarg2);
  public final static native boolean Drones_isEmpty(long jarg1, Drones jarg1_);
  public final static native void Drones_clear(long jarg1, Drones jarg1_);
  public final static native void Drones_add(long jarg1, Drones jarg1_, long jarg2, Drone jarg2_);
  public final static native long Drones_get(long jarg1, Drones jarg1_, int jarg2);
  public final static native void Drones_set(long jarg1, Drones jarg1_, int jarg2, long jarg3, Drone jarg3_);
  public final static native void delete_Drones(long jarg1);
  public final static native double Capacitor_capacity(long jarg1, Capacitor jarg1_);
  public final static native boolean Capacitor_isStable(long jarg1, Capacitor jarg1_);
  public final static native double Capacitor_stableLevel(long jarg1, Capacitor jarg1_);
  public final static native double Capacitor_rechargeTime(long jarg1, Capacitor jarg1_);
  public final static native double Capacitor_lastsTime(long jarg1, Capacitor jarg1_);
  public final static native long Capacitor_use(long jarg1, Capacitor jarg1_);
  public final static native long Capacitor_recharge(long jarg1, Capacitor jarg1_);
  public final static native void delete_Capacitor(long jarg1);
  public final static native long Ship_supportedDroneCategories(long jarg1, Ship jarg1_);
  public final static native int Ship_rigSize(long jarg1, Ship jarg1_);
  public final static native void Ship_damagePattern__SWIG_0(long jarg1, Ship jarg1_, long jarg2, DamageVector jarg2_);
  public final static native long Ship_damagePattern__SWIG_1(long jarg1, Ship jarg1_);
  public final static native long Ship_addModule__SWIG_0(long jarg1, Ship jarg1_, int jarg2, int jarg3, boolean jarg4);
  public final static native long Ship_addModule__SWIG_1(long jarg1, Ship jarg1_, int jarg2, int jarg3);
  public final static native long Ship_addModule__SWIG_2(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_addDrone__SWIG_0(long jarg1, Ship jarg1_, int jarg2, int jarg3);
  public final static native long Ship_addDrone__SWIG_1(long jarg1, Ship jarg1_, int jarg2);
  public final static native void Ship_remove__SWIG_0(long jarg1, Ship jarg1_, long jarg2, Module jarg2_);
  public final static native void Ship_remove__SWIG_1(long jarg1, Ship jarg1_, long jarg2, Drone jarg2_);
  public final static native boolean Ship_canFit__SWIG_0(long jarg1, Ship jarg1_, long jarg2, Module jarg2_);
  public final static native boolean Ship_canFit__SWIG_1(long jarg1, Ship jarg1_, long jarg2, Drone jarg2_);
  public final static native long Ship_modules__SWIG_0(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_modules__SWIG_1(long jarg1, Ship jarg1_);
  public final static native long Ship_drones(long jarg1, Ship jarg1_);
  public final static native long Ship_totalDroneSquadron__SWIG_0(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_totalDroneSquadron__SWIG_1(long jarg1, Ship jarg1_);
  public final static native long Ship_usedDroneSquadron__SWIG_0(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_usedDroneSquadron__SWIG_1(long jarg1, Ship jarg1_);
  public final static native long Ship_totalFighterLaunchTubes(long jarg1, Ship jarg1_);
  public final static native long Ship_usedFighterLaunchTubes(long jarg1, Ship jarg1_);
  public final static native long Ship_totalSlots(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_freeSlots(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_usedSlots(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_totalHardpoints(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_freeHardpoints(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_usedHardpoints(long jarg1, Ship jarg1_, int jarg2);
  public final static native long Ship_capacitor(long jarg1, Ship jarg1_);
  public final static native double Ship_usedCalibration(long jarg1, Ship jarg1_);
  public final static native double Ship_totalCalibration(long jarg1, Ship jarg1_);
  public final static native double Ship_usedPowerGrid(long jarg1, Ship jarg1_);
  public final static native double Ship_totalPowerGrid(long jarg1, Ship jarg1_);
  public final static native double Ship_usedCPU(long jarg1, Ship jarg1_);
  public final static native double Ship_totalCPU(long jarg1, Ship jarg1_);
  public final static native double Ship_usedDroneBandwidth(long jarg1, Ship jarg1_);
  public final static native double Ship_totalDroneBandwidth(long jarg1, Ship jarg1_);
  public final static native double Ship_usedDroneBay(long jarg1, Ship jarg1_);
  public final static native double Ship_totalDroneBay(long jarg1, Ship jarg1_);
  public final static native double Ship_usedFighterHangar(long jarg1, Ship jarg1_);
  public final static native double Ship_totalFighterHangar(long jarg1, Ship jarg1_);
  public final static native double Ship_cargoCapacity(long jarg1, Ship jarg1_);
  public final static native double Ship_specialHoldCapacity(long jarg1, Ship jarg1_);
  public final static native long Ship_resistances(long jarg1, Ship jarg1_);
  public final static native long Ship_tank(long jarg1, Ship jarg1_);
  public final static native long Ship_effectiveTank(long jarg1, Ship jarg1_);
  public final static native long Ship_sustainableTank(long jarg1, Ship jarg1_);
  public final static native long Ship_effectiveSustainableTank(long jarg1, Ship jarg1_);
  public final static native long Ship_hitPoints(long jarg1, Ship jarg1_);
  public final static native long Ship_effectiveHitPoints(long jarg1, Ship jarg1_);
  public final static native long Ship_turretsVolley(long jarg1, Ship jarg1_);
  public final static native long Ship_launchersVolley(long jarg1, Ship jarg1_);
  public final static native long Ship_dronesVolley(long jarg1, Ship jarg1_);
  public final static native long Ship_turretsDPS(long jarg1, Ship jarg1_);
  public final static native long Ship_launchersDPS(long jarg1, Ship jarg1_);
  public final static native long Ship_dronesDPS(long jarg1, Ship jarg1_);
  public final static native long Ship_minerYield(long jarg1, Ship jarg1_);
  public final static native long Ship_droneYield(long jarg1, Ship jarg1_);
  public final static native double Ship_alignTime(long jarg1, Ship jarg1_);
  public final static native long Ship_warpSpeed(long jarg1, Ship jarg1_);
  public final static native double Ship_maxWarpDistance(long jarg1, Ship jarg1_);
  public final static native long Ship_velocity(long jarg1, Ship jarg1_);
  public final static native double Ship_signatureRadius(long jarg1, Ship jarg1_);
  public final static native double Ship_mass(long jarg1, Ship jarg1_);
  public final static native double Ship_volume(long jarg1, Ship jarg1_);
  public final static native double Ship_agility(long jarg1, Ship jarg1_);
  public final static native long Ship_maxVelocityInOrbit(long jarg1, Ship jarg1_, double jarg2);
  public final static native double Ship_orbitRadiusWithTransverseVelocity(long jarg1, Ship jarg1_, long jarg2, UnitsPerSecond jarg2_);
  public final static native double Ship_orbitRadiusWithAngularVelocity(long jarg1, Ship jarg1_, long jarg2, UnitsPerSecond jarg2_);
  public final static native long Ship_maxTargets(long jarg1, Ship jarg1_);
  public final static native double Ship_maxTargetRange(long jarg1, Ship jarg1_);
  public final static native double Ship_scanStrength(long jarg1, Ship jarg1_);
  public final static native int Ship_scanType(long jarg1, Ship jarg1_);
  public final static native double Ship_probeSize(long jarg1, Ship jarg1_);
  public final static native double Ship_scanResolution(long jarg1, Ship jarg1_);
  public final static native void delete_Ship(long jarg1);
  public final static native long new_Characters__SWIG_0();
  public final static native long new_Characters__SWIG_1(long jarg1);
  public final static native long Characters_size(long jarg1, Characters jarg1_);
  public final static native long Characters_capacity(long jarg1, Characters jarg1_);
  public final static native void Characters_reserve(long jarg1, Characters jarg1_, long jarg2);
  public final static native boolean Characters_isEmpty(long jarg1, Characters jarg1_);
  public final static native void Characters_clear(long jarg1, Characters jarg1_);
  public final static native void Characters_add(long jarg1, Characters jarg1_, long jarg2, Character jarg2_);
  public final static native long Characters_get(long jarg1, Characters jarg1_, int jarg2);
  public final static native void Characters_set(long jarg1, Characters jarg1_, int jarg2, long jarg3, Character jarg3_);
  public final static native void delete_Characters(long jarg1);
  public final static native long new_Implants__SWIG_0();
  public final static native long new_Implants__SWIG_1(long jarg1);
  public final static native long Implants_size(long jarg1, Implants jarg1_);
  public final static native long Implants_capacity(long jarg1, Implants jarg1_);
  public final static native void Implants_reserve(long jarg1, Implants jarg1_, long jarg2);
  public final static native boolean Implants_isEmpty(long jarg1, Implants jarg1_);
  public final static native void Implants_clear(long jarg1, Implants jarg1_);
  public final static native void Implants_add(long jarg1, Implants jarg1_, long jarg2, Implant jarg2_);
  public final static native long Implants_get(long jarg1, Implants jarg1_, int jarg2);
  public final static native void Implants_set(long jarg1, Implants jarg1_, int jarg2, long jarg3, Implant jarg3_);
  public final static native void delete_Implants(long jarg1);
  public final static native long new_Boosters__SWIG_0();
  public final static native long new_Boosters__SWIG_1(long jarg1);
  public final static native long Boosters_size(long jarg1, Boosters jarg1_);
  public final static native long Boosters_capacity(long jarg1, Boosters jarg1_);
  public final static native void Boosters_reserve(long jarg1, Boosters jarg1_, long jarg2);
  public final static native boolean Boosters_isEmpty(long jarg1, Boosters jarg1_);
  public final static native void Boosters_clear(long jarg1, Boosters jarg1_);
  public final static native void Boosters_add(long jarg1, Boosters jarg1_, long jarg2, Booster jarg2_);
  public final static native long Boosters_get(long jarg1, Boosters jarg1_, int jarg2);
  public final static native void Boosters_set(long jarg1, Boosters jarg1_, int jarg2, long jarg3, Booster jarg3_);
  public final static native void delete_Boosters(long jarg1);
  public final static native long new_Skills__SWIG_0();
  public final static native long new_Skills__SWIG_1(long jarg1);
  public final static native long Skills_size(long jarg1, Skills jarg1_);
  public final static native long Skills_capacity(long jarg1, Skills jarg1_);
  public final static native void Skills_reserve(long jarg1, Skills jarg1_, long jarg2);
  public final static native boolean Skills_isEmpty(long jarg1, Skills jarg1_);
  public final static native void Skills_clear(long jarg1, Skills jarg1_);
  public final static native void Skills_add(long jarg1, Skills jarg1_, long jarg2, Skill jarg2_);
  public final static native long Skills_get(long jarg1, Skills jarg1_, int jarg2);
  public final static native void Skills_set(long jarg1, Skills jarg1_, int jarg2, long jarg3, Skill jarg3_);
  public final static native void delete_Skills(long jarg1);
  public final static native int Implant_slot(long jarg1, Implant jarg1_);
  public final static native void delete_Implant(long jarg1);
  public final static native int Booster_slot(long jarg1, Booster jarg1_);
  public final static native void delete_Booster(long jarg1);
  public final static native int Skill_level__SWIG_0(long jarg1, Skill jarg1_);
  public final static native void Skill_level__SWIG_1(long jarg1, Skill jarg1_, int jarg2);
  public final static native void delete_Skill(long jarg1);
  public final static native long Character_ship__SWIG_0(long jarg1, Character jarg1_);
  public final static native long Character_ship__SWIG_1(long jarg1, Character jarg1_, int jarg2);
  public final static native void Character_setSkillLevels(long jarg1, Character jarg1_, int jarg2);
  public final static native long Character_addImplant__SWIG_0(long jarg1, Character jarg1_, int jarg2, boolean jarg3);
  public final static native long Character_addImplant__SWIG_1(long jarg1, Character jarg1_, int jarg2);
  public final static native long Character_addBooster__SWIG_0(long jarg1, Character jarg1_, int jarg2, boolean jarg3);
  public final static native long Character_addBooster__SWIG_1(long jarg1, Character jarg1_, int jarg2);
  public final static native void Character_remove__SWIG_0(long jarg1, Character jarg1_, long jarg2, Implant jarg2_);
  public final static native void Character_remove__SWIG_1(long jarg1, Character jarg1_, long jarg2, Booster jarg2_);
  public final static native long Character_skills(long jarg1, Character jarg1_);
  public final static native long Character_implants(long jarg1, Character jarg1_);
  public final static native long Character_boosters(long jarg1, Character jarg1_);
  public final static native long Character_implant(long jarg1, Character jarg1_, int jarg2);
  public final static native long Character_booster(long jarg1, Character jarg1_, int jarg2);
  public final static native double Character_droneControlDistance(long jarg1, Character jarg1_);
  public final static native void delete_Character(long jarg1);
  public final static native long new_Gang();
  public final static native long Gang_addPilot(long jarg1, Gang jarg1_);
  public final static native void Gang_remove(long jarg1, Gang jarg1_, long jarg2, Character jarg2_);
  public final static native long Gang_pilots(long jarg1, Gang jarg1_);
  public final static native boolean Gang_factorReload__SWIG_0(long jarg1, Gang jarg1_);
  public final static native void Gang_factorReload__SWIG_1(long jarg1, Gang jarg1_, boolean jarg2);
  public final static native long Gang_area__SWIG_0(long jarg1, Gang jarg1_);
  public final static native long Gang_area__SWIG_1(long jarg1, Gang jarg1_, int jarg2);
  public final static native void delete_Gang(long jarg1);
  public final static native long Charge_SWIGUpcast(long jarg1);
  public final static native long Module_SWIGUpcast(long jarg1);
  public final static native long Drone_SWIGUpcast(long jarg1);
  public final static native long Area_SWIGUpcast(long jarg1);
  public final static native long Ship_SWIGUpcast(long jarg1);
  public final static native long Implant_SWIGUpcast(long jarg1);
  public final static native long Booster_SWIGUpcast(long jarg1);
  public final static native long Skill_SWIGUpcast(long jarg1);
  public final static native long Character_SWIGUpcast(long jarg1);
  public final static native long Gang_SWIGUpcast(long jarg1);
}
