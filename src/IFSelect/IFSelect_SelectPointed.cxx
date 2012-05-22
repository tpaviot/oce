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

#include <IFSelect_SelectPointed.ixx>
#include <TColStd_MapOfTransient.hxx>



IFSelect_SelectPointed::IFSelect_SelectPointed ()
    : theset (Standard_False)    {  }

    void  IFSelect_SelectPointed::Clear()
      {  theitems.Clear();  theset = Standard_False;  }

    Standard_Boolean  IFSelect_SelectPointed::IsSet () const
      {  return theset;  }

    void  IFSelect_SelectPointed::SetEntity
  (const Handle(Standard_Transient)& ent)
{
  theitems.Clear();
  theset = Standard_True;
  if (ent.IsNull()) return;
  theitems.Append (ent);
}

    void  IFSelect_SelectPointed::SetList
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
  theitems.Clear();
  theset = Standard_True;
  if (list.IsNull()) return;
  Standard_Integer i,nb = list->Length();
  for (i = 1; i <= nb; i ++)  theitems.Append (list->Value(i));
}

//  ....    Editions

    Standard_Boolean  IFSelect_SelectPointed::Add
  (const Handle(Standard_Transient)& item)
{
  if (item.IsNull()) return Standard_False;
  for (Standard_Integer i = theitems.Length(); i >= 1; i --)
    if (item == theitems.Value(i)) return Standard_False;
  theitems.Append(item);
  theset = Standard_True;
  return Standard_True;
}

    Standard_Boolean  IFSelect_SelectPointed::Remove
  (const Handle(Standard_Transient)& item)
{
  if (item.IsNull()) return Standard_False;
  for (Standard_Integer i = theitems.Length(); i >= 1; i --)
    if (item == theitems.Value(i)) { theitems.Remove(i); return Standard_True;}
  return Standard_True;
}

    Standard_Boolean  IFSelect_SelectPointed::Toggle
  (const Handle(Standard_Transient)& item)
{
  if (item.IsNull()) return Standard_False;
  Standard_Integer num = 0;
  for (Standard_Integer i = theitems.Length(); i >= 1; i --)
    if (item == theitems.Value(i)) num = i;
  if (num == 0) theitems.Append(item);
  else          theitems.Remove(num);
  return (num == 0);
}

    Standard_Boolean  IFSelect_SelectPointed::AddList
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
//   Optimise avec une Map
  Standard_Boolean res = Standard_False;
  if (list.IsNull()) return res;
  Standard_Integer i, nb = theitems.Length(), nl = list->Length();
  TColStd_MapOfTransient deja (nb+nl+1);
  for (i = 1; i <= nb; i ++) deja.Add (theitems.Value(i));

  for (i = 1; i <= nl; i ++) {
    if (!deja.Contains (list->Value(i)) ) theitems.Append (list->Value(i));
  }
  theset = Standard_True;
  return res;
}

    Standard_Boolean  IFSelect_SelectPointed::RemoveList
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
  Standard_Boolean res = Standard_False;
  if (list.IsNull()) return res;
  Standard_Integer i, nb = list->Length();
  for (i = 1; i <= nb; i ++) res |= Remove (list->Value(i));
  return res;
}

    Standard_Boolean  IFSelect_SelectPointed::ToggleList
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
  Standard_Boolean res = Standard_True;
  if (list.IsNull()) return res;
  Standard_Integer i, nb = list->Length();
  for (i = 1; i <= nb; i ++) res |= Toggle (list->Value(i));
  return res;
}


//  ....   Consultations

    Standard_Integer  IFSelect_SelectPointed::Rank
  (const Handle(Standard_Transient)& item) const
{
  if (item.IsNull()) return 0;
  for (Standard_Integer i = theitems.Length(); i >= 1; i --)
    if (item == theitems.Value(i)) return i;
  return 0;
}

    Standard_Integer  IFSelect_SelectPointed::NbItems () const
      {  return theitems.Length();  }

    Handle(Standard_Transient)  IFSelect_SelectPointed::Item
  (const Standard_Integer num) const
{
  Handle(Standard_Transient) item;
  if (num <= 0 || num > theitems.Length()) return item;
  return theitems.Value(num);
}

    void  IFSelect_SelectPointed::Update
  (const Handle(Interface_CopyControl)& control)
{
  Standard_Integer nb = theitems.Length();
  for (Standard_Integer i = nb; i > 0; i --) {
    Handle(Standard_Transient) enfr, ento;
    enfr = theitems.Value(i);
    if (!control->Search(enfr,ento)) theitems.Remove(i);
    else  theitems.SetValue(i,ento);
  }
}

    void  IFSelect_SelectPointed::Update
  (const Handle(IFSelect_Transformer)& trf)
{
  Standard_Integer nb = theitems.Length();
  for (Standard_Integer i = nb; i > 0; i --) {
    Handle(Standard_Transient) enfr, ento;
    enfr = theitems.Value(i);
    if (!trf->Updated(enfr,ento)) theitems.Remove(i);
    else  theitems.SetValue(i,ento);
  }
}

//  ....  Actions Generales

    Interface_EntityIterator  IFSelect_SelectPointed::RootResult
  (const Interface_Graph& G) const
{
  Interface_EntityIterator result;
  Standard_Integer nb = theitems.Length();
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Handle(Standard_Transient) item = theitems.Value(i);
    if (G.EntityNumber(item) > 0) result.GetOneItem(item);
  }
  return result;
}

    TCollection_AsciiString  IFSelect_SelectPointed::Label () const
      {  return TCollection_AsciiString ("Pointed Entities");  }
