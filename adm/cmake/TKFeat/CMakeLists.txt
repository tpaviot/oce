set(TOOLKIT TKFeat)

set(TOOLKIT_MODULES
	LocOpe
	BRepFeat
)
set(TOOLKIT_DEPENDS
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

include(../BuildToolkit.cmake)

