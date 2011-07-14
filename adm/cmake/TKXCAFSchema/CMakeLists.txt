set(TOOLKIT TKXCAFSchema)

set(TOOLKIT_MODULES
	MXCAFDoc
	PXCAFDoc
	XCAFDrivers
	XCAFSchema
)
set(TOOLKIT_DEPENDS
	TKPLCAF
	TKernel
	PTKernel
	TKMath
	TKPShape
	TKCDF
	TKShapeSchema
	TKLCAF
	TKPCAF
	TKXCAF
	TKStdLSchema
	TKStdSchema
)

include(../BuildToolkit.cmake)

