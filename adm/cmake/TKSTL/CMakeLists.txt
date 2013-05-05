SET(TOOLKIT TKSTL)

SET(TOOLKIT_MODULES
	StlMesh
	StlAPI
	StlTransfer
	RWStl
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKMath
	TKBRep
	TKG2d
	TKG3d
	TKMesh
	TKTopAlgo
)

INCLUDE(../BuildToolkit.cmake)

