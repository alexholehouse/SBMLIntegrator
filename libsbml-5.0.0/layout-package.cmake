###############################################################################
#
# $URL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/layout-package.cmake $
# $Id: layout-package.cmake 12784 2011-02-08 07:37:42Z mhucka $
#
# Description       : CMake configuration for SBML Level 3 Layout package
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright (C) 2009-2011 jointly by the following organizations: 
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
#  
# Copyright (C) 2006-2008 by the California Institute of Technology,
#     Pasadena, CA, USA 
#  
# Copyright (C) 2002-2005 jointly by the following organizations: 
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. Japan Science and Technology Agency, Japan
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#
###############################################################################

option(ENABLE_LAYOUT     "Enable SBML Layout package"    OFF )

if(ENABLE_LAYOUT)
	add_definitions( -DUSE_LAYOUT )
	list(APPEND SWIG_EXTRA_ARGS -DUSE_LAYOUT)	
endif()
