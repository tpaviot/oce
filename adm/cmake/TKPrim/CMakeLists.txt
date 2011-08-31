SET(TOOLKIT TKPrim)

SET(TOOLKIT_MODULES
	BRepPrim
	Primitives
	BRepSweep
	Sweep
	BRepPrimAPI
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKBRep
	TKGeomBase
	TKG3d
	TKTopAlgo
)

INCLUDE(../BuildToolkit.cmake)

