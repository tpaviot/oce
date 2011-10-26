SET(step_file_ap203_1 ${CMAKE_SOURCE_DIR}/test/data/STEP/as1-tu-203.stp)
SET(step_file_ap203_2 ${CMAKE_SOURCE_DIR}/test/data/STEP/as1_pe_203.stp)
SET(step_file_ap214_1 ${CMAKE_SOURCE_DIR}/test/data/STEP/as1-oc-214.stp)
SET(step_file_ap214_2 ${CMAKE_SOURCE_DIR}/test/data/STEP/io1-cm-214.stp)
SET(step_file_ap214_3 ${CMAKE_SOURCE_DIR}/test/data/STEP/sg1-c5-214.stp)

CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/STEPImport_test_config.h.cmake ${CMAKE_CURRENT_SOURCE_DIR}/STEPImport_test_config.h )
ADD_OCE_TEST(STEPImport_test "TKernel;TKSTEP")
