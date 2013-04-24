project(TKAdvTools)

if (WIN32)
  list( APPEND TKAdvTools_PRECOMPILED_DEFS "-D__Dynamic_DLL" )
  list( APPEND TKAdvTools_PRECOMPILED_DEFS "-D__Materials_DLL" )
  list( APPEND TKAdvTools_PRECOMPILED_DEFS "-D__Expr_DLL" )
  list( APPEND TKAdvTools_PRECOMPILED_DEFS "-D__ExprIntrp_DLL" )
  list( APPEND TKAdvTools_PRECOMPILED_DEFS "-D__GraphDS_DLL" )
  list( APPEND TKAdvTools_PRECOMPILED_DEFS "-D__GraphTools_DLL" )
  string( REGEX REPLACE ";" " " TKAdvTools_PRECOMPILED_DEFS "${TKAdvTools_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../drv/Dynamic" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../src/Dynamic" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../drv/Materials" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../src/Materials" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../drv/Expr" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../src/Expr" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../drv/ExprIntrp" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../src/ExprIntrp" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../drv/GraphDS" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../src/GraphDS" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../drv/GraphTools" )
  list( APPEND TKAdvTools_COMPILER_DIRECTORIES "../../../src/GraphTools" )

if (WIN32)
else()
endif()

  list( APPEND TKAdvTools_USED_LIBS TKernel )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_ParameterNode_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_ParameterNode_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SeqOfClasses_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SeqOfClasses_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SeqOfFuzzyDefinitions_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SeqOfFuzzyDefinitions_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SeqOfMethodDefinitions_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SeqOfMethodDefinitions_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SeqOfMethods_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SeqOfMethods_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfClasses_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfClasses_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfFuzzyDefinitions_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfFuzzyDefinitions_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfMethodDefinitions_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfMethodDefinitions_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfMethods_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceNodeOfSeqOfMethods_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceOfClasses_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceOfClasses_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceOfFuzzyDefinitions_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceOfFuzzyDefinitions_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceOfMethodDefinitions_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceOfMethodDefinitions_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_SequenceOfMethods_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_SequenceOfMethods_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Dynamic/Dynamic_VariableNode_0.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../drv/Dynamic/Dynamic_VariableNode_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_AbstractVariableInstance.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_AbstractVariableInstance.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_BooleanParameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_BooleanParameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_CompiledMethod.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_CompiledMethod.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_CompositMethod.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_CompositMethod.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_CompositVariableInstance.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_CompositVariableInstance.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_DynamicClass.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_DynamicClass.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_DynamicDerivedClass.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_DynamicDerivedClass.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_DynamicInstance.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_DynamicInstance.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_FuzzyClass.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_FuzzyClass.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_FuzzyDefinition.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_FuzzyDefinition.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_FuzzyDefinitionsDictionary.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_FuzzyDefinitionsDictionary.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_InstanceParameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_InstanceParameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_IntegerParameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_IntegerParameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_InterpretedMethod.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_InterpretedMethod.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_Method.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_Method.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_MethodDefinition.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_MethodDefinition.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_MethodDefinitionsDictionary.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_MethodDefinitionsDictionary.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_ObjectParameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_ObjectParameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_Parameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_Parameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_RealParameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_RealParameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_StringParameter.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_StringParameter.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_Variable.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_Variable.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_VariableGroup.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_VariableGroup.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Dynamic/Dynamic_VariableInstance.cxx" )
  SOURCE_GROUP (Dynamic FILES "../../../src/Dynamic/Dynamic_VariableInstance.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Materials/Materials_FuzzyInstance_0.cxx" )
  SOURCE_GROUP (Materials FILES "../../../drv/Materials/Materials_FuzzyInstance_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Materials/Materials_MaterialsSequence_0.cxx" )
  SOURCE_GROUP (Materials FILES "../../../drv/Materials/Materials_MaterialsSequence_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Materials/Materials_MtsSequence_0.cxx" )
  SOURCE_GROUP (Materials FILES "../../../drv/Materials/Materials_MtsSequence_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Materials/Materials_SequenceNodeOfMtsSequence_0.cxx" )
  SOURCE_GROUP (Materials FILES "../../../drv/Materials/Materials_SequenceNodeOfMtsSequence_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Materials/Materials.cxx" )
  SOURCE_GROUP (Materials FILES "../../../src/Materials/Materials.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Materials/Materials_Color.cxx" )
  SOURCE_GROUP (Materials FILES "../../../src/Materials/Materials_Color.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Materials/Materials_Material.cxx" )
  SOURCE_GROUP (Materials FILES "../../../src/Materials/Materials_Material.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Materials/Materials_MaterialDefinition.cxx" )
  SOURCE_GROUP (Materials FILES "../../../src/Materials/Materials_MaterialDefinition.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Materials/Materials_MaterialsDictionary.cxx" )
  SOURCE_GROUP (Materials FILES "../../../src/Materials/Materials_MaterialsDictionary.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_Array1OfGeneralExpression_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_Array1OfGeneralExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_Array1OfNamedUnknown_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_Array1OfNamedUnknown_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_Array1OfSingleRelation_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_Array1OfSingleRelation_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_ExprFailure_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_ExprFailure_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_IndexedMapNodeOfMapOfNamedUnknown_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_IndexedMapNodeOfMapOfNamedUnknown_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_InvalidAssignment_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_InvalidAssignment_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_InvalidFunction_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_InvalidFunction_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_InvalidOperand_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_InvalidOperand_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_MapOfNamedUnknown_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_MapOfNamedUnknown_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_NotAssigned_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_NotAssigned_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_NotEvaluable_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_NotEvaluable_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_SequenceNodeOfSequenceOfGeneralExpression_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_SequenceNodeOfSequenceOfGeneralExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_SequenceNodeOfSequenceOfGeneralRelation_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_SequenceNodeOfSequenceOfGeneralRelation_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_SequenceOfGeneralExpression_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_SequenceOfGeneralExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/Expr/Expr_SequenceOfGeneralRelation_0.cxx" )
  SOURCE_GROUP (Expr FILES "../../../drv/Expr/Expr_SequenceOfGeneralRelation_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Absolute.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Absolute.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_ArcCosine.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_ArcCosine.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_ArcSine.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_ArcSine.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_ArcTangent.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_ArcTangent.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_ArgCosh.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_ArgCosh.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_ArgSinh.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_ArgSinh.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_ArgTanh.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_ArgTanh.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_BinaryExpression.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_BinaryExpression.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_BinaryFunction.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_BinaryFunction.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Cosh.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Cosh.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Cosine.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Cosine.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Difference.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Difference.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Different.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Different.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Division.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Division.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Equal.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Equal.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Exponential.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Exponential.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Exponentiate.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Exponentiate.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_FunctionDerivative.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_FunctionDerivative.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_GeneralExpression.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_GeneralExpression.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_GeneralFunction.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_GeneralFunction.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_GeneralRelation.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_GeneralRelation.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_GreaterThan.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_GreaterThan.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_GreaterThanOrEqual.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_GreaterThanOrEqual.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_LessThan.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_LessThan.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_LessThanOrEqual.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_LessThanOrEqual.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_LogOf10.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_LogOf10.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_LogOfe.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_LogOfe.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_NamedConstant.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_NamedConstant.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_NamedExpression.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_NamedExpression.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_NamedFunction.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_NamedFunction.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_NamedUnknown.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_NamedUnknown.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_NumericValue.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_NumericValue.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Operators.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Operators.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_PolyExpression.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_PolyExpression.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_PolyFunction.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_PolyFunction.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Product.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Product.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_RUIterator.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_RUIterator.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_RelationIterator.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_RelationIterator.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Sign.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Sign.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Sine.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Sine.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_SingleRelation.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_SingleRelation.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Sinh.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Sinh.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Square.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Square.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_SquareRoot.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_SquareRoot.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Sum.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Sum.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_SystemRelation.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_SystemRelation.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Tangent.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Tangent.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_Tanh.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_Tanh.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_UnaryExpression.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_UnaryExpression.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_UnaryFunction.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_UnaryFunction.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_UnaryMinus.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_UnaryMinus.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/Expr/Expr_UnknownIterator.cxx" )
  SOURCE_GROUP (Expr FILES "../../../src/Expr/Expr_UnknownIterator.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp.tab.c" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp.tab.c")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedExpression_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedFunction_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedFunction_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_SequenceOfNamedExpression_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_SequenceOfNamedExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_SequenceOfNamedFunction_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_SequenceOfNamedFunction_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralExpression_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralFunction_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralFunction_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralRelation_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfGeneralRelation_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfNames_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackIteratorOfStackOfNames_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralExpression_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralFunction_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralFunction_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralRelation_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfGeneralRelation_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfNames_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackNodeOfStackOfNames_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackOfGeneralExpression_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackOfGeneralExpression_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackOfGeneralFunction_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackOfGeneralFunction_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackOfGeneralRelation_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackOfGeneralRelation_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_StackOfNames_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_StackOfNames_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/ExprIntrp_SyntaxError_0.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/ExprIntrp_SyntaxError_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/ExprIntrp/lex.ExprIntrp.c" )
  SOURCE_GROUP (ExprIntrp FILES "../../../drv/ExprIntrp/lex.ExprIntrp.c")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_Analysis.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_Analysis.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_GenExp.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_GenExp.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_GenFct.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_GenFct.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_GenRel.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_GenRel.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_Generator.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_Generator.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_yaccintrf.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_yaccintrf.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/ExprIntrp/ExprIntrp_yacclex.cxx" )
  SOURCE_GROUP (ExprIntrp FILES "../../../src/ExprIntrp/ExprIntrp_yacclex.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphDS/GraphDS_DataMapIteratorOfEntityRoleMap_0.cxx" )
  SOURCE_GROUP (GraphDS FILES "../../../drv/GraphDS/GraphDS_DataMapIteratorOfEntityRoleMap_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphDS/GraphDS_DataMapNodeOfEntityRoleMap_0.cxx" )
  SOURCE_GROUP (GraphDS FILES "../../../drv/GraphDS/GraphDS_DataMapNodeOfEntityRoleMap_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphDS/GraphDS_EntityRoleMap_0.cxx" )
  SOURCE_GROUP (GraphDS FILES "../../../drv/GraphDS/GraphDS_EntityRoleMap_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphTools/GraphTools_ListIteratorOfListOfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../drv/GraphTools/GraphTools_ListIteratorOfListOfSequenceOfInteger_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphTools/GraphTools_ListIteratorOfSCList_0.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../drv/GraphTools/GraphTools_ListIteratorOfSCList_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphTools/GraphTools_ListNodeOfListOfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../drv/GraphTools/GraphTools_ListNodeOfListOfSequenceOfInteger_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphTools/GraphTools_ListNodeOfSCList_0.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../drv/GraphTools/GraphTools_ListNodeOfSCList_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphTools/GraphTools_ListOfSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../drv/GraphTools/GraphTools_ListOfSequenceOfInteger_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../drv/GraphTools/GraphTools_SCList_0.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../drv/GraphTools/GraphTools_SCList_0.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/GraphTools/GraphTools_RGNode.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../src/GraphTools/GraphTools_RGNode.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/GraphTools/GraphTools_SC.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../src/GraphTools/GraphTools_SC.cxx")

  list( APPEND TKAdvTools_USED_SRCFILES "../../../src/GraphTools/GraphTools_TSNode.cxx" )
  SOURCE_GROUP (GraphTools FILES "../../../src/GraphTools/GraphTools_TSNode.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKAdvTools)
 add_library( TKAdvTools SHARED ${TKAdvTools_USED_SRCFILES} )

 set_property(TARGET TKAdvTools PROPERTY FOLDER FoundationClasses)

 install( TARGETS TKAdvTools
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKAdvTools.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKAdvTools PROPERTIES COMPILE_FLAGS "${TKAdvTools_PRECOMPILED_DEFS}" )
 include_directories( ${TKAdvTools_COMPILER_DIRECTORIES} )
 target_link_libraries( TKAdvTools ${TKAdvTools_USED_LIBS} )
endif()
