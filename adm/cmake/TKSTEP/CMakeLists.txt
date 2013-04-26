SET(TOOLKIT TKSTEP)

SET(TOOLKIT_MODULES
	StepAP214
	RWStepAP214
	StepAP203
	RWStepAP203
	STEPConstruct
	STEPEdit
	GeomToStep
	StepToGeom
	StepToTopoDS
	TopoDSToStep
	STEPControl
	STEPSelections
	StepAP209
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKSTEPAttr
	TKSTEP209
	TKSTEPBase
	TKBRep
	TKMath
	TKG2d
	TKShHealing
	TKTopAlgo
	TKG3d
	TKGeomBase
	TKGeomAlgo
	TKXSBase
)
SET(TOOLKIT_LIBS ${CSF_wsock32_LIB})

INCLUDE(../BuildToolkit.cmake)

