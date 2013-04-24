# Makefile.am for Open Cascade toolkit TKShHealing
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/ShapeBuild : @top_srcdir@/src/ShapeBuild: \
@top_srcdir@/drv/ShapeExtend : @top_srcdir@/src/ShapeExtend: \
@top_srcdir@/drv/ShapeConstruct : @top_srcdir@/src/ShapeConstruct: \
@top_srcdir@/drv/ShapeCustom : @top_srcdir@/src/ShapeCustom: \
@top_srcdir@/drv/ShapeAnalysis : @top_srcdir@/src/ShapeAnalysis: \
@top_srcdir@/drv/ShapeFix : @top_srcdir@/src/ShapeFix: \
@top_srcdir@/drv/ShapeUpgrade : @top_srcdir@/src/ShapeUpgrade: \
@top_srcdir@/drv/ShapeAlgo : @top_srcdir@/src/ShapeAlgo: \
@top_srcdir@/drv/ShapeProcess : @top_srcdir@/src/ShapeProcess: \
@top_srcdir@/drv/ShapeProcessAPI : @top_srcdir@/src/ShapeProcessAPI


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES) $(CSF_wsock32_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/ShapeBuild -I@top_srcdir@/src/ShapeBuild \
-I@top_srcdir@/drv/ShapeExtend -I@top_srcdir@/src/ShapeExtend \
-I@top_srcdir@/drv/ShapeConstruct -I@top_srcdir@/src/ShapeConstruct \
-I@top_srcdir@/drv/ShapeCustom -I@top_srcdir@/src/ShapeCustom \
-I@top_srcdir@/drv/ShapeAnalysis -I@top_srcdir@/src/ShapeAnalysis \
-I@top_srcdir@/drv/ShapeFix -I@top_srcdir@/src/ShapeFix \
-I@top_srcdir@/drv/ShapeUpgrade -I@top_srcdir@/src/ShapeUpgrade \
-I@top_srcdir@/drv/ShapeAlgo -I@top_srcdir@/src/ShapeAlgo \
-I@top_srcdir@/drv/ShapeProcess -I@top_srcdir@/src/ShapeProcess \
-I@top_srcdir@/drv/ShapeProcessAPI -I@top_srcdir@/src/ShapeProcessAPI


lib_LTLIBRARIES=libTKShHealing.la

libTKShHealing_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKBRep/libTKBRep.la \
../TKernel/libTKernel.la \
../TKMath/libTKMath.la \
../TKG2d/libTKG2d.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
../TKGeomAlgo/libTKGeomAlgo.la \
$(STLPort_LIB) $(CSF_wsock32_LIB) 

libTKShHealing_la_SOURCES = \
@top_srcdir@/drv/ShapeAnalysis/ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal_0.cxx \
@top_srcdir@/drv/ShapeAnalysis/ShapeAnalysis_DataMapNodeOfDataMapOfShapeListOfReal_0.cxx \
@top_srcdir@/drv/ShapeAnalysis/ShapeAnalysis_DataMapOfShapeListOfReal_0.cxx \
@top_srcdir@/drv/ShapeAnalysis/ShapeAnalysis_HSequenceOfFreeBounds_0.cxx \
@top_srcdir@/drv/ShapeAnalysis/ShapeAnalysis_SequenceNodeOfSequenceOfFreeBounds_0.cxx \
@top_srcdir@/drv/ShapeAnalysis/ShapeAnalysis_SequenceOfFreeBounds_0.cxx \
@top_srcdir@/drv/ShapeExtend/ShapeExtend_DataMapIteratorOfDataMapOfShapeListOfMsg_0.cxx \
@top_srcdir@/drv/ShapeExtend/ShapeExtend_DataMapIteratorOfDataMapOfTransientListOfMsg_0.cxx \
@top_srcdir@/drv/ShapeExtend/ShapeExtend_DataMapNodeOfDataMapOfShapeListOfMsg_0.cxx \
@top_srcdir@/drv/ShapeExtend/ShapeExtend_DataMapNodeOfDataMapOfTransientListOfMsg_0.cxx \
@top_srcdir@/drv/ShapeExtend/ShapeExtend_DataMapOfShapeListOfMsg_0.cxx \
@top_srcdir@/drv/ShapeExtend/ShapeExtend_DataMapOfTransientListOfMsg_0.cxx \
@top_srcdir@/drv/ShapeFix/ShapeFix_DataMapIteratorOfDataMapOfShapeBox2d_0.cxx \
@top_srcdir@/drv/ShapeFix/ShapeFix_DataMapNodeOfDataMapOfShapeBox2d_0.cxx \
@top_srcdir@/drv/ShapeFix/ShapeFix_DataMapOfShapeBox2d_0.cxx \
@top_srcdir@/drv/ShapeFix/ShapeFix_SequenceNodeOfSequenceOfWireSegment_0.cxx \
@top_srcdir@/drv/ShapeFix/ShapeFix_SequenceOfWireSegment_0.cxx \
@top_srcdir@/drv/ShapeProcess/ShapeProcess_DictionaryOfOperator_0.cxx \
@top_srcdir@/drv/ShapeProcess/ShapeProcess_IteratorOfDictionaryOfOperator_0.cxx \
@top_srcdir@/drv/ShapeProcess/ShapeProcess_StackItemOfDictionaryOfOperator_0.cxx \
@top_srcdir@/src/ShapeAlgo/ShapeAlgo.cxx \
@top_srcdir@/src/ShapeAlgo/ShapeAlgo_AlgoContainer.cxx \
@top_srcdir@/src/ShapeAlgo/ShapeAlgo_ToolContainer.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_BoxBndTree.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_CheckSmallFace.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_Curve.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_Edge.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_FreeBoundData.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_FreeBounds.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_FreeBoundsProperties.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_Geom.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_ShapeContents.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_ShapeTolerance.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_Shell.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_Surface.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_TransferParameters.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_TransferParametersProj.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_Wire.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_WireOrder.cxx \
@top_srcdir@/src/ShapeAnalysis/ShapeAnalysis_WireVertex.cxx \
@top_srcdir@/src/ShapeBuild/ShapeBuild.cxx \
@top_srcdir@/src/ShapeBuild/ShapeBuild_Edge.cxx \
@top_srcdir@/src/ShapeBuild/ShapeBuild_ReShape.cxx \
@top_srcdir@/src/ShapeBuild/ShapeBuild_Vertex.cxx \
@top_srcdir@/src/ShapeConstruct/ShapeConstruct.cxx \
@top_srcdir@/src/ShapeConstruct/ShapeConstruct_CompBezierCurves2dToBSplineCurve2d.cxx \
@top_srcdir@/src/ShapeConstruct/ShapeConstruct_CompBezierCurvesToBSplineCurve.cxx \
@top_srcdir@/src/ShapeConstruct/ShapeConstruct_Curve.cxx \
@top_srcdir@/src/ShapeConstruct/ShapeConstruct_MakeTriangulation.cxx \
@top_srcdir@/src/ShapeConstruct/ShapeConstruct_ProjectCurveOnSurface.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_BSplineRestriction.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_ConvertToBSpline.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_ConvertToRevolution.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_Curve.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_Curve2d.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_DirectModification.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_RestrictionParameters.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_Surface.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_SweptToElementary.cxx \
@top_srcdir@/src/ShapeCustom/ShapeCustom_TrsfModification.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend_BasicMsgRegistrator.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend_ComplexCurve.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend_CompositeSurface.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend_Explorer.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend_MsgRegistrator.cxx \
@top_srcdir@/src/ShapeExtend/ShapeExtend_WireData.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_ComposeShell.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Edge.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_EdgeConnect.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_EdgeProjAux.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Face.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_FaceConnect.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_FixSmallFace.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_FreeBounds.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_IntersectionTool.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Root.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Shape.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_ShapeTolerance.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Shell.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Solid.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_SplitCommonVertex.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_SplitTool.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Wire.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_WireSegment.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_WireVertex.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Wire_1.cxx \
@top_srcdir@/src/ShapeFix/ShapeFix_Wireframe.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess_Context.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess_OperFunc.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess_OperLibrary.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess_Operator.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess_ShapeContext.cxx \
@top_srcdir@/src/ShapeProcess/ShapeProcess_UOperator.cxx \
@top_srcdir@/src/ShapeProcessAPI/ShapeProcessAPI_ApplySequence.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ClosedEdgeDivide.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ClosedFaceDivide.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ConvertCurve2dToBezier.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ConvertCurve3dToBezier.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ConvertSurfaceToBezierBasis.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_EdgeDivide.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_FaceDivide.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_FaceDivideArea.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_FixSmallBezierCurves.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_FixSmallCurves.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_RemoveInternalWires.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_RemoveLocations.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeConvertToBezier.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeDivide.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeDivideAngle.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeDivideArea.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeDivideClosed.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeDivideClosedEdges.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShapeDivideContinuity.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_ShellSewing.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitCurve.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitCurve2d.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitCurve2dContinuity.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitCurve3d.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitCurve3dContinuity.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitSurface.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceAngle.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceArea.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceContinuity.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_Tool.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_UnifySameDomain.cxx \
@top_srcdir@/src/ShapeUpgrade/ShapeUpgrade_WireDivide.cxx

