SET(TOOLKIT TKStdLSchema)

SET(TOOLKIT_MODULES
	StdLSchema
	StdLDrivers
)
SET(TOOLKIT_DEPENDS
	TKCDF
	PTKernel
	TKernel
	TKShapeSchema
	TKLCAF
	TKPLCAF
)

INCLUDE(../BuildToolkit.cmake)

