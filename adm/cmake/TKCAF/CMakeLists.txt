SET(TOOLKIT TKCAF)

SET(TOOLKIT_MODULES
	TDataXtd
	TNaming
	TPrsStd
	AppStd
)
SET(TOOLKIT_DEPENDS
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

INCLUDE(../BuildToolkit.cmake)

