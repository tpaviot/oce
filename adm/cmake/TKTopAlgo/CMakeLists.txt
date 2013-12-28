project(TKTopAlgo)

if (WIN32)
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__IntCurvesFace_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__MAT_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__MAT2d_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__Bisector_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepMAT2d_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepCheck_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepBndLib_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepExtrema_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepClass_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepClass3d_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepLib_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepGProp_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepIntCurveSurface_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepTopAdaptor_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepBuilderAPI_DLL" )
  list( APPEND TKTopAlgo_PRECOMPILED_DEFS "-D__BRepApprox_DLL" )
  string( REGEX REPLACE ";" " " TKTopAlgo_PRECOMPILED_DEFS "${TKTopAlgo_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/IntCurvesFace" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/IntCurvesFace" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/MAT" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/MAT" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/MAT2d" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/MAT2d" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/Bisector" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/Bisector" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepMAT2d" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepMAT2d" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepCheck" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepCheck" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepBndLib" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepBndLib" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepExtrema" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepExtrema" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepClass" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepClass" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepClass3d" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepClass3d" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepLib" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepLib" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepGProp" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepGProp" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepIntCurveSurface" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepIntCurveSurface" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepTopAdaptor" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepTopAdaptor" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepBuilderAPI" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepBuilderAPI" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../drv/BRepApprox" )
  list( APPEND TKTopAlgo_COMPILER_DIRECTORIES "../../../src/BRepApprox" )

