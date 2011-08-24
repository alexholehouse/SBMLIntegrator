package org.sbml.libsbml;

/**
 * Constants defined in libSBML.
 * <p>
 * <em style='color: #555'>
 * This interace class is defined by libSBML only and has no direct
 * equivalent in terms of SBML components.
 * </em>
 * <p>
 * This interface is necessary because of programming language differences
 * between Java and the underlying C++ core of libSBML's implementation, as
 * well as limitations in the translation system (SWIG) used to create the
 * Java interface.  In the C++ core, nearly all of the following constants
 * are defined as enumerations.  However, owing to how SWIG works and the
 * lack of proper enumerations in Java before Java 1.4, the enumerations
 * are instead translated to plain constants here in this {@link
 * libsbmlConstants} interface.
 */   
public interface libsbmlConstants
{
    /**
     * A version string of the form "1.2.3".
     */
    public final static String LIBSBML_DOTTED_VERSION = "4.2.0";


    /**
     * The version as an integer: version 1.2.3 becomes 10203.  Since the major
     * number comes first, the overall number will always increase when a new
     * libSBML is released, making it easy to use less-than and greater-than
     * comparisons when testing versions numbers.
     */
    public final static int LIBSBML_VERSION = 40200;


    /**
     * The numeric version as a string: version 1.2.3 becomes "10203".
     */
    public final static String LIBSBML_VERSION_STRING = "40200";
    // OperationReturnValues_t 
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The operation was successful.
     */
    public final static int LIBSBML_OPERATION_SUCCESS = 0;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: An index parameter exceeded the
     * bounds of a data array or other collection used in the operation.
     * This return value is typically returned by methods that take index
     * numbers to refer to lists of objects, when the caller has provided
     * an index that exceeds the bounds of the list.  LibSBML provides
     * methods for checking the size of list/sequence/collection
     * structures, and callers should verify the sizes before calling
     * methods that take index numbers.
     */
    public final static int LIBSBML_INDEX_EXCEEDS_SIZE = -1;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The attribute that is the
     * subject of this operation is not valid for the combination of SBML
     * Level and Version for the underlying object.  This can happen
     * because libSBML strives to offer a uniform API for all SBML Levels
     * and Versions, but some object attributes and elements are not
     * defined for all SBML Levels and Versions.  Calling programs are
     * expected to be aware of which object structures they are working
     * with, but when errors of this kind occur, they are reported using
     * this return value.
     */
    public final static int LIBSBML_UNEXPECTED_ATTRIBUTE = -2;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The requested action could not
     * be performed.  This can occur in a variety of contexts, such as
     * passing a null object as a parameter in a situation where it does
     * not make sense to permit a null object.
     */
    public final static int LIBSBML_OPERATION_FAILED = -3;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: A value passed as an argument
     * to the method is not of a type that is valid for the operation or
     * kind of object involved.  For example, this return code is used when
     * a calling program attempts to set an SBML object identifier to a
     * string whose syntax does not conform to the SBML identifier syntax.
     */
    public final static int LIBSBML_INVALID_ATTRIBUTE_VALUE = -4;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The object passed as an
     * argument to the method is not of a type that is valid for the
     * operation or kind of object involved.  For example, handing an
     * invalidly-constructed ASTNode to a method expecting an ASTNode will
     * result in this error.
     */
    public final static int LIBSBML_INVALID_OBJECT = -5;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: There already exists an object
     * with this identifier in the context where this operation is being
     * attempted.  This error is typically returned in situations where
     * SBML object identifiers must be unique, such as attempting to add
     * two species with the same identifier to a model.
     */
    public final static int LIBSBML_DUPLICATE_OBJECT_ID = -6;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The SBML Level associated with
     * the object does not match the Level of the parent object.  This
     * error can happen when an SBML component such as a species or
     * compartment object is created outside of a model and a calling
     * program then attempts to add the object to a model that has a
     * different SBML Level defined.
     */
    public final static int LIBSBML_LEVEL_MISMATCH = -7;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The SBML Version within the
     * SBML Level associated with the object does not match the Version of
     * the parent object.  This error can happen when an SBML component
     * such as a species or compartment object is created outside of a
     * model and a calling program then attempts to add the object to a
     * model that has a different SBML Level+Version combination.
     */
    public final static int LIBSBML_VERSION_MISMATCH = -8;
  

    /**
     * One of the possible libSBML operation return codes.
     *
     * This code has the following meaning: The XML operation attempted is
     * not valid for the object or context involved.  This error is
     * typically returned by the XML interface layer of libSBML, when a
     * calling program attempts to construct or manipulate XML in an
     * invalid way.
     */
    public final static int LIBSBML_INVALID_XML_OPERATION = -9;


    /**
     * One of the possible libSBML package operation return codes.
     *
     * This code has the following meaning: the Version of the package
     * extension within the SBML Level and version associated with the
     * object does not match the Version of the parent object. This error
     * can happen when an SBML component object is created outside of a
     * model, and a calling program then attempts to add the object to a
     * model that has a different SBML Level+Version+Package Version
     * combination.
     */
    public final static int LIBSBML_PKG_VERSION_MISMATCH  = -20;


    /**
     * One of the possible libSBML package operation return codes.
     *
     * This code has the following meaning: the required package extension
     * is unknown. This error is typically returned when creating an object
     * of SBase derived class with the required package, creating an object
     * of SBMLNamespaces or its derived class with the required package, or
     * invoking functions depending on the required package.  To avoid this
     * error, the library of the required package needs to be linked.
     */
    public final static int LIBSBML_PKG_UNKNOWN           = -21;


    /**
     * One of the possible libSBML package operation return codes.
     *
     * This code has the following meaning: The required version of the
     * package extension is unknown.  This error is typically returned when
     * creating an object of SBase derived class with the required package,
     * creating an object of SBMLNamespaces or its derived class with the
     * required package, or invoking functions depending on the required
     * package.  This error may be avoided by updating the library of the
     * required package to be linked.
     */
    public final static int LIBSBML_PKG_UNKNOWN_VERSION    = -22;


