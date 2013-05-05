// Created on: 2000-03-01
// Created by: Denis PASCAL
// Copyright (c) 2000-2012 OPEN CASCADE SAS
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



#include <DDocStd.hxx>
#include <Draw.hxx>
#include <Draw_Interpretor.hxx>
#include <Draw_Viewer.hxx>
#include <DDocStd_DrawDocument.hxx>
#include <TDocStd_Application.hxx>
#include <TDocStd_Document.hxx>
#include <TDataStd_Name.hxx>
#include <Draw.hxx>
#include <Standard_GUID.hxx>
#include <Standard_ExtString.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>
#include <TDF.hxx>
#include <TDF_Data.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Tool.hxx> 

#include <OSD_Path.hxx>
#include <TDocStd_PathParser.hxx>
//#include <TPrsStd_AISViewer.hxx>
//#include <AIS_InteractiveContext.hxx>

#ifndef WNT
extern Draw_Viewer dout;
#else
Standard_IMPORT Draw_Viewer dout;
#endif

extern int ViewerMainLoop (Standard_Integer, const char**); 
#include <ViewerTest_Tool.hxx>

//=======================================================================
//function : ListDocuments
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_ListDocuments (Draw_Interpretor& di,
					       Standard_Integer nb,
					       const char** /*a*/)
{  
  if (nb == 1) {
    Handle(TDocStd_Application) A;
    if (!DDocStd::Find(A)) return 1;
    Handle(TDocStd_Document) D;
    Standard_Integer nbdoc = A->NbDocuments();
    for (Standard_Integer i = 1; i <= nbdoc; i++) {
      A->GetDocument(i,D);
      di <<"document " << i;
      if (D->IsSaved()) {
	TCollection_AsciiString GetNameAsciiString(D->GetName().ToExtString(),'?');
	TCollection_AsciiString GetPathAsciiString(D->GetPath().ToExtString(),'?');
	//cout << " name : " << D->GetName();
	//cout << " path : " << D->GetPath();
	di << " name : " << GetNameAsciiString.ToCString();
	di << " path : " << GetPathAsciiString.ToCString();
      }
      else di << " not saved";
      di << "\n";
    }
    return 0;
  }
  di << "DDocStd_ListDocuments : Error" << "\n";
  return 1; 
}


//=======================================================================
//function : NewDocument
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_NewDocument (Draw_Interpretor& di,
					     Standard_Integer nb,
					     const char** a)
{    
  Handle(TDocStd_Document) D; 
  Handle(DDocStd_DrawDocument) DD;
  if (nb == 2) {
    if (!DDocStd::GetDocument(a[1],D,Standard_False)) { 
      D = new TDocStd_Document("dummy");  
      DD = new DDocStd_DrawDocument(D);  
      Draw::Set(a[1],DD);       
      di << "document (not handled by application)  " << a[1] << " created" << "\n";  
      DDocStd::ReturnLabel(di,D->Main()); 
    }    
    else di << a[1] << " is already a document" << "\n";
    return 0;
  }
  if (nb == 3) {   
    if (!DDocStd::GetDocument(a[1],D,Standard_False)) {  
      Handle(TDocStd_Application) A;
      if (!DDocStd::Find(A)) return 1;
      A->NewDocument(a[2],D);  
      DD = new DDocStd_DrawDocument(D);  
      TDataStd_Name::Set(D->GetData()->Root(),a[1]);  
      Draw::Set(a[1],DD);    
      di << "document " << a[1] << " created" << "\n";    
      DDocStd::ReturnLabel(di,D->Main()); 
    }
    else di << a[1] << " is already a document" << "\n";
    return 0;
  }   
  di << "DDocStd_NewDocument : Error" << "\n";
  return 1;
}

//=======================================================================
//function : InitViewer
//purpose  : 
//=======================================================================

