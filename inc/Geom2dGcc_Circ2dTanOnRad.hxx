// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Geom2dGcc_Circ2dTanOnRad_HeaderFile
#define _Geom2dGcc_Circ2dTanOnRad_HeaderFile

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
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _TColgp_Array1OfCirc2d_HeaderFile
#include <TColgp_Array1OfCirc2d.hxx>
#endif
#ifndef _GccEnt_Array1OfPosition_HeaderFile
#include <GccEnt_Array1OfPosition.hxx>
#endif
#ifndef _TColStd_Array1OfInteger_HeaderFile
#include <TColStd_Array1OfInteger.hxx>
#endif
#ifndef _TColgp_Array1OfPnt2d_HeaderFile
#include <TColgp_Array1OfPnt2d.hxx>
#endif
#ifndef _TColStd_Array1OfReal_HeaderFile
#include <TColStd_Array1OfReal.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Handle_Geom2d_Point_HeaderFile
#include <Handle_Geom2d_Point.hxx>
#endif
#ifndef _GccEnt_Position_HeaderFile
#include <GccEnt_Position.hxx>
#endif
class Standard_NegativeValue;
class Standard_OutOfRange;
class GccEnt_BadQualifier;
class StdFail_NotDone;
class Geom2dGcc_QualifiedCurve;
class Geom2dAdaptor_Curve;
class Geom2d_Point;
class GccAna_Circ2dTanOnRad;
class Geom2dGcc_MyCirc2dTanOnRad;
class gp_Circ2d;
class gp_Pnt2d;


//! This class implements the algorithms used to <br>
//!          create a 2d circle tangent to a 2d entity, <br>
//!          centered on a 2d entity and with a given radius. <br>
//!          More than one argument must be a curve. <br>
//!          The arguments of all construction methods are : <br>
//!             - The qualified element for the tangency constrains <br>
//!             (QualifiedCirc, QualifiedLin, QualifiedCurvPoints). <br>
//!             - The Center element (circle, line, curve). <br>
//!             - A real Tolerance. <br>
//!          Tolerance is only used in the limits cases. <br>
//!          For example : <br>
//!          We want to create a circle tangent to an OutsideCurv Cu1 <br>
//!          centered on a line OnLine with a radius Radius and with <br>
//!          a tolerance Tolerance. <br>
//!          If we did not used Tolerance it is impossible to <br>
//!          find a solution in the the following case : OnLine is <br>
//!          outside Cu1. There is no intersection point between Cu1 <br>
//!          and OnLine. The distance between the line and the <br>
//!          circle is greater than Radius. <br>
//!          With Tolerance we will give a solution if the <br>
//!          distance between Cu1 and OnLine is lower than or <br>
//!          equal Tolerance. <br>
class Geom2dGcc_Circ2dTanOnRad  {
public:

  DEFINE_STANDARD_ALLOC

  //! Constructs one or more 2D circles of radius Radius, <br>
//! centered on the 2D curve OnCurv and: <br>
//! -   tangential to the curve Qualified1 <br>
  Standard_EXPORT   Geom2dGcc_Circ2dTanOnRad(const Geom2dGcc_QualifiedCurve& Qualified1,const Geom2dAdaptor_Curve& OnCurv,const Standard_Real Radius,const Standard_Real Tolerance);
  //! Constructs one or more 2D circles of radius Radius, <br>
//! centered on the 2D curve OnCurv and: <br>
//! passing through the point Point1. <br>
//!  OnCurv is an adapted curve, i.e. an object which is an <br>
//! interface between: <br>
//! -   the services provided by a 2D curve from the package Geom2d, <br>
//! -   and those required on the curve by the construction algorithm. <br>
//! Similarly, the qualified curve Qualified1 is created from <br>
//! an adapted curve. <br>
//! Adapted curves are created in the following way: <br>
//! Handle(Geom2d_Curve) myCurveOn = ... ; <br>
//! Geom2dAdaptor_Curve OnCurv ( myCurveOn ) ; <br>
//! The algorithm is then constructed with this object: <br>
//! Handle(Geom2d_Curve) myCurve1 = ... <br>
//! ; <br>
//! Geom2dAdaptor_Curve Adapted1 ( myCurve1 ) ; <br>
//! Geom2dGcc_QualifiedCurve <br>
//!           Qualified1 = Geom2dGcc::Outside(Adapted1); <br>
//! Standard_Real Radius = ... , Tolerance = ... ; <br>
//! Geom2dGcc_Circ2dTanOnRad <br>
//!             myAlgo ( Qualified1 , OnCurv , Radius , Tolerance ) ; <br>
//! if ( myAlgo.IsDone() ) <br>
//!     { Standard_Integer Nbr = myAlgo.NbSolutions() ; <br>
//!     gp_Circ2d Circ ; <br>
//!     for ( Standard_Integer i = 1 ; <br>
//! i <= nbr ; i++ ) <br>
//!        { Circ = myAlgo.ThisSolution (i) ; <br>
//!           ... <br>
//!        } <br>
//!     } <br>
  Standard_EXPORT   Geom2dGcc_Circ2dTanOnRad(const Handle(Geom2d_Point)& Point1,const Geom2dAdaptor_Curve& OnCurv,const Standard_Real Radius,const Standard_Real Tolerance);
  
