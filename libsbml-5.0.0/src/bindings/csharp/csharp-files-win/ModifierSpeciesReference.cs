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
 * LibSBML implementation of %SBML's %ModifierSpeciesReference construct.
 *
 * Sometimes a species appears in the kinetic rate formula of a reaction
 * but is itself neither created nor destroyed in that reaction (for
 * example, because it acts as a catalyst or inhibitor).  In SBML, all such
 * species are simply called @em modifiers without regard to the detailed
 * role of those species in the model.  The Reaction structure provides a
 * way to express which species act as modifiers in a given reaction.  This
 * is the purpose of the list of modifiers available in Reaction.  The list
 * contains instances of ModifierSpeciesReference structures.
 *
 * The ModifierSpeciesReference structure inherits the mandatory attribute
 * 'species' and optional attributes 'id' and 'name' from the parent class
 * SimpleSpeciesReference.  See the description of SimpleSpeciesReference
 * for more information about these.
 *
 * The value of the 'species' attribute must be the identifier of a species
 * defined in the enclosing Model; this species is designated as a modifier
 * for the current reaction.  A reaction may have any number of modifiers.
 * It is permissible for a modifier species to appear simultaneously in the
 * list of reactants and products of the same reaction where it is
 * designated as a modifier, as well as to appear in the list of reactants,
 * products and modifiers of other reactions in the model.
 *
 * 
 * <!---------------------------------------------------------------------- -->
 *
 */
public class ModifierSpeciesReference : SimpleSpeciesReference {
	private HandleRef swigCPtr;
	
	internal ModifierSpeciesReference(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.ModifierSpeciesReference_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.ModifierSpeciesReferenceUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(ModifierSpeciesReference obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (ModifierSpeciesReference obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~ModifierSpeciesReference() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_ModifierSpeciesReference(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  
  /**
   * Creates a new ModifierSpeciesReference using the given SBML @p level and @p version
   * values.
   *
   * @param level a long integer, the SBML Level to assign to this ModifierSpeciesReference
   *
   * @param version a long integer, the SBML Version to assign to this
   * ModifierSpeciesReference
   * 
   * @note Upon the addition of a ModifierSpeciesReference object to an
   * SBMLDocument (e.g., using Reaction::addModifier(@if java ModifierSpeciesReference msr@endif)), the
   * SBML Level, SBML Version and XML namespace of the document @em
   * override the values used when creating the ModifierSpeciesReference
   * object via this constructor.  This is necessary to ensure that an SBML
   * document is a consistent structure.  Nevertheless, the ability to
   * supply the values at the time of creation of a
   * ModifierSpeciesReference is an important aid to producing valid SBML.
   * Knowledge of the intented SBML Level and Version determine whether it
   * is valid to assign a particular value to an attribute, or whether it
   * is valid to add an object to an existing SBMLDocument.
   */
 public ModifierSpeciesReference(long level, long version) : this(libsbmlPINVOKE.new_ModifierSpeciesReference__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates a new ModifierSpeciesReference using the given SBMLNamespaces object
   * @p sbmlns.
   *
   * @param sbmlns an SBMLNamespaces object.
   *
   * @note Upon the addition of a ModifierSpeciesReference object to an
   * SBMLDocument (e.g., using Reaction::addModifier(@if java ModifierSpeciesReference msr@endif)), the
   * SBML XML namespace of the document @em overrides the value used when
   * creating the ModifierSpeciesReference object via this constructor.
   * This is necessary to ensure that an SBML document is a consistent
   * structure.  Nevertheless, the ability to supply the values at the time
   * of creation of a ModifierSpeciesReference is an important aid to
   * producing valid SBML.  Knowledge of the intented SBML Level and
   * Version determine whether it is valid to assign a particular value to
   * an attribute, or whether it is valid to add an object to an existing
   * SBMLDocument.
   */
 public ModifierSpeciesReference(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_ModifierSpeciesReference__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates and returns a deep copy of this ModifierSpeciesReference
   * instance.
   *
   * @return a (deep) copy of this ModifierSpeciesReference.
   */
 public new SBase clone() {
    IntPtr cPtr = libsbmlPINVOKE.ModifierSpeciesReference_clone(swigCPtr);
    ModifierSpeciesReference ret = (cPtr == IntPtr.Zero) ? null : new ModifierSpeciesReference(cPtr, true);
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
    int ret = libsbmlPINVOKE.ModifierSpeciesReference_getTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the XML element name of this object, which for Species, is
   * always @c 'modifierSpeciesReference'.
   * 
   * @return the name of this element, i.e., @c 'modifierSpeciesReference'.
   */
 public new string getElementName() {
    string ret = libsbmlPINVOKE.ModifierSpeciesReference_getElementName(swigCPtr);
    return ret;
  }

  
  /**
   * Predicate returning @c true if
   * all the required attributes for this ModifierSpeciesReference object
   * have been set.
   *
   * @note The required attributes for a ModifierSpeciesReference object are:
   * species
   */
 public new bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.ModifierSpeciesReference_hasRequiredAttributes(swigCPtr);
    return ret;
  }

}

}