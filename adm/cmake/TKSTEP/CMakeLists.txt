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
	TKXSBase
	TKSTEPBase
	TKSTEPAttr
	TKMath
	TKG3d
	TKG2d
	TKShHealing
	TKSTEP209
	TKGeomBase
	TKBRep
	TKTopAlgo
	TKGeomAlgo
)
SET(TOOLKIT_LIBS ${CSF_wsock32_LIB})

INCLUDE(../OccBuildKit.cmake)

