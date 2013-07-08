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
	TKBRep
	TKernel
	TKMath
	TKTopAlgo
	TKShHealing
	TKG2d
	TKG3d
	TKGeomBase
	TKGeomAlgo
	TKPrim
	TKBool
	TKOffset
	TKXSBase
)

INCLUDE(../BuildToolkit.cmake)

