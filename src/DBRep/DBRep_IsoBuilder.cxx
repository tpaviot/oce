// Created on: 1994-03-25
// Created by: Jean Marc LACHAUME
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



#include <DBRep_IsoBuilder.ixx>

#include <Precision.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <Geom2dAdaptor_Curve.hxx>
#include <Geom2dHatch_Intersector.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <HatchGen_Domain.hxx>
#include <Precision.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pnt2d.hxx>

//  Modified by Sergey KHROMOV - Thu Nov  9 12:08:37 2000
static Standard_Real IntersectorConfusion = 1.e-10 ; // -8 ;
static Standard_Real IntersectorTangency  = 1.e-10 ; // -8 ;
//  Modified by Sergey KHROMOV - Thu Nov  9 12:08:38 2000
static Standard_Real HatcherConfusion2d   = 1.e-8 ;
static Standard_Real HatcherConfusion3d   = 1.e-8 ;

//=======================================================================
// Function : DBRep_IsoBuilder
// Purpose  : Constructeur.
//=======================================================================

DBRep_IsoBuilder::DBRep_IsoBuilder (const TopoDS_Face&     TopologicalFace,
				    const Standard_Real    Infinite,
				    const Standard_Integer NbIsos) :
       Geom2dHatch_Hatcher (Geom2dHatch_Intersector (IntersectorConfusion,
						     IntersectorTangency),
			    HatcherConfusion2d,
			    HatcherConfusion3d,
			    Standard_True,
			    Standard_False) ,
       myInfinite (Infinite) ,
       myUMin     (0.0) ,
       myUMax     (0.0) ,
       myVMin     (0.0) ,
       myVMax     (0.0) ,
       myUPrm     (1, NbIsos) ,
       myUInd     (1, NbIsos) ,
       myVPrm     (1, NbIsos) ,
       myVInd     (1, NbIsos) ,
       myNbDom    (0)
{
  myUInd.Init(0);
  myVInd.Init(0);

//-----------------------------------------------------------------------
// If the Min Max bounds are infinite, there are bounded to Infinite
// value.
//-----------------------------------------------------------------------

  BRepTools::UVBounds (TopologicalFace, myUMin, myUMax, myVMin, myVMax) ;
  Standard_Boolean InfiniteUMin = Precision::IsNegativeInfinite (myUMin) ;
  Standard_Boolean InfiniteUMax = Precision::IsPositiveInfinite (myUMax) ;
  Standard_Boolean InfiniteVMin = Precision::IsNegativeInfinite (myVMin) ;
  Standard_Boolean InfiniteVMax = Precision::IsPositiveInfinite (myVMax) ;
  if (InfiniteUMin && InfiniteUMax) {
    myUMin = - Infinite ;
    myUMax =   Infinite ;
  } else if (InfiniteUMin) {
    myUMin = myUMax - Infinite ;
  } else if (InfiniteUMax) {
    myUMax = myUMin + Infinite ;
  }
  if (InfiniteVMin && InfiniteVMax) {
    myVMin = - Infinite ;
    myVMax =   Infinite ;
  } else if (InfiniteVMin) {
    myVMin = myVMax - Infinite ;
  } else if (InfiniteVMax) {
    myVMax = myVMin + Infinite ;
  }

//-----------------------------------------------------------------------
// Retreiving the edges and loading them into the hatcher.
//-----------------------------------------------------------------------

  TopExp_Explorer ExpEdges;
  for (ExpEdges.Init (TopologicalFace, TopAbs_EDGE); ExpEdges.More(); ExpEdges.Next())
  {
    const TopoDS_Edge& TopologicalEdge = TopoDS::Edge (ExpEdges.Current());
    Standard_Real U1, U2;
    const Handle(Geom2d_Curve) PCurve = BRep_Tool::CurveOnSurface (TopologicalEdge, TopologicalFace, U1, U2);

    if (PCurve.IsNull())
    {
    #ifdef DEB
      cout << "DBRep_IsoBuilder : PCurve is null\n";
    #endif
      return;
    }
    else if (U1 == U2)
    {
    #ifdef DEB
      cout << "DBRep_IsoBuilder PCurve : U1==U2\n";
    #endif
      return;
    }

    //-- Test if a TrimmedCurve is necessary
    if (Abs(PCurve->FirstParameter()-U1)<= Precision::PConfusion()
     && Abs(PCurve->LastParameter()-U2)<= Precision::PConfusion())
    {
      AddElement (PCurve, TopologicalEdge.Orientation());
    }
    else
    {
      if (!PCurve->IsPeriodic())
      {
        Handle (Geom2d_TrimmedCurve) TrimPCurve = Handle(Geom2d_TrimmedCurve)::DownCast (PCurve);
        if (!TrimPCurve.IsNull())
        {
          if (TrimPCurve->BasisCurve()->FirstParameter() - U1 > Precision::PConfusion() ||
              TrimPCurve->BasisCurve()->FirstParameter() - U2 > Precision::PConfusion() ||
              U1 - TrimPCurve->BasisCurve()->LastParameter()  > Precision::PConfusion() ||
              U2 - TrimPCurve->BasisCurve()->LastParameter()  > Precision::PConfusion())
          {
            AddElement (PCurve, TopologicalEdge.Orientation());
          #ifdef DEB
            cout << "DBRep_IsoBuilder TrimPCurve : parameters out of range\n";
            cout << "    U1(" << U1 << "), Umin(" << PCurve->FirstParameter()
                 << "), U2("  << U2 << "), Umax(" << PCurve->LastParameter() << ")\n";
          #endif
            return;
          }
        }
        else
        {
          if (PCurve->FirstParameter() - U1 > Precision::PConfusion())
          {
          #ifdef DEB
            cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            cout << "    U1(" << U1 << "), Umin(" << PCurve->FirstParameter() << ")\n";
          #endif
            U1 = PCurve->FirstParameter();
          }
          if (PCurve->FirstParameter() - U2 > Precision::PConfusion())
          {
          #ifdef DEB
            cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            cout << "    U2(" << U2 << "), Umin(" << PCurve->FirstParameter() << ")\n";
          #endif
            U2 = PCurve->FirstParameter();
          }
          if (U1 - PCurve->LastParameter() > Precision::PConfusion())
          {
          #ifdef DEB
            cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            cout << "    U1(" << U1 << "), Umax(" << PCurve->LastParameter() << ")\n";
          #endif
            U1 = PCurve->LastParameter();
          }
          if (U2 - PCurve->LastParameter() > Precision::PConfusion())
          {
          #ifdef DEB
            cout << "DBRep_IsoBuilder PCurve : parameters out of range\n";
            cout << "    U2(" << U2 << "), Umax(" << PCurve->LastParameter() << ")\n";
          #endif
            U2 = PCurve->LastParameter();
          }
        }
      }

      // if U1 and U2 coincide-->do nothing
      if (Abs (U1 - U2) <= Precision::PConfusion()) continue;
      Handle (Geom2d_TrimmedCurve) TrimPCurve = new Geom2d_TrimmedCurve (PCurve, U1, U2);
      AddElement (TrimPCurve, TopologicalEdge.Orientation());
    }
  }

//-----------------------------------------------------------------------
// Loading and trimming the hatchings.
//-----------------------------------------------------------------------

  Standard_Integer IIso ;
  Standard_Real DeltaU = Abs (myUMax - myUMin) ;
  Standard_Real DeltaV = Abs (myVMax - myVMin) ;
  Standard_Real confusion = Min (DeltaU, DeltaV) * HatcherConfusion3d ;
  Confusion3d (confusion) ;

  Standard_Real StepU = DeltaU / (Standard_Real) NbIsos ;
  if (StepU > confusion) {
    Standard_Real UPrm = myUMin + StepU / 2. ;
    gp_Dir2d Dir (0., 1.) ;
    for (IIso = 1 ; IIso <= NbIsos ; IIso++) {
      myUPrm(IIso) = UPrm ;
      gp_Pnt2d Ori (UPrm, 0.) ;
      Geom2dAdaptor_Curve HCur (new Geom2d_Line (Ori, Dir)) ;
      myUInd(IIso) = AddHatching (HCur) ;
      UPrm += StepU ;
    }
  }

  Standard_Real StepV = DeltaV / (Standard_Real) NbIsos ;
  if (StepV > confusion) {
    Standard_Real VPrm = myVMin + StepV / 2. ;
    gp_Dir2d Dir (1., 0.) ;
    for (IIso = 1 ; IIso <= NbIsos ; IIso++) {
      myVPrm(IIso) = VPrm ;
      gp_Pnt2d Ori (0., VPrm) ;
      Geom2dAdaptor_Curve HCur (new Geom2d_Line (Ori, Dir)) ;
      myVInd(IIso) = AddHatching (HCur) ;
      VPrm += StepV ;
    }
  }

//-----------------------------------------------------------------------
// Computation.
//-----------------------------------------------------------------------

  Trim() ;

  myNbDom = 0 ;
  for (IIso = 1 ; IIso <= NbIsos ; IIso++) {
    Standard_Integer Index ;

    Index = myUInd(IIso) ;
    if (Index != 0) {
      if (TrimDone (Index) && !TrimFailed (Index)) {
	ComputeDomains (Index);
	if (IsDone (Index)) myNbDom = myNbDom + Geom2dHatch_Hatcher::NbDomains (Index) ;
      }
    }

    Index = myVInd(IIso) ;
    if (Index != 0) {
      if (TrimDone (Index) && !TrimFailed (Index)) {
	ComputeDomains (Index);
	if (IsDone (Index)) myNbDom = myNbDom + Geom2dHatch_Hatcher::NbDomains (Index) ;
      }
    }
  }
}

