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
 * Methods for checking syntax of SBML identifiers and other strings.
 * 
 * @htmlinclude not-sbml-warning.html
 * 
 * This utility class provides static methods for checking the syntax of
 * identifiers and other text used in an SBML model.  The methods allow
 * callers to verify that strings such as SBML identifiers and XHTML notes
 * text conform to the SBML specifications.
 */
public class SyntaxChecker : IDisposable {
	private HandleRef swigCPtr;
	protected bool swigCMemOwn;
	
	internal SyntaxChecker(IntPtr cPtr, bool cMemoryOwn)
	{
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(SyntaxChecker obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (SyntaxChecker obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~SyntaxChecker() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_SyntaxChecker(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  
  /**
   * Returns true @c true or @c false depending on whether the argument
   * string conforms to the syntax of SBML identifiers.
   *
   * In SBML, identifiers that are the values of 'id' attributes on objects
   * must conform to a data type called <c>SId</c> in the SBML
   * specifications.  LibSBML does not provide an explicit <c>SId</c>
   * data type; it uses ordinary character strings, which is easier for
   * applications to support.  LibSBML does, however, test for identifier
   * validity at various times, such as when reading in models from files
   * and data streams.
   *
   * This method provides programs with the ability to test explicitly that
   * the identifier strings they create conform to the SBML identifier
   * syntax.
   *
   * @param sid string to be checked for conformance to SBML identifier
   * syntax.
   *
   * @return @c true if the string conforms to type SBML data type
   * <c>SId</c>, @c false otherwise.
   *
   * @note @htmlinclude id-syntax.html
   *
   * @see isValidUnitSId(string sid)
   * @see isValidXMLID(string sid)
   */  
 public static bool isValidSBMLSId(string sid) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_isValidSBMLSId(sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  
  /**
   * Returns @c true or @c false depending on whether the argument string
   * conforms to the XML data type <c>ID</c>.
   *
   * In SBML, identifiers that are the values of 'metaid' attributes on
   * objects must conform to the <a target='_blank'
   * href='http://www.w3.org/TR/REC-xml/#id'>XML ID</a> data type.  LibSBML
   * does not provide an explicit XML <c>ID</c> data type; it uses
   * ordinary character strings, which is easier for applications to
   * support.  LibSBML does, however, test for identifier validity at
   * various times, such as when reading in models from files and data
   * streams.
   *
   * This method provides programs with the ability to test explicitly that
   * the identifier strings they create conform to the SBML identifier
   * syntax.
   *
   * @param id string to be checked for conformance to the syntax of
   * <a target='_blank' href='http://www.w3.org/TR/REC-xml/#id'>XML ID</a>.
   *
   * @return @c true if the string is a syntactically-valid value for the
   * XML type <a target='_blank'
   * href='http://www.w3.org/TR/REC-xml/#id'>ID</a>, @c false otherwise.
   *
   * @note @htmlinclude xmlid-syntax.html
   * 
   * @see isValidSBMLSId(string sid)
   * @see isValidUnitSId(string sid)
   */  
 public static bool isValidXMLID(string id) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_isValidXMLID(id);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  
  /**
   * Returns @c true or @c false depending on whether the argument string
   * conforms to the syntax of SBML unit identifiers.
   *
   * In SBML, the identifiers of units (of both the predefined units and
   * user-defined units) must conform to a data type called
   * <c>UnitSId</c> in the SBML specifications.  LibSBML does not
   * provide an explicit <c>UnitSId</c> data type; it uses ordinary
   * character strings, which is easier for applications to support.
   * LibSBML does, however, test for identifier validity at various times,
   * such as when reading in models from files and data streams.
   *
   * This method provides programs with the ability to test explicitly that
   * the identifier strings they create conform to the SBML identifier
   * syntax.
   *
   * @param units string to be checked for conformance to SBML unit
   * identifier syntax.
   *
   * @return @c true if the string conforms to type SBML data type
   * <c>UnitSId</c>, @c false otherwise.
   *
   * @note @htmlinclude unitid-syntax.html
   *
   * @see isValidSBMLSId(string sid)
   * @see isValidXMLID(string sid)
   */
 public static bool isValidUnitSId(string units) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_isValidUnitSId(units);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  
  /**
   * Returns @c true or @c false depending on whether the given XMLNode
   * object contains valid XHTML content.
   *
   * In SBML, the content of the 'notes' subelement available on SBase, as
   * well as the 'message' subelement available on Constraint, must conform
   * to <a target='_blank'
   * href='http://www.w3.org/TR/xhtml1/'>XHTML&nbsp;1.0</a> (which is
   * simply an XML-ized version of HTML).  However, the content cannot be
   * @em entirely free-form; it must satisfy certain requirements defined in
   * the <a target='_blank'
   * href='http://sbml.org/Documents/Specifications'>SBML
   * specifications</a> for specific SBML Levels.  This method implements a
   * verification process that lets callers check whether the content of a
   * given XMLNode object conforms to the SBML requirements for 'notes' and
   * 'message' structure.
   *
   * An aspect of XHTML validity is that the content is declared to be in
   * the XML namespace for XHTML&nbsp;1.0.  There is more than one way in
   * which this can be done in XML.  In particular, a model might not
   * contain the declaration within the 'notes' or 'message' subelement
   * itself, but might instead place the declaration on an enclosing
   * element and use an XML namespace prefix within the 'notes' element to
   * refer to it.  In other words, the following is valid:
   * <code>
<sbml xmlns='http://www.sbml.org/sbml/level2/version3' level='2' version='3'
      xmlns:xhtml='http://www.w3.org/1999/xhtml'>
  <model>
    <notes>
      <xhtml:body>
        <xhtml:center><xhtml:h2>A Simple Mitotic Oscillator</xhtml:h2></xhtml:center>
        <xhtml:p>A minimal cascade model for the mitotic oscillator.</xhtml:p>
      </xhtml:body>
    </notes>
  ... rest of model ...
</sbml>
</code>
   * Contrast the above with the following, self-contained version, which
   * places the XML namespace declaration within the <c>&lt;notes&gt;</c>
   * element itself:
   * <code>
<sbml xmlns='http://www.sbml.org/sbml/level2/version3' level='2' version='3'>
  <model>
    <notes>
      <html xmlns='http://www.w3.org/1999/xhtml'>
        <head>
          <title/>
        </head>
        <body>
          <center><h2>A Simple Mitotic Oscillator</h2></center>
          <p>A minimal cascade model for the mitotic oscillator.</p>
        </body>
      </html>
    </notes>
  ... rest of model ...
</sbml>
</code>
   *
   * Both of the above are valid XML.  The purpose of the @p sbmlns
   * argument to this method is to allow callers to check the validity of
   * 'notes' and 'message' subelements whose XML namespace declarations
   * have been put elsewhere in the manner illustrated above.  Callers can
   * can pass in the SBMLNamespaces object of a higher-level model
   * component if the XMLNode object does not itself have the XML namespace
   * declaration for XHTML&nbsp;1.0.
   * 
   * @param xhtml the XMLNode to be checked for conformance.
   * @param sbmlns the SBMLNamespaces associated with the object.
   *
   * @return @c true if the XMLNode content conforms, @c false otherwise.
   *
   * @if notcpp @docnote @htmlinclude warn-default-args-in-docs.html @endif
   */
 public static bool hasExpectedXHTMLSyntax(XMLNode xhtml, SBMLNamespaces sbmlns) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_hasExpectedXHTMLSyntax__SWIG_0(XMLNode.getCPtr(xhtml), SBMLNamespaces.getCPtr(sbmlns));
    return ret;
  }

  
  /**
   * Returns @c true or @c false depending on whether the given XMLNode
   * object contains valid XHTML content.
   *
   * In SBML, the content of the 'notes' subelement available on SBase, as
   * well as the 'message' subelement available on Constraint, must conform
   * to <a target='_blank'
   * href='http://www.w3.org/TR/xhtml1/'>XHTML&nbsp;1.0</a> (which is
   * simply an XML-ized version of HTML).  However, the content cannot be
   * @em entirely free-form; it must satisfy certain requirements defined in
   * the <a target='_blank'
   * href='http://sbml.org/Documents/Specifications'>SBML
   * specifications</a> for specific SBML Levels.  This method implements a
   * verification process that lets callers check whether the content of a
   * given XMLNode object conforms to the SBML requirements for 'notes' and
   * 'message' structure.
   *
   * An aspect of XHTML validity is that the content is declared to be in
   * the XML namespace for XHTML&nbsp;1.0.  There is more than one way in
   * which this can be done in XML.  In particular, a model might not
   * contain the declaration within the 'notes' or 'message' subelement
   * itself, but might instead place the declaration on an enclosing
   * element and use an XML namespace prefix within the 'notes' element to
   * refer to it.  In other words, the following is valid:
   * <code>
<sbml xmlns='http://www.sbml.org/sbml/level2/version3' level='2' version='3'
      xmlns:xhtml='http://www.w3.org/1999/xhtml'>
  <model>
    <notes>
      <xhtml:body>
        <xhtml:center><xhtml:h2>A Simple Mitotic Oscillator</xhtml:h2></xhtml:center>
        <xhtml:p>A minimal cascade model for the mitotic oscillator.</xhtml:p>
      </xhtml:body>
    </notes>
  ... rest of model ...
</sbml>
</code>
   * Contrast the above with the following, self-contained version, which
   * places the XML namespace declaration within the <c>&lt;notes&gt;</c>
   * element itself:
   * <code>
<sbml xmlns='http://www.sbml.org/sbml/level2/version3' level='2' version='3'>
  <model>
    <notes>
      <html xmlns='http://www.w3.org/1999/xhtml'>
        <head>
          <title/>
        </head>
        <body>
          <center><h2>A Simple Mitotic Oscillator</h2></center>
          <p>A minimal cascade model for the mitotic oscillator.</p>
        </body>
      </html>
    </notes>
  ... rest of model ...
</sbml>
</code>
   *
   * Both of the above are valid XML.  The purpose of the @p sbmlns
   * argument to this method is to allow callers to check the validity of
   * 'notes' and 'message' subelements whose XML namespace declarations
   * have been put elsewhere in the manner illustrated above.  Callers can
   * can pass in the SBMLNamespaces object of a higher-level model
   * component if the XMLNode object does not itself have the XML namespace
   * declaration for XHTML&nbsp;1.0.
   * 
   * @param xhtml the XMLNode to be checked for conformance.
   * @param sbmlns the SBMLNamespaces associated with the object.
   *
   * @return @c true if the XMLNode content conforms, @c false otherwise.
   *
   * @if notcpp @docnote @htmlinclude warn-default-args-in-docs.html @endif
   */
 public static bool hasExpectedXHTMLSyntax(XMLNode xhtml) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_hasExpectedXHTMLSyntax__SWIG_1(XMLNode.getCPtr(xhtml));
    return ret;
  }

  
  /**
   * Returns true @c true or @c false depending on whether the argument
   * string conforms to the syntax of SBML identifiers or is empty.
   */  
 /* libsbml-internal */ public static bool isValidInternalSId(string sid) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_isValidInternalSId(sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  
  /**
   * Returns true @c true or @c false depending on whether the argument
   * string conforms to the syntax of SBML identifiers or is empty.
   */  
 /* libsbml-internal */ public static bool isValidInternalUnitSId(string sid) {
    bool ret = libsbmlPINVOKE.SyntaxChecker_isValidInternalUnitSId(sid);
    if (libsbmlPINVOKE.SWIGPendingException.Pending) throw libsbmlPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public SyntaxChecker() : this(libsbmlPINVOKE.new_SyntaxChecker(), true) {
  }

}

}
