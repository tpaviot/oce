// Created on: 1997-01-13
// Created by: VAUTHIER Jean-Claude
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


#include <DNaming.hxx>
#include <TCollection_AsciiString.hxx>
#include <TDF_Data.hxx>
#include <TDF_ListIteratorOfLabelList.hxx>
#include <TDF_LabelList.hxx>
#include <TDF_LabelMap.hxx>
#include <TDF_Tool.hxx>
#include <DDF.hxx>
#include <DDF_Data.hxx>
#include <TNaming.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_NewShapeIterator.hxx>
#include <TNaming_OldShapeIterator.hxx>
#include <TNaming_Iterator.hxx>
#include <TNaming_Tool.hxx>
#include <TNaming_MapOfNamedShape.hxx>
#include <TNaming_MapIteratorOfMapOfNamedShape.hxx>
#include <Draw_Drawable3D.hxx>
#include <Draw.hxx>
#include <Draw_Interpretor.hxx>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_DataMapOfShapeShape.hxx>
#include <TopoDS_Shape.hxx>
#include <DBRep.hxx>

#include <TNaming_Builder.hxx>
#include <TDataStd_Name.hxx>
#include <TDF_TagSource.hxx>
#include <TopExp_Explorer.hxx>

#include <gp.hxx>
#include <gp_Vec.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax3.hxx>
#include <gp_Trsf.hxx>

#include <TColStd_HArray1OfInteger.hxx>
//#ifdef WNT
#include <stdio.h>
//#endif

// POP : first Wrong Declaration : now it is correct
//       second not used
//extern void DNaming_BuildMap(TDF_LabelMap& Updated, const TDF_Label& Lab);


//=======================================================================
//function : Ascendants
//purpose  : 
//=======================================================================
static Standard_Integer Ascendants (Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  
  char name[100];

  Handle(TDF_Data)           ND;
//  Handle(TNaming_UsedShapes) US;
  
  if (!DDF::GetDF(a[1],ND)) return 1;
//  ND->Root().FindAttribute(TNaming_UsedShapes::GetID(),US);

  TopoDS_Shape S = DBRep::Get (a[2]);
  if (S.IsNull ()) return 1;

  Standard_Integer T;

  if (n > 3) T = Draw::Atoi(a[3]);
  else       T = ND->Transaction ();

  //TNaming_OldShapeIterator it (S, T, US);  
  TNaming_OldShapeIterator it (S, T, ND->Root());
  Standard_Integer i = 0;
  TCollection_AsciiString entry;
  for (;it.More (); it.Next ()) {
    S = it.Shape ();
    Sprintf (name,"%s_%s_%d",a[2],"old", i++);
    DBRep::Set (name,it.Shape());
    TDF_Label Label = it.Label ();
    TDF_Tool::Entry(Label,entry);
    di<<entry.ToCString()<<"\n";
  }
  return 0;
}


//=======================================================================
//function : Descendants
//purpose  : 
//=======================================================================
static Standard_Integer Descendants (Draw_Interpretor& di, Standard_Integer n, const char** a)

{
  if (n < 3) return 1;
  
  char name[100];
  Handle(TDF_Data)           ND;
//  Handle(TNaming_UsedShapes) US;
  if (!DDF::GetDF(a[1],ND)) return 1;
//  ND->Root().FindAttribute(TNaming_UsedShapes::GetID(),US);


  TopoDS_Shape S = DBRep::Get (a[2]);
  if (S.IsNull ()) return 1;

  Standard_Integer T;

  if (n > 3) T = Draw::Atoi(a[3]);
  else       T = ND->Transaction ();

  TNaming_NewShapeIterator it (S, T, ND->Root());
  Standard_Integer i = 0;
  TCollection_AsciiString entry;
  for (;it.More (); it.Next ()) {
    S = it.Shape ();
    Sprintf (name,"%s_%s_%d",a[2],"new", i++);
    DBRep::Set (name,it.Shape ());
    TDF_Label Label = it.Label ();
    TDF_Tool::Entry(Label,entry);
    di<<entry.ToCString()<<"\n";
  }

  return 0;
}

