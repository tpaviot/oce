// Created on: 1993-06-17
// Created by: Jean Yves LEBEY
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


#include <TopOpeBRepBuild_PaveSet.ixx>

#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp_Explorer.hxx>
#include <Precision.hxx>
#include <Geom_Curve.hxx>
#include <BRep_Tool.hxx>
#include <TCollection_AsciiString.hxx>

#include <TopExp.hxx>
#include <gp_Pnt.hxx>

#ifdef DEB
Standard_IMPORT Standard_Boolean TopOpeBRepTool_GettraceVC();
#include <TopOpeBRepBuild_Builder.hxx>
#include <gp_Pnt.hxx>
#endif

//=======================================================================
//function : TopOpeBRepBuild_PaveSet
//purpose  : 
//=======================================================================

TopOpeBRepBuild_PaveSet::TopOpeBRepBuild_PaveSet(const TopoDS_Shape& E) :
   myEdge(TopoDS::Edge(E)),
   myHasEqualParameters(Standard_False),
   myClosed(Standard_False),
   myPrepareDone(Standard_False),
   myRemovePV(Standard_True)
{
}

//=======================================================================
//function : RemovePV
//purpose  : 
//=======================================================================
void  TopOpeBRepBuild_PaveSet::RemovePV(const Standard_Boolean B)
{
  myRemovePV = B;
}

//=======================================================================
//function : Append
//purpose  : 
//=======================================================================

void  TopOpeBRepBuild_PaveSet::Append
(const Handle(TopOpeBRepBuild_Pave)& PV)
{
  myVertices.Append(PV);
  myPrepareDone = Standard_False;
}


#include <TColStd_HArray1OfBoolean.hxx>
#include <TColStd_Array1OfBoolean.hxx>

//=======================================================================
//function : SortPave
//purpose  : 
//=======================================================================

void TopOpeBRepBuild_PaveSet::SortPave(const TopOpeBRepBuild_ListOfPave& List, 
				       TopOpeBRepBuild_ListOfPave& SortedList)
{
  // NYI : sort a list o Items, giving a sorting function is impossible
  // NYI : --> foobar method complexity n2.
  
  Standard_Integer iPV=0,nPV = List.Extent();
  Handle(TColStd_HArray1OfBoolean) HT = 
    new TColStd_HArray1OfBoolean(0,nPV,Standard_False);
  TColStd_Array1OfBoolean& T = HT->ChangeArray1();
  
  Handle(TopOpeBRepBuild_Pave) PV1;
  for (Standard_Integer i = 1; i <= nPV; i++) { 
    Standard_Real parmin = RealLast();
    TopOpeBRepBuild_ListIteratorOfListOfPave it(List);
    for (Standard_Integer itest = 1; it.More(); it.Next(),itest++) {
      if ( ! T(itest) ) {
	const Handle(TopOpeBRepBuild_Pave)& PV2 = it.Value();
	Standard_Real par = PV2->Parameter();
	if (par < parmin) {
	  parmin = par;
	  PV1 = PV2;
	  iPV = itest;
	}
      }
    }
    SortedList.Append(PV1);
    T(iPV) = Standard_True;
  }

  // tete = FORWARD
  // modifier TopOpeBRepBuild_DataStructure::SortOnParameter
  Standard_Boolean found = Standard_False;
  TopOpeBRepBuild_ListIteratorOfListOfPave it(SortedList);
  TopOpeBRepBuild_ListOfPave L1,L2;

  for (; it.More(); it.Next() ) {
    const Handle(TopOpeBRepBuild_Pave)& PV = it.Value();
    if ( ! found) {
      TopAbs_Orientation o = PV->Vertex().Orientation();
      if (o == TopAbs_FORWARD) {
	found = Standard_True;
	L1.Append(PV);
      }
      else L2.Append(PV);
    }
    else L1.Append(PV);
  }

  SortedList.Clear();
  SortedList.Append(L1);
  SortedList.Append(L2);

}   

