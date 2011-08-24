# @configure_input@
# -----------------------------------------------------------------------------
# File name         : doxyfile-config-python.txt
# Description       : Doxygen config for Python libSBML API manual 
# Original author(s): Michael Hucka <mhucka@caltech.edu>
# Organization      : California Institute of Technology
# $Id: doxygen-config-python.txt.in 12164 2010-10-18 08:39:46Z sarahkeating $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/docs/src/doxygen-config-python.txt.in $
# -----------------------------------------------------------------------------

# Include libSBML's common Doxygen settings:

@INCLUDE               = doxygen-config-common.txt

# -----------------------------------------------------------------------------
# Beginning of C++ specific configuration settings
# -----------------------------------------------------------------------------

# The PROJECT_NAME tag is a single word (or a sequence of words surrounded 
# by quotes) that should identify the project.

PROJECT_NAME           = "@PACKAGE_NAME@ Python Public API"

# The PROJECT_NUMBER tag can be used to enter a project or revision number. 
# This could be handy for archiving the generated documentation or 
# if some version control system is used.

PROJECT_NUMBER         = "@PACKAGE_NAME@ @PACKAGE_VERSION@ Python Public API"

# The HTML_OUTPUT tag is used to specify where the HTML docs will be put. 
# If a relative path is entered the value of OUTPUT_DIRECTORY will be 
# put in front of it. If left blank `html' will be used as the default path.

HTML_OUTPUT            = ../formatted/python-api

# If you use STL classes (i.e. std::string, std::vector, etc.) but do not
# want to include (a tag file for) the STL sources as input, then you should
# set this tag to YES in order to let doxygen match functions declarations
# and definitions whose arguments contain STL classes
# (e.g. func(std::string); v.s. func(std::string) {}). This also make the
# inheritance and collaboration diagrams that involve STL classes more
# complete and accurate.

BUILTIN_STL_SUPPORT    = YES

# The PREDEFINED tag can be used to specify one or more macro names that 
# are defined before the preprocessor is started (similar to the -D option of 
# gcc). The argument of the tag is a list of macros of the form: name 
# or name=definition (no spaces). If the definition and the = are 
# omitted =1 is assumed.

PREDEFINED             = __cplusplus  \
		         LIBSBML_EXTERN:="" \
			 BEGIN_C_DECLS:="" \
			 END_C_DECLS:="" \
			 LIBSBML_CPP_NAMESPACE_BEGIN:="" \
			 LIBSBML_CPP_NAMESPACE_END:="" \
			 SWIG=1 \
			 doxygen_ignore

# The ENABLED_SECTIONS tag can be used to enable conditional 
# documentation sections, marked by \if sectionname ... \endif.

ENABLED_SECTIONS       = notcpp doxygen-python-only python

# Because of how we construct the Python documentation, we don't want
# the first sentence to be assumed to be the brief description.

BRIEF_MEMBER_DESC      = NO

# Override the settings in doxygen-config-common.txt to refer to just
# the files relevant for the Python bindings.

INPUT = \
  libsbml-accessing.txt            \
  libsbml-blurb.txt                \
  libsbml-coding.txt               \
  libsbml-communications.txt       \
  libsbml-features.txt             \
  libsbml-installation.txt         \
  libsbml-issues.txt               \
  libsbml-license.txt              \
  libsbml-news.txt                 \
  libsbml-python-mainpage.txt      \
  libsbml-python-math.txt          \
  libsbml-python-reading-files.txt \
  libsbml-uninstallation.txt       \
  ../../src/bindings/python/libsbml.py

# The INPUT_FILTER tag can be used to specify a program that doxygen should 
# invoke to filter for each input file. Doxygen will invoke the filter program 
# by executing (via popen()) the command <filter> <input-file>, where <filter> 
# is the value of the INPUT_FILTER tag, and <input-file> is the name of an 
# input file. Doxygen will then use the output that the filter program writes 
# to standard output.

INPUT_FILTER           = pythondocfilter.py

# Because of the way the proxies are done, @param never works properly.
# So don't bother telling us.

WARN_IF_DOC_ERROR      = NO

# According to the Doxygen 1.5.4 docs, you're supposed to set this for Python.

OPTIMIZE_OUTPUT_JAVA    = YES

# Ignore some symbols from the output

EXCLUDE_SYMBOLS         = *_swigregister __cmp__
