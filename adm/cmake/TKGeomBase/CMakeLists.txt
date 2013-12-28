project(TKGeomBase)

if (WIN32)
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__ProjLib_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GeomProjLib_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GCPnts_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__CPnts_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__Approx_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__AppParCurves_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__FEmTool_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__AppCont_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__Extrema_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__IntAna_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__IntAna2d_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GeomConvert_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__AdvApp2Var_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GeomLib_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__Geom2dConvert_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__Hermit_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__BndLib_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__AppDef_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GeomTools_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GC_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__GCE2d_DLL" )
  list( APPEND TKGeomBase_PRECOMPILED_DEFS "-D__gce_DLL" )
  string( REGEX REPLACE ";" " " TKGeomBase_PRECOMPILED_DEFS "${TKGeomBase_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/ProjLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/ProjLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GeomProjLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GeomProjLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GCPnts" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GCPnts" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/CPnts" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/CPnts" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/Approx" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/Approx" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/AppParCurves" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/AppParCurves" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/FEmTool" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/FEmTool" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/AppCont" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/AppCont" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/Extrema" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/Extrema" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/IntAna" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/IntAna" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/IntAna2d" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/IntAna2d" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GeomConvert" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GeomConvert" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/AdvApp2Var" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/AdvApp2Var" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GeomLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GeomLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/Geom2dConvert" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/Geom2dConvert" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/Hermit" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/Hermit" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/BndLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/BndLib" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/AppDef" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/AppDef" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GeomTools" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GeomTools" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GC" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GC" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/GCE2d" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/GCE2d" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../drv/gce" )
  list( APPEND TKGeomBase_COMPILER_DIRECTORIES "../../../src/gce" )

if (WIN32)
else()
endif()

  list( APPEND TKGeomBase_USED_LIBS TKernel )
  list( APPEND TKGeomBase_USED_LIBS TKMath )
  list( APPEND TKGeomBase_USED_LIBS TKG2d )
  list( APPEND TKGeomBase_USED_LIBS TKG3d )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/ProjLib/ProjLib_HCompProjectedCurve_0.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../drv/ProjLib/ProjLib_HCompProjectedCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/ProjLib/ProjLib_HProjectedCurve_0.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../drv/ProjLib/ProjLib_HProjectedCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/ProjLib/ProjLib_HSequenceOfHSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../drv/ProjLib/ProjLib_HSequenceOfHSequenceOfPnt_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/ProjLib/ProjLib_SequenceNodeOfSequenceOfHSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../drv/ProjLib/ProjLib_SequenceNodeOfSequenceOfHSequenceOfPnt_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/ProjLib/ProjLib_SequenceOfHSequenceOfPnt_0.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../drv/ProjLib/ProjLib_SequenceOfHSequenceOfPnt_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_CompProjectedCurve.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_CompProjectedCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_ComputeApprox.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_ComputeApprox.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_ComputeApproxOnPolarSurface.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_ComputeApproxOnPolarSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_Cone.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_Cone.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_Cylinder.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_Cylinder.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_Plane.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_Plane.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_PrjFunc.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_PrjFunc.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_PrjResolve.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_PrjResolve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_ProjectOnPlane.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_ProjectOnPlane.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_ProjectOnSurface.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_ProjectOnSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_ProjectedCurve.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_ProjectedCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_Projector.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_Projector.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_Sphere.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_Sphere.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/ProjLib/ProjLib_Torus.cxx" )
  SOURCE_GROUP (ProjLib FILES "../../../src/ProjLib/ProjLib_Torus.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomProjLib/GeomProjLib.cxx" )
  SOURCE_GROUP (GeomProjLib FILES "../../../src/GeomProjLib/GeomProjLib.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCPnts/GCPnts_AbscissaPoint.cxx" )
  SOURCE_GROUP (GCPnts FILES "../../../src/GCPnts/GCPnts_AbscissaPoint.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCPnts/GCPnts_QuasiUniformAbscissa.cxx" )
  SOURCE_GROUP (GCPnts FILES "../../../src/GCPnts/GCPnts_QuasiUniformAbscissa.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCPnts/GCPnts_QuasiUniformDeflection.cxx" )
  SOURCE_GROUP (GCPnts FILES "../../../src/GCPnts/GCPnts_QuasiUniformDeflection.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCPnts/GCPnts_TangentialDeflection.cxx" )
  SOURCE_GROUP (GCPnts FILES "../../../src/GCPnts/GCPnts_TangentialDeflection.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCPnts/GCPnts_UniformAbscissa.cxx" )
  SOURCE_GROUP (GCPnts FILES "../../../src/GCPnts/GCPnts_UniformAbscissa.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCPnts/GCPnts_UniformDeflection.cxx" )
  SOURCE_GROUP (GCPnts FILES "../../../src/GCPnts/GCPnts_UniformDeflection.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/CPnts/CPnts_AbscissaPoint.cxx" )
  SOURCE_GROUP (CPnts FILES "../../../src/CPnts/CPnts_AbscissaPoint.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/CPnts/CPnts_MyGaussFunction.cxx" )
  SOURCE_GROUP (CPnts FILES "../../../src/CPnts/CPnts_MyGaussFunction.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/CPnts/CPnts_MyRootFunction.cxx" )
  SOURCE_GROUP (CPnts FILES "../../../src/CPnts/CPnts_MyRootFunction.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/CPnts/CPnts_UniformDeflection.cxx" )
  SOURCE_GROUP (CPnts FILES "../../../src/CPnts/CPnts_UniformDeflection.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_Array1OfAdHSurface_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_Array1OfAdHSurface_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_Array1OfGTrsf2d_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_Array1OfGTrsf2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_FitAndDivide2d_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_FitAndDivide2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_FitAndDivide_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_FitAndDivide_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_HArray1OfAdHSurface_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_HArray1OfAdHSurface_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_HArray1OfGTrsf2d_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_HArray1OfGTrsf2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_MyLeastSquareOfFitAndDivide2d_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_MyLeastSquareOfFitAndDivide2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_MyLeastSquareOfFitAndDivide_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_MyLeastSquareOfFitAndDivide_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_SequenceNodeOfSequenceOfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_SequenceNodeOfSequenceOfHArray1OfReal_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Approx/Approx_SequenceOfHArray1OfReal_0.cxx" )
  SOURCE_GROUP (Approx FILES "../../../drv/Approx/Approx_SequenceOfHArray1OfReal_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_Curve2d.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_Curve2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_Curve3d.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_Curve3d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_CurveOnSurface.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_CurveOnSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_CurvilinearParameter.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_CurvilinearParameter.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_CurvlinFunc.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_CurvlinFunc.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_MCurvesToBSpCurve.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_MCurvesToBSpCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_SameParameter.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_SameParameter.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_SweepApproximation.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_SweepApproximation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Approx/Approx_SweepFunction.cxx" )
  SOURCE_GROUP (Approx FILES "../../../src/Approx/Approx_SweepFunction.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_Array1OfConstraintCouple_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_Array1OfConstraintCouple_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_Array1OfMultiBSpCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_Array1OfMultiBSpCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_Array1OfMultiCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_Array1OfMultiCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_Array1OfMultiPoint_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_Array1OfMultiPoint_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_HArray1OfConstraintCouple_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_HArray1OfConstraintCouple_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_HArray1OfMultiBSpCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_HArray1OfMultiBSpCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_HArray1OfMultiCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_HArray1OfMultiCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_HArray1OfMultiPoint_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_HArray1OfMultiPoint_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_SequenceNodeOfSequenceOfMultiBSpCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_SequenceNodeOfSequenceOfMultiBSpCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_SequenceNodeOfSequenceOfMultiCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_SequenceNodeOfSequenceOfMultiCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_SequenceOfMultiBSpCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_SequenceOfMultiBSpCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppParCurves/AppParCurves_SequenceOfMultiCurve_0.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../drv/AppParCurves/AppParCurves_SequenceOfMultiCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppParCurves/AppParCurves.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../src/AppParCurves/AppParCurves.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppParCurves/AppParCurves_ConstraintCouple.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../src/AppParCurves/AppParCurves_ConstraintCouple.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppParCurves/AppParCurves_MultiBSpCurve.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../src/AppParCurves/AppParCurves_MultiBSpCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppParCurves/AppParCurves_MultiCurve.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../src/AppParCurves/AppParCurves_MultiCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppParCurves/AppParCurves_MultiPoint.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../src/AppParCurves/AppParCurves_MultiPoint.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppParCurves/AppParCurves_SmoothCriterion.cxx" )
  SOURCE_GROUP (AppParCurves FILES "../../../src/AppParCurves/AppParCurves_SmoothCriterion.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_AssemblyTable_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_AssemblyTable_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_HAssemblyTable_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_HAssemblyTable_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_ListIteratorOfListOfVectors_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_ListIteratorOfListOfVectors_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_ListNodeOfListOfVectors_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_ListNodeOfListOfVectors_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_ListOfVectors_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_ListOfVectors_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_SeqOfLinConstr_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_SeqOfLinConstr_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/FEmTool/FEmTool_SequenceNodeOfSeqOfLinConstr_0.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../drv/FEmTool/FEmTool_SequenceNodeOfSeqOfLinConstr_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_Assembly.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_Assembly.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_Curve.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_Curve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_ElementaryCriterion.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_ElementaryCriterion.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_ElementsOfRefMatrix.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_ElementsOfRefMatrix.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_LinearFlexion.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_LinearFlexion.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_LinearJerk.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_LinearJerk.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_LinearTension.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_LinearTension.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_ProfileMatrix.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_ProfileMatrix.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/FEmTool/FEmTool_SparseMatrix.cxx" )
  SOURCE_GROUP (FEmTool FILES "../../../src/FEmTool/FEmTool_SparseMatrix.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppCont/AppCont_FitFunction2d_0.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../drv/AppCont/AppCont_FitFunction2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppCont/AppCont_FitFunction_0.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../drv/AppCont/AppCont_FitFunction_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_ContMatrices.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_ContMatrices.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_ContMatrices_1.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_ContMatrices_1.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_ContMatrices_2.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_ContMatrices_2.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_ContMatrices_3.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_ContMatrices_3.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_ContMatrices_4.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_ContMatrices_4.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_Function.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_Function.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_Function2d.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_Function2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_FunctionTool.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_FunctionTool.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppCont/AppCont_FunctionTool2d.cxx" )
  SOURCE_GROUP (AppCont FILES "../../../src/AppCont/AppCont_FunctionTool2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array1OfPOnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array1OfPOnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array1OfPOnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array1OfPOnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array1OfPOnSurf_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array1OfPOnSurf_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array2OfPOnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array2OfPOnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array2OfPOnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array2OfPOnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array2OfPOnSurfParams_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array2OfPOnSurfParams_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_Array2OfPOnSurf_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_Array2OfPOnSurf_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCFOfECC2dOfExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCFOfECC2dOfExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCFOfECCOfExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCFOfECCOfExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCFOfELCC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCFOfELCC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCFOfELCCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCFOfELCCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCLocFOfLocECC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCLocFOfLocECC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCLocFOfLocECCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCLocFOfLocECCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCache2dOfExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCache2dOfExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_CCacheOfExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_CCacheOfExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ECC2dOfExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ECC2dOfExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ECCOfExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ECCOfExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ELCC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ELCC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ELCCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ELCCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ELPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ELPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ELPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ELPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_EPCOfELPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_EPCOfELPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_EPCOfELPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_EPCOfELPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_EPCOfExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_EPCOfExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_EPCOfExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_EPCOfExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_ExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_ExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray1OfPOnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray1OfPOnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray1OfPOnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray1OfPOnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray1OfPOnSurf_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray1OfPOnSurf_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray2OfPOnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray2OfPOnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray2OfPOnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray2OfPOnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray2OfPOnSurfParams_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray2OfPOnSurfParams_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_HArray2OfPOnSurf_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_HArray2OfPOnSurf_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LCCache2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LCCache2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LCCacheOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LCCacheOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocECC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocECC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocECCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocECCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocEPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocEPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocEPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocEPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_LocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_LocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_PCFOfEPCOfELPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_PCFOfEPCOfELPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_PCFOfEPCOfELPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_PCFOfEPCOfELPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_PCFOfEPCOfExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_PCFOfEPCOfExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_PCFOfEPCOfExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_PCFOfEPCOfExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_PCLocFOfLocEPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_PCLocFOfLocEPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_PCLocFOfLocEPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_PCLocFOfLocEPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_POnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_POnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_POnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_POnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfELPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfELPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfELPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfELPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPCOfPCFOfEPCOfExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPCOfPCLocFOfLocEPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPCOfPCLocFOfLocEPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPCOfPCLocFOfLocEPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPCOfPCLocFOfLocEPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfECC2dOfExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfECC2dOfExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfECCOfExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfECCOfExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfELCC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfELCC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfELCCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCFOfELCCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCLocFOfLocECC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCLocFOfLocECC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCLocFOfLocECCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SeqPOnCOfCCLocFOfLocECCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfELPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfELPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfELPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfELPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCFOfEPCOfExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCLocFOfLocEPCOfLocateExtPC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCLocFOfLocEPCOfLocateExtPC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCLocFOfLocEPCOfLocateExtPC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPCOfPCLocFOfLocEPCOfLocateExtPC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfECC2dOfExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfECC2dOfExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfECCOfExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfECCOfExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfELCC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfELCC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfELCCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCFOfELCCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCLocFOfLocECC2dOfLocateExtCC2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCLocFOfLocECC2dOfLocateExtCC2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCLocFOfLocECCOfLocateExtCC_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSeqPOnCOfCCLocFOfLocECCOfLocateExtCC_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSequenceOfPOnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSequenceOfPOnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSequenceOfPOnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSequenceOfPOnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceNodeOfSequenceOfPOnSurf_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceNodeOfSequenceOfPOnSurf_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceOfPOnCurv2d_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceOfPOnCurv2d_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceOfPOnCurv_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceOfPOnCurv_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/Extrema/Extrema_SequenceOfPOnSurf_0.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../drv/Extrema/Extrema_SequenceOfPOnSurf_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_Curve2dTool.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_Curve2dTool.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_CurveTool.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_CurveTool.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtCS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtCS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtElC.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtElC.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtElC2d.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtElC2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtElCS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtElCS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtElSS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtElSS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtPElC.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtPElC.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtPElC2d.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtPElC2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtPElS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtPElS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtPExtS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtPExtS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtPRevS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtPRevS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtPS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtPS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_ExtSS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_ExtSS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_FuncExtCS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_FuncExtCS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_FuncExtPS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_FuncExtPS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_FuncExtSS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_FuncExtSS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_GenExtCS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_GenExtCS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_GenExtPS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_GenExtPS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_GenExtSS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_GenExtSS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_GenLocateExtCS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_GenLocateExtCS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_GenLocateExtPS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_GenLocateExtPS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_GenLocateExtSS.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_GenLocateExtSS.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_POnSurf.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_POnSurf.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Extrema/Extrema_POnSurfParams.cxx" )
  SOURCE_GROUP (Extrema FILES "../../../src/Extrema/Extrema_POnSurfParams.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/IntAna/IntAna_ListIteratorOfListOfCurve_0.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../drv/IntAna/IntAna_ListIteratorOfListOfCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/IntAna/IntAna_ListNodeOfListOfCurve_0.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../drv/IntAna/IntAna_ListNodeOfListOfCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/IntAna/IntAna_ListOfCurve_0.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../drv/IntAna/IntAna_ListOfCurve_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_Curve.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_Curve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_Int3Pln.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_Int3Pln.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_IntConicQuad.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_IntConicQuad.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_IntLinTorus.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_IntLinTorus.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_IntQuadQuad.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_IntQuadQuad.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_QuadQuadGeo.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_QuadQuadGeo.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna/IntAna_Quadric.cxx" )
  SOURCE_GROUP (IntAna FILES "../../../src/IntAna/IntAna_Quadric.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_1.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_1.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_2.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_2.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_3.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_3.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_4.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_4.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_5.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_5.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_6.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_6.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_7.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_7.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_8.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_AnaIntersection_8.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_Conic.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_Conic.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_IntPoint.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_IntPoint.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/IntAna2d/IntAna2d_Outils.cxx" )
  SOURCE_GROUP (IntAna2d FILES "../../../src/IntAna2d/IntAna2d_Outils.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_1.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_1.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_ApproxCurve.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_ApproxCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_ApproxSurface.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_ApproxSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_BSplineCurveKnotSplitting.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_BSplineCurveKnotSplitting.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_BSplineCurveToBezierCurve.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_BSplineCurveToBezierCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_BSplineSurfaceKnotSplitting.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_BSplineSurfaceKnotSplitting.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_BSplineSurfaceToBezierSurface.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_BSplineSurfaceToBezierSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_CompBezierSurfacesToBSplineSurface.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_CompBezierSurfacesToBSplineSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomConvert/GeomConvert_CompCurveToBSplineCurve.cxx" )
  SOURCE_GROUP (GeomConvert FILES "../../../src/GeomConvert/GeomConvert_CompCurveToBSplineCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfSequenceOfNode_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfSequenceOfNode_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfSequenceOfPatch_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfSequenceOfPatch_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfSequenceOfStrip_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfSequenceOfStrip_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfStrip_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceNodeOfStrip_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceOfNode_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceOfNode_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceOfPatch_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceOfPatch_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceOfStrip_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_SequenceOfStrip_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AdvApp2Var/AdvApp2Var_Strip_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../drv/AdvApp2Var/AdvApp2Var_Strip_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_ApproxAFunc2Var.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_ApproxAFunc2Var.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_ApproxF2var.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_ApproxF2var.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Context.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Context.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Criterion.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Criterion.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_0.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_1.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_1.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_2.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_2.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_3.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_3.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_4.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_4.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_5.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_5.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_6.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_6.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Data_7.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Data_7.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Framework.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Framework.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Iso.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Iso.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_MathBase.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_MathBase.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_MathBase_mathinit.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_MathBase_mathinit.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Network.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Network.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Node.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Node.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_Patch.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_Patch.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_SysBase.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_SysBase.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AdvApp2Var/AdvApp2Var_SysBase_baseinit.cxx" )
  SOURCE_GROUP (AdvApp2Var FILES "../../../src/AdvApp2Var/AdvApp2Var_SysBase_baseinit.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/GeomLib/GeomLib_Array1OfMat_0.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../drv/GeomLib/GeomLib_Array1OfMat_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_Check2dBSplineCurve.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_Check2dBSplineCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_CheckBSplineCurve.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_CheckBSplineCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_DenominatorMultiplier.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_DenominatorMultiplier.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_Interpolate.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_Interpolate.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_IsPlanarSurface.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_IsPlanarSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_LogSample.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_LogSample.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_MakeCurvefromApprox.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_MakeCurvefromApprox.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_PolyFunc.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_PolyFunc.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomLib/GeomLib_Tool.cxx" )
  SOURCE_GROUP (GeomLib FILES "../../../src/GeomLib/GeomLib_Tool.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Geom2dConvert/Geom2dConvert.cxx" )
  SOURCE_GROUP (Geom2dConvert FILES "../../../src/Geom2dConvert/Geom2dConvert.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Geom2dConvert/Geom2dConvert_ApproxCurve.cxx" )
  SOURCE_GROUP (Geom2dConvert FILES "../../../src/Geom2dConvert/Geom2dConvert_ApproxCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Geom2dConvert/Geom2dConvert_BSplineCurveKnotSplitting.cxx" )
  SOURCE_GROUP (Geom2dConvert FILES "../../../src/Geom2dConvert/Geom2dConvert_BSplineCurveKnotSplitting.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Geom2dConvert/Geom2dConvert_BSplineCurveToBezierCurve.cxx" )
  SOURCE_GROUP (Geom2dConvert FILES "../../../src/Geom2dConvert/Geom2dConvert_BSplineCurveToBezierCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Geom2dConvert/Geom2dConvert_CompCurveToBSplineCurve.cxx" )
  SOURCE_GROUP (Geom2dConvert FILES "../../../src/Geom2dConvert/Geom2dConvert_CompCurveToBSplineCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/Hermit/Hermit.cxx" )
  SOURCE_GROUP (Hermit FILES "../../../src/Hermit/Hermit.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/BndLib/BndLib.cxx" )
  SOURCE_GROUP (BndLib FILES "../../../src/BndLib/BndLib.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/BndLib/BndLib_Add2dCurve.cxx" )
  SOURCE_GROUP (BndLib FILES "../../../src/BndLib/BndLib_Add2dCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/BndLib/BndLib_Add3dCurve.cxx" )
  SOURCE_GROUP (BndLib FILES "../../../src/BndLib/BndLib_Add3dCurve.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/BndLib/BndLib_AddSurface.cxx" )
  SOURCE_GROUP (BndLib FILES "../../../src/BndLib/BndLib_AddSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/BndLib/BndLib_Compute2d.cxx" )
  SOURCE_GROUP (BndLib FILES "../../../src/BndLib/BndLib_Compute2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/BndLib/BndLib_Compute3d.cxx" )
  SOURCE_GROUP (BndLib FILES "../../../src/BndLib/BndLib_Compute3d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_Array1OfMultiPointConstraint_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_Array1OfMultiPointConstraint_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_BSpGradient_BFGSOfMyBSplGradientOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_BSpParFunctionOfMyBSplGradientOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_BSpParLeastSquareOfMyBSplGradientOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_BSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_BSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_Compute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_Compute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_Gradient_BFGSOfMyGradientOfCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_Gradient_BFGSOfMyGradientOfCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_Gradient_BFGSOfMyGradientbisOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_Gradient_BFGSOfTheGradient_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_Gradient_BFGSOfTheGradient_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_HArray1OfMultiPointConstraint_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_HArray1OfMultiPointConstraint_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_MyBSplGradientOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_MyBSplGradientOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_MyCriterionOfTheVariational_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_MyCriterionOfTheVariational_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_MyGradientOfCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_MyGradientOfCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_MyGradientbisOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_MyGradientbisOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ParFunctionOfMyGradientOfCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ParFunctionOfMyGradientOfCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ParFunctionOfMyGradientbisOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ParFunctionOfMyGradientbisOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ParFunctionOfTheGradient_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ParFunctionOfTheGradient_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ParLeastSquareOfMyGradientOfCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ParLeastSquareOfMyGradientOfCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ParLeastSquareOfMyGradientbisOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ParLeastSquareOfTheGradient_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ParLeastSquareOfTheGradient_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ResConstraintOfMyGradientOfCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ResConstraintOfMyGradientOfCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ResConstraintOfMyGradientbisOfBSplineCompute_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ResConstraintOfMyGradientbisOfBSplineCompute_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_ResConstraintOfTheGradient_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_ResConstraintOfTheGradient_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_TheFunction_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_TheFunction_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_TheGradient_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_TheGradient_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_TheLeastSquares_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_TheLeastSquares_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_TheResol_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_TheResol_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../drv/AppDef/AppDef_TheVariational_0.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../drv/AppDef/AppDef_TheVariational_0.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppDef/AppDef_MultiLine.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../src/AppDef/AppDef_MultiLine.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppDef/AppDef_MultiPointConstraint.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../src/AppDef/AppDef_MultiPointConstraint.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/AppDef/AppDef_MyLineTool.cxx" )
  SOURCE_GROUP (AppDef FILES "../../../src/AppDef/AppDef_MyLineTool.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomTools/GeomTools.cxx" )
  SOURCE_GROUP (GeomTools FILES "../../../src/GeomTools/GeomTools.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomTools/GeomTools_Curve2dSet.cxx" )
  SOURCE_GROUP (GeomTools FILES "../../../src/GeomTools/GeomTools_Curve2dSet.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomTools/GeomTools_CurveSet.cxx" )
  SOURCE_GROUP (GeomTools FILES "../../../src/GeomTools/GeomTools_CurveSet.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomTools/GeomTools_SurfaceSet.cxx" )
  SOURCE_GROUP (GeomTools FILES "../../../src/GeomTools/GeomTools_SurfaceSet.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GeomTools/GeomTools_UndefinedTypeHandler.cxx" )
  SOURCE_GROUP (GeomTools FILES "../../../src/GeomTools/GeomTools_UndefinedTypeHandler.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeArcOfCircle.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeArcOfCircle.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeArcOfEllipse.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeArcOfEllipse.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeArcOfHyperbola.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeArcOfHyperbola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeArcOfParabola.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeArcOfParabola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeCircle.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeCircle.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeConicalSurface.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeConicalSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeCylindricalSurface.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeCylindricalSurface.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeEllipse.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeEllipse.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeHyperbola.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeHyperbola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeLine.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeLine.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeMirror.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeMirror.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakePlane.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakePlane.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeRotation.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeRotation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeScale.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeScale.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeSegment.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeSegment.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeTranslation.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeTranslation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeTrimmedCone.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeTrimmedCone.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_MakeTrimmedCylinder.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_MakeTrimmedCylinder.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GC/GC_Root.cxx" )
  SOURCE_GROUP (GC FILES "../../../src/GC/GC_Root.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeArcOfCircle.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeArcOfCircle.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeArcOfEllipse.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeArcOfEllipse.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeArcOfHyperbola.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeArcOfHyperbola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeArcOfParabola.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeArcOfParabola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeCircle.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeCircle.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeEllipse.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeEllipse.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeHyperbola.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeHyperbola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeLine.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeLine.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeMirror.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeMirror.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeParabola.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeParabola.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeRotation.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeRotation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeScale.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeScale.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeSegment.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeSegment.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_MakeTranslation.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_MakeTranslation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/GCE2d/GCE2d_Root.cxx" )
  SOURCE_GROUP (GCE2d FILES "../../../src/GCE2d/GCE2d_Root.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeCirc.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeCirc.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeCirc2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeCirc2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeCone.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeCone.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeCylinder.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeCylinder.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeDir.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeDir.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeDir2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeDir2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeElips.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeElips.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeElips2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeElips2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeHypr.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeHypr.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeHypr2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeHypr2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeLin.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeLin.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeLin2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeLin2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeMirror.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeMirror.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeMirror2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeMirror2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeParab.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeParab.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeParab2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeParab2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakePln.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakePln.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeRotation.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeRotation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeRotation2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeRotation2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeScale.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeScale.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeScale2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeScale2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeTranslation.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeTranslation.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_MakeTranslation2d.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_MakeTranslation2d.cxx")

  list( APPEND TKGeomBase_USED_SRCFILES "../../../src/gce/gce_Root.cxx" )
  SOURCE_GROUP (gce FILES "../../../src/gce/gce_Root.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKGeomBase)
 add_library( TKGeomBase SHARED ${TKGeomBase_USED_SRCFILES} )

 set_property(TARGET TKGeomBase PROPERTY FOLDER ModelingData)

 install( TARGETS TKGeomBase
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKGeomBase.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKGeomBase PROPERTIES COMPILE_FLAGS "${TKGeomBase_PRECOMPILED_DEFS}" )
 include_directories( ${TKGeomBase_COMPILER_DIRECTORIES} )
 target_link_libraries( TKGeomBase ${TKGeomBase_USED_LIBS} )
endif()
