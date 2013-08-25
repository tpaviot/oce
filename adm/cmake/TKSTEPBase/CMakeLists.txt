set(TOOLKIT TKSTEPBase)

set(TOOLKIT_MODULES
	StepBasic
	RWStepBasic
	StepRepr
	RWStepRepr
	StepGeom
	RWStepGeom
	StepShape
	RWStepShape
)
set(TOOLKIT_DEPENDS
	TKernel
	TKXSBase
	TKMath
)

include(../BuildToolkit.cmake)

