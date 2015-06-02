# Makefile.am for Open Cascade toolkit TKMath
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/math : @top_srcdir@/src/math: \
@top_srcdir@/drv/ElCLib : @top_srcdir@/src/ElCLib: \
@top_srcdir@/drv/ElSLib : @top_srcdir@/src/ElSLib: \
@top_srcdir@/drv/BSplCLib : @top_srcdir@/src/BSplCLib: \
@top_srcdir@/drv/BSplSLib : @top_srcdir@/src/BSplSLib: \
@top_srcdir@/drv/PLib : @top_srcdir@/src/PLib: \
@top_srcdir@/drv/Precision : @top_srcdir@/src/Precision: \
@top_srcdir@/drv/GeomAbs : @top_srcdir@/src/GeomAbs: \
@top_srcdir@/drv/Poly : @top_srcdir@/src/Poly: \
@top_srcdir@/drv/CSLib : @top_srcdir@/src/CSLib: \
@top_srcdir@/drv/Convert : @top_srcdir@/src/Convert: \
@top_srcdir@/drv/Bnd : @top_srcdir@/src/Bnd: \
@top_srcdir@/drv/BVH : @top_srcdir@/src/BVH: \
@top_srcdir@/drv/gp : @top_srcdir@/src/gp: \
@top_srcdir@/drv/TColgp : @top_srcdir@/src/TColgp: \
@top_srcdir@/drv/TopLoc : @top_srcdir@/src/TopLoc: \
@top_srcdir@/drv/Expr : @top_srcdir@/src/Expr: \
@top_srcdir@/drv/ExprIntrp : @top_srcdir@/src/ExprIntrp


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_TBB_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/math -I@top_srcdir@/src/math \
-I@top_srcdir@/drv/ElCLib -I@top_srcdir@/src/ElCLib \
-I@top_srcdir@/drv/ElSLib -I@top_srcdir@/src/ElSLib \
-I@top_srcdir@/drv/BSplCLib -I@top_srcdir@/src/BSplCLib \
-I@top_srcdir@/drv/BSplSLib -I@top_srcdir@/src/BSplSLib \
-I@top_srcdir@/drv/PLib -I@top_srcdir@/src/PLib \
-I@top_srcdir@/drv/Precision -I@top_srcdir@/src/Precision \
-I@top_srcdir@/drv/GeomAbs -I@top_srcdir@/src/GeomAbs \
-I@top_srcdir@/drv/Poly -I@top_srcdir@/src/Poly \
-I@top_srcdir@/drv/CSLib -I@top_srcdir@/src/CSLib \
-I@top_srcdir@/drv/Convert -I@top_srcdir@/src/Convert \
-I@top_srcdir@/drv/Bnd -I@top_srcdir@/src/Bnd \
-I@top_srcdir@/drv/BVH -I@top_srcdir@/src/BVH \
-I@top_srcdir@/drv/gp -I@top_srcdir@/src/gp \
-I@top_srcdir@/drv/TColgp -I@top_srcdir@/src/TColgp \
-I@top_srcdir@/drv/TopLoc -I@top_srcdir@/src/TopLoc \
-I@top_srcdir@/drv/Expr -I@top_srcdir@/src/Expr \
-I@top_srcdir@/drv/ExprIntrp -I@top_srcdir@/src/ExprIntrp


lib_LTLIBRARIES=libTKMath.la

libTKMath_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKernel/libTKernel.la \
$(STLPort_LIB) $(CSF_TBB_LIB) 

