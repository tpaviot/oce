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

//gka 06.01.99 S3767 new function TPSTAT (first version)
//pdn 11.01.99 putting "return" statement for compilation on NT
#include <XSDRAWIGES.ixx>

#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>
#include <Interface_Static.hxx>

#include <IGESControl_Writer.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESData_BasicEditor.hxx>

#include <IGESData.hxx>
#include <IGESData_Protocol.hxx>
// #include <IGESData_IGESWriter.hxx>
#include <IGESData_IGESEntity.hxx>         // pour igeslist
#include <IGESData_IGESModel.hxx>

#include <Interface_Check.hxx>
#include <Interface_CheckTool.hxx>
#include <Interface_CheckIterator.hxx>

#include <stdio.h>
#include <TCollection_HAsciiString.hxx>
#include <TCollection_AsciiString.hxx>
#include <TColStd_HSequenceOfTransient.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>

#include <IGESToBRep.hxx>
#include <IGESToBRep_Actor.hxx>
#include <IGESToBRep_Reader.hxx>

#include <Geom_Curve.hxx>
#include <Geom_Surface.hxx>

#include <Interface_Macros.hxx>
#include <Message_Messenger.hxx>

#include <Draw_Appli.hxx>
#include <Draw_Printer.hxx>
#include <DrawTrSurf.hxx>
#include <DBRep.hxx>
//#include <GeometryTest.hxx>  essai CKY 4-AUT-1998
//#include <BRepTest.hxx>      essai CKY 4-AUT-1998
//#include <MeshTest.hxx>      essai CKY 4-AUT-1998

// Init functions

#include <IGESSelect_Activator.hxx>
#include <XSDRAW.hxx>
#include <XSDRAW_Commands.hxx>
#include <Transfer_TransientProcess.hxx>
#include <Transfer_TransferOutput.hxx>
#include <Transfer_FinderProcess.hxx>
#include <XSControl_WorkSession.hxx>

// + tplosttrim
#include <IFSelect_SessionPilot.hxx>
#include <XSControl.hxx>
#include <Transfer_IteratorOfProcessForTransient.hxx>
#include <TColStd_MapOfTransient.hxx>
#include <IFSelect_Functions.hxx>
#include <TColStd_MapIteratorOfMapOfTransient.hxx>
#include <IGESControl_Reader.hxx>
#include <Interface_InterfaceModel.hxx>
#include <Draw_ProgressIndicator.hxx>
#include <TopExp_Explorer.hxx>
#include <Message_ProgressSentry.hxx>

//--------------------------------------------------------------
// Function : igesbrep
//--------------------------------------------------------------

