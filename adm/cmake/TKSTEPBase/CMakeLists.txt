SET(TOOLKIT TKSTEPBase)

SET(TOOLKIT_MODULES
	StepBasic
	RWStepBasic
	StepRepr
	RWStepRepr
	StepGeom
	RWStepGeom
	StepShape
	RWStepShape
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKXSBase
	TKMath
)

INCLUDE(../BuildToolkit.cmake)

