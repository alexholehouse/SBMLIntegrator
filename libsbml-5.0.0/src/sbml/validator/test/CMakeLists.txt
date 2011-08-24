####################################################################
#
# CMake Build Script for libsbml validator tests
#
# $Author: fbergmann $
# $Id: CMakeLists.txt 13416 2011-04-04 21:49:58Z fbergmann $
# $HeadURL: https://sbml.svn.sourceforge.net/svnroot/sbml/branches/libsbml-5/src/sbml/validator/test/CMakeLists.txt $
#

if(UNIX)
    if(APPLE)
		if(WITH_LIBXML)
			# this is an odd one
			add_definitions(-DBUGGY_APPLE_LIBXML)
		endif()
	endif()
endif()

include(${CMAKE_SOURCE_DIR}/common.cmake)

file(GLOB C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

foreach(c_file ${C_FILES})
	set_source_files_properties(${c_file} PROPERTIES LANGUAGE CXX)
endforeach()

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )

set(TEST_FILES ${CPP_FILES} ${C_FILES})

include_directories(${CMAKE_SOURCE_DIR}/include/sbml)
include_directories(${CMAKE_SOURCE_DIR}/include/validator)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${LIBCHECK_INCLUDE_DIR})
add_executable(test_sbml_validator ${TEST_FILES})
target_link_libraries(test_sbml_validator ${LIBSBML_LIBRARY}-static ${LIBCHECK_LIBRARY})
add_test(test_sbml_validator_run ${CMAKE_CURRENT_BINARY_DIR}/test_sbml_validator 
		${CMAKE_CURRENT_SOURCE_DIR})