    /**
     * One of the possible libSBML package operation return codes.
     *
     * This code has the following meaning: The required package extension
     * is disabled.  This error is typically returned when creating an
     * object of SBase derived class with the required package, creating an
     * object of SBMLNamespaces or its derived class with the required
     * package, or invoking functions depending on the required package.
     * To avoid this error, the library of the required package needs to be
     * enabled.
     */
    public final static int LIBSBML_PKG_DISABLED            = -23;


    /**
     * One of the possible libSBML package operation return codes.
     *
     * This code has the following meaning: another version of the required
     * package extension has already been enabled in the target SBase
     * object, or enabled in the model to/in which the target object to be
     * added/contained. This error is typically returned when adding an
     * object of some SBase derived class with the required package to
     * other SBase derived object, or when enabling the required package in
     * the target object.  To avoid this error, the conflict of versions
     * need to be avoided.
     */
    public final static int LIBSBML_PKG_CONFLICTED_VERSION  = -24;


    /**
     * One of the possible libSBML package operation return codes.
     *
     * This code has the following meaning: another SBML package extension
     * for the same URI has already been registered. This error is
     * typically returned when adding a SBML package extension to the
     * SBMLExtensionRegistry. To avoid this error, ensure that SBML package
     * extensions are only registered once.
     */
    public final static int LIBSBML_PKG_CONFLICT            = -25;


    // SBMLTypeCode_t 

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_UNKNOWN = 0;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_COMPARTMENT = SBML_UNKNOWN + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_COMPARTMENT_TYPE = SBML_COMPARTMENT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_CONSTRAINT = SBML_COMPARTMENT_TYPE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_DOCUMENT = SBML_CONSTRAINT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_EVENT = SBML_DOCUMENT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_EVENT_ASSIGNMENT = SBML_EVENT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_FUNCTION_DEFINITION = SBML_EVENT_ASSIGNMENT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_INITIAL_ASSIGNMENT = SBML_FUNCTION_DEFINITION + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_KINETIC_LAW = SBML_INITIAL_ASSIGNMENT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LIST_OF = SBML_KINETIC_LAW + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_MODEL = SBML_LIST_OF + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_PARAMETER = SBML_MODEL + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_REACTION = SBML_PARAMETER + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_RULE = SBML_REACTION + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_SPECIES = SBML_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_SPECIES_REFERENCE = SBML_SPECIES + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_SPECIES_TYPE = SBML_SPECIES_REFERENCE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_MODIFIER_SPECIES_REFERENCE = SBML_SPECIES_TYPE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_UNIT_DEFINITION = SBML_MODIFIER_SPECIES_REFERENCE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_UNIT = SBML_UNIT_DEFINITION + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_ALGEBRAIC_RULE = SBML_UNIT + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_ASSIGNMENT_RULE = SBML_ALGEBRAIC_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_RATE_RULE = SBML_ASSIGNMENT_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_SPECIES_CONCENTRATION_RULE = SBML_RATE_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_COMPARTMENT_VOLUME_RULE = SBML_SPECIES_CONCENTRATION_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_PARAMETER_RULE = SBML_COMPARTMENT_VOLUME_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_TRIGGER = SBML_PARAMETER_RULE + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_DELAY = SBML_TRIGGER + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_STOICHIOMETRY_MATH = SBML_DELAY + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LOCAL_PARAMETER = SBML_STOICHIOMETRY_MATH + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_PRIORITY = SBML_LOCAL_PARAMETER + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_FORMULA_UNITS_DATA = SBML_PRIORITY + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LIST_FORMULA_UNITS_DATA = SBML_FORMULA_UNITS_DATA + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_COMPARTMENTS = SBML_LIST_FORMULA_UNITS_DATA + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_COMPARTMENT_TYPES = SBML_LISTOF_COMPARTMENTS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_CONSTRAINTS = SBML_LISTOF_COMPARTMENT_TYPES + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_EVENTS = SBML_LISTOF_CONSTRAINTS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_EVENT_ASSIGNMENTS = SBML_LISTOF_EVENTS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_FUNCTION_DEFINITIONS = SBML_LISTOF_EVENT_ASSIGNMENTS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_INITIAL_ASSIGNMENTS = SBML_LISTOF_FUNCTION_DEFINITIONS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_PARAMETERS = SBML_LISTOF_INITIAL_ASSIGNMENTS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_REACTIONS = SBML_LISTOF_PARAMETERS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_RULES = SBML_LISTOF_REACTIONS + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_SPECIES = SBML_LISTOF_RULES + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_SPECIES_REFERENCES = SBML_LISTOF_SPECIES + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_SPECIES_TYPES = SBML_LISTOF_SPECIES_REFERENCES + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_UNIT_DEFINITIONS = SBML_LISTOF_SPECIES_TYPES + 1;
  

    /**
     * One of the possible SBML component type codes.
     *
     * LibSBML attaches an identifying code to every kind of SBML object.
     * These are known as <em>SBML type codes</em>.  In other languages,
     * the set of type codes is stored in an enumeration; in the Java
     * language interface for libSBML, the type codes are defined as static
     * integer constants in the interface class {@link libsbmlConstants}.
     * The names of the type codes all begin with the characters
     * <code>SBML_</code>.
     */
    public final static int SBML_LISTOF_UNITS = SBML_LISTOF_UNIT_DEFINITIONS + 1;

