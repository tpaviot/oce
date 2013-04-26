SET(TOOLKIT TKVRML)

SET(TOOLKIT_MODULES
	VrmlConverter
	VrmlAPI
	Vrml
	VrmlData
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKTopAlgo
	TKMath
	TKGeomBase
	TKernel
	TKPrim
	TKG2d
	TKG3d
	TKMesh
	TKHLR
	TKService
	TKGeomAlgo
	TKV3d
)

INCLUDE(../BuildToolkit.cmake)

