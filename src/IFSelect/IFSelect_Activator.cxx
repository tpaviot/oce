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

#include <IFSelect_Activator.ixx>
#include <Dico_DictionaryOfInteger.hxx>
#include <Dico_IteratorOfDictionaryOfInteger.hxx>
#include <TColStd_SequenceOfInteger.hxx>
#include <TColStd_SequenceOfTransient.hxx>
#include <Standard_DomainError.hxx>

#include <IFSelect_Profile.hxx>
#include <IFSelect_Option.hxx>
#include <TCollection_HAsciiString.hxx>

#include <Interface_Macros.hxx>


static Handle(Dico_DictionaryOfInteger) thedico; // = new Dico_DictionaryOfInteger;
static TColStd_SequenceOfInteger   thenums, themodes;
static TColStd_SequenceOfTransient theacts;

static Handle(IFSelect_Profile) thealiases;


    void IFSelect_Activator::Adding
  (const Handle(IFSelect_Activator)& actor,
   const Standard_Integer number,
   const Standard_CString command,
   const Standard_Integer mode)
{
  Standard_Boolean deja;
  if (thedico.IsNull()) thedico = new Dico_DictionaryOfInteger;
  Standard_Integer& num = thedico->NewItem(command,deja,Standard_True);
  if (deja) {
#ifdef DEB
    cout<<"****  XSTEP commands, name conflict on "<<command<<" first defined remains  ****"<<endl;
//    Standard_DomainError::Raise("IFSelect_Activator : Add");
#endif
  }
  num = thenums.Length() + 1;
  thenums.Append(number);
  theacts.Append(actor);
  themodes.Append(mode);
}

    void IFSelect_Activator::Add
  (const Standard_Integer number, const Standard_CString command) const
      {  Adding (this,number,command,0);  }

    void IFSelect_Activator::AddSet
  (const Standard_Integer number, const Standard_CString command) const
      {  Adding (this,number,command,1);  }


    void IFSelect_Activator::Remove (const Standard_CString command)
      {  thedico->RemoveItem(command);  }

//  ALIAS : gere avec un Profile
//  Chaque commande est representee par une Option
//   Au sein de laquelle chaque configuration nomme un cas, dont la valeur
//   est le nom de son alias pour cette conf
//  Et chaque conf porte un switch sur cette option avec pour valeur le propre
//   nom de la conf

    void  IFSelect_Activator::SetAlias
  (const Standard_CString conf,
   const Standard_CString command, const Standard_CString alias)
{
  if (thealiases.IsNull()) thealiases = new IFSelect_Profile;
  Handle(IFSelect_Option) opt = thealiases->Option(command);
  if (opt.IsNull()) {
    opt = new IFSelect_Option(STANDARD_TYPE(TCollection_HAsciiString),command);
    thealiases->AddOption (opt);
  }
  opt->Add (conf,new TCollection_HAsciiString(alias));

  if (!thealiases->HasConf(conf)) thealiases->AddConf (conf);
  thealiases->AddSwitch (conf,command,conf);
}

    void  IFSelect_Activator::SetCurrentAlias (const Standard_CString conf)
{
  if (!thealiases.IsNull()) thealiases->SetCurrent (conf);
}

    TCollection_AsciiString  IFSelect_Activator::Alias
  (const Standard_CString command)
{
  TCollection_AsciiString str;
  if (thealiases.IsNull()) return str;
  Handle(TCollection_HAsciiString) val;
  if (!thealiases->Value(command,val)) return str;
  str.AssignCat (val->ToCString());
  return str;
}


    Standard_Boolean IFSelect_Activator::Select
  (const Standard_CString command, Standard_Integer& number,
   Handle(IFSelect_Activator)& actor)
{
  Standard_Integer num;
  if (!thedico->GetItem(command,num,Standard_False)) return Standard_False;
  number = thenums(num);
  actor = Handle(IFSelect_Activator)::DownCast(theacts(num));
  return Standard_True;
}

    Standard_Integer IFSelect_Activator::Mode
  (const Standard_CString command)
{
  Standard_Integer num;
  if (!thedico->GetItem(command,num,Standard_False)) return -1;
  return themodes(num);
}


    Handle(TColStd_HSequenceOfAsciiString) IFSelect_Activator::Commands
  (const Standard_Integer mode, const Standard_CString command)
{
  Standard_Integer num;
  Dico_IteratorOfDictionaryOfInteger iter (thedico,command);
  Handle(TColStd_HSequenceOfAsciiString) list =
    new  TColStd_HSequenceOfAsciiString();
  for (iter.Start(); iter.More(); iter.Next()) {
    if (mode < 0) {
      DeclareAndCast(IFSelect_Activator,acti,theacts(iter.Value()));
      if (acti.IsNull()) continue;
      if (command[0] == '\0' || !strcmp(command,acti->Group()) )
	list->Append(iter.Name());
    } else {
      num = iter.Value();
      if (themodes(num) == mode) list->Append(iter.Name());
    }
  }
  return list;
}


    IFSelect_Activator::IFSelect_Activator ()
    : thegroup ("XSTEP")    {  }

    void  IFSelect_Activator::SetForGroup
  (const Standard_CString group, const Standard_CString file)
    {  thegroup.Clear();  thegroup.AssignCat (group);
       thefile.Clear();   thefile.AssignCat  (file);   }

    Standard_CString  IFSelect_Activator::Group () const
    {  return thegroup.ToCString();  }

    Standard_CString  IFSelect_Activator::File  () const
    {  return thefile.ToCString();   }
