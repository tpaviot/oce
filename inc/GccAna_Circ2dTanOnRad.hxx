// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GccAna_Circ2dTanOnRad_HeaderFile
#define _GccAna_Circ2dTanOnRad_HeaderFile

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
#ifndef _GccEnt_Position_HeaderFile
#include <GccEnt_Position.hxx>
#endif
class Standard_NegativeValue;
class Standard_OutOfRange;
class StdFail_NotDone;
class GccEnt_BadQualifier;
class GccEnt_QualifiedCirc;
class gp_Lin2d;
class GccEnt_QualifiedLin;
class gp_Pnt2d;
class gp_Circ2d;


//! This class implements the algorithms used to <br>
//!          create a 2d circle tangent to a 2d entity, <br>
//!          centered on a curv and with a given radius. <br>
//!          The arguments of all construction methods are : <br>
//!             - The qualified element for the tangency constrains <br>
//!             (QualifiedCirc, QualifiedLin, Points). <br>
//!             - The Center element (circle, line). <br>
//!             - A real Tolerance. <br>
//!          Tolerance is only used in the limits cases. <br>
//!          For example : <br>
//!          We want to create a circle tangent to an OutsideCirc C1 <br>
//!          centered on a line OnLine with a radius Radius and with <br>
//!          a tolerance Tolerance. <br>
//!          If we did not use Tolerance it is impossible to <br>
//!          find a solution in the the following case : OnLine is <br>
//!          outside C1. There is no intersection point between C1 <br>
//!          and OnLine. The distance between the line and the <br>
//!          circle is greater than Radius. <br>
//!          With Tolerance we will give a solution if the <br>
//!          distance between C1 and OnLine is lower than or <br>
//!          equal Tolerance. <br>
class GccAna_Circ2dTanOnRad  {
public:

  DEFINE_STANDARD_ALLOC

