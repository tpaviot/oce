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

#include <Interface_EntityIterator.ixx>
#include <Standard_NoMoreObject.hxx>
#include <Standard_NoSuchObject.hxx>


//  Iterateur pour ecriture for, ou while avec Next en fin :
//  for (creer iterateur; iter.More(); iter.Next()) { val = iter.Value(); ... }


// .... Definitions initiales : en particulier celles requises pour
//      les outils de graphe (construction avec le graphe, avec un vertex)

Interface_EntityIterator::Interface_EntityIterator ()
{
//  thecurr = new Interface_IntVal;
//  thecurr->CValue() = 0;
//  thelist = new TColStd_HSequenceOfTransient();  // constructeur vide
//  thelist sera construit au premier Add (quelquefois, il nyena pas)
}

    Interface_EntityIterator::Interface_EntityIterator
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
  thecurr = new Interface_IntVal;
  thecurr->CValue() = 0;
  thelist = list;
}

    void Interface_EntityIterator::AddList
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
  if (thelist.IsNull()) thelist = new TColStd_HSequenceOfTransient();
  if (thecurr.IsNull()) thecurr = new Interface_IntVal;
  thecurr->CValue() = 0;
  thelist->Append(list);
}

    void Interface_EntityIterator::AddItem
  (const Handle(Standard_Transient)& anentity)
{
  if (anentity.IsNull()) return;
  if (thecurr.IsNull()) thecurr = new Interface_IntVal;
  if (thelist.IsNull()) thelist = new TColStd_HSequenceOfTransient();
  thecurr->CValue() = 0;
  thelist->Append(anentity);
}

    void Interface_EntityIterator::GetOneItem
  (const Handle(Standard_Transient)& anentity)
      {  AddItem(anentity);  }

    void Interface_EntityIterator::Reset ()
{
  if (thecurr.IsNull()) thecurr = new Interface_IntVal;
  thecurr->CValue() = 0;
  thelist = new TColStd_HSequenceOfTransient();
}


// .... Fonctionnalites de tri prealable a l'iteration ....

//  Facon "bete" : supprimer les termes qui ne conviennent pas : lent !
//  Mieux vaut refaire une autre sequence a cote

    void Interface_EntityIterator::SelectType
  (const Handle(Standard_Type)& atype, const Standard_Boolean keep)
{
  if (thelist.IsNull()) return;
  Standard_Integer i, n = thelist->Length();
  Handle(TColStd_HSequenceOfTransient) nlist = new TColStd_HSequenceOfTransient();
  for (i = 1 ; i <= n ; i ++) {
    if (thelist->Value(i)->IsKind(atype) == keep) nlist->Append(thelist->Value(i));
  }
  thelist = nlist;
}

//  ....  Iteration proprement dite  ....

    Standard_Integer Interface_EntityIterator::NbEntities () const
{
  if (thelist.IsNull()) return 0;
  if (!thecurr.IsNull() && thecurr->Value() == 0) Start();
  return thelist->Length();
}

    Standard_Integer Interface_EntityIterator::NbTyped
  (const Handle(Standard_Type)& atype) const
{
  Standard_Integer res = 0;
  if (thelist.IsNull()) return res;
  Standard_Integer i, n = thelist->Length();
  for (i = 1 ; i <= n ; i ++) {
    if (thelist->Value(i)->IsKind(atype)) res ++;
  }
  return res;
}

    Interface_EntityIterator  Interface_EntityIterator::Typed
  (const Handle(Standard_Type)& atype) const
{
  Interface_EntityIterator res;
  if (thelist.IsNull()) return res;
  Standard_Integer i, n = thelist->Length();
  for (i = 1 ; i <= n ; i ++) {
    if (thelist->Value(i)->IsKind(atype)) res.AddItem (thelist->Value(i));
  }
  return res;
}


    void Interface_EntityIterator::Start () const
      {    if (!thecurr.IsNull()) thecurr->CValue() = 1 ;  }     // peut etre redefini ...

    Standard_Boolean Interface_EntityIterator::More () const
{
  if (thecurr.IsNull()) return Standard_False;
  if (thecurr->Value() == 0) Start();  // preparation de l iteration
  if (thelist.IsNull()) return Standard_False;
  return (thecurr->Value() <= thelist->Length());
}

    void Interface_EntityIterator::Next () const
      {    thecurr->CValue() ++;  }    // Next ne verifie rien : soin laisse a Value

    const Handle(Standard_Transient)& Interface_EntityIterator::Value () const
{
//  NbEntity pas const (on ne sait pas comment il est implemente apres tout)
  if (thelist.IsNull()) Standard_NoSuchObject::Raise("Interface_EntityIterator");
  if (thecurr->Value() < 1 || thecurr->Value() > thelist->Length())
    Standard_NoSuchObject::Raise("Interface_EntityIterator");
  return thelist->Value(thecurr->Value());
}

    Handle(TColStd_HSequenceOfTransient)  Interface_EntityIterator::Content () const
{
  if (!thecurr.IsNull() && thecurr->Value() == 0) Start();
  if (thelist.IsNull()) return new TColStd_HSequenceOfTransient();  // vide
  return thelist;
}

    void  Interface_EntityIterator::Destroy ()
      {  thecurr.Nullify();  }  // redevient vide !
