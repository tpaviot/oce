// Created on: 1995-12-11
// Created by: Jacques GOUSSARD
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



#include <BRepCheck_Edge.ixx>
#include <TColStd_Array1OfTransient.hxx>

#include <BRepCheck_ListOfStatus.hxx>
#include <BRepCheck_ListIteratorOfListOfStatus.hxx>

#include <BRep_TEdge.hxx>
#include <BRep_TFace.hxx>

#include <BRep_CurveRepresentation.hxx>
#include <BRep_ListOfCurveRepresentation.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>
#include <BRep_GCurve.hxx>
#include <BRep_CurveOnSurface.hxx>

#include <BRep_Tool.hxx>

#include <TopExp_Explorer.hxx>

#include <Geom_Surface.hxx>
#include <Geom_RectangularTrimmedSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <Geom2d_Curve.hxx>

#include <Geom2dAdaptor_HCurve.hxx>
#include <GeomAdaptor_Curve.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <GeomAdaptor_HSurface.hxx>
#include <Adaptor3d_CurveOnSurface.hxx>
#include <Adaptor3d_HCurveOnSurface.hxx>

#include <ProjLib_ProjectedCurve.hxx>
#include <GeomProjLib.hxx>
#include <Extrema_LocateExtPC.hxx>

#include <BRepCheck.hxx>
#include <Geom2dAdaptor.hxx>
#include <TopoDS.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS_Face.hxx>
#include <Precision.hxx>


//modified by NIZNHY-PKV Thu May 05 09:01:57 2011f
static 
  Standard_Boolean Validate(const Adaptor3d_Curve&,
			    const Adaptor3d_CurveOnSurface&,
			    const Standard_Real,
			    const Standard_Boolean);
static
  void PrintProblematicPoint(const gp_Pnt&,
			     const Standard_Real,
			     const Standard_Real);

static
  Standard_Real Prec(const Adaptor3d_Curve& aAC3D,
		     const Adaptor3d_CurveOnSurface& aACS);
static
  Standard_Real PrecCurve(const Adaptor3d_Curve& aAC3D);
static
  Standard_Real PrecSurface(const Adaptor3d_CurveOnSurface& aACS);

//static Standard_Boolean Validate(const Adaptor3d_Curve&,
//				 const Adaptor3d_Curve&,
//				 const Standard_Real,
//				 const Standard_Boolean);
//modified by NIZNHY-PKV Thu May 05 09:02:01 2011t

#define NCONTROL 23

//=======================================================================
//function : BRepCheck_Edge
//purpose  : 
//=======================================================================

BRepCheck_Edge::BRepCheck_Edge(const TopoDS_Edge& E)
{
  Init(E);
  myGctrl = Standard_True;
}

//=======================================================================
//function : Minimum
//purpose  : 
//=======================================================================

void BRepCheck_Edge::Minimum()
{

  if (!myMin) {
    BRepCheck_ListOfStatus thelist;
    myMap.Bind(myShape, thelist);
    BRepCheck_ListOfStatus& lst = myMap(myShape);
    myCref.Nullify();

    // Existence et unicite d`une representation 3D
    Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*)&myShape.TShape());
    BRep_ListIteratorOfListOfCurveRepresentation itcr(TE->Curves());
    Standard_Boolean exist = Standard_False;
    Standard_Boolean unique = Standard_True;
    // Search for a 3D reference. If no existent one, creates it with the 
    // first encountered CurveOnSurf; if multiple, chooses the first one...
    
    Standard_Boolean Degenerated = TE->Degenerated();
    Standard_Boolean SameParameter = TE->SameParameter();
    Standard_Boolean SameRange = TE->SameRange();
    if (!SameRange && SameParameter) {
      BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
    }
