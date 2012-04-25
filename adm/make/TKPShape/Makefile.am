# Makefile.am for Open Cascade toolkit TKPShape
srcdir = @srcdir@

VPATH = @srcdir@ : \
@top_srcdir@/drv/PBRep : @top_srcdir@/src/PBRep: \
@top_srcdir@/drv/PTopoDS : @top_srcdir@/src/PTopoDS: \
@top_srcdir@/drv/PGeom : @top_srcdir@/src/PGeom: \
@top_srcdir@/drv/PGeom2d : @top_srcdir@/src/PGeom2d: \
@top_srcdir@/drv/PPoly : @top_srcdir@/src/PPoly: \
@top_srcdir@/drv/PColgp : @top_srcdir@/src/PColgp: \
@top_srcdir@/drv/PTopLoc : @top_srcdir@/src/PTopLoc: \
@top_srcdir@/drv/PColPGeom : @top_srcdir@/src/PColPGeom: \
@top_srcdir@/drv/PColPGeom2d : @top_srcdir@/src/PColPGeom2d: \
@top_srcdir@/drv/MgtBRep : @top_srcdir@/src/MgtBRep: \
@top_srcdir@/drv/MgtGeom : @top_srcdir@/src/MgtGeom: \
@top_srcdir@/drv/MgtGeom2d : @top_srcdir@/src/MgtGeom2d: \
@top_srcdir@/drv/MgtPoly : @top_srcdir@/src/MgtPoly: \
@top_srcdir@/drv/MgtTopLoc : @top_srcdir@/src/MgtTopLoc: \
@top_srcdir@/drv/MgtTopoDS : @top_srcdir@/src/MgtTopoDS


AM_CXXFLAGS = 


AM_CFLAGS = 


INCLUDES = $(CSF_OPT_INCLUDES)  \
-I@top_srcdir@/inc \
-I@top_srcdir@/drv/PBRep -I@top_srcdir@/src/PBRep \
-I@top_srcdir@/drv/PTopoDS -I@top_srcdir@/src/PTopoDS \
-I@top_srcdir@/drv/PGeom -I@top_srcdir@/src/PGeom \
-I@top_srcdir@/drv/PGeom2d -I@top_srcdir@/src/PGeom2d \
-I@top_srcdir@/drv/PPoly -I@top_srcdir@/src/PPoly \
-I@top_srcdir@/drv/PColgp -I@top_srcdir@/src/PColgp \
-I@top_srcdir@/drv/PTopLoc -I@top_srcdir@/src/PTopLoc \
-I@top_srcdir@/drv/PColPGeom -I@top_srcdir@/src/PColPGeom \
-I@top_srcdir@/drv/PColPGeom2d -I@top_srcdir@/src/PColPGeom2d \
-I@top_srcdir@/drv/MgtBRep -I@top_srcdir@/src/MgtBRep \
-I@top_srcdir@/drv/MgtGeom -I@top_srcdir@/src/MgtGeom \
-I@top_srcdir@/drv/MgtGeom2d -I@top_srcdir@/src/MgtGeom2d \
-I@top_srcdir@/drv/MgtPoly -I@top_srcdir@/src/MgtPoly \
-I@top_srcdir@/drv/MgtTopLoc -I@top_srcdir@/src/MgtTopLoc \
-I@top_srcdir@/drv/MgtTopoDS -I@top_srcdir@/src/MgtTopoDS


lib_LTLIBRARIES=libTKPShape.la

libTKPShape_la_LIBADD = $(CSF_OPT_LIBS) \
../TKMath/libTKMath.la \
../TKernel/libTKernel.la \
../TKG2d/libTKG2d.la \
../TKG3d/libTKG3d.la \
../PTKernel/libPTKernel.la \
../TKBRep/libTKBRep.la


