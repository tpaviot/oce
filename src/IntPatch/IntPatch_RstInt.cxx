// Created on: 1993-05-07
// Created by: Jacques GOUSSARD
// Copyright (c) 1993-1999 Matra Datavision
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


// ----------------------------------------------------------------------
//-- lbr: Modifs importantes du 16-17 Nov 95
//--      - Chercher APointOnRstStillExist et OnDifferentRst
//--      On veut pouvoir creer un Vtx (A1 sur S1, A2    sur S2)
//--                         et le Vtx (A1 sur S1, A2bis sur S2)
//--      ce qui revient a distinguer un point deja pose sur une 
//--      restriction de S avec un point pose sur une nouvelle
//--       restriction de S.
//--      - Pour rester coherent avec cette facon de faire, 
//--      Chercher(Nbvtx++). 

#include <IntPatch_RstInt.ixx>

#include <IntSurf.hxx>

#include <TColgp_SequenceOfPnt.hxx>
#include <TColgp_SequenceOfPnt2d.hxx>
#include <Intf_SectionPoint.hxx>
#include <Intf_TangentZone.hxx>
#include <gp_Pnt2d.hxx>
#include <Precision.hxx>

#include <Adaptor2d_HCurve2d.hxx>
#include <IntPatch_WLine.hxx>
#include <IntPatch_RLine.hxx>
#include <IntPatch_HInterTool.hxx>
#include <IntPatch_SearchPnt.hxx>
#include <IntPatch_PolyLine.hxx>
#include <IntPatch_PolyArc.hxx>
#include <IntPatch_CSFunction.hxx>
#include <IntPatch_CurvIntSurf.hxx>


static void Recadre(GeomAbs_SurfaceType typeS1,
                    GeomAbs_SurfaceType typeS2,
                    const Handle(IntPatch_WLine)& wlin,
                    Standard_Integer Param,
                    Standard_Real& U1,
                    Standard_Real& V1,
                    Standard_Real& U2,
                    Standard_Real& V2)
{
  Standard_Integer nbpnts = wlin->NbPnts();
  if(Param<1) Param=1; else if(Param>nbpnts) Param=nbpnts;
  Standard_Real U1p,V1p,U2p,V2p;

  wlin->Point(Param).Parameters(U1p,V1p,U2p,V2p);
  switch(typeS1) { 
  case GeomAbs_Cylinder:
  case GeomAbs_Cone:
  case GeomAbs_Sphere:
  case GeomAbs_Torus:
    while(U1<(U1p-1.5*M_PI)) U1+=M_PI+M_PI;
    while(U1>(U1p+1.5*M_PI)) U1-=M_PI+M_PI;
    break;
  default: 
    break;
  }
  if(typeS1==GeomAbs_Torus) { 
    while(V1<(V1p-1.5*M_PI)) V1+=M_PI+M_PI;
    while(V1>(V1p+1.5*M_PI)) V1-=M_PI+M_PI;
  }
  
  switch(typeS2) { 
  case GeomAbs_Cylinder:
  case GeomAbs_Cone:
  case GeomAbs_Sphere:
  case GeomAbs_Torus:
    while(U2<(U2p-1.5*M_PI)) U2+=M_PI+M_PI;
    while(U2>(U2p+1.5*M_PI)) U2-=M_PI+M_PI;
    break;
  default: 
    break;
  }
  if(typeS2==GeomAbs_Torus) { 
    while(V2<(V1p-1.5*M_PI)) V2+=M_PI+M_PI;
    while(V2>(V2p+1.5*M_PI)) V2-=M_PI+M_PI;
  }
}

const Standard_Real Confusion = Precision::Confusion();

inline Standard_Real Tol3d (const Handle(Adaptor3d_HVertex)& vtx,
			    const Handle(Adaptor3d_TopolTool)& Domain,
			    const Standard_Real tolDef = 0.)
{
  return (Domain->Has3d() ? Domain->Tol3d(vtx)
	  : tolDef < Confusion ? Confusion
	  : tolDef);
}

inline Standard_Real Tol3d (const Handle(Adaptor2d_HCurve2d)& arc,
			    const Handle(Adaptor3d_TopolTool)& Domain,
			    const Standard_Real tolDef = 0.)
{
  return (Domain->Has3d() ? Domain->Tol3d(arc)
	  : tolDef < Confusion ? Confusion
	  : tolDef);
}

static Standard_Boolean CoincideOnArc(const gp_Pnt& Ptsommet,
				      const Handle(Adaptor2d_HCurve2d)& A,
				      const Handle(Adaptor3d_HSurface)& Surf,
				      const Standard_Real Toler,
				      const Handle(Adaptor3d_TopolTool)& Domain,
				      Handle(Adaptor3d_HVertex)& Vtx)
{
  Standard_Real distmin = RealLast();
  Standard_Real tolarc = Max(Toler,Tol3d(A,Domain));

  Domain->Initialize(A);
  Domain->InitVertexIterator();
  while (Domain->MoreVertex()) {
    Handle(Adaptor3d_HVertex) vtx1 = Domain->Vertex();
    Standard_Real prm = IntPatch_HInterTool::Parameter(vtx1,A);
    gp_Pnt2d p2d = A->Value(prm);
    gp_Pnt point = Surf->Value(p2d.X(),p2d.Y());
    const Standard_Real dist = point.Distance(Ptsommet);
    Standard_Real tol = Max (tolarc, Tol3d(vtx1,Domain));

    if (dist <= tol && dist <= distmin) { // the best coincidence
      distmin = dist;
      Vtx = vtx1;
    }
    Domain->NextVertex();
  }
  return distmin < RealLast();
}


static void VerifyTgline(const Handle(IntPatch_WLine)& wlin,
			 const Standard_Integer param,
			 const Standard_Real Tol,
			 gp_Vec& Tgl) { 
  
  if(   Abs(Tgl.X())<Tol 
     && Abs(Tgl.Y())<Tol
     && Abs(Tgl.Z())<Tol) { 
    //-- On construit une tangente plus grande
    //-- (Eviter des points tres proches ds Walking)		    
    Standard_Integer i, n, nbpt=wlin->NbPnts();
    Standard_Boolean forward = (nbpt-param) >= (param-1);
    for (n = 2; n > 0; n--, forward = !forward) {
      if (forward) {
	for(i=param+1; i<=nbpt; i++) { 
	  gp_Vec T(wlin->Point(param).Value(),wlin->Point(i).Value());
	  if(   Abs(T.X())>=Tol 
	     || Abs(T.Y())>=Tol
	     || Abs(T.Z())>=Tol) { 
	    Tgl = T ; 
	    return;
	  }
	}
      }
      else {
	for(i=param-1; i>=1; i--) { 
	  gp_Vec T(wlin->Point(i).Value(),wlin->Point(param).Value());
	  if(   Abs(T.X())>=Tol 
	     || Abs(T.Y())>=Tol
	     || Abs(T.Z())>=Tol) { 
	    Tgl = T ; 
	    return;
	  }
	}
      }
    }
  }
}  

