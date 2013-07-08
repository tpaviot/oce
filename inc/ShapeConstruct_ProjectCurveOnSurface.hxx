// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeConstruct_ProjectCurveOnSurface_HeaderFile
#define _ShapeConstruct_ProjectCurveOnSurface_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_ShapeConstruct_ProjectCurveOnSurface_HeaderFile
#include <Handle_ShapeConstruct_ProjectCurveOnSurface.hxx>
#endif

#ifndef _Handle_ShapeAnalysis_Surface_HeaderFile
#include <Handle_ShapeAnalysis_Surface.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _gp_Pnt_HeaderFile
#include <gp_Pnt.hxx>
#endif
#ifndef _gp_Pnt2d_HeaderFile
#include <gp_Pnt2d.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Handle_Geom_Surface_HeaderFile
#include <Handle_Geom_Surface.hxx>
#endif
#ifndef _ShapeExtend_Status_HeaderFile
#include <ShapeExtend_Status.hxx>
#endif
#ifndef _Handle_Geom_Curve_HeaderFile
#include <Handle_Geom_Curve.hxx>
#endif
#ifndef _Handle_Geom2d_Curve_HeaderFile
#include <Handle_Geom2d_Curve.hxx>
#endif
#ifndef _GeomAbs_Shape_HeaderFile
#include <GeomAbs_Shape.hxx>
#endif
#ifndef _Handle_TColgp_HArray1OfPnt2d_HeaderFile
#include <Handle_TColgp_HArray1OfPnt2d.hxx>
#endif
#ifndef _Handle_TColStd_HArray1OfReal_HeaderFile
#include <Handle_TColStd_HArray1OfReal.hxx>
#endif
#ifndef _Handle_TColgp_HArray1OfPnt_HeaderFile
#include <Handle_TColgp_HArray1OfPnt.hxx>
#endif
class ShapeAnalysis_Surface;
class Geom_Surface;
class Geom_Curve;
class Geom2d_Curve;
class TColgp_Array1OfPnt;
class TColStd_Array1OfReal;
class TColgp_Array1OfPnt2d;
class TColgp_HArray1OfPnt2d;
class TColStd_HArray1OfReal;
class TColgp_HArray1OfPnt;
class gp_Pnt2d;


//! This tool provides a method for computing pcurve by projecting <br>
//!          3d curve onto a surface. <br>
//!          Projection is done by 23 or more points (this number is changed <br>
//!          for B-Splines according to the following rule: <br>
//!          the total number of the points is not less than number of spans * <br>
//!          (degree + 1); <br>
//!          it is increased recursively starting with 23 and is added with 22 <br>
//!          until the condition is fulfilled). <br>
//!          Isoparametric cases (if curve corresponds to U=const or V=const on <br>
//!          the surface) are recognized with the given precision. <br>
class ShapeConstruct_ProjectCurveOnSurface : public MMgt_TShared {

public:

