SET(TOOLKIT TKStdLSchema)

SET(TOOLKIT_MODULES
	StdLSchema
	StdLDrivers
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKPLCAF
	TKLCAF
	PTKernel
	TKCDF
	TKShapeSchema
)

INCLUDE(../OccBuildKit.cmake)

