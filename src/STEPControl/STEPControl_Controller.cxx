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

//:j4 gka 16.03.99 S4134
//    gka 05.04.99 S4136: parameters definitions changed
#include <STEPControl_Controller.ixx>
#include <StepSelect_WorkLibrary.hxx>
#include <IFSelect_Option.hxx>
#include <IFSelect_Profile.hxx>

//#include <StepAP214.hxx>
#include <RWStepAP214.hxx>

#include <Standard_Version.hxx>
#include <StepData_StepModel.hxx>
#include <APIHeaderSection_MakeHeader.hxx>
#include <StepData_FileProtocol.hxx>
#include <HeaderSection.hxx>
#include <RWHeaderSection.hxx>
#include <IFSelect_SignCounter.hxx>
#include <IFSelect_SelectSignature.hxx>
#include <StepSelect_StepType.hxx>

//  Pour NewModel et Write : definition de produit (temporaire ...)
#include <STEPControl_ActorRead.hxx>
#include <STEPControl_ActorWrite.hxx>

#include <STEPEdit.hxx>
#include <STEPEdit_EditContext.hxx>
#include <STEPEdit_EditSDR.hxx>

#include <APIHeaderSection_EditHeader.hxx>
#include <IFSelect_EditForm.hxx>

#include <TCollection_HAsciiString.hxx>

#include <Interface_Static.hxx>
#include <Interface_Macros.hxx>
#include <IFSelect_SignAncestor.hxx>
#include <STEPSelections_SelectFaces.hxx>
#include <STEPSelections_SelectDerived.hxx>
#include <STEPSelections_SelectGSCurves.hxx>
#include <STEPSelections_SelectInstances.hxx>
#include <STEPSelections_SelectAssembly.hxx>
#include <XSAlgo.hxx>
#include <STEPSelections_SelectForTransfer.hxx>
#include <IFSelect_SelectModelRoots.hxx>


