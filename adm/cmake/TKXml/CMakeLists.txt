SET(TOOLKIT TKXml)

SET(TOOLKIT_MODULES
	XmlDrivers
	XmlMDataXtd
	XmlMNaming
	XmlMPrsStd
)
SET(TOOLKIT_DEPENDS
	TKMath
	TKernel
	TKLCAF
	TKG2d
	TKCAF
	TKV3d
	TKBRep
	TKXmlL
	TKG3d
	TKCDF
	TKGeomBase
)

INCLUDE(../OccBuildKit.cmake)

