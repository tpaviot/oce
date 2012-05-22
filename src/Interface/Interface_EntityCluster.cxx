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

#include <Interface_EntityCluster.ixx>
#include <Standard_OutOfRange.hxx>
#include <Standard_NullObject.hxx>

// Un Cluster, ce sont 4 entites qui se suivent (dans le principe, nombre fixe,
// meme si pas 4). Elles sont remplies depuis 0. Il y a donc autant d Entites
// que de Handles non Nuls, plus le fait qu ils sont remplis dans l ordre

// Ainsi (avec Next), on consomme 5 Handles pour 4 Entites, avec une pointe
// pour 1 et 2 Entites (on reste a 5 Handles)

// Suppression : On retasse le Cluster pour que les Nulls soient tjrs a la fin

//  ....                        CONSTRUCTEURS                        ....

Interface_EntityCluster::Interface_EntityCluster ()    {  }

    Interface_EntityCluster::Interface_EntityCluster
  (const Handle(Standard_Transient)& ent)
      {  theents[0] = ent;  }

    Interface_EntityCluster::Interface_EntityCluster
  (const Handle(Interface_EntityCluster)& ec)
      {  thenext = ec;  }

    Interface_EntityCluster::Interface_EntityCluster
  (const Handle(Standard_Transient)& ent,
   const Handle(Interface_EntityCluster)& ec)
      {  theents[0] = ent;  thenext = ec;  }

//  ....                        AJOUT - SUPPRESSION                        ....

    void  Interface_EntityCluster::Append
  (const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityCluster Append");
  if      (theents[0].IsNull()) theents[0] = ent;
  else if (theents[1].IsNull()) theents[1] = ent;
  else if (theents[2].IsNull()) theents[2] = ent;
  else if (theents[3].IsNull()) theents[3] = ent;
  else {                                // Si celui-ci est plein ...
    if (thenext.IsNull()) thenext = new Interface_EntityCluster(ent);
    else thenext->Append(ent);
  }
}

    Standard_Boolean  Interface_EntityCluster::Remove
  (const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityCluster Remove");
  Standard_Integer i;
//  <ent> est-il ici ? si oui, on a son rang
  if      (ent == theents[0]) i = 1;
  else if (ent == theents[1]) i = 2;
  else if (ent == theents[2]) i = 3;
  else if (ent == theents[3]) i = 4;

//  Sinon, passer au suivant, qui peut du coup devenir vide ->
//  On enleve le cluster vide de la liste (en principe cest le dernier)
  else {                                // Pas trouve dans celui-ci ...
    if (thenext.IsNull()) return Standard_False;
    Standard_Integer res = thenext->Remove(ent);
    if (res) thenext = thenext->Next();
    return Standard_False;
  }
  return Remove(i);
}

    Standard_Boolean  Interface_EntityCluster::Remove
  (const Standard_Integer num)
{
  if (num < 1) Standard_OutOfRange::Raise("EntityCluster : Remove");
  Standard_Integer n = NbLocal();
  if (num > n) {
    if (thenext.IsNull()) Standard_OutOfRange::Raise("EntityCluster : Remove");
    Standard_Boolean res = thenext->Remove (num-n);
    if (res) thenext = thenext->Next();
    return Standard_False;
  }
  for (Standard_Integer j = num; j < n; j --) theents[j-1] = theents[j];
  theents[3].Nullify();     // On Nullify par la fin
  return (n == 1);          // Ancien NbLocal == 1  -> devient nul
}

//  ....                        ACCES AUX DONNEES                        ....

    Standard_Integer  Interface_EntityCluster::NbEntities() const 
{
  Standard_Integer nb = NbLocal();
  if (!thenext.IsNull()) nb += thenext->NbEntities();
  return nb;
}

    const Handle(Standard_Transient)&  Interface_EntityCluster::Value
  (const Standard_Integer num) const
{
  Standard_Integer nb = NbLocal();
  if (num <= 0) Standard_OutOfRange::Raise("Interface EntityCluster : Value");
  if (num > nb) {
    if (thenext.IsNull()) Standard_OutOfRange::Raise
      ("Interface EntityCluster : Value");
    return thenext->Value(num-nb);
  }
  return theents[num-1];  // numerotation a partir de 0
}

    void  Interface_EntityCluster::SetValue
  (const Standard_Integer num, const Handle(Standard_Transient)& ent)
{
  if (ent.IsNull()) Standard_NullObject::Raise("Interface_EntityCluster SetValue");
  Standard_Integer nb = NbLocal();
  if (num <= 0) Standard_OutOfRange::Raise("Interface EntityCluster : SetValue");
  if (num > nb) {
    if (thenext.IsNull()) Standard_OutOfRange::Raise
      ("Interface EntityCluster : SetValue");
    thenext->SetValue(num-nb,ent);
  }
  else theents[num-1] = ent;  // numerotation a partir de 0
}

    void  Interface_EntityCluster::FillIterator
  (Interface_EntityIterator& iter) const 
{
  if (!theents[0].IsNull()) iter.GetOneItem(theents[0]);
  if (!theents[1].IsNull()) iter.GetOneItem(theents[1]);
  if (!theents[2].IsNull()) iter.GetOneItem(theents[2]);
  if (!theents[3].IsNull()) iter.GetOneItem(theents[3]);
  if (!thenext.IsNull()) thenext->FillIterator(iter);
}

//  ....                    Actions atomiques internes                    ....

Standard_Boolean  Interface_EntityCluster::IsLocalFull () const 
{
  // Solaris Forte C++ compiler insisted it couldn't cast this,
  // even though it seems to do so elsewhere
  Handle_Standard_Transient tmp = Handle_Standard_Transient(theents[3]);
  return ( !tmp.IsNull() );
}

    Standard_Integer  Interface_EntityCluster::NbLocal () const
{
  Standard_Integer nb;
  if      (!theents[3].IsNull()) nb = 4;
  else if (!theents[2].IsNull()) nb = 3;
  else if (!theents[1].IsNull()) nb = 2;
  else if (!theents[0].IsNull()) nb = 1;
  else                           nb = 0;
  return nb;
}

    Standard_Boolean  Interface_EntityCluster::HasNext () const 
      {  return (!thenext.IsNull());  }

    Handle(Interface_EntityCluster)  Interface_EntityCluster::Next () const 
      {  return thenext;  }
