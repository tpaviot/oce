SET(TOOLKIT TKPrim)

SET(TOOLKIT_MODULES
	BRepPrim
	Primitives
	BRepSweep
	Sweep
	BRepPrimAPI
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKG2d
	TKGeomBase
	TKG3d
	TKTopAlgo
)

INCLUDE(../BuildToolkit.cmake)

