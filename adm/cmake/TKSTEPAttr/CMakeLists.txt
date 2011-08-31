SET(TOOLKIT TKSTEPAttr)

SET(TOOLKIT_MODULES
	StepVisual
	RWStepVisual
	StepDimTol
	RWStepDimTol
)
SET(TOOLKIT_DEPENDS
	TKSTEPBase
	TKernel
	TKXSBase
)

INCLUDE(../BuildToolkit.cmake)

