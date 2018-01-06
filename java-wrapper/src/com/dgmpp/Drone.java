/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Drone extends Type {
  private transient long swigCPtr;

  protected Drone(long cPtr, boolean cMemoryOwn) {
    super(dgmppJNI.Drone_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Drone obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Drone(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public static int getAnySquadronTag() {
    return dgmppJNI.Drone_anySquadronTag_get();
  }

  public void active(boolean active) {
    dgmppJNI.Drone_active__SWIG_0(swigCPtr, this, active);
  }

  public boolean active() {
    return dgmppJNI.Drone_active__SWIG_1(swigCPtr, this);
  }

  public Charge charge() {
    long cPtr = dgmppJNI.Drone_charge(swigCPtr, this);
    return (cPtr == 0) ? null : new Charge(cPtr, false);
  }

  public int squadron() {
    return dgmppJNI.Drone_squadron(swigCPtr, this);
  }

  public long squadronSize() {
    return dgmppJNI.Drone_squadronSize(swigCPtr, this);
  }

  public int squadronTag() {
    return dgmppJNI.Drone_squadronTag(swigCPtr, this);
  }

  public Ship target() {
    long cPtr = dgmppJNI.Drone_target__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Ship(cPtr, false);
  }

  public void target(Ship target) {
    dgmppJNI.Drone_target__SWIG_1(swigCPtr, this, Ship.getCPtr(target), target);
  }

  public DamageVector volley() {
    return new DamageVector(dgmppJNI.Drone_volley(swigCPtr, this), true);
  }

  public DamagePerSecond dps() {
    return new DamagePerSecond(dgmppJNI.Drone_dps(swigCPtr, this), true);
  }

  public double optimal() {
    return dgmppJNI.Drone_optimal(swigCPtr, this);
  }

  public double falloff() {
    return dgmppJNI.Drone_falloff(swigCPtr, this);
  }

  public double accuracyScore() {
    return dgmppJNI.Drone_accuracyScore(swigCPtr, this);
  }

  public UnitsPerSecond miningYield() {
    return new UnitsPerSecond(dgmppJNI.Drone_miningYield(swigCPtr, this), true);
  }

  public UnitsPerSecond velocity() {
    return new UnitsPerSecond(dgmppJNI.Drone_velocity(swigCPtr, this), true);
  }

  public double cycleTime() {
    return dgmppJNI.Drone_cycleTime(swigCPtr, this);
  }

  public final static class Squadron {
    public final static int none = 0;
    public final static int heavy = none + 1;
    public final static int light = heavy + 1;
    public final static int support = light + 1;
  }

}