static Standard_Integer igesbrep (Draw_Interpretor& di, Standard_Integer argc, const char** argv) 
{
  DeclareAndCast(IGESControl_Controller,ctl,XSDRAW::Controller());
  if (ctl.IsNull()) XSDRAW::SetNorm("IGES");

  // Progress indicator
  Handle(Draw_ProgressIndicator) progress = new Draw_ProgressIndicator ( di, 1 );
  progress->SetScale ( 0, 100, 1 );
  progress->Show();
 
  IGESControl_Reader Reader (XSDRAW::Session(),Standard_False);
  Standard_Boolean aFullMode = Standard_True;
  Reader.WS()->SetModeStat(aFullMode);
  if (ctl.IsNull())
    ctl=Handle(IGESControl_Controller)::DownCast(XSDRAW::Controller());

  TCollection_AsciiString fnom,rnom;

  Standard_Boolean modfic = XSDRAW::FileAndVar
    (argv[1],argv[2],"IGESBREP",fnom,rnom);
  if (modfic) di<<" File IGES to read : "<<fnom.ToCString()<<"\n";
  else        di<<" Model taken from the session : "<<fnom.ToCString()<<"\n";
  di<<" -- Names of variables BREP-DRAW prefixed by : "<<rnom.ToCString()<<"\n";
  IFSelect_ReturnStatus readstat = IFSelect_RetVoid;

#ifdef CHRONOMESURE
  OSD_Timer Chr; Chr.Reset();
  IDT_SetLevel(3);
#endif


// Reading the file
  progress->NewScope ( 20, "Loading" ); // On average loading takes 20% 
  progress->Show();

  if (modfic) readstat = Reader.ReadFile (fnom.ToCString());
  else  if (XSDRAW::Session()->NbStartingEntities() > 0) readstat = IFSelect_RetDone;

  progress->EndScope();
  progress->Show();

  if (readstat != IFSelect_RetDone) {
    if (modfic) di<<"Could not read file "<<fnom.ToCString()<<" , abandon"<<"\n";
    else di<<"No model loaded"<<"\n";
    return 1;
  }
// Choice of treatment
  Standard_Boolean fromtcl = (argc > 3);
  Standard_Integer modepri = 1, nent, nbs;
  if (fromtcl) modepri = 4;

  while (modepri) {
    //Roots for transfer are defined before setting mode ALL or OnlyVisible - gka 
    //mode OnlyVisible does not work.
    // nent = Reader.NbRootsForTransfer();
    if (!fromtcl) {
      cout<<"Mode (0 End, 1 Visible Roots, 2 All Roots, 3 Only One Entity, 4 Selection) :"<<flush;
      modepri = -1;
      
// amv 26.09.2003 : this is used to avoid error of enter's simbol        
      char str[80];                                                             
      cin>>str;                                                                 
      modepri = Draw::Atoi(str);   
    }

    if (modepri == 0) {  //fin
      di << "Bye and good luck! " << "\n";
      break;
    } 

    else if (modepri <= 2) {  // 1 : Visible Roots, 2 : All Roots
      di << "All Geometry Transfer"<<"\n";
      di<<"spline_continuity (read) : "<<Interface_Static::IVal("read.iges.bspline.continuity")<<" (0 : no modif, 1 : C1, 2 : C2)"<<"\n";
      di<<"  To modify : command  param read.iges.bspline.continuity"<<"\n";
      Handle(XSControl_WorkSession) thesession = Reader.WS();
      thesession->ClearContext();
      XSDRAW::SetTransferProcess (thesession->MapReader());
      progress->NewScope ( 80, "Translation" );
      progress->Show();
      thesession->MapReader()->SetProgress ( progress );
      
      if (modepri == 1) Reader.SetReadVisible (Standard_True);
      Reader.TransferRoots();
      
      thesession->MapReader()->SetProgress ( 0 );
      progress->EndScope();
      progress->Show();
      // result in only one shape for all the roots
      //        or in one shape for one root.
      di<<"Count of shapes produced : "<<Reader.NbShapes()<<"\n";
      Standard_Integer answer = 1;
      if (Reader.NbShapes() > 1) {
	cout << " pass(0)  one shape for all (1)\n or one shape per root (2)\n + WriteBRep (one for all : 3) (one per root : 4) : " << flush;
        answer = -1;
        //amv 26.09.2003                                                        
        char str_a[80];                                                         
        cin >> str_a;                                                           
        answer = Draw::Atoi(str_a);    
      }
      if ( answer == 0) continue;
      if ( answer == 1 || answer == 3) {
	TopoDS_Shape shape = Reader.OneShape();
	// save the shape
	if (shape.IsNull()) { di<<"No Shape produced"<<"\n"; continue; }
	char fname[110];
	Sprintf(fname, "%s", rnom.ToCString());
	di << "Saving shape in variable Draw : " << fname << "\n";
	if (answer == 3) IGESToBRep::WriteShape (shape,1);
	try {
	  OCC_CATCH_SIGNALS
	  DBRep::Set(fname,shape);
	}
	catch(Standard_Failure) {
	  di << "** Exception : ";
	  di << Standard_Failure::Caught()->GetMessageString();
	  di<<" ** Skip"<<"\n";
	  di << "Saving shape in variable Draw : " << fname << "\n";
	  IGESToBRep::WriteShape (shape,1);
	}
      }
	
      else if (answer == 2 || answer == 4) {
	Standard_Integer numshape = Reader.NbShapes();
	for (Standard_Integer inum = 1; inum <= numshape; inum++) {
	  // save all the shapes
	  TopoDS_Shape shape = Reader.Shape(inum);
	  if (shape.IsNull()) { di<<"No Shape produced"<<"\n"; continue; }
	  char fname[110];
	  Sprintf(fname, "%s_%d", rnom.ToCString(),inum);
	  di << "Saving shape in variable Draw : " << fname << "\n";
	  if (answer == 4) IGESToBRep::WriteShape (shape,inum);
	  try {
	    OCC_CATCH_SIGNALS
	    DBRep::Set(fname,shape);
	  }
	  catch(Standard_Failure) {
	    di << "** Exception : ";
	    di << Standard_Failure::Caught()->GetMessageString();
	    di<<" ** Skip"<<"\n";
	  }
	}
      }
      else return 0;
    }

    else if (modepri == 3) {  // One Entity
      cout << "Only One Entity"<<endl;
      cout<<"spline_continuity (read) : "<<Interface_Static::IVal("read.iges.bspline.continuity")<<" (0 : no modif, 1 : C1, 2 : C2)"<<endl;
      cout<<"  To modify : command  param read.iges.bspline.continuity"<<endl;
      cout << " give the number of the Entity : " << flush;
      nent = XSDRAW::GetEntityNumber();

      if (!Reader.TransferOne (nent)) di<<"Transfer entity n0 "<<nent<<" : no result"<<"\n";
      else {
	nbs = Reader.NbShapes();
	char shname[30];  Sprintf (shname,"%s_%d",rnom.ToCString(),nent);
	di<<"Transfer entity n0 "<<nent<<" OK  -> DRAW Shape: "<<shname<<"\n";
	di<<"Now, "<<nbs<<" Shapes produced"<<"\n";
	TopoDS_Shape sh = Reader.Shape(nbs);
	DBRep::Set (shname,sh);
      }
    }

    else if (modepri == 4) {   // Selection
      Standard_Integer answer = 1;
      Handle(TColStd_HSequenceOfTransient)  list;

//  Selection, nommee ou via tcl. tcl : raccourcis admis
//   * donne iges-visible + xst-transferrable-roots
//   *r donne xst-model-roots (TOUTES racines)

      if( fromtcl && argv[3][0]=='*' && argv[3][1]=='\0' ) {         
        di << "All Geometry Transfer"<<"\n";
        di<<"spline_continuity (read) : "<<Interface_Static::IVal("read.iges.bspline.continuity")<<" (0 : no modif, 1 : C1, 2 : C2)"<<"\n";
        di<<"  To modify : command  param read.iges.bspline.continuity"<<"\n";
        Handle(XSControl_WorkSession) thesession = Reader.WS();
        thesession->ClearContext();
        XSDRAW::SetTransferProcess (thesession->MapReader());
        progress->NewScope ( 80, "Translation" );
        progress->Show();
        thesession->MapReader()->SetProgress ( progress );
      
        Reader.SetReadVisible (Standard_True);
        Reader.TransferRoots();
      
        thesession->MapReader()->SetProgress ( 0 );
        progress->EndScope();
        progress->Show();
        
        // result in only one shape for all the roots
        TopoDS_Shape shape = Reader.OneShape();
        // save the shape
        char fname[110];
        Sprintf(fname, "%s", rnom.ToCString());
        di << "Saving shape in variable Draw : " << fname << "\n";
        try {
          OCC_CATCH_SIGNALS
          DBRep::Set(fname,shape);
        }
        catch(Standard_Failure) {
          di << "** Exception : ";
	  di << Standard_Failure::Caught()->GetMessageString();
	  di<<" ** Skip"<<"\n";
          di << "Saving shape in variable Draw : " << fname << "\n";
          IGESToBRep::WriteShape (shape,1);
        }                                                                             
        return 0;
      }
   
      if(fromtcl) {
	modepri = 0;    // d office, une seule passe
	if (argv[3][0] == '*' && argv[3][1] == 'r' && argv[3][2] == '\0') {
	  di<<"All Roots : ";
	  list = XSDRAW::GetList ("xst-model-roots");
	}
        else {
	  TCollection_AsciiString compart = XSDRAW_CommandPart (argc,argv,3);
	  di<<"List given by "<<compart.ToCString()<<" : ";
	  list = XSDRAW::GetList (compart.ToCString());
	}
	if (list.IsNull()) {
          di<<"No list defined. Give a selection name or * for all visible transferrable roots"<<"\n";
          continue;
        }
      }
      else {
	cout<<"Name of Selection :"<<flush;
	list = XSDRAW::GetList();
	if (list.IsNull()) { cout<<"No list defined"<<endl; continue; }
      }

      Standard_Integer nbl = list->Length();
      di<<"Nb entities selected : "<<nbl<<"\n";
      if (nbl == 0) continue;
      while (answer) {
	if (!fromtcl) {
	  cout<<"Choice: 0 abandon  1 transfer all  2 with confirmation  3 list n0s ents :"<<flush;
          answer = -1;
          // anv 26.09.2003                                                     
          char str_answer[80];                                                  
          cin>>str_answer;                                                      
          answer = Draw::Atoi(str_answer);    
	}
	if (answer <= 0 || answer > 3) continue;
	if (answer == 3) {
	  for (Standard_Integer ill = 1; ill <= nbl; ill ++) {
	    Handle(Standard_Transient) ent = list->Value(ill);
	    di<<"  ";// model->Print(ent,di);
	  }
	  di<<"\n";
	}
	if (answer == 1 || answer == 2) {
	  Standard_Integer nbt = 0;
	  Handle(XSControl_WorkSession) thesession = Reader.WS();
	
	  XSDRAW::SetTransferProcess (thesession->MapReader());
          progress->NewScope ( 80, "Translation" );
          progress->Show();
          thesession->MapReader()->SetProgress ( progress );

          Message_ProgressSentry PSentry ( progress, "Root", 0, nbl, 1 );
	  for (Standard_Integer ill = 1; ill <= nbl && PSentry.More(); ill ++, PSentry.Next()) {
	  
	    nent = Reader.Model()->Number(list->Value(ill));
	    if (nent == 0) continue;
	    if (!Reader.TransferOne(nent)) di<<"Transfer entity n0 "<<nent<<" : no result"<<"\n";
	    else {
	      nbs = Reader.NbShapes();
	      char shname[30];  Sprintf (shname,"%s_%d",rnom.ToCString(),nbs);
	      di<<"Transfer entity n0 "<<nent<<" OK  -> DRAW Shape: "<<shname<<"\n";
	      di<<"Now, "<<nbs<<" Shapes produced"<<"\n";
	      TopoDS_Shape sh = Reader.Shape(nbs);
	      DBRep::Set (shname,sh);
              nbt++;
	    }
	  }
	  thesession->MapReader()->SetProgress ( 0 );
          progress->EndScope();
          progress->Show();
	  di<<"Nb Shapes successfully produced : "<<nbt<<"\n";
	  answer = 0;  // on ne reboucle pas
	}
      }
    }
    else di<<"Unknown mode n0 "<<modepri<<"\n";
  }
  return 0;
}

