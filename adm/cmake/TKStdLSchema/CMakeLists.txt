set(TOOLKIT TKStdLSchema)

set(TOOLKIT_MODULES
	StdLSchema
	StdLDrivers
)
set(TOOLKIT_DEPENDS
	TKCDF
	PTKernel
	TKernel
	TKShapeSchema
	TKLCAF
	TKPLCAF
)

include(../BuildToolkit.cmake)