libTKMath_la_SOURCES = \
@top_srcdir@/drv/Bnd/Bnd_Array1OfBox2d_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_Array1OfBox_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_Array1OfSphere_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_B2d_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_B2f_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_B3d_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_B3f_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_HArray1OfBox2d_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_HArray1OfBox_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_HArray1OfSphere_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_SeqOfBox_0.cxx \
@top_srcdir@/drv/Bnd/Bnd_SequenceNodeOfSeqOfBox_0.cxx \
@top_srcdir@/drv/Convert/Convert_SequenceNodeOfSequenceOfArray1OfPoles_0.cxx \
@top_srcdir@/drv/Convert/Convert_SequenceOfArray1OfPoles_0.cxx \
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
@top_srcdir@/drv/ExprIntrp/ExprIntrp_ListIteratorOfStackOfGeneralExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_ListIteratorOfStackOfGeneralFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_ListIteratorOfStackOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_ListNodeOfStackOfGeneralExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_ListNodeOfStackOfGeneralFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_ListNodeOfStackOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceNodeOfSequenceOfNamedFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceOfNamedExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SequenceOfNamedFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfGeneralExpression_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfGeneralFunction_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_StackOfGeneralRelation_0.cxx \
@top_srcdir@/drv/ExprIntrp/ExprIntrp_SyntaxError_0.cxx \
@top_srcdir@/drv/ExprIntrp/lex.ExprIntrp.c \
@top_srcdir@/drv/Poly/Poly_Array1OfTriangle_0.cxx \
@top_srcdir@/drv/Poly/Poly_HArray1OfTriangle_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfCirc2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfLin2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array1OfXY_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfCirc2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfLin2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_Array2OfXY_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfCirc2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfLin2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray1OfXY_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfCirc2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfLin2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HArray2OfXY_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_HSequenceOfXY_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfAx1_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceNodeOfSequenceOfXY_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfAx1_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfDir2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfDir_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfPnt2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfPnt_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfVec2d_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfVec_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfXYZ_0.cxx \
@top_srcdir@/drv/TColgp/TColgp_SequenceOfXY_0.cxx \
@top_srcdir@/drv/TopLoc/TopLoc_IndexedMapNodeOfIndexedMapOfLocation_0.cxx \
@top_srcdir@/drv/TopLoc/TopLoc_IndexedMapOfLocation_0.cxx \
@top_srcdir@/drv/TopLoc/TopLoc_MapIteratorOfMapOfLocation_0.cxx \
@top_srcdir@/drv/TopLoc/TopLoc_MapLocationHasher_0.cxx \
@top_srcdir@/drv/TopLoc/TopLoc_MapOfLocation_0.cxx \
@top_srcdir@/drv/TopLoc/TopLoc_StdMapNodeOfMapOfLocation_0.cxx \
@top_srcdir@/drv/gp/gp_VectorWithNullMagnitude_0.cxx \
@top_srcdir@/drv/math/math_Array1OfValueAndWeight_0.cxx \
@top_srcdir@/drv/math/math_NotSquare_0.cxx \
@top_srcdir@/drv/math/math_QuickSortOfValueAndWeight_0.cxx \
@top_srcdir@/drv/math/math_SingularMatrix_0.cxx \
@top_srcdir@/src/BSplCLib/BSplCLib.cxx \
@top_srcdir@/src/BSplCLib/BSplCLib_1.cxx \
@top_srcdir@/src/BSplCLib/BSplCLib_2.cxx \
@top_srcdir@/src/BSplCLib/BSplCLib_3.cxx \
@top_srcdir@/src/BSplCLib/BSplCLib_BzSyntaxes.cxx \
@top_srcdir@/src/BSplSLib/BSplSLib.cxx \
@top_srcdir@/src/BSplSLib/BSplSLib_BzSyntaxes.cxx \
@top_srcdir@/src/BVH/BVH.cxx \
@top_srcdir@/src/BVH/BVH_Properties.cxx \
@top_srcdir@/src/Bnd/Bnd_BoundSortBox.cxx \
@top_srcdir@/src/Bnd/Bnd_BoundSortBox2d.cxx \
@top_srcdir@/src/Bnd/Bnd_Box.cxx \
@top_srcdir@/src/Bnd/Bnd_Box2d.cxx \
@top_srcdir@/src/Bnd/Bnd_Sphere.cxx \
@top_srcdir@/src/CSLib/CSLib.cxx \
@top_srcdir@/src/CSLib/CSLib_Class2d.cxx \
@top_srcdir@/src/CSLib/CSLib_NormalPolyDef.cxx \
@top_srcdir@/src/Convert/Convert_CircleToBSplineCurve.cxx \
@top_srcdir@/src/Convert/Convert_CompBezierCurves2dToBSplineCurve2d.cxx \
@top_srcdir@/src/Convert/Convert_CompBezierCurvesToBSplineCurve.cxx \
@top_srcdir@/src/Convert/Convert_CompPolynomialToPoles.cxx \
@top_srcdir@/src/Convert/Convert_ConeToBSplineSurface.cxx \
@top_srcdir@/src/Convert/Convert_ConicToBSplineCurve.cxx \
@top_srcdir@/src/Convert/Convert_CylinderToBSplineSurface.cxx \
@top_srcdir@/src/Convert/Convert_ElementarySurfaceToBSplineSurface.cxx \
@top_srcdir@/src/Convert/Convert_EllipseToBSplineCurve.cxx \
@top_srcdir@/src/Convert/Convert_GridPolynomialToPoles.cxx \
@top_srcdir@/src/Convert/Convert_HyperbolaToBSplineCurve.cxx \
@top_srcdir@/src/Convert/Convert_ParabolaToBSplineCurve.cxx \
@top_srcdir@/src/Convert/Convert_PolynomialCosAndSin.cxx \
@top_srcdir@/src/Convert/Convert_SphereToBSplineSurface.cxx \
@top_srcdir@/src/Convert/Convert_TorusToBSplineSurface.cxx \
@top_srcdir@/src/ElCLib/ElCLib.cxx \
@top_srcdir@/src/ElSLib/ElSLib.cxx \
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
@top_srcdir@/src/PLib/PLib.cxx \
@top_srcdir@/src/PLib/PLib_Base.cxx \
@top_srcdir@/src/PLib/PLib_DoubleJacobiPolynomial.cxx \
@top_srcdir@/src/PLib/PLib_HermitJacobi.cxx \
@top_srcdir@/src/PLib/PLib_JacobiPolynomial.cxx \
@top_srcdir@/src/Poly/Poly.cxx \
@top_srcdir@/src/Poly/Poly_CoherentLink.cxx \
@top_srcdir@/src/Poly/Poly_CoherentNode.cxx \
@top_srcdir@/src/Poly/Poly_CoherentTriPtr.cxx \
@top_srcdir@/src/Poly/Poly_CoherentTriangle.cxx \
@top_srcdir@/src/Poly/Poly_CoherentTriangulation.cxx \
@top_srcdir@/src/Poly/Poly_Connect.cxx \
@top_srcdir@/src/Poly/Poly_MakeLoops.cxx \
@top_srcdir@/src/Poly/Poly_Polygon2D.cxx \
@top_srcdir@/src/Poly/Poly_Polygon3D.cxx \
@top_srcdir@/src/Poly/Poly_PolygonOnTriangulation.cxx \
@top_srcdir@/src/Poly/Poly_Triangle.cxx \
@top_srcdir@/src/Poly/Poly_Triangulation.cxx \
@top_srcdir@/src/Precision/Precision.cxx \
@top_srcdir@/src/TopLoc/TopLoc_Datum3D.cxx \
@top_srcdir@/src/TopLoc/TopLoc_ItemLocation.cxx \
@top_srcdir@/src/TopLoc/TopLoc_Location.cxx \
@top_srcdir@/src/TopLoc/TopLoc_SListNodeOfItemLocation.cxx \
@top_srcdir@/src/TopLoc/TopLoc_SListOfItemLocation.cxx \
@top_srcdir@/src/gp/gp.cxx \
@top_srcdir@/src/gp/gp_Ax1.cxx \
@top_srcdir@/src/gp/gp_Ax2.cxx \
@top_srcdir@/src/gp/gp_Ax22d.cxx \
@top_srcdir@/src/gp/gp_Ax2d.cxx \
@top_srcdir@/src/gp/gp_Ax3.cxx \
@top_srcdir@/src/gp/gp_Circ.cxx \
@top_srcdir@/src/gp/gp_Circ2d.cxx \
@top_srcdir@/src/gp/gp_Cone.cxx \
@top_srcdir@/src/gp/gp_Cylinder.cxx \
@top_srcdir@/src/gp/gp_Dir.cxx \
@top_srcdir@/src/gp/gp_Dir2d.cxx \
@top_srcdir@/src/gp/gp_Elips.cxx \
@top_srcdir@/src/gp/gp_Elips2d.cxx \
@top_srcdir@/src/gp/gp_GTrsf.cxx \
@top_srcdir@/src/gp/gp_GTrsf2d.cxx \
@top_srcdir@/src/gp/gp_Hypr.cxx \
@top_srcdir@/src/gp/gp_Hypr2d.cxx \
@top_srcdir@/src/gp/gp_Lin.cxx \
@top_srcdir@/src/gp/gp_Lin2d.cxx \
@top_srcdir@/src/gp/gp_Mat.cxx \
@top_srcdir@/src/gp/gp_Mat2d.cxx \
@top_srcdir@/src/gp/gp_Parab.cxx \
@top_srcdir@/src/gp/gp_Parab2d.cxx \
@top_srcdir@/src/gp/gp_Pln.cxx \
@top_srcdir@/src/gp/gp_Pnt.cxx \
@top_srcdir@/src/gp/gp_Pnt2d.cxx \
@top_srcdir@/src/gp/gp_Quaternion.cxx \
@top_srcdir@/src/gp/gp_Sphere.cxx \
@top_srcdir@/src/gp/gp_Torus.cxx \
@top_srcdir@/src/gp/gp_Trsf.cxx \
@top_srcdir@/src/gp/gp_Trsf2d.cxx \
@top_srcdir@/src/gp/gp_Vec.cxx \
@top_srcdir@/src/gp/gp_Vec2d.cxx \
@top_srcdir@/src/gp/gp_XY.cxx \
@top_srcdir@/src/gp/gp_XYZ.cxx \
@top_srcdir@/src/math/math.cxx \
@top_srcdir@/src/math/math_BFGS.cxx \
@top_srcdir@/src/math/math_BissecNewton.cxx \
@top_srcdir@/src/math/math_BracketMinimum.cxx \
@top_srcdir@/src/math/math_BracketedRoot.cxx \
@top_srcdir@/src/math/math_BrentMinimum.cxx \
@top_srcdir@/src/math/math_CompareOfValueAndWeight.cxx \
@top_srcdir@/src/math/math_ComputeGaussPointsAndWeights.cxx \
@top_srcdir@/src/math/math_ComputeKronrodPointsAndWeights.cxx \
@top_srcdir@/src/math/math_Crout.cxx \
@top_srcdir@/src/math/math_DirectPolynomialRoots.cxx \
@top_srcdir@/src/math/math_DoubleTab.cxx \
@top_srcdir@/src/math/math_EigenValuesSearcher.cxx \
@top_srcdir@/src/math/math_FRPR.cxx \
@top_srcdir@/src/math/math_Function.cxx \
@top_srcdir@/src/math/math_FunctionAllRoots.cxx \
@top_srcdir@/src/math/math_FunctionRoot.cxx \
@top_srcdir@/src/math/math_FunctionRoots.cxx \
@top_srcdir@/src/math/math_FunctionSample.cxx \
@top_srcdir@/src/math/math_FunctionSet.cxx \
@top_srcdir@/src/math/math_FunctionSetRoot.cxx \
@top_srcdir@/src/math/math_FunctionSetWithDerivatives.cxx \
@top_srcdir@/src/math/math_FunctionWithDerivative.cxx \
@top_srcdir@/src/math/math_Gauss.cxx \
@top_srcdir@/src/math/math_GaussLeastSquare.cxx \
@top_srcdir@/src/math/math_GaussMultipleIntegration.cxx \
@top_srcdir@/src/math/math_GaussSetIntegration.cxx \
@top_srcdir@/src/math/math_GaussSingleIntegration.cxx \
@top_srcdir@/src/math/math_GlobOptMin.cxx \
@top_srcdir@/src/math/math_Householder.cxx \
@top_srcdir@/src/math/math_IntegerVector.cxx \
@top_srcdir@/src/math/math_Jacobi.cxx \
@top_srcdir@/src/math/math_Kronrod.cxx \
@top_srcdir@/src/math/math_KronrodSingleIntegration.cxx \
@top_srcdir@/src/math/math_Matrix.cxx \
@top_srcdir@/src/math/math_Memory.cxx \
@top_srcdir@/src/math/math_MultipleVarFunction.cxx \
@top_srcdir@/src/math/math_MultipleVarFunctionWithGradient.cxx \
@top_srcdir@/src/math/math_MultipleVarFunctionWithHessian.cxx \
@top_srcdir@/src/math/math_NewtonFunctionRoot.cxx \
@top_srcdir@/src/math/math_NewtonFunctionSetRoot.cxx \
@top_srcdir@/src/math/math_NewtonMinimum.cxx \
@top_srcdir@/src/math/math_PSO.cxx \
@top_srcdir@/src/math/math_PSOParticlesPool.cxx \
@top_srcdir@/src/math/math_Powell.cxx \
@top_srcdir@/src/math/math_Recipes.cxx \
@top_srcdir@/src/math/math_SVD.cxx \
@top_srcdir@/src/math/math_TrigonometricFunctionRoots.cxx \
@top_srcdir@/src/math/math_Uzawa.cxx \
@top_srcdir@/src/math/math_ValueAndWeight.cxx \
@top_srcdir@/src/math/math_Vector.cxx

