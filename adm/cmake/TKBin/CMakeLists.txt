set(TOOLKIT TKBin)

set(TOOLKIT_MODULES
	BinDrivers
	BinMDataXtd
	BinMPrsStd
	BinMNaming
	BinTools
)
set(TOOLKIT_DEPENDS
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

include(../BuildToolkit.cmake)

