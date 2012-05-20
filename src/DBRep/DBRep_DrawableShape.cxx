// Created on: 1991-07-04
// Created by: Christophe MARION
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


#include <DBRep_DrawableShape.ixx>


#include <Draw_Appli.hxx>

#include <DBRep_Face.hxx>
#include <DBRep_Edge.hxx>
#include <DBRep_IsoBuilder.hxx>
#include <DBRep_ListIteratorOfListOfFace.hxx>
#include <DBRep_ListIteratorOfListOfEdge.hxx>
#include <DBRep_ListIteratorOfListOfHideData.hxx>
#include <DBRep_HideData.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>

#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_ListOfShape.hxx>

#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>

#include <BRep_Tool.hxx>

#include <BRepTools.hxx>

#include <BRepMesh_IncrementalMesh.hxx>

#include <BRepAdaptor_Surface.hxx>
#include <BRepAdaptor_Curve.hxx>

#include <HLRBRep.hxx>

#include <gp_Lin2d.hxx>
#include <gp_Trsf.hxx>

#include <Poly_Polygon3D.hxx>
#include <Poly_Triangulation.hxx>
#include <Poly_PolygonOnTriangulation.hxx>
#include <Poly_Connect.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColStd_HArray1OfInteger.hxx>

#include <Precision.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Adaptor3d_HCurve.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <TColStd_DataMapOfIntegerInteger.hxx>
#include <TColStd_DataMapIteratorOfDataMapOfIntegerInteger.hxx>

static Standard_Real IsoRatio = 1.001;

static Standard_Integer MaxPlotCount = 5; // To avoid huge recursive calls in
static Standard_Integer PlotCount = 0;    // PlotEdge and PlotIso for cases of "bad" 
                                          // curves and surfaces
                                          // Set PlotCount = 0 before first call of
                                          // PlotEdge or PlotIso
static TopoDS_Shape  pickshape;
static Standard_Real upick,vpick;
#ifdef WNT
extern Draw_Viewer dout;
#endif

//=======================================================================
//function : DBRep_DrawableShape
//purpose  : constructor
//=======================================================================

