function(GET_INVALID_CLANG_HEADERS INVALID_CLANG_HEADERS)
  #Execute the clang compiler in verbose mode to find the location of inttypes.h and stdint.h
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    execute_process(COMMAND ${CMAKE_C_COMPILER} -E -x c - -v
      INPUT_FILE /dev/null
      OUTPUT_FILE /dev/null
      ERROR_VARIABLE clang_c_raw_verbose)
    string(REGEX MATCHALL "\n /[^\n]*" clang_c_search_dirs "${clang_c_raw_verbose}")
    string(REPLACE "\n " "" clang_c_search_dirs "${clang_c_search_dirs}")
    find_file(inttypes_c_location "inttypes.h" PATHS ${clang_c_search_dirs} PATH_SUFFIXES include NO_DEFAULT_PATH)
    find_file(stdint_c_location "stdint.h" PATHS ${clang_c_search_dirs} PATH_SUFFIXES include NO_DEFAULT_PATH)
    set(${INVALID_CLANG_HEADERS} ${${INVALID_CLANG_HEADERS}} ${inttypes_c_location} ${stdint_c_location} PARENT_SCOPE)
  endif()

  if("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    execute_process(COMMAND ${CMAKE_C_COMPILER} -E -x c++ - -v
      INPUT_FILE /dev/null
      OUTPUT_FILE /dev/null
      ERROR_VARIABLE clang_cxx_raw_verbose)
    string(REGEX MATCHALL "\n /[^\n]*" clang_cxx_search_dirs "${clang_cxx_raw_verbose}")
    string(REPLACE "\n " "" clang_cxx_search_dirs "${clang_cxx_search_dirs}")
    find_file(inttypes_cxx_location "inttypes.h" PATHS ${clang_cxx_search_dirs} PATH_SUFFIXES include NO_DEFAULT_PATH)
    find_file(stdint_cxx_location "stdint.h" PATHS ${clang_cxx_search_dirs} PATH_SUFFIXES include NO_DEFAULT_PATH)
  endif()

  set(${INVALID_CLANG_HEADERS} ${inttypes_c_location} ${inttypes_cxx_location} ${stdint_cxx_location} ${stdint_cxx_location} PARENT_SCOPE)
endfunction()
