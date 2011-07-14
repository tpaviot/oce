set(TOOLKIT TKXmlXCAF)

set(TOOLKIT_MODULES
	XmlXCAFDrivers
	XmlMXCAFDoc
)
set(TOOLKIT_DEPENDS
	TKXmlL
	TKBRep
	TKCDF
	TKMath
	TKernel
	TKG2d
	TKGeomBase
	TKCAF
	TKG3d
	TKLCAF
	TKXCAF
	TKXml
)

include(../BuildToolkit.cmake)

