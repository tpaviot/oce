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

#include <StepData_Protocol.ixx>
#include <StepData_StepModel.hxx>
#include <StepData_UndefinedEntity.hxx>
#include <StepData_Described.hxx>
#include <Interface_DataMapIteratorOfDataMapOfTransientInteger.hxx>
#include <stdio.h>


//  Le Protocol de base reconnait UnknownEntity

//static TCollection_AsciiString  thename("(DEFAULT)");
static Standard_CString thename = "(DEFAULT)";

StepData_Protocol::StepData_Protocol ()
{
}

Standard_Integer  StepData_Protocol::NbResources () const
{
  return 0;
}


Handle(Interface_Protocol) StepData_Protocol::Resource
  (const Standard_Integer /*num*/) const
{
  Handle(Interface_Protocol) nulproto;  
  return nulproto;
}


Standard_Integer  StepData_Protocol::CaseNumber
  (const Handle(Standard_Transient)& obj) const
{
  if (obj.IsNull()) return 0;
  Standard_Integer num = TypeNumber (obj->DynamicType());
  if (num > 0) return num;
  Handle(StepData_Described) dc = Handle(StepData_Described)::DownCast(obj);
  if (dc.IsNull()) return 0;
  return DescrNumber (dc->Description());
}


Standard_Integer  StepData_Protocol::TypeNumber
  (const Handle(Standard_Type)& atype) const
{
  if (atype == STANDARD_TYPE(StepData_UndefinedEntity)) return 1;
  return 0;
}


Standard_CString StepData_Protocol::SchemaName () const
{
  return thename;
}


Handle(Interface_InterfaceModel)  StepData_Protocol::NewModel () const 
{
  return new StepData_StepModel;
}


Standard_Boolean  StepData_Protocol::IsSuitableModel
  (const Handle(Interface_InterfaceModel)& model) const 
{
  return model->IsKind(STANDARD_TYPE(StepData_StepModel));
}


Handle(Standard_Transient)  StepData_Protocol::UnknownEntity () const
{
  return new StepData_UndefinedEntity;
}


Standard_Boolean  StepData_Protocol::IsUnknownEntity
  (const Handle(Standard_Transient)& ent) const 
{
  if (!ent.IsNull())
    return ent->IsKind(STANDARD_TYPE(StepData_UndefinedEntity));
  return Standard_False;
}


//  ####    Description pour LateBinding

Standard_Integer  StepData_Protocol::DescrNumber
  (const Handle(StepData_EDescr)& adescr) const
{
  if (thedscnum.IsBound(adescr)) return thedscnum.Find(adescr);
  return 0;
}


void  StepData_Protocol::AddDescr
  (const Handle(StepData_EDescr)& adescr, const Standard_Integer CN)
{
  Handle(StepData_ESDescr) sd = Handle(StepData_ESDescr)::DownCast(adescr);
  thedscnum.Bind (adescr,CN);

//  Simple : memorisee selon son nom
//  sinon que faire ? on memorise selon le numero passe en alpha-num ...
//   (temporaire)
  if (thedscnam.IsNull()) thedscnam = new Dico_DictionaryOfTransient;
  if (!sd.IsNull()) thedscnam->SetItem (sd->TypeName(),sd);
  char fonom[10];
  sprintf(fonom,"%d",CN);
  thedscnam->SetItem (fonom,adescr);
}


Standard_Boolean  StepData_Protocol::HasDescr () const
{
  return !thedscnam.IsNull();
}


Handle(StepData_EDescr)  StepData_Protocol::Descr
  (const Standard_Integer num) const
{
  Handle(StepData_EDescr) dsc;
  if (thedscnam.IsNull()) return dsc;
  char fonom[10];
  sprintf(fonom,"%d",num);
  if (!thedscnam->GetItem (fonom,dsc)) dsc.Nullify();
  return dsc;
}