//--------------------------------------------------------------
// Function : testreadiges
//
//--------------------------------------------------------------
static Standard_Integer testread (Draw_Interpretor& di, Standard_Integer argc, const char** argv) 
{
  if (argc != 3)                                                                                      
    {                                                                                             
      di << "ERROR in " << argv[0] << "Wrong Number of Arguments."<<"\n";                     
      di << " Usage : " << argv[0] <<" file_name shape_name"<< "\n";                          
      return 1;                                                                                 
    }  
  IGESControl_Reader Reader;
  Standard_CString filename = argv[1];
  IFSelect_ReturnStatus readstat =  Reader.ReadFile(filename);
  di<<"Status from reading IGES file "<<filename<<" : ";  
  switch(readstat) {                                                              
    case IFSelect_RetVoid  : { di<<"empty file"<<"\n"; return 1; }            
    case IFSelect_RetDone  : { di<<"file read"<<"\n";    break; }             
    case IFSelect_RetError : { di<<"file not found"<<"\n";   return 1; }      
    case IFSelect_RetFail  : { di<<"error during read"<<"\n";  return 1; }    
    default  :  { di<<"failure"<<"\n";   return 1; }                          
  }       
  Reader.TransferRoots();
  TopoDS_Shape shape = Reader.OneShape();
  DBRep::Set(argv[2],shape); 
  di<<"Count of shapes produced : "<<Reader.NbShapes()<<"\n";
  return 0;  
}
 
