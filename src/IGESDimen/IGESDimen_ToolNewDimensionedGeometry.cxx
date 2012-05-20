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

#include <IGESDimen_ToolNewDimensionedGeometry.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <gp_XYZ.hxx>
#include <gp_Pnt.hxx>
#include <TColgp_HArray1OfXYZ.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <IGESData_TransfEntity.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESDimen_ToolNewDimensionedGeometry::IGESDimen_ToolNewDimensionedGeometry ()
      {  }


void  IGESDimen_ToolNewDimensionedGeometry::ReadOwnParams
  (const Handle(IGESDimen_NewDimensionedGeometry)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down
  Standard_Integer i, num;
  Standard_Integer tempNbDimens;
  Standard_Integer tempDimOrientFlag;
  Standard_Real tempAngle;
  Handle(IGESData_IGESEntity) tempDimen;
  Handle(IGESData_HArray1OfIGESEntity) tempGeomEnts;
  Handle(TColStd_HArray1OfInteger) tempDimLocFlags;
  Handle(TColgp_HArray1OfXYZ) tempPoints;

  if (PR.DefinedElseSkip())
    PR.ReadInteger(PR.Current(), "Number of Dimensions", tempNbDimens); //szv#4:S4163:12Mar99 `st=` not needed
  else
    tempNbDimens = 1;

  Standard_Boolean st = PR.ReadInteger(PR.Current(), "Number of Geometries", num);
  if (st && num > 0)
    {
      tempGeomEnts    = new IGESData_HArray1OfIGESEntity(1, num);
      tempDimLocFlags = new TColStd_HArray1OfInteger(1, num);
      tempPoints      = new TColgp_HArray1OfXYZ(1, num);
    }
  else  PR.AddFail("Number of Geometries: Not Positive");

  //szv#4:S4163:12Mar99 `st=` not needed
  PR.ReadEntity(IR, PR.Current(), "Dimension Entity", tempDimen);
  PR.ReadInteger(PR.Current(), "Dimension Orientation Flag", tempDimOrientFlag);
  PR.ReadReal(PR.Current(), "Angle Value", tempAngle);

  if (!tempGeomEnts.IsNull())
    for ( i = 1; i <= num; i++)
      {
	Handle(IGESData_IGESEntity) tempEnt;
	//szv#4:S4163:12Mar99 `st=` not needed
	PR.ReadEntity(IR, PR.Current(), "Geometry Entity", tempEnt, (i == num)); // The last one may be Null
	tempGeomEnts->SetValue(i, tempEnt);

	Standard_Integer tempInt;
	PR.ReadInteger(PR.Current(), "Dimension Location Flag", tempInt); //szv#4:S4163:12Mar99 `st=` not needed
	tempDimLocFlags->SetValue(i, tempInt);

	gp_XYZ tempPnt;
	PR.ReadXYZ(PR.CurrentList(1, 3), "Point", tempPnt); //szv#4:S4163:12Mar99 `st=` not needed
	tempPoints->SetValue(i, tempPnt);
      }

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init
    (tempNbDimens, tempDimen, tempDimOrientFlag, tempAngle,
     tempGeomEnts, tempDimLocFlags, tempPoints);
}

void  IGESDimen_ToolNewDimensionedGeometry::WriteOwnParams
  (const Handle(IGESDimen_NewDimensionedGeometry)& ent, IGESData_IGESWriter& IW) const
{
  Standard_Integer i, num;
  IW.Send(ent->NbDimensions());
  IW.Send(ent->NbGeometries());
  IW.Send(ent->DimensionEntity());
  IW.Send(ent->DimensionOrientationFlag());
  IW.Send(ent->AngleValue());
  for ( num = ent->NbGeometries(), i = 1; i <= num; i++ )
    {
      IW.Send(ent->GeometryEntity(i));
      IW.Send(ent->DimensionLocationFlag(i));
      IW.Send(ent->Point(i).X());
      IW.Send(ent->Point(i).Y());
      IW.Send(ent->Point(i).Z());
    }
}

void  IGESDimen_ToolNewDimensionedGeometry::OwnShared
  (const Handle(IGESDimen_NewDimensionedGeometry)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer i, num;
  iter.GetOneItem(ent->DimensionEntity());
  for ( num = ent->NbGeometries(), i = 1; i <= num; i++ )
    iter.GetOneItem(ent->GeometryEntity(i));
}

