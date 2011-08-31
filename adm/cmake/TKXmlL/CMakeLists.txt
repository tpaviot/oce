SET(TOOLKIT TKXmlL)

SET(TOOLKIT_MODULES
	XmlLDrivers
	XmlMDF
	XmlMDataStd
	XmlMDocStd
	XmlMFunction
	XmlObjMgt
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKMath
	TKLCAF
	TKCDF
)

INCLUDE(../BuildToolkit.cmake)

