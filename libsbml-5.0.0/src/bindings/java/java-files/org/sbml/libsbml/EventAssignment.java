/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * LibSBML implementation of SBML's EventAssignment construct for Event.
 * <p>
 * {@link Event} contains an optional element called 'listOfEventAssignments', of
 * class {@link ListOfEventAssignments}.  In every instance of an event definition
 * in a model, the object's 'listOfEventAssignments' element must have a
 * non-empty list of one or more 'eventAssignment' elements of class
 * {@link EventAssignment}.  The object class {@link EventAssignment} has one required
 * attribute, 'variable', and a required element, 'math'.  Being derived
 * from {@link SBase}, it also has all the usual attributes and elements of its
 * parent class.
 * <p>
 * An {@link Event} object defines when the event can occur, the variables that are
 * affected by the event, and how the variables are affected.  The purpose
 * of the {@link EventAssignment} object class is to define how variables are
 * affected by an {@link Event}.  In SBML Level&nbsp;2, every {@link Event} object instance
 * must have a nonempty list of event assignments; in SBML Level&nbsp;3,
 * the list of assignments is optional.
 * <p>
 * The operation of an {@link Event} is divided into two phases (regardless of
 * whether a delay is involved): one phase when the event is <em>triggered</em>,
 * and the other when the event is <em>executed</em>.   {@link EventAssignment} objects
 * are interpreted when an event is executed.  The effects are described
 * below.
 * <p>
 * <h2>The attribute 'variable'</h2>
 * <p>
 * The {@link EventAssignment} attribute 'variable' must be the identifier of an
 * existing {@link Compartment}, {@link Species}, {@link SpeciesReference}, or {@link Parameter}
 * instance defined in the model.  When the event is executed, the value of
 * the model component identified by 'variable' is changed by the
 * {@link EventAssignment} to the value computed by the 'math' element; that is, a
 * species' quantity, species reference's stoichiometry, compartment's size
 * or parameter's value are reset to the value computed by 'math'.
 * <p>
 * Certain restrictions are placed on what can appear in 'variable':
 * <ul>
 * <li> The object identified by the value of the {@link EventAssignment} attribute
 * 'variable' must not have its 'constant' attribute set to or default to
 * <code>true.</code>  (Constants cannot be affected by events.)
 * <p>
 * <li> The 'variable' attribute must not contain the identifier of a
 * reaction; only species, species references, compartment and parameter
 * values may be set by an {@link Event}.
 * <p>
 * <li> The value of every 'variable' attribute must be unique among the set
 * of {@link EventAssignment} structures within a given {@link Event} structure.  In other
 * words, a single event cannot have multiple {@link EventAssignment} objects
 * assigning the same variable.  (All of them would be performed at the
 * same time when that particular {@link Event} triggers, resulting in
 * indeterminacy.)  However, <em>separate</em> {@link Event} instances can refer to the
 * same variable.
 * <p>
 * <li> A variable cannot be assigned a value in an {@link EventAssignment} object
 * instance and also be assigned a value by an {@link AssignmentRule}; i.e., the
 * value of an {@link EventAssignment}'s 'variable' attribute cannot be the same as
 * the value of a {@link AssignmentRule}' 'variable' attribute.  (Assignment rules
 * hold at all times, therefore it would be inconsistent to also define an
 * event that reassigns the value of the same variable.)
 * </ul>
 * <p>
 * Note that the time of assignment of the object identified by the
 * value of the 'variable' attribute is always the time at which the {@link Event}
 * is <em>executed</em>, not when it is <em>triggered</em>.  The timing is
 * controlled by the optional {@link Delay} in an {@link Event}.  The time of
 * assignment is not affected by the 'useValuesFromTriggerTime'
 * attribute on Eventmdash;that attribute affects the time at which the
 * {@link EventAssignment}'s 'math' expression is <em>evaluated</em>.  In other
 * words, SBML allows decoupling the time at which the
 * 'variable' is assigned from the time at which its value
 * expression is calculated.
 * <p>
 * <h2>The 'math' subelement in an {@link EventAssignment}</h2>
 * <p>
 * The MathML expression contained in an {@link EventAssignment} defines the new
 * value of the variable being assigned by the {@link Event}.
 * <p>
 * As mentioned above, the time at which the expression in 'math' is
 * evaluated is determined by the attribute 'useValuesFromTriggerTime' on
 * {@link Event}.  If the attribute value is <code>true</code>, the expression must be
 * evaluated when the event is <em>triggered</em>; more precisely, the values of
 * identifiers occurring in MathML <code>&lt;ci&gt;</code> elements in the
 * {@link EventAssignment}'s 'math' expression are the values they have at the
 * point when the event <em>triggered</em>.  If, instead,
 * 'useValuesFromTriggerTime''s value is <code>false</code>, it means the values at
 * <em>execution</em> time should be used; that is, the values of identifiers
 * occurring in MathML <code>&lt;ci&gt;</code> elements in the
 * {@link EventAssignment}'s 'math' expression are the values they have at the
 * point when the event <em>executed</em>.
 * <p>
 * <h2>SBML Level/Version differences</h2>
 * <p>
 * Between Version&nbsp;4 and previous versions of SBML Level&nbsp;2, the
 * requirements regarding the matching of units between an
 * EvengAssignment's formula and the units of the object identified by the
 * 'variable' attribute changed.  Previous versions required consistency,
 * but in SBML Level&nbsp;2 Version&nbsp;4 and in SBML Level&nbsp;3, unit
 * consistency is only <em>recommended</em>.  More precisely:
 * <ul>
 * <p>
 * <li> In the case of a species, an {@link EventAssignment} sets the referenced
 * species' quantity (concentration or amount of substance) to the value
 * determined by the formula in the {@link EventAssignment}'s 'math' subelement.
 * The units of the 'math' formula should (in SBML Level&nbsp;2
 * Version&nbsp;4 and in Level&nbsp;3) or must (in previous Versions of
 * Level&nbsp;2) be identical to the units of the species.
 * <p>
 * <li> (SBML Level&nbsp;3 only.) In the case of a species reference, an
 * {@link EventAssignment} sets the stoichiometry of the reactant or product
 * referenced by the {@link SpeciesReference} object to the value determined by the
 * formula in the 'math' element.  The unit associated with the value
 * produced by the 'math' formula should be <code>dimensionless</code>, because
 * reactant and product stoichiometries in reactions are dimensionless
 * quantities.
 * <p>
 * <li> In the case of a compartment, an {@link EventAssignment} sets the
 * referenced compartment's size to the size determined by the formula in
 * the 'math' subelement of the {@link EventAssignment}.  The overall units of the
 * formula should (in SBML Level&nbsp;2 Version&nbsp;4 and in Level&nbsp;3)
 * or must (in previous Versions of Level&nbsp;2) be identical to the units
 * specified for the size of the compartment identified by the
 * {@link EventAssignment}'s 'variable' attribute.
 * <p>
 * <li> In the case of a parameter, an {@link EventAssignment} sets the referenced
 * parameter's value to that determined by the formula in 'math'.  The
 * overall units of the formula should (in SBML Level&nbsp;2 Version&nbsp;4
 * and Level&nbsp;3) or must (in previous Versions of Level&nbsp;2) be
 * identical to the units defined for the parameter.
 * </ul>
 * <p>
 * Note that the formula placed in the 'math' element <em>has no assumed
 * units</em>.  The consistency of the units of the formula, and the units
 * of the entity which the assignment affects, must be explicitly
 * established just as in the case of the value of the {@link Delay} subelement.
 * An approach similar to the one discussed in the context of {@link Delay} may be
 * used for the formula of an {@link EventAssignment}.
 * <p>
 * @see Event
 * <p>
 * <p>
 */

