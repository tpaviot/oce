project(TKShHealing)

if (WIN32)
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeBuild_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeExtend_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeConstruct_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeCustom_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeAnalysis_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeFix_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeUpgrade_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeAlgo_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeProcess_DLL" )
  list( APPEND TKShHealing_PRECOMPILED_DEFS "-D__ShapeProcessAPI_DLL" )
  string( REGEX REPLACE ";" " " TKShHealing_PRECOMPILED_DEFS "${TKShHealing_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKShHealing_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeBuild" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeBuild" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeExtend" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeExtend" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeConstruct" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeConstruct" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeCustom" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeCustom" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeAnalysis" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeAnalysis" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeFix" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeFix" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeUpgrade" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeUpgrade" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeAlgo" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeAlgo" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeProcess" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeProcess" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../drv/ShapeProcessAPI" )
  list( APPEND TKShHealing_COMPILER_DIRECTORIES "../../../src/ShapeProcessAPI" )

if (WIN32)
else()
endif()

  list( APPEND TKShHealing_USED_LIBS TKBRep )
  list( APPEND TKShHealing_USED_LIBS TKernel )
  list( APPEND TKShHealing_USED_LIBS TKMath )
  list( APPEND TKShHealing_USED_LIBS TKG2d )
  list( APPEND TKShHealing_USED_LIBS TKTopAlgo )
  list( APPEND TKShHealing_USED_LIBS TKG3d )
  list( APPEND TKShHealing_USED_LIBS TKGeomBase )
  list( APPEND TKShHealing_USED_LIBS TKGeomAlgo )

if (WIN32)
  list( APPEND TKShHealing_USED_LIBS wsock32.lib )
