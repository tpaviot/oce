project(TKGeomAlgo)

if (WIN32)
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Hatch_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GeomInt_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntStart_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntWalk_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntImp_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntCurveSurface_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntSurf_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntPatch_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Geom2dInt_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntImpParGen_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntRes2d_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntCurve_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__TopTrans_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Intf_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__ApproxInt_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GccAna_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GccEnt_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GccInt_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GccIter_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GccGeo_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__HatchGen_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Geom2dHatch_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Law_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__AppBlend_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Plate_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GeomPlate_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__LocalAnalysis_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GeomAPI_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__GeomFill_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Geom2dAPI_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__Geom2dGcc_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__FairCurve_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__NLPlate_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__IntPolyh_DLL" )
  list( APPEND TKGeomAlgo_PRECOMPILED_DEFS "-D__TopClass_DLL" )
  string( REGEX REPLACE ";" " " TKGeomAlgo_PRECOMPILED_DEFS "${TKGeomAlgo_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Hatch" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Hatch" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GeomInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GeomInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntStart" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntStart" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntWalk" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntWalk" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntImp" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntImp" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntCurveSurface" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntCurveSurface" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntSurf" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntSurf" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntPatch" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntPatch" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Geom2dInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Geom2dInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntImpParGen" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntImpParGen" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntRes2d" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntRes2d" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntCurve" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntCurve" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/TopTrans" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/TopTrans" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Intf" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Intf" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/ApproxInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/ApproxInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GccAna" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GccAna" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GccEnt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GccEnt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GccInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GccInt" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GccIter" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GccIter" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GccGeo" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GccGeo" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/HatchGen" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/HatchGen" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Geom2dHatch" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Geom2dHatch" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Law" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Law" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/AppBlend" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/AppBlend" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Plate" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Plate" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GeomPlate" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GeomPlate" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/LocalAnalysis" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/LocalAnalysis" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GeomAPI" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GeomAPI" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/GeomFill" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/GeomFill" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Geom2dAPI" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Geom2dAPI" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/Geom2dGcc" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/Geom2dGcc" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/FairCurve" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/FairCurve" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/NLPlate" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/NLPlate" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/IntPolyh" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/IntPolyh" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../drv/TopClass" )
  list( APPEND TKGeomAlgo_COMPILER_DIRECTORIES "../../../src/TopClass" )

if (WIN32)
else()
endif()

  list( APPEND TKGeomAlgo_USED_LIBS TKernel )
  list( APPEND TKGeomAlgo_USED_LIBS TKMath )
  list( APPEND TKGeomAlgo_USED_LIBS TKG3d )
  list( APPEND TKGeomAlgo_USED_LIBS TKG2d )
  list( APPEND TKGeomAlgo_USED_LIBS TKGeomBase )
  list( APPEND TKGeomAlgo_USED_LIBS TKBRep )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Hatch/Hatch_SequenceNodeOfSequenceOfLine_0.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../drv/Hatch/Hatch_SequenceNodeOfSequenceOfLine_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Hatch/Hatch_SequenceNodeOfSequenceOfParameter_0.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../drv/Hatch/Hatch_SequenceNodeOfSequenceOfParameter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Hatch/Hatch_SequenceOfLine_0.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../drv/Hatch/Hatch_SequenceOfLine_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Hatch/Hatch_SequenceOfParameter_0.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../drv/Hatch/Hatch_SequenceOfParameter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Hatch/Hatch_Hatcher.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../src/Hatch/Hatch_Hatcher.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Hatch/Hatch_Line.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../src/Hatch/Hatch_Line.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Hatch/Hatch_Parameter.cxx" )
  SOURCE_GROUP (Hatch FILES "../../../src/Hatch/Hatch_Parameter.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_MyBSplGradientOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_MyGradientOfTheComputeLineBezierOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_MyGradientbisOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_MyGradientbisOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ParFunctionOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ParFunctionOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ParLeastSquareOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ResConstraintOfMyGradientOfTheComputeLineBezierOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ResConstraintOfMyGradientbisOfTheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_SequenceNodeOfSequenceOfParameterAndOrientation_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_SequenceNodeOfSequenceOfParameterAndOrientation_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_SequenceOfParameterAndOrientation_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_SequenceOfParameterAndOrientation_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheComputeLineBezierOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheComputeLineBezierOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheComputeLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheComputeLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheImpPrmSvSurfacesOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheImpPrmSvSurfacesOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheInt2SOfThePrmPrmSvSurfacesOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheMultiLineOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheMultiLineOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheMultiLineToolOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheMultiLineToolOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_ThePrmPrmSvSurfacesOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_ThePrmPrmSvSurfacesOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_TheZerImpFuncOfTheImpPrmSvSurfacesOfWLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomInt/GeomInt_WLApprox_0.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../drv/GeomInt/GeomInt_WLApprox_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomInt/GeomInt_IntSS.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../src/GeomInt/GeomInt_IntSS.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomInt/GeomInt_IntSS_1.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../src/GeomInt/GeomInt_IntSS_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomInt/GeomInt_LineConstructor.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../src/GeomInt/GeomInt_LineConstructor.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomInt/GeomInt_LineTool.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../src/GeomInt/GeomInt_LineTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomInt/GeomInt_ParameterAndOrientation.cxx" )
  SOURCE_GROUP (GeomInt FILES "../../../src/GeomInt/GeomInt_ParameterAndOrientation.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntStart/IntStart_SITopolTool.cxx" )
  SOURCE_GROUP (IntStart FILES "../../../src/IntStart/IntStart_SITopolTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntImp/IntImp_ComputeTangence.cxx" )
  SOURCE_GROUP (IntImp FILES "../../../src/IntImp/IntImp_ComputeTangence.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_HInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_HInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceNodeOfSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceNodeOfSequenceOfPnt_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceNodeOfSequenceOfSeg_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceNodeOfSequenceOfSeg_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceOfPnt_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceOfPnt_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceOfSeg_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_SequenceOfSeg_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_TheCSFunctionOfHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_TheCSFunctionOfHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_TheExactHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_TheExactHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_TheHCurveTool_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_TheHCurveTool_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_TheInterferenceOfHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_TheInterferenceOfHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolygonOfHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolygonOfHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolygonToolOfHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolygonToolOfHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolyhedronOfHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolyhedronOfHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolyhedronToolOfHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_ThePolyhedronToolOfHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_TheQuadCurvExactHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_TheQuadCurvExactHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurveSurface/IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter_0.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../drv/IntCurveSurface/IntCurveSurface_TheQuadCurvFuncOfTheQuadCurvExactHInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurveSurface/IntCurveSurface_Intersection.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../src/IntCurveSurface/IntCurveSurface_Intersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurveSurface/IntCurveSurface_IntersectionPoint.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../src/IntCurveSurface/IntCurveSurface_IntersectionPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurveSurface/IntCurveSurface_IntersectionSegment.cxx" )
  SOURCE_GROUP (IntCurveSurface FILES "../../../src/IntCurveSurface/IntCurveSurface_IntersectionSegment.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_ListIteratorOfListOfPntOn2S_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_ListIteratorOfListOfPntOn2S_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_ListNodeOfListOfPntOn2S_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_ListNodeOfListOfPntOn2S_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_ListOfPntOn2S_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_ListOfPntOn2S_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfCouple_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfCouple_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfInteriorPoint_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfInteriorPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfPathPoint_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfPathPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfPntOn2S_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceNodeOfSequenceOfPntOn2S_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceOfCouple_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceOfCouple_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceOfInteriorPoint_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceOfInteriorPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceOfPathPoint_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceOfPathPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntSurf/IntSurf_SequenceOfPntOn2S_0.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../drv/IntSurf/IntSurf_SequenceOfPntOn2S_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_Couple.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_Couple.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_InteriorPoint.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_InteriorPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_InteriorPointTool.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_InteriorPointTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_LineOn2S.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_LineOn2S.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_PathPoint.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_PathPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_PathPointTool.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_PathPointTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_PntOn2S.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_PntOn2S.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_Quadric.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_Quadric.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_QuadricTool.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_QuadricTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntSurf/IntSurf_Transition.cxx" )
  SOURCE_GROUP (IntSurf FILES "../../../src/IntSurf/IntSurf_Transition.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_CSFunction_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_CSFunction_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_CurvIntSurf_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_CurvIntSurf_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfIWLineOfTheIWalking_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfLine_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfLine_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfPoint_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfSegmentOfTheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceNodeOfSequenceOfSegmentOfTheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceOfIWLineOfTheIWalking_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceOfIWLineOfTheIWalking_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceOfLine_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceOfLine_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceOfPathPointOfTheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceOfPathPointOfTheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceOfPoint_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceOfPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_SequenceOfSegmentOfTheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_SequenceOfSegmentOfTheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheFunctionOfTheInt2SOfThePWalkingInter_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheFunctionOfTheInt2SOfThePWalkingInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheIWLineOfTheIWalking_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheIWLineOfTheIWalking_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheIWalking_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheIWalking_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheInt2SOfThePWalkingInter_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheInt2SOfThePWalkingInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheInterfPolyhedron_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheInterfPolyhedron_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_ThePWalkingInter_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_ThePWalkingInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_ThePathPointOfTheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_ThePathPointOfTheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheSearchInside_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheSearchInside_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheSegmentOfTheSOnBounds_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheSegmentOfTheSOnBounds_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPatch/IntPatch_TheSurfFunction_0.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../drv/IntPatch/IntPatch_TheSurfFunction_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_ALine.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_ALine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_ALineToWLine.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_ALineToWLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_ArcFunction.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_ArcFunction.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_GLine.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_GLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_HCurve2dTool.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_HCurve2dTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_HInterTool.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_HInterTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_ImpImpIntersection.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_ImpImpIntersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_ImpPrmIntersection.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_ImpPrmIntersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_Intersection.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_Intersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_Line.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_Line.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_LineConstructor.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_LineConstructor.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_Point.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_Point.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_PolyArc.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_PolyArc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_PolyLine.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_PolyLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_Polygo.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_Polygo.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_Polyhedron.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_Polyhedron.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_PolyhedronTool.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_PolyhedronTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_PrmPrmIntersection.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_PrmPrmIntersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_PrmPrmIntersection_T3Bits.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_PrmPrmIntersection_T3Bits.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_RLine.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_RLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_RstInt.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_RstInt.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPatch/IntPatch_WLine.cxx" )
  SOURCE_GROUP (IntPatch FILES "../../../src/IntPatch/IntPatch_WLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_ExactIntersectionPointOfTheIntPCurvePCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_GInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_GInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_Geom2dCurveTool_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_Geom2dCurveTool_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_IntConicCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_IntConicCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_MyImpParToolOfTheIntersectorOfTheIntConicCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_PCLocFOfTheLocateExtPCOfTheProjPCurOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_PCLocFOfTheLocateExtPCOfTheProjPCurOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_SeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_SeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_SequenceNodeOfSeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_SequenceNodeOfSeqPCOfPCLocFOfTheLocateExtPCOfTheProjPCurOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheCurveLocatorOfTheProjPCurOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheDistBetweenPCurvesOfTheIntPCurvePCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheIntConicCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheIntConicCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheIntPCurvePCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheIntPCurvePCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheIntersectorOfTheIntConicCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheLocateExtPCOfTheProjPCurOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_ThePolygon2dOfTheIntPCurvePCurveOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dInt/Geom2dInt_TheProjPCurOfGInter_0.cxx" )
  SOURCE_GROUP (Geom2dInt FILES "../../../drv/Geom2dInt/Geom2dInt_TheProjPCurOfGInter_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntImpParGen/IntImpParGen.cxx" )
  SOURCE_GROUP (IntImpParGen FILES "../../../src/IntImpParGen/IntImpParGen.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntImpParGen/IntImpParGen_ImpTool.cxx" )
  SOURCE_GROUP (IntImpParGen FILES "../../../src/IntImpParGen/IntImpParGen_ImpTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntImpParGen/IntImpParGen_Tool.cxx" )
  SOURCE_GROUP (IntImpParGen FILES "../../../src/IntImpParGen/IntImpParGen_Tool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntRes2d/IntRes2d_SequenceNodeOfSequenceOfIntersectionPoint_0.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../drv/IntRes2d/IntRes2d_SequenceNodeOfSequenceOfIntersectionPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntRes2d/IntRes2d_SequenceNodeOfSequenceOfIntersectionSegment_0.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../drv/IntRes2d/IntRes2d_SequenceNodeOfSequenceOfIntersectionSegment_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntRes2d/IntRes2d_SequenceOfIntersectionPoint_0.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../drv/IntRes2d/IntRes2d_SequenceOfIntersectionPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntRes2d/IntRes2d_SequenceOfIntersectionSegment_0.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../drv/IntRes2d/IntRes2d_SequenceOfIntersectionSegment_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntRes2d/IntRes2d_Domain.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../src/IntRes2d/IntRes2d_Domain.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntRes2d/IntRes2d_Intersection.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../src/IntRes2d/IntRes2d_Intersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntRes2d/IntRes2d_IntersectionPoint.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../src/IntRes2d/IntRes2d_IntersectionPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntRes2d/IntRes2d_IntersectionSegment.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../src/IntRes2d/IntRes2d_IntersectionSegment.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntRes2d/IntRes2d_Transition.cxx" )
  SOURCE_GROUP (IntRes2d FILES "../../../src/IntRes2d/IntRes2d_Transition.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurve/IntCurve_IntImpConicParConic_0.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../drv/IntCurve/IntCurve_IntImpConicParConic_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntCurve/IntCurve_MyImpParToolOfIntImpConicParConic_0.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../drv/IntCurve/IntCurve_MyImpParToolOfIntImpConicParConic_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_IConicTool.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_IConicTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_IntConicConic.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_IntConicConic.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_IntConicConic_1.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_IntConicConic_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_IntConicConic_Tool.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_IntConicConic_Tool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_PConic.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_PConic.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_PConicTool.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_PConicTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntCurve/IntCurve_ProjectOnPConicTool.cxx" )
  SOURCE_GROUP (IntCurve FILES "../../../src/IntCurve/IntCurve_ProjectOnPConicTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/TopTrans/TopTrans_Array2OfOrientation_0.cxx" )
  SOURCE_GROUP (TopTrans FILES "../../../drv/TopTrans/TopTrans_Array2OfOrientation_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/TopTrans/TopTrans_CurveTransition.cxx" )
  SOURCE_GROUP (TopTrans FILES "../../../src/TopTrans/TopTrans_CurveTransition.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/TopTrans/TopTrans_SurfaceTransition.cxx" )
  SOURCE_GROUP (TopTrans FILES "../../../src/TopTrans/TopTrans_SurfaceTransition.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_Array1OfLin_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_Array1OfLin_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_SeqOfSectionLine_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_SeqOfSectionLine_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_SeqOfSectionPoint_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_SeqOfSectionPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_SeqOfTangentZone_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_SeqOfTangentZone_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_SequenceNodeOfSeqOfSectionLine_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_SequenceNodeOfSeqOfSectionLine_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_SequenceNodeOfSeqOfSectionPoint_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_SequenceNodeOfSeqOfSectionPoint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Intf/Intf_SequenceNodeOfSeqOfTangentZone_0.cxx" )
  SOURCE_GROUP (Intf FILES "../../../drv/Intf/Intf_SequenceNodeOfSeqOfTangentZone_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_Interference.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_Interference.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_InterferencePolygon2d.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_InterferencePolygon2d.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_Polygon2d.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_Polygon2d.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_SectionLine.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_SectionLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_SectionPoint.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_SectionPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_TangentZone.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_TangentZone.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Intf/Intf_Tool.cxx" )
  SOURCE_GROUP (Intf FILES "../../../src/Intf/Intf_Tool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/ApproxInt/ApproxInt_SvSurfaces.cxx" )
  SOURCE_GROUP (ApproxInt FILES "../../../src/ApproxInt/ApproxInt_SvSurfaces.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GccAna/GccAna_NoSolution_0.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../drv/GccAna/GccAna_NoSolution_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_1.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_10.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_10.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_11.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_11.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_2.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_2.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_3.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_3.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_4.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_4.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_5.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_5.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_6.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_6.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_7.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_7.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_8.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_8.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanOn_9.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanOn_9.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanRad.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanRad.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanRad_1.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanRad_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanRad_2.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanRad_2.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanRad_3.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanRad_3.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanRad_4.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanRad_4.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d2TanRad_5.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d2TanRad_5.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_1.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_2.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_2.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_3.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_3.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_4.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_4.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_5.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_5.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_6.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_6.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_7.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_7.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_8.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_8.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2d3Tan_9.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2d3Tan_9.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dBisec.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dBisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanCen.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanCen.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanOnRad.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanOnRad.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_1.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_2.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_2.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_3.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_3.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_4.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_4.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_5.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Circ2dTanOnRad_5.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_CircLin2dBisec.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_CircLin2dBisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_CircPnt2dBisec.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_CircPnt2dBisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Lin2d2Tan.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Lin2d2Tan.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Lin2dBisec.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Lin2dBisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Lin2dTanObl.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Lin2dTanObl.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Lin2dTanPar.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Lin2dTanPar.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Lin2dTanPer.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Lin2dTanPer.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_LinPnt2dBisec.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_LinPnt2dBisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccAna/GccAna_Pnt2dBisec.cxx" )
  SOURCE_GROUP (GccAna FILES "../../../src/GccAna/GccAna_Pnt2dBisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GccEnt/GccEnt_Array1OfPosition_0.cxx" )
  SOURCE_GROUP (GccEnt FILES "../../../drv/GccEnt/GccEnt_Array1OfPosition_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GccEnt/GccEnt_BadQualifier_0.cxx" )
  SOURCE_GROUP (GccEnt FILES "../../../drv/GccEnt/GccEnt_BadQualifier_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccEnt/GccEnt.cxx" )
  SOURCE_GROUP (GccEnt FILES "../../../src/GccEnt/GccEnt.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccEnt/GccEnt_QualifiedCirc.cxx" )
  SOURCE_GROUP (GccEnt FILES "../../../src/GccEnt/GccEnt_QualifiedCirc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccEnt/GccEnt_QualifiedLin.cxx" )
  SOURCE_GROUP (GccEnt FILES "../../../src/GccEnt/GccEnt_QualifiedLin.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_BCirc.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_BCirc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_BElips.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_BElips.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_BHyper.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_BHyper.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_BLine.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_BLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_BParab.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_BParab.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_BPoint.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_BPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GccInt/GccInt_Bisec.cxx" )
  SOURCE_GROUP (GccInt FILES "../../../src/GccInt/GccInt_Bisec.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GccIter/GccIter_IsParallel_0.cxx" )
  SOURCE_GROUP (GccIter FILES "../../../drv/GccIter/GccIter_IsParallel_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/HatchGen/HatchGen_Domains_0.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../drv/HatchGen/HatchGen_Domains_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/HatchGen/HatchGen_PointsOnElement_0.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../drv/HatchGen/HatchGen_PointsOnElement_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/HatchGen/HatchGen_PointsOnHatching_0.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../drv/HatchGen/HatchGen_PointsOnHatching_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/HatchGen/HatchGen_SequenceNodeOfDomains_0.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../drv/HatchGen/HatchGen_SequenceNodeOfDomains_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/HatchGen/HatchGen_SequenceNodeOfPointsOnElement_0.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../drv/HatchGen/HatchGen_SequenceNodeOfPointsOnElement_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/HatchGen/HatchGen_SequenceNodeOfPointsOnHatching_0.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../drv/HatchGen/HatchGen_SequenceNodeOfPointsOnHatching_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/HatchGen/HatchGen_Domain.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../src/HatchGen/HatchGen_Domain.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/HatchGen/HatchGen_IntersectionPoint.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../src/HatchGen/HatchGen_IntersectionPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/HatchGen/HatchGen_PointOnElement.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../src/HatchGen/HatchGen_PointOnElement.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/HatchGen/HatchGen_PointOnHatching.cxx" )
  SOURCE_GROUP (HatchGen FILES "../../../src/HatchGen/HatchGen_PointOnHatching.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_ClassifierOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_ClassifierOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapIteratorOfHatchingsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapIteratorOfHatchingsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapIteratorOfMapOfElementsOfElementsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapIteratorOfMapOfElementsOfElementsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapNodeOfHatchingsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapNodeOfHatchingsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapNodeOfMapOfElementsOfElementsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_DataMapNodeOfMapOfElementsOfElementsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_ElementOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_ElementOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_ElementsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_ElementsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_FClass2dOfClassifierOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_FClass2dOfClassifierOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_Hatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_Hatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_HatchingOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_HatchingOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_HatchingsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_HatchingsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dHatch/Geom2dHatch_MapOfElementsOfElementsOfHatcher_0.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../drv/Geom2dHatch/Geom2dHatch_MapOfElementsOfElementsOfHatcher_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dHatch/Geom2dHatch_Intersector.cxx" )
  SOURCE_GROUP (Geom2dHatch FILES "../../../src/Geom2dHatch/Geom2dHatch_Intersector.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Law/Law_Laws_0.cxx" )
  SOURCE_GROUP (Law FILES "../../../drv/Law/Law_Laws_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Law/Law_ListIteratorOfLaws_0.cxx" )
  SOURCE_GROUP (Law FILES "../../../drv/Law/Law_ListIteratorOfLaws_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Law/Law_ListNodeOfLaws_0.cxx" )
  SOURCE_GROUP (Law FILES "../../../drv/Law/Law_ListNodeOfLaws_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_BSpFunc.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_BSpFunc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_BSpline.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_BSpline.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_BSplineKnotSplitting.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_BSplineKnotSplitting.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_Composite.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_Composite.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_Constant.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_Constant.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_Function.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_Function.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_Interpol.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_Interpol.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_Interpolate.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_Interpolate.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_Linear.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_Linear.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Law/Law_S.cxx" )
  SOURCE_GROUP (Law FILES "../../../src/Law/Law_S.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/AppBlend/AppBlend_Approx.cxx" )
  SOURCE_GROUP (AppBlend FILES "../../../src/AppBlend/AppBlend_Approx.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/AppBlend/AppBlend_Debug.cxx" )
  SOURCE_GROUP (AppBlend FILES "../../../src/AppBlend/AppBlend_Debug.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_Array1OfPinpointConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_Array1OfPinpointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_HArray1OfPinpointConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_HArray1OfPinpointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_SequenceNodeOfSequenceOfLinearScalarConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_SequenceNodeOfSequenceOfLinearScalarConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_SequenceNodeOfSequenceOfLinearXYZConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_SequenceNodeOfSequenceOfLinearXYZConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_SequenceNodeOfSequenceOfPinpointConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_SequenceNodeOfSequenceOfPinpointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_SequenceOfLinearScalarConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_SequenceOfLinearScalarConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_SequenceOfLinearXYZConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_SequenceOfLinearXYZConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Plate/Plate_SequenceOfPinpointConstraint_0.cxx" )
  SOURCE_GROUP (Plate FILES "../../../drv/Plate/Plate_SequenceOfPinpointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_D1.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_D1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_D2.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_D2.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_D3.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_D3.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_FreeGtoCConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_FreeGtoCConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_GlobalTranslationConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_GlobalTranslationConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_GtoCConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_GtoCConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_LineConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_LineConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_LinearScalarConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_LinearScalarConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_LinearXYZConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_LinearXYZConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_PinpointConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_PinpointConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_PlaneConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_PlaneConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_Plate.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_Plate.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Plate/Plate_SampledCurveConstraint.cxx" )
  SOURCE_GROUP (Plate FILES "../../../src/Plate/Plate_SampledCurveConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_Array1OfHCurveOnSurface_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_Array1OfHCurveOnSurface_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_Array1OfSequenceOfReal_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_Array1OfSequenceOfReal_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_HArray1OfHCurveOnSurface_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_HArray1OfHCurveOnSurface_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_HArray1OfSequenceOfReal_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_HArray1OfSequenceOfReal_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_HSequenceOfCurveConstraint_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_HSequenceOfCurveConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_HSequenceOfPointConstraint_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_HSequenceOfPointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_SequenceNodeOfSequenceOfAij_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_SequenceNodeOfSequenceOfAij_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_SequenceNodeOfSequenceOfCurveConstraint_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_SequenceNodeOfSequenceOfCurveConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_SequenceNodeOfSequenceOfPointConstraint_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_SequenceNodeOfSequenceOfPointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_SequenceOfAij_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_SequenceOfAij_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_SequenceOfCurveConstraint_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_SequenceOfCurveConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomPlate/GeomPlate_SequenceOfPointConstraint_0.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../drv/GeomPlate/GeomPlate_SequenceOfPointConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_Aij.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_Aij.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_BuildAveragePlane.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_BuildAveragePlane.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_BuildPlateSurface.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_BuildPlateSurface.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_CurveConstraint.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_CurveConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_MakeApprox.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_MakeApprox.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_PlateG0Criterion.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_PlateG0Criterion.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_PlateG1Criterion.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_PlateG1Criterion.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_PointConstraint.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_PointConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomPlate/GeomPlate_Surface.cxx" )
  SOURCE_GROUP (GeomPlate FILES "../../../src/GeomPlate/GeomPlate_Surface.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/LocalAnalysis/LocalAnalysis.cxx" )
  SOURCE_GROUP (LocalAnalysis FILES "../../../src/LocalAnalysis/LocalAnalysis.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/LocalAnalysis/LocalAnalysis_CurveContinuity.cxx" )
  SOURCE_GROUP (LocalAnalysis FILES "../../../src/LocalAnalysis/LocalAnalysis_CurveContinuity.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/LocalAnalysis/LocalAnalysis_SurfaceContinuity.cxx" )
  SOURCE_GROUP (LocalAnalysis FILES "../../../src/LocalAnalysis/LocalAnalysis_SurfaceContinuity.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_ExtremaCurveCurve.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_ExtremaCurveCurve.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_ExtremaCurveSurface.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_ExtremaCurveSurface.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_ExtremaSurfaceSurface.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_ExtremaSurfaceSurface.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_IntCS.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_IntCS.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_IntSS.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_IntSS.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_Interpolate.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_Interpolate.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_PointsToBSpline.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_PointsToBSpline.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_PointsToBSplineSurface.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_PointsToBSplineSurface.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_ProjectPointOnCurve.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_ProjectPointOnCurve.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomAPI/GeomAPI_ProjectPointOnSurf.cxx" )
  SOURCE_GROUP (GeomAPI FILES "../../../src/GeomAPI/GeomAPI_ProjectPointOnSurf.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_AppSurf_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_AppSurf_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_AppSweep_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_AppSweep_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_Array1OfLocationLaw_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_Array1OfLocationLaw_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_Array1OfSectionLaw_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_Array1OfSectionLaw_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_HArray1OfLocationLaw_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_HArray1OfLocationLaw_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_HArray1OfSectionLaw_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_HArray1OfSectionLaw_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_HSequenceOfAx2_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_HSequenceOfAx2_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_SequenceNodeOfSequenceOfAx2_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_SequenceNodeOfSequenceOfAx2_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_SequenceNodeOfSequenceOfTrsf_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_SequenceNodeOfSequenceOfTrsf_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_SequenceOfAx2_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_SequenceOfAx2_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/GeomFill/GeomFill_SequenceOfTrsf_0.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../drv/GeomFill/GeomFill_SequenceOfTrsf_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_BSplineCurves.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_BSplineCurves.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_BezierCurves.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_BezierCurves.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_BoundWithSurf.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_BoundWithSurf.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Boundary.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Boundary.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_CircularBlendFunc.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_CircularBlendFunc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_ConstantBiNormal.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_ConstantBiNormal.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_ConstrainedFilling.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_ConstrainedFilling.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Coons.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Coons.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_CoonsAlgPatch.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_CoonsAlgPatch.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_CornerState.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_CornerState.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_CorrectedFrenet.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_CorrectedFrenet.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_CurveAndTrihedron.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_CurveAndTrihedron.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Curved.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Curved.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Darboux.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Darboux.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_DegeneratedBound.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_DegeneratedBound.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_DiscreteTrihedron.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_DiscreteTrihedron.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_DraftTrihedron.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_DraftTrihedron.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_EvolvedSection.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_EvolvedSection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Filling.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Filling.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Fixed.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Fixed.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Frenet.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Frenet.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_FunctionDraft.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_FunctionDraft.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_FunctionGuide.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_FunctionGuide.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Generator.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Generator.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_GuideTrihedronAC.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_GuideTrihedronAC.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_GuideTrihedronPlan.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_GuideTrihedronPlan.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Line.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Line.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_LocFunction.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_LocFunction.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_LocationDraft.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_LocationDraft.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_LocationGuide.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_LocationGuide.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_LocationLaw.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_LocationLaw.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_NSections.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_NSections.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Pipe.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Pipe.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_PlanFunc.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_PlanFunc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_PolynomialConvertor.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_PolynomialConvertor.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Profiler.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Profiler.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_QuasiAngularConvertor.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_QuasiAngularConvertor.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SectionGenerator.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SectionGenerator.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SectionLaw.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SectionLaw.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SectionPlacement.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SectionPlacement.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SimpleBound.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SimpleBound.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SnglrFunc.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SnglrFunc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Stretch.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Stretch.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Sweep.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Sweep.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SweepFunction.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SweepFunction.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_SweepSectionGenerator.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_SweepSectionGenerator.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_Tensor.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_Tensor.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_TgtField.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_TgtField.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_TgtOnCoons.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_TgtOnCoons.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_TrihedronLaw.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_TrihedronLaw.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_TrihedronWithGuide.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_TrihedronWithGuide.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/GeomFill/GeomFill_UniformSection.cxx" )
  SOURCE_GROUP (GeomFill FILES "../../../src/GeomFill/GeomFill_UniformSection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dAPI/Geom2dAPI_ExtremaCurveCurve.cxx" )
  SOURCE_GROUP (Geom2dAPI FILES "../../../src/Geom2dAPI/Geom2dAPI_ExtremaCurveCurve.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dAPI/Geom2dAPI_InterCurveCurve.cxx" )
  SOURCE_GROUP (Geom2dAPI FILES "../../../src/Geom2dAPI/Geom2dAPI_InterCurveCurve.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dAPI/Geom2dAPI_Interpolate.cxx" )
  SOURCE_GROUP (Geom2dAPI FILES "../../../src/Geom2dAPI/Geom2dAPI_Interpolate.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dAPI/Geom2dAPI_PointsToBSpline.cxx" )
  SOURCE_GROUP (Geom2dAPI FILES "../../../src/Geom2dAPI/Geom2dAPI_PointsToBSpline.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dAPI/Geom2dAPI_ProjectPointOnCurve.cxx" )
  SOURCE_GROUP (Geom2dAPI FILES "../../../src/Geom2dAPI/Geom2dAPI_ProjectPointOnCurve.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCirCuOfMyL2d2Tan_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCirCuOfMyL2d2Tan_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuCuCuOfMyC2d3Tan_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuCuCuOfMyC2d3Tan_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuCuOfMyL2d2Tan_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuCuOfMyL2d2Tan_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuCuOnCuOfMyC2d2TanOn_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuCuOnCuOfMyC2d2TanOn_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuPtOfMyL2d2Tan_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTCuPtOfMyL2d2Tan_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTOblOfMyL2dTanObl_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_FuncTOblOfMyL2dTanObl_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyC2d2TanOn_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyC2d2TanOn_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyC2d3Tan_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyC2d3Tan_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2d2TanOn_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2d2TanOn_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2d2TanRad_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2d2TanRad_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2dTanCen_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2dTanCen_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2dTanOnRad_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCirc2dTanOnRad_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCurveTool_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyCurveTool_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyL2d2Tan_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyL2d2Tan_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyL2dTanObl_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyL2dTanObl_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/Geom2dGcc/Geom2dGcc_MyQCurve_0.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../drv/Geom2dGcc/Geom2dGcc_MyQCurve_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2d2TanOn.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2d2TanOn.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2d2TanRad.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2d2TanRad.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2d3Tan.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2d3Tan.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2dTanCen.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2dTanCen.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2dTanOnRad.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Circ2dTanOnRad.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_CurveTool.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_CurveTool.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Lin2d2Tan.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Lin2d2Tan.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_Lin2dTanObl.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_Lin2dTanObl.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/Geom2dGcc/Geom2dGcc_QualifiedCurve.cxx" )
  SOURCE_GROUP (Geom2dGcc FILES "../../../src/Geom2dGcc/Geom2dGcc_QualifiedCurve.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_Batten.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_Batten.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_BattenLaw.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_BattenLaw.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_DistributionOfEnergy.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_DistributionOfEnergy.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_DistributionOfJerk.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_DistributionOfJerk.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_DistributionOfSagging.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_DistributionOfSagging.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_DistributionOfTension.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_DistributionOfTension.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_Energy.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_Energy.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_EnergyOfBatten.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_EnergyOfBatten.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_EnergyOfMVC.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_EnergyOfMVC.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_MinimalVariation.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_MinimalVariation.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/FairCurve/FairCurve_Newton.cxx" )
  SOURCE_GROUP (FairCurve FILES "../../../src/FairCurve/FairCurve_Newton.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/NLPlate/NLPlate_SequenceNodeOfSequenceOfHGPPConstraint_0.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../drv/NLPlate/NLPlate_SequenceNodeOfSequenceOfHGPPConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/NLPlate/NLPlate_SequenceOfHGPPConstraint_0.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../drv/NLPlate/NLPlate_SequenceOfHGPPConstraint_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/NLPlate/NLPlate_StackIteratorOfStackOfPlate_0.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../drv/NLPlate/NLPlate_StackIteratorOfStackOfPlate_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/NLPlate/NLPlate_StackNodeOfStackOfPlate_0.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../drv/NLPlate/NLPlate_StackNodeOfStackOfPlate_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/NLPlate/NLPlate_StackOfPlate_0.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../drv/NLPlate/NLPlate_StackOfPlate_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HGPPConstraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HGPPConstraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG0Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG0Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG0G1Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG0G1Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG0G2Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG0G2Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG0G3Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG0G3Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG1Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG1Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG2Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG2Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_HPG3Constraint.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_HPG3Constraint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/NLPlate/NLPlate_NLPlate.cxx" )
  SOURCE_GROUP (NLPlate FILES "../../../src/NLPlate/NLPlate_NLPlate.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPolyh/IntPolyh_SeqOfStartPoints_0.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../drv/IntPolyh/IntPolyh_SeqOfStartPoints_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../drv/IntPolyh/IntPolyh_SequenceNodeOfSeqOfStartPoints_0.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../drv/IntPolyh/IntPolyh_SequenceNodeOfSeqOfStartPoints_0.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_Couple.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_Couple.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_Edge.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_Edge.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_Intersection.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_Intersection.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_Intersection_1.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_Intersection_1.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_MaillageAffinage.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_MaillageAffinage.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_Point.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_Point.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_SectionLine.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_SectionLine.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_StartPoint.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_StartPoint.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/IntPolyh/IntPolyh_Triangle.cxx" )
  SOURCE_GROUP (IntPolyh FILES "../../../src/IntPolyh/IntPolyh_Triangle.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/TopClass/TopClass.cxx" )
  SOURCE_GROUP (TopClass FILES "../../../src/TopClass/TopClass.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/TopClass/TopClass_Intersection3d.cxx" )
  SOURCE_GROUP (TopClass FILES "../../../src/TopClass/TopClass_Intersection3d.cxx")

  list( APPEND TKGeomAlgo_USED_SRCFILES "../../../src/TopClass/TopClass_SolidExplorer.cxx" )
  SOURCE_GROUP (TopClass FILES "../../../src/TopClass/TopClass_SolidExplorer.cxx")

if (WIN32)
else()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKGeomAlgo)
 add_library( TKGeomAlgo SHARED ${TKGeomAlgo_USED_SRCFILES} )

 set_property(TARGET TKGeomAlgo PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKGeomAlgo
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKGeomAlgo.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKGeomAlgo PROPERTIES COMPILE_FLAGS "${TKGeomAlgo_PRECOMPILED_DEFS}" )
 include_directories( ${TKGeomAlgo_COMPILER_DIRECTORIES} )
 target_link_libraries( TKGeomAlgo ${TKGeomAlgo_USED_LIBS} )
endif()
