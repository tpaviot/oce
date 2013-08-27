if (OCE_DATAEXCHANGE AND NOT OCE_DISABLE_X11)
	# This test will dlopen FWOSPlugin, we link against it to ensure that
	# the library from the build tree is used.
	add_oce_test(TDataXtd_test "TKCAF;TKXCAF;FWOSPlugin")
	file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../src/StdResource" BuildPluginDir)
	# Semi-colon is a delimiter in SET_TESTS_PROPERTIES and have to be escaped
	string(REPLACE ";" "\\;" BuildPluginDir "${BuildPluginDir}")
	set_tests_properties(TDataXtdTestSuite.testPattern PROPERTIES ENVIRONMENT "CSF_PluginDefaults=${BuildPluginDir};CSF_PluginUserDefaults=${BuildPluginDir}")
endif (OCE_DATAEXCHANGE AND NOT OCE_DISABLE_X11)
