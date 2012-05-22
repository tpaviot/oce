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

#include <IFSelect_SelectSignature.ixx>


//  theexact : -1  OUI   0  NON une seule valeur  > 0 NON nb de valeurs
//  signmode : 1 prendre si contenu, 2 refuser si contenu
//             3 prendre si egal,    4 refuser si egal
//  ou test numerique, ajouter : 16 <  24 <=  32 >  40 >=

static Standard_Integer multsign
  (const TCollection_AsciiString& signtext,
   TColStd_SequenceOfAsciiString& signlist,
   TColStd_SequenceOfInteger&     signmode)
{
  Standard_Integer i, nb = signtext.Length(), mode = 0;
  for (i = 1; i <= nb; i ++) {
    char unsign = signtext.Value(i);
    if (unsign == '|' || unsign == '!' || unsign == '=') { mode = 1; break; }
    if (unsign == '<' || unsign == '>') { mode = 1; break; }
  }
  if (mode == 0) return mode;
//  On va tronconner
  TCollection_AsciiString item;  Standard_Integer imod = 1;
  for (i = 1; i <= nb; i ++) {
    char unsign = signtext.Value(i);
    if (unsign == '|' || unsign == '!') {
      if (item.Length() > 0) {
	signlist.Append (item);
	signmode.Append (imod);
	item.Clear();
	mode ++;
      }
      imod = (unsign == '|' ? 1 : 2);
    }
    else if (unsign == '<') imod += 16;
    else if (unsign == '>') imod += 32;
    else if (unsign == '=') { if (imod < 8) imod += 2; else imod += 8; }
    else item.AssignCat (unsign);
  }
  if (item.Length() > 0) {
    signlist.Append (item);
    signmode.Append (imod);
//    mode ++;  valait un au depart
  }
  return mode;
}



    IFSelect_SelectSignature::IFSelect_SelectSignature
  (const Handle(IFSelect_Signature)& matcher,
   const TCollection_AsciiString& signtext, const Standard_Boolean exact)
    : thematcher (matcher) , thesigntext (signtext) , theexact (exact ? -1 : 0)
{  if (!exact) theexact = multsign (thesigntext,thesignlist,thesignmode);  }

    IFSelect_SelectSignature::IFSelect_SelectSignature
  (const Handle(IFSelect_Signature)& matcher,
   const Standard_CString signtext, const Standard_Boolean exact)
    : thematcher (matcher) , thesigntext (signtext) , theexact (exact ? -1 : 0)
{  if (!exact) theexact = multsign (thesigntext,thesignlist,thesignmode);  }

    IFSelect_SelectSignature::IFSelect_SelectSignature
  (const Handle(IFSelect_SignCounter)& counter,
   const Standard_CString signtext, const Standard_Boolean exact)
    : thecounter (counter) , thesigntext (signtext) , theexact (exact ? -1 : 0)
{  if (!exact) theexact = multsign (thesigntext,thesignlist,thesignmode);  }

    Handle(IFSelect_Signature)  IFSelect_SelectSignature::Signature () const
      {  return thematcher;  }

    Handle(IFSelect_SignCounter)  IFSelect_SelectSignature::Counter () const
      {  return thecounter;  }


    Standard_Boolean  IFSelect_SelectSignature::SortInGraph
  (const Standard_Integer , const Handle(Standard_Transient)& ent,
   const Interface_Graph& G) const
{
  Standard_Boolean res;
  Standard_CString txt;
  Handle(Interface_InterfaceModel) model = G.Model();
  if (theexact <= 0) {
    if (!thematcher.IsNull()) return thematcher->Matches (ent,model,thesigntext, (theexact < 0));
    txt = thecounter->ComputedSign(ent,G);
    return IFSelect_Signature::MatchValue (txt,thesigntext , (theexact < 0));
  }

//  sinon : liste
//  Analyse en sequence : si alternance prend/prend-pas, le dernier a raison
//   en consequence, si que des prend ou que des prend-pas, c est commutatif
//   DONC recommandation : mettre les prend-pas en fin

//  AU DEPART : prendre = ne prendre que. prend-pas = prend-tout-sauf ...
//  Donc si le premier est un prend-pas, je commence par tout prendre
  Standard_Integer hmod = thesignmode.Value(1);
  Standard_Integer jmod = hmod/8;
  Standard_Integer imod = hmod - (jmod*8);
  res = (imod == 2 || imod == 4);
  for (Standard_Integer i = 1; i <= theexact; i ++) {
    Standard_CString signtext = thesignlist.Value(i).ToCString();
    hmod = thesignmode.Value(i);
    jmod = hmod/8;
    imod = hmod - (jmod*8);
    Standard_Boolean quid;
    if (jmod == 0) {
      if (!thematcher.IsNull()) quid = thematcher->Matches (ent,model,signtext,(imod > 2));
      else quid = IFSelect_Signature::MatchValue
	( thecounter->ComputedSign(ent,G),signtext, (imod > 2) );
    }
    else {
      if (!thematcher.IsNull()) txt = thematcher->Value (ent,model);
      else txt = thecounter->ComputedSign (ent,G);

      Standard_Integer val = atoi(txt);
      Standard_Integer lav = atoi (signtext);
      switch (jmod) {
        case 2 : quid = (val <  lav); break;
        case 3 : quid = (val <= lav); break;
        case 4 : quid = (val >  lav); break;
        case 5 : quid = (val >= lav); break;
	default : quid = Standard_False; break;
      }
    }
    if ((imod == 1 || imod == 3) && quid) res = Standard_True;
    if ((imod == 2 || imod == 4) && quid) res = Standard_False;
  }
  return res;
}

    Standard_Boolean  IFSelect_SelectSignature::Sort
  (const Standard_Integer , const Handle(Standard_Transient)& ent,
   const Handle(Interface_InterfaceModel)& model) const
{  return Standard_True;  }

    const TCollection_AsciiString&  IFSelect_SelectSignature::SignatureText () const
      {  return thesigntext;  }

    Standard_Boolean  IFSelect_SelectSignature::IsExact () const
      {  return (theexact < 0);  }

    TCollection_AsciiString  IFSelect_SelectSignature::ExtractLabel () const
{
  TCollection_AsciiString lab;
  if (!thematcher.IsNull()) lab.AssignCat (thematcher->Name());
  else                      lab.AssignCat (thecounter->Name());
  if      (theexact  < 0) lab.AssignCat(" matching ");
  else if (theexact == 0) lab.AssignCat(" containing ");
  else                    lab.AssignCat(" matching list ");
  lab.AssignCat(thesigntext);
  return lab;
}