//--------------------------------------------------------------
// Function : brepiges
//
//--------------------------------------------------------------

static Standard_Integer brepiges (Draw_Interpretor& di, Standard_Integer n, const char** a) 
{
  XSDRAW::SetNorm ("IGES");
  // ecriture dans le model d'une entite :
  //    -  model_AddEntity(ent)             : ecriture de l`entite seule
  //    -  model->AddWithRefs(ent, protocol): ecriture de l`entite et eventuellement 
  //                                          . de sa matrice de transformation 
  //                                          . de ses sous-elements

  IGESControl_Writer ICW (Interface_Static::CVal("write.iges.unit"),
			  Interface_Static::IVal("write.iges.brep.mode"));
  di<<"unit (write) : "<<Interface_Static::CVal("write.iges.unit")<<"\n";
  di<<"mode  write  : "<<Interface_Static::CVal("write.iges.brep.mode")<<"\n";
  di<<"  To modifiy : command  param"<<"\n";

//  Mode d emploi (K4B ->) : brepiges shape [+shape][ +shape] nomfic
//   c a d tant qu il y a des + on ajoute ce qui suit
  const char* nomfic;
  Standard_Integer npris = 0;

  Handle(Draw_ProgressIndicator) progress = new Draw_ProgressIndicator ( di, 1 );
  progress->NewScope(90,"Translating");
  progress->Show();
  ICW.TransferProcess()->SetProgress(progress);

  for ( Standard_Integer i = 1; i < n; i++) {
    const char* nomvar = a[i];
    if (a[i][0] == '+') nomvar = &(a[i])[1];
    else if (i > 1)  {  nomfic = a[i];  break;  }
    TopoDS_Shape Shape = DBRep::Get(nomvar);
    if      (ICW.AddShape (Shape)) npris ++;
    else if (ICW.AddGeom (DrawTrSurf::GetCurve   (nomvar)) ) npris ++;
    else if (ICW.AddGeom (DrawTrSurf::GetSurface (nomvar)) ) npris ++;
  }
  ICW.ComputeModel();
  XSDRAW::SetModel(ICW.Model());
  XSDRAW::SetTransferProcess (ICW.TransferProcess());
    
  ICW.TransferProcess()->SetProgress(0);
  progress->EndScope();
  progress->Show();
  progress->NewScope(10,"Writing");
  progress->Show();

  di<<npris<<" Shapes written, giving "<<XSDRAW::Model()->NbEntities()<<" Entities"<<"\n";

  if ( ! nomfic ) // delayed write
  {
    di<<" Now, to write a file, command : writeall filename"<<"\n";
    return 0;
  }

  // write file
  if (! ICW.Write(nomfic)) di<<" Error: could not write file " << nomfic;
  else                     di<<" File " << nomfic << " written";

  progress->EndScope();
  progress->Show();

  return 0;
}

