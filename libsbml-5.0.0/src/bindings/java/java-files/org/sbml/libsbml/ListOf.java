/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * Parent class for the various SBML 'ListOfXYZ' classes.
 * <p>
 * <p style='color: #555; font-style: italic'>
This class of objects is defined by libSBML only and has no direct
equivalent in terms of SBML components.  This class is not prescribed by
the SBML specifications, although it is used to implement features
defined in SBML.
</p>

 * <p>
 * SBML defines various ListOf___ classes that are containers used for
 * organizing the main components of an SBML model.  All are derived from
 * the abstract class {@link SBase}, and inherit the attributes and subelements of
 * {@link SBase}, such as 'metaid' as and 'annotation'.  The ListOf___ classes do
 * not add any attributes of their own.
 * <p>
 * The {@link ListOf} class in libSBML is a utility class that serves as the parent
 * class for implementing the ListOf__ classes.  It provides methods for
 * working generically with the various SBML lists of objects in a program.
 * LibSBML uses this separate list class rather than ordinary
 * Java lists,
 * so that it can provide the methods and features associated with {@link SBase}.
 * <p>
 * @see ListOfFunctionDefinitions
 * @see ListOfUnitDefinitions
 * @see ListOfCompartmentTypes
 * @see ListOfSpeciesTypes
 * @see ListOfCompartments
 * @see ListOfSpecies
 * @see ListOfParameters
 * @see ListOfInitialAssignments
 * @see ListOfRules
 * @see ListOfConstraints
 * @see ListOfReactions
 * @see ListOfEvents
 */

public class ListOf extends SBase {
   private long swigCPtr;

   protected ListOf(long cPtr, boolean cMemoryOwn)
   {
     super(libsbmlJNI.ListOf_SWIGUpcast(cPtr), cMemoryOwn);
     swigCPtr = cPtr;
   }

