project(TKShapeSchema)

if (WIN32)
  list( APPEND TKShapeSchema_PRECOMPILED_DEFS "-D__ShapeSchema_DLL" )
  list( APPEND TKShapeSchema_PRECOMPILED_DEFS "-D__PCDMShape_DLL" )
  string( REGEX REPLACE ";" " " TKShapeSchema_PRECOMPILED_DEFS "${TKShapeSchema_PRECOMPILED_DEFS}")
endif()

  list( APPEND TKShapeSchema_COMPILER_DIRECTORIES "${WOK_LIB_PATH}" )
  list( APPEND TKShapeSchema_COMPILER_DIRECTORIES "../../../inc" )
  list( APPEND TKShapeSchema_COMPILER_DIRECTORIES "../../../drv/ShapeSchema" )
  list( APPEND TKShapeSchema_COMPILER_DIRECTORIES "../../../src/ShapeSchema" )
  list( APPEND TKShapeSchema_COMPILER_DIRECTORIES "../../../drv/PCDMShape" )
  list( APPEND TKShapeSchema_COMPILER_DIRECTORIES "../../../src/PCDMShape" )

if (WIN32)
else()
endif()

  list( APPEND TKShapeSchema_USED_LIBS TKernel )
  list( APPEND TKShapeSchema_USED_LIBS TKG2d )
  list( APPEND TKShapeSchema_USED_LIBS PTKernel )
  list( APPEND TKShapeSchema_USED_LIBS TKMath )
  list( APPEND TKShapeSchema_USED_LIBS TKCDF )
  list( APPEND TKShapeSchema_USED_LIBS TKPShape )

