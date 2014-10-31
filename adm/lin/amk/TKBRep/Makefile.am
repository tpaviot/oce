# Makefile.am for Open Cascade toolkit TKBRep
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/TopoDS : @top_srcdir@/src/TopoDS: \
@top_srcdir@/drv/TopExp : @top_srcdir@/src/TopExp: \
@top_srcdir@/drv/TopTools : @top_srcdir@/src/TopTools: \
@top_srcdir@/drv/BRep : @top_srcdir@/src/BRep: \
@top_srcdir@/drv/BRepLProp : @top_srcdir@/src/BRepLProp: \
@top_srcdir@/drv/BRepAdaptor : @top_srcdir@/src/BRepAdaptor: \
@top_srcdir@/drv/BRepTools : @top_srcdir@/src/BRepTools


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES) $(STLPort_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/TopoDS -I@top_srcdir@/src/TopoDS \
-I@top_srcdir@/drv/TopExp -I@top_srcdir@/src/TopExp \
-I@top_srcdir@/drv/TopTools -I@top_srcdir@/src/TopTools \
-I@top_srcdir@/drv/BRep -I@top_srcdir@/src/BRep \
-I@top_srcdir@/drv/BRepLProp -I@top_srcdir@/src/BRepLProp \
-I@top_srcdir@/drv/BRepAdaptor -I@top_srcdir@/src/BRepAdaptor \
-I@top_srcdir@/drv/BRepTools -I@top_srcdir@/src/BRepTools


lib_LTLIBRARIES=libTKBRep.la

libTKBRep_la_LIBADD = $(CSF_OPT_LIBS) \
 \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../TKGeomBase/libTKGeomBase.la \
$(STLPort_LIB) 

libTKBRep_la_SOURCES = \
@top_srcdir@/drv/BRep/BRep_ListIteratorOfListOfCurveRepresentation_0.cxx \
@top_srcdir@/drv/BRep/BRep_ListIteratorOfListOfPointRepresentation_0.cxx \
@top_srcdir@/drv/BRep/BRep_ListNodeOfListOfCurveRepresentation_0.cxx \
@top_srcdir@/drv/BRep/BRep_ListNodeOfListOfPointRepresentation_0.cxx \
@top_srcdir@/drv/BRep/BRep_ListOfCurveRepresentation_0.cxx \
@top_srcdir@/drv/BRep/BRep_ListOfPointRepresentation_0.cxx \
@top_srcdir@/drv/BRepAdaptor/BRepAdaptor_Array1OfCurve_0.cxx \
@top_srcdir@/drv/BRepAdaptor/BRepAdaptor_HArray1OfCurve_0.cxx \
@top_srcdir@/drv/BRepAdaptor/BRepAdaptor_HCompCurve_0.cxx \
@top_srcdir@/drv/BRepAdaptor/BRepAdaptor_HCurve2d_0.cxx \
@top_srcdir@/drv/BRepAdaptor/BRepAdaptor_HCurve_0.cxx \
@top_srcdir@/drv/BRepAdaptor/BRepAdaptor_HSurface_0.cxx \
@top_srcdir@/drv/BRepLProp/BRepLProp_CLProps_0.cxx \
@top_srcdir@/drv/BRepLProp/BRepLProp_SLProps_0.cxx \
@top_srcdir@/drv/BRepTools/BRepTools_DataMapIteratorOfMapOfVertexPnt2d_0.cxx \
@top_srcdir@/drv/BRepTools/BRepTools_DataMapNodeOfMapOfVertexPnt2d_0.cxx \
@top_srcdir@/drv/BRepTools/BRepTools_MapOfVertexPnt2d_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_Array1OfListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_Array1OfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_Array2OfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfIntegerShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfOrientedShapeInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfOrientedShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeListOfInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeReal_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapIteratorOfDataMapOfShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfIntegerListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfIntegerShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfOrientedShapeInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfOrientedShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeListOfInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeReal_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeSequenceOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapNodeOfDataMapOfShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfIntegerListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfIntegerShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfOrientedShapeInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfOrientedShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfShapeInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfShapeListOfInteger_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfShapeReal_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfShapeSequenceOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_DataMapOfShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_HArray1OfListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_HArray1OfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_HArray2OfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_HSequenceOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeAddress_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedDataMapNodeOfIndexedDataMapOfShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedDataMapOfShapeAddress_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedDataMapOfShapeListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedDataMapOfShapeShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedMapNodeOfIndexedMapOfOrientedShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedMapNodeOfIndexedMapOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedMapOfOrientedShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_IndexedMapOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_ListIteratorOfListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_ListNodeOfListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_ListOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_MapIteratorOfMapOfOrientedShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_MapIteratorOfMapOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_MapOfOrientedShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_MapOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_SequenceNodeOfSequenceOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_SequenceOfShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_StdMapNodeOfMapOfOrientedShape_0.cxx \
@top_srcdir@/drv/TopTools/TopTools_StdMapNodeOfMapOfShape_0.cxx \
@top_srcdir@/drv/TopoDS/TopoDS_FrozenShape_0.cxx \
@top_srcdir@/drv/TopoDS/TopoDS_ListIteratorOfListOfShape_0.cxx \
@top_srcdir@/drv/TopoDS/TopoDS_ListNodeOfListOfShape_0.cxx \
@top_srcdir@/drv/TopoDS/TopoDS_ListOfShape_0.cxx \
@top_srcdir@/drv/TopoDS/TopoDS_LockedShape_0.cxx \
@top_srcdir@/drv/TopoDS/TopoDS_UnCompatibleShapes_0.cxx \
@top_srcdir@/src/BRep/BRep_Builder.cxx \
@top_srcdir@/src/BRep/BRep_Curve3D.cxx \
@top_srcdir@/src/BRep/BRep_CurveOn2Surfaces.cxx \
@top_srcdir@/src/BRep/BRep_CurveOnClosedSurface.cxx \
@top_srcdir@/src/BRep/BRep_CurveOnSurface.cxx \
@top_srcdir@/src/BRep/BRep_CurveRepresentation.cxx \
@top_srcdir@/src/BRep/BRep_GCurve.cxx \
@top_srcdir@/src/BRep/BRep_PointOnCurve.cxx \
@top_srcdir@/src/BRep/BRep_PointOnCurveOnSurface.cxx \
@top_srcdir@/src/BRep/BRep_PointOnSurface.cxx \
@top_srcdir@/src/BRep/BRep_PointRepresentation.cxx \
@top_srcdir@/src/BRep/BRep_PointsOnSurface.cxx \
@top_srcdir@/src/BRep/BRep_Polygon3D.cxx \
@top_srcdir@/src/BRep/BRep_PolygonOnClosedSurface.cxx \
@top_srcdir@/src/BRep/BRep_PolygonOnClosedTriangulation.cxx \
@top_srcdir@/src/BRep/BRep_PolygonOnSurface.cxx \
@top_srcdir@/src/BRep/BRep_PolygonOnTriangulation.cxx \
@top_srcdir@/src/BRep/BRep_TEdge.cxx \
@top_srcdir@/src/BRep/BRep_TFace.cxx \
@top_srcdir@/src/BRep/BRep_TVertex.cxx \
@top_srcdir@/src/BRep/BRep_Tool.cxx \
@top_srcdir@/src/BRepAdaptor/BRepAdaptor_CompCurve.cxx \
@top_srcdir@/src/BRepAdaptor/BRepAdaptor_Curve.cxx \
@top_srcdir@/src/BRepAdaptor/BRepAdaptor_Curve2d.cxx \
@top_srcdir@/src/BRepAdaptor/BRepAdaptor_Surface.cxx \
@top_srcdir@/src/BRepLProp/BRepLProp.cxx \
@top_srcdir@/src/BRepLProp/BRepLProp_CurveTool.cxx \
@top_srcdir@/src/BRepLProp/BRepLProp_SurfaceTool.cxx \
@top_srcdir@/src/BRepTools/BRepTools.cxx \
@top_srcdir@/src/BRepTools/BRepTools_Debug.cxx \
@top_srcdir@/src/BRepTools/BRepTools_GTrsfModification.cxx \
@top_srcdir@/src/BRepTools/BRepTools_Modification.cxx \
@top_srcdir@/src/BRepTools/BRepTools_Modifier.cxx \
@top_srcdir@/src/BRepTools/BRepTools_NurbsConvertModification.cxx \
@top_srcdir@/src/BRepTools/BRepTools_Quilt.cxx \
@top_srcdir@/src/BRepTools/BRepTools_ReShape.cxx \
@top_srcdir@/src/BRepTools/BRepTools_ShapeSet.cxx \
@top_srcdir@/src/BRepTools/BRepTools_Substitution.cxx \
@top_srcdir@/src/BRepTools/BRepTools_TrsfModification.cxx \
@top_srcdir@/src/BRepTools/BRepTools_WireExplorer.cxx \
@top_srcdir@/src/TopExp/TopExp.cxx \
@top_srcdir@/src/TopExp/TopExp_Explorer.cxx \
@top_srcdir@/src/TopTools/TopTools.cxx \
@top_srcdir@/src/TopTools/TopTools_LocationSet.cxx \
@top_srcdir@/src/TopTools/TopTools_MutexForShapeProvider.cxx \
@top_srcdir@/src/TopTools/TopTools_OrientedShapeMapHasher.cxx \
@top_srcdir@/src/TopTools/TopTools_ShapeMapHasher.cxx \
@top_srcdir@/src/TopTools/TopTools_ShapeSet.cxx \
@top_srcdir@/src/TopoDS/TopoDS.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Builder.cxx \
@top_srcdir@/src/TopoDS/TopoDS_CompSolid.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Compound.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Edge.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Face.cxx \
@top_srcdir@/src/TopoDS/TopoDS_HShape.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Iterator.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Shape.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Shell.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Solid.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TCompSolid.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TCompound.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TEdge.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TFace.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TShape.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TShell.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TSolid.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TVertex.cxx \
@top_srcdir@/src/TopoDS/TopoDS_TWire.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Vertex.cxx \
@top_srcdir@/src/TopoDS/TopoDS_Wire.cxx

