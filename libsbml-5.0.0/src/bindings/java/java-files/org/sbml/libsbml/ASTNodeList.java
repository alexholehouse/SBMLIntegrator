/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

public class ASTNodeList {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  public ASTNodeList(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  public static long getCPtr(ASTNodeList obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        libsbmlJNI.delete_ASTNodeList(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public ASTNodeList() {
    this(libsbmlJNI.new_ASTNodeList(), true);
  }

  public void add(ASTNode item) {
    libsbmlJNI.ASTNodeList_add(swigCPtr, this, ASTNode.getCPtr(item), item);
  }

  public ASTNode get(long n) {
    long cPtr = libsbmlJNI.ASTNodeList_get(swigCPtr, this, n);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  public void prepend(ASTNode item) {
    libsbmlJNI.ASTNodeList_prepend(swigCPtr, this, ASTNode.getCPtr(item), item);
  }

  public ASTNode remove(long n) {
    long cPtr = libsbmlJNI.ASTNodeList_remove(swigCPtr, this, n);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  public long getSize() {
    return libsbmlJNI.ASTNodeList_getSize(swigCPtr, this);
  }

}