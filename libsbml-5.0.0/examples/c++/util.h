/**
 * @file    util.h
 * @brief   Supporting functions for example code
 * @author  Ben Bornstein
 *
 * $Id: util.h 12748 2011-02-03 19:54:07Z luciansmith $
 * $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/c++/util.h $
 *
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 */

#include <sbml/common/extern.h>


BEGIN_C_DECLS

/**
 * @return the number of milliseconds elapsed since the Epoch.
 */
unsigned long long
getCurrentMillis (void);

/**
 * @return the size (in bytes) of the given filename.
 */
unsigned long
getFileSize (const char* filename);

END_C_DECLS
