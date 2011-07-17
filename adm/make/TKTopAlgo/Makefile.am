# Makefile.am for Open Cascade toolkit TKTopAlgo
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/IntCurvesFace : @top_srcdir@/src/IntCurvesFace: \
@top_srcdir@/drv/MAT : @top_srcdir@/src/MAT: \
@top_srcdir@/drv/MAT2d : @top_srcdir@/src/MAT2d: \
@top_srcdir@/drv/Bisector : @top_srcdir@/src/Bisector: \
@top_srcdir@/drv/BRepMAT2d : @top_srcdir@/src/BRepMAT2d: \
@top_srcdir@/drv/BRepCheck : @top_srcdir@/src/BRepCheck: \
@top_srcdir@/drv/BRepBndLib : @top_srcdir@/src/BRepBndLib: \
@top_srcdir@/drv/BRepExtrema : @top_srcdir@/src/BRepExtrema: \
@top_srcdir@/drv/BRepClass : @top_srcdir@/src/BRepClass: \
@top_srcdir@/drv/BRepClass3d : @top_srcdir@/src/BRepClass3d: \
@top_srcdir@/drv/BRepLib : @top_srcdir@/src/BRepLib: \
@top_srcdir@/drv/BRepGProp : @top_srcdir@/src/BRepGProp: \
@top_srcdir@/drv/BRepIntCurveSurface : @top_srcdir@/src/BRepIntCurveSurface: \
@top_srcdir@/drv/BRepTopAdaptor : @top_srcdir@/src/BRepTopAdaptor: \
@top_srcdir@/drv/BRepBuilderAPI : @top_srcdir@/src/BRepBuilderAPI: \
@top_srcdir@/drv/BRepApprox : @top_srcdir@/src/BRepApprox


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/IntCurvesFace -I@top_srcdir@/src/IntCurvesFace \
-I@top_srcdir@/drv/MAT -I@top_srcdir@/src/MAT \
-I@top_srcdir@/drv/MAT2d -I@top_srcdir@/src/MAT2d \
-I@top_srcdir@/drv/Bisector -I@top_srcdir@/src/Bisector \
-I@top_srcdir@/drv/BRepMAT2d -I@top_srcdir@/src/BRepMAT2d \
-I@top_srcdir@/drv/BRepCheck -I@top_srcdir@/src/BRepCheck \
-I@top_srcdir@/drv/BRepBndLib -I@top_srcdir@/src/BRepBndLib \
-I@top_srcdir@/drv/BRepExtrema -I@top_srcdir@/src/BRepExtrema \
-I@top_srcdir@/drv/BRepClass -I@top_srcdir@/src/BRepClass \
-I@top_srcdir@/drv/BRepClass3d -I@top_srcdir@/src/BRepClass3d \
-I@top_srcdir@/drv/BRepLib -I@top_srcdir@/src/BRepLib \
-I@top_srcdir@/drv/BRepGProp -I@top_srcdir@/src/BRepGProp \
-I@top_srcdir@/drv/BRepIntCurveSurface -I@top_srcdir@/src/BRepIntCurveSurface \
-I@top_srcdir@/drv/BRepTopAdaptor -I@top_srcdir@/src/BRepTopAdaptor \
-I@top_srcdir@/drv/BRepBuilderAPI -I@top_srcdir@/src/BRepBuilderAPI \
-I@top_srcdir@/drv/BRepApprox -I@top_srcdir@/src/BRepApprox


lib_LTLIBRARIES=libTKTopAlgo.la

libTKTopAlgo_la_LIBADD = \
../TKernel/libTKernel.la \
../TKGeomBase/libTKGeomBase.la \
../TKMath/libTKMath.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKBRep/libTKBRep.la \
$(STLPort_LIB) 

