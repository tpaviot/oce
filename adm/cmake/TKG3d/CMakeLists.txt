SET(TOOLKIT TKG3d)

SET(TOOLKIT_MODULES
	Geom
	TColGeom
	GeomAdaptor
	AdvApprox
	GeomLProp
	Adaptor3d
	LProp3d
	TopAbs
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
)

INCLUDE(../BuildToolkit.cmake)

