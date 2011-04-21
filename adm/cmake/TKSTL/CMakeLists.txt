SET(TOOLKIT TKSTL)

SET(TOOLKIT_MODULES
	StlMesh
	StlAPI
	StlTransfer
	RWStl
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKMesh
	TKBRep
	TKG3d
	TKTopAlgo
)

INCLUDE(../OccBuildKit.cmake)

