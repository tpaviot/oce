set(TOOLKIT TKSTEP)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
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
set(TOOLKIT_LIBS ${CSF_wsock32_LIB})

include(../BuildToolkit.cmake)

