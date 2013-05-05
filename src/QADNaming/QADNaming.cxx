// Created on: 1997-01-09
// Created by: VAUTHIER Jean-Claude & Fricaud Yves
// Copyright (c) 1997-1999 Matra Datavision
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


#include <stdio.h>

#include <QADNaming.ixx>

#include <DDF.hxx>

#include <Draw.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColStd_ListIteratorOfListOfInteger.hxx>
#include <TColStd_ListOfInteger.hxx>
#include <TCollection_AsciiString.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_LabelList.hxx>
#include <TDF_LabelMap.hxx>
#include <TDF_Tool.hxx>
#include <TNaming_Iterator.hxx>
#include <TNaming_Tool.hxx>
#include <TNaming_NamedShape.hxx>
#include <DBRep.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <gp_Pnt.hxx>

//=======================================================================
//function : GetShape
//purpose  : 
//=======================================================================

void QADNaming::GetShape (const Standard_CString      LabelName,
			const Handle(TDF_Data)&     DF,
			TopTools_ListOfShape&       L)
{
  L.Clear();
  TDF_Label Label;
  Standard_Boolean Found = DDF::AddLabel (DF, LabelName, Label);
  if (Found) {
    TNaming_Iterator it (Label, DF->Transaction ());
    for (; it.More(); it.Next()) {
      L.Append(it.NewShape());
    }
  }
}

//=======================================================================
//function : BuildMap
//purpose  : 
//=======================================================================

void QADNaming_BuildMap(TDF_LabelMap& Updated, 
		      const TDF_Label& Lab)
{
  TDF_ChildIterator it(Lab);
  for (; it.More(); it.Next()) {
    Updated.Add(it.Value());
    QADNaming_BuildMap(Updated,it.Value());
  }
}

//=======================================================================
//function : CurrentShape
//purpose  : 
//=======================================================================

TopoDS_Shape QADNaming::CurrentShape (const Standard_CString  LabelName,
				    const Handle(TDF_Data)& DF)
{
  TopoDS_Shape S;
  TDF_Label Label; 
  Standard_Boolean Found =  DDF::AddLabel (DF, LabelName, Label);
  if (!Found) {
    cout <<"no labels"<<endl;
    return S;
  }
  if (Found) { 
    Handle(TNaming_NamedShape)  NS;
    Label.FindAttribute(TNaming_NamedShape::GetID(),NS);
    S =  TNaming_Tool::CurrentShape(NS);
    if (S.IsNull())
      cout <<"current shape from "<< LabelName <<" is deleted"<<endl;
    return S;
  }
  return S;
}

//=======================================================================
//function : GetEntry
//purpose  : 
//=======================================================================

TCollection_AsciiString QADNaming::GetEntry (const TopoDS_Shape&         Shape,
					   const Handle(TDF_Data)&     DF,
					   Standard_Integer&           Status)
{
  Status = 0;
  //Handle(TNaming_UsedShapes) US;
  //DF->Root().FindAttribute(TNaming_UsedShapes::GetID(),US);

  if (!TNaming_Tool::HasLabel (DF->Root(), Shape)) {
    return TCollection_AsciiString ();
  }
  Standard_Integer Transdef;
  TDF_Label Lab = TNaming_Tool::Label (DF->Root(), Shape,Transdef);
  TCollection_AsciiString entry; TDF_Tool::Entry(Lab,entry);
  //Update Status;
  TNaming_Iterator it(Lab,DF->Transaction());
  for (; it.More(); it.Next()) {
    Status++;
    if (Status == 2) break;
  }
  return entry;
}

//=======================================================================
//function : GetEntry
//purpose  : 
//=======================================================================

Standard_Boolean QADNaming::Entry(const Standard_Address theArguments,
				TDF_Label& theLabel) {
  const char** arg = (const char**)theArguments;
  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF)) {
    cout<<"Wrong df"<<endl;
    return Standard_False;
  }
  DDF::AddLabel(DF,arg[2],theLabel);
  if (!theLabel.IsNull()) return Standard_True;
  cout<<"Wrong entry"<<endl;
  return Standard_False;
}

//=======================================================================
//function : IsSameShapes
//purpose  : IsSameShapes DrawShape1 DrawShape2
//=======================================================================
static Standard_Integer QADNaming_IsSameShapes (Draw_Interpretor& di,
				Standard_Integer nb, 
				const char** arg) {
  if (nb == 3) {
    TopoDS_Shape aShape1 = DBRep::Get(arg[1]);
    TopoDS_Shape aShape2 = DBRep::Get(arg[2]);
    if (aShape1.IsNull() || aShape2.IsNull()) return 0;
    if (aShape1.IsSame(aShape2)) di<<"1";
    return 0;
  }
  return 1;
}

//=======================================================================
//function : CenterOfShape
//purpose  : CenterOfShape DrawShape
//=======================================================================
static Standard_Integer QADNaming_CenterOfShape (Draw_Interpretor& di,
					       Standard_Integer nb, 
					       const char** arg) {
  if (nb == 2) {
    TopoDS_Shape aShape = DBRep::Get(arg[1]);
    if (aShape.IsNull()) return 1;
    Standard_Real x=0,y=0,z=0;
    float all = 0;
    TopExp_Explorer anExp(aShape,TopAbs_VERTEX);
    for(;anExp.More();anExp.Next(),all++) {
      TopoDS_Vertex aVertex = TopoDS::Vertex(anExp.Current());
      gp_Pnt aPoint = BRep_Tool::Pnt(aVertex);
      x+=aPoint.X();
      y+=aPoint.Y();
      z+=aPoint.Z();
    }
    if (all != 0) {
      char s[100];
      Sprintf(s,"%f %f %f",(float)x/all,(float)y/all,(float)z/all);
      di<<s;
      return 0;
    }
  }
  return 1;
}

//=======================================================================
//function : AllCommands
//purpose  : 
//=======================================================================

void QADNaming::AllCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  QADNaming::BasicCommands     (theCommands); 
  QADNaming::BuilderCommands   (theCommands); 
  QADNaming::IteratorsCommands (theCommands); 
  QADNaming::ToolsCommands     (theCommands);  
  QADNaming::SelectionCommands (theCommands);

  // auxiliary command IsSameShapes
  theCommands.Add("IsSameShapes","IsSameShapes DrawShape1 DrawShape2",__FILE__,QADNaming_IsSameShapes, "Auxiliary methods");
  theCommands.Add("CenterOfShape","CenterOfShape DrawShape",__FILE__,QADNaming_CenterOfShape, "Auxiliary methods");
  // define the TCL variable Draw_NamingData
  const char* com = "set Draw_NamingData 1";
  theCommands.Eval(com);
}
