/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace libsbml {

 using System;
 using System.Runtime.InteropServices;

/** 
 * LibSBML implementation of SBML's %ListOfUnits construct.
 * 
 * The various ListOf___ classes in %SBML are merely containers used for
 * organizing the main components of an %SBML model.  All are derived from
 * the abstract class SBase, and inherit the various attributes and
 * subelements of SBase, such as 'metaid' as and 'annotation'.  The
 * ListOf___ classes do not add any attributes of their own.
 *
 * ListOfUnits is entirely contained within UnitDefinition.
 */
public class ListOfUnits : ListOf {
	private HandleRef swigCPtr;
	
	internal ListOfUnits(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.ListOfUnits_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.ListOfUnitsUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(ListOfUnits obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (ListOfUnits obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~ListOfUnits() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_ListOfUnits(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  
  /**
   * Creates a new ListOfUnits object.
   *
   * The object is constructed such that it is valid for the given SBML
   * Level and Version combination.
   *
   * @param level the SBML Level
   * 
   * @param version the Version within the SBML Level
   */
 public ListOfUnits(long level, long version) : this(libsbmlPINVOKE.new_ListOfUnits__SWIG_0(level, version), true) {
  }

  
  /**
   * Creates a new ListOfUnits object.
   *
   * The object is constructed such that it is valid for the SBML Level and
   * Version combination determined by the SBMLNamespaces object in @p
   * sbmlns.
   *
   * @param sbmlns an SBMLNamespaces object that is used to determine the
   * characteristics of the ListOfUnits object to be created.
   */
 public ListOfUnits(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_ListOfUnits__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
  }

  
  /**
   * Creates and returns a deep copy of this ListOfUnits.
   *
   * @return a (deep) copy of this ListOfUnits.
   */
 public new ListOfUnits clone() {
    IntPtr cPtr = libsbmlPINVOKE.ListOfUnits_clone(swigCPtr);
    ListOfUnits ret = (cPtr == IntPtr.Zero) ? null : new ListOfUnits(cPtr, true);
    return ret;
  }

  
  /**
   * Returns the libSBML type code for this %SBML object.
   * 
   * @if clike LibSBML attaches an identifying code to every kind of SBML
   * object.  These are known as <em>SBML type codes</em>.  The set of
   * possible type codes is defined in the enumeration #SBMLTypeCode_t.
   * The names of the type codes all begin with the characters @c
   * SBML_. @endif@if java LibSBML attaches an identifying code to every
   * kind of SBML object.  These are known as <em>SBML type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libSBML, the type codes are defined as
   * static integer constants in the interface class {@link
   * libsbmlcs.libsbml}.  The names of the type codes all begin with the
   * characters @c SBML_. @endif@if python LibSBML attaches an identifying
   * code to every kind of SBML object.  These are known as <em>SBML type
   * codes</em>.  In the Python language interface for libSBML, the type
   * codes are defined as static integer constants in the interface class
   * @link libsbml@endlink.  The names of the type codes all begin with the
   * characters @c SBML_. @endif@if csharp LibSBML attaches an identifying
   * code to every kind of SBML object.  These are known as <em>SBML type
   * codes</em>.  In the C# language interface for libSBML, the type codes
   * are defined as static integer constants in the interface class @link
   * libsbmlcs.libsbml@endlink.  The names of the type codes all begin with
   * the characters @c SBML_. @endif
   *
   * @return the SBML type code for this object, or @link libsbmlcs.libsbml.SBML_UNKNOWN SBML_UNKNOWN@endlink (default).
   *
   * @see getElementName()
   */
 public new int getTypeCode() {
    int ret = libsbmlPINVOKE.ListOfUnits_getTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the libSBML type code for the objects contained in this ListOf
   * (i.e., Unit objects, if the list is non-empty).
   * 
   * @if clike LibSBML attaches an identifying code to every kind of SBML
   * object.  These are known as <em>SBML type codes</em>.  The set of
   * possible type codes is defined in the enumeration #SBMLTypeCode_t.
   * The names of the type codes all begin with the characters @c
   * SBML_. @endif@if java LibSBML attaches an identifying code to every
   * kind of SBML object.  These are known as <em>SBML type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libSBML, the type codes are defined as
   * static integer constants in the interface class {@link
   * libsbmlcs.libsbml}.  The names of the type codes all begin with the
   * characters @c SBML_. @endif@if python LibSBML attaches an identifying
   * code to every kind of SBML object.  These are known as <em>SBML type
   * codes</em>.  In the Python language interface for libSBML, the type
   * codes are defined as static integer constants in the interface class
   * @link libsbml@endlink.  The names of the type codes all begin with the
   * characters @c SBML_. @endif@if csharp LibSBML attaches an identifying
   * code to every kind of SBML object.  These are known as <em>SBML type
   * codes</em>.  In the C# language interface for libSBML, the type codes
   * are defined as static integer constants in the interface class @link
   * libsbmlcs.libsbml@endlink.  The names of the type codes all begin with
   * the characters @c SBML_. @endif
   * 
   * @return the SBML type code for the objects contained in this ListOf
   * instance, or @link libsbmlcs.libsbml.SBML_UNKNOWN SBML_UNKNOWN@endlink (default).
   *
   * @see getElementName()
   */
 public new int getItemTypeCode() {
    int ret = libsbmlPINVOKE.ListOfUnits_getItemTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the XML element name of this object.
   *
   * For ListOfUnits, the XML element name is @c 'listOfUnits'.
   * 
   * @return the name of this element, i.e., @c 'listOfUnits'.
   */
 public new string getElementName() {
    string ret = libsbmlPINVOKE.ListOfUnits_getElementName(swigCPtr);
    return ret;
  }

  
  /**
   * Get a Unit from the ListOfUnits.
   *
   * @param n the index number of the Unit to get.
   * 
   * @return the nth Unit in this ListOfUnits.
   *
   * @see size()
   */
 public new Unit get(long n) {
    IntPtr cPtr = libsbmlPINVOKE.ListOfUnits_get__SWIG_0(swigCPtr, n);
    Unit ret = (cPtr == IntPtr.Zero) ? null : new Unit(cPtr, false);
    return ret;
  }

  
  /**
   * Removes the nth item from this ListOfUnits items and returns a pointer to
   * it.
   *
   * The caller owns the returned item and is responsible for deleting it.
   *
   * @param n the index of the item to remove
   *
   * @see size()
   */
 public new Unit remove(long n) {
    IntPtr cPtr = libsbmlPINVOKE.ListOfUnits_remove(swigCPtr, n);
    Unit ret = (cPtr == IntPtr.Zero) ? null : new Unit(cPtr, true);
    return ret;
  }

}

}