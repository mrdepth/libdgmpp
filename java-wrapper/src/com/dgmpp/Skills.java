/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Skills {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected Skills(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Skills obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Skills(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public Skills() {
    this(dgmppJNI.new_Skills__SWIG_0(), true);
  }

  public Skills(long n) {
    this(dgmppJNI.new_Skills__SWIG_1(n), true);
  }

  public long size() {
    return dgmppJNI.Skills_size(swigCPtr, this);
  }

  public long capacity() {
    return dgmppJNI.Skills_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    dgmppJNI.Skills_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return dgmppJNI.Skills_isEmpty(swigCPtr, this);
  }

  public void clear() {
    dgmppJNI.Skills_clear(swigCPtr, this);
  }

  public void add(Skill x) {
    dgmppJNI.Skills_add(swigCPtr, this, Skill.getCPtr(x), x);
  }

  public Skill get(int i) {
    long cPtr = dgmppJNI.Skills_get(swigCPtr, this, i);
    return (cPtr == 0) ? null : new Skill(cPtr, false);
  }

  public void set(int i, Skill val) {
    dgmppJNI.Skills_set(swigCPtr, this, i, Skill.getCPtr(val), val);
  }

}
