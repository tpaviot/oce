//--------------------------------------------------------------------
//
//  File Name : IGESAppli_LineWidening.cxx
//  Date      :
//  Author    : CKY / Contract Toubro-Larsen
//  Copyright : MATRA-DATAVISION 1993
//
//--------------------------------------------------------------------

#include <IGESAppli_ToolLineWidening.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_LevelListEntity.hxx>


IGESAppli_ToolLineWidening::IGESAppli_ToolLineWidening ()    {  }


void  IGESAppli_ToolLineWidening::ReadOwnParams
  (const Handle(IGESAppli_LineWidening)& ent,
   const Handle(IGESData_IGESReaderData)& /*IR*/, IGESData_ParamReader& PR) const
{
  Standard_Integer tempNbPropertyValues;
  Standard_Real tempWidth;
  Standard_Integer tempCorneringCode;
  Standard_Integer tempExtensionFlag;
  Standard_Integer tempJustificationFlag;
  Standard_Real tempExtensionValue = 0.0;
  //Standard_Boolean st; //szv#4:S4163:12Mar99 not needed

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadInteger(PR.Current(),"No. of Property values",tempNbPropertyValues);
  PR.ReadReal(PR.Current(),"Width of metalization",tempWidth);
  PR.ReadInteger(PR.Current(),"Cornering code",tempCorneringCode);
  PR.ReadInteger(PR.Current(),"Extension Flag",tempExtensionFlag);
  PR.ReadInteger(PR.Current(),"Justification Flag",tempJustificationFlag);
  if (PR.IsParamDefined(PR.CurrentNumber()))
    PR.ReadReal(PR.Current(),"Extension value",tempExtensionValue);
  else if (tempExtensionFlag == 2)
    PR.AddFail("Extension Value not defined while Extension Flag = 2");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init(tempNbPropertyValues,tempWidth,tempCorneringCode,tempExtensionFlag,
	    tempJustificationFlag,tempExtensionValue);
}

void  IGESAppli_ToolLineWidening::WriteOwnParams
  (const Handle(IGESAppli_LineWidening)& ent, IGESData_IGESWriter& IW) const
{
  IW.Send(ent->NbPropertyValues());
  IW.Send(ent->WidthOfMetalization());
  IW.Send(ent->CorneringCode());
  IW.Send(ent->ExtensionFlag());
  IW.Send(ent->JustificationFlag());
  IW.Send(ent->ExtensionValue());
}

void  IGESAppli_ToolLineWidening::OwnShared
  (const Handle(IGESAppli_LineWidening)& /*ent*/, Interface_EntityIterator& /*iter*/) const
{
}

void  IGESAppli_ToolLineWidening::OwnCopy
  (const Handle(IGESAppli_LineWidening)& another,
   const Handle(IGESAppli_LineWidening)& ent, Interface_CopyTool& /*TC*/) const
{
  ent->Init
    (5,another->WidthOfMetalization(),another->CorneringCode(),
     another->ExtensionFlag(),another->JustificationFlag(),
     another->ExtensionValue());
}

Standard_Boolean  IGESAppli_ToolLineWidening::OwnCorrect
  (const Handle(IGESAppli_LineWidening)& ent) const
{
  Standard_Boolean res = (ent->NbPropertyValues() != 5);
  if (res) ent->Init
    (5,ent->WidthOfMetalization(),ent->CorneringCode(),ent->ExtensionFlag(),
     ent->JustificationFlag(),ent->ExtensionValue());
  if (ent->SubordinateStatus() != 0) {
    Handle(IGESData_LevelListEntity) nulevel;
    ent->InitLevel(nulevel,0);
    res = Standard_True;
  }
  return res;    // nbpropertyvalues = 5 + RAZ level selon subordinate
}

IGESData_DirChecker  IGESAppli_ToolLineWidening::DirChecker
  (const Handle(IGESAppli_LineWidening)& /*ent*/ ) const
{
  IGESData_DirChecker DC(406,5);  //Form no = 5 & Type = 406
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.BlankStatusIgnored();
  DC.UseFlagIgnored();
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESAppli_ToolLineWidening::OwnCheck
  (const Handle(IGESAppli_LineWidening)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->SubordinateStatus() != 0)
    if (ent->DefLevel() == IGESData_DefOne ||
	ent->DefLevel() == IGESData_DefSeveral)
      ach->AddWarning("Level type: defined while ignored");
  if (ent->NbPropertyValues() != 5)
    ach->AddFail("Number of Property Values != 5");
  if (ent->CorneringCode() != 0 && ent->CorneringCode() != 1)
    ach->AddFail("Cornering Code incorrect");
  if (ent->ExtensionFlag() < 0 || ent->ExtensionFlag() > 2)
    ach->AddFail("Extension Flag value incorrect");
  if (ent->JustificationFlag() < 0 || ent->JustificationFlag() > 2)
    ach->AddFail("Justification Flag value incorrect");
}

void  IGESAppli_ToolLineWidening::OwnDump
  (const Handle(IGESAppli_LineWidening)& ent, const IGESData_IGESDumper& /*dumper*/,
   const Handle(Message_Messenger)& S, const Standard_Integer /*level*/) const
{
  S << "IGESAppli_LineWidening" << endl;

  S << "Number of property values : " << ent->NbPropertyValues()     << endl;
  S << "Width of metalization : " << ent->WidthOfMetalization()      << endl;
  S << "Cornering Code : " ;
  if      (ent->CorneringCode() == 0) S << "0 (rounded)" << endl;
  else if (ent->CorneringCode() == 1) S << "1 (squared)" << endl;
  else                                S << "incorrect value" << endl;

  S << "Extension Flag : " ;
  if      (ent->ExtensionFlag() == 0) S << "0 (No Extension)" << endl;
  else if (ent->ExtensionFlag() == 1) S << "1 (One-half width extension)" << endl;
  else if (ent->ExtensionFlag() == 2) S << "2 (Extension set by ExtensionValue)" << endl;
  else    S << "incorrect value" << endl;

  S << "Justification Flag : " ;
  if (ent->JustificationFlag() == 0)
    S << "0 (Centre justified)" << endl;
  else if (ent->JustificationFlag() == 1)
    S << "1 (left justified)" << endl;
  else if (ent->JustificationFlag() == 2)
    S << "2 (right justified)" << endl;
  else
    S << "incorrect value" << endl;

  if (ent->ExtensionFlag() == 2)
    S << "Extension Value : " << ent->ExtensionValue()  << endl;
  else
    S << "No Extension Value (Extension Flag != 2)" << endl;
}

