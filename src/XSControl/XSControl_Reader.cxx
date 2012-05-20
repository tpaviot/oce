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

// pdn 26.02.99 added initializing of compound in function OneShape
//:   gka 14.04.99: S4136: apply scaling
#include <XSControl_Reader.ixx>
#include <XSControl_Controller.hxx>
#include <XSControl_TransferReader.hxx>
#include <Interface_ShareFlags.hxx>
#include <IFSelect_Functions.hxx>

#include <ShapeExtend_Explorer.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <Transfer_IteratorOfProcessForTransient.hxx>
#include <Transfer_TransientProcess.hxx>
#include <Transfer_Binder.hxx>
//#include <ShapeCustom.hxx>
#include <Interface_Static.hxx>
#include <Interface_Check.hxx>
#include <Message_ProgressSentry.hxx>


//#include <ShapeAlgo.hxx>
//#include <ShapeAlgo_AlgoContainer.hxx>


//=======================================================================
//function : XSControl_Reader
//purpose  : 
//=======================================================================

XSControl_Reader::XSControl_Reader ()
{
  SetWS (new XSControl_WorkSession);
}


//=======================================================================
//function : XSControl_Reader
//purpose  : 
//=======================================================================

XSControl_Reader::XSControl_Reader (const Standard_CString norm)
{
  SetNorm (norm);
}


//=======================================================================
//function : XSControl_Reader
//purpose  : 
//=======================================================================

XSControl_Reader::XSControl_Reader(const Handle(XSControl_WorkSession)& WS,
                                   const Standard_Boolean scratch)
{
  SetWS (WS,scratch);
}


//=======================================================================
//function : SetNorm
//purpose  : 
//=======================================================================

Standard_Boolean  XSControl_Reader::SetNorm (const Standard_CString norm)
{
  if (thesession.IsNull()) SetWS (new XSControl_WorkSession);
  Standard_Boolean stat = thesession->SelectNorm (norm);
  if (stat) {
    thesession->InitTransferReader(0);
    thesession->InitTransferReader(4);
  }
  return stat;
}


//=======================================================================
//function : SetWS
//purpose  : 
//=======================================================================

void XSControl_Reader::SetWS(const Handle(XSControl_WorkSession)& WS,
                             const Standard_Boolean scratch)
{
  therootsta = Standard_False;
  theroots.Clear();
  thesession = WS;
  //  Il doit y avoir un Controller ...  Sinon onverra plus tard (apres SetNorm)
  if (thesession->NormAdaptor().IsNull()) return;
  Handle(Interface_InterfaceModel) model = thesession->Model ();
  if (scratch || model.IsNull())   model = thesession->NewModel ();
  thesession->InitTransferReader(0);
  thesession->InitTransferReader(4);
}


//=======================================================================
//function : WS
//purpose  : 
//=======================================================================

Handle(XSControl_WorkSession) XSControl_Reader::WS () const
{
  return thesession;
}


//=======================================================================
//function : ReadFile
//purpose  : 
//=======================================================================

IFSelect_ReturnStatus  XSControl_Reader::ReadFile
  (const Standard_CString filename)
{
  IFSelect_ReturnStatus stat = thesession->ReadFile(filename);
  thesession->InitTransferReader(4);
  return stat;
}


Handle(Interface_InterfaceModel) XSControl_Reader::Model () const
{
  return thesession->Model();
}


//=======================================================================
//function : GiveList
//purpose  : 
//=======================================================================

Handle(TColStd_HSequenceOfTransient)  XSControl_Reader::GiveList
       (const Standard_CString first, const Standard_CString second)
{
  if (first && first[0] != '\0') {
    return thesession->GiveList (first,second);
  }

  Handle(TColStd_HSequenceOfTransient) list = new TColStd_HSequenceOfTransient();
  Standard_Integer i,nbr = NbRootsForTransfer();
  for (i = 1; i <= nbr; i ++) list->Append (RootForTransfer(i));
  return list;
}


//=======================================================================
//function : GiveList
//purpose  : 
//=======================================================================

