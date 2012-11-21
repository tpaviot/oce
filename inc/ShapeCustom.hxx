// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeCustom_HeaderFile
#define _ShapeCustom_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Handle_BRepTools_Modification_HeaderFile
#include <Handle_BRepTools_Modification.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_ShapeCustom_RestrictionParameters_HeaderFile
#include <Handle_ShapeCustom_RestrictionParameters.hxx>
#endif
class TopoDS_Shape;
class BRepTools_Modification;
class TopTools_DataMapOfShapeShape;
class BRepTools_Modifier;
class ShapeCustom_RestrictionParameters;
class ShapeCustom_Surface;
class ShapeCustom_Curve;
class ShapeCustom_Curve2d;
class ShapeCustom_RestrictionParameters;
class ShapeCustom_DirectModification;
class ShapeCustom_TrsfModification;
class ShapeCustom_BSplineRestriction;
class ShapeCustom_ConvertToRevolution;
class ShapeCustom_SweptToElementary;
class ShapeCustom_ConvertToBSpline;


//!  This package is intended to <br>
//! convert geometrical objects and topological. The <br>
//! modifications of one geometrical object to another <br>
//! (one) geometrical object are provided. The supported <br>
//! modifications are the following: <br>
//!    conversion of BSpline and Bezier surfaces to analytical form, <br>
//!     conversion of indirect elementary surfaces (with left-handed <br>
//!      coordinate systems) into  direct ones, <br>
//!  conversion of elementary surfaces to surfaces of revolution, <br>
//!  conversion of surface of linear extrusion, revolution, offset <br>
//!   surface to bspline, <br>
//! modification of parameterization, degree, number of segments of bspline <br>
//! surfaces,  scale the shape. <br>
class ShapeCustom  {
public:

  DEFINE_STANDARD_ALLOC

  //! Applies modifier to shape and checks sharing in the case assemblies. <br>
  Standard_EXPORT   static  TopoDS_Shape ApplyModifier(const TopoDS_Shape& S,const Handle(BRepTools_Modification)& M,TopTools_DataMapOfShapeShape& context,BRepTools_Modifier& MD) ;
  //! Returns a new shape without indirect surfaces. <br>
  Standard_EXPORT   static  TopoDS_Shape DirectFaces(const TopoDS_Shape& S) ;
  //! Returns a new shape which is scaled original <br>
  Standard_EXPORT   static  TopoDS_Shape ScaleShape(const TopoDS_Shape& S,const Standard_Real scale) ;
  //! Returns a new shape with all surfaces, curves and pcurves <br>
//!          which type is BSpline/Bezier or based on them converted <br>
//!          having Degree less than <MaxDegree> or number of spans less <br>
//!          than <NbMaxSegment> in dependence on parameter priority <Degree>. <br>
//!          <GmaxDegree> and <GMaxSegments> are maximum possible degree <br>
//!          and number of spans correspondingly. <br>
//!          These values will be used in those cases when approximation with <br>
//!          specified parameters is impossible and one of GmaxDegree or <br>
//!          GMaxSegments is selected in dependence on priority. <br>
//!          Note that even if approximation is impossible with <GMaxDegree> <br>
//!          then number of spans can exceed specified <GMaxSegment> <br>
//!          <Rational> specifies if to convert Rational BSpline/Bezier into <br>
//!          polynomial B-Spline. <br>
//!          If flags ConvOffSurf,ConvOffCurve3d,ConvOffCurve2d are Standard_True there are means <br>
//!          that Offset surfaces , Offset curves 3d and Offset curves 2d are converted to BSPline <br>
//!          correspondingly. <br>
  Standard_EXPORT   static  TopoDS_Shape BSplineRestriction(const TopoDS_Shape& S,const Standard_Real Tol3d,const Standard_Real Tol2d,const Standard_Integer MaxDegree,const Standard_Integer MaxNbSegment,const GeomAbs_Shape Continuity3d,const GeomAbs_Shape Continuity2d,const Standard_Boolean Degree,const Standard_Boolean Rational,const Handle(ShapeCustom_RestrictionParameters)& aParameters) ;
  //! Returns a new shape with all elementary periodic surfaces converted <br>
//!          to Geom_SurfaceOfRevolution <br>
  Standard_EXPORT   static  TopoDS_Shape ConvertToRevolution(const TopoDS_Shape& S) ;
  //! Returns a new shape with all surfaces of revolution and linear extrusion <br>
//!          convert to elementary periodic surfaces <br>
  Standard_EXPORT   static  TopoDS_Shape SweptToElementary(const TopoDS_Shape& S) ;
  //! Returns a new shape with all surfaces of linear extrusion, revolution, <br>
//!          offset, and planar surfaces converted according to flags to <br>
//!          Geom_BSplineSurface (with same parameterisation). <br>
  Standard_EXPORT   static  TopoDS_Shape ConvertToBSpline(const TopoDS_Shape& S,const Standard_Boolean extrMode,const Standard_Boolean revolMode,const Standard_Boolean offsetMode,const Standard_Boolean planeMode = Standard_False) ;





protected:





private:




friend class ShapeCustom_Surface;
friend class ShapeCustom_Curve;
friend class ShapeCustom_Curve2d;
friend class ShapeCustom_RestrictionParameters;
friend class ShapeCustom_DirectModification;
friend class ShapeCustom_TrsfModification;
friend class ShapeCustom_BSplineRestriction;
friend class ShapeCustom_ConvertToRevolution;
friend class ShapeCustom_SweptToElementary;
friend class ShapeCustom_ConvertToBSpline;

};





// other Inline functions and methods (like "C++: function call" methods)


#endif
