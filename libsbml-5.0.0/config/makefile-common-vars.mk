## config/makefile-common-vars.mk.  Generated from makefile-common-vars.mk.in by configure.
##
## Filename    : makefile-common-vars.mk.in
## Description : Makefile include file containing common variable definitions
## Author(s)   : SBML Team <sbml-team@caltech.edu>
## Organization: California Institute of Technology
## Created     : 2004-06-11
## Revision    : $Id: makefile-common-vars.mk.in 13492 2011-04-07 23:33:33Z mhucka $
## $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/config/makefile-common-vars.mk.in $
##
## <!--------------------------------------------------------------------------
## This file is part of libSBML.  Please visit http://sbml.org for more
## information about SBML, and the latest version of libSBML.
##
## Copyright (C) 2009-2011 jointly by the following organizations: 
##     1. California Institute of Technology, Pasadena, CA, USA
##     2. EMBL European Bioinformatics Institute (EBML-EBI), Hinxton, UK
##  
## Copyright (C) 2006-2008 by the California Institute of Technology,
##     Pasadena, CA, USA 
##  
## Copyright (C) 2002-2005 jointly by the following organizations: 
##     1. California Institute of Technology, Pasadena, CA, USA
##     2. Japan Science and Technology Agency, Japan
##
## This library is free software; you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation.  A copy of the license agreement is provided
## in the file named "LICENSE.txt" included with this software distribution
## and also available online as http://sbml.org/software/libsbml/license.html
## ---------------------------------------------------------------------- -->*/


# -----------------------------------------------------------------------------
# Commmon variables.
# -----------------------------------------------------------------------------
#
# For '@' variables (which are expanded by configure), make sure not to
# put anything in here that might expand to a relative path.
#
# `prefix', `exec_prefix', `top_srcdir' and `top_builddir' must be in
# lowercase, because some of the autoconf macros expand into strings that
# use them.
#
# The enclosing makefile is assumed to define `srcdir'.

prefix            = /home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml
exec_prefix       = ${prefix}

# The TOP_SRCDIR and TOP_BUILDDIR variables frequently looks like
# /foo/config/.. and this is kind of ugly (and leads to other paths looking
# confusing), so let's get a cleaned up path first:

top_srcdir        = /home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml-5.0.0
top_builddir      = /home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml-5.0.0
TOP_SRCDIR        := $(shell cd $(top_srcdir); /bin/pwd)
TOP_BUILDDIR      := $(shell cd $(top_builddir); /bin/pwd)
DISTDIR           = $(top_srcdir)/$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)


# As of autoconf 2.60, @ datadir @ has been changed to @ datarootdir @.
# Prior to 2.60, @ datarootdir @ won't get expanded.

nodatarootdir     = $(findstring @,"${prefix}/share")

ifeq "$(nodatarootdir)" "@"
  DATADIR         = ${datarootdir}
else
  DATADIR         = ${prefix}/share
endif

BINDIR            = ${exec_prefix}/bin
INCLUDEDIR        = ${prefix}/include
LIBDIR            = ${exec_prefix}/lib
DOCDIR            = $(DATADIR)/doc/$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)
MANDIR            = ${datarootdir}/man

# Starting release 2.3, we put header files in ...include/sbml
INCLUDEPREFIX	  = sbml

LIBSBML_OPTIONS   =  USE_UNIVBINARY USE_PYTHON USE_PERL USE_JAVA USE_MATLAB USE_OCTAVE USE_RUBY USE_CSHARP USE_SWIG USE_EXPAT USE_XERCES USE_LIBCHECK USE_ZLIB USE_BZ2
RUN_LDPATH        = :/home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml/lib/:/home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml/lib/:/home/alex/Documents/imperial/project/work/SBMLIntegrator/source/libsbml/lib/:

USE_LIBCHECK      = 
LIBCHECK_CPPFLAGS = 
LIBCHECK_LDFLAGS  = 
LIBCHECK_LIBS     = 

USE_EXPAT         = 
EXPAT_CPPFLAGS    = 
EXPAT_LDFLAGS     = 
EXPAT_LIBS        = 

USE_XERCES        = 
XERCES_CPPFLAGS   = 
XERCES_LDFLAGS    = 
XERCES_LIBS       = 

USE_LIBXML        = 1
LIBXML_CPPFLAGS   = -I/usr/include/libxml2
LIBXML_LDFLAGS    = 
LIBXML_LIBS       = -lxml2
XML2_CONFIG       = /usr/bin/xml2-config
BUGGY_APPLE_LIBXML = 

USE_PYTHON        = 
PYTHON            = 
PYTHON_CPPFLAGS   = 
PYTHON_LDFLAGS    = 
PYTHON_LIBS       = 
PYTHON_EXT        = 

USE_PERL          = 
PERL              = 
PERL_CPPFLAGS     = 
PERL_LDFLAGS      = 
PERL_LIBS         = 

