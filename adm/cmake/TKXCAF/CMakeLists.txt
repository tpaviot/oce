set(TOOLKIT TKXCAF)

set(TOOLKIT_MODULES
	XCAFApp
	XCAFDoc
	XCAFPrs
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKService
	TKG2d
	TKTopAlgo
	TKV3d
	TKCDF
	TKLCAF
	TKG3d
	TKCAF
)

include(../BuildToolkit.cmake)