// static Standard_Integer DDocStd_InitViewer (Draw_Interpretor& di,
// 					    Standard_Integer nb,
// 					    const char** arg)
// {
//   if (nb == 2) {    
//     Handle(TDocStd_Application) A;
//     if (!DDocStd::Find(A)) return 1;       
//     Handle(TDocStd_Document) D;
//     if (!DDocStd::GetDocument(arg[1],D)) return 1;     
//     Handle(TPrsStd_AISViewer) viewer;
//     if (!TPrsStd_AISViewer::Find (D->Main(),viewer)) {
//       TCollection_AsciiString title;  
//       title.Prepend(arg[1]);   
//       title.Prepend("_"); 
//       title.Prepend("Document");  
//       Handle(V3d_Viewer) vw = ViewerTest_Tool::MakeViewer (title.ToCString()); 
//       Handle(AIS_InteractiveContext) IC = new AIS_InteractiveContext(vw);
//       A->SetViewer (D,IC);
//     } 
//     ViewerTest_Tool::InitViewerTest (viewer->GetInteractiveContext());
//     return 0;
//   }
//   cout << "DDocStd_InitViewer : Error" << endl;
//   return 1;
// }


//=======================================================================
//function : Open
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_Open (Draw_Interpretor& di,
				      Standard_Integer nb,
				      const char** a)
{   
  if (nb == 3) {
    TCollection_ExtendedString path (a[1]); 
    Handle(TDocStd_Application) A;
    if (!DDocStd::Find(A)) return 1;
    Handle(TDocStd_Document) D;
    Standard_Integer insession = A->IsInSession(path);
    if (insession > 0) {  
      di <<"document " << insession << "  is already in session" << "\n";
      return 0;
    }
    PCDM_ReaderStatus theStatus = A->Open(path,D);
    if (theStatus == PCDM_RS_OK && !D.IsNull()) {
      Handle(DDocStd_DrawDocument) DD = new DDocStd_DrawDocument(D);
      TDataStd_Name::Set(D->GetData()->Root(),a[2]);
      Draw::Set(a[2],DD);
      return 0; 
    } else {
      switch ( theStatus ) {
      case PCDM_RS_AlreadyRetrieved: 
      case PCDM_RS_AlreadyRetrievedAndModified: {
	di << " already retrieved " << "\n" ;  
	break;
      }
      case PCDM_RS_NoDriver: {
	di << " could not retrieve , no Driver to make it " <<"\n" ;
	break ;
      }
      case PCDM_RS_UnknownDocument:
      case PCDM_RS_NoModel: {
	di << " could not retrieve , Unknown Document or No Model " <<"\n";
	break ; 
      }
      case PCDM_RS_TypeNotFoundInSchema:
      case PCDM_RS_UnrecognizedFileFormat: {
	di << " could not retrieve , Type not found or Unrecognized File Format" <<"\n";
	break ;
      }
      case PCDM_RS_PermissionDenied: {
	di << " could not retrieve , permission denied " << "\n" ;  
	break;
      }
      default:
	di << " could not retrieve " << "\n" ;  
	break;
      }
      di << "DDocStd_Open : Error" << "\n";
    }	
  }
  return 1;
}

//=======================================================================
//function : Save
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_Save (Draw_Interpretor& di,
				      Standard_Integer nb,
				      const char** a)
{  
  if (nb == 2) {
    Handle(TDocStd_Document) D;    
    if (!DDocStd::GetDocument(a[1],D)) return 1;
    Handle(TDocStd_Application) A;
    if (!DDocStd::Find(A)) return 1;  
    if (!D->IsSaved()) {
      di << "this document has never been saved" << "\n";
      return 0;
    }
    A->Save(D);
    return 0; 
  }
  di << "DDocStd_Save : Error" << "\n";
  return 1;
}

