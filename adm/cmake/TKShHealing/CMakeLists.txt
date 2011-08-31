SET(TOOLKIT TKShHealing)

SET(TOOLKIT_MODULES
	ShapeBuild
	ShapeExtend
	ShapeConstruct
	ShapeCustom
	ShapeAnalysis
	ShapeFix
	ShapeUpgrade
	ShapeAlgo
	ShapeProcess
	ShapeProcessAPI
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKGeomBase
	TKMath
	TKG2d
	TKG3d
	TKTopAlgo
	TKBRep
	TKGeomAlgo
)
SET(TOOLKIT_LIBS ${CSF_wsock32_LIB})

INCLUDE(../BuildToolkit.cmake)