//    Handle(Geom_Curve) C3d;

    while (itcr.More()) {
      const Handle(BRep_CurveRepresentation)& cr = itcr.Value();
      if (cr->IsCurve3D()) {
	if (!exist) {
	  exist = Standard_True;
	}
	else {
	  unique = Standard_False;
	}
	if (myCref.IsNull() && !cr->Curve3D().IsNull()) {
	  myCref = cr;
	}
      }
      itcr.Next();
    }

    if (!exist) {
      BRepCheck::Add(lst,BRepCheck_No3DCurve);
      // myCref est nulle
    }
    else if (!unique) {
      BRepCheck::Add(lst,BRepCheck_Multiple3DCurve);
    }

    if (myCref.IsNull() && !Degenerated) {
      itcr.Initialize(TE->Curves());
      while (itcr.More()) {
	const Handle(BRep_CurveRepresentation)& cr = itcr.Value();
	if (cr->IsCurveOnSurface()) {
	  myCref = cr;
	  break;
	}
	itcr.Next();
      }
    }
    else if (!myCref.IsNull() && Degenerated){
      BRepCheck::Add(lst,BRepCheck_InvalidDegeneratedFlag);
    }

    if (!myCref.IsNull()) {
      const Handle(BRep_GCurve)& GCref = *((Handle(BRep_GCurve)*)&myCref);
      Standard_Real First,Last;
      GCref->Range(First,Last);
      if (Last<=First) {
	myCref.Nullify();
	BRepCheck::Add(lst,BRepCheck_InvalidRange);
      }
      else {
	if (myCref->IsCurve3D()) {
          // eap 6 Jun 2002 occ332
          // better transform C3d instead of transforming Surf upto C3d initial location,
          // on transformed BSpline surface 'same parameter' may seem wrong
          TopLoc_Location L = myShape.Location() * myCref->Location();
	  Handle(Geom_Curve) C3d = Handle(Geom_Curve)::DownCast
	    (myCref->Curve3D()->Transformed
	     (/*myCref->Location()*/L.Transformation()));
	  GeomAdaptor_Curve GAC3d(C3d,First,Last);
	  myHCurve = new GeomAdaptor_HCurve(GAC3d);
	}
	else { // curve on surface
	  Handle(Geom_Surface) Sref = myCref->Surface();
	  Sref = Handle(Geom_Surface)::DownCast
	    (Sref->Transformed(myCref->Location().Transformation()));
	  const Handle(Geom2d_Curve)& PCref = myCref->PCurve();
	  Handle(GeomAdaptor_HSurface) GAHSref = new GeomAdaptor_HSurface(Sref);
	  Handle(Geom2dAdaptor_HCurve) GHPCref = 
	    new Geom2dAdaptor_HCurve(PCref,First,Last);
	  Adaptor3d_CurveOnSurface ACSref(GHPCref,GAHSref);
	  myHCurve = new Adaptor3d_HCurveOnSurface(ACSref);
	}
      }
    }
    if (lst.IsEmpty()) {
      lst.Append(BRepCheck_NoError);
    }
    myMin = Standard_True;
  }
}


//=======================================================================
//function : InContext
//purpose  : 
//=======================================================================

void BRepCheck_Edge::InContext(const TopoDS_Shape& S)
{
  if (myMap.IsBound(S)) {
    return;
  }
  BRepCheck_ListOfStatus thelist;
  myMap.Bind(S, thelist);
  BRepCheck_ListOfStatus& lst = myMap(S);

  Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*)&myShape.TShape());
  Standard_Real Tol = BRep_Tool::Tolerance(TopoDS::Edge(myShape));

  TopAbs_ShapeEnum styp = S.ShapeType();