//=======================================================================
//function : SaveAs
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_SaveAs (Draw_Interpretor& di,
					Standard_Integer nb,
					const char** a)
{  
  if (nb == 3) {
    Handle(TDocStd_Document) D;    
    if (!DDocStd::GetDocument(a[1],D)) return 1;  
    TCollection_ExtendedString path (a[2]); 
    Handle(TDocStd_Application) A;
    if (!DDocStd::Find(A)) return 1;
    PCDM_StoreStatus theStatus = A->SaveAs(D,path);
    if (theStatus != PCDM_SS_OK ) {
      switch ( theStatus ) {
      case PCDM_SS_DriverFailure: {
	di << " could not store , no driver found to make it " <<"\n" ;
	break ;
      }
      case PCDM_SS_WriteFailure: {
	di << " Write access failure " << "\n" ;  
	break;
      }
      case PCDM_SS_Failure: {
	di << " Write failure " << "\n" ;  
      }
      default: /* Do nothing */ break;
      }
      return 1;
    } else {
      return 0; 
    }
  }
  di << "DDocStd_SaveAs : Error not enough argument" << "\n";
  return 1;
}

//=======================================================================
//function : Close
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_Close (Draw_Interpretor& di,
				       Standard_Integer nb,
				       const char** a)
{   
  if (nb == 2) {   
    Handle(TDocStd_Document) D;   
    if (!DDocStd::GetDocument(a[1],D)) return 1;
    Handle(TDocStd_Application) A;
    if (!DDocStd::Find(A)) return 1;
    A->Close(D); 

    Handle(Draw_Drawable3D) DD = Draw::Get(a[1],Standard_False);
    dout.RemoveDrawable (DD);
    Handle(Draw_Drawable3D) aDNull;
    Draw::Set(a[1], aDNull);
    return 0;
  }
  di << "DDocStd_Close : Error" << "\n";
  return 1;
}

//=======================================================================
//function : IsInSession
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_IsInSession (Draw_Interpretor& di,
					     Standard_Integer nb,
					     const char** a)
{   
  if (nb == 2) {   
    Handle(TDocStd_Application) A;
    if (!DDocStd::Find(A)) return 1;
    di << A->IsInSession(a[1]);
    return 0;
  }  
  di << "DDocStd_IsInSession : Error" << "\n";
  return 1;
}

 
//=======================================================================
//function : OSDPath
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_OSDPath (Draw_Interpretor& di,
                                         Standard_Integer nb,
                                         const char** a)
{   
  if (nb == 2) { 
    OSD_Path path (a[1]);
    di << "Node      : " << path.Node().ToCString() << "\n";  
    di << "UserName  : " << path.UserName().ToCString() << "\n"; 
    di << "Password  : " << path.Password().ToCString() << "\n";  
    di << "Disk      : " << path.Disk().ToCString() << "\n";
    di << "Trek      : " << path.Trek().ToCString() << "\n"; 
    di << "Name      : " << path.Name().ToCString() << "\n";  
    di << "Extension : " << path.Extension().ToCString() << "\n";
    return 0;
  }
  di << "DDocStd_OSDPath : Error" << "\n";
  return 1;
}


//=======================================================================
//function : Path
//purpose  : 
//=======================================================================

static Standard_Integer DDocStd_Path (Draw_Interpretor& di,
				       Standard_Integer nb,
				       const char** a)
{   
  if (nb == 2) { 
    TDocStd_PathParser path (a[1]);
    //cout << "Trek      : " << path.Trek() << endl;  
    //cout << "Name      : " << path.Name() << endl; 
    //cout << "Extension : " << path.Extension() << endl;
    //cout << "Path      : " << path.Path() << endl;
    TCollection_AsciiString TrekAsciiString(path.Trek().ToExtString(),'?');
    TCollection_AsciiString NameAsciiString(path.Name().ToExtString(),'?');
    TCollection_AsciiString ExtensionAsciiString(path.Extension().ToExtString(),'?');
    TCollection_AsciiString PathAsciiString(path.Path().ToExtString(),'?');
    di << "Trek      : " << TrekAsciiString.ToCString() << "\n";  
    di << "Name      : " << NameAsciiString.ToCString() << "\n"; 
    di << "Extension : " << ExtensionAsciiString.ToCString() << "\n";
    di << "Path      : " << PathAsciiString.ToCString() << "\n";
    return 0;
  }
  di << "DDocStd_Path : Error" << "\n";
  return 1;
}

