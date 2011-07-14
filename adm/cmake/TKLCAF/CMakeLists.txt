set(TOOLKIT TKLCAF)

set(TOOLKIT_MODULES
	TDF
	TDataStd
	TFunction
	TDocStd
	AppStdL
)
set(TOOLKIT_DEPENDS
	TKCDF
	TKernel
)

include(../BuildToolkit.cmake)

