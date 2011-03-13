# Makefile.am for Open Cascade toolkit TKAdvTools
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/Dynamic : @top_srcdir@/src/Dynamic: \
@top_srcdir@/drv/Materials : @top_srcdir@/src/Materials: \
@top_srcdir@/drv/Expr : @top_srcdir@/src/Expr: \
@top_srcdir@/drv/ExprIntrp : @top_srcdir@/src/ExprIntrp: \
@top_srcdir@/drv/GraphDS : @top_srcdir@/src/GraphDS: \
@top_srcdir@/drv/GraphTools : @top_srcdir@/src/GraphTools


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/Dynamic -I@top_srcdir@/src/Dynamic \
-I@top_srcdir@/drv/Materials -I@top_srcdir@/src/Materials \
-I@top_srcdir@/drv/Expr -I@top_srcdir@/src/Expr \
-I@top_srcdir@/drv/ExprIntrp -I@top_srcdir@/src/ExprIntrp \
-I@top_srcdir@/drv/GraphDS -I@top_srcdir@/src/GraphDS \
-I@top_srcdir@/drv/GraphTools -I@top_srcdir@/src/GraphTools


lib_LTLIBRARIES=libTKAdvTools.la

libTKAdvTools_la_LIBADD = \
../TKernel/libTKernel.la \
$(STLPort_LIB) 