libTKPShape_la_SOURCES = \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray1OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray1OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray2OfBSplineSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray2OfBezierSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray2OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_FieldOfHArray2OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray1OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray1OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray2OfBSplineSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray2OfBezierSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray2OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_HArray2OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray1OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBSplineSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBezierSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayNodeOfFieldOfHArray2OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray1OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBSplineSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBezierSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfBoundedSurface_0.cxx \
@top_srcdir@/drv/PColPGeom/PColPGeom_VArrayTNodeOfFieldOfHArray2OfSurface_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_FieldOfHArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_HArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_HArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_HArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_HArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayNodeOfFieldOfHArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBSplineCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBezierCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfBoundedCurve_0.cxx \
@top_srcdir@/drv/PColPGeom2d/PColPGeom2d_VArrayTNodeOfFieldOfHArray1OfCurve_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray1OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_FieldOfHArray2OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray1OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HArray2OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HSequenceOfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HSequenceOfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HSequenceOfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_HSequenceOfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqExplorerOfHSequenceOfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqExplorerOfHSequenceOfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqExplorerOfHSequenceOfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqExplorerOfHSequenceOfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqNodeOfHSequenceOfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqNodeOfHSequenceOfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqNodeOfHSequenceOfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_SeqNodeOfHSequenceOfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray1OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayNodeOfFieldOfHArray2OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray1OfXY_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfCirc2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfDir2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfDir_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfLin2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfPnt2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfPnt_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfVec2d_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfVec_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfXYZ_0.cxx \
@top_srcdir@/drv/PColgp/PColgp_VArrayTNodeOfFieldOfHArray2OfXY_0.cxx \
@top_srcdir@/drv/PPoly/PPoly_FieldOfHArray1OfTriangle_0.cxx \
@top_srcdir@/drv/PPoly/PPoly_HArray1OfTriangle_0.cxx \
@top_srcdir@/drv/PPoly/PPoly_VArrayNodeOfFieldOfHArray1OfTriangle_0.cxx \
@top_srcdir@/drv/PPoly/PPoly_VArrayTNodeOfFieldOfHArray1OfTriangle_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_FieldOfHArray1OfHShape_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_FieldOfHArray1OfShape1_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_HArray1OfHShape_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_HArray1OfShape1_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_VArrayNodeOfFieldOfHArray1OfHShape_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_VArrayNodeOfFieldOfHArray1OfShape1_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_VArrayTNodeOfFieldOfHArray1OfHShape_0.cxx \
@top_srcdir@/drv/PTopoDS/PTopoDS_VArrayTNodeOfFieldOfHArray1OfShape1_0.cxx \
@top_srcdir@/src/MgtBRep/MgtBRep.cxx \
@top_srcdir@/src/MgtBRep/MgtBRep_TranslateTool.cxx \
@top_srcdir@/src/MgtBRep/MgtBRep_TranslateTool1.cxx \
@top_srcdir@/src/MgtGeom/MgtGeom.cxx \
@top_srcdir@/src/MgtGeom2d/MgtGeom2d.cxx \
@top_srcdir@/src/MgtPoly/MgtPoly.cxx \
@top_srcdir@/src/MgtTopLoc/MgtTopLoc.cxx \
@top_srcdir@/src/MgtTopoDS/MgtTopoDS.cxx \
@top_srcdir@/src/MgtTopoDS/MgtTopoDS_TranslateTool.cxx \
@top_srcdir@/src/MgtTopoDS/MgtTopoDS_TranslateTool1.cxx \
@top_srcdir@/src/PBRep/PBRep_Curve3D.cxx \
@top_srcdir@/src/PBRep/PBRep_CurveOn2Surfaces.cxx \
@top_srcdir@/src/PBRep/PBRep_CurveOnClosedSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_CurveOnSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_CurveRepresentation.cxx \
@top_srcdir@/src/PBRep/PBRep_GCurve.cxx \
@top_srcdir@/src/PBRep/PBRep_PointOnCurve.cxx \
@top_srcdir@/src/PBRep/PBRep_PointOnCurveOnSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_PointOnSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_PointRepresentation.cxx \
@top_srcdir@/src/PBRep/PBRep_PointsOnSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_Polygon3D.cxx \
@top_srcdir@/src/PBRep/PBRep_PolygonOnClosedSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_PolygonOnClosedTriangulation.cxx \
@top_srcdir@/src/PBRep/PBRep_PolygonOnSurface.cxx \
@top_srcdir@/src/PBRep/PBRep_PolygonOnTriangulation.cxx \
@top_srcdir@/src/PBRep/PBRep_TEdge.cxx \
@top_srcdir@/src/PBRep/PBRep_TEdge1.cxx \
@top_srcdir@/src/PBRep/PBRep_TFace.cxx \
@top_srcdir@/src/PBRep/PBRep_TFace1.cxx \
@top_srcdir@/src/PBRep/PBRep_TVertex.cxx \
@top_srcdir@/src/PBRep/PBRep_TVertex1.cxx \
@top_srcdir@/src/PGeom/PGeom_Axis1Placement.cxx \
@top_srcdir@/src/PGeom/PGeom_Axis2Placement.cxx \
@top_srcdir@/src/PGeom/PGeom_AxisPlacement.cxx \
@top_srcdir@/src/PGeom/PGeom_BSplineCurve.cxx \
@top_srcdir@/src/PGeom/PGeom_BSplineSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_BezierCurve.cxx \
@top_srcdir@/src/PGeom/PGeom_BezierSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_BoundedCurve.cxx \
@top_srcdir@/src/PGeom/PGeom_BoundedSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_CartesianPoint.cxx \
@top_srcdir@/src/PGeom/PGeom_Circle.cxx \
@top_srcdir@/src/PGeom/PGeom_Conic.cxx \
@top_srcdir@/src/PGeom/PGeom_ConicalSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_Curve.cxx \
@top_srcdir@/src/PGeom/PGeom_CylindricalSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_Direction.cxx \
@top_srcdir@/src/PGeom/PGeom_ElementarySurface.cxx \
@top_srcdir@/src/PGeom/PGeom_Ellipse.cxx \
@top_srcdir@/src/PGeom/PGeom_Geometry.cxx \
@top_srcdir@/src/PGeom/PGeom_Hyperbola.cxx \
@top_srcdir@/src/PGeom/PGeom_Line.cxx \
@top_srcdir@/src/PGeom/PGeom_OffsetCurve.cxx \
@top_srcdir@/src/PGeom/PGeom_OffsetSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_Parabola.cxx \
@top_srcdir@/src/PGeom/PGeom_Plane.cxx \
@top_srcdir@/src/PGeom/PGeom_Point.cxx \
@top_srcdir@/src/PGeom/PGeom_RectangularTrimmedSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_SphericalSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_Surface.cxx \
@top_srcdir@/src/PGeom/PGeom_SurfaceOfLinearExtrusion.cxx \
@top_srcdir@/src/PGeom/PGeom_SurfaceOfRevolution.cxx \
@top_srcdir@/src/PGeom/PGeom_SweptSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_ToroidalSurface.cxx \
@top_srcdir@/src/PGeom/PGeom_Transformation.cxx \
@top_srcdir@/src/PGeom/PGeom_TrimmedCurve.cxx \
@top_srcdir@/src/PGeom/PGeom_Vector.cxx \
@top_srcdir@/src/PGeom/PGeom_VectorWithMagnitude.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_AxisPlacement.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_BSplineCurve.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_BezierCurve.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_BoundedCurve.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_CartesianPoint.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Circle.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Conic.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Curve.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Direction.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Ellipse.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Geometry.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Hyperbola.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Line.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_OffsetCurve.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Parabola.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Point.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Transformation.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_TrimmedCurve.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_Vector.cxx \
@top_srcdir@/src/PGeom2d/PGeom2d_VectorWithMagnitude.cxx \
@top_srcdir@/src/PPoly/PPoly_Polygon2D.cxx \
@top_srcdir@/src/PPoly/PPoly_Polygon3D.cxx \
@top_srcdir@/src/PPoly/PPoly_PolygonOnTriangulation.cxx \
@top_srcdir@/src/PPoly/PPoly_Triangle.cxx \
@top_srcdir@/src/PPoly/PPoly_Triangulation.cxx \
@top_srcdir@/src/PTopLoc/PTopLoc_Datum3D.cxx \
@top_srcdir@/src/PTopLoc/PTopLoc_ItemLocation.cxx \
@top_srcdir@/src/PTopLoc/PTopLoc_Location.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_CompSolid.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Compound.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Edge.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Face.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_HShape.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Shape1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Shell.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Solid.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TCompSolid.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TCompSolid1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TCompound.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TCompound1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TEdge.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TEdge1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TFace.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TFace1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TShape.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TShape1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TShell.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TShell1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TSolid.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TSolid1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TVertex.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TVertex1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TWire.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_TWire1.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Vertex.cxx \
@top_srcdir@/src/PTopoDS/PTopoDS_Wire.cxx

