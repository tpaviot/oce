set(TOOLKIT TKSTEP209)

set(TOOLKIT_MODULES
	StepElement
	StepFEA
	RWStepElement
	RWStepFEA
)
set(TOOLKIT_DEPENDS
	TKernel
	TKXSBase
	TKSTEPBase
)

include(../BuildToolkit.cmake)

