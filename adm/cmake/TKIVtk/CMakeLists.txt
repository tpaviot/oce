set(TOOLKIT TKIVtk)

set(TOOLKIT_MODULES
	IVtk
	IVtkOCC
	IVtkVTK
	IVtkTools
)
set(TOOLKIT_DEPENDS
	TKernel
	TKBRep
	TKG2d
	TKG3d
	TKGeomAlgo
	TKGeomBase
	TKMath
	TKMesh
	TKService
	TKTopAlgo
	TKV3d
)

set(TOOLKIT_INCLUDE_DIRECTORIES ${VTK_INCLUDE_DIRS})
set(TOOLKIT_LIBS ${VTK_LIBRARIES})

include(../BuildToolkit.cmake)

