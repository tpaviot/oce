// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntTools_FaceFace_HeaderFile
#define _IntTools_FaceFace_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _IntPatch_Intersection_HeaderFile
#include <IntPatch_Intersection.hxx>
#endif
#ifndef _IntTools_LineConstructor_HeaderFile
#include <IntTools_LineConstructor.hxx>
#endif
#ifndef _Handle_GeomAdaptor_HSurface_HeaderFile
#include <Handle_GeomAdaptor_HSurface.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _IntTools_SequenceOfCurves_HeaderFile
#include <IntTools_SequenceOfCurves.hxx>
#endif
#ifndef _TopoDS_Face_HeaderFile
#include <TopoDS_Face.hxx>
#endif
#ifndef _IntTools_SequenceOfPntOn2Faces_HeaderFile
#include <IntTools_SequenceOfPntOn2Faces.hxx>
#endif
#ifndef _IntSurf_ListOfPntOn2S_HeaderFile
#include <IntSurf_ListOfPntOn2S.hxx>
#endif
#ifndef _Handle_IntTools_Context_HeaderFile
#include <Handle_IntTools_Context.hxx>
#endif
#ifndef _Handle_Adaptor3d_TopolTool_HeaderFile
#include <Handle_Adaptor3d_TopolTool.hxx>
#endif
class GeomAdaptor_HSurface;
class IntTools_Context;
class StdFail_NotDone;
class TopoDS_Face;
class IntTools_SequenceOfCurves;
class IntTools_SequenceOfPntOn2Faces;
class IntSurf_ListOfPntOn2S;
class Adaptor3d_TopolTool;


//! This class provides the intersection of <br>
//!	    face's underlying surfaces. <br>
class IntTools_FaceFace  {
public:

  DEFINE_STANDARD_ALLOC

  
//! Empty constructor. <br>
  Standard_EXPORT   IntTools_FaceFace();
  
//! Modifier <br>
  Standard_EXPORT     void SetParameters(const Standard_Boolean ApproxCurves,const Standard_Boolean ComputeCurveOnS1,const Standard_Boolean ComputeCurveOnS2,const Standard_Real ApproximationTolerance) ;
  
//! Intersects underliing surfaces of F1 and F2 <br>
//! Use sum of tolerance of F1 and F2 as intersection <br>
//! criteria <br>
  Standard_EXPORT     void Perform(const TopoDS_Face& F1,const TopoDS_Face& F2) ;
  
//! Returns True if the intersection was successful <br>
  Standard_EXPORT     Standard_Boolean IsDone() const;
  
//! Returns sequence of 3d curves as result of intersection <br>
  Standard_EXPORT    const IntTools_SequenceOfCurves& Lines() const;
  
//! Returns sequence of 3d curves as result of intersection <br>
  Standard_EXPORT    const IntTools_SequenceOfPntOn2Faces& Points() const;
  
//! Returns tolerance reached during approximation. <br>
//! If approximation was not done, returns zero. <br>
  Standard_EXPORT     Standard_Real TolReached3d() const;
  
//! Returns tolerance reached during approximation. <br>
//! If approximation was not done, returns zero. <br>
  Standard_EXPORT     Standard_Real TolReached2d() const;
  
//! Returns first of processed faces <br>
  Standard_EXPORT    const TopoDS_Face& Face1() const;
  
//! Returns second of processed faces <br>
  Standard_EXPORT    const TopoDS_Face& Face2() const;
  
//! Returns True if faces are tangent <br>
//! <br>
  Standard_EXPORT     Standard_Boolean TangentFaces() const;
  
//! Provides post-processing the result lines. <br>
//! <bToSplit> - the flag. <br>
//!  In case of <bToSplit> is true the closed 3D-curves will be splitted <br>
//!  on parts. <br>
//!  In case of <bToSplit> is false the closed 3D-curves remain untouched. <br>
  Standard_EXPORT     void PrepareLines3D(const Standard_Boolean bToSplit = Standard_True) ;
  
  Standard_EXPORT     void SetList(IntSurf_ListOfPntOn2S& ListOfPnts) ;
  
//! Sets the intersecton context <br>
  Standard_EXPORT     void SetContext(const Handle(IntTools_Context)& aContext) ;
  
//! Gets the intersecton context <br>
//! <br>
  Standard_EXPORT    const Handle_IntTools_Context& Context() const;





protected:

  
  Standard_EXPORT     void MakeCurve(const Standard_Integer Index,const Handle(Adaptor3d_TopolTool)& D1,const Handle(Adaptor3d_TopolTool)& D2) ;
  
  Standard_EXPORT     void ComputeTolReached3d() ;




private:



Standard_Boolean myIsDone;
IntPatch_Intersection myIntersector;
IntTools_LineConstructor myLConstruct;
Handle_GeomAdaptor_HSurface myHS1;
Handle_GeomAdaptor_HSurface myHS2;
Standard_Integer myNbrestr;
Standard_Real myTolReached2d;
Standard_Real myTolReached3d;
Standard_Boolean myApprox;
Standard_Boolean myApprox1;
Standard_Boolean myApprox2;
Standard_Real myTolApprox;
IntTools_SequenceOfCurves mySeqOfCurve;
Standard_Boolean myTangentFaces;
TopoDS_Face myFace1;
TopoDS_Face myFace2;
IntTools_SequenceOfPntOn2Faces myPnts;
IntSurf_ListOfPntOn2S myListOfPnts;
Handle_IntTools_Context myContext;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
