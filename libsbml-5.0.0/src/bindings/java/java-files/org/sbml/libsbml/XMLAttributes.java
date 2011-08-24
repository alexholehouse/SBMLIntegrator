/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.0
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.sbml.libsbml;

/** 
 * Representation of attributes on an XML node.
 * <p>
 * <p style='color: #555; font-style: italic'>
This class of objects is defined by libSBML only and has no direct
equivalent in terms of SBML components.  This class is not prescribed by
the SBML specifications, although it is used to implement features
defined in SBML.
</p>

 * <p>
 */

public class XMLAttributes {
   private long swigCPtr;
   protected boolean swigCMemOwn;

   protected XMLAttributes(long cPtr, boolean cMemoryOwn)
   {
     swigCMemOwn = cMemoryOwn;
     swigCPtr    = cPtr;
   }

   protected static long getCPtr(XMLAttributes obj)
   {
     return (obj == null) ? 0 : obj.swigCPtr;
   }

   protected static long getCPtrAndDisown (XMLAttributes obj)
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
        libsbmlJNI.delete_XMLAttributes(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  /**
   * Equality comparison method for XMLAttributes.
   * <p>
   * Because the Java methods for libSBML are actually wrappers around code
   * implemented in C++ and C, certain operations will not behave as
   * expected.  Equality comparison is one such case.  An instance of a
   * libSBML object class is actually a <em>proxy object</em>
   * wrapping the real underlying C/C++ object.  The normal <code>==</code>
   * equality operator in Java will <em>only compare the Java proxy objects</em>,
   * not the underlying native object.  The result is almost never what you
   * want in practical situations.  Unfortunately, Java does not provide a
   * way to override <code>==</code>.
   *  <p>
   * The alternative that must be followed is to use the
   * <code>equals()</code> method.  The <code>equals</code> method on this
   * class overrides the default java.lang.Object one, and performs an
   * intelligent comparison of instances of objects of this class.  The
   * result is an assessment of whether two libSBML Java objects are truly 
   * the same underlying native-code objects.
   *  <p>
   * The use of this method in practice is the same as the use of any other
   * Java <code>equals</code> method.  For example,
   * <em>a</em><code>.equals(</code><em>b</em><code>)</code> returns
   * <code>true</code> if <em>a</em> and <em>b</em> are references to the
   * same underlying object.
   *
   * @param sb a reference to an object to which the current object
   * instance will be compared
   *
   * @return <code>true</code> if <code>sb</code> refers to the same underlying 
   * native object as this one, <code>false</code> otherwise
   */
  public boolean equals(Object sb)
  {
    if ( this == sb ) 
    {
      return true;
    }
    return swigCPtr == getCPtr((XMLAttributes)(sb));
  }

  /**
   * Returns a hashcode for this XMLAttributes object.
   *
   * @return a hash code usable by Java methods that need them.
   */
  public int hashCode()
  {
    return (int)(swigCPtr^(swigCPtr>>>32));
  }

  
  /**
   * Creates a new empty {@link XMLAttributes} set.
   */
 public XMLAttributes() throws org.sbml.libsbml.XMLConstructorException {
    this(libsbmlJNI.new_XMLAttributes__SWIG_0(), true);
  }

  
  /**
   * Copy constructor; creates a copy of this {@link XMLAttributes} set.
   */
 public XMLAttributes(XMLAttributes orig) throws org.sbml.libsbml.XMLConstructorException {
    this(libsbmlJNI.new_XMLAttributes__SWIG_1(XMLAttributes.getCPtr(orig), orig), true);
  }

  
  /**
   * Creates and returns a deep copy of this {@link XMLAttributes} set.
   * <p>
   * @return a (deep) copy of this {@link XMLAttributes} set.
   */
 public XMLAttributes cloneObject() {
    long cPtr = libsbmlJNI.XMLAttributes_cloneObject(swigCPtr, this);
    return (cPtr == 0) ? null : new XMLAttributes(cPtr, true);
  }

  
  /**
   * Adds an attribute (a name/value pair) to this {@link XMLAttributes} object,
   * optionally with a prefix and URI defining a namespace.
   * <p>
   * @param name a string, the local name of the attribute.
   * @param value a string, the value of the attribute.
   * @param namespaceURI a string, the namespace URI of the attribute.
   * @param prefix a string, the prefix of the namespace
   * <p>
   * @return an integer code indicating the success or failure of the
   * function.  The possible values returned by this
   * function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <p>
   * @note if local name with the same namespace URI already exists in this 
   * attribute set, its value and prefix will be replaced.
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
 public int add(String name, String value, String namespaceURI, String prefix) {
    return libsbmlJNI.XMLAttributes_add__SWIG_0(swigCPtr, this, name, value, namespaceURI, prefix);
  }

  
  /**
   * Adds an attribute (a name/value pair) to this {@link XMLAttributes} object,
   * optionally with a prefix and URI defining a namespace.
   * <p>
   * @param name a string, the local name of the attribute.
   * @param value a string, the value of the attribute.
   * @param namespaceURI a string, the namespace URI of the attribute.
   * @param prefix a string, the prefix of the namespace
   * <p>
   * @return an integer code indicating the success or failure of the
   * function.  The possible values returned by this
   * function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <p>
   * @note if local name with the same namespace URI already exists in this 
   * attribute set, its value and prefix will be replaced.
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
 public int add(String name, String value, String namespaceURI) {
    return libsbmlJNI.XMLAttributes_add__SWIG_1(swigCPtr, this, name, value, namespaceURI);
  }

  
  /**
   * Adds an attribute (a name/value pair) to this {@link XMLAttributes} object,
   * optionally with a prefix and URI defining a namespace.
   * <p>
   * @param name a string, the local name of the attribute.
   * @param value a string, the value of the attribute.
   * @param namespaceURI a string, the namespace URI of the attribute.
   * @param prefix a string, the prefix of the namespace
   * <p>
   * @return an integer code indicating the success or failure of the
   * function.  The possible values returned by this
   * function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <p>
   * @note if local name with the same namespace URI already exists in this 
   * attribute set, its value and prefix will be replaced.
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
 public int add(String name, String value) {
    return libsbmlJNI.XMLAttributes_add__SWIG_2(swigCPtr, this, name, value);
  }

  
  /**
   * Adds an attribute with the given {@link XMLTriple}/value pair to this {@link XMLAttributes} set.
   * <p>
   * @note if local name with the same namespace URI already exists in this attribute set, 
   * its value and prefix will be replaced.
   * <p>
   * @param triple an {@link XMLTriple}, the XML triple of the attribute.
   * @param value a string, the value of the attribute.
   * <p>
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   */
 public int add(XMLTriple triple, String value) {
    return libsbmlJNI.XMLAttributes_add__SWIG_3(swigCPtr, this, XMLTriple.getCPtr(triple), triple, value);
  }

  
  /**
   * Removes an attribute with the given index from this {@link XMLAttributes} set.  
   * <p>
   * @param n an integer the index of the resource to be deleted
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE }
   */
 public int removeResource(int n) {
    return libsbmlJNI.XMLAttributes_removeResource(swigCPtr, this, n);
  }

  
  /**
   * Removes an attribute with the given index from this {@link XMLAttributes} set.  
   * (This function is an alias of {@link XMLAttributes#removeResource(int n)} ).
   * <p>
   * @param n an integer the index of the resource to be deleted
   * <p>
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE }
   */
 public int remove(int n) {
    return libsbmlJNI.XMLAttributes_remove__SWIG_0(swigCPtr, this, n);
  }

  
  /**
   * Removes an attribute with the given local name and namespace URI from 
   * this {@link XMLAttributes} set.  
   * <p>
   * @param name   a string, the local name of the attribute.
   * @param uri    a string, the namespace URI of the attribute.
   * <p>
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE }
   */
 public int remove(String name, String uri) {
    return libsbmlJNI.XMLAttributes_remove__SWIG_1(swigCPtr, this, name, uri);
  }

  
  /**
   * Removes an attribute with the given local name and namespace URI from 
   * this {@link XMLAttributes} set.  
   * <p>
   * @param name   a string, the local name of the attribute.
   * @param uri    a string, the namespace URI of the attribute.
   * <p>
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE }
   */
 public int remove(String name) {
    return libsbmlJNI.XMLAttributes_remove__SWIG_2(swigCPtr, this, name);
  }

  
  /**
   * Removes an attribute with the given {@link XMLTriple} from this {@link XMLAttributes} set.  
   * <p>
   * @param triple an {@link XMLTriple}, the XML triple of the attribute.
   * <p>
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   * <li> {@link  libsbmlConstants#LIBSBML_INDEX_EXCEEDS_SIZE LIBSBML_INDEX_EXCEEDS_SIZE }
   */
 public int remove(XMLTriple triple) {
    return libsbmlJNI.XMLAttributes_remove__SWIG_3(swigCPtr, this, XMLTriple.getCPtr(triple), triple);
  }

  
  /**
   * Clears (deletes) all attributes in this {@link XMLAttributes} object.
   * <p>
   * @return integer value indicating success/failure of the
   * function. The possible values
   * returned by this function are:
   * <li> {@link  libsbmlConstants#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS }
   */
 public int clear() {
    return libsbmlJNI.XMLAttributes_clear(swigCPtr, this);
  }

  
  /**
   * Return the index of an attribute with the given name.
   * <p>
   * @note A namespace bound to the name is not checked by this function.
   * Thus, if there are multiple attributes with the given local name and
   * different namespaces, the smallest index among those attributes will
   * be returned.  {@link XMLAttributes#getIndex(String name, String uri)} const or
   * {@link XMLAttributes#getIndex(XMLTriple triple)} const should be used to get an index of an
   * attribute with the given local name and namespace.
   * <p>
   * @param name a string, the local name of the attribute for which the 
   * index is required.
   * <p>
   * @return the index of an attribute with the given local name, or -1 if not present.
   */
 public int getIndex(String name) {
    return libsbmlJNI.XMLAttributes_getIndex__SWIG_0(swigCPtr, this, name);
  }

  
  /**
   * Return the index of an attribute with the given local name and namespace URI.
   * <p>
   * @param name a string, the local name of the attribute.
   * @param uri  a string, the namespace URI of the attribute.
   * <p>
   * @return the index of an attribute with the given local name and namespace URI, 
   * or -1 if not present.
   */
 public int getIndex(String name, String uri) {
    return libsbmlJNI.XMLAttributes_getIndex__SWIG_1(swigCPtr, this, name, uri);
  }

  
  /**
   * Return the index of an attribute with the given {@link XMLTriple}.
   * <p>
   * @param triple an {@link XMLTriple}, the XML triple of the attribute for which 
   *        the index is required.
   * <p>
   * @return the index of an attribute with the given {@link XMLTriple}, or -1 if not present.
   */
 public int getIndex(XMLTriple triple) {
    return libsbmlJNI.XMLAttributes_getIndex__SWIG_2(swigCPtr, this, XMLTriple.getCPtr(triple), triple);
  }

  
  /**
   * Return the number of attributes in the set.
   * <p>
   * @return the number of attributes in this {@link XMLAttributes} set.
   */
 public int getLength() {
    return libsbmlJNI.XMLAttributes_getLength(swigCPtr, this);
  }

  
  /**
   * Return the number of attributes in the set.
   * <p>
   * @return the number of attributes in this {@link XMLAttributes} set.
   * <p>
   * This function is an alias for getLength introduced for consistency
   * with other XML classes.
   */
 public int getNumAttributes() {
    return libsbmlJNI.XMLAttributes_getNumAttributes(swigCPtr, this);
  }

  
  /**
   * Return the local name of an attribute in this {@link XMLAttributes} set (by position).
   * <p>
   * @param index an integer, the position of the attribute whose local name is 
   * required.
   * <p>
   * @return the local name of an attribute in this list (by position).  
   * <p>
   * @note If index is out of range, an empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(int index)} const to test for the attribute
   * existence.
   */
 public String getName(int index) {
    return libsbmlJNI.XMLAttributes_getName(swigCPtr, this, index);
  }

  
  /**
   * Return the prefix of an attribute in this {@link XMLAttributes} set (by position).
   * <p>
   * @param index an integer, the position of the attribute whose prefix is 
   * required.
   * <p>
   * @return the namespace prefix of an attribute in this list (by
   * position).  
   * <p>
   * @note If index is out of range, an empty string will be returned. Use
   * {@link XMLAttributes#hasAttribute(int index)} const to test for the attribute
   * existence.
   */
 public String getPrefix(int index) {
    return libsbmlJNI.XMLAttributes_getPrefix(swigCPtr, this, index);
  }

  
  /**
   * Return the prefixed name of an attribute in this {@link XMLAttributes} set (by position).
   * <p>
   * @param index an integer, the position of the attribute whose prefixed 
   * name is required.
   * <p>
   * @return the prefixed name of an attribute in this list (by
   * position).  
   * <p>
   * @note If index is out of range, an empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(int index)} const to test for attribute existence.
   */
 public String getPrefixedName(int index) {
    return libsbmlJNI.XMLAttributes_getPrefixedName(swigCPtr, this, index);
  }

  
  /**
   * Return the namespace URI of an attribute in this {@link XMLAttributes} set (by position).
   * <p>
   * @param index an integer, the position of the attribute whose namespace URI is 
   * required.
   * <p>
   * @return the namespace URI of an attribute in this list (by position).
   * <p>
   * @note If index is out of range, an empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(int index)} const to test for attribute existence.
   */
 public String getURI(int index) {
    return libsbmlJNI.XMLAttributes_getURI(swigCPtr, this, index);
  }

  
  /**
   * Return the value of an attribute in this {@link XMLAttributes} set (by position).
   * <p>
   * @param index an integer, the position of the attribute whose value is 
   * required.
   * <p>
   * @return the value of an attribute in the list (by position).  
   * <p>
   * @note If index is out of range, an empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(int index)} const to test for attribute existence.
   */
 public String getValue(int index) {
    return libsbmlJNI.XMLAttributes_getValue__SWIG_0(swigCPtr, this, index);
  }

  
  /**
   * Return an attribute's value by name.
   * <p>
   * @param name a string, the local name of the attribute whose value is required.
   * <p>
   * @return The attribute value as a string.  
   * <p>
   * @note If an attribute with the given local name does not exist, an
   * empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(String name, String uri)} const
   * to test for attribute existence.  A namespace bound to the local name
   * is not checked by this function.  Thus, if there are multiple
   * attributes with the given local name and different namespaces, the
   * value of an attribute with the smallest index among those attributes
   * will be returned.  {@link XMLAttributes#getValue(String name)} const or
   * {@link XMLAttributes#getValue(XMLTriple triple)} const should be used to get a value of an
   * attribute with the given local name and namespace.
   */
 public String getValue(String name) {
    return libsbmlJNI.XMLAttributes_getValue__SWIG_1(swigCPtr, this, name);
  }

  
  /**
   * Return a value of an attribute with the given local name and namespace URI.
   * <p>
   * @param name a string, the local name of the attribute whose value is required.
   * @param uri  a string, the namespace URI of the attribute.
   * <p>
   * @return The attribute value as a string.  
   * <p>
   * @note If an attribute with the given local name and namespace URI does
   * not exist, an empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(String name, String uri)} const
   * to test for attribute existence.
   */
 public String getValue(String name, String uri) {
    return libsbmlJNI.XMLAttributes_getValue__SWIG_2(swigCPtr, this, name, uri);
  }

  
  /**
   * Return a value of an attribute with the given {@link XMLTriple}.
   * <p>
   * @param triple an {@link XMLTriple}, the XML triple of the attribute whose 
   *        value is required.
   * <p>
   * @return The attribute value as a string.  
   * <p>
   * @note If an attribute with the given {@link XMLTriple} does not exist, an
   * empty string will be returned.  Use
   * {@link XMLAttributes#hasAttribute(XMLTriple triple)} const to test for attribute existence.
   */
 public String getValue(XMLTriple triple) {
    return libsbmlJNI.XMLAttributes_getValue__SWIG_3(swigCPtr, this, XMLTriple.getCPtr(triple), triple);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * an attribute with the given index exists in this {@link XMLAttributes}.
   * <p>
   * @param index an integer, the position of the attribute.
   * <p>
   * @return <code>true</code> if an attribute with the given index exists in this
   * {@link XMLAttributes}, <code>false</code> otherwise.
   */
 public boolean hasAttribute(int index) {
    return libsbmlJNI.XMLAttributes_hasAttribute__SWIG_0(swigCPtr, this, index);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * an attribute with the given local name and namespace URI exists in this 
   * {@link XMLAttributes}.
   * <p>
   * @param name a string, the local name of the attribute.
   * @param uri  a string, the namespace URI of the attribute.
   * <p>
   * @return <code>true</code> if an attribute with the given local name and namespace 
   * URI exists in this {@link XMLAttributes}, <code>false</code> otherwise.
   */
 public boolean hasAttribute(String name, String uri) {
    return libsbmlJNI.XMLAttributes_hasAttribute__SWIG_1(swigCPtr, this, name, uri);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * an attribute with the given local name and namespace URI exists in this 
   * {@link XMLAttributes}.
   * <p>
   * @param name a string, the local name of the attribute.
   * @param uri  a string, the namespace URI of the attribute.
   * <p>
   * @return <code>true</code> if an attribute with the given local name and namespace 
   * URI exists in this {@link XMLAttributes}, <code>false</code> otherwise.
   */
 public boolean hasAttribute(String name) {
    return libsbmlJNI.XMLAttributes_hasAttribute__SWIG_2(swigCPtr, this, name);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether
   * an attribute with the given XML triple exists in this {@link XMLAttributes}.
   * <p>
   * @param triple an {@link XMLTriple}, the XML triple of the attribute 
   * <p>
   * @return <code>true</code> if an attribute with the given XML triple exists in this
   * {@link XMLAttributes}, <code>false</code> otherwise.
   * <p>
   */
 public boolean hasAttribute(XMLTriple triple) {
    return libsbmlJNI.XMLAttributes_hasAttribute__SWIG_3(swigCPtr, this, XMLTriple.getCPtr(triple), triple);
  }

  
  /**
   * Predicate returning <code>true</code> or <code>false</code> depending on whether 
   * this {@link XMLAttributes} set is empty.
   * <p>
   * @return <code>true</code> if this {@link XMLAttributes} set is empty, <code>false</code> otherwise.
   */
 public boolean isEmpty() {
    return libsbmlJNI.XMLAttributes_isEmpty(swigCPtr, this);
  }

}