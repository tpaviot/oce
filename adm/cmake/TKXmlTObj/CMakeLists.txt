set(TOOLKIT TKXmlTObj)

set(TOOLKIT_MODULES
	XmlTObjDrivers
)
set(TOOLKIT_DEPENDS
	TKCDF
	TKernel
	TKTObj
	TKMath
	TKLCAF
	TKXmlL
)

include(../BuildToolkit.cmake)

