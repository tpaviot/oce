SET(TOOLKIT TKAdvTools)

SET(TOOLKIT_MODULES
	Dynamic
	Materials
	Expr
	ExprIntrp
	GraphDS
	GraphTools
)
SET(TOOLKIT_DEPENDS
	TKernel
)

INCLUDE(../BuildToolkit.cmake)