static Standard_Boolean FUN_islook(const TopoDS_Edge& e)
{
  TopoDS_Vertex v1,v2;
  TopExp::Vertices(e,v1,v2);
  gp_Pnt p1 = BRep_Tool::Pnt(v1);
  gp_Pnt p2 = BRep_Tool::Pnt(v2);
  Standard_Real dp1p2 = p1.Distance(p2);
  Standard_Boolean islook = (Abs(dp1p2) > 1.e-8) ? Standard_True : Standard_False;
  return islook;
}

//=======================================================================
//function : Prepare
//purpose  : 
//=======================================================================

void  TopOpeBRepBuild_PaveSet::Prepare()
{   
  // add the edge vertices to the list of interference
  // if an edge vertex VE is already in the list as interference VI : 
  //  - do not add VE in the list,
  //  - if VI is INTERNAL, set VI orientation to VE orientation.
  //  - remove VI from the list if : 
  //      VI is EXTERNAL or VE and VI have opposite orientations.
  //      
  if (myPrepareDone) {
    return;
  }

#ifdef DEB
  Standard_Boolean trc = Standard_False;
  trc = trc || TopOpeBRepTool_GettraceVC();
  Standard_Integer iv=0;//,nv=myVertices.Extent();
  if (trc) {
    TopOpeBRepBuild_ListIteratorOfListOfPave itd(myVertices);
    cout<<endl;
    for(;itd.More();itd.Next() ) {
      const Handle(TopOpeBRepBuild_Pave)& PV = itd.Value(); 
      TopoDS_Vertex& VI = TopoDS::Vertex(PV->ChangeVertex());
      Standard_Boolean hasVSD = PV->HasSameDomain();
      TopoDS_Vertex VSD; if (hasVSD) VSD = TopoDS::Vertex(PV->SameDomain());
      TopAbs_Orientation VIori = VI.Orientation(); 
      Standard_Real p = PV->Parameter();
      cout<<"pvs : v "<<++iv<<" par "<<p<<" ";TopAbs::Print(VIori,cout);cout<<endl;
    }
  }
#endif

  Standard_Boolean isEd = BRep_Tool::Degenerated(myEdge);
  Standard_Integer EdgeVertexCount = 0;


  if (myRemovePV) { // jyl + 980217
    TopExp_Explorer EVexp(myEdge,TopAbs_VERTEX);
    for (; EVexp.More(); EVexp.Next() ) {
      
      // VE = edge vertex
      const TopoDS_Vertex& VE = TopoDS::Vertex(EVexp.Current());
      TopAbs_Orientation VEori = VE.Orientation(); 
      Standard_Boolean VEbound=(VEori==TopAbs_FORWARD)||(VEori==TopAbs_REVERSED);
      
      Standard_Integer EdgeVertexIndex = 0;
      Standard_Boolean addVE = Standard_True;

      Standard_Boolean add = Standard_False;//ofv
      
      TopOpeBRepBuild_ListIteratorOfListOfPave it(myVertices);
      for(;it.More();it.Next() ) {
	EdgeVertexIndex++; // skip edge vertices inserted at the head of the list
	if (EdgeVertexIndex <= EdgeVertexCount) continue;
	
	// PV = Parametrized vertex, VI = interference vertex
	const Handle(TopOpeBRepBuild_Pave)& PV = it.Value(); 
	TopoDS_Vertex& VI = TopoDS::Vertex(PV->ChangeVertex());
	Standard_Boolean hasVSD = PV->HasSameDomain();
	TopoDS_Vertex VSD; if (hasVSD) VSD = TopoDS::Vertex(PV->SameDomain());
	
	TopAbs_Orientation VIori = VI.Orientation(); 	
	Standard_Boolean visameve = (VI.IsSame(VE));
	Standard_Boolean vsdsameve = Standard_False;
	if (hasVSD) vsdsameve = (VSD.IsSame(VE));
	Standard_Boolean samevertexprocessing = (visameve || vsdsameve) && !isEd; 
	
	if (samevertexprocessing) {
	  //	if (VEbound) {  // xpu: 29-05-97
	  if (VEbound || vsdsameve) {
	    switch (VIori ) {
	      
	    case TopAbs_EXTERNAL : 
	      myVertices.Remove(it); 
	      break;
	      
	    case TopAbs_INTERNAL :
	      VI.Orientation(VEori); 
	      break;
	      
	    case TopAbs_FORWARD : case TopAbs_REVERSED :
	      //ofv:
	      //if (VIori != VEori) myVertices.Remove(it);
	      if (VIori != VEori)//ofv
		{ myVertices.Remove(it);//ofv
		  Standard_Boolean islook = FUN_islook(myEdge);
		  if((VEbound && (vsdsameve ||visameve)) && islook) add = Standard_True;//ofv
		}
	      break;
	    }
	  }
	  //ofv:
	  //addVE = Standard_False;
	  addVE = (!add) ? Standard_False : Standard_True;
	  break;
	}
      }
      // if VE not found in the list, add it
      if ( addVE ) {
	Standard_Real parVE = BRep_Tool::Parameter(VE,myEdge);
	Handle(TopOpeBRepBuild_Pave) newPV = 
	  new TopOpeBRepBuild_Pave(VE,parVE,Standard_True);
	myVertices.Prepend(newPV);
	
	EdgeVertexCount++;
	
      }
    }
  } // myRemovePV

  Standard_Integer ll = myVertices.Extent();
  
  // if no more interferences vertices, clear the list
  if (ll == EdgeVertexCount)  {
    myVertices.Clear();
  }
  else if ( ll >= 2 ) {
    // sort the parametrized vertices on Parameter() value.
    TopOpeBRepBuild_ListOfPave List;
    List = myVertices;
    myVertices.Clear();
    SortPave(List,myVertices);
  }
  
#ifdef DEB
  if ( TopOpeBRepTool_GettraceVC() ) {
    myVerticesIt.Initialize(myVertices);
    if ( MoreLoop() ) cout<<"--- PaveSet : Prepare"<<endl;
    for (; MoreLoop(); NextLoop() ) {
      const Handle(TopOpeBRepBuild_Pave)& PV = 
	*((Handle(TopOpeBRepBuild_Pave)*)&(Loop()));
      const TopoDS_Vertex& v = TopoDS::Vertex(PV->Vertex());
      Standard_Real p = PV->Parameter();
      Standard_Boolean b = PV->IsShape();
      TopOpeBRepBuild_Builder::GdumpORIPARPNT(v.Orientation(),p,BRep_Tool::Pnt(v));
      if (b) cout<<" is bound"; else cout<<" is not bound";
      cout<<endl;
    }
  }
#endif

  myPrepareDone = Standard_True;
  return;
}