//=======================================================================
//function : GetEntry
//purpose  : 
//=======================================================================
static Standard_Integer Getentry (Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  Handle(TDF_Data)           ND;
//  Handle(TNaming_UsedShapes) US;

  if (!DDF::GetDF(a[1],ND)) return 1;
//  ND->Root().FindAttribute(TNaming_UsedShapes::GetID(),US);

  TopoDS_Shape S = DBRep::Get(a[2]);
  if (S.IsNull()) {
    di <<"Noone shape selected"<<"\n";
    //di << 0;
    return 0;
  }
  Standard_Integer Status ;
  TCollection_AsciiString Name   = DNaming::GetEntry(S,ND,Status);
  if (Status == 0) {
    di <<"E_NoName";
  }
  else  {
    di <<Name.ToCString();
    if (Status == 2) {
      di <<"Several shapes have the same name"<<"\n";
    }
  }
  return 0;
}

//=======================================================================
//function : NamedShape
//purpose  : retrive label of Primitive or a Generated shape
//=======================================================================
static Standard_Integer NamedShape(Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  Handle(TDF_Data)           ND;
//  Handle(TNaming_UsedShapes) US;

  if (!DDF::GetDF(a[1],ND)) return 1;
  TopoDS_Shape  SS = DBRep::Get(a[2]);
  if (SS.IsNull()) {
    di <<"Noone shape selected"<<"\n";
    //di << 0;
    return 0;
  }
  
  Handle(TNaming_NamedShape) NS = TNaming_Tool::NamedShape (SS,ND->Root());

  if (NS.IsNull()) { 
    di <<"E_NoName";
    return 0;
  }
  TCollection_AsciiString Name; TDF_Tool::Entry(NS->Label(),Name);
  di <<Name.ToCString();
  return 0;
}

//=======================================================================
//function : Currentshape
//purpose  : 
//=======================================================================
static Standard_Integer Currentshape (Draw_Interpretor& , Standard_Integer n, const char** a)
{ 
  if (n < 4) return 1;

  Handle(TDF_Data)           ND;
  if (!DDF::GetDF(a[1],ND)) return 1;

  Standard_CString LabelName = a[2];
  TopoDS_Shape S = DNaming::CurrentShape(LabelName,ND);
  if (!S.IsNull()) {
    if (n == 4) DBRep::Set(a[3],S);
    else        DBRep::Set(a[2],S);
    return 0;
  }
  return 0;
}

//=======================================================================
//function : Initialshape
//purpose  : 
//=======================================================================
static Standard_Integer Initialshape (Draw_Interpretor& di, Standard_Integer n, const char** a)
{ 
  if (n < 4) return 1;

  Handle(TDF_Data)           ND;
  
  if (!DDF::GetDF(a[1],ND)) return 1;

  TopoDS_Shape NS = DBRep::Get(a[2]);
  if (NS.IsNull()) return 1;

  TDF_LabelList Labels;
  TopoDS_Shape S = TNaming_Tool::InitialShape (NS,ND->Root(),Labels);
  if (!S.IsNull()) {
    DBRep::Set (a[3], S);
  }
  TDF_ListIteratorOfLabelList itL(Labels);

  TCollection_AsciiString entry;
  if (itL.More()) {
    TDF_Tool::Entry(itL.Value(),entry);
    di << entry.ToCString();
    itL.Next();
  }
  for (; itL.More(); itL.Next()) {
    TDF_Tool::Entry(itL.Value(),entry);
    di <<" , "<< entry.ToCString();    
  }
  di <<"."<<"\n";
  return 0;
}

