#
# The OCE unittest framework use GoogleTest 1.6.0 (aka GTest)
# The GTest source code is available in the /test/gtest-1.6.0 folder
#
SET(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.6.0)

INCLUDE_DIRECTORIES(${GTEST_ROOT}/include ${GTEST_ROOT})
ADD_LIBRARY(gtest STATIC ${GTEST_ROOT}/src/gtest-all.cc )
TARGET_LINK_LIBRARIES(gtest ${CMAKE_THREAD_LIBS_INIT})

IF (USE_SOLUTION_FOLDERS)
	SET_TARGET_PROPERTIES(gtest PROPERTIES FOLDER "Tests" )
ENDIF(USE_SOLUTION_FOLDERS)

# Fix for MSVC11
IF(MSVC11)
  ADD_DEFINITIONS("-D_VARIADIC_MAX=10")
ENDIF()

# Copied from CMake
# Thanks to Daniel Blezek <blezek@gmail.com> for the GTEST_ADD_TESTS code
function(GTEST_ADD_TESTS executable extra_args)
    if(NOT ARGN)
        message(FATAL_ERROR "Missing ARGN: Read the documentation for GTEST_ADD_TESTS")
    endif()
    foreach(source ${ARGN})
        file(READ "${source}" contents)
        string(REGEX MATCHALL "TEST_?F?\\(([A-Za-z_0-9 ,]+)\\)" found_tests ${contents})
        foreach(hit ${found_tests})
            string(REGEX REPLACE ".*\\( *([A-Za-z_0-9]+), *([A-Za-z_0-9]+) *\\).*" "\\1.\\2" test_name ${hit})
            add_test(NAME ${test_name} COMMAND ${executable} --gtest_filter=${test_name} ${extra_args})
        endforeach()
    endforeach()
endfunction()

MACRO(ADD_OCE_TEST test_name libs)
  FILE(GLOB TEST_SOURCES *.cpp)
  SET(SOURCE_FILES ${TEST_SOURCES})
  ADD_EXECUTABLE(${test_name} ${SOURCE_FILES})
 
  IF (USE_SOLUTION_FOLDERS)
		SET_TARGET_PROPERTIES(${test_name} PROPERTIES FOLDER "Tests" )
  ENDIF(USE_SOLUTION_FOLDERS)
  
  SET(TEST_DEPENDS_INCLUDE_DIRECTORIES)
  FOREACH(LIB ${libs})
     TARGET_LINK_LIBRARIES(${test_name} ${LIB})
     SET(TEST_DEPENDS_INCLUDE_DIRECTORIES ${TEST_DEPENDS_INCLUDE_DIRECTORIES} ${${PROJECT_NAME}_${LIB}_INCLUDE_DIRECTORIES})
  ENDFOREACH(LIB ${libs})
  IF(TEST_DEPENDS_INCLUDE_DIRECTORIES)
     LIST(REMOVE_DUPLICATES TEST_DEPENDS_INCLUDE_DIRECTORIES)
     INCLUDE_DIRECTORIES(${TEST_DEPENDS_INCLUDE_DIRECTORIES})
  ENDIF(TEST_DEPENDS_INCLUDE_DIRECTORIES)
  
  IF (${PROJECT_NAME}_COVERAGE)
    TARGET_LINK_LIBRARIES(${test_name} gcov gtest)
  ELSE (${PROJECT_NAME}_COVERAGE)
    TARGET_LINK_LIBRARIES(${test_name} gtest)
  ENDIF (${PROJECT_NAME}_COVERAGE)
  GTEST_ADD_TESTS(${test_name} "" ${SOURCE_FILES})
ENDMACRO(ADD_OCE_TEST test_name libs)

FILE(GLOB TEST_DIRECTORIES ./*_test gtest_sandbox)
SUBDIRS(${TEST_DIRECTORIES})

