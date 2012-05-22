// Copyright (c) 1995-1999 Matra Datavision
// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

#include <GccAna_Circ2dTanOnRad.jxx>

#include <ElCLib.hxx>
#include <IntAna2d_AnaIntersection.hxx>
#include <IntAna2d_IntPoint.hxx>
#include <Standard_NegativeValue.hxx>
#include <Standard_OutOfRange.hxx>
#include <gp_Dir2d.hxx>

//=========================================================================
//   Circle tangent to a point   Point1.                                  +
//          center on circle     OnCirc.                                  +
//          radius               Radius.                                  +
//                                                                        +
//  Initialize the table of solutions cirsol and all fields.              +
//  Eliminate cases not being the solution.                               +
//  Create the circle with center in Point1 of radius Radius.             +
//  Intersect this circle with OnCirc and obtain the center points        +
//  of found solutions.                                                   +
//  Create solutions cirsol.                                              +
//=========================================================================

GccAna_Circ2dTanOnRad::
   GccAna_Circ2dTanOnRad (const gp_Pnt2d&     Point1    ,
                          const gp_Circ2d&    OnCirc    ,
                          const Standard_Real Radius    ,
                          const Standard_Real Tolerance ):
   cirsol(1,2)   ,
   qualifier1(1,2) ,
   TheSame1(1,2) ,
   pnttg1sol(1,2),
   pntcen3(1,2)  ,
   par1sol(1,2)  ,
   pararg1(1,2)  ,
   parcen3(1,2)  
{

   gp_Dir2d dirx(1.0,0.0);
   Standard_Real Tol = Abs(Tolerance);
   WellDone = Standard_False;
   NbrSol = 0;
   Standard_Real Roncirc = OnCirc.Radius();
   Standard_Real dist1 = Point1.Distance(OnCirc.Location())-Roncirc;
   Standard_Real dist2 = Point1.Distance(OnCirc.Location())+Roncirc;

   if (Radius < 0.0) { Standard_NegativeValue::Raise(); }
   else if ((dist1-Radius > Tol) || (Tol < Radius-dist2)) { 
     WellDone = Standard_True; 
   }
   else {
     Standard_Integer signe = 0;
     if (Abs(dist1-Radius) < Tol) { signe = 1; }
     else if (Abs(dist2-Radius) < Tol) { signe = -1; }
     if (signe != 0) {
       gp_Ax2d axe(gp_Pnt2d(OnCirc.Location().XY()-Roncirc*
			 gp_Dir2d(OnCirc.Location().X()-signe*Point1.X(),
			   OnCirc.Location().Y()-signe*Point1.Y()).XY()),dirx);
       cirsol(1) = gp_Circ2d(axe,Radius);
//      ================================
       qualifier1(1) = GccEnt_noqualifier;
       TheSame1(1) = 0;
       pnttg1sol(1) = Point1;
       pntcen3(1) = cirsol(1).Location();
       pararg1(1) = 0.0;
       par1sol(1)=ElCLib::Parameter(cirsol(1),pnttg1sol(1));
       parcen3(1) = ElCLib::Parameter(OnCirc,pntcen3(1));
       WellDone = Standard_True;
       NbrSol = 1;
     }
     else {
       IntAna2d_AnaIntersection Intp(OnCirc,gp_Circ2d(gp_Ax2d(Point1,dirx),
						      Radius));
       if (Intp.IsDone()) {
	 if (!Intp.IsEmpty()) {
	   for (Standard_Integer i = 1 ; i <= Intp.NbPoints() ; i++) {
	     NbrSol++;
	     gp_Pnt2d Center(Intp.Point(i).Value());
	     cirsol(NbrSol) = gp_Circ2d(gp_Ax2d(Center,dirx),Radius);
//           =======================================================
       qualifier1(1) = GccEnt_noqualifier;
	     TheSame1(1) = 0;
	     pnttg1sol(1) = Point1;
	     pntcen3(1) = cirsol(1).Location();
	     par1sol(1)=ElCLib::Parameter(cirsol(1),pnttg1sol(1));
	     parcen3(1) = ElCLib::Parameter(OnCirc,pntcen3(1));
	     pararg1(1) = 0.0;
	   }
	 }
	 WellDone = Standard_True;
       }
     }
   }
 }
