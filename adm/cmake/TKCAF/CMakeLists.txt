set(TOOLKIT TKCAF)

set(TOOLKIT_MODULES
	TDataXtd
	TNaming
	TPrsStd
	AppStd
)
set(TOOLKIT_DEPENDS
	TKernel
	TKGeomBase
	TKBRep
	TKTopAlgo
	TKMath
	TKService
	TKG2d
	TKG3d
	TKCDF
	TKLCAF
	TKV3d
	TKBO
)

include(../BuildToolkit.cmake)