USE_RUBY          = 
RUBY              = 
RUBY_CPPFLAGS     = 
RUBY_LDFLAGS      = 
RUBY_LIBS         = 

USE_JAVA          = 
JAVA              = 
JAVAC             = 
JAR               = 
JAVADOC_JAR       = 
JAVA_CPPFLAGS     = 
JAVA_LDFLAGS      = 
JNIEXT            = 
JNIBASENAME       = 

USE_CSHARP            = 
CSHARP_COMPILER       = 
CSHARP_CILINTERPRETER = 
CSHARP_CPPFLAGS       = 
CSHARP_LDFLAGS        = 
CSHARP_SWIGFLAGS      = 
CSHARP_EXT            = 
SN                    = 
GACUTIL               = 

USE_MATLAB        = 
MATLAB            = 

USE_OCTAVE        = 
OCTAVE            = 
MKOCTFILE         = 
MKOCTFILE_FLAGS   = 
MKOCTFILE_WRAPPER = $(SHELL) $(top_srcdir)/config/mkoctfile_wrapper.sh
LOCALOCTFILEDIR   = 
OCTAVE_CONFIG     = 
OCTAVEEXT         = 

USE_LISP          = @USE_LISP@
LISP              = @LISP@
LISPEXIT          = @LISPEXIT@
FASLEXT           = @FASLEXT@
EXT_ASDF          = @EXT_ASDF@
ASDF              = @ASDF@
EXT_UFFI          = @EXT_UFFI@
UFFI              = @UFFI@
EXT_CPARSE        = @EXT_CPARSE@
CPARSE            = @CPARSE@

USE_LAYOUT        = 

USE_SWIG          = 
SWIG              = swig
SWIGLIB           = 
SWIGFLAGS         = 
SWIGNEEDVERSION   = 2.0.0

ACLOCAL           = /usr/bin/aclocal
ACLOCAL_M4        = $(top_srcdir)/aclocal.m4
ACINCLUDE_M4      = $(top_srcdir)/acinclude.m4
AUTOCONF          = /usr/bin/autoconf

USE_DOXYGEN       = 
DOXYGEN           = no-doxygen-found

USE_ZLIB          = 1
ZLIB_CPPFLAGS     = 
ZLIB_LDFLAGS      = 
ZLIB_LIBS         = -lz

USE_BZ2           = 1
BZ2_CPPFLAGS      = 
BZ2_LDFLAGS       = 
BZ2_LIBS          = -lbz2

USE_UNIVBINARY    = 
USE_SUN_CC        = 
HAS_GCC_WNO_LONG_DOUBLE = 1

LIBSUFFIX         = 

AR                = ar
AWK               = awk
BUILD             = i686-pc-linux-gnu
BUILD_CPU         = i686
BUILD_OS          = linux-gnu
CC                = gcc
CD                = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
CFLAGS            = 
CPP               = gcc -E
CPPFLAGS          = -DLINUX   
CTAGS             = ctags
CTAGSFLAGS        = --ignore-indentation --members --globals --typedefs-and-c++ --no-warn -o CTAGS
CXX               = g++
CXXFLAGS          = 
CYGPATH_W         = @CYGPATH_W@
DEFS              = -DHAVE_CONFIG_H
DEPDIR            = .deps
DEPEXT            = Po
ETAGS             = etags
ETAGSFLAGS        = --declarations --ignore-indentation --members
EXEEXT            = 
HOST_OS           = linux-gnu
HOST_TYPE         = linux
HOST_CPU          = i686
ifeq "$(HOST_TYPE)" "darwin"
  MACOS_VERSION   = $(shell sw_vers -productVersion | cut -d"." -f1,2)
else
  MACOS_VERSION   =
endif
INSTALL           = /usr/bin/install -c
INSTALL_SH        = $(top_srcdir)/config/install-sh -c
LDFLAGS           =   
LIBS              = -lm   -lz -lbz2
MKINSTALLDIRS     = $(SHELL) $(top_srcdir)/config/mkinstalldirs
OBJEXT            = o
PACKAGE           = libsbml
PACKAGE_BUGREPORT = libsbml-team@caltech.edu
PACKAGE_NAME      = libSBML
PACKAGE_STRING    = libSBML 5.0.0
PACKAGE_TARNAME   = libsbml
PACKAGE_VERSION   = 5.0.0
RANLIB            = ranlib
SHAREDLIBEXT      = so
LIBTOOL           = $(top_builddir)/doltlibtool
SHELL             = /bin/bash

LIBSBML_VERSION   = 5.0.0
LIBSBML_VERSION_NUMERIC = 50000


# -----------------------------------------------------------------------------
# End.
# -----------------------------------------------------------------------------

## The following is for [X]Emacs users.  Please leave in place.
## Local Variables:
## mode: Makefile
## End:
