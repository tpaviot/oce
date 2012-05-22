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

//#58 rln 28.12.98 changing default values for Global Section
//sln 14.01.2002 OCC51 : verifying whether entry model of method ActorRead is IGESDatat_IGESModel 

#include <IGESControl_Controller.ixx>
#include <IGESSelect_WorkLibrary.hxx>
#include <IGESToBRep_Actor.hxx>
#include <IGESData_IGESModel.hxx>
#include <IGESSolid.hxx>
#include <IGESAppli.hxx>

#include <Interface_Static.hxx>
#include <IGESSelect_AutoCorrect.hxx>
#include <IGESSelect_ComputeStatus.hxx>
#include <IGESSelect_UpdateFileName.hxx>
#include <IGESSelect_SetGlobalParameter.hxx>
#include <IGESSelect_FloatFormat.hxx>
#include <IGESSelect_SelectBypassGroup.hxx>
#include <IGESSelect_SelectBypassSubfigure.hxx>
#include <IGESSelect_SelectBasicGeom.hxx>
#include <IGESSelect_SelectFaces.hxx>
#include <IGESSelect_SelectPCurves.hxx>
#include <IGESSelect_SelectVisibleStatus.hxx>
#include <IGESSelect_SelectSubordinate.hxx>
#include <IFSelect_SelectType.hxx>
#include <IGESBasic_SubfigureDef.hxx>
#include <IGESSelect_IGESTypeForm.hxx>
#include <IGESSelect_SignStatus.hxx>
#include <IGESSelect_SignLevelNumber.hxx>
#include <IGESSelect_SignColor.hxx>
#include <IGESSelect_IGESName.hxx>
#include <IFSelect_SignType.hxx>
#include <IFSelect_SignMultiple.hxx>
#include <IGESSelect_CounterOfLevelNumber.hxx>
#include <IFSelect_SignCounter.hxx>
#include <IGESSelect_EditHeader.hxx>
#include <IGESSelect_EditDirPart.hxx>
#include <IFSelect_EditForm.hxx>
#include <IGESSelect_RemoveCurves.hxx>
#include <IGESSelect_SetLabel.hxx>

#include <TCollection_HAsciiString.hxx>

#include <IGESControl_ActorWrite.hxx>
#include <IGESControl_AlgoContainer.hxx>

#include <XSAlgo.hxx>
#include <Interface_Macros.hxx>
#include <IGESToBRep.hxx>
#include <IFSelect_SelectModelEntities.hxx>
#include <IFSelect_SelectModelEntities.hxx>
#include <IFSelect_SelectModelRoots.hxx>
#include <XSControl_SelectForTransfer.hxx>

//szv#4:S4163:12Mar99 never referenced
//static const Standard_CString thelong  = "IGES";
//static const Standard_CString theshort = "iges";

//=======================================================================
//function : IGESControl_Controller
//purpose  : 
//=======================================================================

IGESControl_Controller::IGESControl_Controller (const Standard_Boolean mod)
//JR/Hp
     : XSControl_Controller ((Standard_CString ) (mod ? "FNES" : "IGES") , (Standard_CString ) (mod ? "fnes" : "iges") ) ,
