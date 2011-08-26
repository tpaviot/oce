#
# The OCE unittest framework use GoogleTest 1.6.0 (aka GTest)
# The GTest source code is available in the /test/gtest-1.6.0 folder
#
SET(GTEST_ROOT ./gtest-1.6.0)

FIND_PACKAGE(GTest)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIR})

MACRO(ADD_OCE_TEST test_name libs)
  FILE(GLOB TEST_SOURCES *.cpp)
  SET(SOURCE_FILES ${TEST_SOURCES})
  ADD_EXECUTABLE(${test_name} ${SOURCE_FILES})
  
  FOREACH(LIB ${libs})
     TARGET_LINK_LIBRARIES(${test_name} ${LIB})
  ENDFOREACH(LIB ${libs})
  
  IF (${PROJECT_NAME}_COVERAGE)
    TARGET_LINK_LIBRARIES(${test_name} gcov ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
  ELSE (${PROJECT_NAME}_COVERAGE)
    TARGET_LINK_LIBRARIES(${test_name} ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY})
  ENDIF (${PROJECT_NAME}_COVERAGE)
  GTEST_ADD_TESTS(${test_name} "" ${SOURCE_FILES})
ENDMACRO(ADD_OCE_TEST test_name libs)

FILE(GLOB TEST_DIRECTORIES ./*_test gtest_sandbox)
SUBDIRS(${TEST_DIRECTORIES})

