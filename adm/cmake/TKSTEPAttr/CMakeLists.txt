set(TOOLKIT TKSTEPAttr)

set(TOOLKIT_MODULES
	StepVisual
	RWStepVisual
	StepDimTol
	RWStepDimTol
)
set(TOOLKIT_DEPENDS
	TKernel
	TKXSBase
	TKSTEPBase
)

include(../BuildToolkit.cmake)

