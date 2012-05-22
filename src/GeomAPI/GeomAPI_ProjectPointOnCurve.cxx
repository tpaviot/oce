// Created on: 1994-03-17
// Created by: Bruno DUMORTIER
// Copyright (c) 1994-1999 Matra Datavision
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



#include <GeomAPI_ProjectPointOnCurve.ixx>

#include <GeomAdaptor_Curve.hxx>


//=======================================================================
//function : GeomAPI_ProjectPointOnCurve
//purpose  : 
//=======================================================================
GeomAPI_ProjectPointOnCurve::GeomAPI_ProjectPointOnCurve()
{
  myIsDone = Standard_False;
}
//=======================================================================
//function : GeomAPI_ProjectPointOnCurve
//purpose  : 
//=======================================================================
  GeomAPI_ProjectPointOnCurve::GeomAPI_ProjectPointOnCurve
  (const gp_Pnt&             P, 
   const Handle(Geom_Curve)& Curve)
{
  Init(P,Curve);
}
//=======================================================================
//function : GeomAPI_ProjectPointOnCurve
//purpose  : 
//=======================================================================
  GeomAPI_ProjectPointOnCurve::GeomAPI_ProjectPointOnCurve
  (const gp_Pnt&             P, 
   const Handle(Geom_Curve)& Curve,
   const Standard_Real       Umin,
   const Standard_Real       Usup)
{
  Init(P,Curve,Umin,Usup);
}
//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
  void GeomAPI_ProjectPointOnCurve::Init
  (const gp_Pnt&             P,
   const Handle(Geom_Curve)& Curve)
{
  myC.Load(Curve);
/*
  Extrema_ExtPC theExtPC(P, myC);
  myExtPC = theExtPC;
*/
  myExtPC.Initialize(myC, myC.FirstParameter(), myC.LastParameter());
  myExtPC.Perform(P);
  
  myIsDone = myExtPC.IsDone() && ( myExtPC.NbExt() > 0);

  if ( myIsDone) {

    // evaluate the lower distance and its index;
    
    Standard_Real Dist2, Dist2Min = myExtPC.SquareDistance(1);
    myIndex = 1;
    
    for ( Standard_Integer i = 2; i <= myExtPC.NbExt(); i++) {
      Dist2 = myExtPC.SquareDistance(i);
      if ( Dist2 < Dist2Min) {
	Dist2Min = Dist2;
	myIndex = i;
      }
    }
  }
}
//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
  void GeomAPI_ProjectPointOnCurve::Init(const gp_Pnt&             P,
					 const Handle(Geom_Curve)& Curve,
					 const Standard_Real       Umin,
					 const Standard_Real       Usup )
{
  myC.Load(Curve,Umin,Usup);
/*
  Extrema_ExtPC theExtPC(P, myC);
  myExtPC = theExtPC;
*/
  myExtPC.Initialize(myC, myC.FirstParameter(), myC.LastParameter());
  myExtPC.Perform(P);
  
  myIsDone = myExtPC.IsDone() && ( myExtPC.NbExt() > 0);

  if ( myIsDone) {

    // evaluate the lower distance and its index;
    
    Standard_Real Dist2, Dist2Min = myExtPC.SquareDistance(1);
    myIndex = 1;
    
    for ( Standard_Integer i = 2; i <= myExtPC.NbExt(); i++) {
      Dist2 = myExtPC.SquareDistance(i);
      if ( Dist2 < Dist2Min) {
	Dist2Min = Dist2;
	myIndex = i;
      }
    }
  }
}
//modified by NIZNHY-PKV Wed Apr  3 17:48:51 2002f
//=======================================================================
//function : Init
//purpose  : 
//=======================================================================
  void GeomAPI_ProjectPointOnCurve::Init  (const Handle(Geom_Curve)& Curve,
					   const Standard_Real       Umin,
					   const Standard_Real       Usup )
{
  myC.Load(Curve,Umin,Usup);
  //myExtPC = Extrema_ExtPC(P, myC);
  myExtPC.Initialize(myC, Umin, Usup);
  myIsDone = Standard_False;
}
//=======================================================================
//function : Perform
//purpose  : 
//=======================================================================
  void GeomAPI_ProjectPointOnCurve::Perform(const gp_Pnt& aP3D)
{
  myExtPC.Perform(aP3D);
  
  myIsDone=myExtPC.IsDone() && ( myExtPC.NbExt() > 0);
  if (myIsDone) {
    // evaluate the lower distance and its index;
    Standard_Real Dist2, Dist2Min = myExtPC.SquareDistance(1);
    myIndex = 1;
    
    for ( Standard_Integer i = 2; i <= myExtPC.NbExt(); i++) {
      Dist2 = myExtPC.SquareDistance(i);
      if ( Dist2 < Dist2Min) {
	Dist2Min = Dist2;
	myIndex = i;
      }
    }
  }
}
//modified by NIZNHY-PKV Wed Apr  3 17:48:53 2002t 
//=======================================================================
//function : NbPoints
//purpose  : 
//=======================================================================
  Standard_Integer GeomAPI_ProjectPointOnCurve::NbPoints() const 
{
  if ( myIsDone )
    return myExtPC.NbExt();
  else
    return 0;
}
//=======================================================================
//function : Point
//purpose  : 
//=======================================================================
  gp_Pnt GeomAPI_ProjectPointOnCurve::Point(const Standard_Integer Index) const 
{
  Standard_OutOfRange_Raise_if( Index < 1 || Index > NbPoints(),
			       "GeomAPI_ProjectPointOnCurve::Point");
  return (myExtPC.Point(Index)).Value();
}


