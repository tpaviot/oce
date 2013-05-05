SET(TOOLKIT TKBin)

SET(TOOLKIT_MODULES
	BinDrivers
	BinMDataXtd
	BinMPrsStd
	BinMNaming
	BinTools
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKMath
	TKernel
	TKG2d
	TKG3d
	TKCAF
	TKCDF
	TKLCAF
	TKV3d
	TKBinL
)

INCLUDE(../BuildToolkit.cmake)

