set(TOOLKIT TKBinL)

set(TOOLKIT_MODULES
	BinMDF
	BinMDataStd
	BinMFunction
	BinMDocStd
	BinObjMgt
	BinLDrivers
)
set(TOOLKIT_DEPENDS
	TKCDF
	TKernel
	TKLCAF
)

include(../BuildToolkit.cmake)

