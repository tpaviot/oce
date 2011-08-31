SET(TOOLKIT TKTopAlgo)

SET(TOOLKIT_MODULES
	IntCurvesFace
	MAT
	MAT2d
	Bisector
	BRepMAT2d
	BRepCheck
	BRepBndLib
	BRepExtrema
	BRepClass
	BRepClass3d
	BRepLib
	BRepGProp
	BRepIntCurveSurface
	BRepTopAdaptor
	BRepBuilderAPI
	BRepApprox
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKGeomBase
	TKMath
	TKGeomAlgo
	TKG2d
	TKG3d
	TKBRep
)

INCLUDE(../BuildToolkit.cmake)

