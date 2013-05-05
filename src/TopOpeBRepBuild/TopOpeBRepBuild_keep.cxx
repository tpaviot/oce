// Created on: 1996-03-07
// Created by: Jean Yves LEBEY
// Copyright (c) 1996-1999 Matra Datavision
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


#include <TopOpeBRepBuild_Builder.ixx>
#include <TopOpeBRepDS_define.hxx>

#ifdef DEB
extern Standard_Integer GLOBAL_iexE;
extern Standard_Integer GLOBAL_iexF;
Standard_Boolean STATIC_trace_iexE = Standard_False;
Standard_Boolean STATIC_trace_iexF = Standard_False;
Standard_EXPORT void debkeep(const Standard_Integer i) {cout<<"++ debkeep "<<i<<endl;}
#endif

//=======================================================================
//function : GKeepShape
//purpose  : 
// compute position of shape <S> / shapes of list <LSclass>
// return true if LS is not empty && (position == TB)
// (return always true if LS is empty)
//=======================================================================
Standard_Boolean TopOpeBRepBuild_Builder::GKeepShape
(const TopoDS_Shape& S, const TopTools_ListOfShape& LSclass, const TopAbs_State TB)
{ 
  TopAbs_State pos;
  return GKeepShape1(S,LSclass,TB,pos);
}

Standard_Boolean TopOpeBRepBuild_Builder::GKeepShape1
(const TopoDS_Shape& S, const TopTools_ListOfShape& LSclass, const TopAbs_State TB,
 TopAbs_State& pos)
{ 
  Standard_Boolean keep = Standard_True;
  pos = TopAbs_UNKNOWN;
  Standard_Boolean toclassify = Standard_True;
  if (S.ShapeType() == TopAbs_FACE &&
      !myDataStructure->HasShape(S) &&
      myClassifyDef) {
    toclassify = myClassifyVal;
  }
  
  toclassify = (toclassify && !LSclass.IsEmpty());
  if (toclassify) {
    pos = ShapePosition(S,LSclass);
    if ( pos != TB ) keep = Standard_False;
  }
#ifdef DEB
  Standard_Integer iS; Standard_Boolean tSPS = GtraceSPS(S,iS);
  Standard_Integer iface = 0, isoli = 0; 
  Standard_Boolean tSPSface = Standard_False;
  Standard_Boolean tSPSsoli = Standard_False;
  if ( S.ShapeType() == TopAbs_EDGE ) {
    tSPSface = GtraceSPS(myFaceToFill,iface);
    tSPSface = tSPSface && STATIC_trace_iexE;
  }
  else if ( S.ShapeType() == TopAbs_FACE ) {
    tSPSsoli = GtraceSPS(mySolidToFill,isoli);
    tSPSsoli = tSPSsoli && STATIC_trace_iexF;
  }
  
  Standard_Boolean tr = tSPS || tSPSface || tSPSsoli;
  if(tr){
    if (tSPS) GdumpSHA(S);
    else if (tSPSface) cout<<"EDGE exploration "<<GLOBAL_iexE;
    else if (tSPSsoli) cout<<"FACE exploration "<<GLOBAL_iexF;
    if(keep)cout<<" is kept";else cout<<" is NOT kept";
    cout<<" ";TopAbs::Print(TB,cout);cout<<" / ";
    if(LSclass.IsEmpty())cout<<"empty list";else GdumpLS(LSclass);cout<<endl;
    cout.flush();
  }
#endif
  
  return keep;
}

//=======================================================================
//function : GKeepShapes
//purpose  : 
// select shapes to keep from list Lin located TB compared with LSclass shapes
// selected shapes are stored in list Lou
// (apply GKeepShape on Lin shapes)
// Lou is not cleared
// S is used for trace only
//=======================================================================
void TopOpeBRepBuild_Builder::GKeepShapes
(const TopoDS_Shape& S,const TopTools_ListOfShape& LSclass,const TopAbs_State TB,const TopTools_ListOfShape& Lin,TopTools_ListOfShape& Lou)
{
#ifdef DEB
  Standard_Integer iS; Standard_Boolean tSPS = GtraceSPS(S,iS);
  if (tSPS) debkeep(iS);
#endif
  
#ifdef DEB
  Standard_Integer n = 0;
#endif
  TopTools_ListIteratorOfListOfShape it(Lin);
  for (; it.More(); it.Next() ) {
    const TopoDS_Shape& SL = it.Value();
    
    Standard_Boolean keep = Standard_True;
    if ( ! LSclass.IsEmpty() ) {
      TopAbs_State pos = ShapePosition(SL,LSclass);
      if ( pos != TB ) keep = Standard_False;
    }
    
#ifdef DEB
    TopAbs_ShapeEnum t = SL.ShapeType();
    if(tSPS){cout<<"GKeepShapes : ";}
    if(tSPS){cout<<"new ";TopAbs::Print(t,cout);cout<<" "<<++n;}
    if(tSPS){cout<<" from ";GdumpSHA(S);if(keep)cout<<" is kept";else cout<<" is NOT kept";}
    if(tSPS){cout<<" ";TopAbs::Print(TB,cout);cout<<" / ";}
    if(tSPS){if(LSclass.IsEmpty())cout<<"empty list";else GdumpLS(LSclass);cout<<endl;}
#endif
    
    if (keep) Lou.Append(SL);
  }
}
