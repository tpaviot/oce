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
	TKernel
	TKMath
	TKG2d
	TKG3d
	TKShHealing
	TKBRep
	TKGeomBase
	TKTopAlgo
)

INCLUDE(../OccBuildKit.cmake)

