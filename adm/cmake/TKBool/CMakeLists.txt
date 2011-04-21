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
	TKernel
	TKGeomAlgo
	TKG3d
	TKGeomBase
	TKTopAlgo
	TKMath
	TKBO
	TKG2d
	TKShHealing
	TKBRep
	TKPrim
)

INCLUDE(../OccBuildKit.cmake)