DBRep_DrawableShape::DBRep_DrawableShape 
  (const TopoDS_Shape& aShape,
   const Draw_Color& FreeCol,
   const Draw_Color& ConnCol,
   const Draw_Color& EdgeCol,
   const Draw_Color& IsosCol,
   const Standard_Real size,
   const Standard_Integer nbisos,
   const Standard_Integer discret) :
  mySize(size),
  myDiscret(discret),
  myFreeCol(FreeCol),
  myConnCol(ConnCol),
  myEdgeCol(EdgeCol),
  myIsosCol(IsosCol),
  myNbIsos(nbisos),
  myDispOr(Standard_False),
  mytriangulations(Standard_False),
  mypolygons(Standard_False),
  myHLR(Standard_False),
  myRg1(Standard_False),
  myRgN(Standard_False),
  myHid(Standard_False)
{
  Set(aShape);
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================

void  DBRep_DrawableShape::Set(const TopoDS_Shape& aShape)
{
  myShape = aShape;
  
  myFaces.Clear();
  myEdges.Clear();
  
  if (myShape.IsNull())
    return;

  //==============================================================
  // Process the faces
  //==============================================================
  
  TopExp_Explorer ExpFace;
  TopLoc_Location l;

  for (ExpFace.Init (myShape,TopAbs_FACE);
       ExpFace.More();
       ExpFace.Next()) {
    TopoDS_Face TopologicalFace = TopoDS::Face (ExpFace.Current());
    if(myNbIsos != 0) {
        const Handle(Geom_Surface)& S =
	  BRep_Tool::Surface(TopologicalFace,l);
      if (!S.IsNull()) {
	TopologicalFace.Orientation (TopAbs_FORWARD) ;
	DBRep_IsoBuilder IsoBuild (TopologicalFace, mySize, myNbIsos) ;
	myFaces.Append(new DBRep_Face (TopologicalFace,
				       IsoBuild.NbDomains(),
				       myIsosCol)) ;
	IsoBuild.LoadIsos (myFaces.Last()) ;
      }
      else myFaces.Append(new DBRep_Face(TopologicalFace,0, myEdgeCol));
    }
    else myFaces.Append(new DBRep_Face(TopologicalFace,0, myEdgeCol));
  }
  
  //==============================================================
  // process a 3D edge
  //==============================================================
  
  TopTools_IndexedDataMapOfShapeListOfShape edgemap;
  TopExp::MapShapesAndAncestors(aShape,TopAbs_EDGE,TopAbs_FACE,edgemap);
  Standard_Integer iedge;
  
  for (iedge = 1; iedge <= edgemap.Extent(); iedge++) {
    
    const TopoDS_Edge& theEdge = TopoDS::Edge(edgemap.FindKey(iedge));
    
    // skip degenerated edges
    if (BRep_Tool::Degenerated(theEdge)) continue;

    // compute the number of faces
    Standard_Integer nbf = edgemap(iedge).Extent();
    
    Draw_Color EdgeColor;
    
    switch (nbf) {
      
    case 0 :
      EdgeColor = myEdgeCol;    // isolated edge
      break;
      
    case 1 :
      EdgeColor = myFreeCol;    // edge in only one face
      break;
      
      default :
	EdgeColor = myConnCol;    // edge shared by at least two faces
    }
    
    myEdges.Append(new DBRep_Edge (theEdge,EdgeColor));
  }
}


//=======================================================================
//function : ChangeNbIsos
//purpose  : Changes the number of isoparametric curves in a shape.
//=======================================================================

void  DBRep_DrawableShape::ChangeNbIsos (const Standard_Integer NbIsos)
{
  myFaces.Clear();
  myNbIsos = NbIsos ;
  TopExp_Explorer ExpFace;
  TopLoc_Location l;

  for (ExpFace.Init (myShape, TopAbs_FACE);
       ExpFace.More();
       ExpFace.Next()) {
    TopoDS_Face TopologicalFace = TopoDS::Face (ExpFace.Current());
    const Handle(Geom_Surface)& S =
      BRep_Tool::Surface(TopologicalFace,l);
    if (myNbIsos != 0) {
      if (!S.IsNull()) {
	TopologicalFace.Orientation (TopAbs_FORWARD) ;
	DBRep_IsoBuilder IsoBuild (TopologicalFace, mySize, myNbIsos) ;
	myFaces.Append
	  (new DBRep_Face 
	   (TopologicalFace, IsoBuild.NbDomains(), myIsosCol)) ;
	IsoBuild.LoadIsos (myFaces.Last()) ;
      }
      else myFaces.Append(new DBRep_Face(TopologicalFace,0, myEdgeCol));
    }
    else  myFaces.Append(new DBRep_Face(TopologicalFace,0, myEdgeCol));
  }
}

//=======================================================================
// Function : NbIsos
// Purpose  : Returns the number of isoparametric curves in a shape.
//=======================================================================

Standard_Integer DBRep_DrawableShape::NbIsos () const
{
  return myNbIsos ;
}

//=======================================================================
// Function : Discret
// Purpose  : 
//=======================================================================

Standard_Integer DBRep_DrawableShape::Discret () const
{
  return myDiscret ;
}

Standard_EXPORT Draw_Color DBRep_ColorOrientation (const TopAbs_Orientation Or);


static void PlotIso (Draw_Display& dis,
			 Handle(DBRep_Face)& F, 
			 BRepAdaptor_Surface& S, 
			 GeomAbs_IsoType T,
			 Standard_Real& U, 
			 Standard_Real& V, 
			 Standard_Real Step, 
			 Standard_Boolean& halt)
{

  ++PlotCount; 

  gp_Pnt Pl, Pr, Pm;

   if (T == GeomAbs_IsoU) {
    S.D0(U, V, Pl);
    S.D0(U, V + Step/2., Pm);
    S.D0(U, V + Step, Pr);
  } else {
    S.D0(U, V, Pl);
    S.D0(U + Step/2., V, Pm);
    S.D0(U + Step, V, Pr);
  }

  if (PlotCount > MaxPlotCount) {
    dis.DrawTo(Pr);
    if (dis.HasPicked()) {
      pickshape = F->Face();
      upick = (T == GeomAbs_IsoU) ? U : U + Step;
      vpick = (T == GeomAbs_IsoU) ? V + Step : V;
      halt = Standard_True;
    };
    return;
  }

  if (Pm.Distance(Pl) + Pm.Distance(Pr) <= IsoRatio*Pl.Distance(Pr)) {
    dis.DrawTo(Pr);
    if (dis.HasPicked()) {
      pickshape = F->Face();
      upick = (T == GeomAbs_IsoU) ? U : U + Step;
      vpick = (T == GeomAbs_IsoU) ? V + Step : V;
      halt = Standard_True;
    };
  } else 
     if (T == GeomAbs_IsoU) {
       PlotIso (dis, F, S, T, U, V, Step/2, halt);
       Standard_Real aLocalV = V + Step/2 ;
       PlotIso (dis, F, S, T, U, aLocalV , Step/2, halt);
     } else {
       PlotIso (dis, F, S, T, U, V, Step/2, halt);
       Standard_Real aLocalU = U + Step/2 ;
       PlotIso (dis, F, S, T, aLocalU , V, Step/2, halt);
     }
}


static void PlotEdge (Draw_Display& dis,
		      Handle(DBRep_Edge)& E, 
		      const Adaptor3d_Curve& C, 
		      Standard_Real& f, 
		      Standard_Real step, 
		      Standard_Boolean& halt)
{

  ++PlotCount;

  gp_Pnt Pl, Pr, Pm;

  C.D0(f, Pl);
  C.D0(f + step/2., Pm);
  C.D0(f + step, Pr);

  if (PlotCount > MaxPlotCount) {
    dis.DrawTo(Pr);
    if (dis.HasPicked()) {
      pickshape = E->Edge();
      upick = f + step;
      vpick = 0;
      halt = Standard_True;
    }
    return;
  } 
  
  
  if (Pm.Distance(Pl) + Pm.Distance(Pr) <= IsoRatio*Pl.Distance(Pr)) {
    dis.DrawTo(Pr);
    if (dis.HasPicked()) {
      pickshape = E->Edge();
      upick = f + step;
      vpick = 0;
      halt = Standard_True;
    };
  } else {
    PlotEdge (dis, E, C, f, step/2, halt);
    Standard_Real aLocalF = f + step/2 ;
    PlotEdge (dis, E, C, aLocalF , step/2, halt);
  }
}

//=======================================================================
//function : DrawOn
//purpose  : 
//=======================================================================

void  DBRep_DrawableShape::DrawOn(Draw_Display& dis) const 
{
  Standard_Boolean halt = Standard_False;

  if (myShape.IsNull()) {
    dis.SetColor(myConnCol);
    dis.DrawString(gp_Pnt(0,0,0),"Null Shape");
    return;
  }

  // hidden lines
  if (myHLR) {
    DBRep_DrawableShape* p = (DBRep_DrawableShape*) this;
    p->DisplayHiddenLines(dis);
    return;
  }

  GeomAbs_IsoType T;
  Standard_Real Par,T1,T2;
  Standard_Real U1,U2,V1,V2,stepU=0.,stepV=0.;
//  gp_Pnt P, P1;
  gp_Pnt P;
  Standard_Integer i,j;

  // Faces
  Handle(Poly_Triangulation) Tr;
  TopLoc_Location l;
  TopLoc_Location loc;

  DBRep_ListIteratorOfListOfFace itf(myFaces);

  while (itf.More() && !halt) {

    const Handle(DBRep_Face)& F = itf.Value();
    dis.SetColor(F->Color());

    const Handle(Geom_Surface)& S = BRep_Tool::Surface(F->Face(),l);

    if (!S.IsNull()) {

      Standard_Boolean restriction = Standard_False;
      if(S->IsUPeriodic() || S->IsVPeriodic()) {
        Standard_Real SU1 = 0., SU2 = 0., SV1 = 0., SV2 = 0.;
        Standard_Real FU1 = 0., FU2 = 0., FV1 = 0., FV2 = 0.;
        S->Bounds(SU1,SU2,SV1,SV2);
        BRepTools::UVBounds (F->Face(),FU1,FU2,FV1,FV2);
        if(S->IsUPeriodic()) {
          if(FU1 < SU1 || FU1 > SU2)
            restriction = Standard_True;
          if(!restriction && (FU2 < SU1 || FU2 > SU2))
            restriction = Standard_True;
        }
        if(!restriction && S->IsVPeriodic()) {
          if(FV1 < SV1 || FV1 > SV2)
            restriction = Standard_True;
          if(!restriction && (FV2 < SV1 || FV2 > SV2))
            restriction = Standard_True;
        }
        Standard_Boolean  zeroS = (fabs(SU2-SU1) <= 1.e-9 || fabs(SV2-SV1) <= 1.e-9);
        Standard_Boolean  zeroF = (fabs(FU2-FU1) <= 1.e-9 || fabs(FV2-FV1) <= 1.e-9);
        if(restriction && (zeroS || zeroF))
          restriction = Standard_False;
        if(restriction && (FU1 >= FU2 || FV1 >= FV2))
          restriction = Standard_False;
        if(restriction && (fabs(FU2-FU1) > 4.1e+100 || fabs(FV2-FV1) > 4.1e+100))
          restriction = Standard_False;
      }

      BRepAdaptor_Surface S(F->Face(),restriction);

      //BRepAdaptor_Surface S(F->Face(),Standard_False);
      
      GeomAbs_SurfaceType SurfType = S.GetType();

// If the type of the surface is GeomAbs_SurfaceOfExtrusion or GeomAbs_SurfaceOfRevolution
#ifdef DEB
      GeomAbs_CurveType CurvType;
#else
      GeomAbs_CurveType CurvType = GeomAbs_OtherCurve;
#endif

      Standard_Integer N = F->NbIsos();

      Standard_Integer Intrv, nbIntv;
      Standard_Integer nbUIntv = S.NbUIntervals(GeomAbs_CN);
      Standard_Integer nbVIntv = S.NbVIntervals(GeomAbs_CN);
      TColStd_Array1OfReal TI(1,Max(nbUIntv, nbVIntv)+1);

      for (i = 1; i <= N; i++) {

	F->GetIso(i,T,Par,T1,T2);
	if (T == GeomAbs_IsoU) {
	  S.VIntervals(TI, GeomAbs_CN);
	  V1 = Max(T1, TI(1));
	  V2 = Min(T2, TI(2));
	  U1 = Par;
	  U2 = Par;
	  stepU = 0;
	  nbIntv = nbVIntv;
	}
	else {
	  S.UIntervals(TI, GeomAbs_CN);
	  U1 = Max(T1, TI(1));
	  U2 = Min(T2, TI(2));
	  V1 = Par;
	  V2 = Par;
	  stepV = 0;
	  nbIntv = nbUIntv;
	}	
	
	S.D0(U1,V1,P);
	dis.MoveTo(P);

 	for (Intrv = 1; Intrv <= nbIntv; Intrv++) {

	  if (TI(Intrv) <= T1 && TI(Intrv + 1) <= T1)
	    continue;
	  if (TI(Intrv) >= T2 && TI(Intrv + 1) >= T2)
 	    continue;
	  if (T == GeomAbs_IsoU) {
	    V1 = Max(T1, TI(Intrv));
	    V2 = Min(T2, TI(Intrv + 1));
	    stepV = (V2 - V1) / myDiscret;
	  }
	  else {
	    U1 = Max(T1, TI(Intrv));
	    U2 = Min(T2, TI(Intrv + 1));
	    stepU = (U2 - U1) / myDiscret;
	  }

	  switch (SurfType) {
//-------------GeomAbs_Plane---------------
	  case GeomAbs_Plane :
	    break;
//----GeomAbs_Cylinder   GeomAbs_Cone------
	  case GeomAbs_Cylinder :
	  case GeomAbs_Cone :
	    if (T == GeomAbs_IsoV) {
	      for (j = 1; j < myDiscret; j++) {
		U1 += stepU;
		V1 += stepV;
		S.D0(U1,V1,P);
		dis.DrawTo(P);
		if (dis.HasPicked()) {
		  pickshape = F->Face();
		  upick = U1;
		  vpick = V1;
		  halt = Standard_True;
		}
	      }
	    }
	    break;
//---GeomAbs_Sphere   GeomAbs_Torus--------
//GeomAbs_BezierSurface GeomAbs_BezierSurface
	  case GeomAbs_Sphere :
	  case GeomAbs_Torus :
	  case GeomAbs_OffsetSurface :
	  case GeomAbs_OtherSurface :
	    for (j = 1; j < myDiscret; j++) {
	      U1 += stepU;
	      V1 += stepV;
	      S.D0(U1,V1,P);
	      dis.DrawTo(P);
	      if (dis.HasPicked()) {
		pickshape = F->Face();
		upick = U1;
		vpick = V1;
		halt = Standard_True;
	      }
	    }
	    break;
//-------------GeomAbs_BSplineSurface------
	  case GeomAbs_BezierSurface :
	  case GeomAbs_BSplineSurface :
	    for (j = 1; j <= myDiscret/2; j++) {
	      Handle(DBRep_Face) aLocalFace = F;

	      PlotCount = 0;

	      PlotIso (dis, aLocalFace , S, T, U1, V1, (T == GeomAbs_IsoV) ? stepU*2. : stepV*2., halt);
	      U1 += stepU*2.;
	      V1 += stepV*2.;
	    }
	    break;
//-------------GeomAbs_SurfaceOfExtrusion--
//-------------GeomAbs_SurfaceOfRevolution-
	  case GeomAbs_SurfaceOfExtrusion :
	  case GeomAbs_SurfaceOfRevolution :
	    if ((T == GeomAbs_IsoV && SurfType == GeomAbs_SurfaceOfRevolution) ||
		(T == GeomAbs_IsoU && SurfType == GeomAbs_SurfaceOfExtrusion)) {
	      if (SurfType == GeomAbs_SurfaceOfExtrusion) break;
	      for (j = 1; j < myDiscret; j++) {
		U1 += stepU;
		V1 += stepV;
		S.D0(U1,V1,P);
		dis.DrawTo(P);
		if (dis.HasPicked()) {
		  pickshape = F->Face();
		  upick = U1;
		  vpick = V1;
		  halt = Standard_True;
		}
	      }
	    } else {
	      CurvType = (S.BasisCurve())->GetType();
	      switch (CurvType) {
	      case GeomAbs_Line :
		break;
	      case GeomAbs_Circle :
	      case GeomAbs_Ellipse :
		for (j = 1; j < myDiscret; j++) {
		  U1 += stepU;
		  V1 += stepV;
		  S.D0(U1,V1,P);
		  dis.DrawTo(P);
		  if (dis.HasPicked()) {
		    pickshape = F->Face();
		    upick = U1;
		    vpick = V1;
		    halt = Standard_True;
		  }
		}
		break;
	      case GeomAbs_Parabola :
	      case GeomAbs_Hyperbola :
	      case GeomAbs_BezierCurve :
	      case GeomAbs_BSplineCurve :
	      case GeomAbs_OtherCurve :
		for (j = 1; j <= myDiscret/2; j++) {
		  Handle(DBRep_Face) aLocalFace = F;	

		  PlotCount = 0;

		  PlotIso (dis, aLocalFace, S, T, U1, V1,
			   (T == GeomAbs_IsoV) ? stepU*2. : stepV*2., halt);
		  U1 += stepU*2.;
		  V1 += stepV*2.;
		}
		break;
	      }
	    }
	  }
	}
	S.D0(U2,V2,P);
	dis.DrawTo(P);
	if (dis.HasPicked()) {
	  pickshape = F->Face();
	  upick = U2;
	  vpick = V2;
	  halt = Standard_True;
	}
      }
    }
    
    //=====================================
    // trace des eventuelles triangulations.
    //=====================================

    if (S.IsNull() || mytriangulations) {
      Tr = BRep_Tool::Triangulation(F->Face(), loc);
      if (!Tr.IsNull()) {
	Display(Tr, loc.Transformation(), dis);
      }
    }
    itf.Next();
  }


  // Edges
  DBRep_ListIteratorOfListOfEdge ite(myEdges);
  while (ite.More() && !halt) {

    const Handle(DBRep_Edge)& E = ite.Value();
    
    if(myDispOr)
      dis.SetColor(DBRep_ColorOrientation(E->Edge().Orientation()));
    else
      dis.SetColor(E->Color());

    // display geometrical curve if exists.
    Standard_Boolean isgeom = BRep_Tool::IsGeometric(E->Edge());
    Standard_Real U1,U2;

    if (isgeom) {
      // check the range (to report bad edges)
      BRep_Tool::Range(E->Edge(),U1,U2);
      if (U2 < U1) {
	// bad orientation
	cout << "DBRep_DrawableShape : Bad parameters on edge."<<endl;
	BRepTools::Dump(E->Edge(),cout);
	ite.Next();
	continue;
      }

      if (BRep_Tool::Degenerated(E->Edge())) {
	ite.Next();
 	continue;
      }
	
      BRepAdaptor_Curve C(E->Edge());
      
      Standard_Real f = C.FirstParameter();
      Standard_Real l = C.LastParameter();
      if (Precision::IsNegativeInfinite(f)) {
	if (Precision::IsPositiveInfinite(l)) {
	  f = -mySize;
	  l = mySize;
	}
	else {
	  f = l - mySize;
	}
      }
      else if (Precision::IsPositiveInfinite(l)) {
	l = f + mySize;
      }
      
      Handle(Adaptor3d_HCurve) HC = C.Trim(f, l, Precision::Confusion());
      GeomAbs_CurveType CurvType = HC->GetType();

      Standard_Integer intrv, nbintv = HC->NbIntervals(GeomAbs_CN);
      TColStd_Array1OfReal TI(1,nbintv+1);
      HC->Intervals(TI,GeomAbs_CN);

      HC->D0(HC->FirstParameter(), P);
      dis.MoveTo(P);

      for (intrv = 1; intrv <= nbintv; intrv++) {
	Standard_Real t = TI(intrv);
	Standard_Real step = (TI(intrv+1) - t) / myDiscret;

	switch (CurvType) {
	case GeomAbs_Line :
	  break;
	case GeomAbs_Circle :
	case GeomAbs_Ellipse :
	  for (j = 1; j < myDiscret; j++) {
	    t += step;
	    C.D0(t,P);
	    dis.DrawTo(P);
	    if (dis.HasPicked()) {
	      pickshape = E->Edge();
	      upick = t;
	      vpick = 0;
	      halt = Standard_True;
	    }
	  }
	  break;
	case GeomAbs_Parabola :
	case GeomAbs_Hyperbola :
	case GeomAbs_BezierCurve :
	case GeomAbs_BSplineCurve :
	case GeomAbs_OtherCurve :
	  for (j = 1; j <= myDiscret/2; j++) {
	    Handle(DBRep_Edge) aLocaLEdge(E);
	    PlotCount = 0;
	    PlotEdge (dis, aLocaLEdge , HC->Curve(), t, step*2., halt);
	    t += step*2.;
	  }
	  break;
	}
      }

	C.D0(HC->LastParameter(),P);
	dis.DrawTo(P);
	if (dis.HasPicked()) {
	  pickshape = E->Edge();
	  upick = l;
	  vpick = 0;
	  halt = Standard_True;
	}
      
      if (myDispOr) {
	// display an arrow at the end
	gp_Pnt P;
	gp_Vec V;
	C.D1(l,P,V);
	gp_Pnt2d p1,p2;
	dis.Project(P,p1);
	P.Translate(V);
	dis.Project(P,p2);
	gp_Vec2d v(p1,p2);
	if (v.Magnitude() > gp::Resolution()) {
	  Standard_Real L = 20 / dis.Zoom();
	  Standard_Real H = 10 / dis.Zoom();
	  gp_Dir2d d(v);
	  p2.SetCoord(p1.X() - L*d.X() - H*d.Y(), p1.Y() - L*d.Y() + H*d.X());
	  dis.MoveTo(p2);
	  p2.SetCoord(p1.X() - L*d.X() + H*d.Y(), p1.Y() - L*d.Y() - H*d.X());
	  dis.DrawTo(p1);
	  dis.DrawTo(p2);
	}

//	gp_Vec tang;
//	C.D1(l,P,tang);
	
      }
    }
    
    //======================================
    // trace des representations polygonales:
    //======================================

    if (!isgeom || mypolygons) {
      
      // Polygones 3d:
      Handle(Poly_Polygon3D) Polyg = BRep_Tool::Polygon3D(E->Edge(), loc);
      if (!Polyg.IsNull()) {
	const TColgp_Array1OfPnt& Points = Polyg->Nodes();
	Standard_Integer po;
	for (po = Points.Lower()+1; po <= Points.Upper(); po++) {
	  dis.Draw((Points.Value(po-1)).Transformed(loc), 
		   (Points.Value(po)).Transformed(loc));
	  if (dis.HasPicked()) {
	    pickshape = E->Edge();
	    upick = 0;
	    vpick = 0;
	    halt = Standard_True;
	  }
	}
      }
      else {

	// Polygone sur triangulation:
	Handle(Poly_Triangulation) Tr;
	Handle(Poly_PolygonOnTriangulation) Poly;
	BRep_Tool::PolygonOnTriangulation(E->Edge(), Poly, Tr, loc);
	if (!Poly.IsNull()) {
	  const TColStd_Array1OfInteger& Indices = Poly->Nodes();
	  const TColgp_Array1OfPnt& Nodes = Tr->Nodes();
	  for (i=Indices.Lower()+1; i<=Indices.Upper(); i++) {
	    dis.Draw(Nodes(Indices(i-1)).Transformed(loc),
		     Nodes(Indices(i)).Transformed(loc));
	    if (dis.HasPicked()) {
	      pickshape = E->Edge();
	      upick = 0;
	      vpick = 0;
	      halt = Standard_True;
	    }
	  }
	}
      }
    }

    ite.Next();
  }
    
  


  //Vertices
  
  TopExp_Explorer exv;
  dis.SetColor(myConnCol);
  
  for (exv.Init(myShape,TopAbs_VERTEX,TopAbs_EDGE);
       exv.More() && !halt;
       exv.Next()){
    
    if (myDispOr) 
      dis.SetColor(DBRep_ColorOrientation(exv.Current().Orientation()));
    dis.DrawMarker(BRep_Tool::Pnt(TopoDS::Vertex(exv.Current())),
		   Draw_Losange);
    if (dis.HasPicked()) {
      pickshape = exv.Current();
      upick = 0;
      vpick = 0;
      halt = Standard_True;
    }
    
  }
  
}

//=======================================================================
//function : DisplayHiddenLines
//purpose  : 
//=======================================================================

void DBRep_DrawableShape::DisplayHiddenLines(Draw_Display& dis)
{
  Standard_Integer id = dis.ViewId();  

  // get the projection
  gp_Trsf T;
  dout.GetTrsf(id,T);
  Standard_Real focal = -1;
  if (!strcmp(dout.GetType(id),"PERS")) focal = dout.Focal(id);
  Standard_Real Ang,Def;
  HLRBRep::PolyHLRAngleAndDeflection(myAng,Ang,Def);
  BRepMesh_IncrementalMesh MESH(myShape,Def,Standard_True,Ang);
  Standard_Boolean recompute = Standard_True;
  // find if the view must be recomputed
  DBRep_ListIteratorOfListOfHideData it(myHidData);
  
  while (it.More()) {
    if (it.Value().ViewId() == id) {
      // we have the view
      // but did we rotate it
      Standard_Real ang = it.Value().Angle();
      recompute = !it.Value().IsSame(T,focal) || myAng != ang;
      if (recompute) 
	myHidData.Remove(it);
      else {
	it.Value().DrawOn(dis,myRg1,myRgN,myHid,
			  myConnCol,myIsosCol);
	if (dis.HasPicked()) {
	  pickshape = it.Value().LastPick();
	  upick = 0;
	  vpick = 0;
	}
      }
      break;
    }
    it.Next();
  }
  // recompute the hidden lines and display them
  if (recompute) {
    DBRep_HideData theData;
    myHidData.Append(theData);
    myHidData.Last().Set(id,T,focal,myShape,myAng);
    myHidData.Last().DrawOn(dis,myRg1,myRgN,myHid,
			    myConnCol,myIsosCol);
    if (dis.HasPicked()) {
      pickshape = myHidData.Last().LastPick();
      upick = 0;
      vpick = 0;
    }
  }
}

//=======================================================================
//function : Shape
//purpose  : 
//=======================================================================

TopoDS_Shape  DBRep_DrawableShape::Shape()const 
{
  return myShape;
}


//=======================================================================
//function : Copy
//purpose  : 
//=======================================================================

Handle(Draw_Drawable3D)  DBRep_DrawableShape::Copy()const 
{
  Handle(DBRep_DrawableShape) D =
    new DBRep_DrawableShape(myShape,
			    myFreeCol,
			    myConnCol,
			    myEdgeCol,
			    myIsosCol,
			    mySize,
			    myNbIsos,
			    myDiscret);
  return D;
}

//=======================================================================
//function : DisplayOrientation
//purpose  : 
//=======================================================================

void DBRep_DrawableShape::DisplayOrientation(const Standard_Boolean D)
{
  myDispOr = D;
}

//=======================================================================
//function : DisplayTriangulation
//purpose  : 
//=======================================================================

void DBRep_DrawableShape::DisplayTriangulation(const Standard_Boolean D)
{
  mytriangulations = D;
}

//=======================================================================
//function : DisplayPolygons
//purpose  : 
//=======================================================================

void DBRep_DrawableShape::DisplayPolygons(const Standard_Boolean D)
{
  mypolygons = D;
}

//=======================================================================
//function : DisplayHLR
//purpose  : 
//=======================================================================

void DBRep_DrawableShape::DisplayHLR(const Standard_Boolean withHLR,
				     const Standard_Boolean withRg1,
				     const Standard_Boolean withRgN,
				     const Standard_Boolean withHid,
				     const Standard_Real ang)
{
  myHLR = withHLR;
  myRg1 = withRg1;
  myRgN = withRgN;
  myHid = withHid;
  myAng = ang;
}

//=======================================================================
//function : DisplayTriangulation
//purpose  : 
//=======================================================================

Standard_Boolean DBRep_DrawableShape::DisplayTriangulation() const
{
  return mytriangulations;
}

//=======================================================================
//function : DisplayPolygons
//purpose  : 
//=======================================================================

Standard_Boolean DBRep_DrawableShape::DisplayPolygons()const
{
  return mypolygons;
}

//=======================================================================
//function : GetDisplayHLR
//purpose  : 
//=======================================================================

void DBRep_DrawableShape::GetDisplayHLR(Standard_Boolean& withHLR,
					Standard_Boolean& withRg1,
					Standard_Boolean& withRgN,
					Standard_Boolean& withHid,
					Standard_Real& ang) const
{
  withHLR = myHLR;
  withRg1 = myRg1;
  withRgN = myRgN;
  withHid = myHid;
  ang     = myAng;
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

void  DBRep_DrawableShape::Dump(Standard_OStream& S)const 
{
  BRepTools::Dump(myShape,S);
}


//=======================================================================
//function : Whatis
//purpose  : 
//=======================================================================

void  DBRep_DrawableShape::Whatis(Draw_Interpretor& s)const 
{
  if (!myShape.IsNull()) {
      s << "shape ";
      switch (myShape.ShapeType()) {
      case TopAbs_COMPOUND :
	s << "COMPOUND";
	break;
      case TopAbs_COMPSOLID :
	s << "COMPSOLID";
	break;
      case TopAbs_SOLID :
	s << "SOLID";
	break;
      case TopAbs_SHELL :
	s << "SHELL";
	break;
      case TopAbs_FACE :
	s << "FACE";
	break;
      case TopAbs_WIRE :
	s << "WIRE";
	break;
      case TopAbs_EDGE :
	s << "EDGE";
	break;
      case TopAbs_VERTEX :
	s << "VERTEX";
	break;
      case TopAbs_SHAPE :
	s << "SHAPE";
	break;
      }

      s << " ";

      switch (myShape.Orientation()) {
      case TopAbs_FORWARD :
	s << "FORWARD";
	break;
      case TopAbs_REVERSED :
	s << "REVERSED";
	break;
      case TopAbs_INTERNAL :
	s << "INTERNAL";
	break;
      case TopAbs_EXTERNAL :
	s << "EXTERNAL";
	break;
      }

      if (myShape.Free())       s <<" Free";
      if (myShape.Modified())   s <<" Modified";
      if (myShape.Orientable()) s <<" Orientable";
      if (myShape.Closed())     s <<" Closed";
      if (myShape.Infinite())   s <<" Infinite";
      if (myShape.Convex())     s <<" Convex";
    }
}


//=======================================================================
//function : LastPick
//purpose  : 
//=======================================================================

void  DBRep_DrawableShape::LastPick(TopoDS_Shape& s, 
				    Standard_Real& u, Standard_Real& v)
{
  s = pickshape;
  u = upick;
  v = vpick;
}



//=======================================================================
//function : Display
//purpose  : 
//=======================================================================

void  DBRep_DrawableShape::Display(const Handle(Poly_Triangulation)& T,
				   const gp_Trsf&                    tr,
				   Draw_Display&                     dis) const
{
    // Build the connect tool
  Poly_Connect pc(T);

  Standard_Integer i,j, nFree, nbTriangles = T->NbTriangles();
  Standard_Integer t[3];

  // count the free edges
  nFree = 0;
  for (i = 1; i <= nbTriangles; i++) {
    pc.Triangles(i,t[0],t[1],t[2]);
    for (j = 0; j < 3; j++)
      if (t[j] == 0) nFree++;
  }

  // allocate the arrays
  TColStd_Array1OfInteger Free(1,2*nFree);
  
  // array is replaced on map because it is impossible
  // to calculate number of internal edges in advance
  // due to "internal edges"
  TColStd_DataMapOfIntegerInteger Internal;
  
  Standard_Integer fr = 1, in = 1;
  const Poly_Array1OfTriangle& triangles = T->Triangles();
  Standard_Integer n[3];
  for (i = 1; i <= nbTriangles; i++) {
    pc.Triangles(i,t[0],t[1],t[2]);
    triangles(i).Get(n[0],n[1],n[2]);
    for (j = 0; j < 3; j++) {
      Standard_Integer k = (j+1) % 3;
      if (t[j] == 0) {
	Free(fr)   = n[j];
	Free(fr+1) = n[k];
	fr += 2;
      }
      // internal edge if this triangle has a lower index than the adjacent
      else if (i < t[j]) {
	Internal.Bind(in, n[j]);
	Internal.Bind(in+1, n[k]);
	in += 2;
      }
    }
  }

  // Display the edges
  const TColgp_Array1OfPnt& Nodes = T->Nodes();
//  cout<<"nb nodes = "<<Nodes.Length()<<endl;
  
  // free edges
  Standard_Integer nn;
  dis.SetColor(Draw_rouge);
  nn = Free.Length() / 2;
  for (i = 1; i <= nn; i++) {
    dis.Draw(Nodes(Free(2*i-1)).Transformed(tr),
	     Nodes(Free(2*i)).Transformed(tr));
  }
  
  // internal edges

  dis.SetColor(Draw_bleu);
  TColStd_DataMapIteratorOfDataMapOfIntegerInteger aIt(Internal);
  for (; aIt.More(); aIt.Next()) {
    Standard_Integer n1 = aIt.Value();
    //alvays pair is put
    aIt.Next();
    Standard_Integer n2 = aIt.Value();
    dis.Draw(Nodes(n1).Transformed(tr),
	     Nodes(n2).Transformed(tr));

  }
}

