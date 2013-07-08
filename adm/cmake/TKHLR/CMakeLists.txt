SET(TOOLKIT TKHLR)

SET(TOOLKIT_MODULES
	HLRTopoBRep
	HLRBRep
	HLRAlgo
	Intrv
	TopBas
	TopCnx
	Contap
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKGeomBase
	TKG2d
	TKG3d
	TKGeomAlgo
	TKTopAlgo
)

INCLUDE(../BuildToolkit.cmake)