    // UnitKind_t 

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_AMPERE = 0;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_AVOGADRO = UNIT_KIND_AMPERE + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_BECQUEREL = UNIT_KIND_AVOGADRO + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_CANDELA = UNIT_KIND_BECQUEREL + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_CELSIUS = UNIT_KIND_CANDELA + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_COULOMB = UNIT_KIND_CELSIUS + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_DIMENSIONLESS = UNIT_KIND_COULOMB + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_FARAD = UNIT_KIND_DIMENSIONLESS + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_GRAM = UNIT_KIND_FARAD + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_GRAY = UNIT_KIND_GRAM + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_HENRY = UNIT_KIND_GRAY + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_HERTZ = UNIT_KIND_HENRY + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_ITEM = UNIT_KIND_HERTZ + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_JOULE = UNIT_KIND_ITEM + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_KATAL = UNIT_KIND_JOULE + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_KELVIN = UNIT_KIND_KATAL + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_KILOGRAM = UNIT_KIND_KELVIN + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_LITER = UNIT_KIND_KILOGRAM + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_LITRE = UNIT_KIND_LITER + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_LUMEN = UNIT_KIND_LITRE + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_LUX = UNIT_KIND_LUMEN + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_METER = UNIT_KIND_LUX + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_METRE = UNIT_KIND_METER + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_MOLE = UNIT_KIND_METRE + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_NEWTON = UNIT_KIND_MOLE + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_OHM = UNIT_KIND_NEWTON + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_PASCAL = UNIT_KIND_OHM + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_RADIAN = UNIT_KIND_PASCAL + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_SECOND = UNIT_KIND_RADIAN + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_SIEMENS = UNIT_KIND_SECOND + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_SIEVERT = UNIT_KIND_SIEMENS + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_STERADIAN = UNIT_KIND_SIEVERT + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_TESLA = UNIT_KIND_STERADIAN + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_VOLT = UNIT_KIND_TESLA + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_WATT = UNIT_KIND_VOLT + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_WEBER = UNIT_KIND_WATT + 1;
  

    /**
     * One of the possible predefined SBML units.
     */
    public final static int UNIT_KIND_INVALID = UNIT_KIND_WEBER + 1;

    // RuleType_t 
  

    /**
     * One of the possible SBML {@link Rule} object types.
     */
    public final static int RULE_TYPE_RATE = 0;
  

    /**
     * One of the possible SBML {@link Rule} object types.
     */
    public final static int RULE_TYPE_SCALAR = RULE_TYPE_RATE + 1;
  

    /**
     * One of the possible SBML {@link Rule} object types.
     */
    public final static int RULE_TYPE_INVALID = RULE_TYPE_SCALAR + 1;

  

    /**
     * The default SBML Level in this release of libSBML.
     */
    public final static int SBML_DEFAULT_LEVEL = 3;
  

    /**
     * The default Version within the default SBML Level in this release of
     * libSBML.
     */
    public final static int SBML_DEFAULT_VERSION = 1;
  

    /**
     */
    public final static String SBML_XMLNS_L1 = "http://www.sbml.org/sbml/level1";
  

    /**
     */
    public final static String SBML_XMLNS_L2V1 = "http://www.sbml.org/sbml/level2";
  

    /**
     */
    public final static String SBML_XMLNS_L2V2 = "http://www.sbml.org/sbml/level2/version2";
  

    /**
     */
    public final static String SBML_XMLNS_L2V3 = "http://www.sbml.org/sbml/level2/version3";
  

    /**
     */
    public final static String SBML_XMLNS_L2V4 = "http://www.sbml.org/sbml/level2/version4";
  

    /**
     */
    public final static String SBML_XMLNS_L3V1 = "http://www.sbml.org/sbml/level3/version1/core";
    // ASTNodeType_t 
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_PLUS = '+';
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_MINUS = '-';
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_TIMES = '*';
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_DIVIDE = '/';
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_POWER = '^';
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_INTEGER = 256;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_REAL = AST_INTEGER + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_REAL_E = AST_REAL + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RATIONAL = AST_REAL_E + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_NAME = AST_RATIONAL + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_NAME_AVOGADRO = AST_NAME + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_NAME_TIME = AST_NAME_AVOGADRO + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_CONSTANT_E = AST_NAME_TIME + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_CONSTANT_FALSE = AST_CONSTANT_E + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_CONSTANT_PI = AST_CONSTANT_FALSE + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_CONSTANT_TRUE = AST_CONSTANT_PI + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_LAMBDA = AST_CONSTANT_TRUE + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION = AST_LAMBDA + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ABS = AST_FUNCTION + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCCOS = AST_FUNCTION_ABS + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCCOSH = AST_FUNCTION_ARCCOS + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCCOT = AST_FUNCTION_ARCCOSH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCCOTH = AST_FUNCTION_ARCCOT + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCCSC = AST_FUNCTION_ARCCOTH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCCSCH = AST_FUNCTION_ARCCSC + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCSEC = AST_FUNCTION_ARCCSCH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCSECH = AST_FUNCTION_ARCSEC + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCSIN = AST_FUNCTION_ARCSECH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCSINH = AST_FUNCTION_ARCSIN + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCTAN = AST_FUNCTION_ARCSINH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ARCTANH = AST_FUNCTION_ARCTAN + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_CEILING = AST_FUNCTION_ARCTANH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_COS = AST_FUNCTION_CEILING + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_COSH = AST_FUNCTION_COS + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_COT = AST_FUNCTION_COSH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_COTH = AST_FUNCTION_COT + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_CSC = AST_FUNCTION_COTH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_CSCH = AST_FUNCTION_CSC + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_DELAY = AST_FUNCTION_CSCH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_EXP = AST_FUNCTION_DELAY + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_FACTORIAL = AST_FUNCTION_EXP + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_FLOOR = AST_FUNCTION_FACTORIAL + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_LN = AST_FUNCTION_FLOOR + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_LOG = AST_FUNCTION_LN + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_PIECEWISE = AST_FUNCTION_LOG + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_POWER = AST_FUNCTION_PIECEWISE + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_ROOT = AST_FUNCTION_POWER + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_SEC = AST_FUNCTION_ROOT + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_SECH = AST_FUNCTION_SEC + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_SIN = AST_FUNCTION_SECH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_SINH = AST_FUNCTION_SIN + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_TAN = AST_FUNCTION_SINH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_FUNCTION_TANH = AST_FUNCTION_TAN + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_LOGICAL_AND = AST_FUNCTION_TANH + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_LOGICAL_NOT = AST_LOGICAL_AND + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_LOGICAL_OR = AST_LOGICAL_NOT + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_LOGICAL_XOR = AST_LOGICAL_OR + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RELATIONAL_EQ = AST_LOGICAL_XOR + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RELATIONAL_GEQ = AST_RELATIONAL_EQ + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RELATIONAL_GT = AST_RELATIONAL_GEQ + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RELATIONAL_LEQ = AST_RELATIONAL_GT + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RELATIONAL_LT = AST_RELATIONAL_LEQ + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_RELATIONAL_NEQ = AST_RELATIONAL_LT + 1;
  