static void GetLinePoint2d (const Handle(IntPatch_Line)& L,
			    const Standard_Real param,
			    const Standard_Boolean OnFirst,
			    Standard_Real& U, Standard_Real& V)
{
  IntPatch_IType typL = L->ArcType();
  const Handle(IntPatch_WLine)& wlin = (const Handle(IntPatch_WLine)&)L;
  const Handle(IntPatch_RLine)& rlin = (const Handle(IntPatch_RLine)&)L;
  Standard_Integer Nbptlin = (typL == IntPatch_Walking
			      ? wlin->NbPnts()
			      : rlin->NbPnts());

  Standard_Real par = IntegerPart(param);
  Standard_Integer Irang = Standard_Integer(par);
  if (Irang == Nbptlin) {
    Irang--;
    par = 1.0;
  }
  else
    par = Abs(param-par);

  Standard_Real us1,vs1,us2,vs2;
  if (typL == IntPatch_Walking) {
    if (OnFirst) {
      wlin->Point(Irang).ParametersOnS1(us1,vs1);
      wlin->Point(Irang+1).ParametersOnS1(us2,vs2);
    }
    else {
      wlin->Point(Irang).ParametersOnS2(us1,vs1);
      wlin->Point(Irang+1).ParametersOnS2(us2,vs2);
    }
  }
  else {
    if (OnFirst) {
      rlin->Point(Irang).ParametersOnS1(us1,vs1);
      rlin->Point(Irang+1).ParametersOnS1(us2,vs2);
    }
    else {
      rlin->Point(Irang).ParametersOnS2(us1,vs1);
      rlin->Point(Irang+1).ParametersOnS2(us2,vs2);
    }
  }

  U = (1.-par)*us1+par*us2;
  V = (1.-par)*vs1+par*vs2;
}

static void GetWLinePoint (const Handle(IntPatch_WLine)& wlin,
			  const Standard_Real param,
			  Standard_Real& U1, Standard_Real& V1,
			  Standard_Real& U2, Standard_Real& V2,
			  gp_Pnt& P)
{
  Standard_Integer Nbptlin = wlin->NbPnts();
  Standard_Real par = IntegerPart(param);
  Standard_Integer Irang = Standard_Integer(par);
  if (Irang == Nbptlin) {
    Irang--;
    par = 1.0;
  }
  else
    par = Abs(param-par);

  const IntSurf_PntOn2S& p2s1 = wlin->Point(Irang);
  const IntSurf_PntOn2S& p2s2 = wlin->Point(Irang+1);
  const gp_Pnt& p1 = p2s1.Value();
  const gp_Pnt& p2 = p2s2.Value();
  P.ChangeCoord().SetLinearForm(1.-par, p1.XYZ(), par, p2.XYZ());

  Standard_Real us1,vs1,us2,vs2;
  p2s1.ParametersOnS1(us1,vs1);
  p2s2.ParametersOnS1(us2,vs2);
  U1 = (1.-par)*us1+par*us2;
  V1 = (1.-par)*vs1+par*vs2;

  p2s1.ParametersOnS2(us1,vs1);
  p2s2.ParametersOnS2(us2,vs2);
  U2 = (1.-par)*us1+par*us2;
  V2 = (1.-par)*vs1+par*vs2;
}

static Standard_Boolean FindParameter(const Handle(IntPatch_Line)& L,
				      const Handle(Adaptor3d_HSurface)& OtherSurf,
				      const Standard_Real Tol,
				      const gp_Pnt& Ptsom,
				      const gp_Pnt2d& Ptsom2d,
				      Standard_Real& Param,
				      gp_Vec& Tgl,
				      const Standard_Integer ParamApproche,
				      const Standard_Boolean OnFirst)

{
  // MSV 28.03.2002: find parameter on WLine in 2d space

  //Si la ligne est de type restriction, c est qu on provient necessairement
  // du cas implicite/parametree, et que la ligne est restriction de
  // la surface bi-parametree. Cette surface bi-parametree est necessairement
  // passee en argument a PutVertexOnline dans la variable OtherSurf.

  // Dans le cas d une ligne de cheminement, il faudrait voir la projection
  // et le calcul de la tangente.

  const Handle(IntPatch_RLine)&  rlin = (*((Handle(IntPatch_RLine)*)&L)); //-- aucune verification n est 
  const Handle(IntPatch_WLine)&  wlin = (*((Handle(IntPatch_WLine)*)&L)); //-- faite au cast. 
  gp_Pnt ptbid;
  gp_Vec d1u,d1v;
  gp_Pnt2d p2d;
  gp_Vec2d d2d;
  Standard_Real Tol2 = Tol*Tol;
  IntPatch_IType typL = L->ArcType();
  Tgl.SetCoord(0.0,0.0,0.0);

  if ( typL == IntPatch_Restriction) {
    if     (!OnFirst && rlin->IsArcOnS1()) { 
      IntPatch_HInterTool::Project(rlin->ArcOnS1(),Ptsom2d,Param,p2d);
      rlin->ArcOnS1()->D1(Param,p2d,d2d);
    }
    else if (OnFirst && rlin->IsArcOnS2()) { 
      IntPatch_HInterTool::Project(rlin->ArcOnS2(),Ptsom2d,Param,p2d);
      rlin->ArcOnS2()->D1(Param,p2d,d2d);
    }
    else { 
      return(Standard_False);
    }
    OtherSurf->D1(p2d.X(),p2d.Y(),ptbid,d1u,d1v);
    if (ptbid.SquareDistance(Ptsom) > Tol2) {
      return Standard_False;
    }
    Tgl.SetLinearForm(d2d.X(),d1u,d2d.Y(),d1v);
    return(Standard_True);
  }

  else if (typL == IntPatch_Walking) {
    Standard_Integer i, is, nbpt=wlin->NbPnts();
    Standard_Real norm1,norm2;
    Standard_Integer ParamSearchInf=1;
    Standard_Integer ParamSearchSup=nbpt;

    if((ParamApproche-2) > ParamSearchInf) { 
      ParamSearchInf = ParamApproche-2;
    }
    if((ParamApproche+2) < ParamSearchSup) { 
      ParamSearchSup = ParamApproche+2;
    }

    Standard_Integer inf[3],sup[3];
    // first search inside close bounding around ParamApproche;
    // then search to the nearest end of line;
    // and then search to the farest end of line.
    inf[0] = ParamSearchInf; sup[0] = ParamSearchSup;
    if (ParamSearchInf-1 < nbpt-ParamSearchSup) {
      inf[1] = 1;              sup[1] = ParamSearchInf;
      inf[2] = ParamSearchSup; sup[2] = nbpt;
    }
    else {
      inf[1] = ParamSearchSup; sup[1] = nbpt;
      inf[2] = 1;              sup[2] = ParamSearchInf;
    }

    Standard_Boolean found = Standard_False;
    for (is=0; is < 3 && !found; is++) {
      gp_Vec v1,v2;
      gp_Pnt p1,p2;
      p1 = wlin->Point(inf[is]).Value();
      v1 = gp_Vec (Ptsom,p1);
      norm1 = v1.SquareMagnitude();
      Standard_Real normmin = Tol2;
      Standard_Integer ibest = 0;
      if (norm1 <= normmin) {
	normmin = norm1;
	ibest = inf[is];
      }
      for (i=inf[is]+1; i <= sup[is] && !found; i++) {
	p2 = wlin->Point(i).Value();
	v2 = gp_Vec (Ptsom,p2);
	norm2 = v2.SquareMagnitude();
	if (v1.Dot(v2) < 0.) {
	  Param = (Standard_Real)(i-1) + 1./(1.+Sqrt(norm2/norm1));
	  Tgl = gp_Vec (p1,p2);
	  found = Standard_True;
	}
	else if (norm2 < normmin) {
	  normmin = norm2;
	  ibest = i;
	}
	v1 = v2; p1 = p2; norm1 = norm2;
      }
      if (!found && ibest) {
	Param = (Standard_Real)ibest;
	found = Standard_True;
      }
    }
    if (found) return Standard_True;
  }
  else {
    Standard_DomainError::Raise();
  }
  return Standard_False;
}