//=======================================================================
// Function : LoadIsos
// Purpose  : Loading of the isoparametric curves in the Data Structure
//            of a drawable face.
//=======================================================================

void DBRep_IsoBuilder::LoadIsos (const Handle(DBRep_Face)& Face) const
{
  Standard_Integer NumIso = 0 ;

  for (Standard_Integer UIso = myUPrm.Lower() ; UIso <= myUPrm.Upper() ; UIso++) {
    Standard_Integer UInd = myUInd.Value (UIso) ;
    if (UInd != 0) {
      Standard_Real UPrm = myUPrm.Value (UIso) ;
      if (!IsDone (UInd)) {
	cout << "DBRep_IsoBuilder:: U iso of parameter: " << UPrm ;
	switch (Status (UInd)) {
	  case HatchGen_NoProblem          : cout << " No Problem"          << endl ; break ;
	  case HatchGen_TrimFailure        : cout << " Trim Failure"        << endl ; break ;
	  case HatchGen_TransitionFailure  : cout << " Transition Failure"  << endl ; break ;
	  case HatchGen_IncoherentParity   : cout << " Incoherent Parity"   << endl ; break ;
	  case HatchGen_IncompatibleStates : cout << " Incompatible States" << endl ; break ;
	}
      } else {
	Standard_Integer NbDom = Geom2dHatch_Hatcher::NbDomains (UInd) ;
	for (Standard_Integer IDom = 1 ; IDom <= NbDom ; IDom++) {
	  const HatchGen_Domain& Dom = Domain (UInd, IDom) ;
	  Standard_Real V1 = Dom.HasFirstPoint()  ? Dom.FirstPoint().Parameter()  : myVMin - myInfinite ;
	  Standard_Real V2 = Dom.HasSecondPoint() ? Dom.SecondPoint().Parameter() : myVMax + myInfinite ;
	  NumIso++ ;
	  Face->Iso (NumIso, GeomAbs_IsoU, UPrm, V1, V2) ;
	}
      }
    }
  }

  for (Standard_Integer VIso = myVPrm.Lower() ; VIso <= myVPrm.Upper() ; VIso++) {
    Standard_Integer VInd = myVInd.Value (VIso) ;
    if (VInd != 0) {
      Standard_Real VPrm = myVPrm.Value (VIso) ;
      if (!IsDone (VInd)) {
	cout << "DBRep_IsoBuilder:: V iso of parameter: " << VPrm ;
	switch (Status (VInd)) {
	  case HatchGen_NoProblem          : cout << " No Problem"          << endl ; break ;
	  case HatchGen_TrimFailure        : cout << " Trim Failure"        << endl ; break ;
	  case HatchGen_TransitionFailure  : cout << " Transition Failure"  << endl ; break ;
	  case HatchGen_IncoherentParity   : cout << " Incoherent Parity"   << endl ; break ;
	  case HatchGen_IncompatibleStates : cout << " Incompatible States" << endl ; break ;
	}
      } else {
	Standard_Integer NbDom = Geom2dHatch_Hatcher::NbDomains (VInd) ;
	for (Standard_Integer IDom = 1 ; IDom <= NbDom ; IDom++) {
	  const HatchGen_Domain& Dom = Domain (VInd, IDom) ;
	  Standard_Real U1 = Dom.HasFirstPoint()  ? Dom.FirstPoint().Parameter()  : myVMin - myInfinite ;
	  Standard_Real U2 = Dom.HasSecondPoint() ? Dom.SecondPoint().Parameter() : myVMax + myInfinite ;
	  NumIso++ ;
	  Face->Iso (NumIso, GeomAbs_IsoV, VPrm, U1, U2) ;
	}
      }
    }
  }
}