   protected static long getCPtr(ListOf obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (ListOf obj)
   {
     long ptr = 0;

     if (obj != null)
     {
       ptr             = obj.swigCPtr;
       obj.swigCMemOwn = false;
     }

     return ptr;
   }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        libsbmlJNI.delete_ListOf(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  
  /**
   * Creates a new {@link ListOf} object.
   * <p>
   * @param level the SBML Level; if not assigned, defaults to the
   * value of SBML_DEFAULT_LEVEL.
   * <p>
   * @param version the Version within the SBML Level; if not assigned,
   * defaults to the value of SBML_DEFAULT_VERSION.
   * <p>
   * @docnote The native C++ implementation of this method defines a default argument
value. In the documentation generated for different libSBML language
bindings, you may or may not see corresponding arguments in the method
declarations. For example, in Java and C#, a default argument is handled by
declaring two separate methods, with one of them having the argument and
the other one lacking the argument. However, the libSBML documentation will
be <em>identical</em> for both methods. Consequently, if you are reading
this and do not see an argument even though one is described, please look
for descriptions of other variants of this method near where this one
appears in the documentation.

   */
 public ListOf(long level, long version) {
    this(libsbmlJNI.new_ListOf__SWIG_0(level, version), true);
  }

  
  /**
   * Creates a new {@link ListOf} object.
   * <p>
   * @param level the SBML Level; if not assigned, defaults to the
   * value of SBML_DEFAULT_LEVEL.
   * <p>
   * @param version the Version within the SBML Level; if not assigned,
   * defaults to the value of SBML_DEFAULT_VERSION.
   * <p>
   * @docnote The native C++ implementation of this method defines a default argument
value. In the documentation generated for different libSBML language
bindings, you may or may not see corresponding arguments in the method
declarations. For example, in Java and C#, a default argument is handled by
declaring two separate methods, with one of them having the argument and
the other one lacking the argument. However, the libSBML documentation will
be <em>identical</em> for both methods. Consequently, if you are reading
this and do not see an argument even though one is described, please look
for descriptions of other variants of this method near where this one
appears in the documentation.

   */
 public ListOf(long level) {
    this(libsbmlJNI.new_ListOf__SWIG_1(level), true);
  }

  
  /**
   * Creates a new {@link ListOf} object.
   * <p>
   * @param level the SBML Level; if not assigned, defaults to the
   * value of SBML_DEFAULT_LEVEL.
   * <p>
   * @param version the Version within the SBML Level; if not assigned,
   * defaults to the value of SBML_DEFAULT_VERSION.
   * <p>
   * @docnote The native C++ implementation of this method defines a default argument
value. In the documentation generated for different libSBML language
bindings, you may or may not see corresponding arguments in the method
declarations. For example, in Java and C#, a default argument is handled by
declaring two separate methods, with one of them having the argument and
the other one lacking the argument. However, the libSBML documentation will
be <em>identical</em> for both methods. Consequently, if you are reading
this and do not see an argument even though one is described, please look
for descriptions of other variants of this method near where this one
appears in the documentation.

   */
 public ListOf() {
    this(libsbmlJNI.new_ListOf__SWIG_2(), true);
  }

  
  /**
   * Creates a new {@link ListOf} with {@link SBMLNamespaces} object.
   * <p>
   * @param sbmlns the set of namespaces that this {@link ListOf} should contain.
   */
 public ListOf(SBMLNamespaces sbmlns) {
    this(libsbmlJNI.new_ListOf__SWIG_3(SBMLNamespaces.getCPtr(sbmlns), sbmlns), true);
  }

  
  /**
   * Copy constructor;  creates a copy of this {@link ListOf}.
   * <p>
   * @param orig the {@link ListOf} instance to copy.
   */
 public ListOf(ListOf orig) {
    this(libsbmlJNI.new_ListOf__SWIG_4(ListOf.getCPtr(orig), orig), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link ListOf}.
   * <p>
   * @return a (deep) copy of this {@link ListOf}.
   */
 public SBase cloneObject() {
  return libsbml.DowncastSBase(libsbmlJNI.ListOf_cloneObject(swigCPtr, this), true);
}

  
  /**
   * Adds item to the end of this {@link ListOf}.
   * <p>
   * This variant of the method makes a clone of the <code>item</code> handed to it.
   * This means that when the {@link ListOf} is destroyed, the original items will
   * not be destroyed.
   * <p>
   * @param item the item to be added to the list.
   * <p>
   * @see #appendAndOwn(SBase item)
   */
 public int append(SBase item) {
    return libsbmlJNI.ListOf_append(swigCPtr, this, SBase.getCPtr(item), item);
  }

  
  /**
   * Adds item to the end of this {@link ListOf}.
   * <p>
   * This variant of the method does not clone the <code>item</code> handed to it;
   * instead, it assumes ownership of it.  This means that when the {@link ListOf}
   * is destroyed, the item will be destroyed along with it.
   * <p>
   * @param item the item to be added to the list.
   * <p>
   * @see #append(SBase item)
   */
 public int appendAndOwn(SBase item) {
    return libsbmlJNI.ListOf_appendAndOwn(swigCPtr, this, SBase.getCPtrAndDisown(item), item);
  }

  
  /**
   * Get an item from the list.
   * <p>
   * @param n the index number of the item to get.
   * <p>
   * @return the nth item in this {@link ListOf} items.
   * <p>
   * @see #size()
   */
 public SBase get(long n) {
  return libsbml.DowncastSBase(libsbmlJNI.ListOf_get__SWIG_0(swigCPtr, this, n), false);
}

  
  /**
   * Removes all items in this {@link ListOf} object.
   * <p>
   * If <code>doDelete</code> is <code>true</code> (default), all items in this {@link ListOf} object
   * are deleted and cleared, and thus the caller doesn't have to delete
   * those items.  Otherwise, all items are just cleared from this {@link ListOf}
   * object and the caller is responsible for deleting all items.  (In that
   * case, pointers to all items should be stored elsewhere before calling
   * this function.)
   * <p>
   * @param doDelete if <code>true</code> (default), all items are deleted and cleared.
   * Otherwise, all items are just cleared and not deleted.
   * <p>
   * @docnote The native C++ implementation of this method defines a default argument
value. In the documentation generated for different libSBML language
bindings, you may or may not see corresponding arguments in the method
declarations. For example, in Java and C#, a default argument is handled by
declaring two separate methods, with one of them having the argument and
the other one lacking the argument. However, the libSBML documentation will
be <em>identical</em> for both methods. Consequently, if you are reading
this and do not see an argument even though one is described, please look
for descriptions of other variants of this method near where this one
appears in the documentation.

   */
 public void clear(boolean doDelete) {
    libsbmlJNI.ListOf_clear__SWIG_0(swigCPtr, this, doDelete);
  }

  
  /**
   * Removes all items in this {@link ListOf} object.
   * <p>
   * If <code>doDelete</code> is <code>true</code> (default), all items in this {@link ListOf} object
   * are deleted and cleared, and thus the caller doesn't have to delete
   * those items.  Otherwise, all items are just cleared from this {@link ListOf}
   * object and the caller is responsible for deleting all items.  (In that
   * case, pointers to all items should be stored elsewhere before calling
   * this function.)
   * <p>
   * @param doDelete if <code>true</code> (default), all items are deleted and cleared.
   * Otherwise, all items are just cleared and not deleted.
   * <p>
   * @docnote The native C++ implementation of this method defines a default argument
value. In the documentation generated for different libSBML language
bindings, you may or may not see corresponding arguments in the method
declarations. For example, in Java and C#, a default argument is handled by
declaring two separate methods, with one of them having the argument and
the other one lacking the argument. However, the libSBML documentation will
be <em>identical</em> for both methods. Consequently, if you are reading
this and do not see an argument even though one is described, please look
for descriptions of other variants of this method near where this one
appears in the documentation.

   */
 public void clear() {
    libsbmlJNI.ListOf_clear__SWIG_1(swigCPtr, this);
  }

  
  /**
   * Removes the <em>n</em>th item from this {@link ListOf} items and returns a
   * pointer to it.
   * <p>
   * The caller owns the returned item and is responsible for deleting it.
   * <p>
   * @param n the index of the item to remove
   * <p>
   * @see #size()
   */
 public SBase remove(long n) {
  return libsbml.DowncastSBase(libsbmlJNI.ListOf_remove(swigCPtr, this, n), true);
}

  
  /**
   * Get the size of this {@link ListOf}.
   * <p>
   * @return the number of items in this {@link ListOf} items.
   */
 public long size() {
    return libsbmlJNI.ListOf_size(swigCPtr, this);
  }

  
  /**
   * Sets this SBML object to child SBML objects (if any).
   * (Creates a child-parent relationship by the parent)
   * <p>
   * Subclasses must override this function if they define
   * one ore more child elements.
   * Basically, this function needs to be called in
   * constructor, copy constructor and assignment operator.
   * <p>
   * @see setSBMLDocument
   * @see enablePackageInternal
   <p>
 * @deprecated libSBML internal
 */
 public void connectToChild() {
    libsbmlJNI.ListOf_connectToChild(swigCPtr, this);
  }

  
  /**
   * Returns the libSBML type code for this object, namely, 
   * <code>SBML_LIST_OF.</code>
   * <p>
   * LibSBML attaches an identifying code to every
   * kind of SBML object.  These are known as <em>SBML type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libSBML, the type codes are defined as
   * static integer constants in the interface class {@link
   * libsbmlConstants}.  The names of the type codes all begin with the
   * characters <code>SBML_.</code> 
   * <p>
   * @return the SBML type code for this object, or {@link  libsbmlConstants#SBML_UNKNOWN SBML_UNKNOWN} (default).
   * <p>
   * @see #getElementName()
   */
 public int getTypeCode() {
    return libsbmlJNI.ListOf_getTypeCode(swigCPtr, this);
  }

  
  /**
   * Get the type code of the objects contained in this {@link ListOf}.
   * <p>
   * LibSBML attaches an identifying code to every
   * kind of SBML object.  These are known as <em>SBML type codes</em>.  In
   * other languages, the set of type codes is stored in an enumeration; in
   * the Java language interface for libSBML, the type codes are defined as
   * static integer constants in the interface class {@link
   * libsbmlConstants}.  The names of the type codes all begin with the
   * characters <code>SBML_.</code> 
   * <p>
   * @return the SBML type code for the objects contained in this {@link ListOf}
   * instance, or {@link  libsbmlConstants#SBML_UNKNOWN SBML_UNKNOWN} (default).
   */
 public int getItemTypeCode() {
    return libsbmlJNI.ListOf_getItemTypeCode(swigCPtr, this);
  }

  
  /**
   * Returns the XML element name of this object, which for {@link ListOf}, is
   * always <code>'listOf'.</code>
   * <p>
   * @return the XML name of this element.
   */
 public String getElementName() {
    return libsbmlJNI.ListOf_getElementName(swigCPtr, this);
  }

  
  /**
   * Enables/Disables the given package with this element and child
   * elements (if any).
   * (This is an internal implementation for enablePakcage function)
   * <p>
   * @note Subclasses of the SBML Core package in which one or more child
   * elements are defined must override this function.
   <p>
 * @deprecated libSBML internal
 */
 public void enablePackageInternal(String pkgURI, String pkgPrefix, boolean flag) {
    libsbmlJNI.ListOf_enablePackageInternal(swigCPtr, this, pkgURI, pkgPrefix, flag);
  }

}
