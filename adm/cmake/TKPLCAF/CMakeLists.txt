SET(TOOLKIT TKPLCAF)

SET(TOOLKIT_MODULES
	PDF
	PDataStd
	PFunction
	PDocStd
	MDF
	MDataStd
	MFunction
	MDocStd
)
SET(TOOLKIT_DEPENDS
	TKCDF
	PTKernel
	TKernel
	TKLCAF
)

INCLUDE(../BuildToolkit.cmake)

