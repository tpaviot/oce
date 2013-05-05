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
	TKCDF
	TKernel
	TKMath
	TKLCAF
)

INCLUDE(../BuildToolkit.cmake)

