// Created on: 1997-07-30
// Created by: Denis PASCAL
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


#include <DDataStd.hxx>

#include <Standard_PCharacter.hxx>

#include <DDF.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw_Appli.hxx>
#include <DrawTrSurf.hxx>

#include <DDF.hxx>

#include <TDF_Data.hxx>
#include <TDF_Label.hxx>
#include <TDF_Tool.hxx>
#include <TDF_AttributeSequence.hxx>
#include <TDF_AttributeList.hxx>
#include <TDF_ListIteratorOfAttributeList.hxx>

#include <DBRep.hxx>
#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shell.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS_Shape.hxx>

#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Pln.hxx>

#include <TCollection_AsciiString.hxx>
#include <TColStd_HArray1OfReal.hxx>

// LES ATTRIBUTES
#include <TDataStd.hxx>
#include <TDataStd_Comment.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_Integer.hxx>
#include <TDataStd_Real.hxx>
#include <TDF_Reference.hxx>
#include <TDataStd_UAttribute.hxx>
#include <TDataStd_IntegerArray.hxx>
#include <TDataStd_RealArray.hxx>
#include <TDataStd_Variable.hxx>
#include <TDataStd_ExtStringArray.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Tool.hxx>

#include <TDataStd_NamedData.hxx>
#include <TColStd_DataMapOfStringInteger.hxx>
#include <TColStd_DataMapIteratorOfDataMapOfStringInteger.hxx>
#include <TDataStd_DataMapOfStringReal.hxx>
#include <TDataStd_DataMapIteratorOfDataMapOfStringReal.hxx>
#include <TDataStd_DataMapOfStringByte.hxx>
#include <TDataStd_DataMapIteratorOfDataMapOfStringByte.hxx>
#include <TDataStd_DataMapOfStringString.hxx>
#include <TDataStd_DataMapIteratorOfDataMapOfStringString.hxx>
#include <TDataStd_DataMapOfStringHArray1OfInteger.hxx>
#include <TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfInteger.hxx>
#include <TDataStd_DataMapOfStringHArray1OfReal.hxx>
#include <TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfReal.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TDataStd_AsciiString.hxx>
#include <TDataStd_IntPackedMap.hxx>
#include <TColStd_HPackedMapOfInteger.hxx>
#include <TColStd_PackedMapOfInteger.hxx>
#include <TColStd_MapIteratorOfPackedMapOfInteger.hxx>
#include <TDataStd_ByteArray.hxx>

#include <Standard_Macro.hxx>
#ifdef OptJr
#define ROUNDMEM(len) (((len)+3)&~0x3)
#else
#define ROUNDMEM(len) (len)
#endif

//=======================================================================
//function : DDataStd_SetInteger
//purpose  : SetInteger (DF, entry, value)
//=======================================================================

static Standard_Integer DDataStd_SetInteger (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{     
  if (nb == 4) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    TDataStd_Integer::Set(L,Draw::Atoi(arg[3]));  
    return 0;
  }
  di << "DDataStd_SetInteger : Error" << "\n";
  return 1;
}

//=======================================================================
//function : DDataStd_SetReal
//purpose  : SetReal (DF, entry, value)
//=======================================================================

static Standard_Integer DDataStd_SetReal (Draw_Interpretor& di,
                                           Standard_Integer nb, 
                                           const char** arg) 
{   
  if (nb == 4) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    TDataStd_Real::Set(L,Draw::Atof(arg[3]));  
    return 0;
  } 
  di << "DDataStd_SetReal : Error" << "\n";
  return 1;
}



//=======================================================================
//function : DDataStd_SetReference
//purpose  : SetReference (DF, entry, reference)
//=======================================================================

static Standard_Integer DDataStd_SetReference (Draw_Interpretor& di,
                                               Standard_Integer nb, 
                                               const char** arg) 
{   
  if (nb == 4) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);  
    TDF_Label LREF;
    if (!DDF::FindLabel(DF,arg[3],LREF)) return 1;
    TDF_Reference::Set(L,LREF);  
    return 0;
  } 
  di << "DDataStd_SetReference : Error" << "\n";
  return 1;
}


//=======================================================================
//function : DDataStd_SetComment
//purpose  : SetComment (DF, entry, Comment)
//=======================================================================

static Standard_Integer DDataStd_SetComment (Draw_Interpretor& di,
                                               Standard_Integer nb, 
                                               const char** arg) 
{   
  if (nb == 4) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    TDataStd_Comment::Set(L,arg[3]);  
    return 0;
  }
  di << "DDataStd_SetComment : Error" << "\n";
  return 1;
}



//=======================================================================
//function : DDataStd_GetInteger
//purpose  : GetReal (DF, entry, [drawname])
//=======================================================================

static Standard_Integer DDataStd_GetInteger (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{     
  if (nb == 3 || nb == 4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    Handle(TDataStd_Integer) A;
    if (!DDF::Find(DF,arg[2],TDataStd_Integer::GetID(),A)) return 1;
    if (nb == 4) Draw::Set(arg[3],A->Get());
    else         Draw::Set(arg[2],A->Get());
    di << A->Get();
    return 0;
  }
  di << "DDataStd_GetInteger : Error" << "\n";
  return 1;
}

//=======================================================================
//function : DDataStd_GetReal
//purpose  : GetReal (DF, entry, [drawname])
//=======================================================================

static Standard_Integer DDataStd_GetReal (Draw_Interpretor& di,
                                          Standard_Integer nb, 
                                          const char** arg) 
{  
  if (nb == 3 || nb == 4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    Handle(TDataStd_Real) A;
    if (!DDF::Find(DF,arg[2],TDataStd_Real::GetID(),A)) return 1;
    if (nb == 4) Draw::Set(arg[3],A->Get());
    else         Draw::Set(arg[2],A->Get());
    di << A->Get();
    return 0;
  }
  di << "DDataStd_GetReal : Error" << "\n";
  return 1;
}


//=======================================================================
//function : DDataStd_GetReference
//purpose  : GetShape (DF, entry)
//=======================================================================

static Standard_Integer DDataStd_GetReference (Draw_Interpretor& di,
                                               Standard_Integer nb, 
                                               const char** arg) 
{  
  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    Handle(TDF_Reference) REF;
    if (!DDF::Find(DF,arg[2],TDF_Reference::GetID(),REF)) return 1;
    TCollection_AsciiString entry; TDF_Tool::Entry(REF->Get(),entry);
    di << entry.ToCString();
    return 0;
  }
  di << "DDataStd_GetReference : Error" << "\n";
  return 1;
}

//=======================================================================
//function : DDataStd_GetComment
//purpose  : GetShape (DF, entry)
//=======================================================================

static Standard_Integer DDataStd_GetComment (Draw_Interpretor& di,
                                          Standard_Integer nb, 
                                          const char** arg) 
{ 
  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    Handle(TDataStd_Comment) A;
    if (!DDF::Find(DF,arg[2],TDataStd_Comment::GetID(),A)) return 1;
    TCollection_AsciiString s(A->Get(),'?');
    di << s.ToCString();
    return 0;
  }
  di << "DDataStd_GetComment : Error" << "\n";
  return 1;
}



//=======================================================================
//function :
//purpose  : Self (document,label)
//=======================================================================

static Standard_Integer DDataStd_Self (Draw_Interpretor& di,
                                       Standard_Integer nb, 
                                       const char** arg) 
{    
  TCollection_AsciiString s;  
  if (nb == 3) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    if (!DDF::FindLabel(DF,arg[2],L)) return 1; 
//    TDataStd::MakeSelfContained(L,removed);
//    if (removed.IsEmpty()) cout << "noone attriburte removed" << endl;
//    for (TDF_ListIteratorOfAttributeList it(removed);it.More();it.Next()) {
//      TDF_Tool::Entry(it.Value()->Label(),s); cout  << s << " ";
//      cout << endl;
//    }
    return 0;
  } 
  di << "Self : Error" << "\n";
  return 0;
}



//=======================================================================
//function : SetUObject (DF, entry, ObjectID)
//=======================================================================
// static Standard_Integer DDataStd_SetUObject (Draw_Interpretor&,
//                                            Standard_Integer nb, 
//                                            const char** arg) 
// {   
//   if( nb == 4 ) {
//     Handle(TDF_Data) DF;
//     if (!DDF::GetDF(arg[1],DF))  return 1;
//     TDF_Label label;
//     DDF::AddLabel(DF, arg[2], label);

//     Standard_GUID guid(arg[3]);  //"00000000-0000-0000-1111-000000000000");
//     TDataStd_UObject::Set(label, guid);
//     return 0;
//   }

//   cout << "Wrong arguments"  << endl;  
//   return 1;
// } 

//=======================================================================
//function : SetUAttribute (DF, entry, LocalID)
//=======================================================================
static Standard_Integer DDataStd_SetUAttribute (Draw_Interpretor& di,
                                                Standard_Integer nb, 
                                                const char** arg) 
{   
  if( nb == 4 ) { 
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label label;
    DDF::AddLabel(DF, arg[2], label);

    Standard_GUID guid(arg[3]);  //"00000000-0000-0000-2222-000000000000");
    TDataStd_UAttribute::Set(label, guid);
    return 0; 
  }

  di << "Wrong arguments"  << "\n";  
  return 1; 
} 

