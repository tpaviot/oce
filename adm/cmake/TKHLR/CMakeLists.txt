set(TOOLKIT TKHLR)

set(TOOLKIT_MODULES
	HLRTopoBRep
	HLRBRep
	HLRAlgo
	Intrv
	TopBas
	TopCnx
	Contap
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKGeomBase
	TKG2d
	TKG3d
	TKGeomAlgo
	TKTopAlgo
)

include(../BuildToolkit.cmake)

