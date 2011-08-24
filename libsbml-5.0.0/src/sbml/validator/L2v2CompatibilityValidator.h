/**
 * @cond doxygen-libsbml-internal
 *
 * @file    L2v2CompatibilityValidator.h
 * @brief   Checks whether an SBML model can be converted from L2v2/3 to L2v1
 * @author  Sarah Keating
 *
 * $Id: L2v2CompatibilityValidator.h 12789 2011-02-08 23:11:37Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/validator/L2v2CompatibilityValidator.h $
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
 * ---------------------------------------------------------------------- -->*/

#ifndef L2v2CompatibilityValidator_h
#define L2v2CompatibilityValidator_h


#ifdef __cplusplus


#include <sbml/validator/Validator.h>

LIBSBML_CPP_NAMESPACE_BEGIN

class L2v2CompatibilityValidator: public Validator
{
public:

  L2v2CompatibilityValidator () :
    Validator( LIBSBML_CAT_SBML_L2V2_COMPAT ) { }

  virtual ~L2v2CompatibilityValidator () { }

  /**
   * Initializes this Validator with a set of Constraints.
   */
  virtual void init ();
};

LIBSBML_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* L2v2CompatibilityValidator_h */


/** @endcond */