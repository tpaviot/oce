SET(TOOLKIT TKBin)

SET(TOOLKIT_MODULES
	BinDrivers
	BinMDataXtd
	BinMPrsStd
	BinMNaming
	BinTools
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKBinL
	TKLCAF
	TKG2d
	TKCAF
	TKV3d
	TKBRep
	TKG3d
	TKCDF
)

INCLUDE(../OccBuildKit.cmake)

