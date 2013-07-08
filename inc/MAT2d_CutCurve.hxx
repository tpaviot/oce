// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MAT2d_CutCurve_HeaderFile
#define _MAT2d_CutCurve_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TColGeom2d_SequenceOfCurve_HeaderFile
#include <TColGeom2d_SequenceOfCurve.hxx>
#endif
#ifndef _Handle_Geom2d_Curve_HeaderFile
#include <Handle_Geom2d_Curve.hxx>
#endif
#ifndef _MAT_Side_HeaderFile
#include <MAT_Side.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Geom2d_TrimmedCurve_HeaderFile
#include <Handle_Geom2d_TrimmedCurve.hxx>
#endif
class Standard_OutOfRange;
class Geom2d_Curve;
class Geom2d_TrimmedCurve;


//! Cuts a curve at the extremas of curvature <br>
//!          and at the inflections. Constructs a trimmed <br>
//!          Curve for each interval. <br>
class MAT2d_CutCurve  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   MAT2d_CutCurve();
  
  Standard_EXPORT   MAT2d_CutCurve(const Handle(Geom2d_Curve)& C);
  //! Cuts a curve at the extremas of curvature <br>
//!          and at the inflections. <br>
  Standard_EXPORT     void Perform(const Handle(Geom2d_Curve)& C) ;
  //! Cuts a curve at the inflections, and at the extremas <br>
//!          of curvature where the concavity is on <aSide>. <br>
  Standard_EXPORT     void Perform(const Handle(Geom2d_Curve)& C,const MAT_Side aSide) ;
  //! Cuts a curve at the inflections. <br>
  Standard_EXPORT     void PerformInf(const Handle(Geom2d_Curve)& C) ;
  //! Returns True if the curve is not cut. <br>
  Standard_EXPORT     Standard_Boolean UnModified() const;
  //! Returns the number of curves. <br>
//!          it's allways greatest than 2. <br>
//! <br>//! raises if the Curve is UnModified; <br>
  Standard_EXPORT     Standard_Integer NbCurves() const;
  //! Returns the Indexth curve. <br>//! raises if Index not in the range [1,NbCurves()] <br>
  Standard_EXPORT     Handle_Geom2d_TrimmedCurve Value(const Standard_Integer Index) const;





protected:





private:



TColGeom2d_SequenceOfCurve theCurves;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
