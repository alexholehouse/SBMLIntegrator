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
 * LibSBML implementation of %SBML's %RateRule construct.
 *
 * The rule type RateRule is derived from the parent class Rule.  It is
 * used to express equations that determine the rates of change of
 * variables.  The left-hand side (the 'variable' attribute) can refer to
 * the identifier of a species, compartment, or parameter (but not a
 * reaction).  The entity identified must have its 'constant' attribute set
 * to @c false.  The effects of a RateRule are in general terms the same,
 * but differ in the precise details depending on which variable is being
 * set:
 * 
 * <ul> <li> <em>In the case of a species</em>, a RateRule sets the rate of
 * change of the species' quantity (<em>concentration</em> or <em>amount of
 * substance</em>) to the value determined by the formula in the 'math'
 * subelement of the RateRule object.  The overall units of the formula in
 * 'math' @em should (in SBML Level&nbsp;2 Version&nbsp;4 and in SBML Level&nbsp;3) or @em
 * must (in SBML releases prior to Level&nbsp;2 version&nbsp;4) be equal to
 * the unit of <em>species quantity</em> divided by the model-wide unit of
 * <em>time</em>.  <em>Restrictions</em>: There must not be both a RateRule
 * 'variable' attribute and a SpeciesReference 'species' attribute having
 * the same value, unless that species has its 'boundaryCondition'
 * attribute is set to @c true.  This means a rate rule cannot be defined
 * for a species that is created or destroyed in a reaction, unless that
 * species is defined as a boundary condition in the model.
 *
 * <li> (For SBML Level&nbsp;3 only) <em>In the case of a species
 * reference</em>, a RateRule sets the rate of change of the stoichiometry
 * of the referenced reactant or product to the value determined by the
 * formula in 'math'.  The unit associated with the value produced by the
 * 'math' formula should be consistent with the unit 'dimensionless'
 * divided by the model-wide unit of <em>time</em>.
 *
 * <li> <em>In the case of a compartment</em>, a RateRule sets the rate of
 * change of the compartment's size to the value determined by the formula
 * in the 'math' subelement of the RateRule object.  The overall units of
 * the formula @em should (in SBML Level&nbsp;2 Version&nbsp;4 and in SBML
 * Level&nbsp;3) or @em must (in SBML releases prior to Level&nbsp;2
 * version&nbsp;4) be the units of the compartment's <em>size</em> divided
 * by the model-wide unit of <em>time</em>.
 *
 * <li> <em>In the case of a parameter</em>, a RateRule sets the rate of
 * change of the parameter's value to that determined by the formula in the
 * 'math' subelement of the RateRule object.  The overall units of the
 * formula @em should (in SBML Level&nbsp;2 Version&nbsp;4 and in SBML
 * Level&nbsp;3) or @em must (in SBML releases prior to Level&nbsp;2
 * version&nbsp;4) be the Parameter object's 'unit' attribute value divided
 * by the model-wide unit of <em>time</em>.  </ul>
 * 
 * In the context of a simulation, rate rules are in effect for simulation
 * time <em>t</em> &lt; <em>0</em>.  Please consult the relevant SBML
 * specification for additional information about the semantics of
 * assignments, rules, and entity values for simulation time <em>t</em>
 * <= <em>0</em>.
 *
 * As mentioned in the description of AssignmentRule, a model must not
 * contain more than one RateRule or AssignmentRule object having the same
 * value of 'variable'; in other words, in the set of all assignment rules
 * and rate rules in an SBML model, each variable appearing in the
 * left-hand sides can only appear once.  This simply follows from the fact
 * that an indeterminate system would result if a model contained more than
 * one assignment rule for the same variable or both an assignment rule and
 * a rate rule for the same variable.
 * 
 * @section general General summary of SBML rules
 *
 * In SBML Level&nbsp;3 as well as Level&nbsp;2, rules are separated into
 * three subclasses for the benefit of model analysis software.  The three
 * subclasses are based on the following three different possible
 * functional forms (where <em>x</em> is a variable, <em>f</em> is some
 * arbitrary function returning a numerical result, <b><em>V</em></b> is a
 * vector of variables that does not include <em>x</em>, and
 * <b><em>W</em></b> is a vector of variables that may include <em>x</em>):
 * 
 * <center>
 * <table border='0' cellpadding='0' style='font-size: small'>
 * <tr><td width='120px'><em>Algebraic:</em></td><td width='250px'>left-hand side is zero</td><td><em>0 = f(<b>W</b>)</em></td></tr>
 * <tr><td><em>Assignment:</em></td><td>left-hand side is a scalar:</td><td><em>x = f(<b>V</b>)</em></td></tr>
 * <tr><td><em>Rate:</em></td><td>left-hand side is a rate-of-change:</td><td><em>dx/dt = f(<b>W</b>)</em></td></tr>
 * </table>
 * </center>
 * 
 * In their general form given above, there is little to distinguish
 * between <em>assignment</em> and <em>algebraic</em> rules.  They are treated as
 * separate cases for the following reasons:
 *
 * <ul>
 * <li> <em>Assignment</em> rules can simply be evaluated to calculate
 * intermediate values for use in numerical methods.  They are statements
 * of equality that hold at all times.  (For assignments that are only
 * performed once, see InitialAssignment.)<p>
 * 
 * <li> SBML needs to place restrictions on assignment rules, for example
 * the restriction that assignment rules cannot contain algebraic loops.<p>
 * 
 * <li> Some simulators do not contain numerical solvers capable of solving
 * unconstrained algebraic equations, and providing more direct forms such
 * as assignment rules may enable those simulators to process models they
 * could not process if the same assignments were put in the form of
 * general algebraic equations;<p>
 * 
 * <li> Those simulators that <em>can</em> solve these algebraic equations make a
 * distinction between the different categories listed above; and<p>
 * 
 * <li> Some specialized numerical analyses of models may only be applicable
 * to models that do not contain <em>algebraic</em> rules.
 * </ul>
 * 
 * The approach taken to covering these cases in SBML is to define an
 * abstract Rule structure containing a subelement, 'math', to hold the
 * right-hand side expression, then to derive subtypes of Rule that add
 * attributes to distinguish the cases of algebraic, assignment and rate
 * rules.  The 'math' subelement must contain a MathML expression defining the
 * mathematical formula of the rule.  This MathML formula must return a
 * numerical value.  The formula can be an arbitrary expression referencing
 * the variables and other entities in an SBML model.
 * 
 * Each of the three subclasses of Rule (AssignmentRule, AlgebraicRule,
 * RateRule) inherit the the 'math' subelement and other fields from SBase.
 * The AssignmentRule and RateRule classes add an additional attribute,
 * 'variable'.  See the definitions of AssignmentRule, AlgebraicRule and
 * RateRule for details about the structure and interpretation of each one.
 * 
 * @section additional-restrictions Additional restrictions on SBML rules
 * 
 * An important design goal of SBML rule semantics is to ensure that a
 * model's simulation and analysis results will not be dependent on when or
 * how often rules are evaluated.  To achieve this, SBML needs to place two
 * restrictions on rule use.  The first concerns algebraic loops in the system
 * of assignments in a model, and the second concerns overdetermined systems.
 * 
 * @subsection no-algebraic-loops A model must not contain algebraic loops
 * 
 * The combined set of InitialAssignment, AssignmentRule and KineticLaw
 * objects in a model constitute a set of assignment statements that should be
 * considered as a whole.  (A KineticLaw object is counted as an assignment
 * because it assigns a value to the symbol contained in the 'id' attribute of
 * the Reaction object in which it is defined.)  This combined set of
 * assignment statements must not contain algebraic loops&mdash;dependency
 * chains between these statements must terminate.  To put this more formally,
 * consider a directed graph in which nodes are assignment statements and
 * directed arcs exist for each occurrence of an SBML species, compartment or
 * parameter symbol in an assignment statement's 'math' subelement.  Let the
 * directed arcs point from the statement assigning the symbol to the
 * statements that contain the symbol in their 'math' subelement expressions.
 * This graph must be acyclic.
 * 
 * SBML does not specify when or how often rules should be evaluated.
 * Eliminating algebraic loops ensures that assignment statements can be
 * evaluated any number of times without the result of those evaluations
 * changing.  As an example, consider the set of equations <em>x = x + 1</em>,
 * <em>y = z + 200</em> and <em>z = y + 100</em>.  If this set of equations
 * were interpreted as a set of assignment statements, it would be invalid
 * because the rule for <em>x</em> refers to <em>x</em> (exhibiting one type
 * of loop), and the rule for <em>y</em> refers to <em>z</em> while the rule
 * for <em>z</em> refers back to <em>y</em> (exhibiting another type of loop).
 * Conversely, the following set of equations would constitute a valid set of
 * assignment statements: <em>x = 10</em>, <em>y = z + 200</em>, and <em>z = x
 * + 100</em>.
 * 
 * @subsection no-overdetermined A model must not be overdetermined
 * 
 * An SBML model must not be overdetermined; that is, a model must not
 * define more equations than there are unknowns in a model.  An SBML model
 * that does not contain AlgebraicRule structures cannot be overdetermined.
 * 
 * LibSBML implements the static analysis procedure described in
 * Appendix&nbsp;B of the SBML Level&nbsp;3 Version&nbsp;1 Core
 * specification for assessing whether a model is overdetermined.
 * 
 * (In summary, assessing whether a given continuous, deterministic,
 * mathematical model is overdetermined does not require dynamic analysis; it
 * can be done by analyzing the system of equations created from the model.
 * One approach is to construct a bipartite graph in which one set of vertices
 * represents the variables and the other the set of vertices represents the
 * equations.  Place edges between vertices such that variables in the system
 * are linked to the equations that determine them.  For algebraic equations,
 * there will be edges between the equation and each variable occurring in the
 * equation.  For ordinary differential equations (such as those defined by
 * rate rules or implied by the reaction rate definitions), there will be a
 * single edge between the equation and the variable determined by that
 * differential equation.  A mathematical model is overdetermined if the
 * maximal matchings of the bipartite graph contain disconnected vertexes
 * representing equations.  If one maximal matching has this property, then
 * all the maximal matchings will have this property; i.e., it is only
 * necessary to find one maximal matching.)
 *
 *
 * @section RuleType_t Rule types for SBML Level 1
 *
 * SBML Level 1 uses a different scheme than SBML Level&nbsp;2 and
 * Level&nbsp;3 for distinguishing rules; specifically, it uses an
 * attribute whose value is drawn from an enumeration of 3 values.  LibSBML
 * supports this using methods that work @if clike a libSBML enumeration
 * type, #RuleType_t, whose values are @else with the enumeration
 * values @endif listed in the following table.  
 * 
 * <p>
 * <center>
 * <table width='90%' cellspacing='1' cellpadding='1' border='0' class='normal-font'>
 *  <tr style='background: lightgray' class='normal-font'>
 *      <td><strong>Enumerator</strong></td>
 *      <td><strong>Meaning</strong></td>
 *  </tr>
 * <tr><td><c>@link libsbmlcs.libsbml.RULE_TYPE_RATE RULE_TYPE_RATE@endlink</c></td><td>Indicates the rule is a 'rate' rule.</td>
 * <tr><td><c>@link libsbmlcs.libsbml.RULE_TYPE_SCALAR RULE_TYPE_SCALAR@endlink</c></td><td>Indicates the rule is a 'scalar' rule.</td>
 * <tr><td><c>@link libsbmlcs.libsbml.RULE_TYPE_INVALID RULE_TYPE_INVALID@endlink</c></td><td>Indicates the rule type is unknown or not
 * yet set.</td>
 * </table>
 * </center>
 *
 * <!-- leave this next break as-is to work around some doxygen bug -->
 */
