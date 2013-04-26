SET(TOOLKIT TKOffset)

SET(TOOLKIT_MODULES
	BRepOffsetAPI
	Draft
	BRepOffset
	BiTgte
)
SET(TOOLKIT_DEPENDS
	TKFillet
	TKBRep
	TKTopAlgo
	TKMath
	TKernel
	TKGeomBase
	TKG2d
	TKG3d
	TKGeomAlgo
	TKShHealing
	TKBO
	TKPrim
	TKBool
)

INCLUDE(../BuildToolkit.cmake)