//=======================================================================
//function : GetUAttribute (DF, entry, LoaclID)
//=======================================================================
static Standard_Integer DDataStd_GetUAttribute (Draw_Interpretor& di,
                                                Standard_Integer nb, 
                                                const char** arg) 
{   
  if( nb == 4 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1; 
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
     di << "No label for entry"  << "\n";
     return 1;
    }
    Standard_GUID guid(arg[3]);  //"00000000-0000-0000-2222-000000000000");

    Handle(TDataStd_UAttribute) UA;    
    if( !label.FindAttribute(guid, UA) ) {
      di << "No UAttribute Attribute on label"   << "\n";
    }
    else {
//      UA->ID().ShallowDump(cout);
//      cout << endl; 
      char *aStrGUID = new char[37];
      UA->ID().ToCString(aStrGUID);
      di << aStrGUID;
    }
    return 0;  
  }

  di << "Wrong arguments"  << "\n";  
  return 1;  
} 


//=======================================================================
//function : CheckUObject (DF, entry, ObjectID)
//=======================================================================
// static Standard_Integer DDataStd_CheckUObject (Draw_Interpretor&,
//                                           Standard_Integer nb, 
//                                           const char** arg) 
// {   
//   if( nb == 4 ) {   
//     Handle(TDF_Data) DF;
//     if (!DDF::GetDF(arg[1],DF)) return 1;  
//     TDF_Label label;
//     if( !DDF::FindLabel(DF, arg[2], label) ) { 
//      cout << "No label for entry"  << endl;
//      return 1; 
//     }
//     Handle(TDataStd_Object) O;
//     Handle(TDataStd_UObject) UO;    
//     Standard_GUID guidUO(arg[3]);

//     if( !label.FindAttribute( TDataStd_Object::GetID(), O) ) {
//       cout << "No Object Attribute on label"   << endl;
//     }
//     else { 
//       cout << "UObject is found with ObjectID = ";
//       O->Find(label, guidUO, UO);
//       UO->ObjectID().ShallowDump(cout);
//       cout << endl; 
//     }
//     return 0;   
//   }

//   cout << "Wrong arguments"  << endl;  
//   return 1;  
// }


//=======================================================================
//function : SetIntArray (DF, entry , isDelta, From, To,  elmt1, elmt2, ...
//=======================================================================
static Standard_Integer DDataStd_SetIntArray (Draw_Interpretor& di,
                                              Standard_Integer, 
                                              const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1; 
  TDF_Label label;
  DDF::AddLabel(DF, arg[2], label);
  Standard_Integer isDelta = Draw::Atoi(arg[3]);
  Standard_Integer From = Draw::Atoi(arg[4]), To = Draw::Atoi( arg[5] ), j;
  di << "Array of Standard_Integer with bounds from = " << From  << " to = " << To  << "\n";
  Handle(TDataStd_IntegerArray) A = TDataStd_IntegerArray::Set(label, From, To, isDelta);
  
  j = 6;
  for(Standard_Integer i = From; i<=To; i++) {
    A->SetValue(i, Draw::Atoi(arg[j]) ); 
    j++;
  }

  return 0; 
} 

//=======================================================================
//function : GetIntArray (DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetIntArray (Draw_Interpretor& di,
                                              Standard_Integer, 
                                              const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1;  
  TDF_Label label;
  if( !DDF::FindLabel(DF, arg[2], label) ) {
    di << "No label for entry"  << "\n";
    return 1;
  }
 
  Handle(TDataStd_IntegerArray) A;
  if ( !label.FindAttribute(TDataStd_IntegerArray::GetID(), A) ) { 
    di << "There is no TDataStd_IntegerArray under label"  << "\n";
    return 1;
  }
  
  for(Standard_Integer i = A->Lower(); i<=A->Upper(); i++){
    //cout <<  A->Value(i)   << endl;
    di  <<  A->Value(i);
    if(i<A->Upper())  
     di<<" ";
  }
  di<<"\n";
  return 0; 
} 
//
//=======================================================================
//function : ChangeIntArray (DF, entry, indx, val )
//=======================================================================
static Standard_Integer DDataStd_ChangeIntArray (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if( nb == 5 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_IntegerArray) A;
    if ( !label.FindAttribute(TDataStd_IntegerArray::GetID(), A) ) { 
      di << "There is no TDataStd_IntegerArray at label"  << "\n";
      return 1;
    }
    Standard_Integer indx = Draw::Atoi(arg[3]);
    Standard_Integer val  = Draw::Atoi(arg[4]);
    Standard_Integer low = A->Lower(), up = A->Upper();
    if(low <= indx && indx <= up)
      A->SetValue(indx, val);
    else {
      Handle(TColStd_HArray1OfInteger) Arr = A->Array();
      Handle(TColStd_HArray1OfInteger) arr;
      Standard_Integer i;
      if(indx > up) {
	up = indx;
	arr = new TColStd_HArray1OfInteger(low, up);
	for(i=low; i<= Arr->Upper(); i++)
	  arr->SetValue(i, Arr->Value(i));
	for(i=Arr->Upper()+1; i<= up; i++) {
	  if(i == up)
	    arr->SetValue(i, val);
	  else
	    arr->SetValue(i, 0);
	}
      } else if(indx < up) {//clip array : indx to be negative
	up = abs(indx);
	arr = new TColStd_HArray1OfInteger(low, up);
	for(i=low; i< up; i++)
	  arr->SetValue(i, Arr->Value(i));
	arr->SetValue(up, val);
      }
      A->ChangeArray(arr);
    }
    return 0;
  }
  di << "DDataStd_ChangeIntArray: Error" << "\n";
  return 0; 
} 

//=======================================================================
//function : SetIntArrayT (DF, entry , isDelta, From, To) - for testing
//         : huge arrays
//=======================================================================
static Standard_Integer DDataStd_SetIntArrayTest (Draw_Interpretor& di,
                                              Standard_Integer, 
                                              const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1; 
  TDF_Label label;
  DDF::AddLabel(DF, arg[2], label);
  Standard_Integer isDelta = Draw::Atoi(arg[3]);
  Standard_Integer From = Draw::Atoi(arg[4]), To = Draw::Atoi( arg[5] ), j;
  di << "Array of Standard_Integer with bounds from = " << From  << " to = " << To  << "\n";
  Handle(TDataStd_IntegerArray) A = TDataStd_IntegerArray::Set(label, From, To, isDelta);
  
  j = 6;
  Standard_Integer k = 100;
  for(Standard_Integer i = From; i<=To; i++) {
    A->SetValue(i, ++k); 
    j++;
  }

  return 0; 
} 

//=======================================================================
//function : SetRealArray (DF, entry , isDelta, From, To,  elmt1, elmt2, ...
//=======================================================================
static Standard_Integer DDataStd_SetRealArray (Draw_Interpretor& di,
                                               Standard_Integer, 
                                               const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1;  
  TDF_Label label; 
  DDF::AddLabel(DF, arg[2], label);
  Standard_Integer isDelta = Draw::Atoi(arg[3]);
 
  Standard_Integer From = Draw::Atoi(arg[4]), To = Draw::Atoi( arg[5] ), j;
  di << " Array of Standard_Real with bounds from = " << From  << " to = " << To  << "\n";
  Handle(TDataStd_RealArray) A = TDataStd_RealArray::Set(label, From, To, isDelta);
  
  j = 6;
  for(Standard_Integer i = From; i<=To; i++) { 
    A->SetValue(i, Draw::Atof(arg[j]) ); 
    j++;
  }

  return 0;  
} 

//=======================================================================
//function : GetRealArray (DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetRealArray (Draw_Interpretor& di,
                                               Standard_Integer, 
                                               const char** arg) 
{   

  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1;  
  TDF_Label label;
  if( !DDF::FindLabel(DF, arg[2], label) ) { 
    di << "No label for entry"  << "\n";
    return 1; 
  }
 
  Handle(TDataStd_RealArray) A;
  if ( !label.FindAttribute(TDataStd_RealArray::GetID(), A) ) { 
    di << "There is no TDataStd_RealArray under label"  << "\n";
    return 1; 
  }
  
  for(Standard_Integer i = A->Lower(); i<=A->Upper(); i++){
    //cout <<  A->Value(i)   << endl; 
    di   <<  A->Value(i);
    if(i<A->Upper())  
     di<<" ";
  }  
  di<<"\n";

  return 0;  
} 

//
//=======================================================================
//function : ChangeRealArray (DF, entry, indx, val )
//=======================================================================
static Standard_Integer DDataStd_ChangeRealArray (Draw_Interpretor& di,
                                                  Standard_Integer nb, 
                                                  const char** arg) 
{   

  if( nb == 5 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_RealArray) A;
    if ( !label.FindAttribute(TDataStd_RealArray::GetID(), A) ) { 
      di << "There is no TDataStd_RealArray at label"  << "\n";
      return 1;
    }
    Standard_Integer indx = Draw::Atoi(arg[3]);
    Standard_Real val  = Draw::Atof(arg[4]);
    Standard_Integer low = A->Lower(), up = A->Upper();
    if(low <= indx && indx <= up)
      A->SetValue(indx, val);
    else {
      Handle(TColStd_HArray1OfReal) Arr = A->Array();
      Handle(TColStd_HArray1OfReal) arr;
      Standard_Integer i;
      if(indx > up) {
	up = indx;
	arr = new TColStd_HArray1OfReal(low, up);
	for(i=low; i<= Arr->Upper(); i++)
	  arr->SetValue(i, Arr->Value(i));
	for(i=Arr->Upper()+1; i<= up; i++) {
	  if(i == up)
	    arr->SetValue(i, val);
	  else
	    arr->SetValue(i, 0);
	}
      } else if(indx < up) {//clip array : indx to be negative
	up = abs(indx);
	arr = new TColStd_HArray1OfReal(low, up);
	for(i=low; i< up; i++)
	  arr->SetValue(i, Arr->Value(i));
	arr->SetValue(up, val);
      }
      A->ChangeArray(arr);
    }
    return 0;
  }
  di << "DDataStd_ChangeRealArray: Error" << "\n";
  return 0; 
} 

