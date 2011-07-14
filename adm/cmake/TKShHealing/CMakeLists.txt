set(TOOLKIT TKShHealing)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKG2d
	TKTopAlgo
	TKG3d
	TKGeomBase
	TKGeomAlgo
)
set(TOOLKIT_LIBS ${CSF_wsock32_LIB})

include(../BuildToolkit.cmake)

