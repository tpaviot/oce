SET(TOOLKIT TKSTEPAttr)

SET(TOOLKIT_MODULES
	StepVisual
	RWStepVisual
	StepDimTol
	RWStepDimTol
)
SET(TOOLKIT_DEPENDS
	TKernel
	TKXSBase
	TKSTEPBase
)

INCLUDE(../BuildToolkit.cmake)