//=======================================================================
//function : GetShape
//purpose  : 
//=======================================================================
static Standard_Integer Exploreshape (Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  char name[100];

  if (n < 4) return 1;
  Handle(TDF_Data)           ND;
//  Handle(TNaming_UsedShapes) US;
  
  if (!DDF::GetDF(a[1],ND)) return 1;
//  ND->Root().FindAttribute(TNaming_UsedShapes::GetID(),US);
  
  Standard_Integer Trans = ND->Transaction();
  if (n == 5) { Trans = (Standard_Integer ) Draw::Atof(a[4]);}
  
  TDF_Label Lab;
  DDF::FindLabel(ND,a[2],Lab);
  Handle(TNaming_NamedShape) NS;
  if (!Lab.FindAttribute(TNaming_NamedShape::GetID(),NS)) { 
    di <<"No shape"<<"\n";
    return 0;
  }

  //TNaming::Print(NS->Evolution(),cout);
  Standard_SStream aStream;
  TNaming::Print(NS->Evolution(),aStream);
  di << aStream << "\n";

  Standard_Integer NbShapes = 1;
  
  for (TNaming_Iterator itL(Lab,Trans) ; itL.More(); itL.Next()) {
    if (!itL.OldShape().IsNull()) {
      Sprintf(name,"%s%s_%d","old",a[3],NbShapes);
      DBRep::Set (name,itL.OldShape());
    }
    if (!itL.NewShape().IsNull()) {    
      Sprintf(name,"%s_%d",a[3],NbShapes);
      DBRep::Set (name,itL.NewShape());
    }
    NbShapes++;
  }
  di <<"\n";
  if (NbShapes == 0) {
    di <<"No shape"<<"\n";
  }

  return 0;
}

//=======================================================================
//function : GeneratedShape
//purpose  : Generatedshape df shape Generationentry [drawname]
//=======================================================================

static Standard_Integer Generatedshape (Draw_Interpretor& di,
					Standard_Integer nb, 
					const char** arg) 
{ 
  TopoDS_Shape S;
  Handle(TNaming_NamedShape) A;
  if (nb >= 4) { 
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TopoDS_Shape Gen = DBRep::Get(arg[2]);
    Handle(TNaming_NamedShape) Generation;
    if (!DDF::Find(DF,arg[3],TNaming_NamedShape::GetID(),Generation)) return 1;
    S = TNaming_Tool::GeneratedShape(Gen,Generation);
    if (!S.IsNull()) {
      if (nb == 4) DBRep::Set(arg[4],S);
      else         DBRep::Set(arg[3],S);
      return 0;
    }
  }
  di << "GetShape : Error" << "\n";
  return 1;
}

//=======================================================================
//function : DDataStd_GetShape
//purpose  : 
//=======================================================================

static Standard_Integer Getshape (Draw_Interpretor& di,
				  Standard_Integer nb, 
				  const char** arg) 
{ 
  TopoDS_Shape s;
  Handle(TNaming_NamedShape) A;
  if (nb >= 3) { 
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    if (!DDF::Find(DF,arg[2],TNaming_NamedShape::GetID(),A)) return 1;
    s = TNaming_Tool::GetShape(A);
    if (!s.IsNull()) {
      if (nb == 4) DBRep::Set(arg[3],s);
      else         DBRep::Set(arg[2],s);
      return 0;
    }
  }
  di << "DDataStd_GetShape : Error" << "\n";
  return 1;
}
//=======================================================================
//function : Collect
//purpose  : 
//=======================================================================

