SET(TOOLKIT TKBO)

SET(TOOLKIT_MODULES
	BOPTColStd
	BOPTools
	BOP
	BooleanOperations
	IntTools
	BRepAlgoAPI
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKGeomBase
	TKG3d
	TKTopAlgo
	TKMath
	TKBRep
	TKG2d
	TKGeomAlgo
)

INCLUDE(../BuildToolkit.cmake)

