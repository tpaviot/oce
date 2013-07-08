SET(TOOLKIT TKMath)

SET(TOOLKIT_MODULES
	math
	ElCLib
	ElSLib
	BSplCLib
	BSplSLib
	PLib
	Precision
	GeomAbs
	Poly
	CSLib
	Convert
	Bnd
	gp
	TColgp
	TopLoc
)
SET(TOOLKIT_DEPENDS
	TKernel
)

INCLUDE(../BuildToolkit.cmake)

