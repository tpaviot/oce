set(TOOLKIT TKGeomBase)

set(TOOLKIT_MODULES
	ProjLib
	GeomProjLib
	GCPnts
	CPnts
	Approx
	AppParCurves
	FEmTool
	AppCont
	Extrema
	IntAna
	IntAna2d
	GeomConvert
	AdvApp2Var
	GeomLib
	Geom2dConvert
	Hermit
	BndLib
	AppDef
	GeomTools
	GC
	GCE2d
	gce
)
set(TOOLKIT_DEPENDS
	TKernel
	TKMath
	TKG2d
	TKG3d
)

include(../BuildToolkit.cmake)

