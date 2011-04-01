SET(TOOLKIT TKVoxel)

SET(TOOLKIT_MODULES
	Voxel
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKService
	TKMesh
	TKV3d
	TKG2d
	TKV2d
	TKBRep
	TKGeomBase
	TKG3d
	TKTopAlgo
)

INCLUDE(../OccBuildKit.cmake)

