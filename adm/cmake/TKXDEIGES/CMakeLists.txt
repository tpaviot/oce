set(TOOLKIT TKXDEIGES)

set(TOOLKIT_MODULES
	IGESCAFControl
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKXSBase
	TKCDF
	TKLCAF
	TKG2d
	TKXCAF
	TKIGES
)

include(../BuildToolkit.cmake)

