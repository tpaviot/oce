SET(TOOLKIT TKGeomBase)

SET(TOOLKIT_MODULES
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
SET(TOOLKIT_DEPENDS
	TKernel
	TKG3d
	TKMath
	TKG2d
)

INCLUDE(../OccBuildKit.cmake)

