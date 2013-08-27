set(TOOLKIT TKTopTest)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
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

set(TOOLKIT_IS_PRIVATE TRUE)

include(../BuildToolkit.cmake)

