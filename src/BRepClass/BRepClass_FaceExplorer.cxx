// Created on: 1992-11-19
// Created by: Remi LEQUETTE
// Copyright (c) 1992-1999 Matra Datavision
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



//  Modified by skv - Thu Jul 13 17:42:58 2006 OCC12627
//  Total rewriting of the method Segment; add the method OtherSegment.

#include <BRepClass_FaceExplorer.ixx>
#include <Precision.hxx>
#include <Geom2d_Curve.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>

//=======================================================================
//function : BRepClass_FaceExplorer
//purpose  : 
//=======================================================================

BRepClass_FaceExplorer::BRepClass_FaceExplorer(const TopoDS_Face& F) :
       myFace(F),
       myCurEdgeInd(1),
       myCurEdgePar(0.123)
{
  myFace.Orientation(TopAbs_FORWARD);
}

//=======================================================================
//function : Reject
//purpose  : 
//=======================================================================

Standard_Boolean  BRepClass_FaceExplorer::Reject(const gp_Pnt2d&)const 
{
  return Standard_False;
}

//=======================================================================
//function : Segment
//purpose  : 
//=======================================================================

Standard_Boolean BRepClass_FaceExplorer::Segment(const gp_Pnt2d& P, 
						 gp_Lin2d& L,
						 Standard_Real& Par)
{
  myCurEdgeInd = 1;
  myCurEdgePar = 0.123;

  return OtherSegment(P, L, Par);
}

//=======================================================================
//function : OtherSegment
//purpose  : 
//=======================================================================

Standard_Boolean BRepClass_FaceExplorer::OtherSegment(const gp_Pnt2d& P, 
						      gp_Lin2d& L,
						      Standard_Real& Par)
{
  TopExp_Explorer      anExpF(myFace,TopAbs_EDGE);
  Standard_Integer     i;
  Standard_Real        aFPar;
  Standard_Real        aLPar;
  Handle(Geom2d_Curve) aC2d;
  Standard_Real        aTolParConf = Precision::PConfusion();
  gp_Pnt2d             aPOnC;
  Standard_Real        aParamIn;

  for (i = 1; anExpF.More(); anExpF.Next(), i++) {
    if (i != myCurEdgeInd)
      continue;

    const TopoDS_Shape       &aLocalShape   = anExpF.Current();
    const TopAbs_Orientation  anOrientation = aLocalShape.Orientation();

    if (anOrientation == TopAbs_FORWARD || anOrientation == TopAbs_REVERSED) {
      const TopoDS_Edge &anEdge = TopoDS::Edge(aLocalShape);

      aC2d = BRep_Tool::CurveOnSurface(anEdge, myFace, aFPar, aLPar);

      if (!aC2d.IsNull()) {
	// Treatment of infinite cases.
	if (Precision::IsNegativeInfinite(aFPar)) {
	  if (Precision::IsPositiveInfinite(aLPar)) {
	    aFPar = -1.;
	    aLPar =  1.;
	  } else {
	    aFPar = aLPar - 1.;
	  }
	} else if (Precision::IsPositiveInfinite(aLPar))
	  aLPar = aFPar + 1.;

	for (; myCurEdgePar < 0.7 ;myCurEdgePar += 0.2111) {
	  aParamIn = myCurEdgePar*aFPar + (1. - myCurEdgePar)*aLPar;

	  aC2d->D0(aParamIn, aPOnC);
	  Par = aPOnC.Distance(P);

	  if (Par > aTolParConf) {
	    gp_Vec2d aLinVec(P, aPOnC);
	    gp_Dir2d aLinDir(aLinVec);

	    L = gp_Lin2d(P, aLinDir);

	    // Check if ends of a curve lie on a line.
	    aC2d->D0(aFPar, aPOnC);

	    if (L.Distance(aPOnC) > aTolParConf) {
	      aC2d->D0(aLPar, aPOnC);

	      if (L.Distance(aPOnC) > aTolParConf) {
		myCurEdgePar += 0.2111;

		if (myCurEdgePar >= 0.7) {
		  myCurEdgeInd++;
		  myCurEdgePar = 0.123;
		}

		return Standard_True;
	      }
	    }
	  }
	}
      } // if (!aC2d.IsNull()) {
    } // if (anOrientation == TopAbs_FORWARD ...

    // This curve is not valid for line construction. Go to another edge.
    myCurEdgeInd++;
    myCurEdgePar = 0.123;
  }

  // nothing found, return an horizontal line
  Par = RealLast();
  L   = gp_Lin2d(P,gp_Dir2d(1,0));

  return Standard_False;
}

//=======================================================================
//function : InitWires
//purpose  : 
//=======================================================================

void  BRepClass_FaceExplorer::InitWires()
{
  myWExplorer.Init(myFace,TopAbs_WIRE);
}

//=======================================================================
//function : RejectWire NYI
//purpose  : 
//=======================================================================

Standard_Boolean  BRepClass_FaceExplorer::RejectWire
  (const gp_Lin2d& , 
   const Standard_Real)const 
{
  return Standard_False;
}

//=======================================================================
//function : InitEdges
//purpose  : 
//=======================================================================

void  BRepClass_FaceExplorer::InitEdges()
{
  myEExplorer.Init(myWExplorer.Current(),TopAbs_EDGE);
}

//=======================================================================
//function : RejectEdge NYI
//purpose  : 
//=======================================================================

Standard_Boolean  BRepClass_FaceExplorer::RejectEdge
  (const gp_Lin2d& , 
   const Standard_Real )const 
{
  return Standard_False;
}


//=======================================================================
//function : CurrentEdge
//purpose  : 
//=======================================================================

void  BRepClass_FaceExplorer::CurrentEdge(BRepClass_Edge& E, 
					  TopAbs_Orientation& Or) const 
{
  E.Edge() = TopoDS::Edge(myEExplorer.Current());
  E.Face() = myFace;
  Or = E.Edge().Orientation();
}

