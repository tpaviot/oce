SET(TOOLKIT TKShapeSchema)

SET(TOOLKIT_MODULES
	ShapeSchema
	PCDMShape
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKPShape
	TKernel
	PTKernel
	TKG2d
	TKCDF
)

INCLUDE(../BuildToolkit.cmake)

