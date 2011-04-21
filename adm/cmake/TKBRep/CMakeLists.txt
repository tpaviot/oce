SET(TOOLKIT TKBRep)

SET(TOOLKIT_MODULES
	TopoDS
	TopExp
	TopTools
	BRep
	BRepLProp
	BRepAdaptor
	BRepTools
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKGeomBase
	TKMath
	TKG2d
	TKG3d
)

INCLUDE(../OccBuildKit.cmake)