//=======================================================================
//function : SetVariable (DF, entry, isConstant[0/1], units)
//=======================================================================
static Standard_Integer DDataStd_SetVariable (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg)
{
  if (nb == 5)
  {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label label;
    DDF::AddLabel(DF, arg[2], label);

    Handle(TDataStd_Variable) aV = TDataStd_Variable::Set(label);

    const char* aUnits = arg[4];
    aV->Unit(Standard_CString(aUnits));

    aV->Constant(Standard_Boolean(Draw::Atoi(arg[3])));
    return 0; 
  }

  di << "Wrong arguments" << "\n";  
  return 1; 
} 

//=======================================================================
//function : GetVariable (DF, entry, [isConstant], [units])
//=======================================================================
static Standard_Integer DDataStd_GetVariable (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg)
{
  if (nb == 5)
  {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label label;
    DDF::AddLabel(DF, arg[2], label);

    Handle(TDataStd_Variable) aV;
    if (!label.FindAttribute(TDataStd_Variable::GetID(), aV))
    {
      di << "TDataStd_Variable: no such attribute" << "\n";
    }

    Draw::Set(arg[3],TCollection_AsciiString(Standard_Integer(aV->IsConstant())).ToCString());
    Draw::Set(arg[4],aV->Unit().ToCString());
    return 0; 
  }

  di << "Wrong arguments" << "\n";  
  return 1; 
} 

#include <TDataStd_Relation.hxx>
#include <TDataStd_Variable.hxx>
//=======================================================================
//function : SetRelation (DF, entry, expression, var1[, var2, ...])
//=======================================================================
static Standard_Integer DDataStd_SetRelation (Draw_Interpretor& di,
                                              Standard_Integer nb, const char** arg) 
{
  if (nb >= 5)
  {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label label;
    DDF::AddLabel(DF, arg[2], label);

    Standard_CString expr (arg[3]);
    Handle(TDataStd_Relation) aR = TDataStd_Relation::Set(label);
    aR->SetRelation(expr);
    Handle(TDataStd_Variable) aV;

    for (Standard_Integer i = 4; i < nb; i++)
    {
      if (!DDF::FindLabel(DF, arg[i], label))
      {
        di << "No label for entry" << arg[i] << "\n";
        return 1;
      }
      if (!label.FindAttribute(TDataStd_Variable::GetID(), aV))
      {
        di << "No TDataStd_Variable Attribute on label" << "\n";
        return 1;
      }
      aR->GetVariables().Append(aV);
    }
    return 0;
  }
  di << "Usage: SetRelation (DF, entry, expression, var1[, var2, ...])" << "\n";
  return 1;
}

//=======================================================================
//function : DumpRelation (DF, entry)
//=======================================================================
static Standard_Integer DDataStd_DumpRelation (Draw_Interpretor& di,
                                               Standard_Integer nb, const char** arg) 
{
  if (nb == 3)
  {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;

    TDF_Label label;
    if (!DDF::FindLabel(DF, arg[2], label))
    {
      di << "No label for entry " << arg[2] << "\n";
      return 1;
    }
    Handle(TDataStd_Relation) aR;
    if (!label.FindAttribute(TDataStd_Relation::GetID(), aR))
    {
      di << "No TDataStd_Relation Attribute on label " << arg[2] << "\n";
      return 1;
    }

    di << "Relation: expression = \"" << aR->GetRelation()
       << "\" variables list = (";

    Handle(TDF_Attribute) aV;
    TCollection_AsciiString anEntry;

    TDF_ListIteratorOfAttributeList it;
    for (it.Initialize(aR->GetVariables()); it.More(); it.Next())
    {
      aV = it.Value(); 
      if (!aV.IsNull())
      {
        label = aV->Label();
        TDF_Tool::Entry(label, anEntry);
        di << anEntry.ToCString() << " ";
      }
    }
    di << ")";
    return 0;
  }
  di << "Usage: DumpRelation (DF, entry)" << "\n";
  return 1;
}

#include <TFunction_Function.hxx>
//=======================================================================
//function : SetFunction (DF, entry, guid, failure)
//=======================================================================
static Standard_Integer DDataStd_SetFunction (Draw_Interpretor& di,
                                              Standard_Integer nb, const char** arg)
{
  if (nb == 5)
  {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;
    TDF_Label label;
    DDF::AddLabel(DF, arg[2], label);

    Standard_GUID guid (arg[3]);
    Handle(TFunction_Function) aF = TFunction_Function::Set(label, guid);

    int fail = Draw::Atoi(arg[4]);
    aF->SetFailure(fail);

    return 0;
  }

  di << "Wrong arguments"  << "\n";
  return 1;
}

//=======================================================================
//function : GetFunction (DF, entry, guid(out), failure(out))
//=======================================================================
static Standard_Integer DDataStd_GetFunction (Draw_Interpretor& di,
                                              Standard_Integer nb, const char** arg) 
{   
  if (nb == 5)
  {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1; 
    TDF_Label label;
    if (!DDF::FindLabel(DF, arg[2], label))
    {
     di << "No label for entry"  << "\n";
     return 1;
    }

    Handle(TFunction_Function) aF;    
    if (!label.FindAttribute(TFunction_Function::GetID(), aF))
    {
      di << "No TFunction_Function Attribute on label" << "\n";
    }
    else
    {
      char *aStrGUID = new char[37];
      aF->GetDriverGUID().ToCString(aStrGUID);
      Draw::Set(arg[3],aStrGUID);

      Draw::Set(arg[4],TCollection_AsciiString(aF->GetFailure()).ToCString());
    }
    return 0;  
  }

  di << "Wrong arguments"  << "\n";  
  return 1;  
} 

//=======================================================================
//function : SetExtStringArray (DF, entry , isDelta, From, To,  elmt1, elmt2, ...
//=======================================================================
static Standard_Integer DDataStd_SetExtStringArray (Draw_Interpretor& di,
						    Standard_Integer, 
						    const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1; 
  TDF_Label label;
  DDF::AddLabel(DF, arg[2], label);
  Standard_Integer isDelta = Draw::Atoi(arg[3]);

  Standard_Integer From = Draw::Atoi(arg[4]), To = Draw::Atoi( arg[5] ), j;
  di << "Array of ExtString with bounds from = " << From  << " to = " << To  << "\n";
  Handle(TDataStd_ExtStringArray) A = TDataStd_ExtStringArray::Set(label, From, To, isDelta);
  
  j = 6;
  for(Standard_Integer i = From; i<=To; i++) {
    A->SetValue(i, arg[j] ); 
    j++;
  }

  return 0; 
} 

//=======================================================================
//function : GetExtStringArray (DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetExtStringArray (Draw_Interpretor& di,
						    Standard_Integer, 
						    const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1;  
  TDF_Label label;
  if( !DDF::FindLabel(DF, arg[2], label) ) {
    di << "No label for entry"  << "\n";
    return 1;
  }
 
  Handle(TDataStd_ExtStringArray) A;
  if ( !label.FindAttribute(TDataStd_ExtStringArray::GetID(), A) ) { 
    di << "There is no TDataStd_ExtStringArray under label"  << "\n";
    return 1;
  }
  
  TCollection_ExtendedString anExtendedString;
  TCollection_AsciiString anAsciiString;
  for(Standard_Integer i = A->Lower(); i<=A->Upper(); i++){
    anExtendedString = A->Value(i);
    anAsciiString = TCollection_AsciiString (A->Value(i),'?');
    //cout << anAsciiString.ToCString() << endl;
    di << anAsciiString.ToCString();
    if(i<A->Upper())  
      di<<" ";
  }
  di<<"\n";
  return 0; 
} 

//=======================================================================
//function : ChangeExtStrArray (DF, entry, indx, val )
//=======================================================================
static Standard_Integer DDataStd_ChangeExtStrArray (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if( nb == 5 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_ExtStringArray) A;
    if ( !label.FindAttribute(TDataStd_ExtStringArray::GetID(), A) ) { 
      di << "There is no TDataStd_ExtStringArray at label"  << "\n";
      return 1;
    }
    Standard_Integer indx = Draw::Atoi(arg[3]);
    TCollection_ExtendedString val(arg[4]);
    Standard_Integer low = A->Lower(), up = A->Upper();
    if(low <= indx && indx <= up)
      A->SetValue(indx, val);//TColStd_HArray1OfExtendedString
    else {
      Handle(TColStd_HArray1OfExtendedString) Arr = A->Array();
      Handle(TColStd_HArray1OfExtendedString) arr;
      Standard_Integer i;
      if(indx > up) {
	up = indx;
	arr = new TColStd_HArray1OfExtendedString(low, up);
	for(i=low; i<= Arr->Upper(); i++)
	  arr->SetValue(i, Arr->Value(i));
	for(i=Arr->Upper()+1; i<= up; i++) {
	  if(i == up)
	    arr->SetValue(i, val);
	  else
	    arr->SetValue(i, 0);
	}
      } else if(indx < up) {//clip array : indx to be negative
	up = abs(indx);
	arr = new TColStd_HArray1OfExtendedString(low, up);
	for(i=low; i< up; i++)
	  arr->SetValue(i, Arr->Value(i));
	arr->SetValue(up, val);
      }
      A->ChangeArray(arr);
    }    
    return 0;
  }
  di << "DDataStd_ChangeExtStringArray: Error" << "\n";
  return 0; 
} 


