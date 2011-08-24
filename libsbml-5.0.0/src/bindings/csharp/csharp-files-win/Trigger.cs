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
 * LibSBML implementation of %SBML's %Trigger construct for %Event.
 *
 * An Event object defines when the event can occur, the variables that are
 * affected by the event, and how the variables are affected.  The Trigger
 * construct in SBML is used to define a mathematical expression that
 * determines when an Event is @em triggered.
 *
 * A Trigger object in SBML Level&nbsp;2 and Level&nbsp;3 contains one
 * subelement named 'math' containing a MathML expression.  The expression
 * must evaluate to a value of type @c bool.  The exact moment at which
 * the expression evaluates to @c true is the time point when the Event is
 * @em triggered.  In SBML Level&nbsp;3, Trigger has additional attributes
 * that must be assigned values; they are discussed in a separate section
 * below.
 * 
 * An event only @em triggers when its Trigger expression makes the
 * transition in value from @c false to @c true.  The event will also
 * trigger at any subsequent time points when the trigger makes this
 * transition; in other words, an event can be triggered multiple times
 * during a simulation if its trigger condition makes the transition from
 * @c false to @c true more than once.  In SBML Level&nbsp;3, the behavior
 * at the very start of simulation (i.e., at <em>t = 0</em>, where
 * <em>t</em> stands for time) is determined in part by the bool flag
 * 'initialValue'.  This and other additional features introduced in SBML
 * Level&nbsp;3 are discussed further below.
 *
 * @section version-diffs Version differences
 *
 * SBML Level&nbsp;3 Version&nbsp;1 introduces two required attributes
 * on the Trigger object: 'persistent' and 'initialValue'.  The rest of
 * this introduction describes these two attributes.
 *
 * @subsection trigger-persistent The 'persistent' attribute on Trigger
 *
 * In the interval between when an Event object <em>triggers</em> (i.e.,
 * its Trigger object expression transitions in value from @c false to
 * @c true) and when its assignments are to be <em>executed</em>, conditions
 * in the model may change such that the trigger expression transitions
 * back from @c true to @c false.  Should the event's assignments still be
 * made if this happens?  Answering this question is the purpose of the
 * 'persistent' attribute on Trigger.
 * 
 * If the bool attribute 'persistent' has a value of @c true, then once
 * the event is triggered, all of its assignments are always performed when
 * the time of execution is reached.  The name @em persistent is meant to
 * evoke the idea that the trigger expression does not have to be
 * re-checked after it triggers if 'persistent'=@c true.  Conversely, if
 * the attribute value is @c false, then the trigger expression is not
 * assumed to persist: if the expression transitions in value back to @c
 * false at any time between when the event triggered and when it is to be
 * executed, the event is no longer considered to have triggered and its
 * assignments are not executed.  (If the trigger expression transitions
 * once more to @c true after that point, then the event is triggered, but
 * this then constitutes a whole new event trigger-and-execute sequence.)
 * 
 * The 'persistent' attribute can be especially useful when Event objects
 * contain Delay objects, but it is relevant even in a model without delays
 * if the model contains two or more events.  As explained in the
 * introduction to this section, the operation of all events in SBML
 * (delayed or not) is conceptually divided into two phases,
 * <em>triggering</em> and <em>execution</em>; however, unless events have
 * priorities associated with them, SBML does not mandate a particular
 * ordering of event execution in the case of simultaneous events.  Models
 * with multiple events can lead to situations where the execution of one
 * event affects another event's trigger expression value.  If that other
 * event has 'persistent'=@c false, and its trigger expression evaluates to
 * @c false before it is to be executed, the event must not be executed
 * after all.
 * 
 * @subsection trigger-initialvalue The 'initialValue' attribute on Trigger
 * 
 * As mentioned above, an event <em>triggers</em> when the mathematical
 * expression in its Trigger object transitions in value from @c false to
 * @c true.  An unanswered question concerns what happens at the start of a
 * simulation: can event triggers make this transition at <em>t = 0</em>,
 * where <em>t</em> stands for time?
 * 
 * In order to determine whether an event may trigger at <em>t = 0</em>, it
 * is necessary to know what value the Trigger object's 'math' expression
 * had immediately prior to <em>t = 0</em>.  This starting value of the
 * trigger expression is determined by the value of the bool attribute
 * 'initialValue'.  A value of @c true means the trigger expression is
 * taken to have the value @c true immediately prior to <em>t = 0</em>.  In
 * that case, the trigger cannot transition in value from @c false to @c
 * true at the moment simulation begins (because it has the value @c true
 * both before and after <em>t = 0</em>), and can only make the transition
 * from @c false to @c true sometime <em>after</em> <em>t = 0</em>.  (To do
 * that, it would also first have to transition to @c false before it could
 * make the transition from @c false back to @c true.)  Conversely, if
 * 'initialValue'=@c false, then the trigger expression is assumed to start
 * with the value @c false, and therefore may trigger at <em>t = 0</em> if
 * the expression evaluates to @c true at that moment.
 * 
 *
 * @see Event
 * @see Delay
 * @see EventAssignment
 */
