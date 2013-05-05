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
	TKMath
	TKernel
	TKG2d
	TKG3d
	TKGeomBase
)

INCLUDE(../BuildToolkit.cmake)

