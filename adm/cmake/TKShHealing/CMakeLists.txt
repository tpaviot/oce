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
	TKBRep
	TKernel
	TKMath
	TKG2d
	TKTopAlgo
	TKG3d
	TKGeomBase
	TKGeomAlgo
)
SET(TOOLKIT_LIBS ${CSF_wsock32_LIB})

INCLUDE(../BuildToolkit.cmake)

