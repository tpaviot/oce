SET(TOOLKIT TKG2d)

SET(TOOLKIT_MODULES
	Geom2d
	LProp
	TColGeom2d
	Adaptor2d
	Geom2dLProp
	Geom2dAdaptor
	TopAbs
	GProp
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKMath
)

INCLUDE(../BuildToolkit.cmake)

