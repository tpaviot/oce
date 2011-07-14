set(TOOLKIT TKPrim)

set(TOOLKIT_MODULES
	BRepPrim
	Primitives
	BRepSweep
	Sweep
	BRepPrimAPI
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKG2d
	TKGeomBase
	TKG3d
	TKTopAlgo
)

include(../BuildToolkit.cmake)