//=======================================================================
//function : InitLoop
//purpose  : 
//=======================================================================

void  TopOpeBRepBuild_PaveSet::InitLoop()
{   
  if ( ! myPrepareDone ) Prepare();
  myVerticesIt.Initialize(myVertices);
}


//=======================================================================
//function : MoreLoop
//purpose  : 
//=======================================================================

Standard_Boolean  TopOpeBRepBuild_PaveSet::MoreLoop()const 
{
  Standard_Boolean b = myVerticesIt.More();
  return b;
}


//=======================================================================
//function : NextLoop
//purpose  : 
//=======================================================================

void  TopOpeBRepBuild_PaveSet::NextLoop()
{
  myVerticesIt.Next();
}


//=======================================================================
//function : Loop
//purpose  : 
//=======================================================================

const Handle(TopOpeBRepBuild_Loop)& TopOpeBRepBuild_PaveSet::Loop()const 
{
  const Handle(TopOpeBRepBuild_Loop)& L = myVerticesIt.Value();
  return L;
}


//=======================================================================
//function : Edge
//purpose  : 
//=======================================================================

const TopoDS_Edge& TopOpeBRepBuild_PaveSet::Edge()const 
{
  return myEdge;
}


//=======================================================================
//function : HasEqualParameters
//purpose  : 
//=======================================================================

