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

//szv#4 S4163
#include <Interface_ParamSet.ixx>


Interface_ParamSet::Interface_ParamSet (const Standard_Integer nres, const Standard_Integer )//nst)
{
  thelist = new Interface_ParamList;// (nst,nst+nres+2);
  themxpar = nres;
  thenbpar = 0;
  thelnval = 0;
  thelnres = 100; // *20;  // 10 caracteres par Param (\0 inclus) : raisonnable
  theval   = new char[thelnres]; //szv#4:S4163:12Mar99 `thelnres+1` chars was wrong
}


//  Append(CString) : Gestion des caracteres selon <lnval>
//  Si lnval < 0, ParamSet passif, memoire geree de l exterieur, ParamSet
//                se contente de s y referer
//  Sinon, recopie dans une page locale

Standard_Integer  Interface_ParamSet::Append (const Standard_CString val, const Standard_Integer lnval,
					      const Interface_ParamType typ, const Standard_Integer nument)
{
  //  Ici, gestion locale de String
  thenbpar ++;
  if (thenbpar > themxpar) {
    thenext = new Interface_ParamSet (themxpar,1);
    return (thenbpar + thenext->Append(val,lnval,typ,nument));
  }
  else if (lnval < 0) {
    //    ..  Gestion externe des caracteres  ..
    Interface_FileParameter& FP = thelist->ChangeValue(thenbpar);
    FP.Init(val,typ);
    if (nument != 0) FP.SetEntityNumber(nument);
  }
  else {
    //    ..  Gestion locale des caracteres  ..
    Standard_Integer i;
    if (thelnval + lnval + 1 > thelnres) {
      //      Reservation de caracteres insuffisante : d abord augmenter
      Standard_Integer newres = thelnres*2 + lnval ;
      char* newval = new char[newres];
      for (i = 0; i < thelnval; i++) 
        newval[i] = theval[i]; //szv#4:S4163:12Mar99 `<= thelnres` was wrong
      //      et cepatou : il faut realigner les Params deja enregistres sur
      //      l ancienne reservation de caracteres ...
      //Standard_Integer delta = (Standard_Integer) (newval - theval);
      // difference a appliquer
      char* poldVal = &theval[0];
      char* pnewVal= &newval[0];
      for (i = 1; i < thenbpar; i ++) {
	Interface_FileParameter& OFP = thelist->ChangeValue(i);
	Interface_ParamType otyp = OFP.ParamType();
	char* oval = (char*)OFP.CValue();
        Standard_Integer delta = (Standard_Integer) (oval - poldVal);
	//if (oval < theval || oval >= (theval+thelnres)) 
        //  continue;  //hors reserve //szv#4:S4163:12Mar99 `oval >` was wrong
	Standard_Integer onum = OFP.EntityNumber();
	OFP.Init(pnewVal+delta,otyp);    // et voila; on remet dans la boite
	if (onum != 0) OFP.SetEntityNumber(onum);
      }
      //      Enteriner la nouvelle reservation
      delete [] theval;
      theval   = newval;
      thelnres = newres;
    }
    //      Enregistrer ce parametre
    for (i = 0; i < lnval; i ++)  theval[thelnval + i] = val[i];
    theval[thelnval+lnval] = '\0';

    Interface_FileParameter& FP = thelist->ChangeValue(thenbpar);
    FP.Init(&theval[thelnval],typ);
    if (nument != 0) FP.SetEntityNumber(nument);
    thelnval += (lnval+1);
  }
  return thenbpar;
}

Standard_Integer  Interface_ParamSet::Append (const Interface_FileParameter& FP)
{
  //  Ici, FP tout pret : pas de gestion memoire sur String (dommage)

  thenbpar ++;
  if (thenbpar > themxpar) {
    thenext = new Interface_ParamSet (themxpar,1);
    return thenbpar + thenext->Append(FP);
  }
  thelist->SetValue(thenbpar,FP);
  return thenbpar;
}

Standard_Integer Interface_ParamSet::NbParams () const 
{  return thenbpar;  }

const Interface_FileParameter& Interface_ParamSet::Param (const Standard_Integer num) const 
{
  if (num > themxpar) return thenext->Param(num - themxpar);
  else return thelist->Value(num);
}

Interface_FileParameter& Interface_ParamSet::ChangeParam (const Standard_Integer num)
{
  if (num > themxpar) return thenext->ChangeParam(num - themxpar);
  else return thelist->ChangeValue(num);
}

void Interface_ParamSet::SetParam (const Standard_Integer num, const Interface_FileParameter& FP)
{
  if (num > themxpar) thenext->SetParam(num - themxpar, FP);
  else thelist->SetValue(num,FP);
}

Handle(Interface_ParamList) Interface_ParamSet::Params (const Standard_Integer num,
							const Standard_Integer nb) const 
{
  Standard_Integer i, n0 = num-1, nbp = nb;
  if (num > themxpar) 
    return thenext->Params (num-themxpar,nb);
  if (num == 0 && nb == 0) {
    n0 = 0;  nbp = thenbpar;
    if (thenbpar <= themxpar) 
      return thelist;  // et zou
  }
  Handle(Interface_ParamList) list = new Interface_ParamList;
  if (nb == 0) 
    return list;
  
  for (i = 1; i <= nbp; i ++) list->SetValue(i,Param(n0+i));
  return list;
}

void Interface_ParamSet::Destroy () 
{
  //  if (!thenext.IsNull()) thenext->Destroy();
  thenext.Nullify();
  //  Destruction "manuelle" (gestion memoire directe)
  if (theval) delete [] theval;
  theval = NULL;
  thelist->Clear();
  thelist.Nullify();
}