static Standard_Integer Collect (Draw_Interpretor& di,
				 Standard_Integer nb, 
				 const char** arg) 
{   
  TNaming_MapOfNamedShape MNS;
  Handle(TNaming_NamedShape) A;
  Standard_Boolean           OnlyModif = 1;

  if (nb >= 3) { 
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    if (!DDF::Find(DF,arg[2],TNaming_NamedShape::GetID(),A)) return 1;
    if (nb >= 4) {
      OnlyModif = Draw::Atoi(arg[3]);
    }
    TNaming_Tool::Collect(A,MNS,OnlyModif);
    for (TNaming_MapIteratorOfMapOfNamedShape it(MNS); it.More(); it.Next()) {
      TCollection_AsciiString Name; 
      TDF_Tool::Entry(it.Key()->Label(),Name);     
      di <<Name.ToCString()<<" ";
    }
  }
  return 1;
}
//=======================================================================
//function : GetCreationEntry
//purpose  : retrive label of Primitive or a Generated shape
//=======================================================================
static Standard_Integer Getcreationentry (Draw_Interpretor& di, Standard_Integer n, const char** a)
{
  if (n < 3) return 1;
  Handle(TDF_Data)           ND;
//  Handle(TNaming_UsedShapes) US;

  if (!DDF::GetDF(a[1],ND)) return 1;
//  ND->Root().FindAttribute(TNaming_UsedShapes::GetID(),US);

  TopoDS_Shape  SS = DBRep::Get(a[2]);

  if (SS.IsNull()) {
    di <<"Noone shape selected"<<"\n";
    //di << 0;
    return 0;
  }
  
  TDF_LabelList Labels;
  TopoDS_Shape  S = TNaming_Tool::InitialShape(SS, ND->Root(), Labels);

  if (S.IsNull()) { 
    di <<"E_NoName";
    return 0;
  }
  Standard_Integer Status ;
  
  TCollection_AsciiString Name   = DNaming::GetEntry(S,ND,Status);
  if (Status == 0) {
    di <<"E_NoName";
  }
  else  {
    di <<Name.ToCString();
    if (Status == 2) {
      di <<"Several shapes have the same name"<<"\n";
    }
  }
  return 0;
}

//=======================================================================
//function : ImportShape
//purpose  : "ImportShape Doc  entry Shape Name"
//=======================================================================

static Standard_Integer DNaming_ImportShape (Draw_Interpretor& di,
					     Standard_Integer nb, 
					     const char** a)
{
  if (nb >= 4) {
    Handle(TDF_Data) aDF;
    if(!DDF::GetDF(a[1], aDF)) return 1;
    TDF_Label L;
    DDF::AddLabel(aDF, a[2], L);
    const TopoDS_Shape& aShape = DBRep::Get(a[3]);
    if(aShape.IsNull()) return 1;
    if(nb == 5) {
      TDataStd_Name::Set(L, a[4]);
    }
    
    DNaming::LoadImportedShape(L, aShape);
    
    DDF::ReturnLabel(di, L);
    return 0;
  }
  cout << "DNaming_NewShape : Error" << endl;
  return 1;  
}

//=======================================================================
//function : BasicCommands
//purpose  : 
//=======================================================================

void  DNaming::BasicCommands(Draw_Interpretor& theCommands)
{
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  const char* g = "Naming data commands";

  // Exploration
  theCommands.Add("Ascendants",  "Ascendants df shape [trans]",      __FILE__,Ascendants,      g);
  theCommands.Add("Descendants", "Descendants  df shape [trans]",    __FILE__,Descendants,     g);
  theCommands.Add("ExploreShape","ExploreShape df entry res [trans]",__FILE__,Exploreshape,    g);
  theCommands.Add("GetEntry",    "GetEntry df shape",                __FILE__,Getentry,        g);  
  theCommands.Add("GetCreationEntry",    "GetCreationEntry df shape",__FILE__,Getcreationentry,g);
  theCommands.Add("NamedShape",  "NamedShape df shape",              __FILE__,NamedShape,      g);
  theCommands.Add("InitialShape","InitialShape df shape res",        __FILE__,Initialshape,    g);
  theCommands.Add("CurrentShape","Currentshape df entry [drawname]", __FILE__,Currentshape,    g);
  theCommands.Add("GetShape",    "GetShape df entry [drawname]",     __FILE__,Getshape ,       g);  
  theCommands.Add("Collect",     "Collect  df entry [onlymodif 0/1]",__FILE__,Collect ,        g);  
  theCommands.Add ("GeneratedShape", "Generatedshape df shape Generationentry [drawname]", __FILE__,Generatedshape,g);
  theCommands.Add("ImportShape", "ImportShape Doc Entry Shape [Name]",__FILE__,DNaming_ImportShape, g);  
}