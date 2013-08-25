set(TOOLKIT FWOSPlugin)

set(TOOLKIT_MODULES
	FWOSDriver
)
set(TOOLKIT_DEPENDS
	TKernel
	TKCDF
)

include(../BuildToolkit.cmake)

