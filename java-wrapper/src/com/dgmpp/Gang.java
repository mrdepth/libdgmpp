/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Gang extends Type {
  private transient long swigCPtr;

  protected Gang(long cPtr, boolean cMemoryOwn) {
    super(dgmppJNI.Gang_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Gang obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Gang(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public Gang() {
    this(dgmppJNI.new_Gang(), true);
  }

  public Character addPilot() {
    long cPtr = dgmppJNI.Gang_addPilot(swigCPtr, this);
    return (cPtr == 0) ? null : new Character(cPtr, false);
  }

  public void remove(Character pilot) {
    dgmppJNI.Gang_remove(swigCPtr, this, Character.getCPtr(pilot), pilot);
  }

  public Characters pilots() {
    return new Characters(dgmppJNI.Gang_pilots(swigCPtr, this), true);
  }

  public boolean factorReload() {
    return dgmppJNI.Gang_factorReload__SWIG_0(swigCPtr, this);
  }

  public void factorReload(boolean factorReload) {
    dgmppJNI.Gang_factorReload__SWIG_1(swigCPtr, this, factorReload);
  }

  public Area area() {
    long cPtr = dgmppJNI.Gang_area__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new Area(cPtr, false);
  }

  public Area area(int typeID) {
    long cPtr = dgmppJNI.Gang_area__SWIG_1(swigCPtr, this, typeID);
    return (cPtr == 0) ? null : new Area(cPtr, false);
  }

}
