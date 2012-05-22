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

#include <StepSelect_WorkLibrary.ixx>

#include <sys/stat.h>
#include <errno.h>

#include <StepData_Protocol.hxx>
#include <StepData_StepModel.hxx>
#include <StepFile_Read.hxx>
#include <StepData_StepWriter.hxx>
#include <Interface_CheckIterator.hxx>

#include <StepSelect_FileModifier.hxx>

#include <StepData_UndefinedEntity.hxx>
#include <StepData_StepDumper.hxx>

#include <TCollection_HAsciiString.hxx>
#include <TColStd_HSequenceOfInteger.hxx>
#include <IFSelect_GeneralModifier.hxx>
#include <Interface_ParamType.hxx>
#include <Interface_ReportEntity.hxx>
#include <Interface_UndefinedContent.hxx>

#include <Message.hxx>
#include <Message_Messenger.hxx>
#include <Interface_Macros.hxx>
#include <Interface_Check.hxx>

StepSelect_WorkLibrary::StepSelect_WorkLibrary
  (const Standard_Boolean copymode)
  : thecopymode (copymode) , thelabmode (0)
{
  SetDumpLevels (1,2);
  SetDumpHelp (0,"#id + Step Type");
  SetDumpHelp (1,"Entity as in file");
  SetDumpHelp (2,"Entity + shareds (level 1) as in file");
}
// rq : les init sont faits par ailleurs, pas de souci a se faire


void  StepSelect_WorkLibrary::SetDumpLabel (const Standard_Integer mode)
{
  thelabmode = mode;
}


Standard_Integer  StepSelect_WorkLibrary::ReadFile
  (const Standard_CString name,
   Handle(Interface_InterfaceModel)& model,
   const Handle(Interface_Protocol)& protocol) const
{
  long status = 1;
  DeclareAndCast(StepData_Protocol,stepro,protocol);
  if (stepro.IsNull()) return 1;
  Handle(StepData_StepModel) stepmodel  = new StepData_StepModel;
  model  = stepmodel;
  StepFile_ReadTrace (0);
  char *pName=(char *)name;
  status = StepFile_Read (pName,stepmodel,stepro);
  return status;
}


Standard_Boolean  StepSelect_WorkLibrary::WriteFile
  (IFSelect_ContextWrite& ctx) const
{
//  Preparation
  Handle(Message_Messenger) sout = Message::DefaultMessenger();
  DeclareAndCast(StepData_StepModel,stepmodel,ctx.Model());
  DeclareAndCast(StepData_Protocol,stepro,ctx.Protocol());
  if (stepmodel.IsNull() || stepro.IsNull()) return Standard_False;

  ofstream fout;
  fout.open(ctx.FileName(),ios::out|ios::trunc);

  if (!fout || !fout.rdbuf()->is_open()) {
    ctx.CCheck(0)->AddFail("Step File could not be created");
    sout<<" Step File could not be created : " << ctx.FileName() << endl; return 0;
  }
  sout << " Step File Name : "<<ctx.FileName();
  StepData_StepWriter SW(stepmodel);
  sout<<"("<<stepmodel->NbEntities()<<" ents) ";

//  File Modifiers
  Standard_Integer nbmod = ctx.NbModifiers();
  for (Standard_Integer numod = 1; numod <= nbmod; numod ++) {
    ctx.SetModifier (numod);
    DeclareAndCast(StepSelect_FileModifier,filemod,ctx.FileModifier());
    if (!filemod.IsNull()) filemod->Perform(ctx,SW);
//   (impressions de mise au point)
    sout << " .. FileMod." << numod << filemod->Label();
    if (ctx.IsForAll()) sout << " (all model)";
    else  sout << " (" << ctx.NbEntities() << " entities)";
//    sout << flush;
  }

//  Envoi
  SW.SendModel(stepro);
  Interface_CheckIterator chl = SW.CheckList();
  for (chl.Start(); chl.More(); chl.Next())
    ctx.CCheck(chl.Number())->GetMessages(chl.Value());
  sout<<" Write ";
  Standard_Boolean isGood = SW.Print(fout);                 
  sout<<" Done"<<endl;
      
  errno = 0;
  fout.close();
  isGood = fout.good() && isGood && !errno;
  if(errno)
    sout << strerror(errno) << endl;
  return isGood;  
}


Standard_Boolean  StepSelect_WorkLibrary::CopyModel
  (const Handle(Interface_InterfaceModel)& original,
   const Handle(Interface_InterfaceModel)& newmodel,
   const Interface_EntityIterator& list,
   Interface_CopyTool& TC) const
{
  if (thecopymode) return
    IFSelect_WorkLibrary::CopyModel (original,newmodel,list,TC);
  return thecopymode;
}


void  StepSelect_WorkLibrary::DumpEntity
  (const Handle(Interface_InterfaceModel)& model,
   const Handle(Interface_Protocol)& protocol,
   const Handle(Standard_Transient)& entity,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  Standard_Integer nument = model->Number(entity);
  if (nument <= 0 || nument > model->NbEntities()) return;
  Standard_Boolean iserr = model->IsRedefinedContent(nument);
  Handle(Standard_Transient) ent, con;  ent = entity;
  S<<" --- (STEP) Entity ";  model->Print(entity,S);
  if (iserr) con = model->ReportEntity(nument)->Content();
  if (entity.IsNull()) {  S<<" Null"<<endl; return;  }

//  On attaque le dump : d abord cas de l Erreur
  S << " Type cdl : " << entity->DynamicType()->Name() << endl;
  if (iserr)
    S<<" ***  NOT WELL LOADED : CONTENT FROM FILE  ***"<<endl;
  else if (model->IsUnknownEntity(nument))
    S<<" ***  UNKNOWN TYPE  ***"<<endl;

  StepData_StepDumper dump(GetCasted(StepData_StepModel,model),
                           GetCasted(StepData_Protocol,protocol),thelabmode);
  dump.Dump(S,ent,level);
}