//     : XSControl_Controller ( (mod ? "FNES" : "iges") , (mod ? "fnes" : "iges") ) ,
       themode (mod)
{
  static Standard_Boolean init = Standard_False;
  if (!init) {
    IGESSolid::Init();
    IGESAppli::Init();
    init = Standard_True;
  }
   AddSessionItem (new IGESSelect_RemoveCurves(Standard_True) ,"iges-remove-pcurves");
  AddSessionItem (new IGESSelect_RemoveCurves(Standard_False),"iges-remove-curves-3d");
  AddSessionItem (new IGESSelect_SetLabel (0,Standard_True) ,"iges-clear-label");
  AddSessionItem (new IGESSelect_SetLabel (1,Standard_False),"iges-set-label-dnum");

  AddSessionItem (new IGESSelect_AutoCorrect,"iges-auto-correct","send");
  AddSessionItem (new IGESSelect_ComputeStatus,"iges-compute-status","send");
  Handle(IGESSelect_FloatFormat) flf = new IGESSelect_FloatFormat;
  flf->SetDefault (12);
  AddSessionItem (flf,"iges-float-digits-12","send");

//   --   Sender Product Identification   --  (pas un statique ...)
  Handle(IGESSelect_SetGlobalParameter) set3 = new IGESSelect_SetGlobalParameter(3);
//#58 rln Handle(TCollection_HAsciiString) pa3 = new TCollection_HAsciiString("MDTV X-STEP");
  Handle(TCollection_HAsciiString) pa3 =
    Interface_Static::Static("write.iges.header.product")->HStringValue();
  set3->SetValue(pa3);
  AddSessionItem (pa3, "iges-header-val-sender");
  AddSessionItem (set3,"iges-header-set-sender","send");

  AddSessionItem (new IGESSelect_UpdateFileName,"iges-update-file-name","send");

//   --   Receiver   --   Acces par Static, ajustable
  Handle(IGESSelect_SetGlobalParameter) set12 = new IGESSelect_SetGlobalParameter(12);
//  Handle(TCollection_HAsciiString) pa12 = new TCollection_HAsciiString("Unknown");
  Handle(TCollection_HAsciiString) pa12 =
    Interface_Static::Static("write.iges.header.receiver")->HStringValue();
  set12->SetValue(pa12);
  AddSessionItem (pa12, "iges-header-val-receiver");
  AddSessionItem (set12,"iges-header-set-receiver","send");

//   --   Auteur   --   acces par Static (demarre par whoami), ajustable
  Handle(IGESSelect_SetGlobalParameter) set21 = new IGESSelect_SetGlobalParameter(21);
//  Handle(TCollection_HAsciiString) pa21 = new TCollection_HAsciiString("Unknown");
  Handle(TCollection_HAsciiString) pa21 =
    Interface_Static::Static("write.iges.header.author")->HStringValue();
  set21->SetValue(pa21);
  AddSessionItem (pa21, "iges-header-val-author");
  AddSessionItem (set21,"iges-header-set-author","send");

//   --   Compagnie (de l auteur)   --   acces par Static, ajustable
  Handle(IGESSelect_SetGlobalParameter) set22 = new IGESSelect_SetGlobalParameter(22);
//  Handle(TCollection_HAsciiString) pa22 = new TCollection_HAsciiString("MATRA-DATAVISION");
  Handle(TCollection_HAsciiString) pa22 =
    Interface_Static::Static("write.iges.header.company")->HStringValue();
  set22->SetValue(pa22);
  AddSessionItem (pa22, "iges-header-val-company");
  AddSessionItem (set22,"iges-header-set-company","send");
  //  -- STATICS

  TraceStatic ("read.iges.bspline.approxd1.mode",5);
  TraceStatic ("read.iges.bspline.continuity",5);

  TraceStatic ("write.iges.header.receiver",2);
  TraceStatic ("write.iges.header.author",2);
  TraceStatic ("write.iges.header.company",2);
  TraceStatic ("write.iges.unit",6);
  TraceStatic ("write.iges.brep.mode",6);

  theAdaptorLibrary  = new IGESSelect_WorkLibrary(themode);
  theAdaptorProtocol = IGESSelect_WorkLibrary::DefineProtocol();

  Handle(IGESToBRep_Actor) anactiges = new IGESToBRep_Actor;
  anactiges->SetContinuity(0);
  theAdaptorRead     = anactiges;

  theAdaptorWrite    = new IGESControl_ActorWrite;
  SetModeWrite (0,1);
  SetModeWriteHelp (0,"Faces");
  SetModeWriteHelp (1,"BRep");
}
void IGESControl_Controller::Customise(Handle(XSControl_WorkSession)& WS) 
{
  XSControl_Controller::Customise(WS);
 

//   ---  SELECTIONS, SIGNATURES, COMPTEURS, EDITEURS
//   --   BypassGroup / xst-model-roots
  
  
  //DeclareAndCast(IFSelect_Selection,xma,SessionItem("xst-model-all"));
  Handle(IFSelect_SelectModelEntities) xma;
  Handle(Standard_Transient) xma1 = WS->NamedItem("xst-model-all");
  if(xma1.IsNull()) xma = new  IFSelect_SelectModelEntities;
  else {
    xma =Handle(IFSelect_SelectModelEntities)::DownCast(xma1);
    WS->AddNamedItem ("xst-model-all",xma);
  }
  
  //DeclareAndCast(IFSelect_Selection,xmr,SessionItem("xst-model-roots"));
   Handle(IFSelect_SelectModelRoots) xmr;
  Handle(Standard_Transient) xmr1 = WS->NamedItem("xst-model-roots");
  if(!xmr1.IsNull())
    xmr = Handle(IFSelect_SelectModelRoots)::DownCast(xmr1);
  else  {
    xmr = new IFSelect_SelectModelRoots;
    WS->AddNamedItem ("xst-model-roots",xmr);
  }
//  DeclareAndCast(IFSelect_Selection,xtr,SessionItem("xst-transferrable-roots"));
  Handle(XSControl_SelectForTransfer) xtr;
  Handle(Standard_Transient) xtr1 = WS->NamedItem("xst-transferrable-roots");
  if(!xtr1.IsNull())
    xtr = Handle(XSControl_SelectForTransfer)::DownCast(xtr1);
  //st1->SetInput (slr);
  else {
    xtr= new XSControl_SelectForTransfer;
    xtr->SetReader (WS->TransferReader());
    WS->AddNamedItem ("xst-transferrable-roots",xtr);
  }
  if (!xmr.IsNull()) {
    Handle(IGESSelect_SelectVisibleStatus) visa = new IGESSelect_SelectVisibleStatus;
    visa->SetInput(xmr);
    WS->AddNamedItem ("iges-visible-roots",visa);
    Handle(IGESSelect_SelectVisibleStatus) vist = new IGESSelect_SelectVisibleStatus;
    vist->SetInput(xtr);
    WS->AddNamedItem ("iges-visible-transf-roots",vist);
    Handle(IGESSelect_SelectVisibleStatus) blka = new IGESSelect_SelectVisibleStatus;
    blka->SetDirect (Standard_False);
    blka->SetInput(xmr);
    WS->AddNamedItem ("iges-blanked-roots",blka);
    Handle(IGESSelect_SelectVisibleStatus) blkt = new IGESSelect_SelectVisibleStatus;
    blkt->SetDirect (Standard_False);
    blkt->SetInput(xtr);
    WS->AddNamedItem ("iges-blanked-transf-roots",blkt);
    Handle(IGESSelect_SelectSubordinate) indp = new IGESSelect_SelectSubordinate (0);
    indp->SetInput (xma);
    WS->AddNamedItem ("iges-status-independant",indp);

    Handle(IGESSelect_SelectBypassGroup) sb = new IGESSelect_SelectBypassGroup;
    sb->SetInput(xmr);
    WS->AddNamedItem ("iges-bypass-group",sb);
    Handle(IGESSelect_SelectBypassSubfigure) sfi = new IGESSelect_SelectBypassSubfigure;
    sfi->SetInput(xmr);
    WS->AddNamedItem ("iges-bypass-subfigure",sfi);
    Handle(IGESSelect_SelectBypassGroup) sfb = new IGESSelect_SelectBypassGroup;
    sfb->SetInput(sfi);
    WS->AddNamedItem ("iges-bypass-group-subfigure",sfb);
    Handle(IGESSelect_SelectBasicGeom) sc3d = new IGESSelect_SelectBasicGeom(1);
    sc3d->SetInput(sfi);
    WS->AddNamedItem ("iges-curves-3d",sc3d);
    Handle(IGESSelect_SelectBasicGeom) sb3d = new IGESSelect_SelectBasicGeom(2);
    sb3d->SetInput(sfi);
    WS->AddNamedItem ("iges-basic-curves-3d",sb3d);
    Handle(IGESSelect_SelectBasicGeom) sbg = new IGESSelect_SelectBasicGeom(0);
    sbg->SetInput(sfi);
    WS->AddNamedItem ("iges-basic-geom",sbg);
    Handle(IGESSelect_SelectBasicGeom) srf = new IGESSelect_SelectBasicGeom(-1);
    srf->SetInput(sfi);
    WS->AddNamedItem ("iges-surfaces",srf);
    Handle(IGESSelect_SelectFaces) sfa = new IGESSelect_SelectFaces;
    sfa->SetInput(sfi);
    WS->AddNamedItem ("iges-faces",sfa );
    Handle(IGESSelect_SelectPCurves) spc = new IGESSelect_SelectPCurves(Standard_True);
    spc->SetInput(sfa);
    WS->AddNamedItem ("iges-pcurves",spc);

    Handle(IFSelect_SelectType) snosub = new IFSelect_SelectType
      (STANDARD_TYPE(IGESBasic_SubfigureDef));
    snosub->SetDirect(Standard_False);
    snosub->SetInput(xmr);
    WS->AddNamedItem ("iges-no-indep-subfigure-def",snosub);

    Handle(IGESSelect_IGESTypeForm) itf = new IGESSelect_IGESTypeForm(Standard_True);
    WS->AddNamedItem ("iges-type",itf);

    Handle(IGESSelect_SignStatus) sigst = new IGESSelect_SignStatus;
    Handle(IFSelect_SignMultiple) typsta = new IFSelect_SignMultiple
      ("IGES Type Form    Status");
    typsta->Add (itf,15);
    typsta->Add (sigst);
    WS->AddNamedItem ("iges-type-status",typsta);

    Handle(IFSelect_SignMultiple) typnam = new IFSelect_SignMultiple
      ("IGES Type Form  TypeName");
    typnam->Add (itf,4);
    typnam->Add (new IFSelect_SignType(Standard_True));
    WS->AddNamedItem ("iges-type-name",typnam);

    Handle(IFSelect_SignCounter) itfs = new IFSelect_SignCounter
      (itf,Standard_False,Standard_True);
    WS->AddNamedItem ("iges-types",itfs);
    Handle(IGESSelect_CounterOfLevelNumber) levs =
      new IGESSelect_CounterOfLevelNumber;
    WS->AddNamedItem ("iges-levels",levs);

    Handle(IGESSelect_SignLevelNumber) slev = new IGESSelect_SignLevelNumber(Standard_False);
    WS->AddNamedItem ("iges-level-number",slev);
    Handle(IGESSelect_IGESName) igna = new IGESSelect_IGESName;
    WS->AddNamedItem ("iges-name",igna);

    Handle(IGESSelect_SignColor) scol1 = new IGESSelect_SignColor (1);
    WS->AddNamedItem ("iges-color-number",scol1);
    Handle(IGESSelect_SignColor) scol2 = new IGESSelect_SignColor (2);
    WS->AddNamedItem ("iges-color-name",scol2);
    Handle(IGESSelect_SignColor) scol3 = new IGESSelect_SignColor (3);
    WS->AddNamedItem ("iges-color-rgb",scol3);
    Handle(IGESSelect_SignColor) scol4 = new IGESSelect_SignColor (4);
    WS->AddNamedItem ("iges-color-red",scol4);
    Handle(IGESSelect_SignColor) scol5 = new IGESSelect_SignColor (5);
    WS->AddNamedItem ("iges-color-green",scol5);
    Handle(IGESSelect_SignColor) scol6 = new IGESSelect_SignColor (6);
    WS->AddNamedItem ("iges-color-blue",scol6);

    Handle(IGESSelect_EditHeader) edhead = new IGESSelect_EditHeader;
    WS->AddNamedItem ("iges-header-edit",edhead);
    Handle(IFSelect_EditForm) edheadf = edhead->Form(Standard_False);
    WS->AddNamedItem ("iges-header",edheadf);

    Handle(IGESSelect_EditDirPart) eddirp = new IGESSelect_EditDirPart;
    WS->AddNamedItem ("iges-dir-part-edit",eddirp);
    Handle(IFSelect_EditForm) eddirpf = eddirp->Form(Standard_False);
    WS->AddNamedItem ("iges-dir-part",eddirpf);

    theSignType = typnam;
  }


}


