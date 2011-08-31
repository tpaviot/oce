SET(TOOLKIT TKCAF)

SET(TOOLKIT_MODULES
	TDataXtd
	TNaming
	TPrsStd
	AppStd
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKLCAF
	TKG3d
	TKGeomBase
	TKV3d
	TKService
	TKMath
	TKCDF
	TKBRep
	TKG2d
	TKTopAlgo
	TKV2d
)

INCLUDE(../BuildToolkit.cmake)

