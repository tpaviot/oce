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


#include <Standard_Stream.hxx>

#include <IGESSelect_WorkLibrary.ixx>
#include <Standard_ErrorHandler.hxx>
#include <Message_Messenger.hxx>
#include <Message.hxx>

#include <IGESSolid.hxx>
#include <IGESAppli.hxx>
#include <IGESDefs.hxx>

#include <IGESData_IGESWriter.hxx>
#include <IGESData_IGESModel.hxx>
#include <IGESData_Protocol.hxx>
#include <IGESData_FileProtocol.hxx>
#include <IGESFile_Read.hxx>
#include <IGESSelect_Dumper.hxx>
#include <IFSelect_GeneralModifier.hxx>
#include <TColStd_HSequenceOfInteger.hxx>
#include <IGESSelect_FileModifier.hxx>

#include <Interface_ReportEntity.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESData_IGESDumper.hxx>

#include <Interface_Check.hxx>

#include <Interface_Macros.hxx>
#include <errno.h>

static int deja = 0;
static  Handle(IGESData_FileProtocol) IGESProto;


     IGESSelect_WorkLibrary::IGESSelect_WorkLibrary
  (const Standard_Boolean modefnes)
  : themodefnes (modefnes)
{
  IGESSolid::Init();
  IGESAppli::Init();
  IGESDefs::Init();

  if (!deja) {
    Handle(IGESSelect_Dumper) sesdump = new IGESSelect_Dumper;  // ainsi,cestfait
    deja = 1;
  }
  SetDumpLevels (4,6);
  SetDumpHelp (0,"Only DNum");
  SetDumpHelp (1,"DNum, IGES Type & Form");
  SetDumpHelp (2,"Main Directory Informations");
  SetDumpHelp (3,"Complete Directory Part");
  SetDumpHelp (4,"Directory + Fields (except list contents)");
  SetDumpHelp (5,"Complete (with list contents)");
  SetDumpHelp (6,"Complete + Transformed data");
}

    Standard_Integer  IGESSelect_WorkLibrary::ReadFile
  (const Standard_CString name,
   Handle(Interface_InterfaceModel)& model,
   const Handle(Interface_Protocol)& protocol) const
{
  Handle(Message_Messenger) sout = Message::DefaultMessenger();
  Handle(IGESData_IGESModel) igesmod = new IGESData_IGESModel;
  DeclareAndCast(IGESData_Protocol,prot,protocol);

  char* pname=(char*) name;
  Standard_Integer status = IGESFile_Read (pname,igesmod,prot);

  if (status < 0) sout<<"File not found : "<<name<<endl;
  if (status > 0) sout<<"Error when reading file : "<<name<<endl;
  if (status == 0) model = igesmod;
  else             model.Nullify();
  return status;
}


    Standard_Boolean  IGESSelect_WorkLibrary::WriteFile
  (IFSelect_ContextWrite& ctx) const
{
  Handle(Message_Messenger) sout = Message::DefaultMessenger();
//  Preparation
  DeclareAndCast(IGESData_IGESModel,igesmod,ctx.Model());
  DeclareAndCast(IGESData_Protocol,prot,ctx.Protocol());

  if (igesmod.IsNull() || prot.IsNull()) return Standard_False;
  ofstream fout;
  fout.rdbuf()->open(ctx.FileName(),ios::out );
  if (!fout) {
    ctx.CCheck(0)->AddFail("IGES File could not be created");
    sout<<" - IGES File could not be created : " << ctx.FileName() << endl; return 0;
  }
  sout<<" IGES File Name : "<<ctx.FileName();
  IGESData_IGESWriter VW(igesmod);  
  sout<<"("<<igesmod->NbEntities()<<" ents) ";

//  File Modifiers
  Standard_Integer nbmod = ctx.NbModifiers();
  for (Standard_Integer numod = 1; numod <= nbmod; numod ++) {
    ctx.SetModifier (numod);
    DeclareAndCast(IGESSelect_FileModifier,filemod,ctx.FileModifier());
    if (!filemod.IsNull()) filemod->Perform(ctx,VW);
//   (impressions de mise au point)
    sout << " .. FileMod." << numod <<" "<< filemod->Label();
    if (ctx.IsForAll()) sout << " (all model)";
    else  sout << " (" << ctx.NbEntities() << " entities)";
//    sout << flush;
  }

//  Envoi
  VW.SendModel(prot);            
  sout<<" Write ";
  if (themodefnes) VW.WriteMode() = 10;
  Standard_Boolean status = VW.Print(fout);                sout<<" Done"<<endl;

  errno = 0;
  fout.close();
  status = fout.good() && status && !errno;
  if(errno)
    sout << strerror(errno) << endl;

  return status;
}

    Handle(IGESData_Protocol)  IGESSelect_WorkLibrary::DefineProtocol ()
{
  if (!IGESProto.IsNull()) return IGESProto;
  Handle(IGESData_Protocol)     IGESProto1 = IGESSolid::Protocol();
  Handle(IGESData_Protocol)     IGESProto2 = IGESAppli::Protocol();
//  Handle(IGESData_FileProtocol) IGESProto  = new IGESData_FileProtocol;
  IGESProto  = new IGESData_FileProtocol;
  IGESProto->Add(IGESProto1);
  IGESProto->Add(IGESProto2);
  return IGESProto;
}


    void  IGESSelect_WorkLibrary::DumpEntity
  (const Handle(Interface_InterfaceModel)& model, 
   const Handle(Interface_Protocol)& protocol,
   const Handle(Standard_Transient)& entity,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  DeclareAndCast(IGESData_IGESModel,igesmod,model);
  DeclareAndCast(IGESData_Protocol,igespro,protocol);
  DeclareAndCast(IGESData_IGESEntity,igesent,entity);
  if (igesmod.IsNull() || igespro.IsNull() || igesent.IsNull()) return;
  Standard_Integer num = igesmod->Number(igesent);
  if (num == 0) return;

  S<<" --- Entity "<<num;
  Standard_Boolean iserr = model->IsRedefinedContent(num);
  Handle(Standard_Transient) con;
  if (iserr) con = model->ReportEntity(num)->Content();
  if (entity.IsNull()) { S<<" Null"<<endl; return ;  }

//  On attaque le dump : d abord cas de l Erreur
  if (iserr) {
    S << " ERRONEOUS, Content, Type cdl : ";
    if (!con.IsNull()) S << con->DynamicType()->Name();
    else S << "(undefined)" << endl;
    igesent = GetCasted(IGESData_IGESEntity,con);
    con.Nullify();
    Handle(Interface_Check) check = model->ReportEntity(num)->Check();
    Interface_CheckIterator chlist;
    chlist.Add (check,num);
    chlist.Print (S,igesmod,Standard_False);
    if (igesent.IsNull()) return;
  }
  else S << " Type cdl : " << igesent->DynamicType()->Name();

  IGESData_IGESDumper dump(igesmod,igespro);
  try {
    OCC_CATCH_SIGNALS
    dump.Dump(igesent,S,level,(level-1)/3);
  }
  catch (Standard_Failure) {
    S << " **  Dump Interrupt **" << endl;
  }
}
