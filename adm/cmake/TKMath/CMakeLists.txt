project(TKMath)

if (WIN32)
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__math_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__ElCLib_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__ElSLib_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__BSplCLib_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__BSplSLib_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__PLib_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__Precision_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__GeomAbs_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__Poly_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__CSLib_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__Convert_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__Bnd_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__gp_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__TColgp_DLL" )
  list( APPEND TKMath_PRECOMPILED_DEFS "-D__TopLoc_DLL" )
  string( REGEX REPLACE ";" " " TKMath_PRECOMPILED_DEFS "${TKMath_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKMath_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/math" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/math" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/ElCLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/ElCLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/ElSLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/ElSLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/BSplCLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/BSplCLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/BSplSLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/BSplSLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/PLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/PLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/Precision" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/Precision" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/GeomAbs" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/GeomAbs" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/Poly" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/Poly" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/CSLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/CSLib" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/Convert" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/Convert" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/Bnd" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/Bnd" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/gp" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/gp" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/TColgp" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/TColgp" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../drv/TopLoc" )
  list( APPEND TKMath_COMPILER_DIRECTORIES "../../../src/TopLoc" )

if (WIN32)
else()
endif()

  list( APPEND TKMath_USED_LIBS TKernel )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_Array1OfValueAndWeight_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_Array1OfValueAndWeight_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_DoubleTabOfReal_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_DoubleTabOfReal_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_NotSquare_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_NotSquare_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_QuickSortOfValueAndWeight_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_QuickSortOfValueAndWeight_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_SingleTabOfInteger_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_SingleTabOfInteger_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_SingleTabOfReal_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_SingleTabOfReal_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/math/math_SingularMatrix_0.cxx" )
  SOURCE_GROUP (math FILES "../../../drv/math/math_SingularMatrix_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_BFGS.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_BFGS.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_BissecNewton.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_BissecNewton.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_BracketMinimum.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_BracketMinimum.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_BracketedRoot.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_BracketedRoot.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_BrentMinimum.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_BrentMinimum.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_CompareOfValueAndWeight.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_CompareOfValueAndWeight.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_ComputeGaussPointsAndWeights.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_ComputeGaussPointsAndWeights.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_ComputeKronrodPointsAndWeights.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_ComputeKronrodPointsAndWeights.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Crout.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Crout.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_DirectPolynomialRoots.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_DirectPolynomialRoots.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_EigenValuesSearcher.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_EigenValuesSearcher.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FRPR.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FRPR.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Function.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Function.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionAllRoots.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionAllRoots.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionRoot.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionRoot.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionRoots.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionRoots.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionSample.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionSample.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionSet.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionSet.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionSetRoot.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionSetRoot.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionSetWithDerivatives.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionSetWithDerivatives.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_FunctionWithDerivative.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_FunctionWithDerivative.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Gauss.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Gauss.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_GaussLeastSquare.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_GaussLeastSquare.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_GaussMultipleIntegration.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_GaussMultipleIntegration.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_GaussSetIntegration.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_GaussSetIntegration.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_GaussSingleIntegration.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_GaussSingleIntegration.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Householder.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Householder.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_IntegerRandom.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_IntegerRandom.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_IntegerVector.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_IntegerVector.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Jacobi.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Jacobi.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Kronrod.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Kronrod.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_KronrodSingleIntegration.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_KronrodSingleIntegration.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Matrix.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Matrix.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Memory.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Memory.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_MultipleVarFunction.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_MultipleVarFunction.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_MultipleVarFunctionWithGradient.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_MultipleVarFunctionWithGradient.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_MultipleVarFunctionWithHessian.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_MultipleVarFunctionWithHessian.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_NewtonFunctionRoot.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_NewtonFunctionRoot.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_NewtonFunctionSetRoot.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_NewtonFunctionSetRoot.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_NewtonMinimum.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_NewtonMinimum.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Powell.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Powell.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_RealRandom.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_RealRandom.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Recipes.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Recipes.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_SVD.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_SVD.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_TrigonometricFunctionRoots.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_TrigonometricFunctionRoots.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Uzawa.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Uzawa.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_ValueAndWeight.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_ValueAndWeight.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/math/math_Vector.cxx" )
  SOURCE_GROUP (math FILES "../../../src/math/math_Vector.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/ElCLib/ElCLib.cxx" )
  SOURCE_GROUP (ElCLib FILES "../../../src/ElCLib/ElCLib.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/ElSLib/ElSLib.cxx" )
  SOURCE_GROUP (ElSLib FILES "../../../src/ElSLib/ElSLib.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplCLib/BSplCLib.cxx" )
  SOURCE_GROUP (BSplCLib FILES "../../../src/BSplCLib/BSplCLib.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplCLib/BSplCLib_1.cxx" )
  SOURCE_GROUP (BSplCLib FILES "../../../src/BSplCLib/BSplCLib_1.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplCLib/BSplCLib_2.cxx" )
  SOURCE_GROUP (BSplCLib FILES "../../../src/BSplCLib/BSplCLib_2.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplCLib/BSplCLib_3.cxx" )
  SOURCE_GROUP (BSplCLib FILES "../../../src/BSplCLib/BSplCLib_3.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplCLib/BSplCLib_BzSyntaxes.cxx" )
  SOURCE_GROUP (BSplCLib FILES "../../../src/BSplCLib/BSplCLib_BzSyntaxes.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplSLib/BSplSLib.cxx" )
  SOURCE_GROUP (BSplSLib FILES "../../../src/BSplSLib/BSplSLib.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/BSplSLib/BSplSLib_BzSyntaxes.cxx" )
  SOURCE_GROUP (BSplSLib FILES "../../../src/BSplSLib/BSplSLib_BzSyntaxes.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/PLib/PLib.cxx" )
  SOURCE_GROUP (PLib FILES "../../../src/PLib/PLib.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/PLib/PLib_Base.cxx" )
  SOURCE_GROUP (PLib FILES "../../../src/PLib/PLib_Base.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/PLib/PLib_DoubleJacobiPolynomial.cxx" )
  SOURCE_GROUP (PLib FILES "../../../src/PLib/PLib_DoubleJacobiPolynomial.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/PLib/PLib_HermitJacobi.cxx" )
  SOURCE_GROUP (PLib FILES "../../../src/PLib/PLib_HermitJacobi.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/PLib/PLib_JacobiPolynomial.cxx" )
  SOURCE_GROUP (PLib FILES "../../../src/PLib/PLib_JacobiPolynomial.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Precision/Precision.cxx" )
  SOURCE_GROUP (Precision FILES "../../../src/Precision/Precision.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Poly/Poly_Array1OfTriangle_0.cxx" )
  SOURCE_GROUP (Poly FILES "../../../drv/Poly/Poly_Array1OfTriangle_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Poly/Poly_HArray1OfTriangle_0.cxx" )
  SOURCE_GROUP (Poly FILES "../../../drv/Poly/Poly_HArray1OfTriangle_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_CoherentLink.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_CoherentLink.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_CoherentNode.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_CoherentNode.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_CoherentTriPtr.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_CoherentTriPtr.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_CoherentTriangle.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_CoherentTriangle.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_CoherentTriangulation.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_CoherentTriangulation.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_Connect.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_Connect.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_MakeLoops.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_MakeLoops.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_Polygon2D.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_Polygon2D.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_Polygon3D.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_Polygon3D.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_PolygonOnTriangulation.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_PolygonOnTriangulation.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_Triangle.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_Triangle.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Poly/Poly_Triangulation.cxx" )
  SOURCE_GROUP (Poly FILES "../../../src/Poly/Poly_Triangulation.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/CSLib/CSLib.cxx" )
  SOURCE_GROUP (CSLib FILES "../../../src/CSLib/CSLib.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/CSLib/CSLib_Class2d.cxx" )
  SOURCE_GROUP (CSLib FILES "../../../src/CSLib/CSLib_Class2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/CSLib/CSLib_NormalPolyDef.cxx" )
  SOURCE_GROUP (CSLib FILES "../../../src/CSLib/CSLib_NormalPolyDef.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Convert/Convert_SequenceNodeOfSequenceOfArray1OfPoles_0.cxx" )
  SOURCE_GROUP (Convert FILES "../../../drv/Convert/Convert_SequenceNodeOfSequenceOfArray1OfPoles_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Convert/Convert_SequenceOfArray1OfPoles_0.cxx" )
  SOURCE_GROUP (Convert FILES "../../../drv/Convert/Convert_SequenceOfArray1OfPoles_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_CircleToBSplineCurve.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_CircleToBSplineCurve.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_CompBezierCurves2dToBSplineCurve2d.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_CompBezierCurves2dToBSplineCurve2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_CompBezierCurvesToBSplineCurve.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_CompBezierCurvesToBSplineCurve.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_CompPolynomialToPoles.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_CompPolynomialToPoles.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_ConeToBSplineSurface.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_ConeToBSplineSurface.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_ConicToBSplineCurve.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_ConicToBSplineCurve.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_CylinderToBSplineSurface.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_CylinderToBSplineSurface.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_ElementarySurfaceToBSplineSurface.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_ElementarySurfaceToBSplineSurface.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_EllipseToBSplineCurve.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_EllipseToBSplineCurve.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_GridPolynomialToPoles.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_GridPolynomialToPoles.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_HyperbolaToBSplineCurve.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_HyperbolaToBSplineCurve.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_ParabolaToBSplineCurve.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_ParabolaToBSplineCurve.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_PolynomialCosAndSin.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_PolynomialCosAndSin.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_SphereToBSplineSurface.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_SphereToBSplineSurface.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Convert/Convert_TorusToBSplineSurface.cxx" )
  SOURCE_GROUP (Convert FILES "../../../src/Convert/Convert_TorusToBSplineSurface.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_Array1OfBox2d_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_Array1OfBox2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_Array1OfBox_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_Array1OfBox_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_Array1OfSphere_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_Array1OfSphere_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_B2d_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_B2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_B2f_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_B2f_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_B3d_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_B3d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_B3f_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_B3f_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_HArray1OfBox2d_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_HArray1OfBox2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_HArray1OfBox_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_HArray1OfBox_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_HArray1OfSphere_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_HArray1OfSphere_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_SeqOfBox_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_SeqOfBox_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/Bnd/Bnd_SequenceNodeOfSeqOfBox_0.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../drv/Bnd/Bnd_SequenceNodeOfSeqOfBox_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Bnd/Bnd_BoundSortBox.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../src/Bnd/Bnd_BoundSortBox.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Bnd/Bnd_BoundSortBox2d.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../src/Bnd/Bnd_BoundSortBox2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Bnd/Bnd_Box.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../src/Bnd/Bnd_Box.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Bnd/Bnd_Box2d.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../src/Bnd/Bnd_Box2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/Bnd/Bnd_Sphere.cxx" )
  SOURCE_GROUP (Bnd FILES "../../../src/Bnd/Bnd_Sphere.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/gp/gp_VectorWithNullMagnitude_0.cxx" )
  SOURCE_GROUP (gp FILES "../../../drv/gp/gp_VectorWithNullMagnitude_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Ax1.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Ax1.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Ax2.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Ax2.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Ax22d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Ax22d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Ax2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Ax2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Ax3.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Ax3.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Circ.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Circ.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Circ2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Circ2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Cone.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Cone.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Cylinder.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Cylinder.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Dir.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Dir.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Dir2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Dir2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Elips.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Elips.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Elips2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Elips2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_GTrsf.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_GTrsf.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_GTrsf2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_GTrsf2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Hypr.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Hypr.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Hypr2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Hypr2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Lin.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Lin.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Lin2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Lin2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Mat.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Mat.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Mat2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Mat2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Parab.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Parab.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Parab2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Parab2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Pln.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Pln.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Pnt.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Pnt.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Pnt2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Pnt2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Quaternion.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Quaternion.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Sphere.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Sphere.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Torus.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Torus.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Trsf.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Trsf.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Trsf2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Trsf2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Vec.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Vec.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_Vec2d.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_Vec2d.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_XY.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_XY.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/gp/gp_XYZ.cxx" )
  SOURCE_GROUP (gp FILES "../../../src/gp/gp_XYZ.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfLin2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfLin2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array1OfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array1OfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfLin2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfLin2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_Array2OfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_Array2OfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_DataMapIteratorOfDataMapOfIntegerCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_DataMapIteratorOfDataMapOfIntegerCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_DataMapNodeOfDataMapOfIntegerCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_DataMapNodeOfDataMapOfIntegerCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_DataMapOfIntegerCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_DataMapOfIntegerCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfLin2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfLin2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray1OfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray1OfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfCirc2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfCirc2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfLin2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfLin2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HArray2OfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HArray2OfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_HSequenceOfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_HSequenceOfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfArray1OfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceNodeOfSequenceOfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfArray1OfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfArray1OfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfDir2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfDir2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfDir_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfDir_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfPnt2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfPnt2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfPnt_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfPnt_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfVec2d_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfVec2d_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfVec_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfVec_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfXYZ_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfXYZ_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TColgp/TColgp_SequenceOfXY_0.cxx" )
  SOURCE_GROUP (TColgp FILES "../../../drv/TColgp/TColgp_SequenceOfXY_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_IndexedMapNodeOfIndexedMapOfLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_IndexedMapNodeOfIndexedMapOfLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_IndexedMapOfLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_IndexedMapOfLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_MapIteratorOfMapOfLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_MapIteratorOfMapOfLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_MapLocationHasher_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_MapLocationHasher_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_MapOfLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_MapOfLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_SListNodeOfSListOfItemLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_SListNodeOfSListOfItemLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_SListOfItemLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_SListOfItemLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../drv/TopLoc/TopLoc_StdMapNodeOfMapOfLocation_0.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../drv/TopLoc/TopLoc_StdMapNodeOfMapOfLocation_0.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/TopLoc/TopLoc_Datum3D.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../src/TopLoc/TopLoc_Datum3D.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/TopLoc/TopLoc_ItemLocation.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../src/TopLoc/TopLoc_ItemLocation.cxx")

  list( APPEND TKMath_USED_SRCFILES "../../../src/TopLoc/TopLoc_Location.cxx" )
  SOURCE_GROUP (TopLoc FILES "../../../src/TopLoc/TopLoc_Location.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKMath)
 add_library( TKMath SHARED ${TKMath_USED_SRCFILES} )

 set_property(TARGET TKMath PROPERTY FOLDER FoundationClasses)

 install( TARGETS TKMath
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKMath.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKMath PROPERTIES COMPILE_FLAGS "${TKMath_PRECOMPILED_DEFS}" )
 include_directories( ${TKMath_COMPILER_DIRECTORIES} )
 target_link_libraries( TKMath ${TKMath_USED_LIBS} )
endif()