Handle(TColStd_HSequenceOfTransient)  XSControl_Reader::GiveList
       (const Standard_CString first, const Handle(Standard_Transient)& list)
{
  return thesession->GiveListFromList (first,list);
}


//=======================================================================
//function : NbRootsForTransfer
//purpose  : 
//=======================================================================

Standard_Integer  XSControl_Reader::NbRootsForTransfer ()
{
  if (therootsta) return theroots.Length();
  therootsta = Standard_True;
  Interface_ShareFlags sf (thesession->Graph());
  Standard_Integer i, nbr = sf.NbRoots();
  for (i = 1; i <= nbr; i ++) {
    //    on filtre les racines qu on sait transferer
    Handle(Standard_Transient) start = sf.Root(i);
    if (thesession->TransferReader()->Recognize(start)) theroots.Append(start);
  }
  return theroots.Length();
}


//=======================================================================
//function : RootForTransfer
//purpose  : 
//=======================================================================

Handle(Standard_Transient)  XSControl_Reader::RootForTransfer
  (const Standard_Integer num)
{
  Handle(Standard_Transient) voidroot;
  Standard_Integer nbr = NbRootsForTransfer();
  if (num < 1 || num > nbr) return voidroot;
  return theroots.Value(num);
}


//  ####        TRANSFERT        ####


//=======================================================================
//function : TransferOneRoot
//purpose  : 
//=======================================================================

Standard_Boolean  XSControl_Reader::TransferOneRoot(const Standard_Integer num)
{
  return TransferEntity (RootForTransfer (num));
}


//=======================================================================
//function : TransferOne
//purpose  : 
//=======================================================================

Standard_Boolean  XSControl_Reader::TransferOne(const Standard_Integer num)
{
  return TransferEntity (thesession->StartingEntity (num));
}


//=======================================================================
//function : TransferEntity
//purpose  : 
//=======================================================================

Standard_Boolean  XSControl_Reader::TransferEntity
  (const Handle(Standard_Transient)& start)
{
  if (start.IsNull()) return Standard_False;
  Handle(XSControl_TransferReader) TR = thesession->TransferReader();
  TR->BeginTransfer();
  if (TR->TransferOne (start) == 0) return Standard_False;
  TopoDS_Shape sh = TR->ShapeResult(start);
  //ShapeExtend_Explorer STU;
  //SMH May 00: allow empty shapes (STEP CAX-IF, external references)
  //if (STU.ShapeType(sh,Standard_True) == TopAbs_SHAPE) return Standard_False;  // nulle-vide 
  theshapes.Append(sh);
  return Standard_True;
}


//=======================================================================
//function : TransferList
//purpose  : 
//=======================================================================

Standard_Integer  XSControl_Reader::TransferList
  (const Handle(TColStd_HSequenceOfTransient)& list)
{
  if (list.IsNull()) return 0;
  Standard_Integer nbt = 0;
  Standard_Integer i, nb = list->Length();
  Handle(XSControl_TransferReader) TR = thesession->TransferReader();
  TR->BeginTransfer();
  ClearShapes();
  ShapeExtend_Explorer STU;
  for (i = 1; i <= nb; i ++) {
    Handle(Standard_Transient) start = list->Value(i);
    if (TR->TransferOne (start) == 0) continue;
    TopoDS_Shape sh = TR->ShapeResult(start);
    if (STU.ShapeType(sh,Standard_True) == TopAbs_SHAPE) continue;  // nulle-vide
    theshapes.Append(sh);
    nbt ++;
  }
  return nbt;
}


//=======================================================================
//function : TransferRoots
//purpose  : 
//=======================================================================

Standard_Integer  XSControl_Reader::TransferRoots ()
{
  NbRootsForTransfer();
  Standard_Integer nbt = 0;
  Standard_Integer i, nb = theroots.Length();
  Handle(XSControl_TransferReader) TR = thesession->TransferReader();
   
  TR->BeginTransfer();
  ClearShapes();
  ShapeExtend_Explorer STU;
  Handle(Transfer_TransientProcess) proc = thesession->MapReader();
  Message_ProgressSentry PS ( proc->GetProgress(), "Root", 0, nb, 1 );
  for (i = 1; i <= nb && PS.More(); i ++,PS.Next()) {
    Handle(Standard_Transient) start = theroots.Value(i);
    if (TR->TransferOne (start) == 0) continue;
    TopoDS_Shape sh = TR->ShapeResult(start);
    if (STU.ShapeType(sh,Standard_True) == TopAbs_SHAPE) continue;  // nulle-vide
    theshapes.Append(sh);
    nbt ++;
  }
  return nbt;
}


