// Created on: 1995-08-04
// Created by: Modelistation
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


// Great zoom leads to non-coincidence of
// a point and non-infinite lines passing throught this point:
#define OCC64 

#include <StdPrs_Curve.ixx>

#include <Graphic3d_ArrayOfSegments.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_Group.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_Arrow.hxx>
#include <Prs3d_ArrowAspect.hxx>
#include <gp_Pnt.hxx>
#include <gp_Circ.hxx>
#include <gp_Dir.hxx>
#include <gp_Vec.hxx>
#include <Prs3d.hxx>
#include <Bnd_Box.hxx>
#include <Precision.hxx>
#include <TColgp_SequenceOfPnt.hxx>


//==================================================================
// function: FindLimits
// purpose:
//==================================================================
static void FindLimits(const Adaptor3d_Curve& aCurve,
                       const Standard_Real  aLimit,
                       Standard_Real&       First,
                       Standard_Real&       Last)
{
  First = aCurve.FirstParameter();
  Last  = aCurve.LastParameter();
  Standard_Boolean firstInf = Precision::IsNegativeInfinite(First);
  Standard_Boolean lastInf  = Precision::IsPositiveInfinite(Last);

  if (firstInf || lastInf) {
    gp_Pnt P1,P2;
    Standard_Real delta = 1;
    if (firstInf && lastInf) {
      do {
        delta *= 2;
        First = - delta;
        Last  =   delta;
        aCurve.D0(First,P1);
        aCurve.D0(Last,P2);
      } while (P1.Distance(P2) < aLimit);
    }
    else if (firstInf) {
      aCurve.D0(Last,P2);
      do {
        delta *= 2;
        First = Last - delta;
        aCurve.D0(First,P1);
      } while (P1.Distance(P2) < aLimit);
    }
    else if (lastInf) {
      aCurve.D0(First,P1);
      do {
        delta *= 2;
        Last = First + delta;
        aCurve.D0(Last,P2);
      } while (P1.Distance(P2) < aLimit);
    }
  }    
}


//==================================================================
// function: DrawCurve
// purpose:
//==================================================================
static void DrawCurve (const Adaptor3d_Curve&        aCurve,
                       const Handle(Graphic3d_Group) aGroup,
                       const Standard_Integer        NbP,
                       const Standard_Real           U1,
                       const Standard_Real           U2,
                       TColgp_SequenceOfPnt&         Points,
                       const Standard_Boolean drawCurve)
{
  Standard_Integer nbintervals = 1;

  if (aCurve.GetType() == GeomAbs_BSplineCurve) {
    nbintervals = aCurve.NbKnots() - 1;
    nbintervals = Max(1, nbintervals/3);
  }

  switch (aCurve.GetType())
  {
    case GeomAbs_Line:
    {
      gp_Pnt p1 = aCurve.Value(U1);
      gp_Pnt p2 = aCurve.Value(U2);
      Points.Append(p1);
      Points.Append(p2);
      if(drawCurve)
      {
        Handle(Graphic3d_ArrayOfSegments) aPrims = new Graphic3d_ArrayOfSegments(2);
        aPrims->AddVertex(p1);
        aPrims->AddVertex(p2);
        aGroup->AddPrimitiveArray(aPrims);
      }
    }
    break;
    default:
    {
      const Standard_Integer N = Max(2, NbP*nbintervals);
      const Standard_Real DU = (U2-U1) / (N-1);
      gp_Pnt p;

      Handle(Graphic3d_ArrayOfPolylines) aPrims;
      if(drawCurve)
        aPrims = new Graphic3d_ArrayOfPolylines(N);

      for (Standard_Integer i = 1; i <= N;i++) {
        p = aCurve.Value(U1 + (i-1)*DU);
        Points.Append(p);
        if(drawCurve)
          aPrims->AddVertex(p);
      }
      if(drawCurve)
        aGroup->AddPrimitiveArray(aPrims);
    }
  }
}


