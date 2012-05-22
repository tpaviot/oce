// Created on: 1997-07-31
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


#include <TDataStd_Name.ixx>

#include <TDF_Label.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Tool.hxx>
#include <TCollection_AsciiString.hxx>
#include <TDF_ListIteratorOfAttributeList.hxx>

//=======================================================================
//function : GetID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_Name::GetID () 
{
  static Standard_GUID TDataStd_NameID("2a96b608-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_NameID;
}

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
Handle(TDataStd_Name) TDataStd_Name::Set
                                (const TDF_Label&                  label,
                                 const TCollection_ExtendedString& theString) 
{
  Handle(TDataStd_Name) N;
  if (!label.FindAttribute(TDataStd_Name::GetID(), N)) { 
    N = new TDataStd_Name ();   
    label.AddAttribute(N);
  }
  N->Set(theString);    
  return N;  
}

//=======================================================================
//function : Find
//purpose  : 
//=======================================================================
// Standard_Boolean TDataStd_Name::Find (const TDF_Label& label, Handle(TDataStd_Name)& name) 
// {  
//   Handle(TDataStd_Name) N;
//   if (label.FindAttribute(TDataStd_Name::GetID(), N)) {
//     name = N;
//     return Standard_True;
//   }
//   TDF_Label L = label;
//   while (!L.IsRoot()) {  
//     L = L.Father();
//     if (L.FindAttribute (TDataStd_Name::GetID(), N)) {
//       name = N;
//       return Standard_True;
//     }      
//   }
//   return Standard_False;
// }

//=======================================================================
//function : IsNamed
//purpose  : 
//=======================================================================
// Standard_Boolean TDataStd_Name::IsNamed(const TDF_Label& label) 
// {
//   Handle(TDataStd_Name) N;
  
//   return label.FindAttribute(TDataStd_Name::GetID(), N);
// }

//=======================================================================
//function : IsEmpty
//purpose  : 
//=======================================================================
// Standard_Boolean TDataStd_Name::IsEmpty(const TDF_Label& label) 
// {
//   Handle(TDataStd_Name) N;
//   if(label.FindAttribute(TDataStd_Name::GetID(), N)) {
//     return N->IsEmpty();
//   }

//   Standard_DomainError::Raise("There isn't the Name Attribute on the label");
// }

//=======================================================================
//function : Erase
//purpose  : 
//=======================================================================
// void TDataStd_Name::Erase(const TDF_Label& label) 
// {
//   Handle(TDataStd_Name) N;
  
//   if(label.FindAttribute(TDataStd_Name::GetID(), N)) {
//     N->SetEmpty();
//     return;
//   }

//   Standard_DomainError::Raise("There isn't the Name Attribute on the label");
// }

//=======================================================================
//function : TDataStd_Name
//purpose  : Empty Constructor
//=======================================================================

TDataStd_Name::TDataStd_Name ()
     : myEmpty(Standard_True) { }

//=======================================================================
//function : Father
//purpose  : 
//=======================================================================
// Standard_Boolean TDataStd_Name::Father (Handle(TDataStd_Name)& name) const
// {
//   Handle(TDataStd_Name) father;
//   TDF_Label L = Label();
//   while (!L.IsRoot()) {  
//     L = L.Father();
//     if (L.FindAttribute (TDataStd_Name::GetID(), father)) {
//       name = father;
//       return Standard_True;
//     }      
//   }
//   return Standard_False;
// }

//=======================================================================
//function : Set
//purpose  : 
//=======================================================================
void TDataStd_Name::Set (const TCollection_ExtendedString& S) 
{
  // OCC2932 correction
  if(myString == S) return;
 
  Backup();
  myString = S;
  //TCollection_ExtendedString tmpS(S);
  //tmpS.RemoveAll(':');
  //myString = tmpS;
  //myEmpty = Standard_False;
}



//=======================================================================
//function : Get
//purpose  : 
//=======================================================================
const TCollection_ExtendedString& TDataStd_Name::Get () const
{
  return myString;
}

//=======================================================================
//function : SetEmpty
//purpose  : 
//=======================================================================
// void TDataStd_Name::SetEmpty() 
// {
//   Backup();
//   myEmpty = Standard_True;
//   myString.Clear();
// }

//=======================================================================
//function : IsEmpty
//purpose  : 
//=======================================================================
//Standard_Boolean TDataStd_Name::IsEmpty() const {return myEmpty;}


// TDF_Attribute methods

//=======================================================================
//function : ID
//purpose  : 
//=======================================================================

const Standard_GUID& TDataStd_Name::ID () const { return GetID(); }




//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================

Handle(TDF_Attribute) TDataStd_Name::NewEmpty () const
{  
  return new TDataStd_Name(); 
}

//=======================================================================
//function : Restore
//purpose  : 
//=======================================================================

void TDataStd_Name::Restore(const Handle(TDF_Attribute)& with) 
{
  myString = Handle(TDataStd_Name)::DownCast (with)->Get();
}


//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================

void TDataStd_Name::Paste (const Handle(TDF_Attribute)& into,
                           const Handle(TDF_RelocationTable)&/* RT*/) const
{
  Handle(TDataStd_Name)::DownCast (into)->Set (myString);
}

//=======================================================================
//function : Dump
//purpose  : 
//=======================================================================

Standard_OStream& TDataStd_Name::Dump (Standard_OStream& anOS) const
{
  TDF_Attribute::Dump(anOS);
  anOS << " Name=|"<<myString<<"|"<<endl;
  return anOS;
}


//=======================================================================
//function : Find (by the full path)
//purpose  : Name
//=======================================================================
// Standard_Boolean TDataStd_Name::Find (const Handle(TDF_Data)& framework,
//                                    const TDataStd_ListOfExtendedString& fullPath,
//                                    Handle(TDataStd_Name)& name) 
// {
//   Handle(TDataStd_Name) Ncurrent;
//   TDF_Label L, root = framework->Root();
//   TDF_ChildIterator ChItr (root, Standard_True);
//   TCollection_ExtendedString string, first = fullPath.First();
//   TDataStd_ListOfExtendedString tmpPath;
//   Standard_Boolean IsRootVisited = Standard_False;

//   tmpPath.Assign(fullPath);
//   if(tmpPath.Extent() > 0 ) tmpPath.RemoveFirst();  

//   while( ChItr.More() ) {
//     if( !IsRootVisited ) L = root;          //For the fisrt time visit the root label
//     else L = ChItr.Value();

//     if( L.FindAttribute(TDataStd_Name::GetID(), Ncurrent) ) { 
//       string = Ncurrent->Get();
//       if( (string == first ) && ((string.Length()) == (first.Length())) ) {   
//      if( fullPath.Extent() == 1 ) {  
//           name = Ncurrent;
//           return Standard_True;  
//      }
//      if (Ncurrent->Find(tmpPath, name) ) return Standard_True;  
//       }
//       else {
//      if( !Ncurrent->IsEmpty() ) { 
//        //The root contains String different from first name in the path 
//        if( !IsRootVisited ) return Standard_False; 
//        ChItr.NextBrother(); continue; 
//      }
//       }
//     }

//     if( !IsRootVisited ) {
//       IsRootVisited = Standard_True; 
//       continue; 
//     }

//     ChItr.Next();
//   }
//   return Standard_False;  
// }

//=======================================================================
//function : Find (by the relative path)
//purpose  : Name
//=======================================================================
// Standard_Boolean TDataStd_Name::Find (const TDF_Label& currentLabel,
//                                    const TDataStd_ListOfExtendedString& relativePath,
//                                    Handle(TDataStd_Name)& name) 
// { 
//   Handle(TDataStd_Name) Ncurrent;
//   TDF_ChildIterator ChItr (currentLabel, Standard_True);
//   TCollection_ExtendedString string, first = relativePath.First();
//   TDataStd_ListOfExtendedString tmpPath;
//   tmpPath.Assign(relativePath);

//   if( !currentLabel.FindAttribute(TDataStd_Name::GetID(), Ncurrent) )
//     Standard_DomainError::Raise("There isn't the Name attribute on the label");

   
//   while( ChItr.More() ) {    
//     if( ChItr.Value().FindAttribute(TDataStd_Name::GetID(), Ncurrent) ) {
//       string = Ncurrent->Get();
//       if( (string == first ) && ((string.Length()) == (first.Length())) ) {
//      if( relativePath.Extent() == 1  ) {  //it has reached the end of the relative path
//        name = Ncurrent;
//           return Standard_True;
//      }
//      else {
//           if (tmpPath.Extent() > 0) tmpPath.RemoveFirst();
//           if (Find(ChItr.Value(), tmpPath, Ncurrent)) return Standard_True; 
//      }
//       }
//       else {
//      if( !Ncurrent->IsEmpty() ) {  
//        ChItr.NextBrother(); continue;  
//      }
//       }
//     }
//     ChItr.Next();
//   }  
  
//   return Standard_False;
// }


//=======================================================================
//function : Find (by the relative path)
//purpose  : NameTool
//=======================================================================
// Standard_Boolean TDataStd_Name::Find(const TDF_Label& currentLabel,
//                                   const TCollection_ExtendedString& string,
//                                   Handle(TDataStd_Name)& name) 
// {
//   TDataStd_ListOfExtendedString tmpPath; 
//   TDataStd_Name::MakePath(string, tmpPath,':');
//   Handle(TDataStd_Name) Ncurrent;
//   if (TDataStd_Name::Find(currentLabel,Ncurrent)) {
//     return Ncurrent->Find(tmpPath, name);
//   }
//   return Standard_False;
// }

//=======================================================================
//function : Find (by the full path)
//purpose  : NameTool
//=======================================================================
// Standard_Boolean TDataStd_Name::Find(const Handle(TDF_Data)& framework,
//                                   const TCollection_ExtendedString& string,
//                                   Handle(TDataStd_Name)& name) 
// {
//   TDataStd_ListOfExtendedString tmpPath; 
//   TDataStd_Name::MakePath(string, tmpPath,':');
//   return Find(framework, tmpPath, name);
// }

//=======================================================================
//function : FullPath
//purpose  : NameTool
//=======================================================================
// Standard_Boolean TDataStd_Name::FullPath (TDF_AttributeList& path) const
// {
//   path.Clear();
//   if( !IsEmpty() ) path.Append(this);
//   TDF_Label L = Label();
//   if(L.IsRoot() ) return Standard_True;
//   Handle(TDataStd_Name) Ncur;
//   while ( !L.IsRoot()) {  
//     L = L.Father();
//     if(L.FindAttribute (TDataStd_Name::GetID(), Ncur)) { 
//       if( !Ncur->IsEmpty() )path.Prepend(Ncur); 
//     }
//   }    
//   return Standard_True;
// }

//=======================================================================
//function : MakePath
//purpose  : NameTool
//=======================================================================
// Standard_Boolean TDataStd_Name::MakePath(const TCollection_ExtendedString& path,
//                                          TDataStd_ListOfExtendedString& pathlist,
//                                          const Standard_ExtCharacter Separator) 
// {
//   TCollection_ExtendedString tmpPath = path, str;

//   str+=Separator; str+=Separator;
//   if( tmpPath.Search(str) != -1 ) return Standard_False;     //Not valid path (contains two adjacent separators)
  
//   if( tmpPath.Search(Separator) == -1 ) {  //The path contains only one name.
//     pathlist.Append(path); 
//     return Standard_True;
//   }
//   Standard_Integer i;
//   while( (i = tmpPath.SearchFromEnd(Separator) ) != -1 ) {
//    str = tmpPath.Split(i-1);
//    str.Remove(1);
//    pathlist.Prepend(str);
//   } 
//   if( tmpPath.Length() > 0 ) pathlist.Prepend(tmpPath);
//   return Standard_True;
// }


//=======================================================================
//function : MakePath
//purpose  : NameTool
//=======================================================================
// Standard_Boolean TDataStd_Name::MakePath(const TDF_AttributeList& pathlist,
//                                          TCollection_ExtendedString& path,
//                                          const Standard_ExtCharacter Separator) 
// {
//   TDF_ListIteratorOfAttributeList Itr(pathlist);
//   Handle(TDataStd_Name) N;

//   if( pathlist.Extent() == 0 ) return Standard_False;
//   path.Clear();
//   for(; Itr.More(); Itr.Next() ) {
//     N = Handle(TDataStd_Name)::DownCast(Itr.Value());
//     path = path + N->Get();
//     path = path + Separator;
//   }
//   path.Remove(path.Length(), 1);
//   return Standard_True;
// }

//=======================================================================
//function : Find (by the relative path)
//purpose  : Name
//=======================================================================
// Standard_Boolean TDataStd_Name::Find (const TDataStd_ListOfExtendedString& relativePath,
//                                       Handle(TDataStd_Name)& name) const
// { 
//   Handle(TDataStd_Name) Ncurrent;
//   TDF_ChildIterator ChItr (Label(), Standard_True);
//   TCollection_ExtendedString string, first = relativePath.First();
//   TDataStd_ListOfExtendedString tmpPath;
//   tmpPath.Assign(relativePath);
//   //
//   while( ChItr.More() ) {    
//     if( ChItr.Value().FindAttribute(TDataStd_Name::GetID(), Ncurrent) ) {
//       string = Ncurrent->Get();
//       if( (string == first ) && ((string.Length()) == (first.Length())) ) {
//      if( relativePath.Extent() == 1  ) {  //it has reached the end of the relative path
//        name = Ncurrent;
//           return Standard_True;
//      }
//      else {
//           if (tmpPath.Extent() > 0) tmpPath.RemoveFirst();
//           if (Ncurrent->Find(tmpPath, name)) return Standard_True; 
//      }
//       }
//       else {
//      if (!Ncurrent->IsEmpty()) {  
//        ChItr.NextBrother(); continue;  
//      }
//       }
//     }
//     ChItr.Next();
//   }  
//   return Standard_False;
// }

//=======================================================================
//function : ChildNames
//purpose  : NameTool
//=======================================================================
// Standard_Boolean TDataStd_Name::ChildNames (TDF_AttributeList& list) const
// {
//   Standard_Boolean found = Standard_False;
//   TDF_ChildIterator ChItr (Label(), Standard_True);
//   Handle(TDataStd_Name) N;
//   list.Clear();
//   for(; ChItr.More(); ChItr.Next()) {
//     if( ChItr.Value().FindAttribute(TDataStd_Name::GetID(), N) ) {
//       list.Append(N);
//       found = Standard_True;
//       cout << N->Get() << endl;
//     }
//   }
//   return found;
// }
