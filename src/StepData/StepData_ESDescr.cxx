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

#include <StepData_ESDescr.ixx>
#include <StepData_Simple.hxx>
#include <Interface_Macros.hxx>


StepData_ESDescr::StepData_ESDescr  (const Standard_CString name)
:  thenom (name)    {  thenames = new Dico_DictionaryOfInteger;  }

void  StepData_ESDescr::SetNbFields (const Standard_Integer nb)
{
  Standard_Integer minb,i, oldnb = NbFields();
  thenames->Clear();
  if (nb == 0)  {  thedescr.Nullify();  return;  }
  Handle(TColStd_HArray1OfTransient) li = new TColStd_HArray1OfTransient(1,nb);
  if (oldnb == 0)  {  thedescr = li;  return;  }
  minb = (oldnb > nb ? nb : oldnb);
  for (i = 1; i <= minb; i ++)  {
    DeclareAndCast(StepData_PDescr,pde,thedescr->Value(i));
    if (!pde.IsNull())  thenames->SetItem (pde->Name(),i);
    li->SetValue (i, pde);
  }
  thedescr = li;
}


    void  StepData_ESDescr::SetField
  (const Standard_Integer num, const Standard_CString name,
   const Handle(StepData_PDescr)& descr)
{
  if (num < 1 || num > NbFields()) return;
  Handle(StepData_PDescr) pde = new StepData_PDescr;
  pde->SetFrom (descr);
  pde->SetName (name);
  thedescr->SetValue (num,pde);
  thenames->SetItem (name,num);
}

    void  StepData_ESDescr::SetBase (const Handle(StepData_ESDescr)& base)
{
  thebase = base;
//  il faut CUMULER les fields de la base et ses supers
}

    void  StepData_ESDescr::SetSuper (const Handle(StepData_ESDescr)& super)
{
  Handle(StepData_ESDescr) sup = super->Base();
  if (sup.IsNull()) sup = super;
  if (!thebase.IsNull()) thebase->SetSuper (sup);
  else thesuper = sup;
}

    Standard_CString  StepData_ESDescr::TypeName () const
      {  return thenom.ToCString();  }

    const TCollection_AsciiString&  StepData_ESDescr::StepType () const
      {  return thenom;  }

    Handle(StepData_ESDescr)  StepData_ESDescr::Base () const
      {  return thebase;  }

    Handle(StepData_ESDescr)  StepData_ESDescr::Super () const
      {  return thesuper;  }

    Standard_Boolean  StepData_ESDescr::IsSub (const Handle(StepData_ESDescr)& other) const
{
  Handle(StepData_ESDescr) oth = other->Base();
  if (oth.IsNull()) oth = other;
  if (!thebase.IsNull()) return thebase->IsSub (oth);
  Handle(Standard_Transient) t1 = this;
  if (oth == t1)       return Standard_True;
  if (oth == thesuper) return Standard_True;
  else if (thesuper.IsNull()) return Standard_False;
  return thesuper->IsSub (oth);
}


    Standard_Integer  StepData_ESDescr::NbFields () const
      {  return (thedescr.IsNull() ? 0 : thedescr->Length());  }

    Standard_Integer  StepData_ESDescr::Rank (const Standard_CString name) const
{
  Standard_Integer rank;
  if (!thenames->GetItem (name,rank)) return 0;
  return rank;
}

    Standard_CString  StepData_ESDescr::Name (const Standard_Integer num) const
{
  if (num < 1) return "";
  if (num > NbFields()) return "";
  DeclareAndCast(StepData_PDescr,pde,thedescr->Value(num));
  return pde->Name();
}

    Handle(StepData_PDescr)  StepData_ESDescr::Field (const Standard_Integer num) const
     {  return GetCasted(StepData_PDescr,thedescr->Value(num));  }

    Handle(StepData_PDescr)  StepData_ESDescr::NamedField
  (const Standard_CString name) const
{
  Handle(StepData_PDescr) pde;
  Standard_Integer rank = Rank(name);
  if (rank > 0) pde = GetCasted(StepData_PDescr,thedescr->Value(rank));
  return pde;
}


    Standard_Boolean  StepData_ESDescr::Matches (const Standard_CString name) const
{
  if (thenom.IsEqual(name)) return Standard_True;
  if (thesuper.IsNull()) return Standard_False;
  return thesuper->Matches (name);
}

    Standard_Boolean  StepData_ESDescr::IsComplex () const
      {  return Standard_False;  }

    Handle(StepData_Described)  StepData_ESDescr::NewEntity () const
{
  Handle(StepData_Simple) ent = new StepData_Simple(this);
  return ent;
}