STEPControl_Controller::STEPControl_Controller ()
     : XSControl_Controller ("STEP", "step")
{
  static Standard_Boolean init = Standard_False;
  if (!init) {
    RWHeaderSection::Init();  RWStepAP214::Init();

    Interface_Static::Init ("step","write.step.product.name",'t',"Open CASCADE STEP translator " OCC_VERSION_STRING);
    Interface_Static::Init ("step","write.step.assembly",'e',"");
    Interface_Static::Init ("step","write.step.assembly",'&',"enum 0");
    Interface_Static::Init ("step","write.step.assembly",'&',"eval Off");
    Interface_Static::Init ("step","write.step.assembly",'&',"eval On");
    Interface_Static::Init ("step","write.step.assembly",'&',"eval Auto");
    Interface_Static::SetCVal("write.step.assembly","Auto"); 

    Interface_Static::Init("step","step.angleunit.mode", 'e',"");
    Interface_Static::Init("step","step.angleunit.mode", '&',"enum 0");
    Interface_Static::Init("step","step.angleunit.mode", '&',"eval File");
    Interface_Static::Init("step","step.angleunit.mode", '&',"eval Rad");
    Interface_Static::Init("step","step.angleunit.mode", '&',"eval Deg");
    Interface_Static::SetCVal("step.angleunit.mode","File"); 

    Interface_Static::Init("step","write.step.schema", 'e',"");  
    Interface_Static::Init("step","write.step.schema",'&',"enum 1");
    Interface_Static::Init("step","write.step.schema",'&',"eval AP214CD");
    Interface_Static::Init("step","write.step.schema",'&',"eval AP214DIS");
    Interface_Static::Init("step","write.step.schema",'&',"eval AP203");
    Interface_Static::Init("step","write.step.schema",'&',"eval AP214IS");  
    Interface_Static::SetCVal("write.step.schema","AP214CD"); 

    // Type of Product Definition for reading
    // Note: the numbers should be consistent with function FindShapeReprType()
    // in STEPControl_ActorRead.cxx
    Interface_Static::Init("step","read.step.shape.repr",'e',"");
    Interface_Static::Init("step","read.step.shape.repr",'&',"enum 1");
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval All");   // 1
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval ABSR");  // 2
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval MSSR");  // 3
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval GBSSR"); // 4
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval FBSR");  // 5
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval EBWSR"); // 6
    Interface_Static::Init("step","read.step.shape.repr",'&',"eval GBWSR"); // 7
    Interface_Static::SetCVal("read.step.shape.repr","All");

    // Mode for reading shapes attached to main SDR by SRR
    // (hybrid model representation in AP203 since 1998)
    Interface_Static::Init("step","read.step.shape.relationship",'e',"");
    Interface_Static::Init("step","read.step.shape.relationship",'&',"enum 0");
    Interface_Static::Init("step","read.step.shape.relationship",'&',"eval OFF");
    Interface_Static::Init("step","read.step.shape.relationship",'&',"eval ON");
    Interface_Static::SetCVal("read.step.shape.relationship","ON");

    // Mode for reading shapes attached to Product by ShapeAspect 
    // (hybrid model representation in AP203 before 1998)
    Interface_Static::Init("step","read.step.shape.aspect",'e',"");
    Interface_Static::Init("step","read.step.shape.aspect",'&',"enum 0");
    Interface_Static::Init("step","read.step.shape.aspect",'&',"eval OFF");
    Interface_Static::Init("step","read.step.shape.aspect",'&',"eval ON");
    Interface_Static::SetCVal("read.step.shape.aspect","ON");

    // Mode for reading SDR and ShapeRepr if it is necessary
    Interface_Static::Init("step","read.step.product.mode",'e',"");
    Interface_Static::Init("step","read.step.product.mode",'&',"enum 0");
    Interface_Static::Init("step","read.step.product.mode",'&',"eval OFF");
    Interface_Static::Init("step","read.step.product.mode",'&',"eval ON");
    Interface_Static::SetCVal("read.step.product.mode","ON");

    // Order of reading ShapeDefinitionRepresentation in ProductDefinition
    Interface_Static::Init("step","read.step.product.context",'e',"");
    Interface_Static::Init("step","read.step.product.context",'&',"enum 1");
    Interface_Static::Init("step","read.step.product.context",'&',"eval all");     // 1
    Interface_Static::Init("step","read.step.product.context",'&',"eval design");  // 2
    Interface_Static::Init("step","read.step.product.context",'&',"eval analysis");// 3
    Interface_Static::SetCVal("read.step.product.context","all");

    // What we try to read in ProductDefinition
    Interface_Static::Init("step","read.step.assembly.level",'e',"");
    Interface_Static::Init("step","read.step.assembly.level",'&',"enum 1");
    Interface_Static::Init("step","read.step.assembly.level",'&',"eval all");      // 1
    Interface_Static::Init("step","read.step.assembly.level",'&',"eval assembly"); // 2
    Interface_Static::Init("step","read.step.assembly.level",'&',"eval structure");// 3
    Interface_Static::Init("step","read.step.assembly.level",'&',"eval shape");    // 4
    Interface_Static::SetCVal("read.step.assembly.level","all");

    // unit: supposed to be cascade unit (target unit for reading)
    Interface_Static::Init("step","write.step.unit", 'e',"");
    Interface_Static::Init("step","write.step.unit",'&',"enum 1");
    Interface_Static::Init("step","write.step.unit",'&',"eval INCH");  // 1
    Interface_Static::Init("step","write.step.unit",'&',"eval MM");    // 2
    Interface_Static::Init("step","write.step.unit",'&',"eval ??");    // 3
    Interface_Static::Init("step","write.step.unit",'&',"eval FT");    // 4
    Interface_Static::Init("step","write.step.unit",'&',"eval MI");    // 5
    Interface_Static::Init("step","write.step.unit",'&',"eval M");     // 6
    Interface_Static::Init("step","write.step.unit",'&',"eval KM");    // 7
    Interface_Static::Init("step","write.step.unit",'&',"eval MIL");   // 8
    Interface_Static::Init("step","write.step.unit",'&',"eval UM");    // 9
    Interface_Static::Init("step","write.step.unit",'&',"eval CM");    //10
    Interface_Static::Init("step","write.step.unit",'&',"eval UIN");   //11
    Interface_Static::SetCVal ("write.step.unit","MM");

    // Non-manifold topology reading: OFF by default (ssv; 26.11.2010)
    Interface_Static::Init ("step","read.step.nonmanifold",'e',"");
    Interface_Static::Init ("step","read.step.nonmanifold",'&',"enum 0");
    Interface_Static::Init ("step","read.step.nonmanifold",'&',"eval Off");
    Interface_Static::Init ("step","read.step.nonmanifold",'&',"eval On");
    Interface_Static::SetIVal("read.step.nonmanifold",0); 

    // Non-manifold topology writing: OFF by default (ssv; 26.11.2010)
    Interface_Static::Init ("step","write.step.nonmanifold",'e',"");
    Interface_Static::Init ("step","write.step.nonmanifold",'&',"enum 0");
    Interface_Static::Init ("step","write.step.nonmanifold",'&',"eval Off");
    Interface_Static::Init ("step","write.step.nonmanifold",'&',"eval On");
    Interface_Static::SetIVal("write.step.nonmanifold",0); 

    // I-Deas-like STEP processing: OFF by default (ssv; 22.11.2010)
    Interface_Static::Init ("step","read.step.ideas",'e',"");
    Interface_Static::Init ("step","read.step.ideas",'&',"enum 0");
    Interface_Static::Init ("step","read.step.ideas",'&',"eval Off");
    Interface_Static::Init ("step","read.step.ideas",'&',"eval On");
    Interface_Static::SetIVal("read.step.ideas",0); 
  
    // abv 15.11.00: ShapeProcessing
    Interface_Static::Init ("XSTEP","write.step.resource.name",'t',"STEP");
    Interface_Static::Init ("XSTEP","read.step.resource.name",'t',"STEP");
    Interface_Static::Init ("XSTEP","write.step.sequence",'t',"ToSTEP");
    Interface_Static::Init ("XSTEP","read.step.sequence",'t',"FromSTEP");

    init = Standard_True;
  }

  Handle(STEPControl_ActorWrite) ActWrite = new STEPControl_ActorWrite;
  ActWrite->SetGroupMode (Interface_Static::IVal("write.step.assembly"));
  theAdaptorWrite = ActWrite;

  Handle(StepSelect_WorkLibrary) swl = new StepSelect_WorkLibrary;
  swl->SetDumpLabel(1);
  theAdaptorLibrary  = swl;
  theAdaptorProtocol =  STEPEdit::Protocol();
//  theAdaptorProtocol =  StepAP214::Protocol();
  theAdaptorRead     = new STEPControl_ActorRead;  // par ex pour Recognize

  SetModeWrite (0,4);
  SetModeWriteHelp (0,"As Is");
  SetModeWriteHelp (1,"Faceted Brep");
  SetModeWriteHelp (2,"Shell Based");
  SetModeWriteHelp (3,"Manifold Solid");
  SetModeWriteHelp (4,"Wireframe");
  TraceStatic ("read.surfacecurve.mode",5);

//   ---  SELECTIONS, SIGNATURES, COMPTEURS, EDITEURS

  DeclareAndCast(IFSelect_Selection,xmr,SessionItem("xst-model-roots"));
  if (!xmr.IsNull()) {
    Handle(IFSelect_Signature) sty = STEPEdit::SignType();
    AddSessionItem (sty,"step-type");
    Handle(IFSelect_SignCounter) tys = new IFSelect_SignCounter
      (sty,Standard_False,Standard_True);
    AddSessionItem (tys,"step-types");
    theSignType = sty;

    
    //pdn S4133 18.02.99
    Handle(IFSelect_SignAncestor)sta =  new IFSelect_SignAncestor();
    AddSessionItem (sta,"xst-derived");
    Handle(STEPSelections_SelectDerived) stdvar = new STEPSelections_SelectDerived();
    stdvar->SetProtocol(STEPEdit::Protocol());
    AddSessionItem (stdvar,"step-derived");
    
    Handle(IFSelect_SelectSignature) selsdr = STEPEdit::NewSelectSDR();
    selsdr->SetInput (xmr);
    AddSessionItem (selsdr,"step-shape-def-repr");
    Handle(IFSelect_SelectSignature) selrrs = STEPEdit::NewSelectPlacedItem();
//    selrrs->SetInput (xmr);  deja prete avec ModelAll
    AddSessionItem (selrrs,"step-placed-items");
    Handle(IFSelect_SelectSignature) selsr = STEPEdit::NewSelectShapeRepr();
//    input deja pret avec ModelAll
    AddSessionItem (selsr,"step-shape-repr");
  }
  
  //pdn
  Handle(STEPSelections_SelectFaces) stfaces = new STEPSelections_SelectFaces;
  stfaces->SetInput (xmr);
  AddSessionItem (stfaces,"step-faces");
  
  Handle(STEPSelections_SelectInstances) stinst = new STEPSelections_SelectInstances;
  AddSessionItem (stinst,"step-instances");
  
  Handle(STEPSelections_SelectGSCurves) stcurves = new STEPSelections_SelectGSCurves;
  stcurves->SetInput (xmr);
  AddSessionItem (stcurves,"step-GS-curves");
  
  Handle(STEPSelections_SelectAssembly) assembly = new STEPSelections_SelectAssembly;
  assembly->SetInput (xmr);
  AddSessionItem (assembly,"step-assembly");
  
  Handle(APIHeaderSection_EditHeader) edhead = new APIHeaderSection_EditHeader;
  Handle(IFSelect_EditForm) edheadf = new IFSelect_EditForm (edhead,Standard_False,Standard_True,"Step Header");
  AddSessionItem (edhead,"step-header-edit");
  AddSessionItem (edheadf,"step-header");

  Handle(STEPEdit_EditContext) edctx = new STEPEdit_EditContext;
  Handle(IFSelect_EditForm) edctxf = new IFSelect_EditForm (edctx,Standard_False,Standard_True,"STEP Product Definition Context");
  AddSessionItem (edctx,"step-context-edit");
  AddSessionItem (edctxf,"step-context");


  Handle(STEPEdit_EditSDR) edsdr = new STEPEdit_EditSDR;
  Handle(IFSelect_EditForm) edsdrf = new IFSelect_EditForm (edsdr,Standard_False,Standard_True,"STEP Product Data (SDR)");
  AddSessionItem (edsdr,"step-SDR-edit");
  AddSessionItem (edsdrf,"step-SDR-data");

//    ####    PROFILE    ####

//  ActorRead : on ajoute le cas Shape possible, a part du default
//  ainsi, on l a tjrs sous la main
  Handle(IFSelect_Option) optacrd = Profile()->Option("tr-read");
  optacrd->Add ("shape",theAdaptorRead);

//  ActorWrite : on ajoute les cas possibles (NB : shape == default)
//  On garde a part les cas shape compound (= shape traitee globale ou en
//   assembly), peuvent etre utiles. Tandis que les autres cas sont
//   susceptibles d etre remplaces si on fait du Model-Editor
  Handle(IFSelect_Option) optacwr = Profile()->Option("tr-write");
  Handle(STEPControl_ActorWrite) ActWSh = new STEPControl_ActorWrite;
  ActWSh->SetGroupMode(0);
  optacwr->Add ("shape",ActWSh);
  Handle(STEPControl_ActorWrite) ActWA1 = new STEPControl_ActorWrite;
  ActWA1->SetGroupMode(1);
  optacwr->Add ("compound",ActWA1);
  optacwr->Add ("assembly",ActWA1);
  optacwr->Add ("SRWT",ActWA1);

  Profile()->AddConf ("Shape");
  Profile()->AddSwitch ("Shape","tr-write","shape");

  Profile()->AddConf ("Assembly");
  Profile()->AddSwitch ("Assembly","tr-write","SRWT");
}

