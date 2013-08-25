if (OCE_OCAF)
    # This test will dlopen FWOSPlugin and TKBin, we link against them to ensure that
    # libraries from the build tree are used.
    add_oce_test(OCAFExport_test "TKCAF;FWOSPlugin;TKBin")
    file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../src/StdResource" BuildPluginDir)
    # Semi-colon is a delimiter in SET_TESTS_PROPERTIES and have to be escaped
    string(REPLACE ";" "\\;" BuildPluginDir "${BuildPluginDir}")
    set_tests_properties(OCAFExportTestSuite.testExportAscii PROPERTIES ENVIRONMENT "CSF_PluginDefaults=${BuildPluginDir};CSF_StandardDefaults=${BuildPluginDir}")
    set_tests_properties(OCAFExportTestSuite.testExportNonAscii PROPERTIES ENVIRONMENT "CSF_PluginDefaults=${BuildPluginDir};CSF_StandardDefaults=${BuildPluginDir}")
endif (OCE_OCAF)
