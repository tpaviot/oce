SET(TOOLKIT TKShapeSchema)

SET(TOOLKIT_MODULES
	ShapeSchema
	PCDMShape
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKG2d
	PTKernel
	TKMath
	TKCDF
	TKPShape
)

INCLUDE(../BuildToolkit.cmake)