Handle(Interface_InterfaceModel)  STEPControl_Controller::NewModel () const
{
  return STEPEdit::NewModel();
}

Handle(Transfer_ActorOfTransientProcess)  STEPControl_Controller::ActorRead
       (const Handle(Interface_InterfaceModel)& ) const
{
  return theAdaptorRead;
}    // new Cc1ToTopoDSAct_Actor ??

//  ####    PROVISOIRE ???   ####

IFSelect_ReturnStatus  STEPControl_Controller::TransferWriteShape
  (const TopoDS_Shape& shape,
   const Handle(Transfer_FinderProcess)& FP,
   const Handle(Interface_InterfaceModel)& model,
   const Standard_Integer modeshape) const
{
  if (modeshape < 0 || modeshape > 4) return IFSelect_RetError;
  Handle(STEPControl_ActorWrite) ActWrite =
    Handle(STEPControl_ActorWrite)::DownCast(theAdaptorWrite);
//    A PRESENT ON PASSE PAR LE PROFILE
  if (!ActWrite.IsNull()) 
    ActWrite->SetGroupMode (Interface_Static::IVal("write.step.assembly"));

  return XSControl_Controller::TransferWriteShape (shape,FP,model,modeshape);
}

Standard_Boolean STEPControl_Controller::Init ()
{
  static Standard_Boolean inic = Standard_False;
  if (!inic) {
    Handle(STEPControl_Controller) STEPCTL = new STEPControl_Controller;
    STEPCTL->AutoRecord();  // avec les noms donnes a la construction
    XSAlgo::Init();                                                                                                        
    inic = Standard_True;
  }
  return Standard_True;
}
//=======================================================================
//function : Customise
//purpose  : 
//=======================================================================

 void STEPControl_Controller::Customise(Handle(XSControl_WorkSession)& WS) 
{
  XSControl_Controller::Customise(WS);
  Handle(IFSelect_SelectModelRoots) slr;
  Handle(Standard_Transient) slr1 = WS->NamedItem("xst-model-roots");
  if(!slr1.IsNull())
    slr = Handle(IFSelect_SelectModelRoots)::DownCast(slr1);
  else  {
    slr = new IFSelect_SelectModelRoots;
    WS->AddNamedItem ("xst-model-roots",slr);
  }
  
  
  Handle(STEPSelections_SelectForTransfer) st1= new STEPSelections_SelectForTransfer;
  st1->SetReader (WS->TransferReader());
  WS->AddNamedItem ("xst-transferrable-roots",st1);
  
  
   //DeclareAndCast(IFSelect_Selection,xmr,SessionItem("xst-model-roots"));
  if (!slr.IsNull()) {
    Handle(IFSelect_Signature) sty = STEPEdit::SignType();
    WS->AddNamedItem ("step-type",sty);
    
    Handle(IFSelect_SignCounter) tys = new IFSelect_SignCounter
      (sty,Standard_False,Standard_True);
    WS->AddNamedItem ("step-types",tys);
    theSignType = sty;

    
    //pdn S4133 18.02.99
    Handle(IFSelect_SignAncestor)sta =  new IFSelect_SignAncestor();
    WS->AddNamedItem ("xst-derived",sta);
    Handle(STEPSelections_SelectDerived) stdvar = new STEPSelections_SelectDerived();
    stdvar->SetProtocol(STEPEdit::Protocol());
    WS->AddNamedItem ("step-derived",stdvar);
    
    Handle(IFSelect_SelectSignature) selsdr = STEPEdit::NewSelectSDR();
    selsdr->SetInput (slr);
    WS->AddNamedItem ("step-shape-def-repr",selsdr);
    Handle(IFSelect_SelectSignature) selrrs = STEPEdit::NewSelectPlacedItem();
//    selrrs->SetInput (slr);  deja prete avec ModelAll
    WS->AddNamedItem ("step-placed-items",selrrs);
    Handle(IFSelect_SelectSignature) selsr = STEPEdit::NewSelectShapeRepr();
//    input deja pret avec ModelAll
    WS->AddNamedItem ("step-shape-repr",selsr);
  }
  
  //pdn
  Handle(STEPSelections_SelectFaces) stfaces = new STEPSelections_SelectFaces;
  stfaces->SetInput (slr);
  WS->AddNamedItem ("step-faces",stfaces);
  
  Handle(STEPSelections_SelectInstances) stinst = new STEPSelections_SelectInstances;
  WS->AddNamedItem ("step-instances",stinst);
  
  Handle(STEPSelections_SelectGSCurves) stcurves = new STEPSelections_SelectGSCurves;
  stcurves->SetInput (slr);
  WS->AddNamedItem ("step-GS-curves",stcurves);
  
  Handle(STEPSelections_SelectAssembly) assembly = new STEPSelections_SelectAssembly;
  assembly->SetInput (slr);
  WS->AddNamedItem ("step-assembly",assembly);
  
  Handle(APIHeaderSection_EditHeader) edhead = new APIHeaderSection_EditHeader;
  Handle(IFSelect_EditForm) edheadf = new IFSelect_EditForm (edhead,Standard_False,Standard_True,"Step Header");
  WS->AddNamedItem ("step-header-edit",edhead);
  WS->AddNamedItem ("step-header",edheadf);

  Handle(STEPEdit_EditContext) edctx = new STEPEdit_EditContext;
  Handle(IFSelect_EditForm) edctxf = new IFSelect_EditForm (edctx,Standard_False,Standard_True,"STEP Product Definition Context");
  WS->AddNamedItem ("step-context-edit",edctx);
  WS->AddNamedItem ("step-context",edctxf);


  Handle(STEPEdit_EditSDR) edsdr = new STEPEdit_EditSDR;
  Handle(IFSelect_EditForm) edsdrf = new IFSelect_EditForm (edsdr,Standard_False,Standard_True,"STEP Product Data (SDR)");
  WS->AddNamedItem ("step-SDR-edit",edsdr);
  WS->AddNamedItem ("step-SDR-data",edsdrf);

  
  
}