//=======================================================================
//function : DDataStd_KeepUTF
//purpose  : SetUTFName (DF, fatherEntry, fileName)
//=======================================================================
static Standard_Integer DDataStd_KeepUTF (Draw_Interpretor& di,
                                               Standard_Integer nb, 
                                               const char** arg) 
{
  if (nb == 4) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    DDF::AddLabel(DF, arg[2], L);
    Standard_CString aFileName(arg[3]);

#ifdef WNT
      ifstream anIS (aFileName, ios::in | ios::binary);
#else
      ifstream anIS (aFileName);
#endif
    if (!anIS) {
      // Can not open file
      cout << "Error: can't open file " << aFileName <<endl;;
      return 1;
    }
    char buf[1024];
    char *p;
    anIS.getline(buf, 1023,'\n');
    //    0xEFBBBF  -  prefix of UTF8 
    p = &buf[3]; //skip prefix
    TCollection_ExtendedString aES1(p, Standard_True);
    TDataStd_Name::Set(L.NewChild(), aES1);
 

    while (anIS.good() && !anIS.eof()) {
      anIS.getline(buf, 1023,'\n');
      TCollection_ExtendedString aES2(buf, Standard_True);
      const TDF_Label& aLab = L.NewChild();
      TDataStd_Name::Set(aLab, aES2);
    }
    return 0;
  }
  di << "SetUTFName : String is not kept in DF" << "\n";
  return 1;
}

//=======================================================================
//function : DDataStd_GetUTFtoFile
//purpose  : GetUTF (DF, fatherEntry, fileName)
//         : all strings from sub-labels of the <fatherEntry> concatenated
//         : in one, converted to UTF8 and kept in the file
//=======================================================================
static Standard_Integer DDataStd_GetUTFtoFile (Draw_Interpretor& di,
                                               Standard_Integer nb, 
                                               const char** arg) 
{
  if (nb == 4) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    if (!DDF::FindLabel(DF,arg[2],L)) return 1;

    TCollection_ExtendedString aES;
    Standard_Boolean aF = Standard_False;
    TDF_ChildIterator anIt(L);
    for(;anIt.More();anIt.Next()) {
      const TDF_Label& aLab = anIt.Value();
      if(!aLab.IsNull()) {
	Handle(TDataStd_Name) anAtt;
	if(aLab.FindAttribute(TDataStd_Name::GetID(), anAtt)) {
	  if(anAtt->Get().Length()) { 
	    if (aF)
	      aES +='\n';	  
	    aES +=anAtt->Get();	
	    aF = Standard_True;
	  }
	}
      }
    }

    if(!aES.Length()) {
      cout << "Data is not found in the Document" <<endl;
      return 1;
    }

    Standard_CString aFileName(arg[3]);

#ifdef WNT
    ofstream anOS (aFileName, ios::in | ios::binary | ios::ate);
#else
    ofstream anOS (aFileName, ios::ate);
#endif
    if (!anOS) {
      // A problem with the stream
#ifdef DEB
      cout << "Error: problem with the file stream, rdstate = " <<anOS.rdstate() <<endl;
#endif
    }
    unsigned char prefix[4] = {0xEF,0xBB,0xBF, 0x00};
    anOS.write( reinterpret_cast<const char*>(&prefix[0]), 3); 
    Standard_Integer  n = aES.LengthOfCString();
    Standard_PCharacter aCstr = (Standard_PCharacter) Standard::Allocate(ROUNDMEM(n+1));
    n = aES.ToUTF8CString(aCstr);
    anOS.write( reinterpret_cast<const char*>(&aCstr[0]), n); 
    anOS.close();
    return 0;
  }
  di << "GetUTF : Data is not extracted to the specified file " <<"\n";
  return 1;
}

//=======================================================================
//function : SetByteArray (DF, entry, isDelta, From, To, elmt1, elmt2, ...  )
//=======================================================================
static Standard_Integer DDataStd_SetByteArray (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb > 6) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label label;
    DDF::AddLabel(DF, arg[2], label);
    Standard_Integer isDelta = Draw::Atoi(arg[3]);
    Standard_Integer From = Draw::Atoi(arg[4]), To = Draw::Atoi( arg[5] ), j;
    di << "Array of Standard_Integer with bounds from = " << From  << " to = " << To  << "\n";
    Handle(TDataStd_ByteArray) A = TDataStd_ByteArray::Set(label, From, To, isDelta);
    
    j = 6;
    for(Standard_Integer i = From; i<=To; i++) {
      Standard_Integer ival = Draw::Atoi(arg[j]);
      if(ival > 255) {
	cout << "Bad value = " << ival<< endl;
	return 1;
      }
      A->SetValue(i,  (Standard_Byte)(unsigned)ival); 
      j++;
    }
    return 0; 
  }
  di << "DDataStd_SetByteArray: Error" << "\n";
  return 1; 
} 

//=======================================================================
//function : GetByteArray (DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetByteArray (Draw_Interpretor& di,
                                              Standard_Integer, 
                                              const char** arg) 
{   


  Handle(TDF_Data) DF;
  if (!DDF::GetDF(arg[1],DF))  return 1;  
  TDF_Label label;
  if( !DDF::FindLabel(DF, arg[2], label) ) {
    di << "No label for entry"  << "\n";
    return 1;
  }
 
  Handle(TDataStd_ByteArray) A;
  if ( !label.FindAttribute(TDataStd_ByteArray::GetID(), A) ) { 
    di << "There is no TDataStd_ByteArray at label"  << "\n";
    return 1;
  }
  
  for(Standard_Integer i = A->Lower(); i<=A->Upper(); i++){
    //cout <<  A->Value(i)   << endl;
    di  <<  A->Value(i);
    if(i<A->Upper())  
     di<<" ";
  }
  di<<"\n";
  return 0; 
} 

//=======================================================================
//function : ChangeByteArray (DF, entry, indx, val )
//=======================================================================
static Standard_Integer DDataStd_ChangeByteArray (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if( nb == 5 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_ByteArray) A;
    if ( !label.FindAttribute(TDataStd_ByteArray::GetID(), A) ) { 
      di << "There is no TDataStd_ByteArray at label"  << "\n";
      return 1;
    }
    Standard_Integer indx = Draw::Atoi(arg[3]);
    Standard_Integer ival  = Draw::Atoi(arg[4]);
    if (ival > 255 || ival < 0) {
        di << "DDataStd_ChangeByteArray: Bad value = " <<ival << "\n";
	return 1;
      }
    Standard_Integer low = A->Lower(), up = A->Upper();
    if(low <= indx && indx <= up)
      A->SetValue(indx, (Standard_Byte)(unsigned)ival);
    else {
      Handle(TColStd_HArray1OfByte) Arr = A->InternalArray();
      Handle(TColStd_HArray1OfByte) arr;
      Standard_Integer i;
      if(indx > up) {
	up = indx;
	arr = new TColStd_HArray1OfByte(low, up);
	for(i=low; i<= Arr->Upper(); i++)
	  arr->SetValue(i, Arr->Value(i));
	for(i=Arr->Upper()+1; i<= up; i++) {
	  if(i == up)
	    arr->SetValue(i, (Standard_Byte)(unsigned)ival);
	  else
	    arr->SetValue(i, 0);
	}
      } else if(indx < up) {//clip array : indx to be negative
	up = abs(indx);
	arr = new TColStd_HArray1OfByte(low, up);
	for(i=low; i< up; i++)
	  arr->SetValue(i, Arr->Value(i));
	arr->SetValue(up, (Standard_Byte)(unsigned)ival);
      }
      A->ChangeArray(arr);
    }
    return 0;
  }
  di << "DDataStd_ChangeByteArray: Error" << "\n";
  return 1; 
}
//=======================================================================
//function : SetIntPackedMap (DF, entry, isDelta, key1, key2, ...
//=======================================================================

static Standard_Integer DDataStd_SetIntPackedMap (Draw_Interpretor& di,
						  Standard_Integer nb, 
						  const char** arg) 
{   

  if (nb > 4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
    Standard_Integer isDelta = Draw::Atoi(arg[3]);
    Standard_Integer aNum = nb - 4;
    Handle(TDataStd_IntPackedMap) anAtt;
    if(!aLabel.FindAttribute(TDataStd_IntPackedMap::GetID(), anAtt))
      anAtt = TDataStd_IntPackedMap::Set(aLabel, isDelta);
    if(anAtt.IsNull()) {
      di << "IntPackedMap attribute is not found or not set"  << "\n";
      return 1;}
    
    Standard_Integer j = 4;
    TColStd_PackedMapOfInteger aMap;
    for(Standard_Integer i = 1; i<=aNum; i++) {
      aMap.Add (Draw::Atoi(arg[j]));
      j++;
    }
    const Handle(TColStd_HPackedMapOfInteger) aHMap = new TColStd_HPackedMapOfInteger(aMap);
    anAtt->ChangeMap(aHMap);
    cout << "Map extent = " << anAtt->Extent()<<endl;
    return 0; 
  }
  di << "DDataStd_SetIntPackedMap : Error" << "\n";
  return 1;
} 

