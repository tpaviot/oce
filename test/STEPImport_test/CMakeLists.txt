if (OCE_DATAEXCHANGE)
    set(step_file_ap203_1 ${CMAKE_SOURCE_DIR}/test/data/STEP/as1-tu-203.stp)
    set(step_file_ap203_2 ${CMAKE_SOURCE_DIR}/test/data/STEP/as1_pe_203.stp)
    set(step_file_ap214_1 ${CMAKE_SOURCE_DIR}/test/data/STEP/as1-oc-214.stp)
    set(step_file_ap214_2 ${CMAKE_SOURCE_DIR}/test/data/STEP/io1-cm-214.stp)
    set(step_file_ap214_3 ${CMAKE_SOURCE_DIR}/test/data/STEP/sg1-c5-214.stp)

    configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/STEPImport_test_config.h.cmake ${CMAKE_BINARY_DIR}/test_inc/STEPImport_test_config.h )
    include_directories(${CMAKE_BINARY_DIR}/test_inc)

    add_oce_test(STEPImport_test "TKernel;TKSTEP")
endif (OCE_DATAEXCHANGE)