//--------------------------------------------------------------
// Function : testwriteiges
//
//--------------------------------------------------------------

static Standard_Integer testwrite (Draw_Interpretor& di, Standard_Integer n, const char** a) 
{
  if (n != 3)                                                                                      
    {                                                                                             
      di << "ERROR in " << a[0] << "Wrong Number of Arguments."<<"\n";                     
      di << " Usage : " << a[0] <<" file_name shape_name"<< "\n";                          
      return 1;                                                                                 
    }
  IGESControl_Writer Writer;
  Standard_CString filename = a[1];
  TopoDS_Shape shape = DBRep::Get(a[2]); 
  Standard_Boolean ok = Writer.AddShape(shape);
  if(!ok){
    di<<"Shape not add"<<"\n";
    return 1;
  }
  
  if(!(Writer.Write(filename))){
    di<<"Error on writing file"<<"\n";
    return 1;
  }
  di<<"File Is Written"<<"\n"; 
  return 0;
}
//--------------------------------------------------------------
// Function : igesparam
//
//--------------------------------------------------------------


static Standard_Integer igesparam (Draw_Interpretor& di, Standard_Integer , const char** ) 
{
//  liste des parametres
  di<<"List of parameters which control IGES :"<<"\n";
  di<<"  unit : write.iges.unit\n  mode write : write.iges.brep.mode\n  spline_continuity (read) : read.iges.bspline.continuity\nSee definition by  defparam, read/edit value by  param"<<"\n";
  di<<"unit (write) : "<<Interface_Static::CVal("write.iges.unit")<<"\n";
  di<<"mode  write  : "<<Interface_Static::CVal("write.iges.brep.mode")<<"\n";
  di<<"spline_continuity (read) : "<<Interface_Static::IVal("read.iges.bspline.continuity")<<" (0 : no modif, 1 : C1, 2 : C2)"<<"\n";
  di<<"\n"<<" To modifier, param nom_param new_val"<<"\n";
  return 0;
}


