SET(TOOLKIT PTKernel)

SET(TOOLKIT_MODULES
	DBC
	PCollection
	PColStd
	PMMgt
	PShort
	PStandard
	PTColStd
	ObjMgt
)
SET(TOOLKIT_DEPENDS
	TKernel
)

INCLUDE(../BuildToolkit.cmake)

