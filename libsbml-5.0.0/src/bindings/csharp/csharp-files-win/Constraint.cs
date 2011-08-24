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
 * LibSBML implementation of SBML's %Constraint construct.
 *
 * The Constraint object class was introduced in SBML Level&nbsp;2
 * Version&nbsp;2 as a mechanism for stating the assumptions under which a
 * model is designed to operate.  The <em>constraints</em> are statements
 * about permissible values of different quantities in a model.
 * Constraints are not used to compute dynamical values for simulation or
 * analysis, but rather, they serve an advisory role for
 * simulation/analysis tools.
 *
 * SBML's Constraint object class has one required attribute, 'id', to
 * give the parameter a unique identifier by which other parts of an SBML
 * model definition can refer to it.  A Constraint object can also have an
 * optional 'name' attribute of type @c string.  Identifiers and names must
 * be used according to the guidelines described in the SBML specification
 * (e.g., Section 3.3 in the Level&nbsp;2 Version 4 specification).  
 *
 * Constraint has one required subelement, 'math', containing a MathML
 * formula defining the condition of the constraint.  This formula must
 * return a bool value of @c true when the model is a <em>valid</em>
 * state.  The formula can be an arbitrary expression referencing the
 * variables and other entities in an SBML model.  The evaluation of 'math'
 * and behavior of constraints are described in more detail below.
 *
 * A Constraint structure also has an optional subelement called 'message'.
 * This can contain a message in XHTML format that may be displayed to the
 * user when the condition of the formula in the 'math' subelement
 * evaluates to a value of @c false.  Software tools are not required to
 * display the message, but it is recommended that they do so as a matter
 * of best practice.  The XHTML content within a 'message' subelement must
 * follow the same restrictions as for the 'notes' element on SBase
 * described in in the SBML Level&nbsp;2 specification; please consult the
 * <a target='_blank' href='http://sbml.org/Documents/Specifications'>SBML
 * specification document</a> corresponding to the SBML Level and Version
 * of your model for more information about the requirements for 'notes'
 * content.
 *
 * Constraint was introduced in SBML Level&nbsp;2 Version&nbsp;2.  It is
 * not available in earlier versions of Level&nbsp;2 nor in any version of
 * Level&nbsp;1.
 *
 * @section constraint-semantics Semantics of Constraints
 * 
 * In the context of a simulation, a Constraint has effect at all times
 * <em>t >= 0</em>.  Each Constraint's 'math' subelement is first
 * evaluated after any InitialAssignment definitions in a model at <em>t =
 * 0</em> and can conceivably trigger at that point.  (In other words, a
 * simulation could fail a constraint immediately.)
 *
 * Constraint structures <em>cannot and should not</em> be used to compute
 * the dynamical behavior of a model as part of, for example, simulation.
 * Constraints may be used as input to non-dynamical analysis, for instance
 * by expressing flux constraints for flux balance analysis.
 *
 * The results of a simulation of a model containing a constraint are
 * invalid from any simulation time at and after a point when the function
 * given by the 'math' subelement returns a value of @c false.  Invalid
 * simulation results do not make a prediction of the behavior of the
 * biochemical reaction network represented by the model.  The precise
 * behavior of simulation tools is left undefined with respect to
 * constraints.  If invalid results are detected with respect to a given
 * constraint, the 'message' subelement may optionally be displayed to the
 * user.  The simulation tool may also halt the simulation or clearly
 * delimit in output data the simulation time point at which the simulation
 * results become invalid.
 *
 * SBML does not impose restrictions on duplicate Constraint definitions or
 * the order of evaluation of Constraint objects in a model.  It is
 * possible for a model to define multiple constraints all with the same
 * mathematical expression.  Since the failure of any constraint indicates
 * that the model simulation has entered an invalid state, a system is not
 * required to attempt to detect whether other constraints in the model
 * have failed once any one constraint has failed.
 *
 * <!---------------------------------------------------------------------- -->
 *
 */
public class Constraint : SBase {
	private HandleRef swigCPtr;
	
