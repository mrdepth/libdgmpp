/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.dgmpp;

public class Skill extends Type {
  private transient long swigCPtr;

  protected Skill(long cPtr, boolean cMemoryOwn) {
    super(dgmppJNI.Skill_SWIGUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  protected static long getCPtr(Skill obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        dgmppJNI.delete_Skill(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public int level() {
    return dgmppJNI.Skill_level__SWIG_0(swigCPtr, this);
  }

  public void level(int level) {
    dgmppJNI.Skill_level__SWIG_1(swigCPtr, this, level);
  }

}
