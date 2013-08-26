set(TOOLKIT TKXSBase)

set(TOOLKIT_MODULES
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
set(TOOLKIT_DEPENDS
	TKBRep
	TKernel
	TKMath
	TKG2d
	TKG3d
	TKTopAlgo
	TKGeomBase
	TKShHealing
)

include(../BuildToolkit.cmake)

