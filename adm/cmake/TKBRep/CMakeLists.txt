set(TOOLKIT TKBRep)

set(TOOLKIT_MODULES
	TopoDS
	TopExp
	TopTools
	BRep
	BRepLProp
	BRepAdaptor
	BRepTools
)
set(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKG3d
	TKGeomBase
)

include(../BuildToolkit.cmake)

