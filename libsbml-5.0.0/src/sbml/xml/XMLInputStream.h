/**
 * @file    XMLInputStream.h
 * @brief   XMLInputStream
 * @author  Ben Bornstein
 *
 * $Id: XMLInputStream.h 12789 2011-02-08 23:11:37Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/xml/XMLInputStream.h $
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2009-2011 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->
 *
 * @class XMLInputStream
 *
 * @if java @deprecated libSBML internal @endif
 */

#ifndef XMLInputStream_h
#define XMLInputStream_h

#include <sbml/xml/XMLExtern.h>
#include <sbml/xml/XMLToken.h>
#include <sbml/common/sbmlfwd.h>
#include <sbml/common/operationReturnValues.h>
#include <sbml/SBMLNamespaces.h>


#ifdef __cplusplus

#include <string>

#include <sbml/xml/XMLTokenizer.h>

LIBSBML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libsbml-internal */

class XMLErrorLog;
class XMLParser;


class LIBLAX_EXTERN XMLInputStream
{
public:

  /**
   * Creates a new XMLInputStream.
   *
   * @if notcpp @docnote @htmlinclude warn-default-args-in-docs.html @endif
   */
  XMLInputStream (  const char*        content
                  , bool               isFile   = true
                  , const std::string  library  = "" 
                  , XMLErrorLog*       errorLog = NULL );

  /**
   * Destroys this XMLInputStream.
   */
  virtual ~XMLInputStream ();


  /**
   * @return the encoding of the XML stream.
   */
  const std::string& getEncoding ();


  /**
   * @return the version of the XML stream.
   */
  const std::string& getVersion ();


  /**
   * @return an XMLErrorLog which can be used to log XML parse errors and
   * other validation errors (and messages).
   */
  XMLErrorLog* getErrorLog ();


  /**
   * @return true if end of file (stream) has been reached, false
   * otherwise.
   */
  bool isEOF () const;


  /**
   * @return true if a fatal error occurred while reading from this stream.
   */
  bool isError () const;


  /**
   * @return true if the stream is in a good state (i.e. isEOF() and
   * isError() are both false), false otherwise.
   */
  bool isGood () const;


  /**
   * Consumes the next XMLToken and return it.
   *
   * @return the next XMLToken or EOF (XMLToken.isEOF() == true).
   */
  XMLToken next ();


  /**
   * Returns the next XMLToken without consuming it.  A subsequent call to
   * either peek() or next() will return the same token.
   *
   * @return the next XMLToken or EOF (XMLToken.isEOF() == true).
   */
  const XMLToken& peek ();


  /**
   * Consume zero or more XMLTokens up to and including the corresponding
   * end XML element or EOF.
   */
  void skipPastEnd (const XMLToken& element);


  /**
   * Consume zero or more XMLTokens up to but not including the next XML
   * element or EOF.
   */
  void skipText ();


  /**
   * Sets the XMLErrorLog this stream will use to log errors.
   *
   * @return integer value indicating success/failure of the
   * function.  @if clike The value is drawn from the
   * enumeration #OperationReturnValues_t. @endif The possible values
   * returned by this function are:
   * @li @link OperationReturnValues_t#LIBSBML_OPERATION_SUCCESS LIBSBML_OPERATION_SUCCESS @endlink
   * @li @link OperationReturnValues_t#@link OperationReturnValues_t#LIBSBML_OPERATION_FAILED LIBSBML_OPERATION_FAILED @endlink @link OperationReturnValues_t#LIBSBML_OPERATION_FAILED LIBSBML_OPERATION_FAILED @endlink @endlink
   */
  int setErrorLog (XMLErrorLog* log);


  /**
   * Prints a string representation of the underlying token stream, for
   * debugging purposes.
   */
  std::string toString ();

  SBMLNamespaces * getSBMLNamespaces();

  void setSBMLNamespaces(SBMLNamespaces * sbmlns);

protected:

  /**
   * Unitialized XMLInputStreams may only be created by subclasses.
   */
  XMLInputStream ();


  /**
   * Runs mParser until mTokenizer is ready to deliver at least one
   * XMLToken or a fatal error occurs.
   */
  void queueToken ();


  bool mIsError;

  XMLToken     mEOF;
  XMLTokenizer mTokenizer;
  XMLParser*   mParser;

  SBMLNamespaces* mSBMLns;

};

/** @endcond */

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */



#ifndef SWIG

LIBSBML_CPP_NAMESPACE_BEGIN

/** @cond doxygen-libsbml-internal */

BEGIN_C_DECLS

/* ----------------------------------------------------------------------------
 * See the .cpp file for the documentation of the following functions.
 * --------------------------------------------------------------------------*/


LIBLAX_EXTERN
XMLInputStream_t *
XMLInputStream_create (const char* content, int isFile, const char *library);


LIBLAX_EXTERN
void
XMLInputStream_free (XMLInputStream_t *stream);


LIBLAX_EXTERN
const char *
XMLInputStream_getEncoding (XMLInputStream_t *stream);


LIBLAX_EXTERN
XMLErrorLog_t *
XMLInputStream_getErrorLog (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_isEOF (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_isError (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_isGood (XMLInputStream_t *stream);


LIBLAX_EXTERN
XMLToken_t *
XMLInputStream_next (XMLInputStream_t *stream);


LIBLAX_EXTERN
const XMLToken_t *
XMLInputStream_peek (XMLInputStream_t *stream);


LIBLAX_EXTERN
void
XMLInputStream_skipPastEnd (XMLInputStream_t *stream,
			    const XMLToken_t *element);


LIBLAX_EXTERN
void
XMLInputStream_skipText (XMLInputStream_t *stream);


LIBLAX_EXTERN
int
XMLInputStream_setErrorLog (XMLInputStream_t *stream, XMLErrorLog_t *log);

END_C_DECLS

/** @endcond */

LIBSBML_CPP_NAMESPACE_END

#endif  /* !SWIG */
#endif  /* XMLInputStream_h */
