SET(TOOLKIT TKV3d)

SET(TOOLKIT_MODULES
	V3d
	Graphic3d
	Visual3d
	Select3D
	Prs3d
	StdPrs
	SelectMgr
	PrsMgr
	AIS
	DsgPrs
	StdSelect
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKG3d
	TKTopAlgo
	TKGeomBase
	TKService
	TKMath
	TKMesh
	TKGeomAlgo
	TKHLR
	TKBRep
	TKG2d
	TKV2d
)
SET(TOOLKIT_LIBS ${OPENGL_LIBRARIES} ${CSF_user32_LIB} ${CSF_gdi32_LIB})

INCLUDE(../OccBuildKit.cmake)

