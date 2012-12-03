IF (${PROJECT_NAME}_OCAF)
    # This test will dlopen FWOSPlugin, we link against it to ensure that
    # the library from the build tree is used.
    ADD_OCE_TEST(TDataXtd_test "TKCAF;TKXCAF;FWOSPlugin")
    FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../src/StdResource" BuildPluginDir)
    # Semi-colon is a delimiter in SET_TESTS_PROPERTIES and have to be escaped
    STRING(REPLACE ";" "\\;" BuildPluginDir "${BuildPluginDir}")
    SET_TESTS_PROPERTIES(TDataXtdTestSuite.testPattern PROPERTIES ENVIRONMENT "CSF_PluginDefaults=${BuildPluginDir};CSF_PluginUserDefaults=${BuildPluginDir}")
ENDIF (${PROJECT_NAME}_OCAF)