    /**
     * One of the possible {@link ASTNode} types.  Each {@link ASTNode} has
     * a type whose value is one of the elements of this enumeration.
     */
    public final static int AST_UNKNOWN = AST_RELATIONAL_NEQ + 1;

    // XMLErrorCode_t 
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLUnknownError = 0;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLOutOfMemory = 1;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLFileUnreadable = 2;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLFileUnwritable = 3;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLFileOperationError = 4;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLNetworkAccessError = 5;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InternalXMLParserError = 101;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnrecognizedXMLParserCode = 102;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLTranscoderError = 103;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingXMLDecl = 1001;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingXMLEncoding = 1002;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLDecl = 1003;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLDOCTYPE = 1004;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidCharInXML = 1005;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadlyFormedXML = 1006;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnclosedXMLToken = 1007;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidXMLConstruct = 1008;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLTagMismatch = 1009;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateXMLAttribute = 1010;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UndefinedXMLEntity = 1011;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadProcessingInstruction = 1012;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLPrefix = 1013;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLPrefixValue = 1014;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingXMLRequiredAttribute = 1015;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLAttributeTypeMismatch = 1016;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLBadUTF8Content = 1017;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingXMLAttributeValue = 1018;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLAttributeValue = 1019;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLAttribute = 1020;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnrecognizedXMLElement = 1021;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLComment = 1022;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLDeclLocation = 1023;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLUnexpectedEOF = 1024;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLIDValue = 1025;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLIDRef = 1026;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UninterpretableXMLContent = 1027;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadXMLDocumentStructure = 1028;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidAfterXMLContent = 1029;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLExpectedQuotedString = 1030;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLEmptyValueNotPermitted = 1031;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLBadNumber = 1032;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLBadColon = 1033;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingXMLElements = 1034;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLContentEmpty = 1035;
  

    /**
     * A value in the enumeration of all the error and warning codes
     * returned by the XML layer in libSBML.  Please consult the
     * documentation for {@link XMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int XMLErrorCodesUpperBound = 9999;

    // XMLErrorCategory_t 
  

    /**
     * Category code for errors in the XML layer.
     *
     * This code has the following meaning: A problem involving the libSBML
     * software itself or the underlying XML parser.  This almost certainly
     * indicates a software defect (i.e., bug) in libSBML.  Please report
     * instances of this to the libSBML developers.
     */
    public final static int LIBSBML_CAT_INTERNAL = 0;
  

    /**
     * Category code for errors in the XML layer.
     *
     * This code has the following meaning: A problem reported by the
     * operating system, such as an inability to read or write a file.
     * This indicates something that is not a program error but is outside
     * of the control of libSBML.
     */
    public final static int LIBSBML_CAT_SYSTEM = LIBSBML_CAT_INTERNAL + 1;
  

    /**
     * Category code for errors in the XML layer.
     *
     * This code has the following meaning: A problem in the XML content
     * itself.  This usually arises from malformed XML or the use of
     * constructs not permitted in SBML.
     */
    public final static int LIBSBML_CAT_XML = LIBSBML_CAT_SYSTEM + 1;

    // XMLErrorSeverity_t 
  

    /**
     * Severity code for errors in the XML layer.
     *
     * This code has the following meaning: The error is actually
     * informational and not necessarily a serious problem.
     */
    public final static int LIBSBML_SEV_INFO = 0;
  

    /**
     * Severity code for errors in the XML layer.
     *
     * This code has the following meaning: The error object represents a
     * problem that is not serious enough to necessarily stop the problem,
     * but applications should take note of the problem and evaluate what
     * its implications may be.
     */
    public final static int LIBSBML_SEV_WARNING = LIBSBML_SEV_INFO + 1;
  

    /**
     * Severity code for errors in the XML layer.
     *
     * This code has the following meaning: The error object represents a
     * serious error.  The application may continue running but it is
     * unlikely to be able to continue processing the same XML file or data
     * stream. 
     */
    public final static int LIBSBML_SEV_ERROR = LIBSBML_SEV_WARNING + 1;
  

    /**
     * Severity code for errors in the XML layer.
     *
     * This code has the following meaning: A serious error occurred, such
     * as an out-of-memory condition, and the software should terminate
     * immediately.
     */
    public final static int LIBSBML_SEV_FATAL = LIBSBML_SEV_ERROR + 1;