if (WIN32)
else()
endif()

  list( APPEND TKTopAlgo_USED_LIBS TKMath )
  list( APPEND TKTopAlgo_USED_LIBS TKernel )
  list( APPEND TKTopAlgo_USED_LIBS TKG2d )
  list( APPEND TKTopAlgo_USED_LIBS TKG3d )
  list( APPEND TKTopAlgo_USED_LIBS TKGeomBase )
  list( APPEND TKTopAlgo_USED_LIBS TKBRep )
  list( APPEND TKTopAlgo_USED_LIBS TKGeomAlgo )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/IntCurvesFace/IntCurvesFace_Intersector.cxx" )
  SOURCE_GROUP (IntCurvesFace FILES "../../../src/IntCurvesFace/IntCurvesFace_Intersector.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/IntCurvesFace/IntCurvesFace_ShapeIntersector.cxx" )
  SOURCE_GROUP (IntCurvesFace FILES "../../../src/IntCurvesFace/IntCurvesFace_ShapeIntersector.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerArc_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerArc_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerBasicElt_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerBisector_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerBisector_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerNode_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerNode_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerArc_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerArc_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerBasicElt_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerBisector_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerBisector_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerNode_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerNode_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapOfIntegerArc_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapOfIntegerArc_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapOfIntegerBasicElt_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapOfIntegerBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapOfIntegerBisector_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapOfIntegerBisector_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_DataMapOfIntegerNode_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_DataMapOfIntegerNode_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_ListOfBisector_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_ListOfBisector_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_ListOfEdge_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_ListOfEdge_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_SequenceNodeOfSequenceOfArc_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_SequenceNodeOfSequenceOfArc_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_SequenceNodeOfSequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_SequenceNodeOfSequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_SequenceOfArc_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_SequenceOfArc_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_SequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_SequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_TListNodeOfListOfBisector_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_TListNodeOfListOfBisector_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT/MAT_TListNodeOfListOfEdge_0.cxx" )
  SOURCE_GROUP (MAT FILES "../../../drv/MAT/MAT_TListNodeOfListOfEdge_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_Arc.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_Arc.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_BasicElt.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_BasicElt.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_Bisector.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_Bisector.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_Edge.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_Edge.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_Graph.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_Graph.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_Node.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_Node.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT/MAT_Zone.cxx" )
  SOURCE_GROUP (MAT FILES "../../../src/MAT/MAT_Zone.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_Array2OfConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_Array2OfConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfBiIntInteger_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfBiIntInteger_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfBiIntSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfBiIntSequenceOfInteger_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerBisec_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerBisec_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerPnt2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerPnt2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerSequenceOfConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerSequenceOfConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfBiIntInteger_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfBiIntInteger_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfBiIntSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfBiIntSequenceOfInteger_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerBisec_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerBisec_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerPnt2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerPnt2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerSequenceOfConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerSequenceOfConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerVec2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerVec2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfBiIntInteger_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfBiIntInteger_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfBiIntSequenceOfInteger_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfBiIntSequenceOfInteger_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerBisec_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerBisec_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerPnt2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerPnt2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerSequenceOfConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerSequenceOfConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerVec2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_DataMapOfIntegerVec2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_Mat2d_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_Mat2d_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfSequenceOfCurve_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfSequenceOfCurve_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfSequenceOfGeometry_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfSequenceOfGeometry_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_SequenceOfConnexion_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_SequenceOfConnexion_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_SequenceOfSequenceOfCurve_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_SequenceOfSequenceOfCurve_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/MAT2d/MAT2d_SequenceOfSequenceOfGeometry_0.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../drv/MAT2d/MAT2d_SequenceOfSequenceOfGeometry_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_BiInt.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_BiInt.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_Circuit.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_Circuit.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_Connexion.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_Connexion.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_CutCurve.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_CutCurve.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_MapBiIntHasher.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_MapBiIntHasher.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_MiniPath.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_MiniPath.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_SketchExplorer.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_SketchExplorer.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/MAT2d/MAT2d_Tool2d.cxx" )
  SOURCE_GROUP (MAT2d FILES "../../../src/MAT2d/MAT2d_Tool2d.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_Bisec.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_Bisec.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_BisecAna.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_BisecAna.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_BisecCC.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_BisecCC.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_BisecPC.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_BisecPC.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_Curve.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_Curve.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_FunctionH.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_FunctionH.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_FunctionInter.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_FunctionInter.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_Inter.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_Inter.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_PointOnBis.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_PointOnBis.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/Bisector/Bisector_PolyBis.cxx" )
  SOURCE_GROUP (Bisector FILES "../../../src/Bisector/Bisector_PolyBis.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_BisectingLocus_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_BisectingLocus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapIteratorOfDataMapOfBasicEltShape_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapIteratorOfDataMapOfBasicEltShape_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapIteratorOfDataMapOfShapeSequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapIteratorOfDataMapOfShapeSequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapNodeOfDataMapOfBasicEltShape_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapNodeOfDataMapOfBasicEltShape_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapNodeOfDataMapOfShapeSequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapNodeOfDataMapOfShapeSequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapOfBasicEltShape_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapOfBasicEltShape_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapOfShapeSequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_DataMapOfShapeSequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_SequenceNodeOfSequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_SequenceNodeOfSequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepMAT2d/BRepMAT2d_SequenceOfBasicElt_0.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../drv/BRepMAT2d/BRepMAT2d_SequenceOfBasicElt_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepMAT2d/BRepMAT2d_Explorer.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../src/BRepMAT2d/BRepMAT2d_Explorer.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepMAT2d/BRepMAT2d_LinkTopoBilo.cxx" )
  SOURCE_GROUP (BRepMAT2d FILES "../../../src/BRepMAT2d/BRepMAT2d_LinkTopoBilo.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_DataMapIteratorOfDataMapOfShapeListOfStatus_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_DataMapIteratorOfDataMapOfShapeListOfStatus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_DataMapIteratorOfDataMapOfShapeResult_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_DataMapIteratorOfDataMapOfShapeResult_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_DataMapNodeOfDataMapOfShapeListOfStatus_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_DataMapNodeOfDataMapOfShapeListOfStatus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_DataMapNodeOfDataMapOfShapeResult_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_DataMapNodeOfDataMapOfShapeResult_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_DataMapOfShapeListOfStatus_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_DataMapOfShapeListOfStatus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_DataMapOfShapeResult_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_DataMapOfShapeResult_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_ListIteratorOfListOfStatus_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_ListIteratorOfListOfStatus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_ListNodeOfListOfStatus_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_ListNodeOfListOfStatus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepCheck/BRepCheck_ListOfStatus_0.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../drv/BRepCheck/BRepCheck_ListOfStatus_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Analyzer.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Analyzer.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Edge.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Edge.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Face.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Face.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Result.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Result.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Shell.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Shell.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Vertex.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Vertex.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepCheck/BRepCheck_Wire.cxx" )
  SOURCE_GROUP (BRepCheck FILES "../../../src/BRepCheck/BRepCheck_Wire.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBndLib/BRepBndLib.cxx" )
  SOURCE_GROUP (BRepBndLib FILES "../../../src/BRepBndLib/BRepBndLib.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepExtrema/BRepExtrema_UnCompatibleShape_0.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../drv/BRepExtrema/BRepExtrema_UnCompatibleShape_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_DistShapeShape.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_DistShapeShape.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_DistanceSS.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_DistanceSS.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_ExtCC.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_ExtCC.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_ExtCF.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_ExtCF.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_ExtFF.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_ExtFF.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_ExtPC.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_ExtPC.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_ExtPF.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_ExtPF.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepExtrema/BRepExtrema_Poly.cxx" )
  SOURCE_GROUP (BRepExtrema FILES "../../../src/BRepExtrema/BRepExtrema_Poly.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass/BRepClass_FClass2dOfFClassifier_0.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../drv/BRepClass/BRepClass_FClass2dOfFClassifier_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass/BRepClass_FClassifier_0.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../drv/BRepClass/BRepClass_FClassifier_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass/BRepClass_FacePassiveClassifier_0.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../drv/BRepClass/BRepClass_FacePassiveClassifier_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass/BRepClass_Edge.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../src/BRepClass/BRepClass_Edge.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass/BRepClass_FaceClassifier.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../src/BRepClass/BRepClass_FaceClassifier.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass/BRepClass_FaceExplorer.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../src/BRepClass/BRepClass_FaceExplorer.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass/BRepClass_Intersector.cxx" )
  SOURCE_GROUP (BRepClass FILES "../../../src/BRepClass/BRepClass_Intersector.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass3d/BRepClass3d_DataMapIteratorOfMapOfInter_0.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../drv/BRepClass3d/BRepClass3d_DataMapIteratorOfMapOfInter_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass3d/BRepClass3d_DataMapNodeOfMapOfInter_0.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../drv/BRepClass3d/BRepClass3d_DataMapNodeOfMapOfInter_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass3d/BRepClass3d_MapOfInter_0.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../drv/BRepClass3d/BRepClass3d_MapOfInter_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepClass3d/BRepClass3d_SolidPassiveClassifier_0.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../drv/BRepClass3d/BRepClass3d_SolidPassiveClassifier_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass3d/BRepClass3d.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../src/BRepClass3d/BRepClass3d.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass3d/BRepClass3d_Intersector3d.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../src/BRepClass3d/BRepClass3d_Intersector3d.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass3d/BRepClass3d_SClassifier.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../src/BRepClass3d/BRepClass3d_SClassifier.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass3d/BRepClass3d_SolidClassifier.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../src/BRepClass3d/BRepClass3d_SolidClassifier.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepClass3d/BRepClass3d_SolidExplorer.cxx" )
  SOURCE_GROUP (BRepClass3d FILES "../../../src/BRepClass3d/BRepClass3d_SolidExplorer.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_Command.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_Command.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_FindSurface.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_FindSurface.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_FuseEdges.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_FuseEdges.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeEdge.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeEdge.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeEdge2d.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeEdge2d.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeFace.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeFace.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakePolygon.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakePolygon.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeShape.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeShape.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeShell.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeShell.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeSolid.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeSolid.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeVertex.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeVertex.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeWire.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeWire.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepLib/BRepLib_MakeWire_1.cxx" )
  SOURCE_GROUP (BRepLib FILES "../../../src/BRepLib/BRepLib_MakeWire_1.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepGProp/BRepGProp_Cinert_0.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../drv/BRepGProp/BRepGProp_Cinert_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepGProp/BRepGProp_Sinert_0.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../drv/BRepGProp/BRepGProp_Sinert_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepGProp/BRepGProp_TFunctionOfVinertGK_0.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../drv/BRepGProp/BRepGProp_TFunctionOfVinertGK_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepGProp/BRepGProp_UFunctionOfVinertGK_0.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../drv/BRepGProp/BRepGProp_UFunctionOfVinertGK_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepGProp/BRepGProp_VinertGK_0.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../drv/BRepGProp/BRepGProp_VinertGK_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepGProp/BRepGProp_Vinert_0.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../drv/BRepGProp/BRepGProp_Vinert_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepGProp/BRepGProp.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../src/BRepGProp/BRepGProp.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepGProp/BRepGProp_Domain.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../src/BRepGProp/BRepGProp_Domain.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepGProp/BRepGProp_EdgeTool.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../src/BRepGProp/BRepGProp_EdgeTool.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepGProp/BRepGProp_Face.cxx" )
  SOURCE_GROUP (BRepGProp FILES "../../../src/BRepGProp/BRepGProp_Face.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepIntCurveSurface/BRepIntCurveSurface_Inter.cxx" )
  SOURCE_GROUP (BRepIntCurveSurface FILES "../../../src/BRepIntCurveSurface/BRepIntCurveSurface_Inter.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepTopAdaptor/BRepTopAdaptor_DataMapIteratorOfMapOfShapeTool_0.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../drv/BRepTopAdaptor/BRepTopAdaptor_DataMapIteratorOfMapOfShapeTool_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepTopAdaptor/BRepTopAdaptor_DataMapNodeOfMapOfShapeTool_0.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../drv/BRepTopAdaptor/BRepTopAdaptor_DataMapNodeOfMapOfShapeTool_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepTopAdaptor/BRepTopAdaptor_MapOfShapeTool_0.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../drv/BRepTopAdaptor/BRepTopAdaptor_MapOfShapeTool_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_FClass2d.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_FClass2d.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_HVertex.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_HVertex.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_Tool.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_Tool.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_TopolTool.cxx" )
  SOURCE_GROUP (BRepTopAdaptor FILES "../../../src/BRepTopAdaptor/BRepTopAdaptor_TopolTool.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Collect.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Collect.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Command.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Command.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Copy.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Copy.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_FindPlane.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_FindPlane.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_GTransform.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_GTransform.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeEdge.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeEdge.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeEdge2d.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeEdge2d.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeFace.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeFace.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakePolygon.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakePolygon.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeShape.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeShape.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeShell.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeShell.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeSolid.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeSolid.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeVertex.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeVertex.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeWire.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_MakeWire.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_ModifyShape.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_ModifyShape.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_NurbsConvert.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_NurbsConvert.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Sewing.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Sewing.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Transform.cxx" )
  SOURCE_GROUP (BRepBuilderAPI FILES "../../../src/BRepBuilderAPI/BRepBuilderAPI_Transform.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ApproxLine_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ApproxLine_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_Approx_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_Approx_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_MyBSplGradientOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_MyBSplGradientOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_MyGradientOfTheComputeLineBezierOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_MyGradientOfTheComputeLineBezierOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_MyGradientbisOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_MyGradientbisOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_SurfaceTool_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_SurfaceTool_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheComputeLineBezierOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheComputeLineBezierOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheComputeLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheComputeLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheImpPrmSvSurfacesOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheImpPrmSvSurfacesOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheMultiLineOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheMultiLineOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheMultiLineToolOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheMultiLineToolOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_ThePrmPrmSvSurfacesOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_ThePrmPrmSvSurfacesOfApprox_0.cxx")

  list( APPEND TKTopAlgo_USED_SRCFILES "../../../drv/BRepApprox/BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox_0.cxx" )
  SOURCE_GROUP (BRepApprox FILES "../../../drv/BRepApprox/BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox_0.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKTopAlgo)
 add_library( TKTopAlgo SHARED ${TKTopAlgo_USED_SRCFILES} )

 set_property(TARGET TKTopAlgo PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKTopAlgo
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKTopAlgo.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKTopAlgo PROPERTIES COMPILE_FLAGS "${TKTopAlgo_PRECOMPILED_DEFS}" )
 include_directories( ${TKTopAlgo_COMPILER_DIRECTORIES} )
 target_link_libraries( TKTopAlgo ${TKTopAlgo_USED_LIBS} )
endif()
