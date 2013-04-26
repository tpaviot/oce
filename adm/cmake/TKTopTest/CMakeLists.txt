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
	TKBRep
	TKGeomAlgo
	TKTopAlgo
	TKernel
	TKMath
	TKBO
	TKG2d
	TKG3d
	TKDraw
	TKHLR
	TKGeomBase
	TKMesh
	TKService
	TKV3d
	TKFillet
	TKPrim
	TKBool
	TKOffset
	TKFeat
)

SET(TOOLKIT_IS_PRIVATE TRUE)

INCLUDE(../BuildToolkit.cmake)