//--------------------------------------------------------------
// Function : tplosttrim
//
//--------------------------------------------------------------

static Standard_Integer XSDRAWIGES_tplosttrim (Draw_Interpretor& di, Standard_Integer n, const char** a) 
{
  Handle(IFSelect_SessionPilot) pilot = XSDRAW::Pilot();

//  Standard_Integer narg = pilot->NbWords();
  Standard_Integer narg = n;

  Handle(Transfer_TransientProcess) TP = XSControl::Session(pilot)->MapReader();
  TColStd_Array1OfAsciiString strarg(1, 3);
  TColStd_Array1OfAsciiString typarg(1, 3);
  strarg.SetValue(1,"xst-type(CurveOnSurface)");
  strarg.SetValue(2,"xst-type(Boundary)");
  strarg.SetValue(3,"xst-type(Loop)");
  typarg.SetValue(1,"IGESGeom_TrimmedSurface");
  typarg.SetValue(2,"IGESGeom_BoundedSurface");
  typarg.SetValue(3,"IGESSolid_Face");
  if (TP.IsNull()) { di<<"No Transfer Read"<<"\n"; return 1; }
  Standard_Integer nbFaces = 0, totFaces = 0 ;
  Handle(IFSelect_WorkSession) WS = pilot->Session(); 
  Transfer_IteratorOfProcessForTransient itrp = TP->AbnormalResult(); 
  Standard_Integer k=0;
  if(narg > 1) {
//    TCollection_AsciiString Arg = pilot->Word(1);
    TCollection_AsciiString Arg(a[1]);
    for(k=1 ; k<=3;k++ ) {
      if(typarg.Value(k).Location(Arg,1,typarg.Value(k).Length()) != 0) break;
    }
  }   
  if( k == 4) {di<< "Invalid argument"<<"\n"; return 0; }
  for(Standard_Integer j = 1 ; j <= 3; j++) {
    TColStd_MapOfTransient aMap;
    if(narg == 1) k=j;
    Handle(TColStd_HSequenceOfTransient) list = IFSelect_Functions::GiveList(pilot->Session(),strarg.Value(k).ToCString());
    if (!list.IsNull()) itrp.Filter (list);
    else {
      di << "No untrimmed faces" << "\n";
      return 0;
    }
    for (itrp.Start(); itrp.More(); itrp.Next()) {
      Handle(Standard_Transient) ent = itrp.Starting();
      Handle(TColStd_HSequenceOfTransient) super = WS->Sharings (ent);
      if (!super.IsNull()) {
	Standard_Integer nb = super->Length();
	if (nb > 0) {
	    for (Standard_Integer i = 1; i <= nb; i++)
	      if (super->Value(i)->IsKind (typarg.Value(k).ToCString())) {
		if(aMap.Add(super->Value(i))) nbFaces++;
	      }
	}
      }
    }
    if(nbFaces != 0) {
      if( j == 1 ) di << "Number of untrimmed faces: " << "\n";
      switch(k){
      case 1:  
	di << "Trimmed Surface: " << "\n"; break;
      case 2:
	di << "Bounded Surface: " << "\n"; break;
      case 3:
	di << "Face: " << "\n"; break;
      }
      Handle(Message_Messenger) aDIMessenger = 
	new Message_Messenger (new Draw_Printer(di));
      TColStd_MapIteratorOfMapOfTransient itmap;
      for(itmap.Initialize(aMap); itmap.More(); itmap.Next()) {
	//XSDRAW::Model()->Print(itmap.Key(),cout);
	Standard_SStream aSStream;
	XSDRAW::Model()->Print(itmap.Key(),aDIMessenger);
	di << aSStream;
	di<<"  ";
      }
      di << "\n";
      di << "\n" << "Number:"<< nbFaces << "\n";
      totFaces += nbFaces;
    }
    if(narg > 1) break;
    nbFaces = 0;
  }
  
  if(totFaces == 0) di << "No untrimmed faces" << "\n";
  else              di << "Total number :" << totFaces << "\n";
  return 0;
}
//-------------------------------------------------------------------
//--------------------------------------------------------------
// Function : TPSTAT
//
//--------------------------------------------------------------
static Standard_Integer XSDRAWIGES_TPSTAT(Draw_Interpretor& di,Standard_Integer n, const char** a)
{
  Handle(IFSelect_SessionPilot) pilot = XSDRAW::Pilot();
  Standard_Integer argc = n;//= pilot->NbWords();
  const Standard_CString arg1 = a[1];//pilot->Arg(1);
  //IGESControl_Reader read; //(XSControl::Session(pilot),Standard_False);
  Handle(Transfer_TransientProcess) TP= XSControl::Session(pilot)->MapReader();
   IGESControl_Reader read; //(XSControl::Session(pilot),Standard_False);
  //read.SetTransientProcess(TP);
//        ****    tpent        ****
//  if (TP.IsNull()) { di<<"No Transfer Read"<<"\n"; return IFSelect_RetError;}
  Handle(Interface_InterfaceModel) model = TP->Model();
  //Handle(Interface_InterfaceModel) model = read.Model();
  if (model.IsNull()) {di<<"No Transfer Read"<<"\n"; return -1;}
 //DeclareAndCast(IGESData_IGESModel,modelig,model);
 // read.SetModel(modelig);
  Handle(XSControl_WorkSession) thesession = read.WS();
  thesession->SetMapReader(TP);
  //read.SetModel(model);
  Standard_Integer mod1 = 0;
  if (argc > 1) {
    char a2 = arg1[1]; if (a2 == '\0') a2 = '!';
    switch (arg1[0]) {
    case 'g' : read.PrintTransferInfo(IFSelect_FailAndWarn,IFSelect_GeneralInfo);break;
    case 'c' : read.PrintTransferInfo(IFSelect_FailAndWarn,IFSelect_CountByItem); break;
    case 'C' : read.PrintTransferInfo(IFSelect_FailAndWarn,IFSelect_ListByItem); break;
    case 'r' : read.PrintTransferInfo(IFSelect_FailAndWarn,IFSelect_ResultCount);break;
    case 's' : read.PrintTransferInfo(IFSelect_FailAndWarn,IFSelect_Mapping);break;
    case '?' : mod1 = -1; break;
    default  : mod1 = -2; break;
    }
  }
  if (mod1 < -1) di<<"Unknown Mode"<<"\n";
  if (mod1 < 0) {
    di<<"Modes available :\n"
      <<"g : general    c : checks (count)  C (list)"<<"\n"
      <<"r : number of CasCade resulting shapes"<<"\n"
      <<"s : mapping between IGES entities and CasCade shapes"<<"\n";
    if (mod1 < -1) return -1;
    return 0;
  }
  return 0;
}

