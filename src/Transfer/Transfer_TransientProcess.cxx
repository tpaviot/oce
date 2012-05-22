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

#include <Transfer_TransientProcess.ixx>
#include <Interface_Check.hxx>
#include <Interface_MSG.hxx>
#include <Transfer_Binder.hxx>
#include <TColStd_HSequenceOfTransient.hxx>


//=======================================================================
//function : Transfer_TransientProcess
//purpose  : 
//=======================================================================

Transfer_TransientProcess::Transfer_TransientProcess
  (const Standard_Integer nb) : Transfer_ProcessForTransient (nb)  
{  
  thetrroots = new TColStd_HSequenceOfTransient;
}


//=======================================================================
//function : SetModel
//purpose  : 
//=======================================================================

void Transfer_TransientProcess::SetModel
  (const Handle(Interface_InterfaceModel)& model)
{
  themodel = model;
}


//=======================================================================
//function : Model
//purpose  : 
//=======================================================================

Handle(Interface_InterfaceModel) Transfer_TransientProcess::Model () const
{
  return themodel;
}


void Transfer_TransientProcess::SetGraph(const Handle(Interface_HGraph)& HG)
{
  thegraph = HG;
  if (!thegraph.IsNull())
    SetModel(thegraph->Graph().Model());
  else
    themodel.Nullify();
}


//=======================================================================
//function : HasGraph
//purpose  : 
//=======================================================================

Standard_Boolean Transfer_TransientProcess::HasGraph () const
{
  return !thegraph.IsNull();
}


//=======================================================================
//function : HGraph
//purpose  : 
//=======================================================================

Handle(Interface_HGraph) Transfer_TransientProcess::HGraph () const
{
  return thegraph;
}


//=======================================================================
//function : Graph
//purpose  : 
//=======================================================================

const Interface_Graph& Transfer_TransientProcess::Graph () const
{
  return thegraph->Graph();
}


//=======================================================================
//function : SetContext
//purpose  : 
//=======================================================================

void Transfer_TransientProcess::SetContext(const Standard_CString name,
                                           const Handle(Standard_Transient)& ctx)
{
  if (thectx.IsNull()) thectx = new Dico_DictionaryOfTransient;
  thectx->SetItem (name,ctx);
}


//=======================================================================
//function : GetContext
//purpose  : 
//=======================================================================

Standard_Boolean Transfer_TransientProcess::GetContext
  (const Standard_CString name, const Handle(Standard_Type)& type,
   Handle(Standard_Transient)& ctx) const
{
  if (thectx.IsNull()) return Standard_False;
  if (!thectx->GetItem (name,ctx)) ctx.Nullify();
  if (ctx.IsNull()) return Standard_False;
  if (type.IsNull()) return Standard_True;
  if (!ctx->IsKind(type)) ctx.Nullify();
  return !ctx.IsNull();
}


//=======================================================================
//function : Context
//purpose  : 
//=======================================================================

Handle(Dico_DictionaryOfTransient)& Transfer_TransientProcess::Context ()
{
  return thectx;
}


//=======================================================================
//function : PrintTrace
//purpose  : 
//=======================================================================

void Transfer_TransientProcess::PrintTrace
  (const Handle(Standard_Transient)& start, const Handle(Message_Messenger)& S) const
{
  if (!start.IsNull()) {
    S << "Entity ";
    if (!themodel.IsNull()) {
      themodel->Print (start,S,1);
//      S<<"id ";  themodel->Print (start,S);
//      S<<" Type:"<<themodel->TypeName (start);
    }
    else S<<" Type:"<< Interface_InterfaceModel::ClassName(start->DynamicType()->Name());
 //  << start (handle)  ??
  }
}


//=======================================================================
//function : CheckNum
//purpose  : 
//=======================================================================

Standard_Integer Transfer_TransientProcess::CheckNum
  (const Handle(Standard_Transient)& start) const
{
  return (themodel.IsNull() ? 0 : themodel->Number(start));
}


//=======================================================================
//function : TypedSharings
//purpose  : 
//=======================================================================

Interface_EntityIterator Transfer_TransientProcess::TypedSharings
  (const Handle(Standard_Transient)& start,
   const Handle(Standard_Type)& type) const
{
  Interface_EntityIterator iter;
  if (thegraph.IsNull()) return iter;
  return thegraph->Graph().TypedSharings (start,type);
}


//=======================================================================
//function : IsDataLoaded
//purpose  : 
//=======================================================================

Standard_Boolean Transfer_TransientProcess::IsDataLoaded
  (const Handle(Standard_Transient)& start) const
{
  if (themodel.IsNull()) return Standard_True;
  Standard_Integer num = themodel->Number(start);
  if (num == 0) return Standard_True;
  if (themodel->IsUnknownEntity(num)) return Standard_False;
  return !themodel->IsRedefinedContent(num);
}


//=======================================================================
//function : IsDataFail
//purpose  : 
//=======================================================================

Standard_Boolean Transfer_TransientProcess::IsDataFail
  (const Handle(Standard_Transient)& start) const
{
  if (themodel.IsNull()) return Standard_False;
  Standard_Integer num = themodel->Number(start);
  if (num == 0) return Standard_False;
  if (themodel->IsErrorEntity(num)) return Standard_True;
  const Handle(Interface_Check) ach = themodel->Check(num,Standard_False); // semantic
  return ach->HasFailed();
}


//=======================================================================
//function : PrintStats
//purpose  : 
//=======================================================================

void Transfer_TransientProcess::PrintStats(const Standard_Integer /*mode*/,
                                           const Handle(Message_Messenger)& S) const
{
  S<<"\n*******************************************************************\n";
//  if (mode == 1) {    //  Statistiques de base
    S << "********                 Basic Statistics                  ********"<<endl;

    Handle(Interface_InterfaceModel) model = Model();
    if (model.IsNull())      S<<"****        Model unknown"<<endl;
    else
      S<<"****        Nb Entities         : "<<model->NbEntities()<<endl;

    Standard_Integer nbr = 0, nbe = 0, nbw = 0;
    Standard_Integer i, max = NbMapped(), nbroots = NbRoots();
    S << "****        Nb Final Results    : "<<nbroots<<endl;

    for (i = 1; i <= max; i ++) {
      const Handle(Transfer_Binder)& binder = MapItem(i);
      if (binder.IsNull()) continue;
      const Handle(Interface_Check) ach = binder->Check();
      Transfer_StatusExec stat = binder->StatusExec();
      if (stat != Transfer_StatusInitial && stat != Transfer_StatusDone)
	nbe ++;
      else {
	if (ach->NbWarnings() > 0) nbw ++;
	if (binder->HasResult())  nbr ++;
      }
    }
    if (nbr > nbroots)
      S<<"****      ( Itermediate Results : "<<nbr-nbroots<<" )\n";
    if (nbe > 0)
      S<<"****                  Errors on : "<<Interface_MSG::Blanks(nbe,4)<<nbe<<" Entities\n";
    if (nbw > 0)
      S<<"****                Warnings on : "<<Interface_MSG::Blanks(nbw,4)<<nbw<<" Entities\n";
    S<<"*******************************************************************";
//  }
  S<<endl;
}


//=======================================================================
//function : RootsForTransfer
//purpose  : 
//=======================================================================

Handle(TColStd_HSequenceOfTransient) Transfer_TransientProcess::RootsForTransfer() 
{
  return thetrroots;
}
