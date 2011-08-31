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
	TKG2d
	TKernel
	PTKernel
	TKBRep
	TKG3d
)

INCLUDE(../BuildToolkit.cmake)

