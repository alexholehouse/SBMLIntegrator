/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * LibSBML implementation of SBML's ListOfInitialAssignments construct.
 * <p>
 * The various ListOf___ classes in SBML are merely containers used for
 * organizing the main components of an SBML model.  All are derived from
 * the abstract class {@link SBase}, and inherit the various attributes and
 * subelements of {@link SBase}, such as 'metaid' as and 'annotation'.  The
 * ListOf___ classes do not add any attributes of their own.
 * <p>
 * The relationship between the lists and the rest of an SBML model is
 * illustrated by the following (for SBML Level&nbsp;2 Version&nbsp;4):
 * <p>
 * <center><img src='listof-illustration.jpg'></center><br>
 * 
 * <p>
 * Readers may wonder about the motivations for using the ListOf___
 * containers.  A simpler approach in XML might be to place the components
 * all directly at the top level of the model definition.  The choice made
 * in SBML is to group them within XML elements named after
 * {@link ListOf}<em>Classname</em>, in part because it helps organize the
 * components.  More importantly, the fact that the container classes are
 * derived from {@link SBase} means that software tools can add information <em>about</em>
 * the lists themselves into each list container's 'annotation'.
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

public class ListOfInitialAssignments extends ListOf {
   private long swigCPtr;

   protected ListOfInitialAssignments(long cPtr, boolean cMemoryOwn)
   {
     super(libsbmlJNI.ListOfInitialAssignments_SWIGUpcast(cPtr), cMemoryOwn);
     swigCPtr = cPtr;
   }

   protected static long getCPtr(ListOfInitialAssignments obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (ListOfInitialAssignments obj)
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
        libsbmlJNI.delete_ListOfInitialAssignments(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  
  /**
   * Creates a new {@link ListOfInitialAssignments} object.
   * <p>
   * The object is constructed such that it is valid for the given SBML
   * Level and Version combination.
   * <p>
   * @param level the SBML Level
   * <p>
   * @param version the Version within the SBML Level
   */
 public ListOfInitialAssignments(long level, long version) {
    this(libsbmlJNI.new_ListOfInitialAssignments__SWIG_0(level, version), true);
  }

  
  /**
   * Creates a new {@link ListOfInitialAssignments} object.
   * <p>
   * The object is constructed such that it is valid for the SBML Level and
   * Version combination determined by the {@link SBMLNamespaces} object in 
   * <code>sbmlns</code>.
   * <p>
   * @param sbmlns an {@link SBMLNamespaces} object that is used to determine the
   * characteristics of the {@link ListOfInitialAssignments} object to be created.
   */
 public ListOfInitialAssignments(SBMLNamespaces sbmlns) {
    this(libsbmlJNI.new_ListOfInitialAssignments__SWIG_1(SBMLNamespaces.getCPtr(sbmlns), sbmlns), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link ListOfInitialAssignments} instance.
   * <p>
   * @return a (deep) copy of this {@link ListOfInitialAssignments}.
   */
 public ListOfInitialAssignments cloneObject() {
    long cPtr = libsbmlJNI.ListOfInitialAssignments_cloneObject(swigCPtr, this);
    return (cPtr == 0) ? null : new ListOfInitialAssignments(cPtr, true);
  }

  
  /**
   * Returns the libSBML type code for this SBML object.
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
    return libsbmlJNI.ListOfInitialAssignments_getTypeCode(swigCPtr, this);
  }

  
  /**
   * Returns the libSBML type code for the objects contained in this {@link ListOf}
   * (i.e., {@link InitialAssignment} objects, if the list is non-empty).
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
   * <p>
   * @see #getElementName()
   */
 public int getItemTypeCode() {
    return libsbmlJNI.ListOfInitialAssignments_getItemTypeCode(swigCPtr, this);
  }

  
  /**
   * Returns the XML element name of this object.
   * <p>
   * For {@link ListOfInitialAssignments}, the XML element name is 
   * <code>'listOfInitialAssignments'.</code>
   * <p>
   * @return the name of this element, i.e., <code>'listOfInitialAssignments'.</code>
   */
 public String getElementName() {
    return libsbmlJNI.ListOfInitialAssignments_getElementName(swigCPtr, this);
  }

  
  /**
   * Get a {@link InitialAssignment} from the {@link ListOfInitialAssignments}.
   * <p>
   * @param n the index number of the {@link InitialAssignment} to get.
   * <p>
   * @return the nth {@link InitialAssignment} in this {@link ListOfInitialAssignments}.
   * <p>
   * @see #size()
   */
 public InitialAssignment get(long n) {
    long cPtr = libsbmlJNI.ListOfInitialAssignments_get__SWIG_0(swigCPtr, this, n);
    return (cPtr == 0) ? null : new InitialAssignment(cPtr, false);
  }

  
  /**
   * Get a {@link InitialAssignment} from the {@link ListOfInitialAssignments}
   * based on its identifier.
   * <p>
   * @param sid a string representing the identifier 
   * of the {@link InitialAssignment} to get.
   * <p>
   * @return {@link InitialAssignment} in this {@link ListOfInitialAssignments}
   * with the given id or <code>null</code> if no such
   * {@link InitialAssignment} exists.
   * <p>
   * @see #get(long n)
   * @see #size()
   */
 public InitialAssignment get(String sid) {
    long cPtr = libsbmlJNI.ListOfInitialAssignments_get__SWIG_2(swigCPtr, this, sid);
    return (cPtr == 0) ? null : new InitialAssignment(cPtr, false);
  }

  
  /**
   * Removes the nth item from this {@link ListOfInitialAssignments} items and returns a pointer to
   * it.
   * <p>
   * The caller owns the returned item and is responsible for deleting it.
   * <p>
   * @param n the index of the item to remove
   * <p>
   * @see #size()
   */
 public InitialAssignment remove(long n) {
    long cPtr = libsbmlJNI.ListOfInitialAssignments_remove__SWIG_0(swigCPtr, this, n);
    return (cPtr == 0) ? null : new InitialAssignment(cPtr, true);
  }

  
  /**
   * Removes item in this {@link ListOfInitialAssignments} items with the given identifier.
   * <p>
   * The caller owns the returned item and is responsible for deleting it.
   * If none of the items in this list have the identifier <code>sid</code>, then 
   * <code>null</code> is returned.
   * <p>
   * @param sid the identifier of the item to remove
   * <p>
   * @return the item removed.  As mentioned above, the caller owns the
   * returned item.
   */
 public InitialAssignment remove(String sid) {
    long cPtr = libsbmlJNI.ListOfInitialAssignments_remove__SWIG_1(swigCPtr, this, sid);
    return (cPtr == 0) ? null : new InitialAssignment(cPtr, true);
  }

}