inline Standard_Boolean ArePnt2dEqual(const gp_Pnt2d& p1, const gp_Pnt2d& p2,
				      const Standard_Real tolU,
				      const Standard_Real tolV)
{
  return Abs(p1.X()-p2.X()) < tolU && Abs(p1.Y()-p2.Y()) < tolV;
}

static gp_Pnt2d GetPointOnPolygo(const IntPatch_Polygo& Pol,
				 const Standard_Real param)
{
  Standard_Real par = IntegerPart(param);
  Standard_Integer irang = Standard_Integer(par) + 1;
  if (irang == Pol.NbPoints()) {
    irang--;
    par = 1.;
  }
  else {
    par = Abs(param-par);
  }
  gp_Pnt2d p1 = Pol.Point(irang);
  gp_Pnt2d p2 = Pol.Point(irang+1);
  gp_Pnt2d p;
  p.ChangeCoord().SetLinearForm(1.-par,p1.XY(),par,p2.XY());
  return p;
}

static Standard_Boolean IsSegment2dSmall(const IntPatch_Polygo& Pol,
					 const Standard_Real parmin,
					 const Standard_Real parmax,
					 const Standard_Real URes,
					 const Standard_Real VRes)
{
  Standard_Integer irang1 = Standard_Integer(IntegerPart(parmin)) + 2;
  Standard_Integer irang2 = Standard_Integer(IntegerPart(parmax)) + 1;
  gp_Pnt2d p1,p2;
  Standard_Real du=0.,dv=0.;
  p1 = GetPointOnPolygo(Pol,parmin);
  for (Standard_Integer i=irang1; i <= irang2 && du <= URes && dv <= VRes; i++) {
    p2 = Pol.Point(i);
    du += Abs(p2.X()-p1.X());
    dv += Abs(p2.Y()-p1.Y());
    p1 = p2;
  }
  if (du <= URes && dv <= VRes) {
    p2 = GetPointOnPolygo(Pol,parmax);
    du += Abs(p2.X()-p1.X());
    dv += Abs(p2.Y()-p1.Y());
  }
  return du <= URes && dv <= VRes;
}

//=======================================================================
//function : PutVertexOnLine
//purpose  : 
//=======================================================================