Handle(StepData_EDescr)  StepData_Protocol::Descr
  (const Standard_CString name, const Standard_Boolean anylevel) const
{
  Handle(StepData_EDescr) sd;
  if (!thedscnam.IsNull()) {
    if (thedscnam->GetItem (name,sd)) return sd;
  }
  if (!anylevel) return sd;

  Standard_Integer i, nb = NbResources();
  for (i = 1; i <= nb; i ++) {
    Handle(StepData_Protocol) sp = Handle(StepData_Protocol)::DownCast(Resource(i));
    if (sp.IsNull()) continue;
    sd = sp->Descr (name,anylevel);
    if (!sd.IsNull()) return sd;
  }
  return sd;
}


Handle(StepData_ESDescr)  StepData_Protocol::ESDescr
  (const Standard_CString name, const Standard_Boolean anylevel) const
{
  return Handle(StepData_ESDescr)::DownCast(Descr(name,anylevel));
}


Handle(StepData_ECDescr)  StepData_Protocol::ECDescr
  (const TColStd_SequenceOfAsciiString& names, const Standard_Boolean anylevel) const
{
  Standard_Integer i, nb = names.Length();
  Handle(StepData_ECDescr) cd;
  Interface_DataMapIteratorOfDataMapOfTransientInteger iter(thedscnum);
  for (; iter.More(); iter.Next()) {
    cd = Handle(StepData_ECDescr)::DownCast (iter.Key());
    if (cd.IsNull()) continue;
    if (cd->NbMembers() != nb) continue;
    Standard_Boolean ok = Standard_True;
    for (i = 1; i <= nb; i ++) {
      if (!names(i).IsEqual (cd->Member(i)->TypeName())) { ok = Standard_False; break; }
    }
    if (ok) return cd;
  }
  cd.Nullify();
  if (!anylevel) return cd;

  nb = NbResources();
  for (i = 1; i <= nb; i ++) {
    Handle(StepData_Protocol) sp = Handle(StepData_Protocol)::DownCast(Resource(i));
    if (sp.IsNull()) continue;
    cd = sp->ECDescr (names,anylevel);
    if (!cd.IsNull()) return cd;
  }
  return cd;
}


void  StepData_Protocol::AddPDescr
  (const Handle(StepData_PDescr)& pdescr)
{
  if (thepdescr.IsNull()) thepdescr = new Dico_DictionaryOfTransient;
  thepdescr->SetItem (pdescr->Name(),pdescr);
}


Handle(StepData_PDescr)  StepData_Protocol::PDescr
  (const Standard_CString name, const Standard_Boolean anylevel) const
{
  Handle(StepData_PDescr) sd;
  if (!thepdescr.IsNull()) {
    if (thepdescr->GetItem (name,sd)) return sd;
  }
  if (!anylevel) return sd;

  Standard_Integer i, nb = NbResources();
  for (i = 1; i <= nb; i ++) {
    Handle(StepData_Protocol) sp = Handle(StepData_Protocol)::DownCast(Resource(i));
    if (sp.IsNull()) continue;
    sd = sp->PDescr (name,anylevel);
    if (!sd.IsNull()) return sd;
  }
  return sd;
}


void  StepData_Protocol::AddBasicDescr
  (const Handle(StepData_ESDescr)& esdescr)
{
  if (thedscbas.IsNull()) thedscbas = new Dico_DictionaryOfTransient;
  thedscbas->SetItem (esdescr->TypeName(),esdescr);
}


Handle(StepData_EDescr)  StepData_Protocol::BasicDescr
  (const Standard_CString name, const Standard_Boolean anylevel) const
{
  Handle(StepData_EDescr) sd;
  if (!thedscbas.IsNull()) {
    if (thedscbas->GetItem (name,sd)) return sd;
  }
  if (!anylevel) return sd;

  Standard_Integer i, nb = NbResources();
  for (i = 1; i <= nb; i ++) {
    Handle(StepData_Protocol) sp = Handle(StepData_Protocol)::DownCast(Resource(i));
    if (sp.IsNull()) continue;
    sd = sp->BasicDescr (name,anylevel);
    if (!sd.IsNull()) return sd;
  }
  return sd;
}
