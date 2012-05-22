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

#include <Interface_EntityList.ixx>
#include <Interface_EntityCluster.hxx>
#include <Interface_InterfaceError.hxx>
#include <Standard_OutOfRange.hxx>
#include <Standard_NullObject.hxx>


// Une EntityList, c est au fond un "Handle" bien entoure :
// S il est nul, la liste est vide
// Si c est une Entite, la liste comprend cette entite et rien d autre
// Si c est un EntityCluster, il definit (avec ses Next eventuels) le contenu
// de la liste


Interface_EntityList::Interface_EntityList ()    {  }

    void  Interface_EntityList::Clear ()
      {  theval.Nullify();  }

//  ....                EDITIONS (ajout-suppression)                ....

    void  Interface_EntityList::Append
  (const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityList Append");
  if (theval.IsNull()) {  theval = ent;  return;  }
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) ec->Append(ent);    // EntityCluster
  else {                                // reste InterfaceEntity ...
    Handle(Interface_EntityCluster) ec = new Interface_EntityCluster(theval);
    ec->Append(ent);
    theval = ec;
  }
}

// Difference avec Append : on optimise, en evitant la recursivite
// En effet, quand un EntityCluster est plein, Append transmet au Next
// Ici, EntityList garde le controle, le temps de traitement reste le meme
// Moyennant quoi, l ordre n est pas garanti

    void  Interface_EntityList::Add
  (const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityList Add");
  if (theval.IsNull()) {  theval = ent;  return;  }
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) {               // EntityCluster
    if (ec->IsLocalFull()) theval = new Interface_EntityCluster(ent,ec);
    else ec->Append (ent);
  } else {                          // reste InterfaceEntity ...
    Handle(Interface_EntityCluster) ec = new Interface_EntityCluster(theval);
    ec->Append(ent);
    theval = ec;
  }
}

//  Remove : Par Identification d Item a supprimer, ou par Rang
//  Identification : Item supprime ou qu il soit
//  N.B.: La liste peut devenir vide ... cf retour Remove de Cluster

    void  Interface_EntityList::Remove (const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityList Remove");
  if (theval.IsNull()) return;
  if (theval == ent) {
    theval.Nullify();
    return;
  }
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (ec.IsNull()) return;   // Une seule Entite et pas la bonne
  Standard_Boolean res = ec->Remove(ent);
  if (res) theval.Nullify();
}

//  Remove par rang : tester OutOfRange

    void  Interface_EntityList::Remove  (const Standard_Integer num)
{
  if (theval.IsNull()) Standard_OutOfRange::Raise("EntityList : Remove");
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (ec.IsNull()) {
    if (num != 1) Standard_OutOfRange::Raise("EntityList : Remove");
    theval.Nullify();
    return;
  }
  Standard_Boolean res = ec->Remove(num);
  if (res) theval.Nullify();
}

//  ....                    ACCES Unitaire AUX DONNEES                    ....

    Standard_Boolean  Interface_EntityList::IsEmpty () const 
      {  return (theval.IsNull());  }

    Standard_Integer  Interface_EntityList::NbEntities () const 
{
  if (theval.IsNull()) return 0;
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (ec.IsNull()) return 1;   // Une seuke Entite
  return ec->NbEntities();
}


    const Handle(Standard_Transient)&  Interface_EntityList::Value
  (const Standard_Integer num) const 
{
  if (theval.IsNull()) Standard_OutOfRange::Raise("Interface EntityList : Value");
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) return ec->Value(num);  // EntityCluster
  else if (num != 1) Standard_OutOfRange::Raise("Interface EntityList : Value");
  return theval;
}

    void  Interface_EntityList::SetValue
  (const Standard_Integer num, const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityList SetValue");
  if (theval.IsNull()) Standard_OutOfRange::Raise("Interface EntityList : SetValue");
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) ec->SetValue(num,ent);   // EntityCluster
  else if (num != 1) Standard_OutOfRange::Raise("Interface EntityList : SetValue");
  else theval = ent;

}

//  ....                Interrogations Generales                ....

    void  Interface_EntityList::FillIterator
  (Interface_EntityIterator& iter) const 
{
  if (theval.IsNull()) return;
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) ec->FillIterator(iter);    // EntityCluster;
  else iter.GetOneItem(theval);
}


    Standard_Integer Interface_EntityList::NbTypedEntities
  (const Handle(Standard_Type)& atype) const
{
  Standard_Integer res = 0;
  if (theval.IsNull()) return 0;
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) {                // EntityCluster
    while (!ec.IsNull()) {
      for (Standard_Integer i = ec->NbLocal(); i > 0; i --) {
	if (ec->Value(i)->IsKind(atype)) res ++;
      }
      if (!ec->HasNext()) break;
      ec = ec->Next();
    }
  } else {                           // Une seule Entite
    if (theval->IsKind(atype)) res = 1;
  }
  return res;
}

    Handle(Standard_Transient) Interface_EntityList::TypedEntity
  (const Handle(Standard_Type)& atype, const Standard_Integer num) const
{
  Standard_Integer res = 0;
  Handle(Standard_Transient) entres;
  if (theval.IsNull()) Interface_InterfaceError::Raise
    ("Interface EntityList : TypedEntity , none found");
  Handle(Interface_EntityCluster) ec =
    Handle(Interface_EntityCluster)::DownCast(theval);
  if (!ec.IsNull()) {                // EntityCluster
    while (!ec.IsNull()) {
      for (Standard_Integer i = ec->NbLocal(); i > 0; i --) {
	if (ec->Value(i)->IsKind(atype)) {
	  res ++;
	  if (num == 0 && res > 1) Interface_InterfaceError::Raise
	    ("Interface EntityList : TypedEntity , several found");
	  entres = ec->Value(i);
	  if (res == num) return entres;
	}
      }
      if (!ec->HasNext()) break;
      ec = ec->Next();
    }
  } else if (num > 1) {
    Interface_InterfaceError::Raise
      ("Interface EntityList : TypedEntity ,out of range");
  } else {                          // InterfaceEntity
    if (!theval->IsKind(atype)) Interface_InterfaceError::Raise
      ("Interface EntityList : TypedEntity , none found");
    entres = theval;
  }
  return entres;
}