//=======================================================================
//function : GetIntPackedMap (DF, entry )
//=======================================================================

static Standard_Integer DDataStd_GetIntPackedMap (Draw_Interpretor& di,
						  Standard_Integer nb, 
						  const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
    Handle(TDataStd_IntPackedMap) anAtt;
    if(!aLabel.FindAttribute(TDataStd_IntPackedMap::GetID(), anAtt)) {
      di << "IntPackedMap attribute is not found or not set"  << "\n";
      return 1;}
//
    const TColStd_PackedMapOfInteger& aMap = anAtt->GetMap();
    TColStd_MapIteratorOfPackedMapOfInteger itr(aMap);
    for (Standard_Integer j = 1; itr.More(); itr.Next(),j++){
      Standard_Integer aKey(itr.Key());
      cout << "Key ("<< j <<")"<<" = " << aKey << endl;;
      }
    return 0; 
  }
  di << "DDataStd_GetIntPackedMap : Error" << "\n";
  return 1;
} 


//=======================================================================
//function : ChangeIntPackedMap_Add (DF, entry, Key1, Key2,... )
//=======================================================================
static Standard_Integer DDataStd_ChangeIntPackedMap_Add (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if( nb >= 4 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_IntPackedMap) A;
    if ( !label.FindAttribute(TDataStd_IntPackedMap::GetID(), A) ) { 
      di << "There is no TDataStd_IntPackedMap at label"  << "\n";
      return 1;
    }
    
    Standard_Integer i, aNum = nb - 3; 
    Handle(TColStd_HPackedMapOfInteger) aHMap = A->GetHMap();
    Handle(TColStd_HPackedMapOfInteger) ahMap = new TColStd_HPackedMapOfInteger();
    if(!aHMap.IsNull()) {
      ahMap->ChangeMap().Assign(aHMap->Map());
      for(i=1; i<=aNum;i++) {
	Standard_Integer val = Draw::Atoi(arg[i+2]);
	if(!ahMap->Map().Contains(val))
	  ahMap->ChangeMap().Add(val);
      }
      
      A->ChangeMap(ahMap);
    }
    return 0;
  }
  di << "DDataStd_ChangeIntPackedMap_Add: Error" << "\n";
  return 0; 
}


//=======================================================================
//function : ChangeIntPackedMap_Rem (DF, entry, Key1, Key2,... )
//=======================================================================
static Standard_Integer DDataStd_ChangeIntPackedMap_Rem (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if( nb >= 4 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_IntPackedMap) A;
    if ( !label.FindAttribute(TDataStd_IntPackedMap::GetID(), A) ) { 
      di << "There is no TDataStd_IntPackedMap at label"  << "\n";
      return 1;
    }
    
    Standard_Integer i, aNum = nb - 3; 
    Handle(TColStd_HPackedMapOfInteger) aHMap = A->GetHMap();
    Handle(TColStd_HPackedMapOfInteger) ahMap = new TColStd_HPackedMapOfInteger();
    if(!aHMap.IsNull()) {
      ahMap->ChangeMap().Assign(aHMap->Map());
      for(i=1; i<=aNum;i++) {
	Standard_Integer val = Draw::Atoi(arg[i+2]);
	if(ahMap->Map().Contains(val))
	  ahMap->ChangeMap().Remove(val);
      }
      
      A->ChangeMap(ahMap);
    }
    return 0;
  }
  di << "DDataStd_ChangeIntPackedMap_Rem: Error" << "\n";
  return 0; 
}

//=======================================================================
//function : ChangeIntPackedMap_AddRem (DF, entry, Key1, Key2,... )
//         : if Keyi exist in map - remove it, if no - add
//=======================================================================
static Standard_Integer DDataStd_ChangeIntPackedMap_AddRem (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if( nb >= 4 ) {  
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1;  
    TDF_Label label;
    if( !DDF::FindLabel(DF, arg[2], label) ) {
      di << "No label for entry"  << "\n";
      return 1;
    }
 
    Handle(TDataStd_IntPackedMap) A;
    if ( !label.FindAttribute(TDataStd_IntPackedMap::GetID(), A) ) { 
      di << "There is no TDataStd_IntPackedMap at label"  << "\n";
      return 1;
    }
    
    Standard_Integer i, aNum = nb - 3; 
    Handle(TColStd_HPackedMapOfInteger) aHMap = A->GetHMap();
    Handle(TColStd_HPackedMapOfInteger) ahMap = new TColStd_HPackedMapOfInteger();
    if(!aHMap.IsNull()) {
      ahMap->ChangeMap().Assign(aHMap->Map());
      for(i=1; i<=aNum;i++) {
	Standard_Integer val = Draw::Atoi(arg[i+2]);
	if(!ahMap->Map().Contains(val))
	  ahMap->ChangeMap().Add(val);
	else
	  ahMap->ChangeMap().Remove(val);
      }
      
      A->ChangeMap(ahMap);
    }
    return 0;
  }
  di << "DDataStd_ChangeIntPackedMap_AddRem: Error" << "\n";
  return 0; 
}

//=======================================================================
//function : SetIntPHugeMap (DF, entry, isDelta Num)
//=======================================================================

static Standard_Integer DDataStd_SetIntPHugeMap (Draw_Interpretor& di,
						  Standard_Integer nb, 
						  const char** arg) 
{   

  if (nb > 4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
    Standard_Integer isDelta = Draw::Atoi(arg[3]);
    Standard_Integer aNum = Draw::Atoi(arg[4]);
    Handle(TDataStd_IntPackedMap) anAtt;
    if(!aLabel.FindAttribute(TDataStd_IntPackedMap::GetID(), anAtt))
      anAtt = TDataStd_IntPackedMap::Set(aLabel, isDelta);
    if(anAtt.IsNull()) {
      di << "IntPackedMap attribute is not found or not set"  << "\n";
      return 1;}
    
    TColStd_PackedMapOfInteger aMap;
    for(Standard_Integer i = 1; i<=aNum; i++) {
      aMap.Add (i);
    }
    const Handle(TColStd_HPackedMapOfInteger) aHMap = new TColStd_HPackedMapOfInteger(aMap);
    anAtt->ChangeMap(aHMap);
    cout << "Map extent = " << anAtt->Extent()<<endl;
    return 0; 
  }
  di << "DDataStd_SetIntPHugeMap : Error" << "\n";
  return 1;
}

//=======================================================================
//function : SetNDataIntegers (DF, entry , Num
//=======================================================================

static Standard_Integer DDataStd_SetNDataIntegers2 (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb ==4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
    Standard_Integer aNumP = Draw::Atoi(arg[3]), j;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      di << "NamedData attribute is not found or not set"  << "\n";
      return 1;}
  
    j = 1111;
    TCollection_ExtendedString aKey("Key_");
    for(Standard_Integer i = 1; i<=aNumP; i++) {
      TCollection_ExtendedString key = aKey + i;
      Standard_Integer aVal = j+i;
      anAtt->SetInteger(key, aVal); 
      j +=1;
    }    
    return 0; 
  }
  di << "DDataStd_SetNDataIntegers2 : Error" << "\n";
  return 1;
} 
//================
//=======================================================================
//function : SetNDataIntArrays2 (DF, entry , key, NumOfArElem )
//=======================================================================

static Standard_Integer DDataStd_SetNDataIntAr2 (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb == 5) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
 
    Standard_Integer j;
    TCollection_ExtendedString aKey(arg[3]);
    Standard_Integer aNum = Draw::Atoi(arg[4]);
    if (aNum <= 0) return 1;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      cout<< "NamedData attribute is not found or not set"  << endl;
      return 1;}
  
    j = 15;
    Handle(TColStd_HArray1OfInteger) anArr =  new TColStd_HArray1OfInteger(1, aNum);
    for(Standard_Integer i = 1; i<=aNum; i++) {
      Standard_Integer aVal = j++;
      anArr->SetValue(i, aVal);
      j++;
    }
    anAtt->SetArrayOfIntegers(aKey, anArr); 
    return 0; 
  }
  di << "DDataStd_SetNDataIntArrays2 : Error" << "\n";
  return 1;
} 


//=======================================================================
//function :  SetAsciiString(DF, entry , String)
//=======================================================================

static Standard_Integer DDataStd_SetAsciiString (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb ==4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
    TCollection_AsciiString aString(arg[3]);
    Handle(TDataStd_AsciiString) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_AsciiString::Set(aLabel, aString);
    if(anAtt.IsNull()) {
      di << "AsciiString attribute is not found or not set"  << "\n";
      return 1;}
  
//    anAtt->Set(aString);
    cout << "String = " << anAtt->Get().ToCString() << " is kept in DF" << endl;
    return 0; 
  }
  di << "DDataStd_SetAsciiString : Error" << "\n";
  return 1;
} 
//
//=======================================================================
//function :  GetAsciiString(DF, entry )
//=======================================================================

static Standard_Integer DDataStd_GetAsciiString (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb ==3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
    Handle(TDataStd_AsciiString) anAtt;
    if(!aLabel.FindAttribute(TDataStd_AsciiString::GetID(), anAtt)) {
      cout << "AsciiString attribute is not found or not set"  << endl;
      return 1;
    }
    cout << "String = " <<anAtt->Get().ToCString()  << endl;
    return 0; 
  }
  di << "DDataStd_GetAsciiString : Error" << "\n";
  return 1;
} 