  //! Empty constructor. <br>
  Standard_EXPORT   ShapeConstruct_ProjectCurveOnSurface();
  //! Initializes the object with all necessary parameters, <br>
//!          i.e. surface and precision <br>
  Standard_EXPORT   virtual  void Init(const Handle(Geom_Surface)& surf,const Standard_Real preci) ;
  //! Initializes the object with all necessary parameters, <br>
//!          i.e. surface and precision <br>
  Standard_EXPORT   virtual  void Init(const Handle(ShapeAnalysis_Surface)& surf,const Standard_Real preci) ;
  //! Loads a surface (in the form of Geom_Surface) to project on <br>
  Standard_EXPORT     void SetSurface(const Handle(Geom_Surface)& surf) ;
  //! Loads a surface (in the form of ShapeAnalysis_Surface) to project on <br>
  Standard_EXPORT     void SetSurface(const Handle(ShapeAnalysis_Surface)& surf) ;
  //! Sets value for current precision <br>
  Standard_EXPORT     void SetPrecision(const Standard_Real preci) ;
  //! Returns (modifiable) the build-curve-3d mode, by default False <br>
//!           If True, if the projected curve has been recomputed by <br>
//!           interpolation, the 3d curve is also rebuild by interpolation <br>
  Standard_EXPORT     Standard_Boolean& BuildCurveMode() ;
  //! Returns (modifiable) the flag specifying to which side of <br>
//!           parametrical space adjust part of pcurve which lies on seam. <br>
//!           This is required in very rare case when 3d curve which is <br>
//!           to be projected goes partly along the seam on the closed <br>
//!           surface with singularity (e.g. sphere), goes through the <br>
//!           degenerated point and paerly lies on internal area of surface. <br>
//! <br>
//!           If this flag is True, the seam part of such curve will be <br>
//!           adjusted to the left side of parametric space (on sphere U=0), <br>
//!           else to the right side (on sphere U=2*PI) <br>
//!           Default value is True <br>
  Standard_EXPORT     Standard_Integer& AdjustOverDegenMode() ;
  //! Returns the status of last Peform <br>
  Standard_EXPORT     Standard_Boolean Status(const ShapeExtend_Status Status) const;
  //! Computes the projection of 3d curve onto a surface using the <br>
//!          standard algorithm from ProjLib. Returns False if standard <br>
//!          projector fails or raises an exception or cuts the curve by <br>
//!          parametrical bounds of the surface. Else, if pcurve computed <br>
//!          successfully, returns True. <br>
//!          The continuity, maxdeg and nbinterval are parameters of call <br>
//!          to Approx_CurveOnSurface. If nbinterval is equal to -1 <br>
//!          (default), this value is computed depending on source 3d curve <br>
//!          and surface. <br>
  Standard_EXPORT   virtual  Standard_Boolean Perform(Handle(Geom_Curve)& c3d,const Standard_Real First,const Standard_Real Last,Handle(Geom2d_Curve)& c2d,const GeomAbs_Shape continuity = GeomAbs_C1,const Standard_Integer maxdeg = 12,const Standard_Integer nbinterval = -1) ;
  //! Computes the projection of 3d curve onto a surface using the <br>
//!          standard algorithm from ProjLib. Returns False if standard <br>
//!          projector fails or raises an exception or cuts the curve by <br>
//!          parametrical bounds of the surface. Else, if pcurve computed <br>
//!          successfully, returns True. <br>
//!          The continuity, maxdeg and nbinterval are parameters of call <br>
//!          to Approx_CurveOnSurface. If nbinterval is equal to -1 <br>
//!          (default), this value is computed depending on source 3d curve <br>
//!          and surface. <br>
  Standard_EXPORT     Standard_Boolean PerformByProjLib(Handle(Geom_Curve)& c3d,const Standard_Real First,const Standard_Real Last,Handle(Geom2d_Curve)& c2d,const GeomAbs_Shape continuity = GeomAbs_C1,const Standard_Integer maxdeg = 12,const Standard_Integer nbinterval = -1) ;
  //! Computes the projection of 3d curve onto a surface using <br>
//!          either standard projector (method PerformByStandard()) or <br>
//!          internal one (method Perform()). The selection is done by <br>
//!          analyzing the surface and 3d curve and is aimed to filter <br>
//!          the cases potentially dangerous for the standard projector. <br>
//!          If the standard projector fails, internal one is used. <br>
  Standard_EXPORT     Standard_Boolean PerformAdvanced(Handle(Geom_Curve)& c3d,const Standard_Real First,const Standard_Real Last,Handle(Geom2d_Curve)& c2d) ;




  DEFINE_STANDARD_RTTI(ShapeConstruct_ProjectCurveOnSurface)

protected:


Handle_ShapeAnalysis_Surface mySurf;
Standard_Real myPreci;
Standard_Boolean myBuild;
Standard_Integer myStatus;
Standard_Integer myAdjustOverDegen;
Standard_Integer myNbCashe;
gp_Pnt myCashe3d[2];
gp_Pnt2d myCashe2d[2];


private: 

  
  Standard_EXPORT     Handle_Geom2d_Curve ProjectAnalytic(const Handle(Geom_Curve)& c3d) const;
  
  Standard_EXPORT     Standard_Boolean ApproxPCurve(const Standard_Integer nbrPnt,const TColgp_Array1OfPnt& points,const TColStd_Array1OfReal& params,TColgp_Array1OfPnt2d& points2d,Handle(Geom2d_Curve)& c2d) ;
  
  Standard_EXPORT     Handle_Geom2d_Curve InterpolatePCurve(const Standard_Integer nbrPnt,Handle(TColgp_HArray1OfPnt2d)& points2d,Handle(TColStd_HArray1OfReal)& params,const Handle(Geom_Curve)& orig) const;
  
  Standard_EXPORT     Handle_Geom2d_Curve ApproximatePCurve(const Standard_Integer nbrPnt,Handle(TColgp_HArray1OfPnt2d)& points2d,Handle(TColStd_HArray1OfReal)& params,const Handle(Geom_Curve)& orig) const;
  
  Standard_EXPORT     Handle_Geom_Curve InterpolateCurve3d(const Standard_Integer nbrPnt,Handle(TColgp_HArray1OfPnt)& points,Handle(TColStd_HArray1OfReal)& params,const Handle(Geom_Curve)& orig) const;
  
  Standard_EXPORT     void CheckPoints(Handle(TColgp_HArray1OfPnt)& points,Handle(TColStd_HArray1OfReal)& params,Standard_Real& preci) const;
  
  Standard_EXPORT     void CheckPoints2d(Handle(TColgp_HArray1OfPnt2d)& points,Handle(TColStd_HArray1OfReal)& params,Standard_Real& preci) const;
  
  Standard_EXPORT     Standard_Boolean IsAnIsoparametric(const Standard_Integer nbrPnt,const TColgp_Array1OfPnt& points,const TColStd_Array1OfReal& params,Standard_Boolean& isoTypeU,Standard_Boolean& p1OnIso,gp_Pnt2d& valueP1,Standard_Boolean& p2OnIso,gp_Pnt2d& valueP2,Standard_Boolean& isoPar2d3d,Handle(Geom_Curve)& cIso,Standard_Real& t1,Standard_Real& t2,TColStd_Array1OfReal& pout) const;



};





// other Inline functions and methods (like "C++: function call" methods)


#endif
