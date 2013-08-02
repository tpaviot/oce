IF (${PROJECT_NAME}_OCAF)
    # This test will dlopen FWOSPlugin and TKBin, we link against them to ensure that
    # libraries from the build tree are used.
    ADD_OCE_TEST(OCAFExport_test "TKCAF;FWOSPlugin;TKBin")
    FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../src/StdResource" BuildPluginDir)
    # Semi-colon is a delimiter in SET_TESTS_PROPERTIES and have to be escaped
    STRING(REPLACE ";" "\\;" BuildPluginDir "${BuildPluginDir}")
    SET_TESTS_PROPERTIES(OCAFExportTestSuite.testExportAscii PROPERTIES ENVIRONMENT "CSF_PluginDefaults=${BuildPluginDir};CSF_StandardDefaults=${BuildPluginDir}")
    SET_TESTS_PROPERTIES(OCAFExportTestSuite.testExportNonAscii PROPERTIES ENVIRONMENT "CSF_PluginDefaults=${BuildPluginDir};CSF_StandardDefaults=${BuildPluginDir}")
ENDIF (${PROJECT_NAME}_OCAF)
