SET(TOOLKIT TKOffset)

SET(TOOLKIT_MODULES
	BRepOffsetAPI
	Draft
	BRepOffset
	BiTgte
)
SET(TOOLKIT_DEPENDS
	TKBool
	TKGeomAlgo
	TKernel
	TKGeomBase
	TKTopAlgo
	TKMath
	TKBO
	TKG2d
	TKG3d
	TKBRep
	TKShHealing
	TKFillet
	TKPrim
)

INCLUDE(../OccBuildKit.cmake)