  //! This methods implements the algorithms used to create <br>
//!          2d Circles tangent to a circle and centered on a 2d Line <br>
//!          with a given radius. <br>
//!          Tolerance is used to find solution in every limit cases. <br>
//!          For example Tolerance is used in the case of EnclosedCirc when <br>
//!          Radius-R1+dist is greater Tolerance (dist is the distance <br>
//!          between the line and the location of the circ, R1 is the <br>
//!          radius of the circ) because there is no solution. <br>//! raises NegativeValue in case of NegativeRadius. <br>
  Standard_EXPORT   GccAna_Circ2dTanOnRad(const GccEnt_QualifiedCirc& Qualified1,const gp_Lin2d& OnLine,const Standard_Real Radius,const Standard_Real Tolerance);
  //! This methods implements the algorithms used to create <br>
//!          2d Circles tangent to a 2d Line and centered on a 2d Line <br>
//!          with a given radius. <br>
//!          Tolerance is used to find solution in every limit cases. <br>//! raises NegativeValue in case of NegativeRadius. <br>
  Standard_EXPORT   GccAna_Circ2dTanOnRad(const GccEnt_QualifiedLin& Qualified1,const gp_Lin2d& OnLine,const Standard_Real Radius,const Standard_Real Tolerance);
  //! This methods implements the algorithms used to create <br>
//!          2d Circles passing through a 2d Point and centered on a <br>
//!          2d Line with a given radius. <br>
//!          Tolerance is used to find solution in every limit cases. <br>
  Standard_EXPORT   GccAna_Circ2dTanOnRad(const gp_Pnt2d& Point1,const gp_Lin2d& OnLine,const Standard_Real Radius,const Standard_Real Tolerance);
  //! This methods implements the algorithms used to create <br>
//!          2d Circles tangent to a circle and centered on a 2d Circle <br>
//!          with a given radius. <br>
//!          Tolerance is used to find solution in every limit cases. <br>//! raises NegativeValue in case of NegativeRadius. <br>
  Standard_EXPORT   GccAna_Circ2dTanOnRad(const GccEnt_QualifiedCirc& Qualified1,const gp_Circ2d& OnCirc,const Standard_Real Radius,const Standard_Real Tolerance);
  //! This methods implements the algorithms used to create <br>
//!          2d Circles tangent to a 2d Line and centered on a 2d Line <br>
//!          with a given radius. <br>
//!          Tolerance is used to find solution in every limit cases. <br>//! raises NegativeValue in case of NegativeRadius. <br>
  Standard_EXPORT   GccAna_Circ2dTanOnRad(const GccEnt_QualifiedLin& Qualified1,const gp_Circ2d& OnCirc,const Standard_Real Radius,const Standard_Real Tolerance);
  //! This methods implements the algorithms used to create <br>
//!          2d Circles passing through a 2d Point and centered on a <br>
//!          2d Line with a given radius. <br>
//!          Tolerance is used to find solution in every limit cases. <br>//! raises NegativeValue in case of NegativeRadius. <br>
  Standard_EXPORT   GccAna_Circ2dTanOnRad(const gp_Pnt2d& Point1,const gp_Circ2d& OnCirc,const Standard_Real Radius,const Standard_Real Tolerance);
  //! Returns true if the construction algorithm does not fail <br>
//!          (even if it finds no solution). <br>
//!          Note: IsDone protects against a failure arising from a <br>
//!          more internal intersection algorithm, which has <br>
//!          reached its numeric limits. <br>
  Standard_EXPORT     Standard_Boolean IsDone() const;
  //! This method returns the number of circles, representing solutions. <br>
//!          Raises NotDone if the construction algorithm didn't succeed. <br>
  Standard_EXPORT     Standard_Integer NbSolutions() const;
  //! Returns the solution number Index and raises OutOfRange <br>
//!   	exception if Index is greater than the number of solutions. <br>
//!          Be careful: the Index is only a way to get all the <br>
//!          solutions, but is not associated to theses outside the <br>
//!          context of the algorithm-object. <br>
//! Raises NotDone if the construction algorithm  didn't succeed. <br>
//!          It raises OutOfRange if Index is greater than the <br>
//!          number of solutions <br>
  Standard_EXPORT     gp_Circ2d ThisSolution(const Standard_Integer Index) const;
  //! Returns the qualifier Qualif1 of the tangency argument <br>
//!     for the solution of index Index computed by this algorithm. <br>
//!     The returned qualifier is: <br>
//! -   that specified at the start of construction when the <br>
//!   solutions are defined as enclosed, enclosing or <br>
//!   outside with respect to the argument, or <br>
//! -   that computed during construction (i.e. enclosed, <br>
//!   enclosing or outside) when the solutions are defined <br>
//!   as unqualified with respect to the argument, or <br>
//! -   GccEnt_noqualifier if the tangency argument is a point. <br>
//! Exceptions <br>
//! Standard_OutOfRange if Index is less than zero or <br>
//! greater than the number of solutions computed by this algorithm. <br>
//! StdFail_NotDone if the construction fails. <br>
  Standard_EXPORT     void WhichQualifier(const Standard_Integer Index,GccEnt_Position& Qualif1) const;
  //! Returns informations about the tangency point between the <br>
//!          result number Index and the first argument. <br>
//!          ParSol is the intrinsic parameter of the point on the <br>
//!          solution curv. <br>
//!          ParArg is the intrinsic parameter of the point on the <br>
//!          argument curv. <br>
//!          PntSol is the tangency point on the solution curv. <br>
//!          PntArg is the tangency point on the argument curv. <br>
//!    Raises NotDone if the construction algorithm didn't succeed. <br>
//!          It raises OutOfRange if Index is greater than the <br>
//!          number of solutions. <br>
  Standard_EXPORT     void Tangency1(const Standard_Integer Index,Standard_Real& ParSol,Standard_Real& ParArg,gp_Pnt2d& PntSol) const;
  //! Returns informations about the center (on the curv) <br>
//!          of the result. <br>
//!          ParArg is the intrinsic parameter of the point on <br>
//!          the argument curv. <br>
//!          PntSol is the center point of the solution curv. <br>
//!    Raises NotDone if the construction algorithm  didn't succeed. <br>
//!          It raises OutOfRange if Index is greater than the <br>
//!          number of solutions. <br>
  Standard_EXPORT     void CenterOn3(const Standard_Integer Index,Standard_Real& ParArg,gp_Pnt2d& PntSol) const;
  //! Returns True if the solution number Index is equal to <br>
//!          the first argument and False in the other cases. <br>
//!    Raises NotDone if the construction algorithm  didn't succeed. <br>
//!          It raises OutOfRange if Index is greater than the <br>
//!          number of solutions. <br>
  Standard_EXPORT     Standard_Boolean IsTheSame1(const Standard_Integer Index) const;





protected:





private:



Standard_Boolean WellDone;
Standard_Integer NbrSol;
TColgp_Array1OfCirc2d cirsol;
GccEnt_Array1OfPosition qualifier1;
TColStd_Array1OfInteger TheSame1;
TColgp_Array1OfPnt2d pnttg1sol;
TColgp_Array1OfPnt2d pntcen3;
TColStd_Array1OfReal par1sol;
TColStd_Array1OfReal pararg1;
TColStd_Array1OfReal parcen3;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
