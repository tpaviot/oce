// Created on: 1996-01-05
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


#include <TopOpeBRepBuild_CompositeClassifier.ixx>
#include <BRepTools.hxx>
#include <TCollection_AsciiString.hxx>

#define MYBB ((TopOpeBRepBuild_BlockBuilder*)myBlockBuilder)

// sourvenir d'un raise sur FrozenShape lors du Add(myShell,aFace)
// avec un shell qui a ete deja ete place dans le solide interne du 
// TopOpeBRepTool_SolidClassifier par LoadShell.

#ifdef DEB
//static Standard_Integer dddjyl = 0;
//static Standard_Integer dddebi = 0;
//static Standard_Integer dddebi2 = 0;
//static void SAVSS(const TopoDS_Shape& S1,const TopoDS_Shape& S2)
//{
//  TCollection_AsciiString aname_1("cc_1"), aname_2("cc_2");
//  Standard_CString name_1 = aname_1.ToCString(), name_2 = aname_2.ToCString();
//  cout<<"compositeclassifier : "<<name_1<<","<<name_2<<endl;
//  BRepTools::Write(S1,name_1); BRepTools::Write(S2,name_2); 
//}
#endif

//=======================================================================
//function : Initialize
//purpose  : 
//=======================================================================

TopOpeBRepBuild_CompositeClassifier::TopOpeBRepBuild_CompositeClassifier
(const TopOpeBRepBuild_BlockBuilder& BB) :
myBlockBuilder((void*)&BB)
{
}


//=======================================================================
//function : Compare
//purpose  : 
//=======================================================================

TopAbs_State TopOpeBRepBuild_CompositeClassifier::Compare
(const Handle(TopOpeBRepBuild_Loop)& L1,
 const Handle(TopOpeBRepBuild_Loop)& L2)
{ 
  TopAbs_State state = TopAbs_UNKNOWN;

  Standard_Boolean isshape1 = L1->IsShape();
  Standard_Boolean isshape2 = L2->IsShape();

  if      ( isshape2 && isshape1 )  { // L1 is Shape , L2 is Shape
    const TopoDS_Shape& s1 = L1->Shape();
    const TopoDS_Shape& s2 = L2->Shape();
    state = CompareShapes(s1,s2);
  }
  else if ( isshape2 && !isshape1 ) { // L1 is Block , L2 is Shape
    TopOpeBRepBuild_BlockIterator Bit1 = L1->BlockIterator();
    Bit1.Initialize();
    Standard_Boolean yena1 = Bit1.More();
    while (yena1) {
      const TopoDS_Shape& s1 = MYBB->Element(Bit1);
      const TopoDS_Shape& s2 = L2->Shape();
      state = CompareElementToShape(s1,s2);
      yena1 = Standard_False;
      if (state == TopAbs_UNKNOWN) { 
	if (Bit1.More()) Bit1.Next();
	yena1 = Bit1.More();
      }
    }
  }
  else if ( !isshape2 && isshape1 ) { // L1 is Shape , L2 is Block
    const TopoDS_Shape& s1 = L1->Shape();
    ResetShape(s1);
    TopOpeBRepBuild_BlockIterator Bit2 = L2->BlockIterator();
    for (Bit2.Initialize(); Bit2.More(); Bit2.Next()) {
      const TopoDS_Shape& s2 = MYBB->Element(Bit2);
      if (!CompareElement(s2)) 
        break;
    }
    state = State();
  }
  else if ( !isshape2 && !isshape1 ) { // L1 is Block , L2 is Block
    TopOpeBRepBuild_BlockIterator Bit1 = L1->BlockIterator();
    Bit1.Initialize();
    Standard_Boolean yena1 = Bit1.More();
    while (yena1) {
      const TopoDS_Shape& s1 = MYBB->Element(Bit1);
      ResetElement(s1);
      TopOpeBRepBuild_BlockIterator Bit2 = L2->BlockIterator();
      for (Bit2.Initialize(); Bit2.More(); Bit2.Next()) {
	const TopoDS_Shape& s2 = MYBB->Element(Bit2);
	CompareElement(s2);
      }
      state = State();
      yena1 = Standard_False;
      if (state == TopAbs_UNKNOWN) { 
	if (Bit1.More()) Bit1.Next();
	yena1 = Bit1.More();
      }
    }
  }

  return state;

}
