set(TOOLKIT PTKernel)

set(TOOLKIT_MODULES
	DBC
	PCollection
	PColStd
	PMMgt
	PShort
	PStandard
	PTColStd
	ObjMgt
)
set(TOOLKIT_DEPENDS
	TKernel
)

include(../BuildToolkit.cmake)

