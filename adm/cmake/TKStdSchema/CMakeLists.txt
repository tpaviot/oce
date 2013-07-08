SET(TOOLKIT TKStdSchema)

SET(TOOLKIT_MODULES
	StdSchema
	StdDrivers
)
SET(TOOLKIT_DEPENDS
	TKCDF
	PTKernel
	TKPLCAF
	TKernel
	TKCAF
	TKShapeSchema
	TKLCAF
	TKStdLSchema
	TKG3d
	TKPShape
	TKMath
	TKG2d
	TKPCAF
)

INCLUDE(../BuildToolkit.cmake)