    // SBMLErrorCode_t 
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnknownError = 10000;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NotUTF8 = 10101;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnrecognizedElement = 10102;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NotSchemaConformant = 10103;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3NotSchemaConformant = 10104;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidMathElement = 10201;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DisallowedMathMLSymbol = 10202;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DisallowedMathMLEncodingUse = 10203;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DisallowedDefinitionURLUse = 10204;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadCsymbolDefinitionURLValue = 10205;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DisallowedMathTypeAttributeUse = 10206;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DisallowedMathTypeAttributeValue = 10207;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int LambdaOnlyAllowedInFunctionDef = 10208;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BooleanOpsNeedBooleanArgs = 10209;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NumericOpsNeedNumericArgs = 10210;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ArgsToEqNeedSameType = 10211;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int PiecewiseNeedsConsistentTypes = 10212;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int PieceNeedsBoolean = 10213;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ApplyCiMustBeUserFunction = 10214;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ApplyCiMustBeModelComponent = 10215;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int KineticLawParametersAreLocalOnly = 10216;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MathResultMustBeNumeric = 10217;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OpsNeedCorrectNumberOfArgs = 10218;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidNoArgsPassedToFunctionDef = 10219;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DisallowedMathUnitsUse = 10220;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidUnitsValue = 10221;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateComponentId = 10301;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateUnitDefinitionId = 10302;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateLocalParameterId = 10303;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MultipleAssignmentOrRateRules = 10304;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MultipleEventAssignmentsForId = 10305;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventAndAssignmentRuleForId = 10306;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateMetaId = 10307;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSBOTermSyntax = 10308;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidMetaidSyntax = 10309;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidIdSyntax = 10310;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidUnitIdSyntax = 10311;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidNameSyntax = 10312;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingAnnotationNamespace = 10401;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateAnnotationNamespaces = 10402;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SBMLNamespaceInAnnotation = 10403;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MultipleAnnotations = 10404;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InconsistentArgUnits = 10501;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InconsistentKineticLawUnitsL3 = 10503;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AssignRuleCompartmentMismatch = 10511;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AssignRuleSpeciesMismatch = 10512;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AssignRuleParameterMismatch = 10513;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AssignRuleStoichiometryMismatch = 10514;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitAssignCompartmenMismatch = 10521;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitAssignSpeciesMismatch = 10522;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitAssignParameterMismatch = 10523;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitAssignStoichiometryMismatch = 10524;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RateRuleCompartmentMismatch = 10531;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RateRuleSpeciesMismatch = 10532;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RateRuleParameterMismatch = 10533;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RateRuleStoichiometryMismatch = 10534;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int KineticLawNotSubstancePerTime = 10541;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpeciesInvalidExtentUnits = 10542;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DelayUnitsNotTime = 10551;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventAssignCompartmentMismatch = 10561;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventAssignSpeciesMismatch = 10562;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventAssignParameterMismatch = 10563;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventAssignStoichiometryMismatch = 10564;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int PriorityUnitsNotDimensionless = 10565;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OverdeterminedSystem = 10601;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidModelSBOTerm = 10701;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidFunctionDefSBOTerm = 10702;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidParameterSBOTerm = 10703;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidInitAssignSBOTerm = 10704;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidRuleSBOTerm = 10705;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidConstraintSBOTerm = 10706;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidReactionSBOTerm = 10707;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesReferenceSBOTerm = 10708;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidKineticLawSBOTerm = 10709;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidEventSBOTerm = 10710;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidEventAssignmentSBOTerm = 10711;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidCompartmentSBOTerm = 10712;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesSBOTerm = 10713;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidCompartmentTypeSBOTerm = 10714;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesTypeSBOTerm = 10715;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidTriggerSBOTerm = 10716;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidDelaySBOTerm = 10717;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NotesNotInXHTMLNamespace = 10801;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NotesContainsXMLDecl = 10802;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NotesContainsDOCTYPE = 10803;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidNotesContent = 10804;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyOneNotesElementAllowed = 10805;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidNamespaceOnSBML = 20101;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingOrInconsistentLevel = 20102;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingOrInconsistentVersion = 20103;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int PackageNSMustMatch = 20104;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int LevelPositiveInteger = 20105;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int VersionPositiveInteger = 20106;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnSBML = 20108;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingModel = 20201;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IncorrectOrderInModel = 20202;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EmptyListElement = 20203;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NeedCompartmentIfHaveSpecies = 20204;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneOfEachListOf = 20205;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyFuncDefsInListOfFuncDefs = 20206;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyUnitDefsInListOfUnitDefs = 20207;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyCompartmentsInListOfCompartments = 20208;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlySpeciesInListOfSpecies = 20209;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyParametersInListOfParameters = 20210;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyInitAssignsInListOfInitAssigns = 20211;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyRulesInListOfRules = 20212;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyConstraintsInListOfConstraints = 20213;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyReactionsInListOfReactions = 20214;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyEventsInListOfEvents = 20215;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3ConversionFactorOnModel = 20216;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3TimeUnitsOnModel = 20217;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3VolumeUnitsOnModel = 20218;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3AreaUnitsOnModel = 20219;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3LengthUnitsOnModel = 20220;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3ExtentUnitsOnModel = 20221;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnModel = 20222;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfFuncs = 20223;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfUnitDefs = 20224;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfComps = 20225;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfSpecies = 20226;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfParams = 20227;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfInitAssign = 20228;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfRules = 20229;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfConstraints = 20230;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfReactions = 20231;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfEvents = 20232;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FunctionDefMathNotLambda = 20301;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidApplyCiInLambda = 20302;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RecursiveFunctionDefinition = 20303;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidCiInLambda = 20304;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidFunctionDefReturnType = 20305;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathElementPerFunc = 20306;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnFunc = 20307;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidUnitDefId = 20401;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSubstanceRedefinition = 20402;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidLengthRedefinition = 20403;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidAreaRedefinition = 20404;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidTimeRedefinition = 20405;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidVolumeRedefinition = 20406;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int VolumeLitreDefExponentNotOne = 20407;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int VolumeMetreDefExponentNot3 = 20408;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EmptyListOfUnits = 20409;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidUnitKind = 20410;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OffsetNoLongerValid = 20411;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CelsiusNoLongerValid = 20412;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EmptyUnitListElement = 20413;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneListOfUnitsPerUnitDef = 20414;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyUnitsInListOfUnits = 20415;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnUnitDefinition = 20419;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfUnits = 20420;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnUnit = 20421;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ZeroDimensionalCompartmentSize = 20501;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ZeroDimensionalCompartmentUnits = 20502;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ZeroDimensionalCompartmentConst = 20503;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UndefinedOutsideCompartment = 20504;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RecursiveCompartmentContainment = 20505;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ZeroDCompartmentContainment = 20506;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int Invalid1DCompartmentUnits = 20507;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int Invalid2DCompartmentUnits = 20508;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int Invalid3DCompartmentUnits = 20509;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidCompartmentTypeRef = 20510;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneDimensionalCompartmentUnits = 20511;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int TwoDimensionalCompartmentUnits = 20512;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ThreeDimensionalCompartmentUnits = 20513;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnCompartment = 20517;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoUnitsOnCompartment = 20518;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesCompartmentRef = 20601;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int HasOnlySubsNoSpatialUnits = 20602;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpatialUnitsInZeroD = 20603;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoConcentrationInZeroD = 20604;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpatialUnitsInOneD = 20605;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpatialUnitsInTwoD = 20606;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpatialUnitsInThreeD = 20607;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesSusbstanceUnits = 20608;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BothAmountAndConcentrationSet = 20609;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NonBoundarySpeciesAssignedAndUsed = 20610;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NonConstantSpeciesUsed = 20611;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesTypeRef = 20612;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MultSpeciesSameTypeInCompartment = 20613;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingSpeciesCompartment = 20614;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpatialSizeUnitsRemoved = 20615;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SubstanceUnitsOnSpecies = 20616;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConversionFactorOnSpecies = 20617;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnSpecies = 20623;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidParameterUnits = 20701;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ParameterUnits = 20702;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConversionFactorMustConstant = 20705;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnParameter = 20706;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidInitAssignSymbol = 20801;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MultipleInitAssignments = 20802;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitAssignmentAndRuleForSameId = 20803;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathElementPerInitialAssign = 20804;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnInitialAssign = 20805;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidAssignRuleVariable = 20901;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidRateRuleVariable = 20902;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AssignmentToConstantEntity = 20903;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RateRuleForConstantEntity = 20904;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RepeatedRule10304 = 20905;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CircularRuleDependency = 20906;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathElementPerRule = 20907;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnAssignRule = 20908;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnRateRule = 20909;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnAlgRule = 20910;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstraintMathNotBoolean = 21001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IncorrectOrderInConstraint = 21002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstraintNotInXHTMLNamespace = 21003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstraintContainsXMLDecl = 21004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstraintContainsDOCTYPE = 21005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidConstraintContent = 21006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathElementPerConstraint = 21007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMessageElementPerConstraint = 21008;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnConstraint = 21009;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoReactantsOrProducts = 21101;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IncorrectOrderInReaction = 21102;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EmptyListInReaction = 21103;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidReactantsProductsList = 21104;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidModifiersList = 21105;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneSubElementPerReaction = 21106;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CompartmentOnReaction = 21107;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnReaction = 21110;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSpeciesReference = 21111;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RepeatedRule20611 = 21112;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BothStoichiometryAndMath = 21113;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnSpeciesReference = 21116;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnModifier = 21117;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UndeclaredSpeciesRef = 21121;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IncorrectOrderInKineticLaw = 21122;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EmptyListInKineticLaw = 21123;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NonConstantLocalParameter = 21124;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SubsUnitsNoLongerValid = 21125;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int TimeUnitsNoLongerValid = 21126;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneListOfPerKineticLaw = 21127;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyLocalParamsInListOfLocalParams = 21128;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfLocalParam = 21129;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathPerKineticLaw = 21130;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UndeclaredSpeciesInStoichMath = 21131;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnKineticLaw = 21132;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfSpeciesRef = 21150;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfMods = 21151;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnLocalParameter = 21172;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingTriggerInEvent = 21201;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int TriggerMathNotBoolean = 21202;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MissingEventAssignment = 21203;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int TimeUnitsEvent = 21204;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IncorrectOrderInEvent = 21205;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ValuesFromTriggerTimeNeedDelay = 21206;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DelayNeedsValuesFromTriggerTime = 21207;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathPerTrigger = 21209;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathPerDelay = 21210;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidEventAssignmentVariable = 21211;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventAssignmentForConstantEntity = 21212;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathPerEventAssignment = 21213;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnEventAssignment = 21214;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyOneDelayPerEvent = 21221;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneListOfEventAssignmentsPerEvent = 21222;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyEventAssignInListOfEventAssign = 21223;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnListOfEventAssign = 21224;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnEvent = 21225;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnTrigger = 21226;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnDelay = 21227;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int PersistentNotBoolean = 21228;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitialValueNotBoolean = 21229;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OnlyOnePriorityPerEvent = 21230;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OneMathPerPriority = 21231;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AllowedAttributesOnPriority = 21232;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int GeneralWarningNotSpecified = 29999;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CompartmentShouldHaveSize = 80501;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ParameterShouldHaveUnits = 80701;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int LocalParameterShadowsId = 81121;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int LibSBMLAdditionalCodesLowerBound = 90000;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CannotConvertToL1V1 = 90001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoEventsInL1 = 91001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoFunctionDefinitionsInL1 = 91002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoConstraintsInL1 = 91003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoInitialAssignmentsInL1 = 91004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesTypesInL1 = 91005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoCompartmentTypeInL1 = 91006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoNon3DComparmentsInL1 = 91007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoFancyStoichiometryMathInL1 = 91008;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoNonIntegerStoichiometryInL1 = 91009;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoUnitMultipliersOrOffsetsInL1 = 91010;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpeciesCompartmentRequiredInL1 = 91011;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesSpatialSizeUnitsInL1 = 91012;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSBOTermsInL1 = 91013;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StrictUnitsRequiredInL1 = 91014;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConversionFactorNotInL1 = 91015;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CompartmentNotOnL1Reaction = 91016;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ExtentUnitsNotSubstance = 91017;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoConstraintsInL2v1 = 92001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoInitialAssignmentsInL2v1 = 92002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesTypeInL2v1 = 92003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoCompartmentTypeInL2v1 = 92004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSBOTermsInL2v1 = 92005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoIdOnSpeciesReferenceInL2v1 = 92006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoDelayedEventAssignmentInL2v1 = 92007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StrictUnitsRequiredInL2v1 = 92008;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IntegerSpatialDimensions = 92009;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StoichiometryMathNotYetSupported = 92010;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int PrioirtyLostFromL3 = 92011;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NonPersistentNotSupported = 92012;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitialValueFalseEventNotSupported = 92013;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SBOTermNotUniversalInL2v2 = 93001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoUnitOffsetInL2v2 = 93002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawTimeUnitsInL2v2 = 93003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawSubstanceUnitsInL2v2 = 93004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoDelayedEventAssignmentInL2v2 = 93005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ModelSBOBranchChangedBeyondL2v2 = 93006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StrictUnitsRequiredInL2v2 = 93007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StrictSBORequiredInL2v2 = 93008;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateAnnotationInvalidInL2v2 = 93009;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoUnitOffsetInL2v3 = 94001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawTimeUnitsInL2v3 = 94002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawSubstanceUnitsInL2v3 = 94003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesSpatialSizeUnitsInL2v3 = 94004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoEventTimeUnitsInL2v3 = 94005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoDelayedEventAssignmentInL2v3 = 94006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ModelSBOBranchChangedBeyondL2v3 = 94007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StrictUnitsRequiredInL2v3 = 94008;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StrictSBORequiredInL2v3 = 94009;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateAnnotationInvalidInL2v3 = 94010;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoUnitOffsetInL2v4 = 95001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawTimeUnitsInL2v4 = 95002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawSubstanceUnitsInL2v4 = 95003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesSpatialSizeUnitsInL2v4 = 95004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoEventTimeUnitsInL2v4 = 95005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ModelSBOBranchChangedInL2v4 = 95006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateAnnotationInvalidInL2v4 = 95007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesTypeInL3v1 = 96001;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoCompartmentTypeInL3v1 = 96002;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoUnitOffsetInL3v1 = 96003;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawTimeUnitsInL3v1 = 96004;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoKineticLawSubstanceUnitsInL3v1 = 96005;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoSpeciesSpatialSizeUnitsInL3v1 = 96006;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoEventTimeUnitsInL3v1 = 96007;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ModelSBOBranchChangedInL3v1 = 96008;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int DuplicateAnnotationInvalidInL3v1 = 96009;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoCompartmentOutsideInL3v1 = 96010;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoStoichiometryMathInL3v1 = 96011;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidSBMLLevelVersion = 99101;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int AnnotationNotesNotAllowedLevel1 = 99104;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidRuleOrdering = 99106;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int RequiredPackagePresent = 99107;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SubsUnitsAllowedInKL = 99127;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int TimeUnitsAllowedInKL = 99128;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FormulaInLevel1KL = 99129;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int TimeUnitsRemoved = 99206;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadMathML = 99219;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FailedMathMLReadOfDouble = 99220;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FailedMathMLReadOfInteger = 99221;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FailedMathMLReadOfExponential = 99222;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FailedMathMLReadOfRational = 99223;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int BadMathMLNodeType = 99224;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoTimeSymbolInFunctionDef = 99301;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NoBodyInFunctionDef = 99302;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InconsistentArgUnitsWarnings = 99502;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InconsistentPowerUnitsWarnings = 99503;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InconsistentExponUnitsWarnings = 99504;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UndeclaredUnits = 99505;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnrecognisedSBOTerm = 99701;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ObseleteSBOTerm = 99702;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IncorrectCompartmentSpatialDimensions = 99901;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CompartmentTypeNotValidAttribute = 99902;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstantNotValidAttribute = 99903;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MetaIdNotValidAttribute = 99904;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SBOTermNotValidAttributeBeforeL2V3 = 99905;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidL1CompartmentUnits = 99906;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L1V1CompartmentVolumeReqd = 99907;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int CompartmentTypeNotValidComponent = 99908;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstraintNotValidComponent = 99909;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int EventNotValidComponent = 99910;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SBOTermNotValidAttributeBeforeL2V2 = 99911;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int FuncDefNotValidComponent = 99912;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InitialAssignNotValidComponent = 99913;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int VariableNotValidAttribute = 99914;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int UnitsNotValidAttribute = 99915;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int ConstantSpeciesNotValidAttribute = 99916;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpatialSizeUnitsNotValidAttribute = 99917;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpeciesTypeNotValidAttribute = 99918;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int HasOnlySubsUnitsNotValidAttribute = 99919;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int IdNotValidAttribute = 99920;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int NameNotValidAttribute = 99921;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SpeciesTypeNotValidComponent = 99922;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int StoichiometryMathNotValidComponent = 99923;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int MultiplierNotValidAttribute = 99924;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int OffsetNotValidAttribute = 99925;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int InvalidTargetLevelVersion = 99997;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int L3NotSupported = 99998;
  

