// Created on: 1998-10-29
// Created by: Jean Yves LEBEY
// Copyright (c) 1998-1999 Matra Datavision
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


#include <TopOpeBRep_Hctxee2d.ixx>
#include <TopOpeBRep_define.hxx>
#include <TopOpeBRepTool_CurveTool.hxx>
#include <TopOpeBRepTool_ShapeTool.hxx>
#include <TopOpeBRepTool_2d.hxx>
#include <TopOpeBRepTool_GEOMETRY.hxx>
#include <TopOpeBRepTool_PROJECT.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>

#ifdef DEB
#include <GeomTools_SurfaceSet.hxx>
#include <GeomTools_CurveSet.hxx>
#include <GeomTools_Curve2dSet.hxx>
Standard_EXPORT Standard_Boolean TopOpeBRep_GettracePROEDG();
#endif

//=======================================================================
//function : TopOpeBRep_Hctxee2d
//purpose  : 
//=======================================================================
TopOpeBRep_Hctxee2d::TopOpeBRep_Hctxee2d() 
{
}

//=======================================================================
//function : SetEdges
//purpose  : 
//=======================================================================
void TopOpeBRep_Hctxee2d::SetEdges(const TopoDS_Edge& E1,const TopoDS_Edge& E2,
				   const BRepAdaptor_Surface& BAS1,
				   const BRepAdaptor_Surface& BAS2)
{
  const TopoDS_Face& F1 = BAS1.Face();
  GeomAbs_SurfaceType ST1 = BAS1.GetType();
  const TopoDS_Face& F2 = BAS2.Face();
#ifdef DEb
  GeomAbs_SurfaceType ST2 = BAS2.GetType();
#endif
  
  myEdge1 = TopoDS::Edge(E1);
  myEdge2 = TopoDS::Edge(E2);
  
  Standard_Real first,last,tole,tolpc;
  gp_Pnt2d pfirst,plast;

  Handle(Geom2d_Curve) PC1;
  PC1 = FC2D_CurveOnSurface(myEdge1,F1,first,last,tolpc);
  if (PC1.IsNull()) Standard_Failure::Raise("TopOpeBRep_Hctxee2d::SetEdges : no 2d curve");
  myCurve1.Load(PC1);
  BRep_Tool::UVPoints(myEdge1,F1,pfirst,plast);
  tole = BRep_Tool::Tolerance(myEdge1);
  myDomain1.SetValues(pfirst,first,tole,plast,last,tole);
  
#ifdef DEB
  Standard_Boolean trc = Standard_False;
  if (trc) {
    cout<<"ed1 on fa1 : {pfirst=("<<pfirst.X()<<" "<<pfirst.Y()<<"),first="<<first<<"\n";
    cout<<"              plast =("<<plast.X()<<" "<<plast.Y()<<"),last="<<last<<"}"<<endl;}
#endif  
  
  Standard_Boolean memesfaces = F1.IsSame(F2);
  Standard_Boolean memesupport = Standard_False;
  TopLoc_Location L1,L2;
  const Handle(Geom_Surface) S1 = BRep_Tool::Surface(F1,L1);
  const Handle(Geom_Surface) S2 = BRep_Tool::Surface(F2,L2);
  if (S1 == S2 && L1 == L2) memesupport=Standard_True;
  
  if ( ST1 == GeomAbs_Plane || memesfaces || memesupport) {    
    Handle(Geom2d_Curve) PC2 = FC2D_CurveOnSurface(myEdge2,F1,first,last,tolpc);
    myCurve2.Load(PC2);
    BRep_Tool::UVPoints(myEdge2,F1,pfirst,plast);
    tole = BRep_Tool::Tolerance(myEdge2);
    myDomain2.SetValues(pfirst,first,tole,plast,last,tole);
    
#ifdef DEB
    if (trc) {
      cout<<"ed2 on fa1 : {pfirst=("<<pfirst.X()<<" "<<pfirst.Y()<<"),first="<<first<<"\n";
      cout<<"              plast =("<<plast.X()<<" "<<plast.Y()<<"),last="<<last<<"}"<<endl;}
#endif
    
  }
  else {

    Handle(Geom2d_Curve) PC2on1; Handle(Geom_Curve) NC;
    Standard_Boolean dgE2 = BRep_Tool::Degenerated(myEdge2);
    if (dgE2) { //xpu210998 : cto900Q3
      TopExp_Explorer exv(myEdge2,TopAbs_VERTEX);
      const TopoDS_Vertex& v2 = TopoDS::Vertex(exv.Current());
      gp_Pnt pt2 = BRep_Tool::Pnt(v2);
      gp_Pnt2d uv2; Standard_Real d; Standard_Boolean ok = FUN_tool_projPonF(pt2,F1,uv2,d);
      if (!ok) return;//nyiRaise
      Handle(Geom_Surface) S1 = BRep_Tool::Surface(F1);
      Standard_Boolean apex = FUN_tool_onapex(uv2,S1);
      if (apex) {
	TopoDS_Vertex vf,vl; TopExp::Vertices(myEdge1,vf,vl);
	gp_Pnt ptf = BRep_Tool::Pnt(vf); Standard_Real df = pt2.Distance(ptf); 
	gp_Pnt ptl = BRep_Tool::Pnt(vl);
#ifdef DEB
        Standard_Real dl =
#endif
                 pt2.Distance(ptl); 
	Standard_Real tolf = BRep_Tool::Tolerance(vf);
#ifdef DEB
        Standard_Real toll =
#endif
                   BRep_Tool::Tolerance(vl);
	Standard_Boolean onf = (df < tolf);
	TopoDS_Vertex v1 = onf ? vf : vl;
	TopTools_IndexedDataMapOfShapeListOfShape mapVE; TopExp::MapShapesAndAncestors(F1,TopAbs_VERTEX,TopAbs_EDGE,mapVE);
	const TopTools_ListOfShape& Edsanc = mapVE.FindFromKey(v1);
	TopTools_ListIteratorOfListOfShape it(Edsanc);
	for (; it.More(); it.Next()){
	  const TopoDS_Edge& ee = TopoDS::Edge(it.Value());
	  Standard_Boolean dgee = BRep_Tool::Degenerated(ee);
	  if (!dgee) continue;
//	  Standard_Real f,l;
          PC2on1 = BRep_Tool::CurveOnSurface(ee,F1,first,last);	  
	}
      }
      else {} // NYIxpu210998
    } //dgE2
    else {
      // project curve of edge 2 on surface of face 1
      TopLoc_Location loc ;
      Handle(Geom_Curve) C = BRep_Tool::Curve(myEdge2,loc,first,last); 
      NC = Handle(Geom_Curve)::DownCast(C->Transformed(loc.Transformation()));
      Standard_Real tolreached2d; PC2on1 = TopOpeBRepTool_CurveTool::MakePCurveOnFace(F1,NC,tolreached2d);
    }
    
    if (!PC2on1.IsNull()) {
      myCurve2.Load(PC2on1);
      tole = BRep_Tool::Tolerance(myEdge2);
      PC2on1->D0(first,pfirst);
      PC2on1->D0(last,plast);
      myDomain2.SetValues(pfirst,first,tole,plast,last,tole);
#ifdef DEB
      if ( TopOpeBRep_GettracePROEDG() ) {
	cout<<"------------ projection de curve"<<endl;
	cout<<"--- Curve : "<<endl;GeomTools_CurveSet::PrintCurve(NC,cout);
	cout<<"--- nouvelle PCurve : "<<endl;GeomTools_Curve2dSet::PrintCurve2d(PC2on1,cout);
	Handle(Geom_Surface) S1 = BRep_Tool::Surface(F1);
	cout<<"--- sur surface : "<<endl;GeomTools_SurfaceSet::PrintSurface(S1,cout);
	cout<<endl;
      }
#endif
    }
  }
  
} // SetEdges