//  for (TopExp_Explorer exp(S,TopAbs_EDGE); exp.More(); exp.Next()) {
  TopExp_Explorer exp(S,TopAbs_EDGE) ;
  for ( ; exp.More(); exp.Next()) {
    if (exp.Current().IsSame(myShape)) {
      break;
    }
  }
  if (!exp.More()) {
    BRepCheck::Add(lst,BRepCheck_SubshapeNotInShape);
    return;
  }
  
  switch (styp) {
  case TopAbs_FACE:
    if (!myCref.IsNull()) {
      
      Standard_Boolean SameParameter = TE->SameParameter();
      Standard_Boolean SameRange = TE->SameRange();
//  Modified by skv - Tue Apr 27 11:48:13 2004 Begin
      if (!SameParameter || !SameRange) {
	if (!SameParameter)
	  BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
	if (!SameRange)
	  BRepCheck::Add(lst,BRepCheck_InvalidSameRangeFlag);

	return;
      }
//  Modified by skv - Tue Apr 27 11:48:14 2004 End
      Standard_Real First = myHCurve->FirstParameter();
      Standard_Real Last  = myHCurve->LastParameter();

      Handle(BRep_TFace)& TF = *((Handle(BRep_TFace)*) &S.TShape());
      const TopLoc_Location& Floc = S.Location();
      const TopLoc_Location& TFloc = TF->Location();
      const Handle(Geom_Surface)& Su = TF->Surface();
      TopLoc_Location L = (Floc * TFloc).Predivided(myShape.Location());
      Standard_Boolean pcurvefound = Standard_False;

      BRep_ListIteratorOfListOfCurveRepresentation itcr(TE->Curves());
      while (itcr.More()) {
	const Handle(BRep_CurveRepresentation)& cr = itcr.Value();
	if (cr != myCref && cr->IsCurveOnSurface(Su,L)) {
	  pcurvefound = Standard_True;
	  const Handle(BRep_GCurve)& GC = *((Handle(BRep_GCurve)*)&cr);
	  Standard_Real f,l;
	  GC->Range(f,l);
          // gka OCC
//  Modified by skv - Tue Apr 27 11:50:35 2004 Begin
// 	  if (SameRange && (fabs(f-First) > Precision::PConfusion() || fabs(l-Last)> Precision::PConfusion())) { //f != First || l != Last)) { gka OCC
	  if (fabs(f-First) > Precision::PConfusion() ||
	      fabs(l-Last)  > Precision::PConfusion()) {
	    BRepCheck::Add(lst,BRepCheck_InvalidSameRangeFlag);
	    BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
// 	    if (SameParameter) {
// 	      BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
// 	    }
	  }
//  Modified by skv - Tue Apr 27 11:50:37 2004 End
	  if (myGctrl) {
	    Handle(Geom_Surface) Sb = cr->Surface();
	    Sb = Handle(Geom_Surface)::DownCast
//	      (Su->Transformed(L.Transformation()));
 	      (Su->Transformed(/*L*/(Floc * TFloc).Transformation()));
	    Handle(Geom2d_Curve) PC = cr->PCurve();
	    Handle(GeomAdaptor_HSurface) GAHS = new GeomAdaptor_HSurface(Sb);
	    Handle(Geom2dAdaptor_HCurve) GHPC = new Geom2dAdaptor_HCurve(PC,f,l);
	    Adaptor3d_CurveOnSurface ACS(GHPC,GAHS);
	    Standard_Boolean ok = 
	      Validate(myHCurve->Curve(),ACS,Tol,SameParameter);
	    if (!ok) {
	      if (cr->IsCurveOnClosedSurface()) {
		BRepCheck::Add(lst,BRepCheck_InvalidCurveOnClosedSurface);
	      }
	      else {
		BRepCheck::Add(lst,BRepCheck_InvalidCurveOnSurface);
	      }
//  Modified by skv - Tue Apr 27 11:53:00 2004 Begin
	      BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
// 	      if (SameParameter) {
// 		BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
// 	      }
//  Modified by skv - Tue Apr 27 11:53:01 2004 End
	    }
	    if (cr->IsCurveOnClosedSurface()) {
	      GHPC->ChangeCurve2d().Load(cr->PCurve2(),f,l); // same bounds
	      ACS.Load(GAHS); // sans doute inutile
	      ACS.Load(GHPC); // meme remarque...
	      ok = Validate(myHCurve->Curve(),ACS,Tol,SameParameter);
	      if (!ok) {
		BRepCheck::Add(lst,BRepCheck_InvalidCurveOnClosedSurface);
//  Modified by skv - Tue Apr 27 11:53:20 2004 Begin
		if (SameParameter) {
		  BRepCheck::Add(lst,BRepCheck_InvalidSameParameterFlag);
		}
//  Modified by skv - Tue Apr 27 11:53:23 2004 End
	      }
	    }
	  }
	}
	itcr.Next();
      }

      if (!pcurvefound) {
	Handle(Geom_Plane) P;
	Handle(Standard_Type) dtyp = Su->DynamicType();
	if (dtyp == STANDARD_TYPE(Geom_RectangularTrimmedSurface)) {
	  P = Handle(Geom_Plane)::DownCast
	    (Handle(Geom_RectangularTrimmedSurface)::
	     DownCast(Su)->BasisSurface());
	}
	else {
	  P = Handle(Geom_Plane)::DownCast(Su);
	}
	if (P.IsNull()) { // not a plane
	  BRepCheck::Add(lst,BRepCheck_NoCurveOnSurface);
	}
	else { // on fait la projection a la volee, comme BRep_Tool
	  // plan en position
	  if (myGctrl) {
	    P = Handle(Geom_Plane)::
	      DownCast(P->Transformed(/*L*/(Floc * TFloc).Transformation()));// eap occ332
	    //on projette Cref sur ce plan
	    Handle(GeomAdaptor_HSurface) GAHS = new GeomAdaptor_HSurface(P);

	    // Dub - Normalement myHCurve est une GeomAdaptor_HCurve
	    GeomAdaptor_Curve& Gac = 
	      Handle(GeomAdaptor_HCurve)::DownCast(myHCurve)->ChangeCurve();
	    Handle(Geom_Curve) C3d = Gac.Curve();
	    Handle(Geom_Curve) ProjOnPlane = 
	      GeomProjLib::ProjectOnPlane(new Geom_TrimmedCurve(C3d,First,Last),
					  P, P->Position().Direction(),
					  Standard_True);
	    Handle(GeomAdaptor_HCurve) aHCurve = 
	      new GeomAdaptor_HCurve(ProjOnPlane);

	    ProjLib_ProjectedCurve proj(GAHS,aHCurve);
	    Handle(Geom2d_Curve) PC = Geom2dAdaptor::MakeCurve(proj);
	    Handle(Geom2dAdaptor_HCurve) GHPC = 
	      new Geom2dAdaptor_HCurve(PC,
				       myHCurve->FirstParameter(),
				       myHCurve->LastParameter());

	    Adaptor3d_CurveOnSurface ACS(GHPC,GAHS);
	    
	    Standard_Boolean ok = Validate(myHCurve->Curve(),ACS,
					   Tol,Standard_True); // voir dub...
	    if (!ok) {
	      BRepCheck::Add(lst,BRepCheck_InvalidCurveOnSurface);
	    }
	  }
	}
      }
    }
    break;
  case TopAbs_SOLID:
    {
      // on verifie que l`edge est bien connectee 2 fois (pas de bord libre)
      Standard_Integer nbconnection = 0;
      //TopExp_Explorer exp;
      for (exp.Init(S,TopAbs_FACE); exp.More(); exp.Next()) {
	const TopoDS_Face& fac = TopoDS::Face(exp.Current());
	TopExp_Explorer exp2;
	for (exp2.Init(fac,TopAbs_EDGE); exp2.More(); exp2.Next()) {
	  if (exp2.Current().IsSame(myShape)) {
	    nbconnection++;
	  }
	}
      }
      if (nbconnection < 2 && !TE->Degenerated()) {
	BRepCheck::Add(myMap(S),BRepCheck_FreeEdge);
      }
      else if (nbconnection > 2) {
	BRepCheck::Add(myMap(S),BRepCheck_InvalidMultiConnexity);
      }
      else {
	BRepCheck::Add(myMap(S),BRepCheck_NoError);
      }
    }
    break;
  default:
    break;
  }
  if (myMap(S).IsEmpty()) {
    myMap(S).Append(BRepCheck_NoError);
  }
}


