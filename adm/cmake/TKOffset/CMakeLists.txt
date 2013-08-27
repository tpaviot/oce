set(TOOLKIT TKOffset)

set(TOOLKIT_MODULES
	BRepOffsetAPI
	Draft
	BRepOffset
	BiTgte
)
set(TOOLKIT_DEPENDS
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

include(../BuildToolkit.cmake)

