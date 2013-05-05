SET(TOOLKIT TKBool)

SET(TOOLKIT_MODULES
	TopOpeBRep
	TopOpeBRepDS
	TopOpeBRepBuild
	TopOpeBRepTool
	BRepAlgo
	BRepFill
	BRepProj
)
SET(TOOLKIT_DEPENDS
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

INCLUDE(../BuildToolkit.cmake)

