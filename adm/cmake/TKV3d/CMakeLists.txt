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
	TKBRep
	TKMath
	TKernel
	TKService
	TKTopAlgo
	TKG2d
	TKG3d
	TKGeomBase
	TKMesh
	TKGeomAlgo
	TKHLR
)
SET(TOOLKIT_LIBS ${CSF_user32_LIB} ${CSF_gdi32_LIB})

INCLUDE(../BuildToolkit.cmake)

