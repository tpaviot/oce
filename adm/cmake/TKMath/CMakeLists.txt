set(TOOLKIT TKMath)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
	TKernel
)

include(../BuildToolkit.cmake)

