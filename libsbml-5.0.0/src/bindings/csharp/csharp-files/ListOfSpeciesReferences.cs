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

/** 
 * LibSBML implementation of SBML's %ListOfSpeciesReferences construct.
 *
 * The ListOfSpeciesReferences class is used to store lists of reactants
 * and products in a Reaction object.
 *
 * As with the various other ListOf___ classes in %SBML, the
 * ListOfSpeciesReferences is merely a container used for organizing
 * instances of other objects, in this case SpeciesReference objects.
 * ListOfSpeciesReferences is derived from the abstract class SBase, and
 * inherit the various attributes and subelements of SBase, such as
 * 'metaid' as and 'annotation'.  The ListOf___ classes do not add any
 * attributes of their own.
 */
public class ListOfSpeciesReferences : ListOf {
	private HandleRef swigCPtr;
	
	internal ListOfSpeciesReferences(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.ListOfSpeciesReferences_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.ListOfSpeciesReferencesUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(ListOfSpeciesReferences obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (ListOfSpeciesReferences obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~ListOfSpeciesReferences() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_ListOfSpeciesReferences(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  
  /**
   * Creates a new, empty ListOfSpeciesReferences object.
   *
   * The object is constructed such that it is valid for the given SBML
   * Level and Version combination.
   *
   * @param level the SBML Level
   * 
   * @param version the Version within the SBML Level
   */
 public ListOfSpeciesReferences(long level, long version) : this(libsbmlPINVOKE.new_ListOfSpeciesReferences__SWIG_0(level, version), true) {
  }

  
  /**
   * Creates a new ListOfSpeciesReferences object.
   *
   * The object is constructed such that it is valid for the SBML Level and
   * Version combination determined by the SBMLNamespaces object in @p
   * sbmlns.
   *
   * @param sbmlns an SBMLNamespaces object that is used to determine the
   * characteristics of the ListOfSpeciesReferences object to be created.
   */
 public ListOfSpeciesReferences(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_ListOfSpeciesReferences__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
  }

  
  /**
   * Creates and returns a deep copy of this ListOfSpeciesReferences
   * instance.
   *
   * @return a (deep) copy of this ListOfSpeciesReferences.
   */
 public new ListOfSpeciesReferences clone() {
    IntPtr cPtr = libsbmlPINVOKE.ListOfSpeciesReferences_clone(swigCPtr);
    ListOfSpeciesReferences ret = (cPtr == IntPtr.Zero) ? null : new ListOfSpeciesReferences(cPtr, true);
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
    int ret = libsbmlPINVOKE.ListOfSpeciesReferences_getTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the libSBML type code for the objects contained in this ListOf
   * (i.e., SpeciesReference objects, if the list is non-empty).
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
    int ret = libsbmlPINVOKE.ListOfSpeciesReferences_getItemTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the XML element name of this object.
   *
   * For ListOfSpeciesReferences, the XML element name is @c
   * 'listOfSpeciesReferences'.
   * 
   * @return the name of this element, i.e., @c 'listOfSpeciesReferences'.
   */
 public new string getElementName() {
    string ret = libsbmlPINVOKE.ListOfSpeciesReferences_getElementName(swigCPtr);
    return ret;
  }

  
  /**
   * Get a SpeciesReference from the ListOfSpeciesReferences.
   *
   * @param n the index number of the SpeciesReference to get.
   * 
   * @return the nth SpeciesReference in this ListOfSpeciesReferences.
   *
   * @see size()
   */
 public new SimpleSpeciesReference get(long n) {
	SimpleSpeciesReference ret
	    = (SimpleSpeciesReference) libsbml.DowncastSBase(libsbmlPINVOKE.ListOfSpeciesReferences_get__SWIG_0(swigCPtr, n), false);
	return ret;
}

  
  /**
   * Get a SpeciesReference from the ListOfSpeciesReferences
   * based on its identifier.
   *
   * @param sid a string representing the identifier 
   * of the SpeciesReference to get.
   * 
   * @return SpeciesReference in this ListOfSpeciesReferences
   * with the given id or @c null if no such
   * SpeciesReference exists.
   *
   * @see get(long n)
   * @see size()
   */
 public new SimpleSpeciesReference get(string sid) {
	SimpleSpeciesReference ret
	    = (SimpleSpeciesReference) libsbml.DowncastSBase(libsbmlPINVOKE.ListOfSpeciesReferences_get__SWIG_2(swigCPtr, sid), false);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
	return ret;
}

  
  /**
   * Removes the nth item from this ListOfSpeciesReferences items and returns a pointer to
   * it.
   *
   * The caller owns the returned item and is responsible for deleting it.
   *
   * @param n the index of the item to remove
   *
   * @see size()
   */
 public new SimpleSpeciesReference remove(long n) {
	SimpleSpeciesReference ret
	    = (SimpleSpeciesReference) libsbml.DowncastSBase(libsbmlPINVOKE.ListOfSpeciesReferences_remove__SWIG_0(swigCPtr, n), true);
	return ret;
}

  
  /**
   * Removes item in this ListOfSpeciesReferences items with the given identifier.
   *
   * The caller owns the returned item and is responsible for deleting it.
   * If none of the items in this list have the identifier @p sid, then @c
   * null is returned.
   *
   * @param sid the identifier of the item to remove
   *
   * @return the item removed.  As mentioned above, the caller owns the
   * returned item.
   */
 public new SimpleSpeciesReference remove(string sid) {
	SimpleSpeciesReference ret
	    = (SimpleSpeciesReference) libsbml.DowncastSBase(libsbmlPINVOKE.ListOfSpeciesReferences_remove__SWIG_1(swigCPtr, sid), true);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
	return ret;
}

}

}