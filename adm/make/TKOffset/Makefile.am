# Makefile.am for Open Cascade toolkit TKOffset
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/BRepOffsetAPI : @top_srcdir@/src/BRepOffsetAPI: \
@top_srcdir@/drv/Draft : @top_srcdir@/src/Draft: \
@top_srcdir@/drv/BRepOffset : @top_srcdir@/src/BRepOffset: \
@top_srcdir@/drv/BiTgte : @top_srcdir@/src/BiTgte


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/BRepOffsetAPI -I@top_srcdir@/src/BRepOffsetAPI \
-I@top_srcdir@/drv/Draft -I@top_srcdir@/src/Draft \
-I@top_srcdir@/drv/BRepOffset -I@top_srcdir@/src/BRepOffset \
-I@top_srcdir@/drv/BiTgte -I@top_srcdir@/src/BiTgte


lib_LTLIBRARIES=libTKOffset.la

libTKOffset_la_LIBADD = \
../TKBool/libTKBool.la \
../TKGeomAlgo/libTKGeomAlgo.la \
../TKernel/libTKernel.la \
../TKGeomBase/libTKGeomBase.la \
../TKTopAlgo/libTKTopAlgo.la \
../TKMath/libTKMath.la \
../TKBO/libTKBO.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKBRep/libTKBRep.la \
../TKShHealing/libTKShHealing.la \
../TKFillet/libTKFillet.la \
../TKPrim/libTKPrim.la \
$(STLPort_LIB) 

libTKOffset_la_SOURCES = \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeListOfInterval_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeMapOfShape_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapIteratorOfDataMapOfShapeOffset_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeListOfInterval_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeMapOfShape_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapNodeOfDataMapOfShapeOffset_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapOfShapeListOfInterval_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapOfShapeMapOfShape_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_DataMapOfShapeOffset_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_ListIteratorOfListOfInterval_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_ListNodeOfListOfInterval_0.cxx \
@top_srcdir@/drv/BRepOffset/BRepOffset_ListOfInterval_0.cxx \
@top_srcdir@/drv/BRepOffsetAPI/BRepOffsetAPI_SequenceNodeOfSequenceOfSequenceOfReal_0.cxx \
@top_srcdir@/drv/BRepOffsetAPI/BRepOffsetAPI_SequenceNodeOfSequenceOfSequenceOfShape_0.cxx \
@top_srcdir@/drv/BRepOffsetAPI/BRepOffsetAPI_SequenceOfSequenceOfReal_0.cxx \
@top_srcdir@/drv/BRepOffsetAPI/BRepOffsetAPI_SequenceOfSequenceOfShape_0.cxx \
@top_srcdir@/drv/BiTgte/BiTgte_DataMapIteratorOfDataMapOfShapeBox_0.cxx \
@top_srcdir@/drv/BiTgte/BiTgte_DataMapNodeOfDataMapOfShapeBox_0.cxx \
@top_srcdir@/drv/BiTgte/BiTgte_DataMapOfShapeBox_0.cxx \
@top_srcdir@/drv/BiTgte/BiTgte_HCurveOnEdge_0.cxx \
@top_srcdir@/drv/BiTgte/BiTgte_HCurveOnVertex_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapIteratorOfDataMapOfEdgeEdgeInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapIteratorOfDataMapOfFaceFaceInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapIteratorOfDataMapOfVertexVertexInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapNodeOfDataMapOfEdgeEdgeInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapNodeOfDataMapOfFaceFaceInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapNodeOfDataMapOfVertexVertexInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapOfEdgeEdgeInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapOfFaceFaceInfo_0.cxx \
@top_srcdir@/drv/Draft/Draft_DataMapOfVertexVertexInfo_0.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_Analyse.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_Inter2d.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_Inter3d.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_Interval.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_MakeLoops.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_MakeOffset.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_Offset.cxx \
@top_srcdir@/src/BRepOffset/BRepOffset_Tool.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_DraftAngle.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_FindContigousEdges.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakeDraft.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakeEvolved.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakeFilling.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakeOffset.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakeOffsetShape.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakePipe.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakePipeShell.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_MakeThickSolid.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_NormalProjection.cxx \
@top_srcdir@/src/BRepOffsetAPI/BRepOffsetAPI_ThruSections.cxx \
@top_srcdir@/src/BiTgte/BiTgte_Blend.cxx \
@top_srcdir@/src/BiTgte/BiTgte_CurveOnEdge.cxx \
@top_srcdir@/src/BiTgte/BiTgte_CurveOnVertex.cxx \
@top_srcdir@/src/Draft/Draft.cxx \
@top_srcdir@/src/Draft/Draft_EdgeInfo.cxx \
@top_srcdir@/src/Draft/Draft_FaceInfo.cxx \
@top_srcdir@/src/Draft/Draft_Modification.cxx \
@top_srcdir@/src/Draft/Draft_Modification_1.cxx \
@top_srcdir@/src/Draft/Draft_VertexInfo.cxx

libTKOffset_laLDFLAGS = -version-info @oce_version_info@

