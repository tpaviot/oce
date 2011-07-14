set(TOOLKIT TKG3d)

set(TOOLKIT_MODULES
	Geom
	TColGeom
	GeomAdaptor
	AdvApprox
	GeomLProp
	Adaptor3d
	LProp3d
	TopAbs
)
set(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
)

include(../BuildToolkit.cmake)

