SET(TOOLKIT TKXSBase)

SET(TOOLKIT_MODULES
	Interface
	Transfer
	IFGraph
	IFSelect
	TransferBRep
	XSControl
	StepData
	StepFile
	HeaderSection
	RWHeaderSection
	APIHeaderSection
	StepSelect
	UnitsMethods
	XSAlgo
	LibCtl
	MoniTool
)
SET(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKG2d
	TKG3d
	TKTopAlgo
	TKGeomBase
	TKShHealing
)

INCLUDE(../BuildToolkit.cmake)

