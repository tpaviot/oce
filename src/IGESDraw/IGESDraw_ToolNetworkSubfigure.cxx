// Created by: CKY / Contract Toubro-Larsen
// Copyright (c) 1993-1999 Matra Datavision
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

//--------------------------------------------------------------------
//--------------------------------------------------------------------

#include <IGESDraw_ToolNetworkSubfigure.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESDraw_ConnectPoint.hxx>
#include <gp_XYZ.hxx>
#include <IGESDraw_HArray1OfConnectPoint.hxx>
#include <IGESGraph_TextDisplayTemplate.hxx>
#include <TCollection_HAsciiString.hxx>
#include <IGESDraw_NetworkSubfigureDef.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDraw_ToolNetworkSubfigure::IGESDraw_ToolNetworkSubfigure ()    {  }


void IGESDraw_ToolNetworkSubfigure::ReadOwnParams
  (const Handle(IGESDraw_NetworkSubfigure)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean                           st; //szv#4:S4163:12Mar99 not needed
  Standard_Integer                           nbval;

  Handle(IGESDraw_NetworkSubfigureDef)       definition; 
  gp_XYZ                                     translation;
  gp_XYZ                                     scale;
  Standard_Integer                           typeflag; 
  Handle(TCollection_HAsciiString)           designator; 
  Handle(IGESGraph_TextDisplayTemplate)      textTemplate; 
  Handle(IGESDraw_HArray1OfConnectPoint) connectPoints;

  Standard_Real                              scaleX; 
  Standard_Real                              scaleY; 
  Standard_Real                              scaleZ; 

  // Reading definition(Instance of NetworkSubfigureDef)
  PR.ReadEntity(IR, PR.Current(), "Instance of NetworkSubfigureDef",
		STANDARD_TYPE(IGESDraw_NetworkSubfigureDef), definition); //szv#4:S4163:12Mar99 `st=` not needed

  // Reading translation(XYZ)
  PR.ReadXYZ( PR.CurrentList(1, 3), "Translation data", translation); //szv#4:S4163:12Mar99 `st=` not needed

  // Reading scale(XYZ)
  if (PR.DefinedElseSkip())        // Reading scale(X)
    PR.ReadReal(PR.Current(), "Scale factors(X)", scaleX); //szv#4:S4163:12Mar99 `st=` not needed
  else
    scaleX = 1.0; // Default Value

  if (PR.DefinedElseSkip())        // Reading scale(Y)
    PR.ReadReal(PR.Current(), "Scale factors(Y)", scaleY); //szv#4:S4163:12Mar99 `st=` not needed
  else
    scaleY = scaleX; // Default Value

  if (PR.DefinedElseSkip())        // Reading scale(Z)
    PR.ReadReal(PR.Current(), "Scale factors(Z)", scaleZ); //szv#4:S4163:12Mar99 `st=` not needed
  else
    scaleZ = scaleX; // Default Value

  scale.SetCoord(scaleX, scaleY, scaleZ);

  if (PR.DefinedElseSkip())       // Reading typeflag(Integer)
    PR.ReadInteger(PR.Current(), "Type flag", typeflag); //szv#4:S4163:12Mar99 `st=` not needed
  else
    typeflag = 0; // Default Value

  // Reading designator(String)
  if (PR.DefinedElseSkip())
    PR.ReadText(PR.Current(), "Primary reference designator", designator); //szv#4:S4163:12Mar99 `st=` not needed
  else PR.AddWarning("Primary reference designator : Null definition");

  // Reading textTemplate(Instance of TextDisplayTemplate or Null)
  Standard_Boolean st = PR.ReadEntity(IR, PR.Current(), "Instance of TextDisplayTemplate",
				      STANDARD_TYPE(IGESGraph_TextDisplayTemplate), textTemplate,
				      Standard_True);

  // Reading nbval(Integer)
  if (PR.DefinedElseSkip()) 
    st = PR.ReadInteger(PR.Current(),"Count of Connect Points", nbval); //szv#4:S4163:12Mar99 `st=` not needed
  else nbval = 0;
  if (st && nbval > 0)
    {
      // Reading connectPoints(HArray1OfConnectPoint)
      connectPoints = new IGESDraw_HArray1OfConnectPoint(1, nbval);
      Handle(IGESDraw_ConnectPoint) tempConnectPoint;
      for (Standard_Integer i = 1; i <= nbval; i++)
	{
	  //st = PR.ReadEntity(IR, PR.Current(), "ConnectPoint entity",
			       //STANDARD_TYPE(IGESDraw_ConnectPoint),tempConnectPoint,
			       //Standard_True); //szv#4:S4163:12Mar99 moved in if
	  if (PR.ReadEntity(IR, PR.Current(), "ConnectPoint entity",
			    STANDARD_TYPE(IGESDraw_ConnectPoint),tempConnectPoint, Standard_True))
	  connectPoints->SetValue(i, tempConnectPoint);
	}
    }
  else if (nbval < 0)
    PR.AddFail ("Count of Connect point entities : Less than Zero");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init
    (definition, translation, scale, typeflag,
     designator, textTemplate, connectPoints);
}