public class EventAssignment extends SBase {
   private long swigCPtr;

   protected EventAssignment(long cPtr, boolean cMemoryOwn)
   {
     super(libsbmlJNI.EventAssignment_SWIGUpcast(cPtr), cMemoryOwn);
     swigCPtr = cPtr;
   }

   protected static long getCPtr(EventAssignment obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (EventAssignment obj)
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
        libsbmlJNI.delete_EventAssignment(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  
  /**
   * Creates a new {@link EventAssignment} using the given SBML <code>level</code> and <code>version</code>
   * values.
   * <p>
   * @param level a long integer, the SBML Level to assign to this {@link EventAssignment}
   * <p>
   * @param version a long integer, the SBML Version to assign to this
   * {@link EventAssignment}
   * <p>
   * @note Upon the addition of a {@link EventAssignment} object to an {@link SBMLDocument}
   * (e.g., using {@link Event#addEventAssignment(EventAssignment ea)}), 
   * the SBML Level, SBML Version and XML namespace of the document 
   * <em>override</em> the values used when creating the {@link EventAssignment} object via
   * this constructor.  This is necessary to ensure that an SBML document
   * is a consistent structure.  Nevertheless, the ability to supply the
   * values at the time of creation of a {@link EventAssignment} is an important
   * aid to producing valid SBML.  Knowledge of the intented SBML Level and
   * Version determine whether it is valid to assign a particular value to
   * an attribute, or whether it is valid to add an object to an existing
   * {@link SBMLDocument}.
   */
 public EventAssignment(long level, long version) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_EventAssignment__SWIG_0(level, version), true);
  }

  
  /**
   * Creates a new {@link EventAssignment} using the given {@link SBMLNamespaces} object
   * <code>sbmlns</code>.
   * <p>
   * The {@link SBMLNamespaces} object encapsulates SBML Level/Version/namespaces
   * information.  It is used to communicate the SBML Level, Version, and
   * (in Level&nbsp;3) packages used in addition to SBML Level&nbsp;3 Core.
   * A common approach to using this class constructor is to create an
   * {@link SBMLNamespaces} object somewhere in a program, once, then pass it to
   * object constructors such as this one when needed.
   * <p>
   * @param sbmlns an {@link SBMLNamespaces} object.
   * <p>
   * @note Upon the addition of a {@link EventAssignment} object to an {@link SBMLDocument}
   * (e.g., using {@link Event#addEventAssignment(EventAssignment ea)}),
   * the SBML XML namespace of the document <em>overrides</em> the value used
   * when creating the {@link EventAssignment} object via this constructor.  This
   * is necessary to ensure that an SBML document is a consistent
   * structure.  Nevertheless, the ability to supply the values at the time
   * of creation of a {@link EventAssignment} is an important aid to producing
   * valid SBML.  Knowledge of the intented SBML Level and Version
   * determine whether it is valid to assign a particular value to an
   * attribute, or whether it is valid to add an object to an existing
   * {@link SBMLDocument}.
   */
 public EventAssignment(SBMLNamespaces sbmlns) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_EventAssignment__SWIG_1(SBMLNamespaces.getCPtr(sbmlns), sbmlns), true);
  }

  
  /**
   * Copy constructor; creates a copy of this {@link EventAssignment}.
   */
 public EventAssignment(EventAssignment orig) throws org.sbml.libsbml.SBMLConstructorException {
    this(libsbmlJNI.new_EventAssignment__SWIG_2(EventAssignment.getCPtr(orig), orig), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link EventAssignment}.
   * <p>
   * @return a (deep) copy of this {@link EventAssignment}.
   */
 public EventAssignment cloneObject() {
    long cPtr = libsbmlJNI.EventAssignment_cloneObject(swigCPtr, this);
    return (cPtr == 0) ? null : new EventAssignment(cPtr, true);
  }

  
  /**
   * Get the value of this {@link EventAssignment}'s 'variable' attribute.
   * <p>
   * @return the identifier stored in the 'variable' attribute of this
   * {@link EventAssignment}.
   */
 public String getVariable() {
    return libsbmlJNI.EventAssignment_getVariable(swigCPtr, this);
  }

  
  /**
   * Get the mathematical expression in this {@link EventAssignment}'s 'math'
   * subelement.
   * <p>
   * @return the top {@link ASTNode} of an abstract syntax tree representing the
   * mathematical formula in this {@link EventAssignment}.
   */
 public ASTNode getMath() {
    long cPtr = libsbmlJNI.EventAssignment_getMath(swigCPtr, this);
    return (cPtr == 0) ? null : new ASTNode(cPtr, false);
  }

  
  /**
   * Predicate for testing whether the attribute 'variable' of this
   * {@link EventAssignment} is set.
   * <p>
   * @return <code>true</code> if the 'variable' attribute of this {@link EventAssignment}
   * is set, <code>false</code> otherwise.
   */
 public boolean isSetVariable() {
    return libsbmlJNI.EventAssignment_isSetVariable(swigCPtr, this);
  }

  
  /**
   * Predicate for testing whether the 'math' subelement of this
   * {@link EventAssignment} is set.
   * <p>
   * @return <code>true</code> if this {@link EventAssignment} has a 'math' subelement,
   * <code>false</code> otherwise.
   */
 public boolean isSetMath() {
    return libsbmlJNI.EventAssignment_isSetMath(swigCPtr, this);
  }

  
  /**
   * Sets the attribute 'variable' of this {@link EventAssignment} to a copy of
   * the given identifier string.
   * <p>
   * @param sid the identifier of a {@link Compartment}, {@link Species} or (global)
   * {@link Parameter} defined in this model.
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INVALID_ATTRIBUTE_VALUE LIBSBML_INVALID_ATTRIBUTE_VALUE }
   */
 public int setVariable(String sid) {
    return libsbmlJNI.EventAssignment_setVariable(swigCPtr, this, sid);
  }

  
  /**
   * Sets the 'math' subelement of this {@link EventAssignment} to a copy of the
   * given {@link ASTNode}.
   * <p>
   * @param math an {@link ASTNode} that will be copied and stored as the
   * mathematical formula for this {@link EventAssignment}.
   * <p>
   * @return integer value indicating success/failure of the
   * function.   The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INVALID_OBJECT LIBSBML_INVALID_OBJECT }
   */
 public int setMath(ASTNode math) {
    return libsbmlJNI.EventAssignment_setMath(swigCPtr, this, ASTNode.getCPtr(math), math);
  }

  
  /**
   * Calculates and returns a {@link UnitDefinition} that expresses the units
   * of measurement assumed for the 'math' expression of this
   * {@link EventAssignment}.
   * <p>
   * The units are calculated based on the mathematical expression in the
   * {@link EventAssignment} and the model quantities referenced by
   * <code>&lt;ci&gt;</code> elements used within that expression.  The
   * {@link EventAssignment#getDerivedUnitDefinition()} method returns the
   * calculated units.
   * <p>
   * Note that the functionality that facilitates unit analysis depends 
   * on the model as a whole.  Thus, in cases where the object has not 
   * been added to a model or the model itself is incomplete,
   * unit analysis is not possible and this method will return <code>null.</code>
   * <p>
   * @warning Note that it is possible the 'math' expression in the
   * {@link EventAssignment} contains literal numbers or parameters with undeclared
   * units.  In those cases, it is not possible to calculate the units of
   * the overall expression without making assumptions.  LibSBML does not
   * make assumptions about the units, and
   * {@link EventAssignment#getDerivedUnitDefinition()} only returns the units as
   * far as it is able to determine them.  For example, in an expression
   * <em>X + Y</em>, if <em>X</em> has unambiguously-defined units and
   * <em>Y</em> does not, it will return the units of <em>X</em>.  When
   * using this method, <strong>it is critical that callers also invoke the
   * method</strong> {@link EventAssignment#containsUndeclaredUnits()} <strong>to
   * determine whether this situation holds</strong>.  Callers should take
   * suitable action in those situations.
   * <p>
   * @return a {@link UnitDefinition} that expresses the units of the math 
   * expression of this {@link EventAssignment}, or <code>null</code> if one cannot be constructed.
   * <p>
   * @see #containsUndeclaredUnits()
   */
 public UnitDefinition getDerivedUnitDefinition() {
    long cPtr = libsbmlJNI.EventAssignment_getDerivedUnitDefinition__SWIG_0(swigCPtr, this);
    return (cPtr == 0) ? null : new UnitDefinition(cPtr, false);
  }

  
  /**
   * Predicate returning <code>true</code> if the math
   * expression of this {@link EventAssignment} contains literal numbers or
   * parameters with undeclared units.
   * <p>
   * The {@link EventAssignment#getDerivedUnitDefinition()} method returns what
   * libSBML computes to be the units of the 'math', to the extent that
   * libSBML can compute them.  However, if the expression contains literal
   * numbers or parameters with undeclared units, libSBML may not be able
   * to compute the full units of the expression and will only return what
   * it can compute.  Callers should always use
   * {@link EventAssignment#containsUndeclaredUnits()} when using
   * {@link EventAssignment#getDerivedUnitDefinition()} to decide whether the
   * returned units may be incomplete.
   * <p>
   * @return <code>true</code> if the math expression of this {@link EventAssignment}
   * includes parameters/numbers 
   * with undeclared units, <code>false</code> otherwise.
   * <p>
   * @note A return value of <code>true</code> indicates that the {@link UnitDefinition}
   * returned by {@link EventAssignment#getDerivedUnitDefinition()} may not
   * accurately represent the units of the expression.
   * <p>
   * @see #getDerivedUnitDefinition()
   */
 public boolean containsUndeclaredUnits() {
    return libsbmlJNI.EventAssignment_containsUndeclaredUnits__SWIG_0(swigCPtr, this);
  }

  
  /**
   * Returns the libSBML type code of this object instance.
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
    return libsbmlJNI.EventAssignment_getTypeCode(swigCPtr, this);
  }

  
  /**
   * Returns the XML element name of this object, which for
   * {@link EventAssignment}, is always <code>'eventAssignment'.</code>
   * <p>
   * @return the name of this element, i.e., <code>'eventAssignment'.</code> 
   */
 public String getElementName() {
    return libsbmlJNI.EventAssignment_getElementName(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> if
   * all the required attributes for this {@link EventAssignment} object
   * have been set.
   * <p>
   * @note The required attributes for a {@link EventAssignment} object are:
   * <li> 'variable'
   * <p>
   * @return a boolean value indicating whether all the required
   * attributes for this object have been defined.
   */
 public boolean hasRequiredAttributes() {
    return libsbmlJNI.EventAssignment_hasRequiredAttributes(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> if
   * all the required elements for this {@link EventAssignment} object
   * have been set.
   * <p>
   * @note The required elements for a {@link EventAssignment} object are:
   * <li> 'math'
   * <p>
   * @return a boolean value indicating whether all the required
   * elements for this object have been defined.
   */
 public boolean hasRequiredElements() {
    return libsbmlJNI.EventAssignment_hasRequiredElements(swigCPtr, this);
  }

  
  /**
   * Predicate returning <code>true</code> if
   * all the required elements for this {@link EventAssignment} object
   * have been set.
   * <p>
   * @note The required elements for a {@link EventAssignment} object are:
   * <li> 'math'
   * <p>
   * @return a boolean value indicating whether all the required
   * elements for this object have been defined.
   <p>
 * @deprecated libSBML internal
 */
 public String getId() {
    return libsbmlJNI.EventAssignment_getId(swigCPtr, this);
  }

}
