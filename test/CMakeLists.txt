SET(GTEST_ROOT /usr/local/lib)
FIND_PACKAGE(GTest)

SUBDIRS(gtest_sandbox gp_test BRepPrimAPI_test)
