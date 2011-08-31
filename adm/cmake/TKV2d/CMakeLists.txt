SET(TOOLKIT TKV2d)

SET(TOOLKIT_MODULES
	V2d
	Graphic2d
	Select2D
	Prs2d
	AIS2D
	GGraphic2d
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKService
	TKG2d
	TKG3d
	TKTopAlgo
	TKMath
	TKBRep
	TKGeomBase
	TKHLR
	TKGeomAlgo
)

INCLUDE(../BuildToolkit.cmake)

