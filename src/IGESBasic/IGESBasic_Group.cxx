// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

// ptv and rln 14.09.2000 BUC60743

#include <IGESBasic_Group.ixx>
#include <Standard_DimensionMismatch.hxx>
#include <Standard_OutOfRange.hxx>


IGESBasic_Group::IGESBasic_Group ()    {  InitTypeAndForm(402,1);  }

    IGESBasic_Group::IGESBasic_Group
  (const Standard_Integer nb)
{
  InitTypeAndForm(402,1);
  if (nb <= 0) return;
  theEntities = new IGESData_HArray1OfIGESEntity (1,nb);
}


    void IGESBasic_Group::Init
  (const Handle(IGESData_HArray1OfIGESEntity)& allEntities)
{
  // ptv and rln September 14, 2000 BUC60743
  // Protection against empty groups
  if (!allEntities.IsNull() && (allEntities->Lower() != 1))
    Standard_DimensionMismatch::Raise("IGESBasic_Group : Init");
  theEntities   = allEntities;
  if (FormNumber() == 0) InitTypeAndForm(402,1);
}

    void  IGESBasic_Group::SetOrdered (const Standard_Boolean mode)
{
  Standard_Integer fn = FormNumber();
  if (mode) {
    if (fn == 0 || fn == 1) InitTypeAndForm (402,14);
    else if (fn == 7)       InitTypeAndForm (402,15);
  } else {
    if      (fn == 14)      InitTypeAndForm (402,1);
    else if (fn == 15)      InitTypeAndForm (402,7);
  }
}

    void  IGESBasic_Group::SetWithoutBackP (const Standard_Boolean mode)
{
  Standard_Integer fn = FormNumber();
  if (mode) {
    if (fn == 0 || fn == 1) InitTypeAndForm (402,7);
    else if (fn == 14)      InitTypeAndForm (402,15);
  } else {
    if      (fn == 7)       InitTypeAndForm (402,1);
    else if (fn == 15)      InitTypeAndForm (402,14);
  }
}

    Standard_Boolean IGESBasic_Group::IsOrdered () const
{
  Standard_Integer fn = FormNumber();
  return (fn > 7);
}

    Standard_Boolean IGESBasic_Group::IsWithoutBackP () const
{
  Standard_Integer fn = FormNumber();
  return (fn == 7 || fn == 15);
}

    void  IGESBasic_Group::SetUser
  (const Standard_Integer type, const Standard_Integer form)
{
  if (type <= 5000) Standard_OutOfRange::Raise("IGESBasic_Group::SetUser");
  InitTypeAndForm (type,form);
}


    void  IGESBasic_Group::SetNb (const Standard_Integer nb)
{
  Standard_Integer i, oldnb = NbEntities();
  if (nb == oldnb || nb <= 0) return;

  Handle(IGESData_HArray1OfIGESEntity) newents = new IGESData_HArray1OfIGESEntity(1,nb);
  if (oldnb > nb) oldnb = nb;
  for (i = 1; i <= oldnb; i ++) newents->SetValue (i,theEntities->Value(i));
  theEntities = newents;
}

    Standard_Integer IGESBasic_Group::NbEntities () const
      {  return(theEntities.IsNull() ? 0 : theEntities->Length());  }

    Handle(IGESData_IGESEntity) IGESBasic_Group::Entity
  (const Standard_Integer Index) const
      {  return theEntities->Value(Index);  }

    Handle(Standard_Transient)  IGESBasic_Group::Value
  (const Standard_Integer Index) const
      {  return theEntities->Value(Index);  }

    void  IGESBasic_Group::SetValue
  (const Standard_Integer Index, const Handle(IGESData_IGESEntity)& ent)
      {  theEntities->SetValue (Index,ent);  }
