SET(GTEST_ROOT /usr/local/lib)

SET(GTEST_INCLUDE_DIRS /usr/local/include)
SET(GTEST_LIBRARY /usr/local/lib/libgtest.a)
SET(GTEST_MAIN_LIBRARY /usr/local/lib/libgtest_main.a)


ADD_DEFINITIONS(-g -Wall)
ADD_DEFINITIONS(--coverage)

SUBDIRS(gp_test gtest_tutorial)
