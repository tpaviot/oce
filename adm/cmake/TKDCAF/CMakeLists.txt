set(TOOLKIT TKDCAF)

set(TOOLKIT_MODULES
	DDF
	DDocStd
	DNaming
	DDataStd
	DPrsStd
	DrawDim
)
set(TOOLKIT_DEPENDS TKCAF
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

set(TOOLKIT_IS_PRIVATE TRUE)

include(../BuildToolkit.cmake)

