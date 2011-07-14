set(TOOLKIT TKVoxel)

set(TOOLKIT_MODULES
	Voxel
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKV3d
	TKMath
	TKService
	TKGeomBase
	TKG2d
	TKTopAlgo
	TKG3d
	TKMesh
)

set(TOOLKIT_LIBS ${OPENGL_LIBRARIES})
set(TOOLKIT_INCLUDE_DIRECTORIES ${OPENGL_INCLUDE_DIR})

include(../BuildToolkit.cmake)

