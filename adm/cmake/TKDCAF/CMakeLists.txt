SET(TOOLKIT TKDCAF)

SET(TOOLKIT_MODULES
	DDF
	DDocStd
	DNaming
	DDataStd
	DPrsStd
	DrawDim
)
SET(TOOLKIT_DEPENDS TKCAF
	TKGeomBase
	TKBRep
	TKGeomAlgo
	TKernel
	TKMath
	TKG2d
	TKG3d
	TKDraw
	TKCDF
	TKV3d
	TKNIS
	TKService
	TKLCAF
	TKFillet
	TKTopAlgo
	TKPrim
	TKBool
	TKBO
	TKCAF
	TKViewerTest
)

SET(TOOLKIT_IS_PRIVATE TRUE)

INCLUDE(../BuildToolkit.cmake)