public class Trigger : SBase {
	private HandleRef swigCPtr;
	
	internal Trigger(IntPtr cPtr, bool cMemoryOwn) : base(libsbmlPINVOKE.Trigger_SWIGUpcast(cPtr), cMemoryOwn)
	{
		//super(libsbmlPINVOKE.TriggerUpcast(cPtr), cMemoryOwn);
		swigCPtr = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(Trigger obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (Trigger obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~Trigger() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_Trigger(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  
  /**
   * Creates a new Trigger using the given SBML @p level and @p version
   * values.
   *
   * @param level a long integer, the SBML Level to assign to this Trigger
   *
   * @param version a long integer, the SBML Version to assign to this
   * Trigger
   */
 public Trigger(long level, long version) : this(libsbmlPINVOKE.new_Trigger__SWIG_0(level, version), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates a new Trigger using the given SBMLNamespaces object
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
   */
 public Trigger(SBMLNamespaces sbmlns) : this(libsbmlPINVOKE.new_Trigger__SWIG_1(SBMLNamespaces.getCPtr(sbmlns)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Copy constructor; creates a copy of this Trigger.
   */
 public Trigger(Trigger orig) : this(libsbmlPINVOKE.new_Trigger__SWIG_2(Trigger.getCPtr(orig)), true) {
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
  }

  
  /**
   * Creates and returns a deep copy of this Trigger.
   *
   * @return a (deep) copy of this Trigger.
   */
 public new Trigger clone() {
    IntPtr cPtr = libsbmlPINVOKE.Trigger_clone(swigCPtr);
    Trigger ret = (cPtr == IntPtr.Zero) ? null : new Trigger(cPtr, true);
    return ret;
  }

  
  /**
   * Get the mathematical formula for the trigger and return it
   * as an AST.
   * 
   * @return the math of this Trigger.
   */
 public ASTNode getMath() {
    IntPtr cPtr = libsbmlPINVOKE.Trigger_getMath(swigCPtr);
    ASTNode ret = (cPtr == IntPtr.Zero) ? null : new ASTNode(cPtr, false);
    return ret;
  }

  
  /**
   * (SBML Level&nbsp;3 only) Get the value of the 'initialValue' attribute
   * of this Trigger.
   * 
   * @return the bool value stored as the 'initialValue' attribute value
   * in this Trigger.
   * 
   * @note The attribute 'initialValue' is available in SBML Level&nbsp;3
   * Version&nbsp;1 Core, but is not present in lower Levels of SBML.
   */
 public bool getInitialValue() {
    bool ret = libsbmlPINVOKE.Trigger_getInitialValue(swigCPtr);
    return ret;
  }

  
  /**
   * (SBML Level&nbsp;3 only) Get the value of the 'persistent' attribute
   * of this Trigger.
   * 
   * @return the bool value stored as the 'persistent' attribute value
   * in this Trigger.
   * 
   * @note The attribute 'persistent' is available in SBML Level&nbsp;3
   * Version&nbsp;1 Core, but is not present in lower Levels of SBML.
   */
 public bool getPersistent() {
    bool ret = libsbmlPINVOKE.Trigger_getPersistent(swigCPtr);
    return ret;
  }

  
  /**
   * Predicate to test whether the math for this trigger is set.
   *
   * @return @c true if the formula (meaning the 'math' subelement) of
   * this Trigger is set, @c false otherwise.
   */
 public bool isSetMath() {
    bool ret = libsbmlPINVOKE.Trigger_isSetMath(swigCPtr);
    return ret;
  }

  
  /**
   * (SBML Level&nbsp;3 only) Predicate to test whether the 'initialValue'
   * attribute for this trigger is set.
   *
   * @return @c true if the initialValue attribute of
   * this Trigger is set, @c false otherwise.
   * 
   * @note The attribute 'initialValue' is available in SBML Level&nbsp;3
   * Version&nbsp;1 Core, but is not present in lower Levels of SBML.
   */
 public bool isSetInitialValue() {
    bool ret = libsbmlPINVOKE.Trigger_isSetInitialValue(swigCPtr);
    return ret;
  }

  
  /**
   * (SBML Level&nbsp;3 only) Predicate to test whether the 'persistent'
   * attribute for this trigger is set.
   *
   * @return @c true if the persistent attribute of
   * this Trigger is set, @c false otherwise.
   * 
   * @note The attribute 'persistent' is available in SBML Level&nbsp;3
   * Version&nbsp;1 Core, but is not present in lower Levels of SBML.
   */
 public bool isSetPersistent() {
    bool ret = libsbmlPINVOKE.Trigger_isSetPersistent(swigCPtr);
    return ret;
  }

  
  /**
   * Sets the trigger expression of this Trigger instance to a copy of the given
   * ASTNode.
   *
   * @param math an ASTNode representing a formula tree.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link libsbmlcs.libsbml.LIBSBML_INVALID_OBJECT LIBSBML_INVALID_OBJECT @endlink
   */
 public int setMath(ASTNode math) {
    int ret = libsbmlPINVOKE.Trigger_setMath(swigCPtr, ASTNode.getCPtr(math));
    return ret;
  }

  
  /**
   * (SBML Level&nbsp;3 only) Sets the 'initialValue' attribute of this Trigger instance.
   *
   * @param initialValue a bool representing the initialValue to be set.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link libsbmlcs.libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE LIBSBML_UNEXPECTED_ATTRIBUTE @endlink
   * 
   * @note The attribute 'initialValue' is available in SBML Level&nbsp;3
   * Version&nbsp;1 Core, but is not present in lower Levels of SBML.
   */
 public int setInitialValue(bool initialValue) {
    int ret = libsbmlPINVOKE.Trigger_setInitialValue(swigCPtr, initialValue);
    return ret;
  }

  
  /**
   * (SBML Level&nbsp;3 only) Sets the 'persistent' attribute of this Trigger instance.
   *
   * @param persistent a bool representing the persistent value to be set.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link libsbmlcs.libsbml.LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link libsbmlcs.libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE LIBSBML_UNEXPECTED_ATTRIBUTE @endlink
   * 
   * @note The attribute 'persistent' is available in SBML Level&nbsp;3
   * Version&nbsp;1 Core, but is not present in lower Levels of SBML.
   */
 public int setPersistent(bool persistent) {
    int ret = libsbmlPINVOKE.Trigger_setPersistent(swigCPtr, persistent);
    return ret;
  }

  
  /**
   * Returns the libSBML type code of this object instance.
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
    int ret = libsbmlPINVOKE.Trigger_getTypeCode(swigCPtr);
    return ret;
  }

  
  /**
   * Returns the XML element name of this object, which for Trigger, is
   * always @c 'trigger'.
   * 
   * @return the name of this element, i.e., @c 'trigger'. 
   */
 public new string getElementName() {
    string ret = libsbmlPINVOKE.Trigger_getElementName(swigCPtr);
    return ret;
  }

  
  /**
   * Predicate returning @c true if
   * all the required elements for this Trigger object
   * have been set.
   *
   * @note The required elements for a Trigger object are:
   * math
   *
   * @return a bool value indicating whether all the required
   * elements for this object have been defined.
   */
 public new bool hasRequiredElements() {
    bool ret = libsbmlPINVOKE.Trigger_hasRequiredElements(swigCPtr);
    return ret;
  }

  
  /**
   * Predicate returning @c true if
   * all the required attributes for this Trigger object
   * have been set.
   *
   * @note The required attributes for a Trigger object are:
   * @li 'persistent' (required in SBML Level&nbsp;3)
   * @li 'initialValue' (required in SBML Level&nbsp;3)
   *
   * @return a bool value indicating whether all the required
   * attributes for this object have been defined.
   */
 public new bool hasRequiredAttributes() {
    bool ret = libsbmlPINVOKE.Trigger_hasRequiredAttributes(swigCPtr);
    return ret;
  }

}

}
