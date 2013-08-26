set(TOOLKIT TKVRML)

set(TOOLKIT_MODULES
	VrmlConverter
	VrmlAPI
	Vrml
	VrmlData
)
set(TOOLKIT_DEPENDS
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

include(../BuildToolkit.cmake)

