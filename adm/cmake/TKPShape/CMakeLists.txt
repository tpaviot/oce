SET(TOOLKIT TKPShape)

SET(TOOLKIT_MODULES
	PBRep
	PTopoDS
	PGeom
	PGeom2d
	PPoly
	PColgp
	PTopLoc
	PColPGeom
	PColPGeom2d
	MgtBRep
	MgtGeom
	MgtGeom2d
	MgtPoly
	MgtTopLoc
	MgtTopoDS
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKG3d
	PTKernel
	TKBRep
)

INCLUDE(../BuildToolkit.cmake)