if (WIN32)
elseif(APPLE)
else()
endif()

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_DBC_VArrayOfCharacter.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_DBC_VArrayOfCharacter.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_DBC_VArrayOfExtCharacter.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_DBC_VArrayOfExtCharacter.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_ExternRef.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_ExternRef.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_ExternShareable.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_ExternShareable.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_PSeqOfExtRef.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_PSeqOfExtRef.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_Curve3D.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_Curve3D.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveOn2Surfaces.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveOn2Surfaces.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveOnClosedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveOnClosedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveOnSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveOnSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveRepresentation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_CurveRepresentation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_GCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_GCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointOnCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointOnCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointOnCurveOnSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointOnCurveOnSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointOnSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointOnSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointRepresentation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointRepresentation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointsOnSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PointsOnSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_Polygon3D.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_Polygon3D.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnClosedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnClosedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnClosedTriangulation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnClosedTriangulation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnTriangulation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_PolygonOnTriangulation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TEdge.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TEdge.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TEdge1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TEdge1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TFace.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TFace.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TFace1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TFace1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TVertex.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TVertex.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TVertex1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PBRep_TVertex1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PCDMShape_Document.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PCDMShape_Document.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PCDM_Document.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PCDM_Document.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfBSplineCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfBSplineCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfBezierCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfBezierCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfBoundedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfBoundedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_FieldOfHArray1OfCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfBezierCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfBezierCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom2d_HArray1OfCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBezierCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBezierCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray1OfSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfBSplineSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfBSplineSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfBezierSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfBezierSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfBoundedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfBoundedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_FieldOfHArray2OfSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBSplineCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBSplineCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBezierCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBezierCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBoundedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBoundedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBoundedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfBoundedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray1OfSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfBSplineSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfBSplineSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfBezierSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfBezierSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfBoundedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfBoundedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColPGeom_HArray2OfSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray1OfInteger.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray1OfInteger.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray1OfReal.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray1OfReal.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray2OfReal.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_FieldOfHArray2OfReal.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_HArray1OfInteger.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_HArray1OfInteger.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_HArray1OfReal.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_HArray1OfReal.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_HArray2OfReal.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColStd_HArray2OfReal.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfCirc2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfCirc2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfDir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfDir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfDir2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfDir2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfLin2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfLin2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfPnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfPnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfPnt2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfPnt2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfVec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfVec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfVec2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfVec2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfXY.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfXY.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfXYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray1OfXYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfCirc2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfCirc2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfDir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfDir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfDir2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfDir2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfLin2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfLin2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfPnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfPnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfPnt2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfPnt2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfVec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfVec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfVec2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfVec2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfXY.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfXY.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfXYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_FieldOfHArray2OfXYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfCirc2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfCirc2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfDir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfDir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfDir2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfDir2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfLin2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfLin2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfPnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfPnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfPnt2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfPnt2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfVec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfVec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfVec2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfVec2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfXY.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfXY.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfXYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray1OfXYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfCirc2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfCirc2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfDir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfDir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfDir2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfDir2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfLin2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfLin2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfPnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfPnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfPnt2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfPnt2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfVec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfVec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfVec2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfVec2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfXY.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfXY.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfXYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HArray2OfXYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfDir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfDir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfPnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfPnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfVec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfVec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfXYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_HSequenceOfXYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PCollection_HAsciiString.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PCollection_HAsciiString.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PCollection_HExtendedString.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PCollection_HExtendedString.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_AxisPlacement.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_AxisPlacement.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_BSplineCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_BSplineCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_BezierCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_BezierCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_BoundedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_BoundedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_CartesianPoint.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_CartesianPoint.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Circle.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Circle.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Conic.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Conic.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Curve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Curve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Direction.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Direction.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Ellipse.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Ellipse.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Geometry.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Geometry.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Hyperbola.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Hyperbola.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Line.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Line.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_OffsetCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_OffsetCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Parabola.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Parabola.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Point.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Point.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Transformation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Transformation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_TrimmedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_TrimmedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Vector.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_Vector.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_VectorWithMagnitude.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom2d_VectorWithMagnitude.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Axis1Placement.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Axis1Placement.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Axis2Placement.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Axis2Placement.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_AxisPlacement.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_AxisPlacement.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BSplineCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BSplineCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BSplineSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BSplineSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BezierCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BezierCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BezierSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BezierSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BoundedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BoundedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BoundedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_BoundedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_CartesianPoint.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_CartesianPoint.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Circle.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Circle.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Conic.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Conic.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_ConicalSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_ConicalSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Curve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Curve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_CylindricalSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_CylindricalSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Direction.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Direction.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_ElementarySurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_ElementarySurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Ellipse.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Ellipse.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Geometry.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Geometry.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Hyperbola.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Hyperbola.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Line.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Line.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_OffsetCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_OffsetCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_OffsetSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_OffsetSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Parabola.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Parabola.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Plane.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Plane.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Point.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Point.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_RectangularTrimmedSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_RectangularTrimmedSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SphericalSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SphericalSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Surface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Surface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SurfaceOfLinearExtrusion.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SurfaceOfLinearExtrusion.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SurfaceOfRevolution.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SurfaceOfRevolution.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SweptSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_SweptSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_ToroidalSurface.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_ToroidalSurface.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Transformation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Transformation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_TrimmedCurve.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_TrimmedCurve.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Vector.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_Vector.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_VectorWithMagnitude.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PGeom_VectorWithMagnitude.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PMMgt_PManaged.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PMMgt_PManaged.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_FieldOfHArray1OfTriangle.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_FieldOfHArray1OfTriangle.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_HArray1OfTriangle.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_HArray1OfTriangle.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Polygon2D.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Polygon2D.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Polygon3D.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Polygon3D.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_PolygonOnTriangulation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_PolygonOnTriangulation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Triangle.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Triangle.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Triangulation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PPoly_Triangulation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopLoc_Datum3D.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopLoc_Datum3D.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopLoc_ItemLocation.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopLoc_ItemLocation.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopLoc_Location.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopLoc_Location.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_CompSolid.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_CompSolid.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Compound.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Compound.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Edge.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Edge.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Face.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Face.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_FieldOfHArray1OfHShape.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_FieldOfHArray1OfHShape.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_FieldOfHArray1OfShape1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_FieldOfHArray1OfShape1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_HArray1OfHShape.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_HArray1OfHShape.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_HArray1OfShape1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_HArray1OfShape1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_HShape.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_HShape.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Shape1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Shape1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Shell.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Shell.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Solid.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Solid.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompSolid.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompSolid.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompSolid1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompSolid1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompound.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompound.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompound1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TCompound1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TEdge.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TEdge.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TEdge1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TEdge1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TFace.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TFace.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TFace1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TFace1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShape.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShape.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShape1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShape1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShell.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShell.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShell1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TShell1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TSolid.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TSolid.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TSolid1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TSolid1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TVertex.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TVertex.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TVertex1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TVertex1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TWire.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TWire.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TWire1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_TWire1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Vertex.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Vertex.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Wire.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_PTopoDS_Wire.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_Standard_Persistent.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_Standard_Persistent.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_Standard_Storable.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_Standard_Storable.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax1.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax1.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax2.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax2.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax22d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax22d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax3.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Ax3.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Circ2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Circ2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Dir.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Dir.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Dir2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Dir2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Lin2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Lin2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Mat.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Mat.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Mat2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Mat2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Pnt.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Pnt.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Pnt2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Pnt2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Trsf.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Trsf.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Trsf2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Trsf2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Vec.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Vec.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_Vec2d.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_Vec2d.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_XY.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_XY.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../drv/ShapeSchema/ShapeSchema_gp_XYZ.cxx" )
  SOURCE_GROUP (ShapeSchema FILES "../../../drv/ShapeSchema/ShapeSchema_gp_XYZ.cxx")

  list( APPEND TKShapeSchema_USED_SRCFILES "../../../src/PCDMShape/PCDMShape_Document.cxx" )
  SOURCE_GROUP (PCDMShape FILES "../../../src/PCDMShape/PCDMShape_Document.cxx")

if (WIN32)
else()

  if (APPLE)

  endif()

endif()

if ("${USED_TOOLKITS}" STREQUAL "" OR DEFINED TurnONtheTKShapeSchema)
 add_library( TKShapeSchema SHARED ${TKShapeSchema_USED_SRCFILES} )

 set_property(TARGET TKShapeSchema PROPERTY FOLDER ApplicationFramework)

 install( TARGETS TKShapeSchema
                                 RUNTIME DESTINATION "${INSTALL_DIR}/bin"
                                 ARCHIVE DESTINATION "${INSTALL_DIR}/lib"
                                 LIBRARY DESTINATION "${INSTALL_DIR}/lib")

 if (MSVC)
  install( FILES  ${CMAKE_BINARY_DIR}/out/bin/Debug/TKShapeSchema.pdb CONFIGURATIONS Debug
                                  DESTINATION "${INSTALL_DIR}/bin")
 endif()


 set_target_properties( TKShapeSchema PROPERTIES COMPILE_FLAGS "${TKShapeSchema_PRECOMPILED_DEFS}" )
 include_directories( ${TKShapeSchema_COMPILER_DIRECTORIES} )
 target_link_libraries( TKShapeSchema ${TKShapeSchema_USED_LIBS} )
endif()
