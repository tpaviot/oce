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
#include <Transfer_TransferOutput.ixx>
#include <Transfer_Binder.hxx>
#include <Interface_ShareFlags.hxx>
#include <Interface_EntityIterator.hxx>
#include <Transfer_TransferFailure.hxx>



Transfer_TransferOutput::Transfer_TransferOutput (const Handle(Transfer_ActorOfTransientProcess)& actor,
						  const Handle(Interface_InterfaceModel)& amodel)
{
  theproc  = new Transfer_TransientProcess (amodel->NbEntities());
  theproc->SetActor(actor);
  themodel = amodel;
//  thescope = Standard_False;
//  theundef = Transfer_UndefIgnore;
}

Transfer_TransferOutput::Transfer_TransferOutput (const Handle(Transfer_TransientProcess)& proc,
						  const Handle(Interface_InterfaceModel)& amodel)
{
  theproc  = proc;
  themodel = amodel;
//  thescope = Standard_False; //szv#4:S4163:12Mar99 initialization needed
//  theundef = Transfer_UndefIgnore;
}

//Standard_Boolean&  Transfer_TransferOutput::ScopeMode ()
//{  return  thescope;  }

Handle(Interface_InterfaceModel)  Transfer_TransferOutput::Model () const
{  return themodel;  }

Handle(Transfer_TransientProcess)  Transfer_TransferOutput::TransientProcess () const
{  return theproc;  }

void  Transfer_TransferOutput::Transfer (const Handle(Standard_Transient)& obj)
{
  if (themodel->Number(obj) == 0) Transfer_TransferFailure::Raise
    ("TransferOutput : Transfer, entities do not come from same initial model");
//  Standard_Integer scope = 0;
//  if (thescope) scope = theproc->NewScope (obj);

  //:1 modified by ABV 5 Nov 97
  //:1  if (!theproc->Transfer(obj)) return;    // auparavant, traitement Undefined
//  Standard_Boolean ok = 
  theproc->Transfer ( obj );  
//  if (scope > 0) theproc->EndScope (scope);
//  if ( ! ok ) return;                               

/*  switch (theundef) {
    case Transfer_UndefIgnore  : return;
    case Transfer_UndefFailure : Transfer_TransferFailure::Raise
      ("TransferOutput : Transfer Undefined as Failure");
    case Transfer_UndefContent : break; // on ne sait pas traiter ...
    case Transfer_UndefUser    : break; // idem
  }
*/
}


//  Resultats :
//   Pour transferer tout simplement toutes les racines d'un modele d'interface
//   Chacune est notee "Root" dans le Process final

void Transfer_TransferOutput::TransferRoots ()
{  TransferRoots(Interface_Protocol::Active());  }

void Transfer_TransferOutput::TransferRoots (const Handle(Interface_Protocol)& protocol)
{
  theproc->SetRootManagement (Standard_False);
  Interface_ShareFlags tool(themodel,protocol);
  Interface_EntityIterator list = tool.RootEntities();
  for (list.Start(); list.More(); list.Next()) {
    Handle(Standard_Transient) ent = list.Value();
//    Standard_Integer scope = 0;
//    if (thescope) scope = theproc->NewScope (ent);
    if (theproc->Transfer(ent)) theproc->SetRoot(ent);
//    if (scope > 0) theproc->EndScope (scope);
  }
}

void Transfer_TransferOutput::TransferRoots (const Interface_Graph& G)
{
  theproc->SetRootManagement (Standard_False);
  Interface_ShareFlags tool(G);
  theproc->SetModel (G.Model());
  Interface_EntityIterator list = tool.RootEntities();
  for (list.Start(); list.More(); list.Next()) {
    Handle(Standard_Transient) ent = list.Value();
//    Standard_Integer scope = 0;
//    if (thescope) scope = theproc->NewScope (ent);
    if (theproc->Transfer(ent)) theproc->SetRoot(ent);
//    if (scope > 0) theproc->EndScope (scope);
  }
}


Interface_EntityIterator  Transfer_TransferOutput::ListForStatus (const Standard_Boolean normal,
								  const Standard_Boolean roots) const
{
  Interface_EntityIterator list;
  Standard_Integer max = (roots ? theproc->NbRoots() : theproc->NbMapped());
  for (Standard_Integer i = 1; i <= max; i ++) {
    const Handle(Transfer_Binder)& binder =
      (roots ? theproc->RootItem(i) : theproc->MapItem(i));
    if (binder.IsNull()) continue;
    Transfer_StatusExec statex = binder->StatusExec();
    Standard_Boolean ok =
      (statex == Transfer_StatusInitial || statex == Transfer_StatusDone);
    if (ok == normal) list.AddItem
      ( (roots ? theproc->Root(i) : theproc->Mapped(i)) );
  }
  return list;
}

Handle(Interface_InterfaceModel)  Transfer_TransferOutput::ModelForStatus
  (const Handle(Interface_Protocol)& protocol,
   const Standard_Boolean normal, const Standard_Boolean roots) const
{
  Handle(Interface_InterfaceModel) newmod;
  if (themodel.IsNull()) return newmod;
  newmod = themodel->NewEmptyModel();
  Interface_EntityIterator list = ListForStatus (normal, roots);
  for (list.Start(); list.More(); list.Next())
    newmod->AddWithRefs (list.Value(),protocol);
  return newmod;
}
