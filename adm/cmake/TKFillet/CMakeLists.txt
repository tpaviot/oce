set(TOOLKIT TKFillet)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKGeomBase
	TKGeomAlgo
	TKG2d
	TKTopAlgo
	TKG3d
	TKBool
	TKShHealing
)

include(../BuildToolkit.cmake)