	internal Constraint(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.Constraint_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.ConstraintUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(Constraint obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (Constraint obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~Constraint() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_Constraint(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  
  /**
   * Creates a new Constraint using the given SBML @p level and @p version
   * values.
   *
   * @param level a long integer, the SBML Level to assign to this Constraint
   *
   * @param version a long integer, the SBML Version to assign to this
   * Constraint
   * 
   * @note Upon the addition of a Constraint object to an SBMLDocument
   * (e.g., using Model::addConstraint(@if java Constraint c@endif)), the
   * SBML Level, SBML Version and XML namespace of the document @em
   * override the values used when creating the Constraint object via this
   * constructor.  This is necessary to ensure that an SBML document is a
   * consistent structure.  Nevertheless, the ability to supply the values
   * at the time of creation of a Constraint is an important aid to
   * producing valid SBML.  Knowledge of the intented SBML Level and
   * Version determine whether it is valid to assign a particular value to
   * an attribute, or whether it is valid to add an object to an existing
   * SBMLDocument.
   */
 public Constraint(long level, long version) : this(libsbmlPINVOKE.new_Constraint__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates a new Constraint using the given SBMLNamespaces object
   * @p sbmlns.
   *
   * The SBMLNamespaces object encapsulates SBML Level/Version/namespaces
   * information.  It is used to communicate the SBML Level, Version, and
   * (in Level&nbsp;3) packages used in addition to SBML Level&nbsp;3 Core.
   * A common approach to using this class constructor is to create an
   * SBMLNamespaces object somewhere in a program, once, then pass it to
   * object constructors such as this one when needed.
   *
   * @param sbmlns an SBMLNamespaces object.
   *
   * @note Upon the addition of a Constraint object to an SBMLDocument
   * (e.g., using Model::addConstraint(@if java Constraint c@endif)), the
   * SBML XML namespace of the document @em overrides the value used when
   * creating the Constraint object via this constructor.  This is
   * necessary to ensure that an SBML document is a consistent structure.
   * Nevertheless, the ability to supply the values at the time of creation
   * of a Constraint is an important aid to producing valid SBML.
   * Knowledge of the intented SBML Level and Version determine whether it
   * is valid to assign a particular value to an attribute, or whether it
   * is valid to add an object to an existing SBMLDocument.
   */
 public Constraint(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_Constraint__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Copy constructor; creates a copy of this Constraint.
   */
 public Constraint(Constraint orig) : this(libsbmlPINVOKE.new_Constraint__SWIG_2(Constraint.getCPtr(orig)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates and returns a deep copy of this Constraint.
   * 
   * @return a (deep) copy of this Constraint.
   */
 public new Constraint clone() {
    IntPtr cPtr = libsbmlPINVOKE.Constraint_clone(swigCPtr);
    Constraint ret = (cPtr == IntPtr.Zero) ? null : new Constraint(cPtr, true);
    return ret;
  }

  
  /**
   * Get the message, if any, associated with this Constraint
   * 
   * @return the message for this Constraint, as an XMLNode.
   */
 public XMLNode getMessage() {
    IntPtr cPtr = libsbmlPINVOKE.Constraint_getMessage(swigCPtr);
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, false);
    return ret;
  }

  
  /**
   * Get the message string, if any, associated with this Constraint
   * 
   * @return the message for this Constraint, as a string.
   */
 public string getMessageString() {
    string ret = libsbmlPINVOKE.Constraint_getMessageString(swigCPtr);
    return ret;
  }

  
  /**
   * Get the mathematical expression of this Constraint
   * 
   * @return the math for this Constraint, as an ASTNode.
   */
 public ASTNode getMath() {
    IntPtr cPtr = libsbmlPINVOKE.Constraint_getMath(swigCPtr);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    return ret;
  }

  
  /**
   * Predicate returning @c true if a
   * message is defined for this Constraint.
   *
   * @return @c true if the message of this Constraint is set,
   * @c false otherwise.
   */
 public bool isSetMessage() {
    bool ret = libsbmlPINVOKE.Constraint_isSetMessage(swigCPtr);
    return ret;
  }

  
  /**
   * Predicate returning @c true if a
   * mathematical formula is defined for this Constraint.
   *
   * @return @c true if the 'math' subelement for this Constraint is
   * set, @c false otherwise.
   */
 public bool isSetMath() {
    bool ret = libsbmlPINVOKE.Constraint_isSetMath(swigCPtr);
    return ret;
  }

  
  /**
   * Sets the message of this Constraint.
   *
   * The XMLNode tree passed in @p xhtml is copied.
   *
   * @param xhtml an XML tree containing XHTML content.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link libsbmlcs.libsbml.LIBSBML_INVALID_OBJECT LIBSBML_INVALID_OBJECT @endlink
   */
 public int setMessage(XMLNode xhtml) {
    int ret = libsbmlPINVOKE.Constraint_setMessage(swigCPtr, XMLNode.getCPtr(xhtml));
    return ret;
  }

  
  /**
   * Sets the mathematical expression of this Constraint to a copy of the
   * AST given as @p math.
   *
   * @param math an ASTNode expression to be assigned as the 'math'
   * subelement of this Constraint
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link libsbmlcs.libsbml.LIBSBML_INVALID_OBJECT LIBSBML_INVALID_OBJECT @endlink
   */
 public int setMath(ASTNode math) {
    int ret = libsbmlPINVOKE.Constraint_setMath(swigCPtr, ASTNode.getCPtr(math));
    return ret;
  }

  
  /**
   * Unsets the 'message' subelement of this Constraint.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_FAILED LIBSBML_OPERATION_FAILED @endlink
   */
 public int unsetMessage() {
    int ret = libsbmlPINVOKE.Constraint_unsetMessage(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the libSBML type code for this SBML object.
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
    int ret = libsbmlPINVOKE.Constraint_getTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the XML element name of this object, which for Constraint, is
   * always @c 'constraint'.
   * 
   * @return the name of this element, i.e., @c 'constraint'.
   */
 public new string getElementName() {
    string ret = libsbmlPINVOKE.Constraint_getElementName(swigCPtr);
    return ret;
  }

  
  /**
   * Predicate returning @c true if
   * all the required elements for this Constraint object
   * have been set.
   *
   * @note The required elements for a Constraint object are:
   * @li 'math'
   *
   * @return a bool value indicating whether all the required
   * elements for this object have been defined.
   */
 public new bool hasRequiredElements() {
    bool ret = libsbmlPINVOKE.Constraint_hasRequiredElements(swigCPtr);
    return ret;
  }

}

}
