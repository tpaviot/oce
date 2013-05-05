SET(TOOLKIT TKPCAF)

SET(TOOLKIT_MODULES
	PDataXtd
	PNaming
	PPrsStd
	MDataXtd
	MPrsStd
	MNaming
)
SET(TOOLKIT_DEPENDS
	PTKernel
	TKBRep
	TKMath
	TKernel
	TKCDF
	TKG2d
	TKV3d
	TKService
	TKG3d
	TKPShape
	TKCAF
	TKLCAF
	TKPLCAF
)

INCLUDE(../BuildToolkit.cmake)

