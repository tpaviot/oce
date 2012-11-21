// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeAnalysis_FreeBoundsProperties_HeaderFile
#define _ShapeAnalysis_FreeBoundsProperties_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TopoDS_Shape_HeaderFile
#include <TopoDS_Shape.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_ShapeAnalysis_HSequenceOfFreeBounds_HeaderFile
#include <Handle_ShapeAnalysis_HSequenceOfFreeBounds.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_ShapeAnalysis_FreeBoundData_HeaderFile
#include <Handle_ShapeAnalysis_FreeBoundData.hxx>
#endif
class ShapeAnalysis_HSequenceOfFreeBounds;
class TopoDS_Shape;
class ShapeAnalysis_FreeBoundData;
class TopoDS_Wire;


//! This class is intended to calculate shape free bounds <br>
//!          properties. <br>
//!          This class provides the following functionalities: <br>
//!          - calculates area of the contour, <br>
//!          - calculates perimeter of the contour, <br>
//!          - calculates ratio of average length to average width of the <br>
//!            contour, <br>
//!          - estimates average width of contour, <br>
//!          - finds the notches (narrow 'V'-like sub-contour) on the <br>
//!            contour. <br>
class ShapeAnalysis_FreeBoundsProperties  {
public:

  DEFINE_STANDARD_ALLOC

  //! Empty constructor <br>
  Standard_EXPORT   ShapeAnalysis_FreeBoundsProperties();
  //! Creates the object and calls corresponding Init. <br>
//!          <shape> should be a compound of faces. <br>
  Standard_EXPORT   ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,const Standard_Real tolerance,const Standard_Boolean splitclosed = Standard_False,const Standard_Boolean splitopen = Standard_False);
  //! Creates the object and calls corresponding Init. <br>
//!          <shape> should be a compound of shells. <br>
  Standard_EXPORT   ShapeAnalysis_FreeBoundsProperties(const TopoDS_Shape& shape,const Standard_Boolean splitclosed = Standard_False,const Standard_Boolean splitopen = Standard_False);
  //! Initializes the object with given parameters. <br>
//!          <shape> should be a compound of faces. <br>
  Standard_EXPORT     void Init(const TopoDS_Shape& shape,const Standard_Real tolerance,const Standard_Boolean splitclosed = Standard_False,const Standard_Boolean splitopen = Standard_False) ;
  //! Initializes the object with given parameters. <br>
//!          <shape> should be a compound of shells. <br>
  Standard_EXPORT     void Init(const TopoDS_Shape& shape,const Standard_Boolean splitclosed = Standard_False,const Standard_Boolean splitopen = Standard_False) ;
  //! Builds and analyzes free bounds of the shape. <br>
//!          First calls ShapeAnalysis_FreeBounds for building free <br>
//!          bounds. <br>
//!          Then on each free bound computes its properties: <br>
//!          - area of the contour, <br>
//!          - perimeter of the contour, <br>
//!          - ratio of average length to average width of the contour, <br>
//!          - average width of contour, <br>
//!          - notches on the contour and for each notch <br>
//!            - maximum width of the notch. <br>
  Standard_EXPORT     Standard_Boolean Perform() ;
  //! Returns True if shape is loaded <br>
        Standard_Boolean IsLoaded() const;
  //! Returns shape <br>
        TopoDS_Shape Shape() const;
  //! Returns tolerance <br>
        Standard_Real Tolerance() const;
  //! Returns number of free bounds <br>
        Standard_Integer NbFreeBounds() const;
  //! Returns number of closed free bounds <br>
        Standard_Integer NbClosedFreeBounds() const;
  //! Returns number of open free bounds <br>
        Standard_Integer NbOpenFreeBounds() const;
  //! Returns all closed free bounds <br>
        Handle_ShapeAnalysis_HSequenceOfFreeBounds ClosedFreeBounds() const;
  //! Returns all open free bounds <br>
        Handle_ShapeAnalysis_HSequenceOfFreeBounds OpenFreeBounds() const;
  //! Returns properties of closed free bound specified by its rank <br>
//!          number <br>
        Handle_ShapeAnalysis_FreeBoundData ClosedFreeBound(const Standard_Integer index) const;
  //! Returns properties of open free bound specified by its rank <br>
//!          number <br>
        Handle_ShapeAnalysis_FreeBoundData OpenFreeBound(const Standard_Integer index) const;
  
  Standard_EXPORT     Standard_Boolean DispatchBounds() ;
  
  Standard_EXPORT     Standard_Boolean CheckContours(const Standard_Real prec = 0.0) ;
  
  Standard_EXPORT     Standard_Boolean CheckNotches(const Standard_Real prec = 0.0) ;
  
  Standard_EXPORT     Standard_Boolean CheckNotches(Handle(ShapeAnalysis_FreeBoundData)& fbData,const Standard_Real prec = 0.0) ;
  
  Standard_EXPORT     Standard_Boolean CheckNotches(const TopoDS_Wire& freebound,const Standard_Integer num,TopoDS_Wire& notch,Standard_Real& distMax,const Standard_Real prec = 0.0) ;
  
  Standard_EXPORT     Standard_Boolean FillProperties(Handle(ShapeAnalysis_FreeBoundData)& fbData,const Standard_Real prec = 0.0) ;





protected:





private:



TopoDS_Shape myShape;
Standard_Real myTolerance;
Standard_Boolean mySplitClosed;
Standard_Boolean mySplitOpen;
Handle_ShapeAnalysis_HSequenceOfFreeBounds myClosedFreeBounds;
Handle_ShapeAnalysis_HSequenceOfFreeBounds myOpenFreeBounds;


};


#include <ShapeAnalysis_FreeBoundsProperties.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
