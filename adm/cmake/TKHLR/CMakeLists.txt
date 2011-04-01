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
	TKernel
	TKGeomBase
	TKG3d
	TKTopAlgo
	TKMath
	TKGeomAlgo
	TKBRep
	TKG2d
)

INCLUDE(../OccBuildKit.cmake)

