SET(TOOLKIT TKTopTest)

SET(TOOLKIT_MODULES
	TestTopOpeDraw
	TestTopOpeTools
	TestTopOpe
	BRepTest
	GeometryTest
	HLRTest
	MeshTest
	GeomliteTest
	DrawFairCurve
	BOPTest
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKBool
	TKGeomAlgo
	TKMesh
	TKG3d
	TKGeomBase
	TKFeat
	TKTopAlgo
	TKBO
	TKMath
	TKG2d
	TKOffset
	TKService
	TKV3d
	TKHLR
	TKBRep
	TKFillet
	TKDraw
	TKPrim
	TKV2d
)

SET(TOOLKIT_IS_PRIVATE TRUE)

INCLUDE(../BuildToolkit.cmake)