//=======================================================================
//function : ClearShapes
//purpose  : 
//=======================================================================

void  XSControl_Reader::ClearShapes ()
{
  theshapes.Clear();
}


//=======================================================================
//function : NbShapes
//purpose  : 
//=======================================================================

Standard_Integer  XSControl_Reader::NbShapes () const
{
  return theshapes.Length();
}


//=======================================================================
//function : Shapes
//purpose  : 
//=======================================================================

TopTools_SequenceOfShape& XSControl_Reader::Shapes()
{
  return theshapes;
}


//=======================================================================
//function : Shape
//purpose  : 
//=======================================================================

TopoDS_Shape  XSControl_Reader::Shape (const Standard_Integer num) const
{
  return theshapes.Value(num);
}


//=======================================================================
//function : OneShape
//purpose  : 
//=======================================================================

TopoDS_Shape  XSControl_Reader::OneShape () const
{
  TopoDS_Shape sh;
  Standard_Integer i,nb = theshapes.Length();
  if (nb == 0) return sh;
  if (nb == 1) return theshapes.Value(1);
  TopoDS_Compound C;
  BRep_Builder B;
  //pdn 26.02.99 testing S4133
  B.MakeCompound(C);
  for (i = 1; i <= nb; i ++)  B.Add (C,theshapes.Value(i));
  return C;
}


//=======================================================================
//function : PrintCheckLoad
//purpose  : 
//=======================================================================

void  XSControl_Reader::PrintCheckLoad (const Standard_Boolean failsonly,
                                        const IFSelect_PrintCount mode) const
{
  thesession->PrintCheckList (thesession->ModelCheckList(),failsonly, mode);
}


//=======================================================================
//function : PrintCheckTransfer
//purpose  : 
//=======================================================================

void XSControl_Reader::PrintCheckTransfer(const Standard_Boolean failsonly,
                                          const IFSelect_PrintCount mode) const
{
  thesession->PrintCheckList (thesession->TransferReader()->LastCheckList(),failsonly, mode);
}


//=======================================================================
//function : PrintStatsTransfer
//purpose  : 
//=======================================================================

void XSControl_Reader::PrintStatsTransfer (const Standard_Integer what, 
                                           const Standard_Integer mode) const
{
  thesession->TransferReader()->PrintStats (what,mode);
}


//=======================================================================
//function : GetStatsTransfer
//purpose  : 
//=======================================================================

void XSControl_Reader::GetStatsTransfer (const Handle(TColStd_HSequenceOfTransient)& list,
					 Standard_Integer& nbMapped,
					 Standard_Integer& nbWithResult,
					 Standard_Integer& nbWithFail) const
{
  Handle(Transfer_TransientProcess) TP = thesession->MapReader();
  Transfer_IteratorOfProcessForTransient itrp(Standard_True);
  itrp = TP->CompleteResult(Standard_True);
  if(!list.IsNull()) itrp.Filter (list);
  nbMapped = nbWithFail = nbWithResult = 0;
  
  for (itrp.Start(); itrp.More(); itrp.Next()) {
    Handle(Transfer_Binder) binder = itrp.Value();
    Handle(Standard_Transient) ent = itrp.Starting();
    nbMapped++;
    if (binder.IsNull())  nbWithFail++;
    else
      if(!binder->HasResult()) nbWithFail++;
      else
	{
	  Interface_CheckStatus cst = binder->Check()->Status();
	  if ((cst == Interface_CheckOK)||(cst == Interface_CheckWarning))
	    nbWithResult++;
	  else
	    nbWithFail++;
	}
  }
}
						      