void IntPatch_RstInt::PutVertexOnLine (Handle(IntPatch_Line)& L,
				       const Handle(Adaptor3d_HSurface)& Surf,
				       const Handle(Adaptor3d_TopolTool)& Domain,
				       const Handle(Adaptor3d_HSurface)& OtherSurf,
				       const Standard_Boolean OnFirst,
				       const Standard_Real Tol )
 {

// Domain est le domaine de restriction de la surface Surf.
// On intersectera un arc de Surf avec la surface OtherSurf.
// Si OnFirst = True, c est que la surface Surf correspond a la 1ere
// surface donnee aux algo d intersection.

  static   IntPatch_SearchPnt Commun;

  Standard_Real U,V,W;
  Standard_Real U1,V1,U2 = 0,V2 = 0;
  Standard_Real paramarc=0.,paramline=0.;
  Standard_Integer i,j,k;
  TColgp_SequenceOfPnt locpt;
  TColgp_SequenceOfPnt2d locpt2;
  const Handle(IntPatch_RLine)&  rlin = (*((Handle(IntPatch_RLine)*)&L)); //-- aucune verification n est 
  const Handle(IntPatch_WLine)&  wlin = (*((Handle(IntPatch_WLine)*)&L)); //-- faite au cast. 
  Standard_Integer Nbvtx =0; 
  Standard_Integer Nbptlin =0;
  Standard_Real tolPLin = Surf->UResolution(Precision::Confusion());
  tolPLin = Max (tolPLin, Surf->VResolution(Precision::Confusion()));
  tolPLin = Min (tolPLin, Precision::Confusion());
  IntPatch_PolyLine PLin(tolPLin);

  Standard_Real PFirst,PLast;
  Standard_Integer NbEchant;
  gp_Pnt ptsommet, ptbid;
  gp_Vec tgline, tgrst, d1u, d1v, normsurf;

  gp_Pnt2d p2d;
  gp_Vec2d d2d;

  IntPatch_Point Sommet, ptline;
  Handle(Adaptor3d_HVertex) vtxarc,vtxline;
  Handle(Adaptor2d_HCurve2d) arc;
  Standard_Boolean VtxOnArc, duplicate, found;
  IntSurf_Transition transarc,transline;

  IntPatch_IType typL = L->ArcType();
  if (typL == IntPatch_Walking) {
    Nbvtx = wlin->NbVertex();
    PLin.SetWLine(OnFirst,wlin);
    Nbptlin = wlin->NbPnts();
  }
  else if ( typL == IntPatch_Restriction) {
    Nbvtx = rlin->NbVertex();
    PLin.SetRLine(OnFirst,rlin);
    Nbptlin = rlin->NbPnts();
  }
  else {
    Standard_DomainError::Raise();
  }
  if (!Domain->Has3d())
    // don't use computed deflection in the mode of pure geometric intersection
    PLin.ResetError();

  const Standard_Boolean SurfaceIsUClosed = Surf->IsUClosed();
  const Standard_Boolean SurfaceIsVClosed = Surf->IsVClosed();
  const Standard_Boolean OSurfaceIsUClosed = OtherSurf->IsUClosed();
  const Standard_Boolean OSurfaceIsVClosed = OtherSurf->IsVClosed();
  const Standard_Boolean possiblyClosed = (SurfaceIsUClosed || SurfaceIsVClosed ||
                                           OSurfaceIsUClosed || OSurfaceIsVClosed);
  Standard_Real tolUClosed=0., tolVClosed=0., tolOUClosed=0., tolOVClosed=0.;
  if (possiblyClosed) {
    if (SurfaceIsUClosed)
      tolUClosed = (Surf->LastUParameter() - Surf->FirstUParameter()) * 0.01;
    if (SurfaceIsVClosed)
      tolVClosed = (Surf->LastVParameter() - Surf->FirstVParameter()) * 0.01;
    if (OSurfaceIsUClosed)
      tolOUClosed = (OtherSurf->LastUParameter() - OtherSurf->FirstUParameter()) * 0.01;
    if (OSurfaceIsVClosed)
      tolOVClosed = (OtherSurf->LastVParameter() - OtherSurf->FirstVParameter()) * 0.01;
  }

  //------------------------------------------------------------------------
  //-- On traite le cas ou la surface est periodique                      --
  //-- il faut dans ce cas considerer la restriction                      --
  //--                                la restriction decalee de +-2PI     --
  //------------------------------------------------------------------------
  const Handle(Adaptor3d_HSurface)& Surf1 = (OnFirst ? Surf : OtherSurf);
  const Handle(Adaptor3d_HSurface)& Surf2 = (OnFirst ? OtherSurf : Surf);
  GeomAbs_SurfaceType TypeS1 = Surf1->GetType();
  GeomAbs_SurfaceType TypeS2 = Surf2->GetType();
  Standard_Boolean SurfaceIsPeriodic   = Standard_False;
  Standard_Boolean SurfaceIsBiPeriodic = Standard_False;
  GeomAbs_SurfaceType surfacetype = (OnFirst ? TypeS1 : TypeS2);
  if(   surfacetype == GeomAbs_Cylinder
     || surfacetype == GeomAbs_Cone
     || surfacetype == GeomAbs_Torus
     || surfacetype == GeomAbs_Sphere) { 
    SurfaceIsPeriodic = Standard_True;
    if(surfacetype == GeomAbs_Torus) { 
      SurfaceIsBiPeriodic = Standard_True;
    }
  }
  
  Standard_Integer NumeroEdge=0;
  Domain->Init();
  while (Domain->More()) {
    NumeroEdge++;
    arc = Domain->Value();

    // MSV Oct 15, 2001: use tolerance of this edge if possible
    Standard_Real edgeTol = Tol3d(arc,Domain,Tol);
    Standard_Real URes = Surf->UResolution(edgeTol);
    Standard_Real VRes = Surf->VResolution(edgeTol);

    IntPatch_HInterTool::Bounds(arc,PFirst,PLast);
    if (Precision::IsNegativeInfinite(PFirst) || 
	Precision::IsPositiveInfinite(PLast)) { 
      //-- cout<<" IntPatch_RstInt::PutVertexOnLine  ---> Restrictions Infinies :"<<endl;
      return; 
    }

    Standard_Boolean isVFirst = Standard_False, isVLast = Standard_False;
    gp_Pnt2d p2dFirst,p2dLast;
    Standard_Real tolUFirst=0.,tolVFirst=0.,tolULast=0.,tolVLast=0.;
    Domain->Initialize(arc);
    for (Domain->InitVertexIterator(); Domain->MoreVertex(); Domain->NextVertex()) {
      Handle(Adaptor3d_HVertex) vtx = Domain->Vertex();
      Standard_Real prm = IntPatch_HInterTool::Parameter(vtx,arc);
      if (Abs(prm - PFirst) < Precision::PConfusion()) {
	arc->D0(PFirst,p2dFirst);
	Standard_Real tol3d = Max (Tol3d(vtx,Domain), edgeTol);
	tolUFirst = Surf->UResolution(tol3d);
	tolVFirst = Surf->VResolution(tol3d);
	isVFirst = Standard_True;
      }
      else if (Abs(prm - PLast) < Precision::PConfusion()) {
	arc->D0(PLast,p2dLast);
	Standard_Real tol3d = Max (edgeTol, Tol3d(vtx,Domain));
	tolULast = Surf->UResolution(tol3d);
	tolVLast = Surf->VResolution(tol3d);
	isVLast = Standard_True;
      }
    }

    Bnd_Box2d BPLin = PLin.Bounding();

    if(SurfaceIsPeriodic) { 
      Standard_Real xmin,ymin,xmax,ymax,g;
      BPLin.Get(xmin,ymin,xmax,ymax);
      g = BPLin.GetGap();
      BPLin.SetVoid();
      BPLin.Update(xmin-M_PI-M_PI,ymin,
		   xmax+M_PI+M_PI,ymax);
      BPLin.SetGap(g);
    }
    if(SurfaceIsBiPeriodic) { 
      Standard_Real xmin,ymin,xmax,ymax,g;
      BPLin.Get(xmin,ymin,xmax,ymax);
      g = BPLin.GetGap();
      BPLin.SetVoid();
      BPLin.Update(xmin,ymin-M_PI-M_PI,
		   xmax,ymax+M_PI+M_PI);
      BPLin.SetGap(g);
    }

    switch(arc->GetType())
    { 
      case GeomAbs_Line: NbEchant=10; break;
      case GeomAbs_BezierCurve:
      {
        NbEchant = (3 + arc->NbPoles());
	    if(NbEchant<10) NbEchant=10;
        else if(NbEchant>50) NbEchant=50;
      }
	  break;
      case GeomAbs_BSplineCurve:
      { 
        //szv:const Standard_Real nbs = (arc->NbKnots() * arc->Degree())*(arc->LastParameter() - arc->FirstParameter())/(PLast-PFirst);
        const Standard_Real nbs = (arc->NbKnots() * arc->Degree())*(PLast-PFirst)/(arc->LastParameter() - arc->FirstParameter());
		NbEchant = (nbs < 2.0 ? 2 : (Standard_Integer)nbs);
	    if(NbEchant<10) NbEchant=10;
        else if (NbEchant>50) NbEchant=50;
      }
      break;
      default:
      {
	    NbEchant = 25;
      }
    }

    IntPatch_PolyArc Brise(arc,NbEchant,PFirst,PLast,BPLin);

    Standard_Integer IndiceOffsetBiPeriodic = 0;    
    Standard_Integer IndiceOffsetPeriodic   = 0;    
    Standard_Real OffsetV = 0.0;
    Standard_Real OffsetU = 0.0;
    
    do { 
      if(IndiceOffsetBiPeriodic == 1) 
	OffsetV = -M_PI-M_PI;
      else if(IndiceOffsetBiPeriodic == 2) 
	OffsetV = M_PI+M_PI;
      
      do { 
	if(IndiceOffsetPeriodic == 1) 
	  OffsetU = -M_PI-M_PI;
	else if(IndiceOffsetPeriodic == 2) 
	  OffsetU = M_PI+M_PI;
	
	Brise.SetOffset(OffsetU,OffsetV);
	
	static int debug_polygon2d =0;
	if(debug_polygon2d) { 
	  cout<<" ***** Numero Restriction : "<<NumeroEdge<<" *****"<<endl;
	  PLin.Dump();
	  Brise.Dump();
	}
	
	Commun.Perform(PLin,Brise);
	locpt.Clear();
	locpt2.Clear();
	Standard_Integer Commun_NbSectionPoints = Commun.NbSectionPoints();
	Standard_Integer Commun_NbTangentZones  = Commun.NbTangentZones();
	Standard_Integer Commun_Section_Tangent = Commun_NbSectionPoints
	  + Commun_NbTangentZones;
	for (i=1;i<=Commun_Section_Tangent;i++) {
	  Standard_Real W1[2],W2[2];
	  Standard_Boolean refine[2],useWL[2];
	  Standard_Integer nbpt = 1;
	  if(i<=Commun_NbSectionPoints) { 
	    // intersection point
	    W1[0] = Commun.PntValue(i).ParamOnFirst();
	    W2[0] = Commun.PntValue(i).ParamOnSecond();
	    refine[0] = Standard_True;
	  }
	  else { 
	    // tangent zone
	    Standard_Real UMinCh,UMaxCh;  //-- ligne de cheminement 0..(Nbptlin-1)
	    Standard_Real UMinAr,UMaxAr;  //-- polyline of arc 0..(NbEchant-1)
	    Commun.ZoneValue(i-Commun_NbSectionPoints).ParamOnFirst(UMinCh,UMaxCh);
	    Commun.ZoneValue(i-Commun_NbSectionPoints).ParamOnSecond(UMinAr,UMaxAr);
	    gp_Pnt2d p1Ar = GetPointOnPolygo(Brise,UMinAr);
	    gp_Pnt2d p2Ar = GetPointOnPolygo(Brise,UMaxAr);
	    Standard_Real tolU = URes*2.;
	    Standard_Real tolV = VRes*2.;
	    if (isVFirst && ArePnt2dEqual(p1Ar,p2dFirst,tolUFirst,tolVFirst)) {
	      tolU = Max(tolUFirst,tolU); tolV = Max(tolVFirst,tolV);
	    }
	    if (isVLast && ArePnt2dEqual(p2Ar,p2dLast,tolULast,tolVLast)) {
	      tolU = Max(tolULast,tolU); tolV = Max(tolVLast,tolV);
	    }
	    Standard_Real nptCh = UMaxCh-UMinCh;
	    Standard_Boolean isNptLow = (nptCh < 10. && nptCh < Nbptlin/100.) ||
	      (!Domain->Has3d() && Standard_Integer(nptCh)+1 < Nbptlin);
	    if (!isNptLow && !IsSegment2dSmall(Brise,UMinAr,UMaxAr,tolU,tolV)) {
	      // treat both ends
	      Standard_Real UMinChP,UMinArP,UMaxArP;
	      UMinChP = IntegerPart(UMinCh); UMinArP = IntegerPart(UMinAr);
	                                     UMaxArP = IntegerPart(UMaxAr);
	      Standard_Integer irangAr1,irangAr2;
	      irangAr1 = Standard_Integer(UMinArP)+1; irangAr2 = Standard_Integer(UMaxArP)+1;
	      UMinChP = UMinCh - UMinChP; UMinArP = UMinAr - UMinArP;
	      //UMaxChP = UMaxCh - UMaxChP; UMaxArP = UMaxAr - UMaxArP;
	      const Standard_Real eps = 1e-10;
//	      Standard_Boolean isChExtr1 = irangCh1==1 && UMinChP<eps;
//	      Standard_Boolean isChExtr2 = irangCh2==Nbptlin;
	      Standard_Boolean isArExtr1 = irangAr1==1 && UMinArP<eps;
	      Standard_Boolean isArExtr2 = irangAr2==NbEchant;
	      // detect orientation
	      gp_Pnt2d p1Ch = GetPointOnPolygo(PLin,UMinCh);
	      Standard_Real d11 = p1Ch.SquareDistance(p1Ar);
	      Standard_Real d12 = p1Ch.SquareDistance(p2Ar);
	      Standard_Boolean sameOri = d11 < d12;
	      if (!sameOri) {
		Standard_Boolean itmp=isArExtr1; isArExtr1=isArExtr2; isArExtr2=itmp;
		Standard_Real dtmp=UMinAr; UMinAr=UMaxAr; UMaxAr=dtmp;
	      }
	      W1[0] = UMinCh; W1[1] = UMaxCh;
	      W2[0] = UMinAr; W2[1] = UMaxAr;
	      //refine[0] = ! (isChExtr1 || isArExtr1);
	      //refine[1] = ! (isChExtr2 || isArExtr2);
	      refine[0] = refine[1] = Standard_False;
	      useWL[0] = !isArExtr1;
	      useWL[1] = !isArExtr2;
	      nbpt = 2;
	    }
	    else {
	      // treat the middle point as an intersection point
	      W1[0] = 0.5*(UMinCh+UMaxCh);
	      W2[0] = 0.5*(UMinAr+UMaxAr);
	      refine[0] = Standard_True;
	    }
	  }

	  Standard_Boolean nbTreated = 0;
	  for (Standard_Integer ip=0; ip < nbpt; ip++) {
	    GetLinePoint2d (L, W1[ip]+1, !OnFirst, U,V);

	    if (!refine[ip] && useWL[ip]) {
	      Standard_Real aU1,aV1;
	      GetLinePoint2d (L, W1[ip]+1, OnFirst, aU1,aV1);
	      p2d.SetCoord(aU1,aV1);
	      Standard_Real paramProj;
	      if (!IntPatch_HInterTool::Project(arc,p2d,paramProj,p2d)) continue;
	      W = paramProj;
	    }
	    else {
	      Standard_Real par = IntegerPart(W2[ip]);
	      Standard_Integer Irang = Standard_Integer(par) + 1;
	      if (Irang == Brise.NbPoints()) {
		Irang--;
		par = 1.;
	      }
	      else {
		par =Abs(W2[ip]-par);
	      }
	      W = (1.-par)*Brise.Parameter(Irang) + par*Brise.Parameter(Irang+1);
	    }

	    Standard_Boolean refined = Standard_False;
	    if (refine[ip]) {
	      //------------------------------------------------------------------------
	      //-- On a trouve un point 2d approche Ua,Va  intersection de la ligne
	      //-- de cheminement et de la restriction. 
	      //--
	      //-- On injecte ce point ds les intersections Courbe-Surface
	      //-- 
	      IntPatch_CSFunction thefunc(OtherSurf,arc,Surf);
	      // MSV: extend UV bounds to not miss solution near the boundary
	      Standard_Real margCoef = 0.004;
	      IntPatch_CurvIntSurf IntCS(U,V,W,thefunc,edgeTol,margCoef);
	      if (IntCS.IsDone()) {
		if (!IntCS.IsEmpty()) {
		  ptsommet = IntCS.Point();
		  IntCS.ParameterOnSurface(U2,V2);
		  paramarc = IntCS.ParameterOnCurve();
		  refined = Standard_True;
		}
	      }
	    }
	    else {
	      U2 = U; V2 = V;
	      paramarc = W;
	      arc->D0(paramarc,p2d);
	      Surf->D0(p2d.X(),p2d.Y(),ptsommet);
	    }

	    if (!refine[ip] || refined) {
	      duplicate = Standard_False;
	      for (j=1; j<=locpt.Length();j++) {
		if (ptsommet.Distance(locpt(j)) <= edgeTol) {
		  if (possiblyClosed) {
		    locpt2(j).Coord(U,V);
		    if ((OSurfaceIsUClosed && Abs(U-U2) > tolOUClosed) ||
			(OSurfaceIsVClosed && Abs(V-V2) > tolOVClosed))
		      continue;
		  }
		  duplicate = Standard_True;
		  break;
		}
	      }

	      if (!duplicate) {
		Standard_Integer ParamApproxOnLine = Standard_Integer(W1[ip])+1;

		arc->D1(paramarc,p2d,d2d);
		U1 = p2d.X(); V1 = p2d.Y();
		if (typL == IntPatch_Walking && SurfaceIsPeriodic) {
		  if (OnFirst)
		    Recadre(TypeS1,TypeS2,wlin,ParamApproxOnLine,U1,V1,U2,V2);
		  else
		    Recadre(TypeS1,TypeS2,wlin,ParamApproxOnLine,U2,V2,U1,V1);
		}

		locpt.Append(ptsommet);
		locpt2.Append(gp_Pnt2d(U2,V2));

		found = FindParameter(L,OtherSurf,edgeTol,ptsommet,gp_Pnt2d(U2,V2),
				      paramline,tgline,ParamApproxOnLine,OnFirst);

		if (typL == IntPatch_Walking && found && possiblyClosed) {
		  // check in 2d
		  if (SurfaceIsUClosed || SurfaceIsVClosed) {
		    GetLinePoint2d (L, paramline, OnFirst, U,V);
		    if ((SurfaceIsUClosed && Abs(U-U1) > tolUClosed) ||
			(SurfaceIsVClosed && Abs(V-V1) > tolVClosed))
		      found = Standard_False;
		  }
		  if (found && (OSurfaceIsUClosed || OSurfaceIsVClosed)) {
		    GetLinePoint2d (L, paramline, !OnFirst, U,V);
		    if ((OSurfaceIsUClosed && Abs(U-U2) > tolOUClosed) ||
			(OSurfaceIsVClosed && Abs(V-V2) > tolOVClosed))
		      found = Standard_False;
		  }
		}
		if (!found) {
		  continue;
		}

		VtxOnArc = CoincideOnArc(ptsommet,arc,Surf,edgeTol,Domain,vtxarc);
		Standard_Real vtxTol;
		if (VtxOnArc) {
		  vtxTol = Tol3d(vtxarc,Domain);
		  if (edgeTol > vtxTol) vtxTol = edgeTol;
		}
		else vtxTol = edgeTol;

		//-- It is necessary to test that the point does not already exist
		//--   - It can be already a point on arc
		//--        BUT on a different arc
		// MSV 27.03.2002: find the nearest point; add check in 2d
		Standard_Integer ivtx = 0;
		Standard_Real dmin = RealLast();
		for (j=1; j<=Nbvtx; j++) {
		  const IntPatch_Point& Rptline = (typL == IntPatch_Walking
					     ? wlin->Vertex(j)
					     : rlin->Vertex(j));
		  Standard_Boolean APointOnRstStillExist =
		    ((OnFirst  && Rptline.IsOnDomS1() && Rptline.ArcOnS1() == arc) ||
		     (!OnFirst && Rptline.IsOnDomS2() && Rptline.ArcOnS2() == arc));
		  if(!APointOnRstStillExist) {
		    if (possiblyClosed) {
		      if (SurfaceIsUClosed || SurfaceIsVClosed) {
			if (OnFirst) Rptline.ParametersOnS1(U,V);
			else         Rptline.ParametersOnS2(U,V);
			if ((SurfaceIsUClosed && Abs(U-U1) > tolUClosed) ||
			    (SurfaceIsVClosed && Abs(V-V1) > tolVClosed))
			  continue;
		      }
		      if (OSurfaceIsUClosed || OSurfaceIsVClosed) {
			if (OnFirst) Rptline.ParametersOnS2(U,V);
			else         Rptline.ParametersOnS1(U,V);
			if ((OSurfaceIsUClosed && Abs(U-U2) > tolOUClosed) ||
			    (OSurfaceIsVClosed && Abs(V-V2) > tolOVClosed))
			  continue;
		      }
		    }
		    Standard_Real dist = ptsommet.Distance(Rptline.Value());
		    Standard_Real dt = Max(vtxTol, Rptline.Tolerance());
		    if (dist < dmin) {
		      if (dist <= dt) {
			ptline = Rptline;
			ivtx = j;
			if( surfacetype == GeomAbs_Cone ) {
			  ivtx = 0;
			}
		      }
		      else {
			// cancel previous solution because this point is better
			// but its tolerance is not large enough
			ivtx = 0;
		      }
		      dmin = dist;
		    } 
		  }
		}
		if (ivtx) {
		  if (ptline.Tolerance() > vtxTol) {
		    vtxTol = ptline.Tolerance();
		    if (!VtxOnArc) {
		      // now we should repeat attempt to coincide on a bound of arc
		      VtxOnArc = CoincideOnArc(ptsommet,arc,Surf,vtxTol,Domain,vtxarc);
		      if (VtxOnArc) {
			Standard_Real tol = Tol3d(vtxarc,Domain);
			if (tol > vtxTol) vtxTol = tol;
		      }
		    }
		  }
		}

		if (typL == IntPatch_Walking)
		  VerifyTgline(wlin,(Standard_Integer)paramline,edgeTol,tgline);

		Surf->D1(U1,V1,ptbid,d1u,d1v);
		tgrst.SetLinearForm(d2d.X(),d1u,d2d.Y(),d1v);

		normsurf = d1u.Crossed(d1v);
		if (normsurf.Magnitude() < gp::Resolution()) {
		  transline.SetValue(Standard_True,IntSurf_Undecided);
		  transarc.SetValue(Standard_True,IntSurf_Undecided);
		}
		else
		  IntSurf::MakeTransition(tgline,tgrst,normsurf,transline,transarc);

		if (typL == IntPatch_Walking && !refine[ip]) {
		  // for new vertex use coordinates from Line
		  if (OnFirst)
		    GetWLinePoint (wlin, paramline, U1,V1,U2,V2,ptsommet);
		  else
		    GetWLinePoint (wlin, paramline, U2,V2,U1,V1,ptsommet);
		}

		nbTreated++;
		if (!ivtx) {
		  Sommet.SetValue(ptsommet,vtxTol,Standard_False); // pour tangence
		  if (OnFirst)
		    Sommet.SetParameters(U1,V1,U2,V2);
		  else
		    Sommet.SetParameters(U2,V2,U1,V1);

		  if (VtxOnArc)
		    Sommet.SetVertex(OnFirst,vtxarc);

		  //---------------------------------------------------------
		  //-- lbr : On remplace le point d indice paramline sur la -
		  //-- ligne par le vertex .                                -
		  //---------------------------------------------------------
		  Sommet.SetParameter(paramline); // sur ligne d intersection
		  Sommet.SetArc(OnFirst,arc,paramarc,transline,transarc);

		  if (typL == IntPatch_Walking) {
		    wlin->AddVertex(Sommet);
		    Nbvtx++;
		  }
		  else {
		    rlin->AddVertex(Sommet);
		    Nbvtx++;
		  }
		}
		else {
		  // CAS DE FIGURE : en appelant s1 la surf sur laquelle on 
		  //   connait les pts sur restriction, et s2 celle sur laquelle
		  //   on les cherche. Le point trouve verifie necessairement
		  //   IsOnDomS1 = True.
		  //  Pas vtxS1, pas vtxS2 :
		  //   on recupere le point et on applique SetArcOnS2 et
		  //   eventuellement SetVertexOnS2. Si on a deja IsOnDomS2,
		  //   on considere que le point est deja traite, mais ne devrait
		  //   pas se produire.
		  //  vtxS1, pas vtxS2     :
		  //   si pas IsOnDomS2 : pour chaque occurrence, faire SetArcOnS2,
		  //   et eventuellement SetVertexOnS2.
		  //   si IsOnDomS2 : impossible, on doit avoir IsVtxOnS2.
		  //  vtxS1,vtxS2          :
		  //   on doit avoir VtxOnArc = True. On duplique chaque occurrence
		  //   "sur S1" du point en changeant ArcOnS2.
		  //  pas vtxS1, vtxS2     :
		  //   on doit avoir VtxOnArc = True. On duplique le point sur S1
		  //   en changeant ArcOnS2.
		  Standard_Boolean OnDifferentRst =
		    ((OnFirst  && ptline.IsOnDomS1() && ptline.ArcOnS1() != arc) ||
		     (!OnFirst && ptline.IsOnDomS2() && ptline.ArcOnS2() != arc));
		  ptline.SetTolerance(vtxTol);
		  if (   (!ptline.IsVertexOnS1() &&  OnFirst) 
		      || (!ptline.IsVertexOnS2() && !OnFirst) 
		      || (OnDifferentRst))  {
		    if (  (!ptline.IsOnDomS2() && !OnFirst)
			||(!ptline.IsOnDomS1() &&  OnFirst)
			||(OnDifferentRst)) {
		      ptline.SetArc(OnFirst,arc,paramarc,transline,transarc);
		      //ptline.SetParameter(paramline); //-- rajout lbr le 20 nov 97
		      if (VtxOnArc)
			ptline.SetVertex(OnFirst,vtxarc);
		      if (typL == IntPatch_Walking) {
			if(OnDifferentRst) { 
			  wlin->AddVertex(ptline); 
			  Nbvtx++;
			}
			else { 
			  wlin->Replace(ivtx,ptline);
			}
		      }
		      else {
			if(OnDifferentRst) { 
			  rlin->AddVertex(ptline);
			  Nbvtx++;
			}
			else {
			  rlin->Replace(ivtx,ptline);
			}
		      }
		    }
		    else if (  ( OnFirst && ptline.IsVertexOnS2())
			     ||(!OnFirst && ptline.IsVertexOnS1())) {
		      Sommet = ptline;
		      Sommet.SetArc(OnFirst,arc,paramarc,transline,transarc);
		      if (VtxOnArc)
			Sommet.SetVertex(OnFirst,vtxarc);
		      if (typL == IntPatch_Walking) {
			wlin->AddVertex(Sommet);
			Nbvtx++;
		      }
		      else {
			rlin->AddVertex(Sommet);
			Nbvtx++;
		      }
		    }
		    else {
		      //-- cout << "pb dans RstInt  Type 1 " << endl;
		    }
		  }
		  else {
		    Handle(Adaptor3d_HVertex) vtxref = (OnFirst)? (ptline.VertexOnS1()) : (ptline.VertexOnS2()) ;
		    if (  ( OnFirst && !ptline.IsOnDomS2())
			||(!OnFirst && !ptline.IsOnDomS1())) {
		      ptline.SetArc(OnFirst,arc,paramarc,transline,transarc);
		      if (VtxOnArc)
			ptline.SetVertex(OnFirst,vtxarc);
		      if (typL == IntPatch_Walking) {
			wlin->Replace(ivtx,ptline);
		      }
		      else {
			rlin->Replace(ivtx,ptline);
		      }

		      for (k=1; k<=Nbvtx; k++) if (k != ivtx) {
			if (typL == IntPatch_Walking) {
			  ptline = wlin->Vertex(k);
			}
			else {
			  ptline = rlin->Vertex(k);
			}
			if (   ( OnFirst && ptline.IsVertexOnS1()) 
			    || (!OnFirst && ptline.IsVertexOnS2())) {
			  if (Domain->Identical(vtxref, (OnFirst)? (ptline.VertexOnS1()) : (ptline.VertexOnS2()))) { 
			    if (ptline.Tolerance() < vtxTol) ptline.SetTolerance(vtxTol);
			    ptline.SetArc(OnFirst,arc,paramarc,transline,transarc);
			    if (VtxOnArc)
			      ptline.SetVertex(OnFirst,vtxarc);
			    if (typL == IntPatch_Walking) {
			      wlin->Replace(k,ptline);
			    }
			    else {
			      rlin->Replace(k,ptline);
			    }
			  }
			}
		      }
		    }
		    else if(   ( OnFirst && ptline.IsVertexOnS2()) 
			    || (!OnFirst && ptline.IsVertexOnS1())) {
		      //                on doit avoir vtxons2 = vtxarc... pas de verif...
		      Sommet = ptline;
		      Sommet.SetArc(OnFirst,arc,paramarc,transline,transarc);
		      if (typL == IntPatch_Walking) {
			wlin->AddVertex(Sommet);
			Nbvtx++;
		      }
		      else {
			rlin->AddVertex(Sommet);
			Nbvtx++;
		      }
		      for (k=1; k<=Nbvtx; k++) if (k != ivtx) {
			if (typL == IntPatch_Walking) {
			  ptline = wlin->Vertex(k);
			}
			else {
			  ptline = rlin->Vertex(k);
			}
			if (  ( OnFirst && ptline.IsVertexOnS1())
			    ||(!OnFirst && ptline.IsVertexOnS2())) {
			  if (Domain->Identical(vtxref,(OnFirst)? (ptline.VertexOnS1()) : (ptline.VertexOnS2()))) { 
			    if (ptline.Tolerance() < vtxTol) ptline.SetTolerance(vtxTol);
			    Sommet = ptline;
			    Sommet.SetArc(OnFirst,arc,paramarc,transline,transarc);
			    if (typL == IntPatch_Walking) {
			      wlin->Replace(k,ptline);
			      wlin->AddVertex(Sommet);
			      Nbvtx++;			      
			    }
			    else {
			      rlin->Replace(k,ptline);
			      rlin->AddVertex(Sommet);
			      Nbvtx++;			      
			    }
			  }
			}
		      }

		    }
		    else {
		      //-- cout << "pb dans RstInt  Type 2 " << endl;
		    }
		  }
		}
	      }
	    }
	  }
	  if (nbTreated == 2 && typL == IntPatch_Walking) {
	    // We processed a tangent zone, and both ends have been treated.
	    // So mark WLine as having arc
	    if(OnFirst) wlin->SetArcOnS1(arc);
	    else        wlin->SetArcOnS2(arc);
	  }
	}
	
	IndiceOffsetPeriodic++;
      }
      while(SurfaceIsPeriodic && IndiceOffsetPeriodic<=2);
      
      IndiceOffsetBiPeriodic++;
    }
    while(SurfaceIsBiPeriodic && IndiceOffsetBiPeriodic<=2);
    Domain->Next(); 
  }
  
  //--------------------------------------------------------------------------------
  //-- On reprend la ligne et on recale les parametres des vertex.
  //-- 
  if (typL == IntPatch_Walking) {
    Standard_Real pu1,pv1,pu2,pv2;
    pu1=pv1=pu2=pv2=0.0;
    switch(TypeS1) { 
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:
      pu1=M_PI+M_PI;
      break;
    case GeomAbs_Torus:
      pu1=pv1=M_PI+M_PI;
      break;
    default:
      {
	if(   Surf1->IsUPeriodic())  {
	  pu1=Surf1->UPeriod();
	}
	else if(Surf1->IsUClosed()) { 
	  pu1=Surf1->LastUParameter() - Surf1->FirstUParameter();
	  //cout<<" UClosed1 "<<pu1<<endl;
	}
	if(   Surf1->IsVPeriodic()) {
	  pv1=Surf1->VPeriod();
	}
	else if(Surf1->IsVClosed()) { 
	  pv1=Surf1->LastVParameter() - Surf1->FirstVParameter();
	  //cout<<" VClosed1 "<<pv1<<endl;
	}

	break;
      }      
    }
    
    switch(TypeS2) { 
    case GeomAbs_Cylinder:
    case GeomAbs_Cone:
    case GeomAbs_Sphere:

      pu2=M_PI+M_PI;
      break;
    case GeomAbs_Torus:
      pu2=pv2=M_PI+M_PI;
      break;
    default:
      { 
	if(   Surf2->IsUPeriodic()) {  
	  pu2=Surf2->UPeriod(); 
	}
	else if(Surf2->IsUClosed()) { 
	  pu2=Surf2->LastUParameter() - Surf2->FirstUParameter();
	  //cout<<" UClosed2 "<<pu2<<endl;
	}

	if(   Surf2->IsVPeriodic())  {
	  pv2=Surf2->VPeriod();
	}
	else if(Surf2->IsVClosed()) { 
	  pv2=Surf2->LastVParameter() - Surf2->FirstVParameter();
	  //cout<<" VClosed2 "<<pv2<<endl;
	}

	break;
      }
    }

/*
    if(pu1==0) { 
      pu1=Surf1->LastUParameter() - Surf1->FirstUParameter();
      pu1+=pu1;
    }
    if(pu2==0) { 
      pu2=Surf2->LastUParameter() - Surf2->FirstUParameter();
      pu2+=pu2;
    }
    if(pv1==0) { 
      pv1=Surf1->LastVParameter() - Surf1->FirstVParameter();
      pv1+=pv1;
    }
    if(pv2==0) { 
      pv2=Surf2->LastVParameter() - Surf2->FirstVParameter();
      pv2+=pv2;
    } 
*/

    wlin->SetPeriod(pu1,pv1,pu2,pv2);
    wlin->ComputeVertexParameters(Tol);
  }
  else {
#ifdef DEB
    //if(rlin->NbVertex()==0) { 
    //  cout<<" \n *** IntPatch RstInt.gxx  : nbvtx = 0 sur rline *** \n"<<endl;
    //}
#endif
    rlin->ComputeVertexParameters(Tol);
  }
}