void  IGESDimen_ToolNewDimensionedGeometry::OwnCopy
  (const Handle(IGESDimen_NewDimensionedGeometry)& another,
   const Handle(IGESDimen_NewDimensionedGeometry)& ent, Interface_CopyTool& TC) const
{
  Standard_Integer num = another->NbGeometries();
  Standard_Integer tempNbDimens = another->NbDimensions();
  Standard_Integer tempDimOrientFlag = another->DimensionOrientationFlag();
  Standard_Real tempAngle = another->AngleValue();
  DeclareAndCast(IGESData_IGESEntity, tempDimen,
		 TC.Transferred(another->DimensionEntity()));

  Handle(IGESData_HArray1OfIGESEntity) tempGeomEnts =
    new IGESData_HArray1OfIGESEntity(1, num);
  Handle(TColStd_HArray1OfInteger) tempDimLocFlags =
    new TColStd_HArray1OfInteger(1, num);
  Handle(TColgp_HArray1OfXYZ) tempPoints = new TColgp_HArray1OfXYZ(1, num);

  for (Standard_Integer i = 1; i <= num; i++)
    {
      DeclareAndCast(IGESData_IGESEntity, tempEnt,
		     TC.Transferred(another->GeometryEntity(i)));
      tempGeomEnts->SetValue(i, tempEnt);
      tempDimLocFlags->SetValue(i, another->DimensionLocationFlag(i));
      tempPoints->SetValue(i, another->Point(i).XYZ());
    }
  ent->Init (tempNbDimens, tempDimen, tempDimOrientFlag, tempAngle,
	     tempGeomEnts, tempDimLocFlags, tempPoints);
}

Standard_Boolean  IGESDimen_ToolNewDimensionedGeometry::OwnCorrect
  (const Handle(IGESDimen_NewDimensionedGeometry)& ent) const
{
  Standard_Boolean res = ent->HasTransf();
  if (res) {
    Handle(IGESData_TransfEntity) nultransf;
    ent->InitTransf(nultransf);
  }
  if (ent->NbDimensions() == 1) return res;
//   Forcer NbDimensions = 1 -> reconstruire
  Standard_Integer nb = ent->NbGeometries();
  Handle(IGESData_HArray1OfIGESEntity) tempGeomEnts =
    new IGESData_HArray1OfIGESEntity(1, nb);
  Handle(TColStd_HArray1OfInteger) tempDimLocFlags =
    new TColStd_HArray1OfInteger(1, nb);
  Handle(TColgp_HArray1OfXYZ) tempPoints = new TColgp_HArray1OfXYZ (1,nb);

  for (Standard_Integer i = 1; i <= nb; i ++) {
    tempGeomEnts->SetValue(i, ent->GeometryEntity(i));
    tempDimLocFlags->SetValue(i, ent->DimensionLocationFlag(i));
    tempPoints->SetValue(i, ent->Point(i).XYZ());
  }
  ent->Init (1,ent->DimensionEntity(),ent->DimensionOrientationFlag(),
	     ent->AngleValue(), tempGeomEnts, tempDimLocFlags, tempPoints);
  return Standard_True;
}

IGESData_DirChecker  IGESDimen_ToolNewDimensionedGeometry::DirChecker
  (const Handle(IGESDimen_NewDimensionedGeometry)& /* ent */ ) const
{
  IGESData_DirChecker DC(402, 21);
  DC.Structure(IGESData_DefVoid);
  DC.GraphicsIgnored();
  DC.LineFont(IGESData_DefVoid);
  DC.LineWeight(IGESData_DefVoid);
  DC.Color(IGESData_DefVoid);
  DC.BlankStatusIgnored();
  DC.SubordinateStatusRequired(1);
  DC.UseFlagRequired(2);
  DC.HierarchyStatusIgnored();
  return DC;
}

void  IGESDimen_ToolNewDimensionedGeometry::OwnCheck
  (const Handle(IGESDimen_NewDimensionedGeometry)& ent,
   const Interface_ShareTool& , Handle(Interface_Check)& ach) const
{
  if (ent->NbDimensions() != 1)
    ach->AddFail("Number of Dimensions != 1");
  if (ent->HasTransf())
    ach->AddWarning("Transformation Matrix exists, ignored");
}

void  IGESDimen_ToolNewDimensionedGeometry::OwnDump
  (const Handle(IGESDimen_NewDimensionedGeometry)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
  Standard_Integer i, num, sublevel = (level > 4) ? 1 : 0;
  S << "IGESDimen_NewDimensionedGeometry" << endl;
  S << "Number of Dimensions : " << ent->NbDimensions() << endl;
  S << "Dimension Entity : ";
  dumper.Dump(ent->DimensionEntity(),S, sublevel);
  S << endl;
  S << "Dimension Orientation Flag : " << ent->DimensionOrientationFlag() << endl;
  S << "Angle Value Flag : " << ent->AngleValue() << endl;
  S << "Geometry Entities : " << endl;
  S << "Dimension Location Flags : " << endl;
  S << "Points : ";
  IGESData_DumpEntities(S,dumper,-level,1, ent->NbGeometries(),ent->GeometryEntity);
  S << endl;
  if (level > 4)
    for ( num = ent->NbGeometries(), i = 1; i <= num; i++ )
      {
	S << "[" << i << "]: " << endl;
	S << "Geometry Entity : ";
	dumper.Dump (ent->GeometryEntity(i),S, 1);
	S << endl;
	S << "Dimension Location Flag : " << ent->DimensionLocationFlag(i) << endl;
	S << "Point : ";
	IGESData_DumpXYZL(S,level, ent->Point(i), ent->Location());
      }
  S << endl;
}