libTKTopAlgo_la_SOURCES = \
@top_srcdir@/drv/BRepApprox/BRepApprox_ApproxLine_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_Approx_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_BSpGradient_BFGSOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_BSpParFunctionOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_BSpParLeastSquareOfMyBSplGradientOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_Gradient_BFGSOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_Gradient_BFGSOfMyGradientbisOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_MyBSplGradientOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_MyGradientOfTheComputeLineBezierOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_MyGradientbisOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ParFunctionOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ParFunctionOfMyGradientbisOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ParLeastSquareOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ParLeastSquareOfMyGradientbisOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ResConstraintOfMyGradientOfTheComputeLineBezierOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ResConstraintOfMyGradientbisOfTheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_SurfaceTool_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheComputeLineBezierOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheComputeLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheFunctionOfTheInt2SOfThePrmPrmSvSurfacesOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheImpPrmSvSurfacesOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheInt2SOfThePrmPrmSvSurfacesOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheMultiLineOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheMultiLineToolOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_ThePrmPrmSvSurfacesOfApprox_0.cxx \
@top_srcdir@/drv/BRepApprox/BRepApprox_TheZerImpFuncOfTheImpPrmSvSurfacesOfApprox_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_DataMapIteratorOfDataMapOfShapeListOfStatus_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_DataMapIteratorOfDataMapOfShapeResult_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_DataMapNodeOfDataMapOfShapeListOfStatus_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_DataMapNodeOfDataMapOfShapeResult_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_DataMapOfShapeListOfStatus_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_DataMapOfShapeResult_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_ListIteratorOfListOfStatus_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_ListNodeOfListOfStatus_0.cxx \
@top_srcdir@/drv/BRepCheck/BRepCheck_ListOfStatus_0.cxx \
@top_srcdir@/drv/BRepClass/BRepClass_FClass2dOfFClassifier_0.cxx \
@top_srcdir@/drv/BRepClass/BRepClass_FClassifier_0.cxx \
@top_srcdir@/drv/BRepClass/BRepClass_FacePassiveClassifier_0.cxx \
@top_srcdir@/drv/BRepClass3d/BRepClass3d_DataMapIteratorOfMapOfInter_0.cxx \
@top_srcdir@/drv/BRepClass3d/BRepClass3d_DataMapNodeOfMapOfInter_0.cxx \
@top_srcdir@/drv/BRepClass3d/BRepClass3d_MapOfInter_0.cxx \
@top_srcdir@/drv/BRepClass3d/BRepClass3d_SolidPassiveClassifier_0.cxx \
@top_srcdir@/drv/BRepExtrema/BRepExtrema_UnCompatibleShape_0.cxx \
@top_srcdir@/drv/BRepGProp/BRepGProp_Cinert_0.cxx \
@top_srcdir@/drv/BRepGProp/BRepGProp_Sinert_0.cxx \
@top_srcdir@/drv/BRepGProp/BRepGProp_TFunctionOfVinertGK_0.cxx \
@top_srcdir@/drv/BRepGProp/BRepGProp_UFunctionOfVinertGK_0.cxx \
@top_srcdir@/drv/BRepGProp/BRepGProp_VinertGK_0.cxx \
@top_srcdir@/drv/BRepGProp/BRepGProp_Vinert_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_BisectingLocus_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_DataMapIteratorOfDataMapOfBasicEltShape_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_DataMapIteratorOfDataMapOfShapeSequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_DataMapNodeOfDataMapOfBasicEltShape_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_DataMapNodeOfDataMapOfShapeSequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_DataMapOfBasicEltShape_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_DataMapOfShapeSequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_SequenceNodeOfSequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/BRepMAT2d/BRepMAT2d_SequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/BRepTopAdaptor/BRepTopAdaptor_DataMapIteratorOfMapOfShapeTool_0.cxx \
@top_srcdir@/drv/BRepTopAdaptor/BRepTopAdaptor_DataMapNodeOfMapOfShapeTool_0.cxx \
@top_srcdir@/drv/BRepTopAdaptor/BRepTopAdaptor_MapOfShapeTool_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerArc_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerBasicElt_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerBisector_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapIteratorOfDataMapOfIntegerNode_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerArc_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerBasicElt_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerBisector_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapNodeOfDataMapOfIntegerNode_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapOfIntegerArc_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapOfIntegerBasicElt_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapOfIntegerBisector_0.cxx \
@top_srcdir@/drv/MAT/MAT_DataMapOfIntegerNode_0.cxx \
@top_srcdir@/drv/MAT/MAT_ListOfBisector_0.cxx \
@top_srcdir@/drv/MAT/MAT_ListOfEdge_0.cxx \
@top_srcdir@/drv/MAT/MAT_SequenceNodeOfSequenceOfArc_0.cxx \
@top_srcdir@/drv/MAT/MAT_SequenceNodeOfSequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/MAT/MAT_SequenceOfArc_0.cxx \
@top_srcdir@/drv/MAT/MAT_SequenceOfBasicElt_0.cxx \
@top_srcdir@/drv/MAT/MAT_TListNodeOfListOfBisector_0.cxx \
@top_srcdir@/drv/MAT/MAT_TListNodeOfListOfEdge_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_Array2OfConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfBiIntInteger_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfBiIntSequenceOfInteger_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerBisec_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerPnt2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerSequenceOfConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapIteratorOfDataMapOfIntegerVec2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfBiIntInteger_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfBiIntSequenceOfInteger_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerBisec_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerPnt2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerSequenceOfConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapNodeOfDataMapOfIntegerVec2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfBiIntInteger_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfBiIntSequenceOfInteger_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfIntegerBisec_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfIntegerConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfIntegerPnt2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfIntegerSequenceOfConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_DataMapOfIntegerVec2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_Mat2d_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfSequenceOfCurve_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_SequenceNodeOfSequenceOfSequenceOfGeometry_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_SequenceOfConnexion_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_SequenceOfSequenceOfCurve_0.cxx \
@top_srcdir@/drv/MAT2d/MAT2d_SequenceOfSequenceOfGeometry_0.cxx \
@top_srcdir@/src/BRepBndLib/BRepBndLib.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_Collect.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_Command.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_Copy.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_FindPlane.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_GTransform.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeEdge.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeEdge2d.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeFace.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakePolygon.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeShape.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeShell.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeSolid.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeVertex.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_MakeWire.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_ModifyShape.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_NurbsConvert.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_Sewing.cxx \
@top_srcdir@/src/BRepBuilderAPI/BRepBuilderAPI_Transform.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Analyzer.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Edge.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Face.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Result.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Shell.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Vertex.cxx \
@top_srcdir@/src/BRepCheck/BRepCheck_Wire.cxx \
@top_srcdir@/src/BRepClass/BRepClass_Edge.cxx \
@top_srcdir@/src/BRepClass/BRepClass_FaceClassifier.cxx \
@top_srcdir@/src/BRepClass/BRepClass_FaceExplorer.cxx \
@top_srcdir@/src/BRepClass/BRepClass_Intersector.cxx \
@top_srcdir@/src/BRepClass3d/BRepClass3d_Intersector3d.cxx \
@top_srcdir@/src/BRepClass3d/BRepClass3d_SClassifier.cxx \
@top_srcdir@/src/BRepClass3d/BRepClass3d_SolidClassifier.cxx \
@top_srcdir@/src/BRepClass3d/BRepClass3d_SolidExplorer.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_DistShapeShape.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_DistanceSS.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_ExtCC.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_ExtCF.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_ExtFF.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_ExtPC.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_ExtPF.cxx \
@top_srcdir@/src/BRepExtrema/BRepExtrema_Poly.cxx \
@top_srcdir@/src/BRepGProp/BRepGProp.cxx \
@top_srcdir@/src/BRepGProp/BRepGProp_Domain.cxx \
@top_srcdir@/src/BRepGProp/BRepGProp_EdgeTool.cxx \
@top_srcdir@/src/BRepGProp/BRepGProp_Face.cxx \
@top_srcdir@/src/BRepIntCurveSurface/BRepIntCurveSurface_Inter.cxx \
@top_srcdir@/src/BRepLib/BRepLib.cxx \
@top_srcdir@/src/BRepLib/BRepLib_Command.cxx \
@top_srcdir@/src/BRepLib/BRepLib_FindSurface.cxx \
@top_srcdir@/src/BRepLib/BRepLib_FuseEdges.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeEdge.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeEdge2d.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeFace.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakePolygon.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeShape.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeShell.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeSolid.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeVertex.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeWire.cxx \
@top_srcdir@/src/BRepLib/BRepLib_MakeWire_1.cxx \
@top_srcdir@/src/BRepMAT2d/BRepMAT2d_Explorer.cxx \
@top_srcdir@/src/BRepMAT2d/BRepMAT2d_LinkTopoBilo.cxx \
@top_srcdir@/src/BRepTopAdaptor/BRepTopAdaptor_FClass2d.cxx \
@top_srcdir@/src/BRepTopAdaptor/BRepTopAdaptor_HVertex.cxx \
@top_srcdir@/src/BRepTopAdaptor/BRepTopAdaptor_Tool.cxx \
@top_srcdir@/src/BRepTopAdaptor/BRepTopAdaptor_TopolTool.cxx \
@top_srcdir@/src/Bisector/Bisector.cxx \
@top_srcdir@/src/Bisector/Bisector_Bisec.cxx \
@top_srcdir@/src/Bisector/Bisector_BisecAna.cxx \
@top_srcdir@/src/Bisector/Bisector_BisecCC.cxx \
@top_srcdir@/src/Bisector/Bisector_BisecPC.cxx \
@top_srcdir@/src/Bisector/Bisector_Curve.cxx \
@top_srcdir@/src/Bisector/Bisector_FunctionH.cxx \
@top_srcdir@/src/Bisector/Bisector_FunctionInter.cxx \
@top_srcdir@/src/Bisector/Bisector_Inter.cxx \
@top_srcdir@/src/Bisector/Bisector_PointOnBis.cxx \
@top_srcdir@/src/Bisector/Bisector_PolyBis.cxx \
@top_srcdir@/src/IntCurvesFace/IntCurvesFace_Intersector.cxx \
@top_srcdir@/src/IntCurvesFace/IntCurvesFace_ShapeIntersector.cxx \
@top_srcdir@/src/MAT/MAT_Arc.cxx \
@top_srcdir@/src/MAT/MAT_BasicElt.cxx \
@top_srcdir@/src/MAT/MAT_Bisector.cxx \
@top_srcdir@/src/MAT/MAT_Edge.cxx \
@top_srcdir@/src/MAT/MAT_Graph.cxx \
@top_srcdir@/src/MAT/MAT_Node.cxx \
@top_srcdir@/src/MAT/MAT_Zone.cxx \
@top_srcdir@/src/MAT2d/MAT2d_BiInt.cxx \
@top_srcdir@/src/MAT2d/MAT2d_Circuit.cxx \
@top_srcdir@/src/MAT2d/MAT2d_Connexion.cxx \
@top_srcdir@/src/MAT2d/MAT2d_CutCurve.cxx \
@top_srcdir@/src/MAT2d/MAT2d_MapBiIntHasher.cxx \
@top_srcdir@/src/MAT2d/MAT2d_MiniPath.cxx \
@top_srcdir@/src/MAT2d/MAT2d_SketchExplorer.cxx \
@top_srcdir@/src/MAT2d/MAT2d_Tool2d.cxx