libTKAdvTools_la_SOURCES = \
@top_srcdir@/drv/Dynamic/Dynamic_ParameterNode_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SeqOfClasses_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SeqOfFuzzyDefinitions_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SeqOfMethodDefinitions_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SeqOfMethods_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceNodeOfSeqOfClasses_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceNodeOfSeqOfFuzzyDefinitions_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceNodeOfSeqOfMethodDefinitions_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceNodeOfSeqOfMethods_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceOfClasses_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceOfFuzzyDefinitions_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceOfMethodDefinitions_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_SequenceOfMethods_0.cxx \
@top_srcdir@/drv/Dynamic/Dynamic_VariableNode_0.cxx \
@top_srcdir@/drv/Expr/Expr_Array1OfGeneralExpression_0.cxx \
@top_srcdir@/drv/Expr/Expr_Array1OfNamedUnknown_0.cxx \
@top_srcdir@/drv/Expr/Expr_Array1OfSingleRelation_0.cxx \
@top_srcdir@/drv/Expr/Expr_ExprFailure_0.cxx \
@top_srcdir@/drv/Expr/Expr_IndexedMapNodeOfMapOfNamedUnknown_0.cxx \
@top_srcdir@/drv/Expr/Expr_InvalidAssignment_0.cxx \
@top_srcdir@/drv/Expr/Expr_InvalidFunction_0.cxx \
@top_srcdir@/drv/Expr/Expr_InvalidOperand_0.cxx \
@top_srcdir@/drv/Expr/Expr_MapOfNamedUnknown_0.cxx \
@top_srcdir@/drv/Expr/Expr_NotAssigned_0.cxx \
@top_srcdir@/drv/Expr/Expr_NotEvaluable_0.cxx \
@top_srcdir@/drv/Expr/Expr_SequenceNodeOfSequenceOfGeneralExpression_0.cxx \
@top_srcdir@/drv/Expr/Expr_SequenceNodeOfSequenceOfGeneralRelation_0.cxx \
@top_srcdir@/drv/Expr/Expr_SequenceOfGeneralExpression_0.cxx \
@top_srcdir@/drv/Expr/Expr_SequenceOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp.tab.c \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceOfNamedExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceOfNamedFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfNames_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfNames_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfGeneralExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfGeneralFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfNames_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SyntaxError_0.cxx \
@top_srcdir@/drv/ExprIntrp/lex.ExprIntrp.c \
@top_srcdir@/drv/GraphDS/GraphDS_DataMapIteratorOfEntityRoleMap_0.cxx \
@top_srcdir@/drv/GraphDS/GraphDS_DataMapNodeOfEntityRoleMap_0.cxx \
@top_srcdir@/drv/GraphDS/GraphDS_EntityRoleMap_0.cxx \
@top_srcdir@/drv/GraphTools/GraphTools_ListIteratorOfListOfSequenceOfInteger_0.cxx \
@top_srcdir@/drv/GraphTools/GraphTools_ListIteratorOfSCList_0.cxx \
@top_srcdir@/drv/GraphTools/GraphTools_ListNodeOfListOfSequenceOfInteger_0.cxx \
@top_srcdir@/drv/GraphTools/GraphTools_ListNodeOfSCList_0.cxx \
@top_srcdir@/drv/GraphTools/GraphTools_ListOfSequenceOfInteger_0.cxx \
@top_srcdir@/drv/GraphTools/GraphTools_SCList_0.cxx \
@top_srcdir@/drv/Materials/Materials_FuzzyInstance_0.cxx \
@top_srcdir@/drv/Materials/Materials_MaterialsSequence_0.cxx \
@top_srcdir@/drv/Materials/Materials_MtsSequence_0.cxx \
@top_srcdir@/drv/Materials/Materials_SequenceNodeOfMtsSequence_0.cxx \
@top_srcdir@/src/Dynamic/Dynamic.cxx \
@top_srcdir@/src/Dynamic/Dynamic_AbstractVariableInstance.cxx \
@top_srcdir@/src/Dynamic/Dynamic_BooleanParameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_CompiledMethod.cxx \
@top_srcdir@/src/Dynamic/Dynamic_CompositMethod.cxx \
@top_srcdir@/src/Dynamic/Dynamic_CompositVariableInstance.cxx \
@top_srcdir@/src/Dynamic/Dynamic_DynamicClass.cxx \
@top_srcdir@/src/Dynamic/Dynamic_DynamicDerivedClass.cxx \
@top_srcdir@/src/Dynamic/Dynamic_DynamicInstance.cxx \
@top_srcdir@/src/Dynamic/Dynamic_FuzzyClass.cxx \
@top_srcdir@/src/Dynamic/Dynamic_FuzzyDefinition.cxx \
@top_srcdir@/src/Dynamic/Dynamic_FuzzyDefinitionsDictionary.cxx \
@top_srcdir@/src/Dynamic/Dynamic_InstanceParameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_IntegerParameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_InterpretedMethod.cxx \
@top_srcdir@/src/Dynamic/Dynamic_Method.cxx \
@top_srcdir@/src/Dynamic/Dynamic_MethodDefinition.cxx \
@top_srcdir@/src/Dynamic/Dynamic_MethodDefinitionsDictionary.cxx \
@top_srcdir@/src/Dynamic/Dynamic_ObjectParameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_Parameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_RealParameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_StringParameter.cxx \
@top_srcdir@/src/Dynamic/Dynamic_Variable.cxx \
@top_srcdir@/src/Dynamic/Dynamic_VariableGroup.cxx \
@top_srcdir@/src/Dynamic/Dynamic_VariableInstance.cxx \
@top_srcdir@/src/Expr/Expr.cxx \
@top_srcdir@/src/Expr/Expr_Absolute.cxx \
@top_srcdir@/src/Expr/Expr_ArcCosine.cxx \
@top_srcdir@/src/Expr/Expr_ArcSine.cxx \
@top_srcdir@/src/Expr/Expr_ArcTangent.cxx \
@top_srcdir@/src/Expr/Expr_ArgCosh.cxx \
@top_srcdir@/src/Expr/Expr_ArgSinh.cxx \
@top_srcdir@/src/Expr/Expr_ArgTanh.cxx \
@top_srcdir@/src/Expr/Expr_BinaryExpression.cxx \
@top_srcdir@/src/Expr/Expr_BinaryFunction.cxx \
@top_srcdir@/src/Expr/Expr_Cosh.cxx \
@top_srcdir@/src/Expr/Expr_Cosine.cxx \
@top_srcdir@/src/Expr/Expr_Difference.cxx \
@top_srcdir@/src/Expr/Expr_Different.cxx \
@top_srcdir@/src/Expr/Expr_Division.cxx \
@top_srcdir@/src/Expr/Expr_Equal.cxx \
@top_srcdir@/src/Expr/Expr_Exponential.cxx \
@top_srcdir@/src/Expr/Expr_Exponentiate.cxx \
@top_srcdir@/src/Expr/Expr_FunctionDerivative.cxx \
@top_srcdir@/src/Expr/Expr_GeneralExpression.cxx \
@top_srcdir@/src/Expr/Expr_GeneralFunction.cxx \
@top_srcdir@/src/Expr/Expr_GeneralRelation.cxx \
@top_srcdir@/src/Expr/Expr_GreaterThan.cxx \
@top_srcdir@/src/Expr/Expr_GreaterThanOrEqual.cxx \
@top_srcdir@/src/Expr/Expr_LessThan.cxx \
@top_srcdir@/src/Expr/Expr_LessThanOrEqual.cxx \
@top_srcdir@/src/Expr/Expr_LogOf10.cxx \
@top_srcdir@/src/Expr/Expr_LogOfe.cxx \
@top_srcdir@/src/Expr/Expr_NamedConstant.cxx \
@top_srcdir@/src/Expr/Expr_NamedExpression.cxx \
@top_srcdir@/src/Expr/Expr_NamedFunction.cxx \
@top_srcdir@/src/Expr/Expr_NamedUnknown.cxx \
@top_srcdir@/src/Expr/Expr_NumericValue.cxx \
@top_srcdir@/src/Expr/Expr_Operators.cxx \
@top_srcdir@/src/Expr/Expr_PolyExpression.cxx \
@top_srcdir@/src/Expr/Expr_PolyFunction.cxx \
@top_srcdir@/src/Expr/Expr_Product.cxx \
@top_srcdir@/src/Expr/Expr_RUIterator.cxx \
@top_srcdir@/src/Expr/Expr_RelationIterator.cxx \
@top_srcdir@/src/Expr/Expr_Sign.cxx \
@top_srcdir@/src/Expr/Expr_Sine.cxx \
@top_srcdir@/src/Expr/Expr_SingleRelation.cxx \
@top_srcdir@/src/Expr/Expr_Sinh.cxx \
@top_srcdir@/src/Expr/Expr_Square.cxx \
@top_srcdir@/src/Expr/Expr_SquareRoot.cxx \
@top_srcdir@/src/Expr/Expr_Sum.cxx \
@top_srcdir@/src/Expr/Expr_SystemRelation.cxx \
@top_srcdir@/src/Expr/Expr_Tangent.cxx \
@top_srcdir@/src/Expr/Expr_Tanh.cxx \
@top_srcdir@/src/Expr/Expr_UnaryExpression.cxx \
@top_srcdir@/src/Expr/Expr_UnaryFunction.cxx \
@top_srcdir@/src/Expr/Expr_UnaryMinus.cxx \
@top_srcdir@/src/Expr/Expr_UnknownIterator.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_Analysis.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_GenExp.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_GenFct.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_GenRel.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_Generator.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_yaccintrf.cxx \
@top_srcdir@/src/ExprIntrp/ExprIntrp_yacclex.cxx \
@top_srcdir@/src/GraphTools/GraphTools_RGNode.cxx \
@top_srcdir@/src/GraphTools/GraphTools_SC.cxx \
@top_srcdir@/src/GraphTools/GraphTools_TSNode.cxx \
@top_srcdir@/src/Materials/Materials.cxx \
@top_srcdir@/src/Materials/Materials_Color.cxx \
@top_srcdir@/src/Materials/Materials_Material.cxx \
@top_srcdir@/src/Materials/Materials_MaterialDefinition.cxx \
@top_srcdir@/src/Materials/Materials_MaterialsDictionary.cxx

