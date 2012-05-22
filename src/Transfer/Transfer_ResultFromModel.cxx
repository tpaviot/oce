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

#include <Transfer_ResultFromModel.ixx>
#include <TColStd_IndexedMapOfTransient.hxx>
#include <Interface_Check.hxx>
#include <Interface_Macros.hxx>
#include <Transfer_Binder.hxx>
#include <TCollection_HAsciiString.hxx>


Transfer_ResultFromModel::Transfer_ResultFromModel ()
      {  themnum = 0;  themchk = Interface_CheckAny;  }

    void  Transfer_ResultFromModel::SetModel
  (const Handle(Interface_InterfaceModel)& model)
      {  themodel = model;  }

    void  Transfer_ResultFromModel::SetFileName
  (const Standard_CString filename)
      {  thename.Clear();  thename.AssignCat(filename);  }

    Handle(Interface_InterfaceModel)  Transfer_ResultFromModel::Model () const
      {  return themodel;  }

    Standard_CString  Transfer_ResultFromModel::FileName () const
      {  return thename.ToCString();  }


    Standard_Boolean  Transfer_ResultFromModel::Fill
  (const Handle(Transfer_TransientProcess)& TP,
   const Handle(Standard_Transient)& ent)
{
  if (TP.IsNull() || ent.IsNull()) return Standard_False;
  Handle(Transfer_Binder) binder = TP->Find (ent);
  if (binder.IsNull()) return Standard_False;
  themain = new Transfer_ResultFromTransient;
  themain->SetStart  (ent);
  themain->SetBinder (binder);
  themain->Fill (TP);
//   Substitution de resultat pour la Shape (-> HShape) : pas ici, on est
//   dans le pk Transfer qui est general et ne sait pas ce qu est une Shape ...
  if (!TP->Model().IsNull()) themodel = TP->Model();
  if (themodel.IsNull()) return Standard_True;
  themnum = themodel->Number (ent);
  themlab.Clear();
  if (themnum > 0)
    themlab.AssignCat (themodel->StringLabel(ent)->ToCString());
  return Standard_True;
}

    void  Transfer_ResultFromModel::Strip (const Standard_Integer mode)
{
  if (themain.IsNull()) return;
  themain->Strip();
  if (mode >= 10) {
    themchk = ComputeCheckStatus (Standard_False);
    themodel.Nullify();
    themain->ClearSubs();
    Handle(Standard_Transient) nulh;  themain->SetStart(nulh);
    if (mode > 10) themain.Nullify();
  }
}

    void  Transfer_ResultFromModel::FillBack
  (const Handle(Transfer_TransientProcess)& TP) const
{
  if (!themodel.IsNull()) TP->SetModel(themodel);
  themain->FillBack (TP);
}


    Standard_Boolean  Transfer_ResultFromModel::HasResult () const
{  return (themain.IsNull() ? Standard_False : themain->HasResult());  }

    Handle(Transfer_ResultFromTransient)  Transfer_ResultFromModel::MainResult
  () const
      {  return themain;  }

    void  Transfer_ResultFromModel::SetMainResult
  (const Handle(Transfer_ResultFromTransient)& amain)
{
  themchk = Interface_CheckAny;
  themain = amain;
  if (themodel.IsNull() || themain.IsNull()) return;
  themnum = themodel->Number (themain->Start());
  themlab.Clear();
  if (themnum > 0)
    themlab.AssignCat (themodel->StringLabel(themain->Start())->ToCString());
}

    Standard_CString  Transfer_ResultFromModel::MainLabel  () const
      {  return themlab.ToCString();  }

    Standard_Integer  Transfer_ResultFromModel::MainNumber () const
      {  return themnum;  }


