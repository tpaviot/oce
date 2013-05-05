SET(TOOLKIT TKFeat)

SET(TOOLKIT_MODULES
	LocOpe
	BRepFeat
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKTopAlgo
	TKGeomAlgo
	TKMath
	TKernel
	TKGeomBase
	TKPrim
	TKG2d
	TKBO
	TKG3d
	TKBool
)

INCLUDE(../BuildToolkit.cmake)

