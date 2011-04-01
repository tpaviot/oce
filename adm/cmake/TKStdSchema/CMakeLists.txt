SET(TOOLKIT TKStdSchema)

SET(TOOLKIT_MODULES
	StdSchema
	StdDrivers
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKPCAF
	TKernel
	TKLCAF
	TKCAF
	TKPLCAF
	TKPShape
	PTKernel
	TKG2d
	TKG3d
	TKCDF
	TKShapeSchema
	TKStdLSchema
)

INCLUDE(../OccBuildKit.cmake)