//  ############  INFORMATIONS  GLOBALES  ###########

    Handle(Transfer_ResultFromTransient)  Transfer_ResultFromModel::ResultFromKey
  (const Handle(Standard_Transient)& start) const
      {  return themain->ResultFromKey (start);  }

    Handle(TColStd_HSequenceOfTransient)  Transfer_ResultFromModel::Results
  (const Standard_Integer level) const
{
  Standard_Integer i,nb;
  Handle(TColStd_HSequenceOfTransient) list = new TColStd_HSequenceOfTransient();
  if (level > 1) {
    TColStd_IndexedMapOfTransient map (themodel.IsNull() ? 1000 : themodel->NbEntities());
    map.Add(themain);
    themain->FillMap(map);
    nb = map.Extent();
    for (i = 1; i <= nb; i ++)  list->Append(map.FindKey(i));
  }
  else list->Append(themain);
  if (level == 1) {
    nb = themain->NbSubResults();
    for (i = 1; i <= nb; i ++)  list->Append(themain->SubResult(i));
    list->Append(themain);
  }
  return list;
}


    Handle(TColStd_HSequenceOfTransient)  Transfer_ResultFromModel::TransferredList
  (const Standard_Integer level) const
{
  Standard_Integer i,nb;
  Handle(TColStd_HSequenceOfTransient) list = new TColStd_HSequenceOfTransient();
  Handle(TColStd_HSequenceOfTransient) res  = Results(level);
  nb = res->Length();
  for (i = 1; i <= nb; i ++) {
    DeclareAndCast(Transfer_ResultFromTransient,unres,res->Value(i));
    if (unres.IsNull()) continue;
    if (unres->HasResult()) list->Append (unres->Start());
  }
  return list;
}

    Handle(TColStd_HSequenceOfTransient)  Transfer_ResultFromModel::CheckedList
  (const Interface_CheckStatus check, const Standard_Boolean result) const
{
  Standard_Integer i,nb;
  Handle(TColStd_HSequenceOfTransient) list = new TColStd_HSequenceOfTransient();
  Handle(TColStd_HSequenceOfTransient) res  = Results(2);
  nb = res->Length();
  for (i = 1; i <= nb; i ++) {
    DeclareAndCast(Transfer_ResultFromTransient,unres,res->Value(i));
    if (unres.IsNull()) continue;
    if (result && !unres->HasResult()) continue;
    const Handle(Interface_Check) ach = unres->Check();
    if (ach->Complies(check)) list->Append (unres->Start());
  }
  return list;
}

    Interface_CheckIterator  Transfer_ResultFromModel::CheckList
  (const Standard_Boolean erronly, const Standard_Integer level) const
{
  Interface_CheckIterator chl;
  Standard_Integer i,nb;
  Handle(TColStd_HSequenceOfTransient) list = new TColStd_HSequenceOfTransient();
  Handle(TColStd_HSequenceOfTransient) res  = Results(level);
  nb = res->Length();
  for (i = 1; i <= nb; i ++) {
    DeclareAndCast(Transfer_ResultFromTransient,unres,res->Value(i));
    if (unres.IsNull()) continue;
    Interface_CheckStatus stat = unres->CheckStatus();
    if ( stat == Interface_CheckOK ||
	(stat == Interface_CheckWarning && erronly)) continue;
    Handle(Transfer_Binder) binder = unres->Binder();
    Handle(Interface_Check) bch = binder->Check();
    bch->SetEntity(unres->Start());
    chl.Add(bch, (themodel.IsNull() ? 0 : themodel->Number(unres->Start())) );
  }
  return chl;
}

    Interface_CheckStatus  Transfer_ResultFromModel::CheckStatus () const
{
  if (themchk != Interface_CheckAny) return themchk;
  Interface_CheckIterator chl = CheckList (Standard_False,2);
  return chl.Status();
}

    Interface_CheckStatus  Transfer_ResultFromModel::ComputeCheckStatus
  (const Standard_Boolean enforce)
{
  if (themchk == Interface_CheckAny || enforce) themchk = CheckStatus();
  return themchk;
}