Standard_Boolean  TopOpeBRepBuild_PaveSet::HasEqualParameters() 
{
  myHasEqualParameters = Standard_False;
  TopOpeBRepBuild_ListIteratorOfListOfPave it1,it2;
  Standard_Real p1,p2;

  for (it1.Initialize(myVertices); 
       (! myHasEqualParameters ) && it1.More();
       it1.Next()) {
    const TopoDS_Shape& v1 = it1.Value()->Vertex();
    p1 = it1.Value()->Parameter();

    for (it2.Initialize(myVertices); 
	 (! myHasEqualParameters ) && it2.More(); 
	 it2.Next()) {
      const TopoDS_Shape& v2 = it2.Value()->Vertex();
      if ( v2.IsEqual(v1) ) continue;

      p2 = it2.Value()->Parameter();
      Standard_Real d = Abs(p1-p2);
#ifdef DEB
      if (TopOpeBRepTool_GettraceVC()) {
	cout<<"VertexSet : p1,p2  d "<<p1<<","<<p2<<"  "<<d<<endl;
      }
#endif
      if (d < Precision::PConfusion()) { 
	myHasEqualParameters = Standard_True;
	myEqualParameters = p1;
      }
    }
  }

  if ( !myHasEqualParameters ) {
    Standard_Boolean rd; Standard_Real f=0;
    {
      TopLoc_Location loc; Standard_Real ff,ll;
      Handle(Geom_Curve) CmyEdge = BRep_Tool::Curve(myEdge,loc,ff,ll);
      if ( CmyEdge.IsNull() ) rd = Standard_False;
      else { f = ff; rd = Standard_True; }
    }
    if (rd) {
      for (it1.Initialize(myVertices); 
	   (! myHasEqualParameters ) && it1.More();
	   it1.Next()) {
#ifdef DEB
//	const TopoDS_Shape& v1 = it1.Value()->Vertex();
#endif
	p1 = it1.Value()->Parameter();
	Standard_Real d = Abs(p1-f);
	if (d < Precision::PConfusion()) { 
	  myHasEqualParameters = Standard_True;
	  myEqualParameters = f;
#ifdef DEB
	  if (TopOpeBRepTool_GettraceVC()) {
	    cout<<"=*=*=*=*=*=*=*=*=*=*=*=*=*=*"<<endl;
	    cout<<"PaveSet : p1,f  d "<<p1<<","<<f<<"  "<<d<<endl;
	    cout<<"=*=*=*=*=*=*=*=*=*=*=*=*=*=*"<<endl;
	  }
#endif
	}
      }
    }
  }

  return myHasEqualParameters;
}

//=======================================================================
//function : EqualParameters
//purpose  : 
//=======================================================================

Standard_Real  TopOpeBRepBuild_PaveSet::EqualParameters() const
{
  if (myHasEqualParameters) {
    return myEqualParameters;
  }
  else {
    // raise NYI
  }
  return 0.; // windowsNT
}

//=======================================================================
//function : ClosedVertices
//purpose  : 
//=======================================================================

Standard_Boolean  TopOpeBRepBuild_PaveSet::ClosedVertices() 
{
  if (myVertices.IsEmpty()) return Standard_False;

  TopoDS_Shape  Vmin,Vmax;
  Standard_Real   parmin = RealLast(), parmax = RealFirst();
  for (TopOpeBRepBuild_ListIteratorOfListOfPave it(myVertices); 
       it.More(); 
       it.Next()) {
    const TopoDS_Shape& V = it.Value()->Vertex();
    Standard_Real par = it.Value()->Parameter();
    if (par > parmax) { Vmax = V; parmax = par; }
    if (par < parmin) { Vmin = V; parmin = par; }
  }

  myClosed = Vmin.IsSame(Vmax);
  return myClosed;
}