//=======================================================================
//function : SetNDataIntegers (DF, entry , Num,  key1, val1, ...
//=======================================================================

static Standard_Integer DDataStd_SetNDataIntegers (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb >=6) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
//
//     TCollection_ExtendedString aString("123456789 0_abcde");
//     Standard_Integer aPos = aString.Search(" ");
//     cout << "From Start = " <<aPos<<endl;
//     aPos = aString.SearchFromEnd(" ");
//     cout << "From Start = " <<aPos<<endl;
//     TCollection_ExtendedString aValue = aString.Split(aPos);
//     cout << "Value = |"<<aValue<<endl;
//     cout << "aKey = " << aString << "|"<<endl;
// 
    Standard_Integer aNumP = Draw::Atoi(arg[3]), j;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      di << "NamedData attribute is not found or not set"  << "\n";
      return 1;}
  
    j = 4;
    for(Standard_Integer i = 1; i<=aNumP; i++) {
      TCollection_ExtendedString aKey(arg[j]);
      Standard_Integer aVal = Draw::Atoi(arg[j+1]);
      anAtt->SetInteger(aKey, aVal); 
      j +=2;
    }    
    return 0; 
  }
  di << "DDataStd_SetNDataIntegers : Error" << "\n";
  return 1;
} 


//=======================================================================
//function :  GetNDIntegers(DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetNDIntegers (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;
    const TColStd_DataMapOfStringInteger& aMap = anAtt->GetIntegersContainer();
    TColStd_DataMapIteratorOfDataMapOfStringInteger itr(aMap);
    for (; itr.More(); itr.Next()){
      TCollection_ExtendedString aKey(itr.Key());
      TCollection_AsciiString aStr(aKey,'?');
      Standard_Integer aValue = itr.Value();
       cout << "Key = "  << aStr.ToCString() << " Value = " <<aValue<<endl;;
      }

    return 0; 
  }
  di << "DDataStd_GetNDIntegers : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDInteger(DF, entry, key [drawname])
//=======================================================================
static Standard_Integer DDataStd_GetNDInteger (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb >=4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}

    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;    
    if(!anAtt->HasInteger(arg[3])) {
      cout << "There is no data specified by Key = "<< arg[3]  << endl;
      return 1;
    } else {
      cout << "Key = "  << arg[3]  << " Value = " <<anAtt->GetInteger(arg[3])<<endl;
      if(nb == 5) 
	Draw::Set(arg[4], anAtt->GetInteger(arg[3]));
      return 0; 
    }
  }
  di << "DDataStd_SetNDataIntegers : Error" << "\n";
  return 1;
} 

//========================== REALS ======================================
//=======================================================================
//function : SetNDataReals (DF, entry , Num,  key1, val1, ...
//=======================================================================

static Standard_Integer DDataStd_SetNDataReals (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb >=6) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
 
    Standard_Integer aNumP = Draw::Atoi(arg[3]), j;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      cout << "NamedData attribute is not found or not set"  << endl;;
      return 1;}
  
    j = 4;
    for(Standard_Integer i = 1; i<=aNumP; i++) {
      TCollection_ExtendedString aKey(arg[j]);
      Standard_Real aVal = Draw::Atof(arg[j+1]);
      anAtt->SetReal(aKey, aVal); 
      j +=2;
    }    
    return 0; 
  }
  di << "DDataStd_SetNDataReals : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDReals(DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetNDReals (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 
    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
    
    const TDataStd_DataMapOfStringReal& aMap = anAtt->GetRealsContainer();
    TDataStd_DataMapIteratorOfDataMapOfStringReal itr(aMap);
    for (; itr.More(); itr.Next()){
      TCollection_ExtendedString aKey(itr.Key());
      TCollection_AsciiString aStr(aKey,'?');
      Standard_Real aValue = itr.Value();
       cout << "Key = "  << aStr.ToCString() << " Value = " <<aValue<<endl;
      }
    return 0; 
  }
  di << "DDataStd_GetNDReals : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDReal(DF, entry, key [drawname])
//=======================================================================
static Standard_Integer DDataStd_GetNDReal (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb >=4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}

    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;    
    if(!anAtt->HasReal(arg[3])) {
      cout << "There is no data specified by Key = "<< arg[3]  << endl;
      return 1;
    } else {
      cout << "Key = "  << arg[3]  << " Value = " <<anAtt->GetReal(arg[3])<<endl;
      if(nb == 5) 
	Draw::Set(arg[4], anAtt->GetReal(arg[3]));
      return 0; 
    }
  }
  di << "DDataStd_GetNDReal : Error" << "\n";
  return 1;
} 

//======================= Strings =======================================
//=======================================================================
//function : SetNDataStrings (DF, entry , Num,  key1, val1, ...
//=======================================================================

static Standard_Integer DDataStd_SetNDataStrings (Draw_Interpretor& di,
						  Standard_Integer nb, 
						  const char** arg) 
{   

  if (nb >=6) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
 
    Standard_Integer aNumP = Draw::Atoi(arg[3]), j;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      di << "NamedData attribute is not found or not set"  << "\n";
      return 1;}
  
    j = 4;
    for(Standard_Integer i = 1; i<=aNumP; i++) {
      TCollection_ExtendedString aKey(arg[j]);
      TCollection_ExtendedString aVal(arg[j+1]);
      anAtt->SetString(aKey, aVal); 
      j +=2;
    }    
    return 0; 
  }
  di << "DDataStd_SetNDataStrings : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDStrings(DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetNDStrings (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;    
    const TDataStd_DataMapOfStringString& aMap = anAtt->GetStringsContainer();
    TDataStd_DataMapIteratorOfDataMapOfStringString itr(aMap);
    for (; itr.More(); itr.Next()){
      TCollection_ExtendedString aKey(itr.Key());
      TCollection_AsciiString aStr(aKey,'?');
      TCollection_ExtendedString aVal(itr.Value());
      TCollection_AsciiString aStrValue(aVal,'?');
      cout << "Key = "  << aStr.ToCString() << " Value = " <<aStrValue.ToCString()<< endl;
      }
    return 0; 
  }
  di << "DDataStd_GetNDStrings : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDString(DF, entry, key [drawname])
//=======================================================================
static Standard_Integer DDataStd_GetNDString (Draw_Interpretor& di,
					      Standard_Integer nb, 
					      const char** arg) 
{   

  if (nb >=4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      di << "NamedData attribute is not found or not set"  << "\n";
      return 1;}

    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;    
    if(!anAtt->HasString(arg[3])) {
      cout << "There is no data specified by Key = "<< arg[3]  << endl;
      return 1;
    } else {
      TCollection_AsciiString aValue (anAtt->GetString(arg[3]), '?');
      cout << "Key = "  << arg[3]  << " Value = " << aValue.ToCString() << endl;
      if(nb == 5) 
	Draw::Set(arg[4], aValue.ToCString());
      return 0; 
    }
  }
  di << "DDataStd_GetNDString : Error" << "\n";
  return 1;
} 

//=========================== Bytes =====================================
//=======================================================================
//function : SetNDataBytes (DF, entry , Num,  key1, val1, ...
//=======================================================================

static Standard_Integer DDataStd_SetNDataBytes (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb >=6) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
 
    Standard_Integer aNumP = Draw::Atoi(arg[3]), j;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
  
    j = 4;
    for(Standard_Integer i = 1; i<=aNumP; i++) {
      TCollection_ExtendedString aKey(arg[j]);
      Standard_Byte aVal = (Standard_Byte)Draw::Atoi(arg[j+1]);
      anAtt->SetByte(aKey, aVal); 
      j +=2;
    }    
    return 0; 
  }
  di << "DDataStd_SetNDataBytes : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDBytes(DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetNDBytes (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;      
    const TDataStd_DataMapOfStringByte& aMap = anAtt->GetBytesContainer();
    TDataStd_DataMapIteratorOfDataMapOfStringByte itr(aMap);
    for (; itr.More(); itr.Next()){
      TCollection_ExtendedString aKey(itr.Key());
      TCollection_AsciiString aStr(aKey,'?');
      Standard_Byte aValue = itr.Value();
      cout << "Key = "  << aStr.ToCString() << " Value = " <<aValue<<endl;
      }
    return 0; 
  }
  di << "DDataStd_GetNDBytes : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDByte(DF, entry, key [drawname])
//=======================================================================
static Standard_Integer DDataStd_GetNDByte (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb >=4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}

    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;      
    if(!anAtt->HasByte(arg[3])) {
      cout << "There is no data specified by Key = "<< arg[3]  << endl;
      return 1;
    } else {
      cout << "Key = "  << arg[3]  << " Value = " <<anAtt->GetByte(arg[3])<< endl;
      if(nb == 5) 
	Draw::Set(arg[4], anAtt->GetByte(arg[3]));
      return 0; 
    }
  }
  di << "DDataStd_GetNDByte : Error" << "\n";
  return 1;
} 
//======================== IntArrays ====================================
//=======================================================================
//function : SetNDataIntArrays (DF, entry , key, NumOfArElem, val1, val2,...  )
//=======================================================================

