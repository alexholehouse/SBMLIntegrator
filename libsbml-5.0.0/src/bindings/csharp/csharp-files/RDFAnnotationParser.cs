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
 * Read/write/manipulate RDF annotations stored in SBML
 * annotation elements.
 *
 * @htmlinclude not-sbml-warning.html
 *
 * RDFAnnotationParser is a libSBML construct used as part of the libSBML
 * support for annotations conforming to the guidelines specified by MIRIAM
 * ('Minimum Information Requested in the Annotation of biochemical
 * Models', <i>Nature Biotechnology</i>, vol. 23, no. 12, Dec. 2005).
 * Section 6 of the SBML Level&nbsp;2 and Level&nbsp;3 specification
 * documents defines a recommended way of encoding MIRIAM information using
 * a subset of RDF in SBML.  The general scheme is as follows.  A set of
 * RDF-based annotations attached to a given SBML
 * <c>&lt;annotation&gt;</c> element are read by RDFAnnotationParser
 * and converted into a list of CVTerm objects.  There
 * are different versions of the main method, @if clike RDFAnnotationParser::parseRDFAnnotation(XMLNode annotation, %List CVTerms) @else RDFAnnotationParser::parseRDFAnnotation(XMLNode annotation, CVTermList CVTerms) @endif
 * and RDFAnnotationParser::parseRDFAnnotation(XMLNode annotation), 
 * used depending on whether the annotation in question concerns the MIRIAM
 * model history or other MIRIAM resource annotations.  A special object
 * class, ModelHistory, is used to make it easier to manipulate model
 * history annotations.
 *
 * All of the methods on RDFAnnotationParser are static; the class exists
 * only to encapsulate the annotation and CVTerm parsing and manipulation
 * functionality.
 */
public class RDFAnnotationParser : IDisposable {
	private HandleRef swigCPtr;
	protected bool swigCMemOwn;
	
	internal RDFAnnotationParser(IntPtr cPtr, bool cMemoryOwn)
	{
		swigCMemOwn = cMemoryOwn;
		swigCPtr    = new HandleRef(this, cPtr);
	}
	
	internal static HandleRef getCPtr(RDFAnnotationParser obj)
	{
		return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
	}
	
	internal static HandleRef getCPtrAndDisown (RDFAnnotationParser obj)
	{
		HandleRef ptr = new HandleRef(null, IntPtr.Zero);
		
		if (obj != null)
		{
			ptr             = obj.swigCPtr;
			obj.swigCMemOwn = false;
		}
		
		return ptr;
	}

  ~RDFAnnotationParser() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          libsbmlPINVOKE.delete_RDFAnnotationParser(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  
  /**
   * Parses an annotation into a ModelHistory class instance.
   *
   * This is used to take an annotation that has been read into an SBML
   * model, identify the RDF elements representing model history
   * information, and create a list of corresponding CVTerm objects.
   *
   * @param annotation XMLNode containing the annotation.
   *
   * @return a pointer to the ModelHistory created.
   */
 public static ModelHistory parseRDFAnnotation(XMLNode annotation) {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_parseRDFAnnotation__SWIG_0(XMLNode.getCPtr(annotation));
    ModelHistory ret = (cPtr == IntPtr.Zero) ? null : new ModelHistory(cPtr, false);
    return ret;
  }

  
  /**
   * Creates a blank annotation and returns its root XMLNode object.
   *
   * This creates a completely empty SBML <c>&lt;annotation&gt;</c>
   * element.  It is not attached to any SBML element.  An example of how
   * this might be used is illustrated in the following code fragment.  In
   * this example, suppose that @c content is an XMLNode object previously
   * created, containing MIRIAM-style annotations, and that @c sbmlObject
   * is an SBML object derived from SBase (e.g., a Model, or a Species, or
   * a Compartment, etc.).  Then:@if clike
<code>
int success;                              // Status code variable, used below.

XMLNode RDF = createRDFAnnotation();     // Create RDF annotation XML structure.
success = RDF->addChild(...content...);   // Put some content into it.
...                                       // Check 'success' return code value.

XMLNode ann = createAnnotation();        // Create <annotation> container.
success = ann->addChild(RDF);             // Put the RDF annotation into it.
...                                       // Check 'success' return code value.

success = sbmlObject->setAnnotation(ann); // Set object's annotation to what we built.
...                                       // Check 'success' return code value.
</code>
   * @endif@if java
<code>
int success;                                   // Status code variable, used below.

XMLNode RDF = createRDFAnnotation();          // Create RDF annotation XML structure.
success      = RDF.addChild(...content...);    // Put some content into it.
...                                            // Check 'success' return code value.

XMLNode ann = createAnnotation();             // Create <annotation> container.
success      = ann.addChild(RDF);              // Put the RDF annotation into it.
...                                            // Check 'success' return code value.

success      = sbmlObject.setAnnotation(ann); // Set object's annotation to what we built.
...                                            // Check 'success' return code value.
</code>
   * @endif@if python
<code>
RDF     = RDFAnnotationParser.createRDFAnnotation() # Create RDF annotation XML structure.
success = RDF.addChild(...content...)               # Put some content into it.
...                                                 # Check 'success' return code value.

annot   = RDFAnnotationParser.createAnnotation()    # Create <annotation> container.
success = annot.addChild(RDF)                       # Put the RDF annotation into it.
...                                                 # Check 'success' return code value.

success = sbmlObject.setAnnotation(annot)           # Set object's annotation to what we built.
...                                                 # Check 'success' return code value.
</code>
   * @endif
   * The SBML specification contains more information about the format of
   * annotations.  We urge readers to consult Section&nbsp;6 of the SBML
   * Level&nbsp;2 (Versions 2&ndash;4) and SBML Level&nbsp;3 specification
   * documents.
   *
   * @return a pointer to an XMLNode for the annotation
   *
   * @see createRDFAnnotation()
   */
 public static XMLNode createAnnotation() {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_createAnnotation();
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  
  /**
   * Creates a blank RDF element suitable for use in SBML annotations.
   *
   * The annotation created by this method has namespace declarations for
   * all the relevant XML namespaces used in RDF annotations and also has
   * an empty RDF element.  The result is the following XML:
<code>
<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'
         xmlns:dc='http://purl.org/dc/elements/1.1/'
         xmlns:dcterms='http://purl.org/dc/terms/'
         xmlns:vCard='http://www.w3.org/2001/vcard-rdf/3.0#'
         xmlns:bqbiol='http://biomodels.net/biology-qualifiers/'
         xmlns:bqmodel='http://biomodels.net/model-qualifiers/' >

</rdf:RDF>
</code>
   *
   * Note that this does not create the containing SBML
   * <c>&lt;annotation&gt;</c> element; the method
   * @if clike createAnnotation()@else RDFAnnotationParser::createAnnotation()@endif
   * is available for creating the container.
   *
   * @return a pointer to an XMLNode
   *
   * @see createAnnotation()
   */
 public static XMLNode createRDFAnnotation() {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_createRDFAnnotation();
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  
  /**
   * Deletes any RDF annotation found in the given XMLNode tree and returns
   * any remaining annotation content.
   *
   * The name of the XMLNode given as parameter @p annotation must be
   * 'annotation', or else this method returns @c null.  The method will
   * walk down the XML structure looking for elements that are in the
   * RDF XML namespace, and remove them.
   *
   * @param annotation the XMLNode tree within which the RDF annotation is
   * to be found and deleted
   *
   * @return the XMLNode structure that is left after RDF annotations are
   * deleted.
   */
 public static XMLNode deleteRDFAnnotation(XMLNode annotation) {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_deleteRDFAnnotation(XMLNode.getCPtr(annotation));
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  
  /**
   * Takes an SBML object and creates an empty XMLNode corresponding to an
   * RDF 'Description' element.
   *
   * This method is a handy way of creating RDF description objects linked
   * by the appropriate 'metaid' field to the given @p object, for
   * insertion into RDF annotations in a model.  The method retrieves the
   * 'metaid' attribute from the @p object passed in as argument, then
   * creates an empty element having the following form
   * (where <span class='code' style='background-color: #eed0d0'>metaid</span> 
   * the value of the 'metaid' attribute of the argument):
   * 
<div class='fragment'>
&lt;rdf:Description rdf:about=&quot;#<span style='background-color: #eed0d0'>metaid</span>&quot; xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'&gt;<br>
...<br>
&lt;/rdf:Description&gt;<br>
</div>
   * Note that this method does @em not create a complete annotation or
   * even an RDF element; it only creates the 'Description' portion.  Callers
   * will need to use other methods such as
   * @if clike createRDFAnnotation()@else RDFAnnotationParser::createRDFAnnotation()@endif
   * to create the rest of the structure for an annotation.
   *
   * @param obj the object to which the 'Description' refers
   *
   * @return a new XMLNode containing the 'rdf:Description' element with
   * its 'about' attribute value set to the @p object meta identifier.
   *
   * @see createRDFAnnotation()
   */
 public static XMLNode createRDFDescription(SBase obj) {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_createRDFDescription(SBase.getCPtr(obj));
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  
  /**
   * Takes a list of CVTerm objects and creates a the RDF 'Description'
   * element.
   *
   * This essentially takes the given SBML object, reads out the CVTerm objects
   * attached to it, calls
   * @if clike createRDFDescription()@else RDFAnnotationParser::createRDFDescription(SBase object)@endif
   * to create an RDF 'Description' element to hold the terms and adds
   * each term with appropriate qualifiers.
   *
   * @param obj the SBML object to start from
   *
   * @return the XMLNode tree corresponding to the Description element of
   * an RDF annotation.
   */
 public static XMLNode createCVTerms(SBase obj) {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_createCVTerms(SBase.getCPtr(obj));
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  
  /**
   * Takes a list of CVTerm objects and creates a complete SBML annotation
   * around it.
   *
   * This essentially takes the given SBML object, calls
   * @if clike RDFAnnotationParser::createCVTerms()@else RDFAnnotationParser::createCVTerms(SBase obj)@endif
   * to read out the CVTerm objects
   * attached to it, calls
   * @if clike createRDFAnnotation()@else RDFAnnotationParser::createRDFAnnotation()@endif
   * to create an RDF
   * annotation to hold the terms, and finally calls
   * @if clike createAnnotation()@else RDFAnnotationParser::createAnnotation()@endif
   * to wrap the result as an SBML <c>&lt;annotation&gt;</c> element.
   *
   * @param obj the SBML object to start from
   *
   * @return the XMLNode tree corresponding to the annotation.
   */
 public static XMLNode parseCVTerms(SBase obj) {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_parseCVTerms(SBase.getCPtr(obj));
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  
  /**
   * Reads the model history stored in @p obj and creates the
   * XML structure for an SBML annotation representing that history.
   *
   * @param obj any SBase object
   *
   * @return the XMLNode corresponding to an annotation containing 
   * MIRIAM-compliant model history information in RDF format.
   */
 public static XMLNode parseModelHistory(SBase obj) {
    IntPtr cPtr = libsbmlPINVOKE.RDFAnnotationParser_parseModelHistory(SBase.getCPtr(obj));
    XMLNode ret = (cPtr == IntPtr.Zero) ? null : new XMLNode(cPtr, true);
    return ret;
  }

  public static void parseRDFAnnotation(XMLNode annotation, CVTermList CVTerms) {
    libsbmlPINVOKE.RDFAnnotationParser_parseRDFAnnotation__SWIG_1(XMLNode.getCPtr(annotation), CVTermList.getCPtr(CVTerms));
  }

  public RDFAnnotationParser() : this(libsbmlPINVOKE.new_RDFAnnotationParser(), true) {
  }

}

}
