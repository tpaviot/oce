// Created on: 1991-10-11
// Created by: Remi GILET
// Copyright (c) 1991-1999 Matra Datavision
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


//=========================================================================
//   CREATION of the BISSECTICE between a CIRCLE and a POINT.               +
//=========================================================================

#include <GccAna_CircPnt2dBisec.ixx>

#include <gp_XY.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Ax2d.hxx>
#include <GccInt_BHyper.hxx>
#include <GccInt_BCirc.hxx>
#include <GccInt_BElips.hxx>
#include <GccInt_BLine.hxx>
#include <Standard_ConstructionError.hxx>
#include <Standard_OutOfRange.hxx>
#include <StdFail_NotDone.hxx>
#include <gp.hxx>

//=========================================================================

GccAna_CircPnt2dBisec::
   GccAna_CircPnt2dBisec (const gp_Circ2d& Circle ,
		          const gp_Pnt2d&  Point  ):

   circle(Circle),
   point(Point)  {

//=========================================================================
//  Initialization of fields :                                            +
//            - circle   ( first argument.)                               +
//            - line     ( second argument.)                              +
//            - theposition (Integer showing the position of Point        +
//                           correspondingly to Circle.)                  +
//            - NbrSol   (Integer showing the number of solutions.)       +
//            - WellDone (Booleen showing the success or failure of the algorithm). +
//=========================================================================

   Standard_Real dist = Circle.Radius()-Point.Distance(Circle.Location());
//   if (Abs(dist) < gp::Resolution())
   if (Abs(dist) < 1.E-10)
     {
       theposition = 0;
       NbrSol = 1;
     }
   else if (dist > 0.0)
     {
       theposition = -1;
       NbrSol = 1;
     }
   else {
     theposition = 1;
     NbrSol = 2;
   }
   WellDone = Standard_True;
 }

//=========================================================================
//  Processing.                                                           +
//  Return the coordinates of origins of the straight line (xloc,yloc) and+
//  of the circle (xcencirc, ycencirc).                                       +
//  Also return the coordinates of the direction of the straight line (xdir,   +
//  ydir) and the radius of circle R1.                                       +
//  Check at which side of the straight line is found the center of circle    +
//  to orientate the parabola (sign).                                    +
//  Create axis of each parabola (axeparab1, axeparb2), then    +
//  two parabolas (biscirPnt1, biscirPnt1).                          +
//=========================================================================

Handle(GccInt_Bisec) GccAna_CircPnt2dBisec::
   ThisSolution (const Standard_Integer Index) const 
{
  
  if (!WellDone)
    StdFail_NotDone::Raise();
  
  if ((Index <=0) || (Index > NbrSol))
    Standard_OutOfRange::Raise();

  Handle(GccInt_Bisec) bissol;  
  Standard_Real xpoint = point.X();
  Standard_Real ypoint = point.Y();
  Standard_Real xcencir = circle.Location().X();
  Standard_Real ycencir = circle.Location().Y();
  Standard_Real R1 = circle.Radius();
  Standard_Real dist = point.Distance(circle.Location());
  //       if (dist < gp::Resolution())
  if (dist < 1.E-10)
    {
      gp_Circ2d biscirpnt1(gp_Ax2d(point,gp_Dir2d(1.0,0.0)),R1/2.);
      bissol = new GccInt_BCirc(biscirpnt1);
      //       ==========================================================
    }
  else {
    gp_Pnt2d center((xpoint+xcencir)/2.,(ypoint+ycencir)/2.);
    gp_Ax2d majax(center,gp_Dir2d(xpoint-xcencir,ypoint-ycencir));
    
    //=========================================================================
    //   The point is inside the circle.                                +
    //=========================================================================
    
    if (theposition == -1) {
      gp_Elips2d biscirpnt(majax,R1/2.,Sqrt(R1*R1-dist*dist)/2.);
      bissol = new GccInt_BElips(biscirpnt);
      //         ===========================================================
    }
    
    //=========================================================================
    //   The point is on the circle.                                          +
    //   There is only one solution : straight line passing through point and the center +
    //   of the circle.                                                           +
    //=========================================================================
    
    else if (theposition == 0) {
      gp_Dir2d dirsol;
      if (circle.IsDirect()) 
	dirsol=gp_Dir2d(xcencir-xpoint,ycencir-ypoint);
      else dirsol = gp_Dir2d(xpoint-xcencir,ypoint-ycencir);
      gp_Lin2d biscirpnt(point,dirsol);
      bissol = new GccInt_BLine(biscirpnt);
      //         =========================================================
    }
    
    //=========================================================================
    //   The point is outside of the circle.                                +
    //   There are two solutions : two main branches of the hyperbola.+
    //=========================================================================
    
    else {
      //	   Standard_Real d1 = sqrt(dist*R1-R1*R1);
      Standard_Real d1 = sqrt(dist*dist-R1*R1)/2.0;
      Standard_Real d2 = R1/2.;
      if (Index == 1) {
	gp_Hypr2d biscirpnt1(majax,d2,d1);
	bissol = new GccInt_BHyper(biscirpnt1);
	//           =========================================
      }
      else {
	gp_Hypr2d biscirpnt1(majax,d2,d1);
	gp_Hypr2d biscirpnt2 = biscirpnt1.OtherBranch();
	bissol = new GccInt_BHyper(biscirpnt2);
	//           =========================================
      }
    }
  }
  return bissol;
}


//=========================================================================

Standard_Boolean GccAna_CircPnt2dBisec::
   IsDone () const { return WellDone; }

Standard_Integer GccAna_CircPnt2dBisec::
   NbSolutions () const { return NbrSol; }