//=======================================================================
//function : Edge
//purpose  : 
//=======================================================================
const TopoDS_Shape& TopOpeBRep_Hctxee2d::Edge(const Standard_Integer Index) const 
{
  if      ( Index == 1 ) return myEdge1;
  else if ( Index == 2 ) return myEdge2;
  else Standard_Failure::Raise("TopOpeBRep_Hctxee2d::Edge");
  
  return myEdge1;
}

//=======================================================================
//function : Curve
//purpose  : 
//=======================================================================
const Geom2dAdaptor_Curve& TopOpeBRep_Hctxee2d::Curve(const Standard_Integer Index) const 
{
  if      ( Index == 1 ) return myCurve1;
  else if ( Index == 2 ) return myCurve2;
  else Standard_Failure::Raise("TopOpeBRep_Hctxee2d::Curve");
  
  return myCurve1;
}

//=======================================================================
//function : Domain
//purpose  : 
//=======================================================================
const IntRes2d_Domain& TopOpeBRep_Hctxee2d::Domain(const Standard_Integer Index) const 
{
  if      ( Index == 1 ) return myDomain1;
  else if ( Index == 2 ) return myDomain2;
  else Standard_Failure::Raise("TopOpeBRep_Hctxee2d::Domain");
  
  return myDomain1;
}
