SET(TOOLKIT TKIGES)

SET(TOOLKIT_MODULES
	IGESData
	IGESFile
	IGESBasic
	IGESGraph
	IGESGeom
	IGESDimen
	IGESDraw
	IGESSolid
	IGESDefs
	IGESAppli
	IGESConvGeom
	IGESSelect
	IGESToBRep
	GeomToIGES
	Geom2dToIGES
	BRepToIGES
	BRepToIGESBRep
	IGESControl
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKXSBase
	TKG3d
	TKMath
	TKOffset
	TKG2d
	TKGeomBase
	TKShHealing
	TKTopAlgo
	TKBRep
	TKGeomAlgo
	TKBool
	TKPrim
)

INCLUDE(../BuildToolkit.cmake)

