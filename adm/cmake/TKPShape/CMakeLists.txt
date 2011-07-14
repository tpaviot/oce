set(TOOLKIT TKPShape)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKG2d
	TKG3d
	PTKernel
	TKBRep
)

include(../BuildToolkit.cmake)