public class RateRule : Rule {
	private HandleRef swigCPtr;
	
	internal RateRule(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.RateRule_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.RateRuleUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(RateRule obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (RateRule obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~RateRule() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_RateRule(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  
  /**
   * Creates a new RateRule using the given SBML @p level and @p version
   * values.
   *
   * @param level a long integer, the SBML Level to assign to this RateRule
   *
   * @param version a long integer, the SBML Version to assign to this
   * RateRule
   * 
   * @note Upon the addition of a RateRule object to an SBMLDocument
   * (e.g., using&nbsp; @if java Model::addRule(Rule r)@else Model::addRule()@endif, the SBML Level, SBML Version
   * and XML namespace of the document @em override the values used
   * when creating the RateRule object via this constructor.  This is
   * necessary to ensure that an SBML document is a consistent structure.
   * Nevertheless, the ability to supply the values at the time of creation
   * of a RateRule is an important aid to producing valid SBML.  Knowledge
   * of the intented SBML Level and Version determine whether it is valid
   * to assign a particular value to an attribute, or whether it is valid
   * to add an object to an existing SBMLDocument.
  */
 public RateRule(long level, long version) : this(libsbmlPINVOKE.new_RateRule__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates a new RateRule using the given SBMLNamespaces object
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
   * @note Upon the addition of a RateRule object to an SBMLDocument (e.g.,
   * using @if java Model::addRule(Rule r)@else Model::addRule()@endif, the SBML XML namespace of the document
   * @em overrides the value used when creating the RateRule object via
   * this constructor.  This is necessary to ensure that an SBML document
   * is a consistent structure.  Nevertheless, the ability to supply the
   * values at the time of creation of a RateRule is an important aid to
   * producing valid SBML.  Knowledge of the intented SBML Level and
   * Version determine whether it is valid to assign a particular value to
   * an attribute, or whether it is valid to add an object to an existing
   * SBMLDocument.
   */
 public RateRule(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_RateRule__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates and returns a deep copy of this Rule.
   * 
   * @return a (deep) copy of this Rule.
   */
 public new RateRule clone() {
    IntPtr cPtr = libsbmlPINVOKE.RateRule_clone(swigCPtr);
    RateRule ret = (cPtr == IntPtr.Zero) ? null : new RateRule(cPtr, true);
    return ret;
  }

  
  /**
   * Predicate returning @c true if
   * all the required attributes for this RateRule object
   * have been set.
   *
   * @note In SBML Levels&nbsp;2&ndash;3, the only required attribute for a
   * RateRule object is 'variable'.  For Level&nbsp;1, where the equivalent
   * attribute is known by different names ('compartment', 'species', or
   * 'name', depending on the type of object), there is an additional
   * required attribute called 'formula'.
   *
   * @return @c true if the required attributes have been set, @c false
   * otherwise.
   */
 public new bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.RateRule_hasRequiredAttributes(swigCPtr);
    return ret;
  }

}

}