void IGESDraw_ToolNetworkSubfigure::WriteOwnParams
  (const Handle(IGESDraw_NetworkSubfigure)& ent, IGESData_IGESWriter& IW)  const
{
  IW.Send( ent->SubfigureDefinition() );
  IW.Send( ent->Translation().X() );
  IW.Send( ent->Translation().Y() );
  IW.Send( ent->Translation().Z() );
  IW.Send( ent->ScaleFactors().X() );
  IW.Send( ent->ScaleFactors().Y() );
  IW.Send( ent->ScaleFactors().Z() );
  IW.Send( ent->TypeFlag() );
  IW.Send( ent->ReferenceDesignator() );

  IW.Send( ent->DesignatorTemplate() );

  IW.Send( ent->NbConnectPoints() );

  Standard_Integer Up  = ent->NbConnectPoints();
  for ( Standard_Integer i = 1; i <= Up; i++)
    IW.Send( ent->ConnectPoint(i) );
}

void  IGESDraw_ToolNetworkSubfigure::OwnShared
  (const Handle(IGESDraw_NetworkSubfigure)& ent, Interface_EntityIterator& iter) const
{
  iter.GetOneItem( ent->SubfigureDefinition() );
  iter.GetOneItem( ent->DesignatorTemplate() );
  Standard_Integer Up  = ent->NbConnectPoints();
  for ( Standard_Integer i = 1; i <= Up; i++)
    iter.GetOneItem( ent->ConnectPoint(i) );
}

void IGESDraw_ToolNetworkSubfigure::OwnCopy
  (const Handle(IGESDraw_NetworkSubfigure)& another,
   const Handle(IGESDraw_NetworkSubfigure)& ent, Interface_CopyTool& TC) const
{
  Standard_Integer                       nbval;
  gp_XYZ                                 translation;
  gp_XYZ                                 scale;
  Standard_Integer                       typeflag; 
  Handle(TCollection_HAsciiString)       designator; 
  Handle(IGESDraw_HArray1OfConnectPoint) connectPoints;
 
  nbval         = another->NbConnectPoints();

  DeclareAndCast(IGESDraw_NetworkSubfigureDef, definition, 
                 TC.Transferred(another->SubfigureDefinition()));

  translation   = another->Translation();
  scale         = another->ScaleFactors();
  typeflag      = another->TypeFlag();
  if (!another->ReferenceDesignator().IsNull())
    designator  = new TCollection_HAsciiString
      (another->ReferenceDesignator());

  DeclareAndCast(IGESGraph_TextDisplayTemplate, textTemplate, 
                 TC.Transferred(another->DesignatorTemplate()));

  if (nbval > 0) connectPoints = new IGESDraw_HArray1OfConnectPoint(1, nbval);
  for (Standard_Integer i = 1; i <= nbval; i++)
    {
      DeclareAndCast(IGESDraw_ConnectPoint, tempconnectPoint, 
                     TC.Transferred(another->ConnectPoint(i)) );
      connectPoints->SetValue( i, tempconnectPoint );
    }

  ent->Init(definition, translation, scale, typeflag,
	    designator, textTemplate, connectPoints);
}

IGESData_DirChecker IGESDraw_ToolNetworkSubfigure::DirChecker
  (const Handle(IGESDraw_NetworkSubfigure)& /*ent*/)  const
{ 
  IGESData_DirChecker DC (420, 0);
  DC.Structure(IGESData_DefVoid);
  DC.LineFont(IGESData_DefAny);
  DC.LineWeight(IGESData_DefValue);
  DC.Color(IGESData_DefAny);
  return DC;
}

void IGESDraw_ToolNetworkSubfigure::OwnCheck
  (const Handle(IGESDraw_NetworkSubfigure)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach)  const
{
  if ( ent->TypeFlag() != 0 &&
      ent->TypeFlag() != 1 &&
      ent->TypeFlag() != 2 )
    ach->AddFail("Type Flag : Value != 0/1/2");
  if (ent->NbConnectPoints() != ent->SubfigureDefinition()->NbPointEntities())
    ach->AddFail("Count of associated Connect Points inconsistent with Definition");
  if (ent->ReferenceDesignator().IsNull())
    ach->AddFail("Primary Reference Designator : not defined");
}

void IGESDraw_ToolNetworkSubfigure::OwnDump
  (const Handle(IGESDraw_NetworkSubfigure)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level)  const
{
  Standard_Integer sublevel = (level <= 4) ? 0 : 1;

  S << "IGESDraw_NetworkSubfigure" << endl;

  S << "Network Subfigure Definition Entity : ";
  dumper.Dump(ent->SubfigureDefinition(),S, sublevel);
  S << endl << "Translation Data : ";
  IGESData_DumpXYZL(S,level, ent->Translation(), ent->Location());
  S << endl << "Scale Factors    : ";
  IGESData_DumpXYZ(S, ent->ScaleFactors());
  S << endl << "Type Flag : " << ent->TypeFlag() << endl;
  S << "Primary Reference Designator : ";
  IGESData_DumpString(S,ent->ReferenceDesignator());
  S << endl << "Text Display Template Entity : ";
  dumper.Dump(ent->DesignatorTemplate(),S, sublevel);
  S << endl << "Connect Points  : ";
  IGESData_DumpEntities(S,dumper ,level,1, ent->NbConnectPoints(),ent->ConnectPoint);
  S << endl;
}
