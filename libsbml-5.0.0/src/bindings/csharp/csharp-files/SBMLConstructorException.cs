/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace libsbmlcs {

using System;
using System.Runtime.InteropServices;

public class SBMLConstructorException : System.ArgumentException, IDisposable {
	private HandleRef swigCPtr;
	protected bool swigCMemOwn;
	
	internal SBMLConstructorException(IntPtr cPtr, bool cMemoryOwn)
	{
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(SBMLConstructorException obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (SBMLConstructorException obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~SBMLConstructorException() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_SBMLConstructorException(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  internal SBMLConstructorException(IntPtr cPtr, bool cMemoryOwn, string v) : base(v)
  {
    swigCMemOwn = cMemoryOwn;
    swigCPtr    = new HandleRef(this, cPtr);
  }

  public SBMLConstructorException(string v) : 
   this(libsbmlPINVOKE.new_SBMLConstructorException(), true, v) 
  {}

  public SBMLConstructorException() : this(libsbmlPINVOKE.new_SBMLConstructorException(), true) {
  }

  public string getSBMLErrMsg() {
    string ret = libsbmlPINVOKE.SBMLConstructorException_getSBMLErrMsg(swigCPtr);
    return ret;
  }

}

}
