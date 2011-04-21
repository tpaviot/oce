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
	TKernel
	TKCAF
	TKLCAF
	TKPLCAF
	TKG3d
	TKV3d
	TKService
	PTKernel
	TKMath
	TKG2d
	TKPShape
	TKCDF
	TKV2d
	TKBRep
)

INCLUDE(../OccBuildKit.cmake)

