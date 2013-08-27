set(TOOLKIT TKSTL)

set(TOOLKIT_MODULES
	StlMesh
	StlAPI
	StlTransfer
	RWStl
)
set(TOOLKIT_DEPENDS
	TKernel
	TKMath
	TKBRep
	TKG2d
	TKG3d
	TKMesh
	TKTopAlgo
)

include(../BuildToolkit.cmake)

