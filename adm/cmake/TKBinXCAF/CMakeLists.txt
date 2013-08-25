set(TOOLKIT TKBinXCAF)

set(TOOLKIT_MODULES
	BinXCAFDrivers
	BinMXCAFDoc
)
set(TOOLKIT_DEPENDS
	TKBRep
	TKXCAF
	TKMath
	TKernel
	TKBinL
	TKG2d
	TKCAF
	TKCDF
	TKG3d
	TKLCAF
	TKBin
)

include(../BuildToolkit.cmake)