//=======================================================================
//function : Blind
//purpose  : 
//=======================================================================

void BRepCheck_Edge::Blind()
{
//  Modified by skv - Tue Apr 27 11:36:01 2004 Begin
// The body of this function is removed because of its useless.
  if (!myBlind) {
    myBlind = Standard_True;
  }
//  Modified by skv - Tue Apr 27 11:36:02 2004 End
}


//=======================================================================
//function : GeometricControls
//purpose  : 
//=======================================================================

void BRepCheck_Edge::GeometricControls(const Standard_Boolean B)
{
  myGctrl = B;
}


//=======================================================================
//function : GeometricControls
//purpose  : 
//=======================================================================

Standard_Boolean BRepCheck_Edge::GeometricControls() const
{
  return myGctrl;
}




//=======================================================================
//function : Tolerance
//purpose  : 
//=======================================================================

Standard_Real BRepCheck_Edge::Tolerance()
{
  Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*)&myShape.TShape());
  Standard_Integer it, iRep=1, nbRep=(TE->Curves()).Extent();
  if (nbRep<=1) {
    return Precision::Confusion();
  }
  TColStd_Array1OfTransient theRep(1, nbRep*2);
  Standard_Real First, Last;
  if (!myHCurve.IsNull()) {
    First = myHCurve->FirstParameter();
    Last=  myHCurve->LastParameter();
  }
  else {
    BRep_Tool::Range(TopoDS::Edge(myShape), First, Last);
  }

  BRep_ListIteratorOfListOfCurveRepresentation itcr(TE->Curves());
  for (; itcr.More(); itcr.Next()) {
    const Handle(BRep_CurveRepresentation)& cr = itcr.Value();
    if (cr->IsCurve3D() && !TE->Degenerated()) {
      //// modified by jgv, 20.03.03 ////
      TopLoc_Location Loc = myShape.Location() * cr->Location();
      Handle(Geom_Curve) C3d = Handle(Geom_Curve)::DownCast
	(cr->Curve3D()->Transformed( Loc.Transformation() ));
      ///////////////////////////////////
      GeomAdaptor_Curve GAC3d(C3d,First,Last);
      it=iRep;
      if (iRep>1) {
	theRep(iRep)=theRep(1);
	it=1;
      }
      theRep(it) = new GeomAdaptor_HCurve(GAC3d);
      iRep++;
    }
    else if (cr->IsCurveOnSurface()) {
      {
        Handle(Geom_Surface) Sref = cr->Surface();
	//// modified by jgv, 20.03.03 ////
	TopLoc_Location Loc = myShape.Location() * cr->Location();
        Sref = Handle(Geom_Surface)::DownCast
          (Sref->Transformed( Loc.Transformation() ));
	///////////////////////////////////
        const Handle(Geom2d_Curve)& PCref = cr->PCurve();
        Handle(GeomAdaptor_HSurface) GAHSref = new GeomAdaptor_HSurface(Sref);
        Handle(Geom2dAdaptor_HCurve) GHPCref = 
          new Geom2dAdaptor_HCurve(PCref,First,Last);
        Adaptor3d_CurveOnSurface ACSref(GHPCref,GAHSref);
        theRep(iRep) = new Adaptor3d_HCurveOnSurface(ACSref);
        iRep++;
      }
      if (cr->IsCurveOnClosedSurface()) {
	Handle(Geom_Surface) Sref = cr->Surface();
	Sref = Handle(Geom_Surface)::DownCast
	  (Sref->Transformed(cr->Location().Transformation()));
	const Handle(Geom2d_Curve)& PCref = cr->PCurve2();
	Handle(GeomAdaptor_HSurface) GAHSref = new GeomAdaptor_HSurface(Sref);
	Handle(Geom2dAdaptor_HCurve) GHPCref = 
	  new Geom2dAdaptor_HCurve(PCref,First,Last);
	Adaptor3d_CurveOnSurface ACSref(GHPCref,GAHSref);
	theRep(iRep) = new Adaptor3d_HCurveOnSurface(ACSref);
	iRep++;
	nbRep++;
      }
    }
    else {
      nbRep--;
    }
  }

  Standard_Real dist2, tol2, tolCal=0., prm;
  gp_Pnt center, othP;
  Standard_Integer i;
  for (i= 0; i< NCONTROL; i++) {
    prm = ((NCONTROL-1-i)*First + i*Last)/(NCONTROL-1);
    tol2=dist2=0.;
    center=(*(Handle(Adaptor3d_HCurve)*)&theRep(1))->Value(prm);
    for (iRep=2; iRep<=nbRep; iRep++) {
      othP=(*(Handle(Adaptor3d_HCurve)*)&theRep(iRep))->Value(prm);
      dist2=center.SquareDistance(othP);
      if (dist2>tolCal) tolCal=dist2;
    }
    if (tol2>tolCal) {
      tolCal=tol2;
    }
  }
  // On prend 5% de marge car au dessus on crontrole severement
  return sqrt(tolCal)*1.05;
}

