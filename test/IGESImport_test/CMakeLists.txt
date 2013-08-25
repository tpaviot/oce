if (OCE_DATAEXCHANGE)
    set(iges_file_1 ${CMAKE_SOURCE_DIR}/test/data/IGES/hammer.igs)

    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/IGESImport_test_config.h.cmake ${CMAKE_BINARY_DIR}/test_inc/IGESImport_test_config.h )
    include_directories(${CMAKE_BINARY_DIR}/test_inc)

    add_oce_test(IGESImport_test "TKernel;TKIGES")
endif (OCE_DATAEXCHANGE)
