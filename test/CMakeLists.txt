#
# The OCE unittest framework use GoogleTest 1.6.0 (aka GTest)
# The GTest source code is available in the /test/gtest-1.6.0 folder
#
set(GTEST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/gtest-1.6.0)

include_directories(${GTEST_ROOT}/include ${GTEST_ROOT})
add_library(gtest STATIC ${GTEST_ROOT}/src/gtest-all.cc )
target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})

if (USE_SOLUTION_FOLDERS)
	set_target_properties(gtest PROPERTIES FOLDER "Tests" )
endif(USE_SOLUTION_FOLDERS)

# Fix for MSVC11
if(MSVC11)
	add_definitions("-D_VARIADIC_MAX=10")
endif()

# Copied from CMake
# Thanks to Daniel Blezek <blezek@gmail.com> for the gtest_add_tests code
function(gtest_add_tests executable extra_args)
	if(NOT ARGN)
		message(FATAL_ERROR "Missing ARGN: Read the documentation for gtest_add_tests")
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

macro(add_oce_test test_name libs)
	file(GLOB TEST_SOURCES *.cpp)
	set(SOURCE_FILES ${TEST_SOURCES})
	add_executable(${test_name} ${SOURCE_FILES})
	
	if (USE_SOLUTION_FOLDERS)
		set_target_properties(${test_name} PROPERTIES FOLDER "Tests" )
	endif(USE_SOLUTION_FOLDERS)
	
	set(TEST_DEPENDS_INCLUDE_DIRECTORIES)
	foreach(LIB ${libs})
		target_link_libraries(${test_name} ${LIB})
		set(TEST_DEPENDS_INCLUDE_DIRECTORIES ${TEST_DEPENDS_INCLUDE_DIRECTORIES} ${OCE_${LIB}_INCLUDE_DIRECTORIES})
	endforeach(LIB ${libs})
	if(TEST_DEPENDS_INCLUDE_DIRECTORIES)
		list(REMOVE_DUPLICATES TEST_DEPENDS_INCLUDE_DIRECTORIES)
		include_directories(${TEST_DEPENDS_INCLUDE_DIRECTORIES})
	endif(TEST_DEPENDS_INCLUDE_DIRECTORIES)
	
	if (OCE_COVERAGE)
		target_link_libraries(${test_name} gcov gtest)
	else (OCE_COVERAGE)
		target_link_libraries(${test_name} gtest)
	endif (OCE_COVERAGE)
	gtest_add_tests(${test_name} "" ${SOURCE_FILES})
endmacro(ADD_OCE_TEST test_name libs)

file(GLOB TEST_DIRECTORIES ./*_test gtest_sandbox)
subdirs(${TEST_DIRECTORIES})

