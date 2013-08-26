set(TOOLKIT TKG2d)

set(TOOLKIT_MODULES
	Geom2d
	LProp
	TColGeom2d
	Adaptor2d
	Geom2dLProp
	Geom2dAdaptor
	GProp
)
set(TOOLKIT_DEPENDS
	TKernel
	TKMath
)

include(../BuildToolkit.cmake)