elseif(APPLE)
else()
endif()

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeBuild/ShapeBuild.cxx" )
  SOURCE_GROUP (ShapeBuild FILES "../../../src/ShapeBuild/ShapeBuild.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeBuild/ShapeBuild_Edge.cxx" )
  SOURCE_GROUP (ShapeBuild FILES "../../../src/ShapeBuild/ShapeBuild_Edge.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeBuild/ShapeBuild_ReShape.cxx" )
  SOURCE_GROUP (ShapeBuild FILES "../../../src/ShapeBuild/ShapeBuild_ReShape.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeBuild/ShapeBuild_Vertex.cxx" )
  SOURCE_GROUP (ShapeBuild FILES "../../../src/ShapeBuild/ShapeBuild_Vertex.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeExtend/ShapeExtend_DataMapIteratorOfDataMapOfShapeListOfMsg_0.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../drv/ShapeExtend/ShapeExtend_DataMapIteratorOfDataMapOfShapeListOfMsg_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeExtend/ShapeExtend_DataMapIteratorOfDataMapOfTransientListOfMsg_0.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../drv/ShapeExtend/ShapeExtend_DataMapIteratorOfDataMapOfTransientListOfMsg_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeExtend/ShapeExtend_DataMapNodeOfDataMapOfShapeListOfMsg_0.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../drv/ShapeExtend/ShapeExtend_DataMapNodeOfDataMapOfShapeListOfMsg_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeExtend/ShapeExtend_DataMapNodeOfDataMapOfTransientListOfMsg_0.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../drv/ShapeExtend/ShapeExtend_DataMapNodeOfDataMapOfTransientListOfMsg_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeExtend/ShapeExtend_DataMapOfShapeListOfMsg_0.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../drv/ShapeExtend/ShapeExtend_DataMapOfShapeListOfMsg_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeExtend/ShapeExtend_DataMapOfTransientListOfMsg_0.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../drv/ShapeExtend/ShapeExtend_DataMapOfTransientListOfMsg_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend_BasicMsgRegistrator.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend_BasicMsgRegistrator.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend_ComplexCurve.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend_ComplexCurve.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend_CompositeSurface.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend_CompositeSurface.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend_Explorer.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend_Explorer.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend_MsgRegistrator.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend_MsgRegistrator.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeExtend/ShapeExtend_WireData.cxx" )
  SOURCE_GROUP (ShapeExtend FILES "../../../src/ShapeExtend/ShapeExtend_WireData.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeConstruct/ShapeConstruct.cxx" )
  SOURCE_GROUP (ShapeConstruct FILES "../../../src/ShapeConstruct/ShapeConstruct.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeConstruct/ShapeConstruct_CompBezierCurves2dToBSplineCurve2d.cxx" )
  SOURCE_GROUP (ShapeConstruct FILES "../../../src/ShapeConstruct/ShapeConstruct_CompBezierCurves2dToBSplineCurve2d.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeConstruct/ShapeConstruct_CompBezierCurvesToBSplineCurve.cxx" )
  SOURCE_GROUP (ShapeConstruct FILES "../../../src/ShapeConstruct/ShapeConstruct_CompBezierCurvesToBSplineCurve.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeConstruct/ShapeConstruct_Curve.cxx" )
  SOURCE_GROUP (ShapeConstruct FILES "../../../src/ShapeConstruct/ShapeConstruct_Curve.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeConstruct/ShapeConstruct_MakeTriangulation.cxx" )
  SOURCE_GROUP (ShapeConstruct FILES "../../../src/ShapeConstruct/ShapeConstruct_MakeTriangulation.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeConstruct/ShapeConstruct_ProjectCurveOnSurface.cxx" )
  SOURCE_GROUP (ShapeConstruct FILES "../../../src/ShapeConstruct/ShapeConstruct_ProjectCurveOnSurface.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_BSplineRestriction.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_BSplineRestriction.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_ConvertToBSpline.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_ConvertToBSpline.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_ConvertToRevolution.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_ConvertToRevolution.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_Curve.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_Curve.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_Curve2d.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_Curve2d.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_DirectModification.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_DirectModification.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_RestrictionParameters.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_RestrictionParameters.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_Surface.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_Surface.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_SweptToElementary.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_SweptToElementary.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeCustom/ShapeCustom_TrsfModification.cxx" )
  SOURCE_GROUP (ShapeCustom FILES "../../../src/ShapeCustom/ShapeCustom_TrsfModification.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeAnalysis/ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal_0.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../drv/ShapeAnalysis/ShapeAnalysis_DataMapIteratorOfDataMapOfShapeListOfReal_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeAnalysis/ShapeAnalysis_DataMapNodeOfDataMapOfShapeListOfReal_0.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../drv/ShapeAnalysis/ShapeAnalysis_DataMapNodeOfDataMapOfShapeListOfReal_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeAnalysis/ShapeAnalysis_DataMapOfShapeListOfReal_0.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../drv/ShapeAnalysis/ShapeAnalysis_DataMapOfShapeListOfReal_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeAnalysis/ShapeAnalysis_HSequenceOfFreeBounds_0.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../drv/ShapeAnalysis/ShapeAnalysis_HSequenceOfFreeBounds_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeAnalysis/ShapeAnalysis_SequenceNodeOfSequenceOfFreeBounds_0.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../drv/ShapeAnalysis/ShapeAnalysis_SequenceNodeOfSequenceOfFreeBounds_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeAnalysis/ShapeAnalysis_SequenceOfFreeBounds_0.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../drv/ShapeAnalysis/ShapeAnalysis_SequenceOfFreeBounds_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_BoxBndTree.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_BoxBndTree.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_CheckSmallFace.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_CheckSmallFace.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_Curve.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_Curve.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_Edge.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_Edge.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_FreeBoundData.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_FreeBoundData.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_FreeBounds.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_FreeBounds.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_FreeBoundsProperties.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_FreeBoundsProperties.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_Geom.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_Geom.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_ShapeContents.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_ShapeContents.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_ShapeTolerance.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_ShapeTolerance.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_Shell.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_Shell.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_Surface.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_Surface.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_TransferParameters.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_TransferParameters.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_TransferParametersProj.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_TransferParametersProj.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_Wire.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_Wire.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_WireOrder.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_WireOrder.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAnalysis/ShapeAnalysis_WireVertex.cxx" )
  SOURCE_GROUP (ShapeAnalysis FILES "../../../src/ShapeAnalysis/ShapeAnalysis_WireVertex.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeFix/ShapeFix_DataMapIteratorOfDataMapOfShapeBox2d_0.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../drv/ShapeFix/ShapeFix_DataMapIteratorOfDataMapOfShapeBox2d_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeFix/ShapeFix_DataMapNodeOfDataMapOfShapeBox2d_0.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../drv/ShapeFix/ShapeFix_DataMapNodeOfDataMapOfShapeBox2d_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeFix/ShapeFix_DataMapOfShapeBox2d_0.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../drv/ShapeFix/ShapeFix_DataMapOfShapeBox2d_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeFix/ShapeFix_SequenceNodeOfSequenceOfWireSegment_0.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../drv/ShapeFix/ShapeFix_SequenceNodeOfSequenceOfWireSegment_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeFix/ShapeFix_SequenceOfWireSegment_0.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../drv/ShapeFix/ShapeFix_SequenceOfWireSegment_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_ComposeShell.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_ComposeShell.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Edge.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Edge.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_EdgeConnect.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_EdgeConnect.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_EdgeProjAux.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_EdgeProjAux.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Face.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Face.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_FaceConnect.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_FaceConnect.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_FixSmallFace.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_FixSmallFace.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_FreeBounds.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_FreeBounds.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_IntersectionTool.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_IntersectionTool.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Root.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Root.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Shape.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Shape.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_ShapeTolerance.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_ShapeTolerance.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Shell.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Shell.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Solid.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Solid.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_SplitCommonVertex.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_SplitCommonVertex.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_SplitTool.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_SplitTool.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Wire.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Wire.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_WireSegment.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_WireSegment.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_WireVertex.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_WireVertex.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Wire_1.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Wire_1.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeFix/ShapeFix_Wireframe.cxx" )
  SOURCE_GROUP (ShapeFix FILES "../../../src/ShapeFix/ShapeFix_Wireframe.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ClosedEdgeDivide.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ClosedEdgeDivide.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ClosedFaceDivide.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ClosedFaceDivide.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ConvertCurve2dToBezier.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ConvertCurve2dToBezier.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ConvertCurve3dToBezier.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ConvertCurve3dToBezier.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ConvertSurfaceToBezierBasis.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ConvertSurfaceToBezierBasis.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_EdgeDivide.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_EdgeDivide.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_FaceDivide.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_FaceDivide.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_FaceDivideArea.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_FaceDivideArea.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_FixSmallBezierCurves.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_FixSmallBezierCurves.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_FixSmallCurves.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_FixSmallCurves.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_RemoveInternalWires.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_RemoveInternalWires.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_RemoveLocations.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_RemoveLocations.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeConvertToBezier.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeConvertToBezier.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivide.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivide.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideAngle.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideAngle.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideArea.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideArea.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideClosed.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideClosed.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideClosedEdges.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideClosedEdges.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideContinuity.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShapeDivideContinuity.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShellSewing.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_ShellSewing.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve2d.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve2d.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve2dContinuity.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve2dContinuity.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve3d.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve3d.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve3dContinuity.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitCurve3dContinuity.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurface.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurface.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceAngle.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceAngle.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceArea.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceArea.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceContinuity.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_SplitSurfaceContinuity.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_Tool.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_Tool.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_UnifySameDomain.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_UnifySameDomain.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeUpgrade/ShapeUpgrade_WireDivide.cxx" )
  SOURCE_GROUP (ShapeUpgrade FILES "../../../src/ShapeUpgrade/ShapeUpgrade_WireDivide.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAlgo/ShapeAlgo.cxx" )
  SOURCE_GROUP (ShapeAlgo FILES "../../../src/ShapeAlgo/ShapeAlgo.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAlgo/ShapeAlgo_AlgoContainer.cxx" )
  SOURCE_GROUP (ShapeAlgo FILES "../../../src/ShapeAlgo/ShapeAlgo_AlgoContainer.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeAlgo/ShapeAlgo_ToolContainer.cxx" )
  SOURCE_GROUP (ShapeAlgo FILES "../../../src/ShapeAlgo/ShapeAlgo_ToolContainer.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeProcess/ShapeProcess_DictionaryOfOperator_0.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../drv/ShapeProcess/ShapeProcess_DictionaryOfOperator_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeProcess/ShapeProcess_IteratorOfDictionaryOfOperator_0.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../drv/ShapeProcess/ShapeProcess_IteratorOfDictionaryOfOperator_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../drv/ShapeProcess/ShapeProcess_StackItemOfDictionaryOfOperator_0.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../drv/ShapeProcess/ShapeProcess_StackItemOfDictionaryOfOperator_0.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess_Context.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess_Context.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess_OperFunc.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess_OperFunc.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess_OperLibrary.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess_OperLibrary.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess_Operator.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess_Operator.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess_ShapeContext.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess_ShapeContext.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcess/ShapeProcess_UOperator.cxx" )
  SOURCE_GROUP (ShapeProcess FILES "../../../src/ShapeProcess/ShapeProcess_UOperator.cxx")

  list( APPEND TKShHealing_USED_SRCFILES "../../../src/ShapeProcessAPI/ShapeProcessAPI_ApplySequence.cxx" )
  SOURCE_GROUP (ShapeProcessAPI FILES "../../../src/ShapeProcessAPI/ShapeProcessAPI_ApplySequence.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKShHealing)
 add_library( TKShHealing SHARED ${TKShHealing_USED_SRCFILES} )

 set_property(TARGET TKShHealing PROPERTY FOLDER ModelingAlgorithms)

 install( TARGETS TKShHealing
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKShHealing.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKShHealing PROPERTIES COMPILE_FLAGS "${TKShHealing_PRECOMPILED_DEFS}" )
 include_directories( ${TKShHealing_COMPILER_DIRECTORIES} )
 target_link_libraries( TKShHealing ${TKShHealing_USED_LIBS} )
endif()
