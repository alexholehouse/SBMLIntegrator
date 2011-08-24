####################################################################
#
# CMake Build Script for libsbml c++ examples
#
# $Author: fbergmann $
# $Id: CMakeLists.txt 13538 2011-04-08 20:44:07Z fbergmann $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/examples/c++/CMakeLists.txt $
#


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)

foreach(example 

	addCVTerms
	addingEvidenceCodes_1
	addingEvidenceCodes_2
	addModelHistory
	appendAnnotation
	convertSBML
	createExampleSBML
	echoSBML
	printAnnotation
	printMath
	printNotes
	printSBML
	printSupported
	printUnits
	readSBML
	translateMath
	unsetAnnotation
	unsetNotes
	validateSBML

)
	add_executable(example_cpp_${example} ${example} util.c)
	set_target_properties(example_cpp_${example} PROPERTIES  OUTPUT_NAME ${example})
	target_link_libraries(example_cpp_${example} ${LIBSBML_LIBRARY}-static)

endforeach()
