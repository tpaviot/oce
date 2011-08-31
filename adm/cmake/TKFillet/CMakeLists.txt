SET(TOOLKIT TKFillet)

SET(TOOLKIT_MODULES
	ChFiDS
	ChFi2d
	ChFi3d
	ChFiKPart
	Blend
	BRepBlend
	BlendFunc
	BRepFilletAPI
	FilletSurf
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKGeomAlgo
	TKBool
	TKG3d
	TKGeomBase
	TKMath
	TKG2d
	TKTopAlgo
	TKBRep
)

INCLUDE(../BuildToolkit.cmake)

