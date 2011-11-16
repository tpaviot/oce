SET(iges_file_1 ${CMAKE_SOURCE_DIR}/test/data/IGES/hammer.igs)

CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/IGESImport_test_config.h.cmake ${CMAKE_BINARY_DIR}/test_inc/IGESImport_test_config.h )
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/test_inc)

ADD_OCE_TEST(IGESImport_test "TKernel;TKIGES")