static Standard_Integer etest(Draw_Interpretor& di, Standard_Integer argc, const char** a)
{
  if(argc < 3) {
    di<<"etest igesfile shape"<<"\n";
    return 0;
  }
  IGESControl_Reader aReader;
  aReader.ReadFile(a[1]);
  aReader.SetReadVisible(Standard_True);
  aReader.TransferRoots();
  TopoDS_Shape shape = aReader.OneShape();
  DBRep::Set(a[2],shape);
  return 0;
}

extern "C" {
static void cleanpilot ()
{
  XSDRAW::Session()->ClearData(1);
}
}


//--------------------------------------------------------------
// Function : Init(s)
//
//--------------------------------------------------------------

void  XSDRAWIGES::InitSelect ()
{
  Handle(IGESSelect_Activator)    igesact = new IGESSelect_Activator;
  IGESControl_Controller::Init();
//  XSDRAW::SetNorm ("IGES");  trop tot
  XSDRAW::SetController (XSControl_Controller::Recorded("iges"));
  
  atexit (cleanpilot);
}


//=======================================================================
//function : InitToBRep
//purpose  : 
//=======================================================================

void  XSDRAWIGES::InitToBRep (Draw_Interpretor& theCommands)
{
  const char* g = "DE: IGES";
  theCommands.Add("igesbrep",     "igesbrep [file else already loaded model] [name DRAW]",     __FILE__, igesbrep,              g);
  theCommands.Add("testreadiges", "testreadiges [file else already loaded model] [name DRAW]", __FILE__, testread,              g);
  theCommands.Add("igesread",     "igesread [file else already loaded model] [name DRAW]",     __FILE__, igesbrep,              g);
  theCommands.Add("igesparam",    "igesparam ->list, + name ->one param, + name val->change",  __FILE__, igesparam,             g);
  theCommands.Add("TPSTAT",       " ",                                                         __FILE__, XSDRAWIGES_TPSTAT,     g);
  theCommands.Add("tplosttrim",   "number of untrimmed faces during last transfer",            __FILE__, XSDRAWIGES_tplosttrim, g);
  theCommands.Add("etest",        "test of eviewer",                                           __FILE__, etest,                 g);

}


//=======================================================================
//function : InitFromBRep
//purpose  : 
//=======================================================================

void  XSDRAWIGES::InitFromBRep (Draw_Interpretor& theCommands)
{
  const char* g = "DE: IGES";
  theCommands.Add("brepiges",      "brepiges sh1 [+sh2 [+sh3 ..]] filename.igs", __FILE__, brepiges,  g);
  theCommands.Add("testwriteiges", "testwriteiges filename.igs shape",           __FILE__, testwrite, g);
}
