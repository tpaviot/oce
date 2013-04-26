SET(TOOLKIT TKBO)

SET(TOOLKIT_MODULES
	IntTools
	BRepAlgoAPI
	BOPCol
	BOPInt
	BOPDS
	BOPAlgo
	BOPTools
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKTopAlgo
	TKMath
	TKernel
	TKG2d
	TKG3d
	TKGeomAlgo
	TKGeomBase
)

INCLUDE(../BuildToolkit.cmake)

