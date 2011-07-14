set(TOOLKIT TKXMesh)

set(TOOLKIT_MODULES
	XBRepMesh
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKMath
	TKernel
	TKG2d
	TKMesh
)

include(../BuildToolkit.cmake)

