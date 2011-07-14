set(TOOLKIT TKMeshVS)

set(TOOLKIT_MODULES
	MeshVS
)
set(TOOLKIT_DEPENDS
	TKV3d
	TKMath
	TKService
	TKernel
	TKG3d
	TKG2d
)

include(../BuildToolkit.cmake)