    /**
     * A value in the enumeration of all the SBML error and warning codes
     * for objects of class {@link SBMLError}.  Please consult the
     * documentation for {@link SBMLError} for an explanation of the
     * meaning of this particular error code.
     */
    public final static int SBMLCodesUpperBound = 99999;

    // SBMLErrorCategory_t 
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning: General SBML error not falling
     * into another category below.
     */
    public final static int LIBSBML_CAT_SBML = (LIBSBML_CAT_XML+1);
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning: Category of errors that can
     * only occur during attempted translation from one Level/Version of
     * SBML to another.  This particular category applies to errors
     * encountered while trying to convert a model from SBML Level&nbsp;2
     * to SBML Level&nbsp;1.
     */
    public final static int LIBSBML_CAT_SBML_L1_COMPAT = LIBSBML_CAT_SBML + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can only occur during attempted
     * translation from one Level/Version of SBML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a model to SBML Level&nbsp;2 Version&nbsp;1.
     */
    public final static int LIBSBML_CAT_SBML_L2V1_COMPAT = LIBSBML_CAT_SBML_L1_COMPAT + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can only occur during attempted
     * translation from one Level/Version of SBML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a model to SBML Level&nbsp;2 Version&nbsp;2.
     */
    public final static int LIBSBML_CAT_SBML_L2V2_COMPAT = LIBSBML_CAT_SBML_L2V1_COMPAT + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can occur while validating general SBML
     * constructs.  With respect to the SBML specification, these concern
     * failures in applying the validation rules numbered 2xxxx in the
     * Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications.
     */
    public final static int LIBSBML_CAT_GENERAL_CONSISTENCY = LIBSBML_CAT_SBML_L2V2_COMPAT + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can occur while validating symbol
     * identifiers in a model.  With respect to the SBML specification,
     * these concern failures in applying the validation rules numbered
     * 103xx in the Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications.
     */
    public final static int LIBSBML_CAT_IDENTIFIER_CONSISTENCY = LIBSBML_CAT_GENERAL_CONSISTENCY + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can occur while validating the units of
     * measurement on quantities in a model.  With respect to the SBML
     * specification, these concern failures in applying the validation
     * rules numbered 105xx in the Level&nbsp;2 Versions&nbsp;2 and&nbsp;3
     * specifications.
     */
    public final static int LIBSBML_CAT_UNITS_CONSISTENCY = LIBSBML_CAT_IDENTIFIER_CONSISTENCY + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can occur while validating MathML formulas
     * in a model.  With respect to the SBML specification, these concern
     * failures in applying the validation rules numbered 102xx in the
     * Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications.
     */
    public final static int LIBSBML_CAT_MATHML_CONSISTENCY = LIBSBML_CAT_UNITS_CONSISTENCY + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can occur while validating SBO identifiers
     * in a model.  With respect to the SBML specification, these concern
     * failures in applying the validation rules numbered 107xx in the
     * Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications.
     */
    public final static int LIBSBML_CAT_SBO_CONSISTENCY = LIBSBML_CAT_MATHML_CONSISTENCY + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Error in the system of equations in the model: the system is
     * overdetermined, therefore violating a tenet of proper SBML.  With
     * respect to the SBML specification, this is validation rule #10601 in
     * the SBML Level&nbsp;2 Versions&nbsp;2 and&nbsp;3 specifications.
     */
    public final static int LIBSBML_CAT_OVERDETERMINED_MODEL = LIBSBML_CAT_SBO_CONSISTENCY + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can only occur during attempted
     * translation from one Level/Version of SBML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a model to SBML Level&nbsp;2 Version&nbsp;3.
     */
    public final static int LIBSBML_CAT_SBML_L2V3_COMPAT = LIBSBML_CAT_OVERDETERMINED_MODEL + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of warnings about recommended good practices involving
     * SBML and computational modeling.  (These are tests performed by
     * libSBML and do not have equivalent SBML validation rules.)
     */
    public final static int LIBSBML_CAT_MODELING_PRACTICE = LIBSBML_CAT_SBML_L2V3_COMPAT + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can occur while validating libSBML's 
     * internal representation of SBML constructs. (These are tests 
     * performed by libSBML and do not have equivalent SBML validation 
     * rules.)
     */
    public final static int LIBSBML_CAT_INTERNAL_CONSISTENCY = LIBSBML_CAT_MODELING_PRACTICE + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:      Category of errors that can only occur during attempted
     * translation from one Level/Version of SBML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a model to SBML Level&nbsp;2 Version&nbsp;4.
     */
    public final static int LIBSBML_CAT_SBML_L2V4_COMPAT = LIBSBML_CAT_INTERNAL_CONSISTENCY + 1;
  

