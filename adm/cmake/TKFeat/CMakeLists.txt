SET(TOOLKIT TKFeat)

SET(TOOLKIT_MODULES
	LocOpe
	BRepFeat
)
SET(TOOLKIT_DEPENDS
	TKGeomAlgo
	TKernel
	TKBool
	TKG3d
	TKMath
	TKBO
	TKG2d
	TKTopAlgo
	TKGeomBase
	TKBRep
	TKPrim
)

INCLUDE(../OccBuildKit.cmake)