//=======================================================================
//function : AddComment
//purpose  : 
//=======================================================================
static Standard_Integer DDocStd_AddComment (Draw_Interpretor& di,
                                            Standard_Integer nb,
                                            const char** a)
{  
  if (nb == 3) {
    Handle(TDocStd_Document) D;    
    if (!DDocStd::GetDocument(a[1],D)) return 1;  
    TCollection_ExtendedString comment (a[2]); 
//    Handle(TDocStd_Application) A;
//    if (!DDocStd::Find(A)) return 1;
//    A->AddComment(D,comment);
    D->AddComment(comment);
    return 0; 
  }
  di << "DDocStd_AddComment : Wrong arguments number" << "\n";
  return 1;
}

//=======================================================================
//function : PrintComments
//purpose  : 
//=======================================================================
static Standard_Integer DDocStd_PrintComments (Draw_Interpretor& di,
                                               Standard_Integer nb,
                                               const char** a)
{  
  if (nb == 2) {
    Handle(TDocStd_Document) D;    
    if (!DDocStd::GetDocument(a[1],D)) return 1;  

    TColStd_SequenceOfExtendedString comments;
    D->Comments(comments);

    for (int i = 1; i <= comments.Length(); i++)
    {
      //cout << comments(i) << endl;
      TCollection_AsciiString commentAsciiString(comments(i).ToExtString(),'?');
      di << commentAsciiString.ToCString() << "\n";
    }

    return 0; 
  }
  di << "DDocStd_PrintComments : Wrong arguments number" << "\n";
  return 1;
}

//=======================================================================
//function : ApplicationCommands
//purpose  : 
//=======================================================================

void DDocStd::ApplicationCommands(Draw_Interpretor& theCommands) 
{
  
  static Standard_Boolean done = Standard_False;
  if (done) return;
  done = Standard_True;

  const char* g = "DDocStd application commands";

  // user application commands

  
  theCommands.Add("ListDocuments",
		  "ListDocuments",
		  __FILE__, DDocStd_ListDocuments, g);  

  theCommands.Add("NewDocument",
		  "NewDocument docname format",
		  __FILE__, DDocStd_NewDocument, g);  

  //theCommands.Add("InitViewer",
	//	  "InitViewer DOC",
	//	  __FILE__, DDocStd_InitViewer, g);

  theCommands.Add("Open",
		  "Open path docname",
		  __FILE__, DDocStd_Open, g);   

  theCommands.Add("SaveAs",
		  "SaveAs DOC path",
		  __FILE__, DDocStd_SaveAs, g);  

  theCommands.Add("Save",
		  "Save",
		  __FILE__, DDocStd_Save, g);  

  theCommands.Add("Close",
		  "Close DOC",
		  __FILE__, DDocStd_Close, g);   

  theCommands.Add("IsInSession",
		  "IsInSession path",
		  __FILE__, DDocStd_IsInSession, g);  

  theCommands.Add("OSDPath",
		  "OSDPath string",
		  __FILE__, DDocStd_OSDPath, g);  

  theCommands.Add("Path",
		  "Path string",
		  __FILE__, DDocStd_Path, g);

  theCommands.Add("AddComment",
		  "AddComment Doc string",
		  __FILE__, DDocStd_AddComment, g);

  theCommands.Add("PrintComments",
		  "PrintComments Doc",
		  __FILE__, DDocStd_PrintComments, g);

 // active document

  //theCommands.Add("Active",
	//	  "Active [D]",
	//	  __FILE__, DDocStd_Active, g);  

}