//==================================================================
// function: MatchCurve
// purpose:
//==================================================================
static Standard_Boolean MatchCurve (
		       const Quantity_Length  X,
		       const Quantity_Length  Y,
		       const Quantity_Length  Z,
		       const Quantity_Length  aDistance,
		       const Adaptor3d_Curve&   aCurve,
		       const Quantity_Length  TheDeflection,
		       const Standard_Integer NbP,
		       const Standard_Real    U1,
		       const Standard_Real    U2)
{
  Quantity_Length retdist;
  switch (aCurve.GetType())
  {
    case GeomAbs_Line:
    {
      gp_Pnt p1 = aCurve.Value(U1);
      if ( Abs(X-p1.X()) + Abs(Y-p1.Y()) + Abs(Z-p1.Z()) <= aDistance)
        return Standard_True;
      gp_Pnt p2 = aCurve.Value(U2);
      if ( Abs(X-p2.X()) + Abs(Y-p2.Y()) + Abs(Z-p2.Z()) <= aDistance)
        return Standard_True;
      return Prs3d::MatchSegment(X,Y,Z,aDistance,p1,p2,retdist);
    }
    case GeomAbs_Circle:
    {
      const Standard_Real Radius = aCurve.Circle().Radius();
      const Standard_Real DU = Sqrt(8.0 * TheDeflection / Radius);
      const Standard_Real Er = Abs( U2 - U1) / DU;
      const Standard_Integer N = Max(2, (Standard_Integer)IntegerPart(Er));
      if ( N > 0) {
        gp_Pnt p1,p2;
        for (Standard_Integer Index = 1; Index <= N+1; Index++) {
          p2 = aCurve.Value(U1 + (Index - 1) * DU);
          if ( Abs(X-p2.X()) + Abs(Y-p2.Y()) + Abs(Z-p2.Z()) <= aDistance)
            return Standard_True;

          if (Index>1) { 
            if (Prs3d::MatchSegment(X,Y,Z,aDistance,p1,p2,retdist)) 
              return Standard_True;
          }
          p1=p2;
        }
      }
      break;
    }
    default:
    {
      const Standard_Real DU = (U2-U1) / (NbP-1);
      gp_Pnt p1,p2;
      for (Standard_Integer i=1;i<=NbP;i++) {
        p2 = aCurve.Value(U1 + (i-1)*DU);
        if ( Abs(X-p2.X()) + Abs(Y-p2.Y()) + Abs(Z-p2.Z()) <= aDistance)
          return Standard_True;
        if (i>1) { 
          if (Prs3d::MatchSegment(X,Y,Z,aDistance,p1,p2,retdist)) 
            return Standard_True;
        }
        p1=p2;
      }
    }
  }
  return Standard_False;
}


//==================================================================
// function: Add
// purpose:
//==================================================================
void StdPrs_Curve::Add (const Handle (Prs3d_Presentation)& aPresentation,
                        const Adaptor3d_Curve&                    aCurve,
                        const Handle (Prs3d_Drawer)&       aDrawer,
                        const Standard_Boolean drawCurve)
{
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(aDrawer->LineAspect()->Aspect());

  Standard_Real V1, V2;
  FindLimits(aCurve, aDrawer->MaximalParameterValue(), V1, V2);

  const Standard_Integer NbPoints =  aDrawer->Discretisation();
  TColgp_SequenceOfPnt Pnts;
  DrawCurve(aCurve,Prs3d_Root::CurrentGroup(aPresentation),NbPoints,V1,V2,Pnts,drawCurve);

  if (aDrawer->LineArrowDraw()) {
    gp_Pnt Location;
    gp_Vec Direction;
    aCurve.D1(aCurve.LastParameter(),Location,Direction);
    Prs3d_Arrow::Draw (aPresentation,Location,gp_Dir(Direction),
                       aDrawer->ArrowAspect()->Angle(),
                       aDrawer->ArrowAspect()->Length());
  }
}


//==================================================================
// function: Add
// purpose:
//==================================================================
void StdPrs_Curve::Add (const Handle (Prs3d_Presentation)& aPresentation,
                        const Adaptor3d_Curve&                    aCurve,
                        const Quantity_Length              aDeflection,
                        const Handle(Prs3d_Drawer)&        aDrawer,
                        TColgp_SequenceOfPnt&           Points,
                        const Standard_Boolean drawCurve)
{
  Standard_Real V1, V2;
  FindLimits(aCurve, aDrawer->MaximalParameterValue(), V1, V2);

  const Standard_Integer NbPoints =  aDrawer->Discretisation();
  DrawCurve(aCurve,Prs3d_Root::CurrentGroup(aPresentation),NbPoints,V1,V2,Points,drawCurve);
}


//==================================================================
// function: Add
// purpose:
//==================================================================
void StdPrs_Curve::Add (const Handle (Prs3d_Presentation)& aPresentation,
                        const Adaptor3d_Curve&                    aCurve,
                        const Standard_Real                U1,
                        const Standard_Real                U2,
                        const Quantity_Length              aDeflection,
                        TColgp_SequenceOfPnt&              Points,
                        const Standard_Integer             NbPoints,
                        const Standard_Boolean drawCurve)
{
  DrawCurve(aCurve,Prs3d_Root::CurrentGroup(aPresentation),NbPoints,U1,U2,Points,drawCurve);
}