static Standard_Integer DDataStd_SetNDataIntAr (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb >=6) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
 
    Standard_Integer j;
    TCollection_ExtendedString aKey(arg[3]);
    Standard_Integer aNum = Draw::Atoi(arg[4]);
    if (aNum <= 0) return 1;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      cout<< "NamedData attribute is not found or not set"  << endl;
      return 1;}
  
    j = 5;
    Handle(TColStd_HArray1OfInteger) anArr =  new TColStd_HArray1OfInteger(1, aNum);
    for(Standard_Integer i = 1; i<=aNum; i++) {
      Standard_Integer aVal = Draw::Atoi(arg[j]);
      anArr->SetValue(i, aVal);
      j++;
    }
    anAtt->SetArrayOfIntegers(aKey, anArr); 
    return 0; 
  }
  di << "DDataStd_SetNDataIntArrays : Error" << "\n";
  return 1;
} 


//=======================================================================
//function :  GetNDIntArrays(DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetNDIntArrays (Draw_Interpretor& di,
						 Standard_Integer nb, 
						 const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
    
    
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;      
    const TDataStd_DataMapOfStringHArray1OfInteger& aMap = anAtt->GetArraysOfIntegersContainer();
    TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfInteger itr(aMap);
    for (; itr.More(); itr.Next()){
      TCollection_ExtendedString aKey(itr.Key());
      TCollection_AsciiString aStr(aKey,'?');
      cout << "Key = "  << aStr.ToCString()<< endl;
      Handle(TColStd_HArray1OfInteger) anArrValue = itr.Value();      
      if(!anArrValue.IsNull()) {
	Standard_Integer lower = anArrValue->Lower();
	Standard_Integer upper = anArrValue->Upper();
	for(Standard_Integer i = lower; i<=upper;i++) {
	  Standard_Integer aValue = anArrValue->Value(i);
	  cout << "\tValue("<<i<<")"<<" = " <<aValue<<endl;
	}
      } else 
	 cout << "\tthe specified array is Null "<<endl;
    }
    return 0; 
  }
  di << "DDataStd_GetNDIntArrays : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDIntArray(DF, entry, key )
//=======================================================================
static Standard_Integer DDataStd_GetNDIntArray (Draw_Interpretor& di,
						Standard_Integer nb, 
						const char** arg) 
{   

  if (nb >=4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}

    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;      
    if(!anAtt->HasArrayOfIntegers(arg[3])) {
      cout << "There is no data specified by Key = "<< arg[3]  << endl;
      return 1;
    } else {
      cout << "Key = "  << arg[3] <<endl;

      Handle(TColStd_HArray1OfInteger) anArrValue = anAtt->GetArrayOfIntegers(arg[3]);      
      if(!anArrValue.IsNull()) {
	Standard_Integer lower = anArrValue->Lower();
	Standard_Integer upper = anArrValue->Upper();
	for(Standard_Integer i = lower; i<=upper;i++) {
	  Standard_Integer aValue = anArrValue->Value(i);
	  cout << "\tValue("<<i<<")"<<" = " <<aValue<<endl;
	}
      } else 
	cout << "\tthe specified array is Null or not found"<<endl;
      return 0; 
    }
  }
  di << "DDataStd_SetNDataIntArray : Error" << "\n";
  return 1;
} 
//============================= RealArrays ==============================
//=======================================================================
//function : SetNDataRealArrays (DF entry key NumOfArElem val1 val2...  )
//=======================================================================

static Standard_Integer DDataStd_SetNDataRealAr (Draw_Interpretor& di,
                                              Standard_Integer nb, 
                                              const char** arg) 
{   

  if (nb >=6) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    DDF::AddLabel(DF, arg[2], aLabel);
 
    Standard_Integer j;
    TCollection_ExtendedString aKey(arg[3]);
    Standard_Integer aNum = Draw::Atoi(arg[4]);
    if (aNum <= 0) return 1;
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt))
      anAtt = TDataStd_NamedData::Set(aLabel);
    if(anAtt.IsNull()) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
  
    j = 5;
    Handle(TColStd_HArray1OfReal) anArr =  new TColStd_HArray1OfReal(1, aNum);
    for(Standard_Integer i = 1; i<=aNum; i++) {
      Standard_Real aVal = Draw::Atof(arg[j]);
      anArr->SetValue(i, aVal);
      j++;
    }
    anAtt->SetArrayOfReals(aKey, anArr); 
    return 0; 
  }
  di << "DDataStd_SetNDataRealArrays : Error" << "\n";
  return 1;
} 


//=======================================================================
//function :  GetNDRealArrays(DF, entry )
//=======================================================================
static Standard_Integer DDataStd_GetNDRealArrays (Draw_Interpretor& di,
						  Standard_Integer nb, 
						  const char** arg) 
{   

  if (nb == 3) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
    
    
    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      cout << "NamedData attribute is not found or not set"  << endl;
      return 1;}
    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;      
    const TDataStd_DataMapOfStringHArray1OfReal& aMap = anAtt->GetArraysOfRealsContainer();
    TDataStd_DataMapIteratorOfDataMapOfStringHArray1OfReal itr(aMap);
    for (; itr.More(); itr.Next()){
      TCollection_ExtendedString aKey(itr.Key());
      TCollection_AsciiString aStr(aKey,'?');
      cout << "Key = "  << aStr.ToCString()<<endl;
      Handle(TColStd_HArray1OfReal) anArrValue = itr.Value();      
      if(!anArrValue.IsNull()) {
	Standard_Integer lower = anArrValue->Lower();
	Standard_Integer upper = anArrValue->Upper();
	for(Standard_Integer i = lower; i<=upper;i++) {
	  Standard_Real aValue = anArrValue->Value(i);
	  cout << "\tValue("<<i<<")"<<" = " <<aValue<<endl;
	}
      } else 
	 cout << "\tthe specified array is Null "<<endl;
    }
    return 0; 
  }
  di << "DDataStd_GetNDRealArrays : Error" << "\n";
  return 1;
} 

//=======================================================================
//function :  GetNDRealArray(DF, entry, key )
//=======================================================================
static Standard_Integer DDataStd_GetNDRealArray (Draw_Interpretor& di,
						 Standard_Integer nb, 
						 const char** arg) 
{   

  if (nb >=4) {
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF))  return 1; 
    TDF_Label aLabel;
    if(!DDF::FindLabel(DF, arg[2], aLabel)) return 1;
 

    Handle(TDataStd_NamedData) anAtt;
    if(!aLabel.FindAttribute(TDataStd_NamedData::GetID(), anAtt)) {
      di << "NamedData attribute is not found or not set"  << "\n";
      return 1;}

    cout <<endl;
    cout <<"NamedData attribute at Label = " << arg[2] <<endl;      
    if(!anAtt->HasArrayOfReals(arg[3])) {
      cout << "There is no data specified by Key = "<< arg[3]  << endl;
      return 1;
    } else {
      cout << "Key = "  << arg[3] <<endl;

      Handle(TColStd_HArray1OfReal) anArrValue = anAtt->GetArrayOfReals(arg[3]);      
      if(!anArrValue.IsNull()) {
	Standard_Integer lower = anArrValue->Lower();
	Standard_Integer upper = anArrValue->Upper();
	for(Standard_Integer i = lower; i<=upper;i++) {
	  Standard_Real aValue = anArrValue->Value(i);
	  cout << "\tValue("<<i<<")"<<" = " <<aValue<<endl;
	}
      } else 
	cout << "\tthe specified array is Null or not found"<<endl;
      return 0; 
    }
  }
  di << "DDataStd_SetNDataRealArray : Error" << "\n";
  return 1;
}

//=======================================================================
//function : BasicCommands
//purpose  : 
//=======================================================================

