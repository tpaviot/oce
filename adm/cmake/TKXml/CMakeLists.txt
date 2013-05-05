SET(TOOLKIT TKXml)

SET(TOOLKIT_MODULES
	XmlDrivers
	XmlMDataXtd
	XmlMNaming
	XmlMPrsStd
)
SET(TOOLKIT_DEPENDS
	TKCDF
	TKernel
	TKV3d
	TKMath
	TKBRep
	TKG2d
	TKGeomBase
	TKG3d
	TKLCAF
	TKCAF
	TKXmlL
)

INCLUDE(../BuildToolkit.cmake)

