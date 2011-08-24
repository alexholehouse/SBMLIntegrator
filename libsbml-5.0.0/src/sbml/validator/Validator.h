/**
 * @file    Validator.h
 * @brief   Base class for SBML Validators
 * @author  Ben Bornstein
 *
 * $Id: Validator.h 13539 2011-04-08 21:56:32Z fbergmann $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/validator/Validator.h $
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
 * @class Validator
 * @brief Entry point for libSBML's implementation of SBML validation
 * 
 * @htmlinclude not-sbml-warning.html
 *
 */

#ifndef Validator_h
#define Validator_h


#ifdef __cplusplus


/** @cond doxygen-libsbml-internal */

#include <list>
#include <string>

/** @endcond */


#include <sbml/SBMLError.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class VConstraint;
struct ValidatorConstraints;
class SBMLDocument;


class Validator
{
public:

  Validator ( SBMLErrorCategory_t category = LIBSBML_CAT_SBML );

  virtual ~Validator ();


  /**
   * Initializes this Validator with a set of Constraints.
   *
   * When creating a subclass of Validator, override this method to add
   * your own Constraints.
   */
  virtual void init () = 0;


  /**
   * Adds the given Contraint to this validator.
   */
  void addConstraint (VConstraint* c);


  /**
   * Clears the Validator's list of failures.
   *
   * If you are validating multiple SBML documents with the same Validator,
   * call this method after you have processed the list of failures from
   * the last Validation run and before validating the next document.
   */
  void clearFailures ();


  /**
   * Get the category of validation rules covered by this validator.
   *
   * The category values are drawn from the enumeration
   * #SBMLErrorCategory_t.  See the documentation for the class SBMLError
   * for more information.
   */
  const unsigned int getCategory () const;


  /**
   * Get the list of SBMLError objects (if any) logged as a result
   * of running the validator.
   * 
   * @return a list of failures logged during validation.
   */
  const std::list<SBMLError>& getFailures () const;


  /**
   * Adds the given failure to this list of Validators failures.
   */
  void logFailure (const SBMLError& msg);


  /**
   * Validates the given SBMLDocument.  Failures logged during
   * validation may be retrieved via getFailures().
   *
   * @return the number of validation errors that occurred.
   */
  unsigned int validate (const SBMLDocument& d);


  /**
   * Validates the given SBMLDocument.  Failures logged during
   * validation may be retrieved via getFailures().
   *
   * @return the number of validation errors that occurred.
   */
  unsigned int validate (const std::string& filename);


protected:
  /** @cond doxygen-libsbml-internal */


  ValidatorConstraints* mConstraints;
  std::list<SBMLError>  mFailures;
  unsigned int          mCategory;


  friend class ValidatingVisitor;

  /** @endcond */
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* Validator_h */
