/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Module extends Type {
  private transient long swigCPtr;

  protected Module(long cPtr, boolean cMemoryOwn) {
    super(dgmppJNI.Module_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Module obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Module(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static int getAnySocket() {
    return dgmppJNI.Module_anySocket_get();
  }

  public static Module Create(int typeID) {
     long cPtr = dgmppJNI.Module_Create(typeID);
     return (cPtr == 0) ? null : new Module(cPtr, true);
   }

  public boolean canHaveState(int state) {
    return dgmppJNI.Module_canHaveState(swigCPtr, this, state);
  }

  public States availableStates() {
    return new States(dgmppJNI.Module_availableStates(swigCPtr, this), true);
  }

  public int state() {
    return dgmppJNI.Module_state__SWIG_0(swigCPtr, this);
  }

  public int preferredState() {
    return dgmppJNI.Module_preferredState(swigCPtr, this);
  }

  public void state(int state) {
    dgmppJNI.Module_state__SWIG_1(swigCPtr, this, state);
  }

  public Ship target() {
    long cPtr = dgmppJNI.Module_target__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Ship(cPtr, false);
  }

  public void target(Ship target) {
    dgmppJNI.Module_target__SWIG_1(swigCPtr, this, Ship.getCPtr(target), target);
  }

  public int slot() {
    return dgmppJNI.Module_slot(swigCPtr, this);
  }

  public int hardpoint() {
    return dgmppJNI.Module_hardpoint(swigCPtr, this);
  }

  public int socket() {
    return dgmppJNI.Module_socket(swigCPtr, this);
  }

  public Charge charge() {
    long cPtr = dgmppJNI.Module_charge__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Charge(cPtr, false);
  }

  public Charge charge(int typeID) {
    long cPtr = dgmppJNI.Module_charge__SWIG_1(swigCPtr, this, typeID);
    return (cPtr == 0) ? null : new Charge(cPtr, false);
  }

  public boolean canFit(Charge charge) {
    return dgmppJNI.Module_canFit(swigCPtr, this, Charge.getCPtr(charge), charge);
  }

  public GroupIDs chargeGroups() {
    return new GroupIDs(dgmppJNI.Module_chargeGroups(swigCPtr, this), false);
  }

  public int chargeSize() {
    return dgmppJNI.Module_chargeSize(swigCPtr, this);
  }

  public boolean requireTarget() {
    return dgmppJNI.Module_requireTarget(swigCPtr, this);
  }

  public boolean fail() {
    return dgmppJNI.Module_fail(swigCPtr, this);
  }

  public long charges() {
    return dgmppJNI.Module_charges(swigCPtr, this);
  }

  public long shots() {
    return dgmppJNI.Module_shots(swigCPtr, this);
  }

  public UnitsPerSecond capUse() {
    return new UnitsPerSecond(dgmppJNI.Module_capUse(swigCPtr, this), true);
  }

  public double cpuUse() {
    return dgmppJNI.Module_cpuUse(swigCPtr, this);
  }

  public double powerGridUse() {
    return dgmppJNI.Module_powerGridUse(swigCPtr, this);
  }

  public double calibrationUse() {
    return dgmppJNI.Module_calibrationUse(swigCPtr, this);
  }

  public double accuracyScore() {
    return dgmppJNI.Module_accuracyScore(swigCPtr, this);
  }

  public double signatureResolution() {
    return dgmppJNI.Module_signatureResolution(swigCPtr, this);
  }

  public UnitsPerSecond miningYield() {
    return new UnitsPerSecond(dgmppJNI.Module_miningYield(swigCPtr, this), true);
  }

  public DamageVector volley() {
    return new DamageVector(dgmppJNI.Module_volley(swigCPtr, this), true);
  }

  public DamagePerSecond dps() {
    return new DamagePerSecond(dgmppJNI.Module_dps(swigCPtr, this), true);
  }

  public double optimal() {
    return dgmppJNI.Module_optimal(swigCPtr, this);
  }

  public double falloff() {
    return dgmppJNI.Module_falloff(swigCPtr, this);
  }

  public double reloadTime() {
    return dgmppJNI.Module_reloadTime(swigCPtr, this);
  }

  public double cycleTime() {
    return dgmppJNI.Module_cycleTime(swigCPtr, this);
  }

  public double rawCycleTime() {
    return dgmppJNI.Module_rawCycleTime(swigCPtr, this);
  }

  public double lifeTime() {
    return dgmppJNI.Module_lifeTime(swigCPtr, this);
  }

  public final static class State {
    public final static int unknown = -1;
    public final static int offline = unknown + 1;
    public final static int online = offline + 1;
    public final static int active = online + 1;
    public final static int overloaded = active + 1;
  }

  public final static class Slot {
    public final static int none = 0;
    public final static int hi = none + 1;
    public final static int med = hi + 1;
    public final static int low = med + 1;
    public final static int rig = low + 1;
    public final static int subsystem = rig + 1;
    public final static int mode = subsystem + 1;
    public final static int service = mode + 1;
    public final static int starbaseStructure = service + 1;
  }

  public final static class Hardpoint {
    public final static int none = 0;
    public final static int launcher = none + 1;
    public final static int turret = launcher + 1;
  }

}
