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

public class OStream : IDisposable {
	private HandleRef swigCPtr;
	protected bool swigCMemOwn;
	
	internal OStream(IntPtr cPtr, bool cMemoryOwn)
	{
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(OStream obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (OStream obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~OStream() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_OStream(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public OStream(int sot) : this(libsbmlPINVOKE.new_OStream__SWIG_0(sot), true) {
  }

  public OStream() : this(libsbmlPINVOKE.new_OStream__SWIG_1(), true) {
  }

  public virtual SWIGTYPE_p_std__ostream get_ostream() {
    IntPtr cPtr = libsbmlPINVOKE.OStream_get_ostream(swigCPtr);
    SWIGTYPE_p_std__ostream ret = (cPtr == IntPtr.Zero) ? null : new SWIGTYPE_p_std__ostream(cPtr, false);
    return ret;
  }

  public void endl() {
    libsbmlPINVOKE.OStream_endl(swigCPtr);
  }

  // StdOSType 
  public const int COUT = 0;
  public const int CERR = COUT + 1;
  public const int CLOG = CERR + 1;

}

}