//=======================================================================
//function : Parameter
//purpose  : 
//=======================================================================

Standard_Real GeomAPI_ProjectPointOnCurve::Parameter
  (const Standard_Integer Index) const
{
  Standard_OutOfRange_Raise_if( Index < 1 || Index > NbPoints(),
			       "GeomAPI_ProjectPointOnCurve::Parameter");
  return (myExtPC.Point(Index)).Parameter();
}
//=======================================================================
//function : Parameter
//purpose  : 
//=======================================================================

void GeomAPI_ProjectPointOnCurve::Parameter
  (const Standard_Integer Index,
         Standard_Real&   U     ) const
{
  Standard_OutOfRange_Raise_if( Index < 1 || Index > NbPoints(),
			       "GeomAPI_ProjectPointOnCurve::Parameter");
  U = (myExtPC.Point(Index)).Parameter();
}
//=======================================================================
//function : Distance
//purpose  : 
//=======================================================================
Standard_Real GeomAPI_ProjectPointOnCurve::Distance
  (const Standard_Integer Index) const 
{
  Standard_OutOfRange_Raise_if( Index < 1 || Index > NbPoints(),
			       "GeomAPI_ProjectPointOnCurve::Distance");
  return sqrt (myExtPC.SquareDistance(Index));
}
//=======================================================================
//function : NearestPoint
//purpose  : 
//=======================================================================

gp_Pnt GeomAPI_ProjectPointOnCurve::NearestPoint() const 
{
  StdFail_NotDone_Raise_if 
    ( !myIsDone, "GeomAPI_ProjectPointOnCurve::NearestPoint");
			    
  return (myExtPC.Point(myIndex)).Value();
}
//=======================================================================
//function : Standard_Integer
//purpose  : 
//=======================================================================

GeomAPI_ProjectPointOnCurve::operator Standard_Integer() const
{
  return NbPoints();
}
//=======================================================================
//function : gp_Pnt
//purpose  : 
//=======================================================================

GeomAPI_ProjectPointOnCurve::operator gp_Pnt() const
{
  return NearestPoint();
}
//=======================================================================
//function : LowerDistanceParameter
//purpose  : 
//=======================================================================

Standard_Real GeomAPI_ProjectPointOnCurve::LowerDistanceParameter() const
{
  StdFail_NotDone_Raise_if
    ( !myIsDone, "GeomAPI_ProjectPointOnCurve::LowerDistanceParameter");

  return (myExtPC.Point(myIndex)).Parameter();
}
//=======================================================================
//function : LowerDistance
//purpose  : 
//=======================================================================
Standard_Real GeomAPI_ProjectPointOnCurve::LowerDistance() const
{
  StdFail_NotDone_Raise_if
    ( !myIsDone, "GeomAPI_ProjectPointOnCurve::LowerDistance");

  return sqrt (myExtPC.SquareDistance(myIndex));
}
//=======================================================================
//function : operator
//purpose  : 
//=======================================================================
GeomAPI_ProjectPointOnCurve::operator Standard_Real() const
{
  return LowerDistance();
}