//=======================================================================
//function : NewModel
//purpose  : 
//=======================================================================

 Handle(Interface_InterfaceModel)  IGESControl_Controller::NewModel () const
{
//  On prend un modele qu on prepare avec les statiques enregistres
  DeclareAndCast(IGESData_IGESModel,igm,Interface_InterfaceModel::Template("iges"));
  IGESData_GlobalSection GS = igm->GlobalSection();

  GS.SetReceiveName (Interface_Static::Static("write.iges.header.receiver")->HStringValue());
  GS.SetUnitFlag    (Interface_Static::IVal("write.iges.unit"));
  GS.SetUnitName    (new TCollection_HAsciiString(Interface_Static::CVal("write.iges.unit")));
  GS.SetAuthorName  (Interface_Static::Static("write.iges.header.author")->HStringValue());
  GS.SetCompanyName (Interface_Static::Static("write.iges.header.company")->HStringValue());
  igm->SetGlobalSection (GS);
  return igm;
}

//=======================================================================
//function : ActorRead
//purpose  : 
//=======================================================================

 Handle(Transfer_ActorOfTransientProcess)  IGESControl_Controller::ActorRead
  (const Handle(Interface_InterfaceModel)& model) const
{
  DeclareAndCast(IGESToBRep_Actor,anactiges,theAdaptorRead);
  if (anactiges.IsNull()) return theAdaptorRead;
  //sln 14.01.2002 OCC51 : verifying whether entry model is IGESDatat_IGESModel,
  // if this condition is false new model is created 
  Handle(Interface_InterfaceModel) aModel;
  if(model->IsKind(STANDARD_TYPE(IGESData_IGESModel)))
    aModel = model;
  else
    aModel = NewModel();
  anactiges->SetModel(GetCasted(IGESData_IGESModel,aModel));
  anactiges->SetContinuity(Interface_Static::IVal("read.iges.bspline.continuity"));
  return anactiges;
}

//  ####    TRANSFERT (ECRITURE SHAPE)    ####
//  modetrans : 0  <5.1 (groupe de faces),  1 BREP-5.1

//=======================================================================
//function : TransferWriteShape
//purpose  : 
//=======================================================================

 IFSelect_ReturnStatus  IGESControl_Controller::TransferWriteShape (const TopoDS_Shape& shape,
                                                                    const Handle(Transfer_FinderProcess)& FP,
                                                                    const Handle(Interface_InterfaceModel)& model,
                                                                    const Standard_Integer modetrans) const
{
  return XSControl_Controller::TransferWriteShape (shape,FP,model,modetrans);
}

//=======================================================================
//function : Init
//purpose  : 
//=======================================================================

 Standard_Boolean  IGESControl_Controller::Init ()
{
  static Standard_Boolean inic = Standard_False;
  if (!inic) {
    Handle(IGESControl_Controller) ADIGES = new IGESControl_Controller(Standard_False);
    ADIGES->AutoRecord();
    XSAlgo::Init();
    IGESToBRep::Init();
    IGESToBRep::SetAlgoContainer (new IGESControl_AlgoContainer());
    inic = Standard_True;
  }
  return Standard_True;
}
