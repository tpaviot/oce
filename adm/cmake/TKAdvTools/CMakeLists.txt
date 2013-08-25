set(TOOLKIT TKAdvTools)

set(TOOLKIT_MODULES
	Dynamic
	Materials
	Expr
	ExprIntrp
	GraphDS
	GraphTools
)
set(TOOLKIT_DEPENDS
	TKernel
)

include(../BuildToolkit.cmake)

