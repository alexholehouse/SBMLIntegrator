/* src/sbml/common/libsbml-config-common.h.  Generated from libsbml-config-common.h.in by configure.  */
/**
 * @file    libsbml-config-common.h
 * @brief   Configuration variables 
 * @author  Ben Bornstein
 *
 * $Id: libsbml-config-unix.h.in 8704 2009-01-04 02:26:05Z mhucka $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/trunk/libsbml/src/common/libsbml-config-unix.h.in $
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
 *------------------------------------------------------------------------- -->
 *
 * If this file is named <tt>libsbml-config-unix.h</tt>, then it was
 * generated from <tt>libsbml-config-unix.h.in</tt> by the @c configure
 * script at the top level of the libSBML source tree.
 *
 * @note This file is handled unusually.  The file itself is generated by
 * @c configure, but unlike other files that are likewise automatically
 * generated, it is also checked into the source repository.  The need for
 * this is due to the fact that under Windows, developers may not be
 * running @c configure at all (e.g., if they are using the MSVC
 * environment).  The <tt>libsbml-config-win.h</tt> file therefore needs to
 * be provided directly in order for people to be able to compile the
 * sources under Windows.  For consistency, the file
 * <tt>libsbml-config-unix.h</tt> is also similarly checked in.  Developers
 * must remember to check in the .h version of this file in the source code
 * repository prior to major releases, so that an up-to-date .h file is
 * present in distributions.  This is admittedly an undesirable and
 * error-prone situation, but it is currently the best alternative we have
 * been able to find.
 */


/* Define to 1 if you have the <check.h> header file. */
#define HAVE_CHECK_H 1

/* Define to 1 if you have the `check' library (-lcheck). */
/* #undef HAVE_LIBCHECK */



/* Define to 1 if you have the <expat.h> header file. */
/* #undef HAVE_EXPAT_H */

/* Define to 1 to use the Expat XML library */
/* #undef USE_EXPAT */


/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <ieeefp.h> header file. */
/* #undef HAVE_IEEEFP_H */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you have the <math.h> header file. */
#define HAVE_MATH_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the `m' library (-lm). */
#define HAVE_LIBM 1


/* Define to 1 to enable primitive memory tracing. */
/* #undef TRACE_MEMORY */

/* Define to 1 to build the SBML layout extension. */
/* #undef USE_LAYOUT */

/* Define to 1 to build the SBML groups extension. */
/* #undef USE_GROUPS */


/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef WORDS_BIGENDIAN */
