// Created on: 1999-08-19
// Created by: Sergey RUIN
// Copyright (c) 1999-1999 Matra Datavision
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

// ATTRIBUTES

#include <TDataStd.hxx>
#include <TDataStd_Name.hxx>

#include <TCollection_AsciiString.hxx>
#include <TDataStd_ListOfExtendedString.hxx>




//=======================================================================
//function : DDataStd_SetName
//purpose  : SetName (DF, entry, name)
//=======================================================================

static Standard_Integer DDataStd_SetName (Draw_Interpretor& di,
					  Standard_Integer nb, 
					  const char** arg) 
{
//   if (nb == 3) {    
//     Handle(TDF_Data) DF;
//     if (!DDF::GetDF(arg[1],DF)) return 1;
//     TDF_Label L;
//     DDF::FindLabel(DF, arg[2], L);
//     if(L.IsNull()) cout << "Label is not found"   << endl;
//     Handle(TDataStd_Name) N = TDataStd_Name::Set(L);
//     return 0;
//  }
  // else if (nb == 4) {  
  if (nb == 4) {     
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1;
    TDF_Label L;
    DDF::FindLabel(DF, arg[2], L);
    if(L.IsNull()) di << "Label is not found"   << "\n";
    Handle(TDataStd_Name) N;
    //if( !L.FindAttribute(TDataStd_Name::GetID(), N) ) N = TDataStd_Name::Set(L);
    //N->Set(arg[3]); 
    N = TDataStd_Name::Set(L,arg[3]); 
    return 0;
  }
  di << "DDataStd_SetName : Error" << "\n";
  return 1;
}


//=======================================================================
//function : DDataStd_GetName
//purpose  : GetName (DF, entry)
//=======================================================================

static Standard_Integer DDataStd_GetName (Draw_Interpretor& di,
					  Standard_Integer nb, 
					  const char** arg) 
{   
  if (nb == 3) {    
    Handle(TDF_Data) DF;
    if (!DDF::GetDF(arg[1],DF)) return 1; 
    TDF_Label L;
    DDF::FindLabel(DF, arg[2], L);
    if(L.IsNull()) di << "Label is not found"   << "\n";
    Handle(TDataStd_Name) N;
    if( !L.FindAttribute(TDataStd_Name::GetID(), N) ) return 1;
    TCollection_AsciiString s(N->Get(),'?');
    di << s.ToCString();
    return 0;
  }
  di << "DDataStd_SetName : Error" << "\n";
  return 1;
}



//=======================================================================
//function : LabelName (DF, [entry], path)
//=======================================================================
// static Standard_Integer DDataStd_LabelName (Draw_Interpretor& di,
// 					    Standard_Integer nb, 
// 					    const char** arg) 
// {
//   Handle(TDF_Data) DF;
//   TDF_Label label;
//   Handle(TDataStd_Name) result;
//   TDataStd_ListOfExtendedString myList;
//   Standard_Integer i = 2;
//   Standard_Boolean Found = Standard_False;

//   if (!DDF::GetDF(arg[1],DF))  return 1;
//   if( nb == 4 ) {
//     if( !DDF::FindLabel(DF, arg[2], label) ) {   
//       cout << "No label for entry"  << endl;
//       return 1;   
//     }
//     i = 3;
//   }
  
//   if( !TDataStd_Name::MakePath(arg[i], myList) ) return 1;

//   if( nb == 4 ) {
//     Handle(TDataStd_Name) current;
//     if (TDataStd_Name::Find(label,current)) {
//       if (current->Find(myList ,result)) Found = Standard_True;
//     }
//   }
//   else {
//     if(TDataStd_Name::Find(DF, myList ,result)) Found = Standard_True;
//   }
  
//   if(Found) {
//     DDF::ReturnLabel(di,  result->Label());
//     return 0;
//   }

//   cout << "Label wasn't found"  << endl;
//   return 1;
// }


// //=======================================================================
// //function : FullPath (DF, entry)
// //=======================================================================
// static Standard_Integer DDataStd_FullPath (Draw_Interpretor& di,
// 					   Standard_Integer nb, 
// 					   const char** arg) 
// {
//   Handle(TDF_Data) DF;
//   if (!DDF::GetDF(arg[1],DF))  return 1; 
//   TDF_Label label;
//   if( !DDF::FindLabel(DF, arg[2], label) ) {   
//     cout << "No label for entry"  << endl;
//     return 1;   
//   } 
//   Handle(TDataStd_Name) current;
//   if (TDataStd_Name::Find(label,current)) {
//     TDF_AttributeList myList;
//     if (!current->FullPath(myList)) return 1;
//     TDF_ListIteratorOfAttributeList itr(myList);
//     TCollection_AsciiString str;
//     for(;itr.More(); itr.Next() ) { 
//       str+=Handle(TDataStd_Name)::DownCast(itr.Value())->Get();
//       str+=":";
//     }
//     str.Remove(str.Length());       //remove last ":"
//     di << str.ToCString(); 
//   }  
// #ifndef DEB
//   return 0 ;
// #endif
// }
//=======================================================================
//function : SetCommands
//purpose  : 
//=======================================================================

void DDataStd::NameCommands (Draw_Interpretor& theCommands)
{  

  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  const char* g = "DDataStd : Name attribute commands";

  theCommands.Add ("SetName", 
                   "SetName (DF, entry, name)",
		   __FILE__, DDataStd_SetName, g);   

  theCommands.Add ("GetName", 
                   "GetNmae (DF, entry)",
                    __FILE__, DDataStd_GetName, g);  

//   theCommands.Add ("LabelName", 
//                    "GetLabel (DF, [entry], path(name1:name2:...nameN)",
// 		   __FILE__, DDataStd_LabelName, g);

//   theCommands.Add ("FullPath", 
//                    "FullPath (DF, entry)",
// 		   __FILE__, DDataStd_FullPath, g);

}