    /**
     * Category code for {@link SBMLError} diagnostics.
     *
     * This code has the following meaning:    Category of errors that can only occur during attempted
     * translation from one Level/Version of SBML to another.  This
     * particular category applies to errors encountered while trying to
     * convert a model to SBML Level&nbsp;3 Version&nbsp;1.  
     */
    public final static int LIBSBML_CAT_SBML_L3V1_COMPAT = LIBSBML_CAT_SBML_L2V4_COMPAT + 1;

    // SBMLErrorSeverity_t 
  
    // QualifierType_t 
  

    /**
     * One of the possible MIRIAM annotation types used by {@link CVTerm}.
     */
    public final static int MODEL_QUALIFIER = 0;
  

    /**
     * One of the possible MIRIAM annotation types used by {@link CVTerm}.
     */
    public final static int BIOLOGICAL_QUALIFIER = MODEL_QUALIFIER + 1;
  

    /**
     * One of the possible MIRIAM annotation types used by {@link CVTerm}.
     */
    public final static int UNKNOWN_QUALIFIER = BIOLOGICAL_QUALIFIER + 1;

    // ModelQualifierType_t 
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.
     */
    public final static int BQM_IS = 0;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.
     */
    public final static int BQM_IS_DESCRIBED_BY = BQM_IS + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.
     */
    public final static int BQM_IS_DERIVED_FROM = BQM_IS_DESCRIBED_BY + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.
     */
    public final static int BQM_UNKNOWN = BQM_IS_DERIVED_FROM + 1;

    // BiolQualifierType_t 
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS = 0;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_HAS_PART = BQB_IS + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS_PART_OF = BQB_HAS_PART + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS_VERSION_OF = BQB_IS_PART_OF + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_HAS_VERSION = BQB_IS_VERSION_OF + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS_HOMOLOG_TO = BQB_HAS_VERSION + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS_DESCRIBED_BY = BQB_IS_HOMOLOG_TO + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS_ENCODED_BY = BQB_IS_DESCRIBED_BY + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_ENCODES = BQB_IS_ENCODED_BY + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_OCCURS_IN = BQB_ENCODES + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_HAS_PROPERTY = BQB_OCCURS_IN + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_IS_PROPERTY_OF = BQB_HAS_PROPERTY + 1;
  

    /**
     * One of the possible MIRIAM annotation model qualifier types used by
     * {@link CVTerm}.  Please consult the explanation of the qualifiers
     * defined by BioModels.net at <a target="_blank"
     * href="http://biomodels.net/qualifiers">http://biomodels.net/qualifiers</a>.
     */
    public final static int BQB_UNKNOWN = BQB_IS_PROPERTY_OF + 1;

}
