set(TOOLKIT TKShapeSchema)

set(TOOLKIT_MODULES
	ShapeSchema
	PCDMShape
)
set(TOOLKIT_DEPENDS
	TKernel
	TKG2d
	PTKernel
	TKMath
	TKCDF
	TKPShape
)

include(../BuildToolkit.cmake)

