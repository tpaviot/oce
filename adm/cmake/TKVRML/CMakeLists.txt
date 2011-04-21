SET(TOOLKIT TKVRML)

SET(TOOLKIT_MODULES
	VrmlConverter
	VrmlAPI
	Vrml
	VrmlData
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKG3d
	TKTopAlgo
	TKMath
	TKBRep
	TKMesh
	TKG2d
	TKHLR
	TKGeomBase
	TKPrim
	TKGeomAlgo
	TKService
	TKV3d
)

INCLUDE(../OccBuildKit.cmake)

