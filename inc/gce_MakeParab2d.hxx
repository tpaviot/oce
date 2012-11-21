// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _gce_MakeParab2d_HeaderFile
#define _gce_MakeParab2d_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _gp_Parab2d_HeaderFile
#include <gp_Parab2d.hxx>
#endif
#ifndef _gce_Root_HeaderFile
#include <gce_Root.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class StdFail_NotDone;
class gp_Ax2d;
class gp_Ax22d;
class gp_Pnt2d;
class gp_Parab2d;


//!This class implements the following algorithms used to <br>
//!          create Parab2d from gp. <br>
//!  Defines an infinite parabola. <br>
//!  An axis placement one axis defines the local cartesian <br>
//!  coordinate system ("XAxis") of the parabola. <br>
//!  The vertex of the parabola is the "Location" point of the <br>
//!  local coordinate system of the parabola. <br>
//!  The "XAxis" of the parabola is its axis of symmetry. <br>
//!  The "XAxis" is oriented from the vertex of the parabola to the <br>
//!  Focus of the parabola. <br>
//!  The "YAxis" is parallel to the directrix of the parabola and <br>
//!  its "Location" point is the vertex of the parabola. <br>
//!  The equation of the parabola in the local coordinate system is <br>
//!  Y**2 = (2*P) * X <br>
//!  P is the distance between the focus and the directrix of the <br>
//!  parabola called Parameter). <br>
//!  The focal length F = P/2 is the distance between the vertex <br>
//!  and the focus of the parabola. <br>
//! <br>
//!          * Create a Parab2d from one apex  and the center. <br>
//!          * Create a Parab2d with the directrix and the focus point. <br>
//!          * Create a Parab2d with its vertex point and its axis <br>
//!            of symetry and its focus length. <br>
class gce_MakeParab2d  : public gce_Root {
public:

  DEFINE_STANDARD_ALLOC

  
//!  Creates a parabola with its axis of symmetry ("MirrorAxis") <br>
//!  and its focal length. <br>
//! Warnings : It is possible to have Focal = 0. <br>
//!  The status is "NullFocalLength" Raised if Focal < 0.0 <br>
  Standard_EXPORT   gce_MakeParab2d(const gp_Ax2d& MirrorAxis,const Standard_Real Focal,const Standard_Boolean Sense = Standard_True);
  
//!  Creates a parabola with its local coordinate system <A> <br>
//!  and its focal length. <br>
//! Warnings : It is possible to have Focal = 0. <br>
//!  The status is "NullFocalLength" Raised if Focal < 0.0 <br>
  Standard_EXPORT   gce_MakeParab2d(const gp_Ax22d& A,const Standard_Real Focal);
  
//!  Creates a parabola with the directrix and the focus point. <br>
//!  The sense of parametrization is given by Sense. <br>
  Standard_EXPORT   gce_MakeParab2d(const gp_Ax2d& D,const gp_Pnt2d& F,const Standard_Boolean Sense = Standard_True);
  
//!  Creates a parabola with the local coordinate system and <br>
//!  the focus point. <br>
//!  The sense of parametrization is given by Sense. <br>
  Standard_EXPORT   gce_MakeParab2d(const gp_Ax22d& D,const gp_Pnt2d& F);
  //! Make an Parab2d with S1 as the Focal point and Center <br>
//!          as the apex of the parabola <br>
//!	Warning <br>
//! The MakeParab2d class does not prevent the <br>
//! construction of a parabola with a null focal distance. <br>
//! If an error occurs (that is, when IsDone returns <br>
//! false), the Status function returns: <br>
//! -   gce_NullFocusLength if Focal is less than 0.0, or <br>
//! -   gce_NullAxis if S1 and Center are coincident. <br>
  Standard_EXPORT   gce_MakeParab2d(const gp_Pnt2d& S1,const gp_Pnt2d& Center,const Standard_Boolean Sense = Standard_True);
  //! Returns the constructed parabola. <br>
//! Exceptions StdFail_NotDone if no parabola is constructed. <br>
  Standard_EXPORT    const gp_Parab2d& Value() const;
  
  Standard_EXPORT    const gp_Parab2d& Operator() const;
Standard_EXPORT operator gp_Parab2d() const;





protected:





private:



gp_Parab2d TheParab2d;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