void DDataStd::BasicCommands (Draw_Interpretor& theCommands)
{  

  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  const char* g = "DData : Standard Attribute Commands";


  // SET

  theCommands.Add ("SetInteger", 
                   "SetInteger (DF, entry, value)",
                   __FILE__, DDataStd_SetInteger, g);

  theCommands.Add ("SetIntArray", 
                   "SetIntArray (DF, entry, isDelta, From, To, elmt1, elmt2, ...  )",
                   __FILE__, DDataStd_SetIntArray, g);
  
  theCommands.Add ("SetReal", 
                   "SetReal (DF, entry, value)",
                   __FILE__, DDataStd_SetReal, g); 

  theCommands.Add ("SetRealArray", 
                   "SetRealArray (DF, entry, isDelta, From, To, elmt1, elmt2, ...  )",
                   __FILE__, DDataStd_SetRealArray, g);

  theCommands.Add ("SetByteArray", 
                   "SetByteArray (DF, entry, isDelta, From, To, elmt1, elmt2, ...  )",
                   __FILE__, DDataStd_SetByteArray, g);

  theCommands.Add ("SetExtStringArray", 
                   "SetExtStringArray (DF, entry, isDelta, From, To, elmt1, elmt2, ...  )",
                   __FILE__, DDataStd_SetExtStringArray, g);

  theCommands.Add ("SetIntPackedMap", 
                   "SetIntPackedMap (DF, entry, isDelta, key1, key2, ...  )",
                   __FILE__, DDataStd_SetIntPackedMap, g);

  theCommands.Add ("SetReference", 
                   "SetReference (DF, entry, reference)",
                   __FILE__, DDataStd_SetReference, g);  

  theCommands.Add ("SetComment", 
                   "SetComment (DF, entry, comment)",
                   __FILE__, DDataStd_SetComment, g);    
  
  theCommands.Add ("SetUAttribute", 
                   "SetUAttribute (DF, entry, LocalID)",
                   __FILE__, DDataStd_SetUAttribute, g);

  theCommands.Add ("SetVariable", 
                   "SetVariable (DF, entry, isConstant[0/1], units)",
                   __FILE__, DDataStd_SetVariable, g);

  theCommands.Add ("SetAsciiString", 
                   "SetAsciiString (DF, entry, String  )",
                   __FILE__, DDataStd_SetAsciiString, g);


  // GET

  theCommands.Add ("GetAsciiString", 
                   "GetAsciiString (DF, entry  )",
                   __FILE__, DDataStd_GetAsciiString, g);

  theCommands.Add ("GetInteger", 
                   "GetInteger (DF, entry, [drawname])",
                    __FILE__, DDataStd_GetInteger, g);

  theCommands.Add ("GetIntArray", 
                   "GetIntArray (DF, entry )",
                   __FILE__, DDataStd_GetIntArray, g);

  theCommands.Add ("GetRealArray", 
                   "GetRealArray (DF, entry )",
                   __FILE__, DDataStd_GetRealArray, g);


  theCommands.Add ("GetByteArray", 
                   "GetByteArray (DF, entry )",
                   __FILE__, DDataStd_GetByteArray, g);

  theCommands.Add ("GetExtStringArray", 
                   "GetExtStringArray (DF, entry )",
                   __FILE__, DDataStd_GetExtStringArray, g);

  theCommands.Add ("GetIntPackedMap", 
                   "GetIntPackedMap (DF, entry  )",
                   __FILE__, DDataStd_GetIntPackedMap, g);

  theCommands.Add ("GetReal", 
                   "GetReal (DF, entry, [drawname])",
                    __FILE__, DDataStd_GetReal, g);  

  theCommands.Add ("GetReference", 
                   "GetReference (DF, entry)",
                   __FILE__, DDataStd_GetReference, g);

  
  theCommands.Add ("GetComment", 
                   "GetComment (DF, entry)",
                   __FILE__, DDataStd_GetComment, g); 

  theCommands.Add("Self", 
                  "Self(document, entry)", 
                  __FILE__, DDataStd_Self, g);  

  theCommands.Add ("GetUAttribute", 
                   "GetUAttribute (DF, entry)",
                   __FILE__, DDataStd_GetUAttribute, g);

  theCommands.Add ("GetVariable", 
                   "GetVariable (DF, entry, [isConstant], [units])",
                   __FILE__, DDataStd_GetVariable, g);

  theCommands.Add ("SetRelation", 
                   "SetRelation (DF, entry, expression, var1[, var2, ...])",
                   __FILE__, DDataStd_SetRelation, g);


  theCommands.Add ("DumpRelation", 
                   "DumpRelation (DF, entry)",
                   __FILE__, DDataStd_DumpRelation, g);



// ========================= UTF =====================================
  const char* ggg = "UTF Commands";

  theCommands.Add ("SetUTFName", 
                   "SetUTFName (DF, entry, fileName)",
                   __FILE__, DDataStd_KeepUTF, ggg);

  theCommands.Add ("GetUTF", 
                   "GetUTF (DF, entry, fileName)",
                   __FILE__, DDataStd_GetUTFtoFile, ggg);

 //======================= NData Commands ========================
 
  const char* gN = "NData Commands";
  theCommands.Add ("SetNDataIntegers", 
                   "SetNDataIntegers (DF, entry, NumPairs, key1, val1, ...  )",
                   __FILE__, DDataStd_SetNDataIntegers, gN);

  theCommands.Add ("SetNDataReals", 
                   "SetNDataReals (DF, entry, NumPairs, key1, val1, ...  )",
                   __FILE__, DDataStd_SetNDataReals, gN);

  theCommands.Add ("SetNDataStrings", 
                   "SetNDataStrings (DF, entry, NumPairs, key1, val1, ...  )",
                   __FILE__, DDataStd_SetNDataStrings, gN);

  theCommands.Add ("SetNDataBytes", 
                   "SetNDataBytes (DF, entry, NumPairs, key1, val1, ...  )",
                   __FILE__, DDataStd_SetNDataBytes, gN);

  theCommands.Add ("SetNDataIntArrays", 
                   "SetNDataIntArrays (DF entry entry  key NumOfArrElems val1 val2...  )",
                   __FILE__, DDataStd_SetNDataIntAr, gN); 

  theCommands.Add ("SetNDataRealArrays", 
                   "SetNDataRealArrays (DF entry key NumOfArrElems val1 val2...  )",
		  __FILE__, DDataStd_SetNDataRealAr, gN); 

 // GET

  theCommands.Add ("GetNDIntegers", 
                   "GetNDIntegers (DF, entry )",
                   __FILE__, DDataStd_GetNDIntegers, g);

  theCommands.Add ("GetNDInteger", 
                   "GetNDInteger (DF entry key [drawname])",
                   __FILE__, DDataStd_GetNDInteger, g);

  theCommands.Add ("GetNDReals", 
                   "GetNDReals (DF entry )",
                   __FILE__, DDataStd_GetNDReals, g);

  theCommands.Add ("GetNDReal", 
                   "GetNDReal (DF entry key [drawname])",
                   __FILE__, DDataStd_GetNDReal, g);

   theCommands.Add ("GetNDStrings", 
                   "GetNDStrings (DF entry )",
                   __FILE__, DDataStd_GetNDStrings, g);

  theCommands.Add ("GetNDString", 
                   "GetNDString (DF entry key [drawname])",
                   __FILE__, DDataStd_GetNDString, g);

  theCommands.Add ("GetNDBytes", 
                   "GetNDBytes (DF entry )",
                   __FILE__, DDataStd_GetNDBytes, g);

  theCommands.Add ("GetNDByte", 
                   "GetNDByte (DF entry key [drawname])",
                   __FILE__, DDataStd_GetNDByte, g);

  theCommands.Add ("GetNDIntArrays", 
                   "GetNDIntArrays (DF, entry )",
                   __FILE__, DDataStd_GetNDIntArrays, g);

  theCommands.Add ("GetNDIntArray", 
                   "GetNDIntArray (DF entry key )",
                   __FILE__, DDataStd_GetNDIntArray, g);

  theCommands.Add ("GetNDRealArrays", 
                   "GetNDRealArrays (DF entry )",
                   __FILE__, DDataStd_GetNDRealArrays, g);

  theCommands.Add ("GetNDRealArray", 
                   "GetNDRealArray (DF entry key )",
		   __FILE__, DDataStd_GetNDRealArray, g);
  
//====================== Change =======================
  theCommands.Add ("ChangeByteArray", 
                   "ChangeByteArray (DF, entry, indx, value )",
                   __FILE__, DDataStd_ChangeByteArray, g);

  theCommands.Add ("ChangeIntArray", 
                   "ChangeIntArray (DF, entry, indx, value )",
                   __FILE__, DDataStd_ChangeIntArray, g);

  theCommands.Add ("ChangeRealArray", 
                   "ChangeRealArray (DF, entry, indx, value )",
                   __FILE__, DDataStd_ChangeRealArray, g);

  theCommands.Add ("ChangeExtStrArray", 
                   "ChangeExtStrArray (DF, entry, indx, value )",
                   __FILE__, DDataStd_ChangeExtStrArray, g);

  theCommands.Add ("ChangeIntPackedMap_Add", 
                   "ChangeIntPackedMAp_Add (DF, entry, key[,key [...]] )",
                   __FILE__, DDataStd_ChangeIntPackedMap_Add, g);

  theCommands.Add ("ChangeIntPackedMap_Rem", 
                   "ChangeIntPackedMAp_Rem (DF, entry, key[,key [...]] )",
                   __FILE__, DDataStd_ChangeIntPackedMap_Rem, g);

  theCommands.Add ("ChangeIntPackedMap_AddRem", 
                   "ChangeIntPackedMAp_AddRem (DF, entry, key[,key [...]] )",
                   __FILE__, DDataStd_ChangeIntPackedMap_AddRem, g);
 
//=========================================================
  // TFunction commands
  const char* gg = "DFunction Commands";

  theCommands.Add ("SetFunction", 
                   "SetFunction (DF, entry, guid, failure)",
                   __FILE__, DDataStd_SetFunction, gg);

  theCommands.Add ("GetFunction", 
                   "GetFunction (DF, entry, guid(out), failure(out))",
                   __FILE__, DDataStd_GetFunction, gg); 

//=========================================================


//======================================================================
//======= for internal use

  theCommands.Add ("SetNDataIntegers2", 
                   "SetNDataIntegers2 (DF, entry, NumPair  )",
                   __FILE__, DDataStd_SetNDataIntegers2, gN);

  theCommands.Add ("SetNDataIntArrays2", 
                   "SetNDataIntArrays2 (DF entry entry  key NumOfArrElems)",
                   __FILE__, DDataStd_SetNDataIntAr2, gN); 
  
  theCommands.Add ("SetIntArrayT", 
                   "SetIntArrayT (DF, entry, isDelta, From, To  )",
                   __FILE__, DDataStd_SetIntArrayTest, g);

  theCommands.Add ("SetIntPHugeMap", 
		    "SetIntPHugeMap (DF, entry, isDelta Num)",
		    __FILE__, DDataStd_SetIntPHugeMap, g);

//=======

}
