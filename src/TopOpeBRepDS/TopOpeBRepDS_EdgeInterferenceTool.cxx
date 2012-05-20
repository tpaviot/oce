// Created on: 1994-11-08
// Created by: Jean Yves LEBEY
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


#include <TopOpeBRepDS_EdgeInterferenceTool.ixx>

#include <TopOpeBRepDS_CurvePointInterference.hxx>
#include <TopOpeBRepDS_EdgeVertexInterference.hxx>
#include <BRepLProp_CLProps.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Iterator.hxx>
#include <Precision.hxx>
#include <TopoDS.hxx>
#include <TopOpeBRepTool_ShapeTool.hxx>
#include <Standard_ProgramError.hxx>

#ifdef DEB
Standard_EXPORT Standard_Boolean TopOpeBRepDS_GettracePEI();
#endif

//=======================================================================
//function : TopOpeBRepDS_EdgeInterferenceTool
//purpose  : 
//=======================================================================

 TopOpeBRepDS_EdgeInterferenceTool::TopOpeBRepDS_EdgeInterferenceTool()
{
}

static Standard_Real Parameter(const Handle(TopOpeBRepDS_Interference)& I)
{ 
  Standard_Real p = 0; 
  if      ( I->IsKind(STANDARD_TYPE(TopOpeBRepDS_EdgeVertexInterference)) )
    p = Handle(TopOpeBRepDS_EdgeVertexInterference)::DownCast(I)->Parameter();
  else if ( I->IsKind(STANDARD_TYPE(TopOpeBRepDS_CurvePointInterference)) )
    p = Handle(TopOpeBRepDS_CurvePointInterference)::DownCast(I)->Parameter();
  else {
#ifdef DEB
    cout<<"EdgeInterference : mauvais type d'interference"<<endl;
#endif
    Standard_ProgramError::Raise("TopOpeBRepDS_EdgeInterferenceTool1");
  }
  return p;
}
  

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

void TopOpeBRepDS_EdgeInterferenceTool::Init
(const TopoDS_Shape& E, const Handle(TopOpeBRepDS_Interference)& I)
{
  myEdgeOrientation = E.Orientation();
  myEdgeOriented    = I->Support();
  
  // NYI 971219 : on ne tient pas compte de l'orientation de E = arete-mere de l'interference I
  if (myEdgeOrientation == TopAbs_INTERNAL || 
      myEdgeOrientation == TopAbs_EXTERNAL) {
    return;
  }
  
  // la premiere arete orientee est gardee dans myEdgeOriented pour MAJ de
  // l'arete croisee dans l'interference resultat.

  // par = parametre sur l'arete croisee
  Standard_Real par = ::Parameter(I);
  gp_Dir T,N; Standard_Real C;
  TopOpeBRepTool_ShapeTool::EdgeData(E,par,T,N,C);
  myTool.Reset(T,N,C);
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void TopOpeBRepDS_EdgeInterferenceTool::Add
(const TopoDS_Shape& E,
 const TopoDS_Shape& V,
 const Handle(TopOpeBRepDS_Interference)& I)
{
  TopAbs_Orientation Eori = E.Orientation();
  if (Eori == TopAbs_INTERNAL || 
      Eori == TopAbs_EXTERNAL) {
    return;
  }

  // premiere interference sur arete orientee : Init
  if (myEdgeOrientation == TopAbs_INTERNAL || 
      myEdgeOrientation == TopAbs_EXTERNAL) {
    Init(E,I);
    return;
  }

  // V est un sommet de E ?
  Standard_Boolean VofE = Standard_False;
  TopoDS_Iterator it(E,Standard_False);
  for ( ; it.More(); it.Next() ) {
    const TopoDS_Shape& S = it.Value();
    if ( S.IsSame(V) ) {
      VofE = Standard_True; 
      break;
    }
  }
 
#ifdef DEB
  if (TopOpeBRepDS_GettracePEI() && !VofE) {
    cout<<"===================== VofE = False"<<endl;
  }
#endif 

  // V est un sommet de E
  const TopoDS_Vertex& VV = TopoDS::Vertex(V);
  const TopoDS_Edge& EE = TopoDS::Edge(E);
  Standard_Real par = BRep_Tool::Parameter(VV,EE);
  
  gp_Dir T,N; Standard_Real C;
  Standard_Real tol = TopOpeBRepTool_ShapeTool::EdgeData(E,par,T,N,C);
  TopAbs_Orientation oriloc = I->Transition().Orientation(TopAbs_IN);
  TopAbs_Orientation oritan = it.Value().Orientation();
  myTool.Compare(tol,T,N,C,oriloc,oritan);
}

//=======================================================================
//function : Add
//purpose  : 
//=======================================================================

void TopOpeBRepDS_EdgeInterferenceTool::Add
(const TopoDS_Shape& E,
// const TopOpeBRepDS_Point& P,
 const TopOpeBRepDS_Point& ,
 const Handle(TopOpeBRepDS_Interference)& I)
{
  TopAbs_Orientation Eori = E.Orientation();
  if (Eori == TopAbs_INTERNAL || 
      Eori == TopAbs_EXTERNAL) {
    return;
  }

  // premiere interference sur arete orientee : Init
  if (myEdgeOrientation == TopAbs_INTERNAL || 
      myEdgeOrientation == TopAbs_EXTERNAL) {
    Init(E,I);
    return;
  }

  Standard_Real par = ::Parameter(I);
  
  gp_Dir T,N; Standard_Real C;
  Standard_Real tol = TopOpeBRepTool_ShapeTool::EdgeData(E,par,T,N,C);
  TopAbs_Orientation oriloc = I->Transition().Orientation(TopAbs_IN);
  TopAbs_Orientation oritan = TopAbs_INTERNAL;
  myTool.Compare(tol,T,N,C,oriloc,oritan);
}

//=======================================================================
//function : Transition
//purpose  : 
//=======================================================================

void TopOpeBRepDS_EdgeInterferenceTool::Transition
(const Handle(TopOpeBRepDS_Interference)& I) const 
{
  TopOpeBRepDS_Transition& T = I->ChangeTransition();

  if (myEdgeOrientation == TopAbs_INTERNAL) {
    T.Set(TopAbs_IN,TopAbs_IN);
  }
  else if (myEdgeOrientation == TopAbs_EXTERNAL) {
    T.Set(TopAbs_OUT,TopAbs_OUT);
  }
  else {
    I->Support(myEdgeOriented);
    T.Set(myTool.StateBefore(),myTool.StateAfter());
  }
}
