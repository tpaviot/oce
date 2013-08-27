set(TOOLKIT TKBO)

set(TOOLKIT_MODULES
	IntTools
	BRepAlgoAPI
	BOPCol
	BOPInt
	BOPDS
	BOPAlgo
	BOPTools
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKTopAlgo
	TKMath
	TKernel
	TKG2d
	TKG3d
	TKGeomAlgo
	TKGeomBase
)

include(../BuildToolkit.cmake)

