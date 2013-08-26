set(TOOLKIT TKPLCAF)

set(TOOLKIT_MODULES
	PDF
	PDataStd
	PFunction
	PDocStd
	MDF
	MDataStd
	MFunction
	MDocStd
)
set(TOOLKIT_DEPENDS
	TKCDF
	PTKernel
	TKernel
	TKLCAF
)

include(../BuildToolkit.cmake)

