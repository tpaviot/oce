#
# The OCE unittest framework use GoogleTest 1.6.0 (aka GTest)
# The GTest source code is available in the /test/gtest-1.6.0 folder
#
SET(GTEST_ROOT ./gtest-1.6.0)
FIND_PACKAGE(GTest)

FILE(GLOB TEST_DIRECTORIES ./*_test gtest_sandbox)
SUBDIRS(${TEST_DIRECTORIES})
