set(TOOLKIT TKBool)

set(TOOLKIT_MODULES
	TopOpeBRep
	TopOpeBRepDS
	TopOpeBRepBuild
	TopOpeBRepTool
	BRepAlgo
	BRepFill
	BRepProj
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKTopAlgo
	TKMath
	TKernel
	TKPrim
	TKG2d
	TKG3d
	TKShHealing
	TKGeomBase
	TKGeomAlgo
	TKBO
)

include(../BuildToolkit.cmake)

