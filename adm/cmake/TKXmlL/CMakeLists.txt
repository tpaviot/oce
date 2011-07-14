set(TOOLKIT TKXmlL)

set(TOOLKIT_MODULES
	XmlLDrivers
	XmlMDF
	XmlMDataStd
	XmlMDocStd
	XmlMFunction
	XmlObjMgt
)
set(TOOLKIT_DEPENDS
	TKCDF
	TKernel
	TKMath
	TKLCAF
)

include(../BuildToolkit.cmake)