  Standard_EXPORT     void Results(const GccAna_Circ2dTanOnRad& Circ) ;
  
  Standard_EXPORT     void Results(const Geom2dGcc_MyCirc2dTanOnRad& Circ) ;
  //! Returns true if the construction algorithm does not fail <br>
//! (even if it finds no solution). <br>
//! Note: IsDone protects against a failure arising from a <br>
//! more internal intersection algorithm which has reached <br>
//! its numeric limits. <br>
  Standard_EXPORT     Standard_Boolean IsDone() const;
  //! Returns the number of circles, representing solutions <br>
//! computed by this algorithm. <br>
//! Exceptions: StdFail_NotDone if the construction fails. <br>
  Standard_EXPORT     Standard_Integer NbSolutions() const;
  //! Returns the solution number Index and raises OutOfRange <br>
//! exception if Index is greater than the number of solutions. <br>
//! Be carefull: the Index is only a way to get all the <br>
//! solutions, but is not associated to theses outside the context <br>
//! of the algorithm-object. <br>
//! Exceptions <br>
//! Standard_OutOfRange if Index is less than zero or <br>
//! greater than the number of solutions computed by this algorithm. <br>
//! StdFail_NotDone if the construction fails. <br>
  Standard_EXPORT     gp_Circ2d ThisSolution(const Standard_Integer Index) const;
  //! Returns the qualifier Qualif1 of the tangency argument <br>
//! for the solution of index Index computed by this algorithm. <br>
//! The returned qualifier is: <br>
//! -   that specified at the start of construction when the <br>
//!   solutions are defined as enclosed, enclosing or <br>
//!   outside with respect to the arguments, or <br>
//! -   that computed during construction (i.e. enclosed, <br>
//!   enclosing or outside) when the solutions are defined <br>
//!   as unqualified with respect to the arguments, or <br>
//! -   GccEnt_noqualifier if the tangency argument is a point. <br>
//!  Exceptions <br>
//! Standard_OutOfRange if Index is less than zero or <br>
//! greater than the number of solutions computed by this algorithm. <br>
//! StdFail_NotDone if the construction fails. <br>
  Standard_EXPORT     void WhichQualifier(const Standard_Integer Index,GccEnt_Position& Qualif1) const;
  //! Returns informations about the tangency point between the <br>
//! result number Index and the first argument. <br>
//! ParSol is the intrinsic parameter of the point on the solution curv. <br>
//! ParArg is the intrinsic parameter of the point on the argument curv. <br>
//! PntSol is the tangency point on the solution curv. <br>
//! PntArg is the tangency point on the argument curv. <br>
//! Exceptions <br>
//! Standard_OutOfRange if Index is less than zero or <br>
//! greater than the number of solutions computed by this algorithm. <br>
//! StdFail_NotDone if the construction fails. <br>
  Standard_EXPORT     void Tangency1(const Standard_Integer Index,Standard_Real& ParSol,Standard_Real& ParArg,gp_Pnt2d& PntSol) const;
  //! Returns the center PntSol on the second argument (i.e. <br>
//! line or circle) of the solution of index Index computed by <br>
//! this algorithm. <br>
//! ParArg is the intrinsic parameter of the point on the argument curv. <br>
//! PntSol is the center point of the solution curv. <br>
//! PntArg is the projection of PntSol on the argument curv. <br>
//! Exceptions: <br>
//! Standard_OutOfRange if Index is less than zero or <br>
//! greater than the number of solutions computed by this algorithm. <br>
//! StdFail_NotDone if the construction fails. <br>
  Standard_EXPORT     void CenterOn3(const Standard_Integer Index,Standard_Real& ParArg,gp_Pnt2d& PntSol) const;
  //! Returns true if the solution of index Index and the first <br>
//! argument of this algorithm are the same (i.e. there are 2 <br>
//! identical circles). <br>
//! If Rarg is the radius of the first argument, Rsol is the <br>
//! radius of the solution and dist is the distance between <br>
//! the two centers, we consider the two circles to be <br>
//! identical if |Rarg - Rsol| and dist are less than <br>
//! or equal to the tolerance criterion given at the time of <br>
//! construction of this algorithm. <br>
//! OutOfRange is raised if Index is greater than the number of solutions. <br>
//! notDone is raised if the construction algorithm did not succeed. <br>
  Standard_EXPORT     Standard_Boolean IsTheSame1(const Standard_Integer Index) const;





protected:





private:



Standard_Boolean WellDone;
Standard_Integer NbrSol;
TColgp_Array1OfCirc2d cirsol;
GccEnt_Array1OfPosition qualifier1;
TColStd_Array1OfInteger TheSame1;
TColgp_Array1OfPnt2d pnttg1sol;
TColStd_Array1OfReal par1sol;
TColStd_Array1OfReal pararg1;
TColgp_Array1OfPnt2d pntcen3;
TColStd_Array1OfReal parcen3;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