//==================================================================
// function: Add
// purpose:
//==================================================================
void StdPrs_Curve::Add (const Handle (Prs3d_Presentation)& aPresentation,
                        const Adaptor3d_Curve&             aCurve,
                        const Standard_Real                U1,
                        const Standard_Real                U2,
                        const Handle (Prs3d_Drawer)&       aDrawer,
                        const Standard_Boolean drawCurve)
{
  Prs3d_Root::CurrentGroup(aPresentation)->SetPrimitivesAspect(aDrawer->LineAspect()->Aspect());

  Standard_Real V1 = U1;
  Standard_Real V2 = U2;  

  if (Precision::IsNegativeInfinite(V1)) V1 = -aDrawer->MaximalParameterValue();
  if (Precision::IsPositiveInfinite(V2)) V2 = aDrawer->MaximalParameterValue();

  const Standard_Integer NbPoints = aDrawer->Discretisation();
  TColgp_SequenceOfPnt Pnts;
  DrawCurve(aCurve,Prs3d_Root::CurrentGroup(aPresentation),NbPoints,V1,V2,Pnts,drawCurve);
    
  if (aDrawer->LineArrowDraw()) {
    gp_Pnt Location;
    gp_Vec Direction;
    aCurve.D1(aCurve.LastParameter(),Location,Direction);
    Prs3d_Arrow::Draw (aPresentation,Location,gp_Dir(Direction),
                       aDrawer->ArrowAspect()->Angle(),
                       aDrawer->ArrowAspect()->Length());
  }
}


//==================================================================
// function: Match
// purpose:
//==================================================================
Standard_Boolean StdPrs_Curve::Match 
		      (const Quantity_Length        X,
		       const Quantity_Length        Y,
		       const Quantity_Length        Z,
		       const Quantity_Length        aDistance,
		       const Adaptor3d_Curve&       aCurve,
		       const Handle (Prs3d_Drawer)& aDrawer)
{
  Standard_Real V1, V2;
  FindLimits(aCurve, aDrawer->MaximalParameterValue(), V1, V2);

  const Standard_Integer NbPoints = aDrawer->Discretisation();
  return MatchCurve(X,Y,Z,aDistance,aCurve,
                    aDrawer->MaximalChordialDeviation(),NbPoints,V1,V2);

}


//==================================================================
// function: Match
// purpose:
//==================================================================
Standard_Boolean StdPrs_Curve::Match 
		      (const Quantity_Length  X,
		       const Quantity_Length  Y,
		       const Quantity_Length  Z,
		       const Quantity_Length  aDistance,
		       const Adaptor3d_Curve&   aCurve,
		       const Quantity_Length  aDeflection,
		       const Standard_Real    aLimit,
		       const Standard_Integer NbPoints)
{
  Standard_Real V1, V2;
  FindLimits(aCurve, aLimit, V1, V2);

  return MatchCurve(X,Y,Z,aDistance,aCurve,
                    aDeflection,NbPoints,V1,V2);
}


//==================================================================
// function: Match
// purpose:
//==================================================================
Standard_Boolean StdPrs_Curve::Match 
			(const Quantity_Length        X,
			 const Quantity_Length        Y,
			 const Quantity_Length        Z,
			 const Quantity_Length        aDistance,
			 const Adaptor3d_Curve&         aCurve,
			 const Standard_Real          U1,
			 const Standard_Real          U2,
			 const Handle (Prs3d_Drawer)& aDrawer)
{
  Standard_Real V1 = U1;
  Standard_Real V2 = U2;  

  if (Precision::IsNegativeInfinite(V1)) V1 = -aDrawer->MaximalParameterValue();
  if (Precision::IsPositiveInfinite(V2)) V2 = aDrawer->MaximalParameterValue();

  return MatchCurve(X,Y,Z,aDistance,aCurve,
                    aDrawer->MaximalChordialDeviation(),
                    aDrawer->Discretisation(),V1,V2);
}


//==================================================================
// function: Match
// purpose:
//==================================================================
Standard_Boolean StdPrs_Curve::Match 
			(const Quantity_Length  X,
			 const Quantity_Length  Y,
			 const Quantity_Length  Z,
			 const Quantity_Length  aDistance,
			 const Adaptor3d_Curve&   aCurve,
			 const Standard_Real    U1,
			 const Standard_Real    U2,
			 const Quantity_Length  aDeflection,
			 const Standard_Integer aNbPoints) 
{
  return MatchCurve(X,Y,Z,aDistance,aCurve,aDeflection,aNbPoints,U1,U2);
}
