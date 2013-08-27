set(TOOLKIT TKCDF)

set(TOOLKIT_MODULES
	CDM
	PCDM
	CDF
	UTL
	LDOM
)
set(TOOLKIT_DEPENDS
	TKernel
)

include(../BuildToolkit.cmake)