//=======================================================================
//function : Validate
//purpose  : 
//=======================================================================
Standard_Boolean Validate(const Adaptor3d_Curve& CRef,
			  const Adaptor3d_CurveOnSurface& Other,
			  const Standard_Real Tol,
			  const Standard_Boolean SameParameter)
{
  Standard_Boolean  Status, proj; 
  Standard_Real aPC, First, Last, Error;
  gp_Pnt  problematic_point ;
  //
  Status = Standard_True;
  Error = 0.;
  First = CRef.FirstParameter();
  Last  = CRef.LastParameter();
  //
  aPC=Precision::PConfusion();
  proj = (!SameParameter || 
	  fabs(Other.FirstParameter()-First) > aPC || 
	  fabs( Other.LastParameter()-Last) > aPC);
  if (!proj) {
    Standard_Integer i;
    Standard_Real Tol2, prm, dD;
    gp_Pnt pref, pother;
    //modified by NIZNHY-PKV Thu May 05 09:06:41 2011f
    //OCC22428
    dD=Prec(CRef, Other);//3.e-15;
    Tol2=Tol+dD;
    Tol2=Tol2*Tol2;
    //Tol2=Tol*Tol;
    //modified by NIZNHY-PKV Thu May 05 09:06:47 2011t
    
    for (i = 0; i< NCONTROL; ++i) {
      prm = ((NCONTROL-1-i)*First + i*Last)/(NCONTROL-1);
      pref = CRef.Value(prm);
      pother = Other.Value(prm);
      if (pref.SquareDistance(pother) > Tol2) {
	problematic_point = pref ;
	Status = Standard_False;
	Error  = pref.Distance(pother);
	PrintProblematicPoint(problematic_point, Error, Tol);
	return Status;
        //goto FINISH ;
      }
    }
  }
  else {
    Extrema_LocateExtPC refd,otherd;
    Standard_Real OFirst = Other.FirstParameter();
    Standard_Real OLast  = Other.LastParameter();
    gp_Pnt pd = CRef.Value(First);
    gp_Pnt pdo = Other.Value(OFirst);
    Standard_Real distt = pd.SquareDistance(pdo);
    if (distt > Tol*Tol) {
      problematic_point = pd ;
      Status = Standard_False ;
      Error = Sqrt(distt);
      PrintProblematicPoint(problematic_point, Error, Tol);
      return Status;
      //goto FINISH ;
    }
    pd = CRef.Value(Last);
    pdo = Other.Value(OLast);
    distt = pd.SquareDistance(pdo);
    if (distt > Tol*Tol) {
      problematic_point = pd ;
      Status = Standard_False ;
      Error = Sqrt(distt);
      PrintProblematicPoint(problematic_point, Error, Tol);
      return Status;
      //goto FINISH ;
    }

    refd.Initialize(CRef,First,Last,CRef.Resolution(Tol));
    otherd.Initialize(Other,OFirst,OLast,Other.Resolution(Tol));
    for (Standard_Integer i = 2; i< NCONTROL-1; i++) {
      Standard_Real rprm = ((NCONTROL-1-i)*First + i*Last)/(NCONTROL-1);
      gp_Pnt pref = CRef.Value(rprm);
      Standard_Real oprm = ((NCONTROL-1-i)*OFirst + i*OLast)/(NCONTROL-1);
      gp_Pnt pother = Other.Value(oprm);
      refd.Perform(pother,rprm);
      if (!refd.IsDone() || refd.SquareDistance() > Tol * Tol) {
	problematic_point = pref ;
	Status = Standard_False ;
	if (refd.IsDone()) {
	  Error = sqrt (refd.SquareDistance());
	}
	else {
	  Error = RealLast();
	}
	PrintProblematicPoint(problematic_point, Error, Tol);
	return Status;
        //goto FINISH ;
      }
      otherd.Perform(pref,oprm);
      if (!otherd.IsDone() || otherd.SquareDistance() > Tol * Tol) {
	problematic_point = pref ;
	Status = Standard_False ;
	if (otherd.IsDone()) {
	  Error = sqrt (otherd.SquareDistance());
	}
	else {
	  Error = RealLast();
	}
	PrintProblematicPoint(problematic_point, Error, Tol);
	return Status;
	//goto FINISH ;
      }
    }
  }
  //FINISH :
/*
#ifdef DEB
    if (! Status) {
      cout << " **** probleme de SameParameter au point :" << endl;
      cout << "         " << problematic_point.Coord(1) << " " 
	   << problematic_point.Coord(2) << " " 
	   << problematic_point.Coord(3) << endl ;
      cout << "   Erreur detectee :" << Error << " Tolerance :" << Tol << endl;
    }
#endif
*/

  return Status ;
  
}
//=======================================================================
//function : Prec
//purpose  : 
//=======================================================================
Standard_Real Prec(const Adaptor3d_Curve& aAC3D,
		   const Adaptor3d_CurveOnSurface& aACS)
{
  Standard_Real aXEmax, aXC, aXS;
  //
  aXC=PrecCurve(aAC3D);
  aXS=PrecSurface(aACS);
  aXEmax=(aXC>aXS) ? aXC: aXS;
  return aXEmax;
}
//=======================================================================
//function : PrecCurve
//purpose  : 
//=======================================================================
Standard_Real PrecCurve(const Adaptor3d_Curve& aAC3D)
{
  Standard_Real aXEmax;
  GeomAbs_CurveType aCT;
  //
  aXEmax=RealEpsilon(); 
  //
  aCT=aAC3D.GetType();
  if (aCT==GeomAbs_Ellipse) {
    Standard_Integer i;
    Standard_Real aX[5], aXE;
    //
    gp_Elips aEL3D=aAC3D.Ellipse();
    aEL3D.Location().Coord(aX[0], aX[1], aX[2]);
    aX[3]=aEL3D.MajorRadius();
    aX[4]=aEL3D.MinorRadius();
    aXEmax=-1.;
    for (i=0; i<5; ++i) {
      if (aX[i]<0.) {
	aX[i]=-aX[i];
      }
      aXE=Epsilon(aX[i]);
      if (aXE>aXEmax) {
	aXEmax=aXE;
      }
    }
  }//if (aCT=GeomAbs_Ellipse) {
  //
  return aXEmax;
}
//=======================================================================
//function : PrecSurface
//purpose  : 
//=======================================================================
Standard_Real PrecSurface(const Adaptor3d_CurveOnSurface& aACS)
{
  Standard_Real aXEmax;
  GeomAbs_SurfaceType aST;
  //
  aXEmax=RealEpsilon(); 
  //
  const Handle(Adaptor3d_HSurface)& aAHS=aACS.GetSurface();
  aST=aAHS->GetType();
  if (aST==GeomAbs_Cone) {
    gp_Cone aCone=aAHS->Cone();
    Standard_Integer i;
    Standard_Real aX[4], aXE;
    //
    aCone.Location().Coord(aX[0], aX[1], aX[2]);
    aX[3]=aCone.RefRadius();
    aXEmax=-1.;
    for (i=0; i<4; ++i) {
      if (aX[i]<0.) {
	aX[i]=-aX[i];
      }
      aXE=Epsilon(aX[i]);
      if (aXE>aXEmax) {
	aXEmax=aXE;
      }
    }
  }//if (aST==GeomAbs_Cone) {
  return aXEmax;
}
//=======================================================================
//function : PrintProblematicPoint
//purpose  : 
//=======================================================================
#ifdef DEB
void PrintProblematicPoint(const gp_Pnt& problematic_point,
			   const Standard_Real Error,
			   const Standard_Real Tol)
{
  cout << " **** probleme de SameParameter au point :" << endl;
  cout << "         " << problematic_point.Coord(1) << " " 
    << problematic_point.Coord(2) << " " << problematic_point.Coord(3) << endl ;
  cout << "   Erreur detectee :" << Error << " Tolerance :" << Tol << endl;
}
#else
void PrintProblematicPoint(const gp_Pnt&,
			   const Standard_Real,
			   const Standard_Real)
{
}
#endif
