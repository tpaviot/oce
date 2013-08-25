if (OCE_DATAEXCHANGE)
    set(brep_file_1 ${CMAKE_SOURCE_DIR}/test/data/brep/15_cylinder_head.brep)
    set(brep_file_2 ${CMAKE_SOURCE_DIR}/test/data/brep/27_leverarm.brep)
    set(brep_file_3 ${CMAKE_SOURCE_DIR}/test/data/brep/29_misc1.brep)
    set(brep_file_4 ${CMAKE_SOURCE_DIR}/test/data/brep/31_misc2.brep)

    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/BRepImport_test_config.h.cmake ${CMAKE_BINARY_DIR}/test_inc/BRepImport_test_config.h )
    include_directories(${CMAKE_BINARY_DIR}/test_inc)

    add_oce_test(BRepImport_test "TKernel;TKSTEP")
endif (OCE_DATAEXCHANGE)
