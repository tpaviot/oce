SET(TOOLKIT TKBinL)

SET(TOOLKIT_MODULES
	BinMDF
	BinMDataStd
	BinMFunction
	BinMDocStd
	BinObjMgt
	BinLDrivers
)
SET(TOOLKIT_DEPENDS
	TKLCAF
	TKCDF
	TKernel
)

INCLUDE(../OccBuildKit.cmake)

