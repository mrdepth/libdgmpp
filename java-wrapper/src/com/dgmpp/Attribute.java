/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Attribute {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Attribute(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Attribute obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Attribute(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public int attributeID() {
    return dgmppJNI.Attribute_attributeID(swigCPtr, this);
  }

  public Type owner() {
    return new Type(dgmppJNI.Attribute_owner(swigCPtr, this), false);
  }

  public double value() {
    return dgmppJNI.Attribute_value(swigCPtr, this);
  }

  public double initialValue() {
    return dgmppJNI.Attribute_initialValue(swigCPtr, this);
  }

}
