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

#include <IGESSolid_ToolSolidAssembly.ixx>
#include <IGESData_ParamCursor.hxx>
#include <IGESData_IGESEntity.hxx>
#include <IGESGeom_TransformationMatrix.hxx>
#include <IGESData_HArray1OfIGESEntity.hxx>
#include <IGESGeom_HArray1OfTransformationMatrix.hxx>
#include <IGESData_Dump.hxx>
#include <Interface_Macros.hxx>


IGESSolid_ToolSolidAssembly::IGESSolid_ToolSolidAssembly ()    {  }


void  IGESSolid_ToolSolidAssembly::ReadOwnParams
  (const Handle(IGESSolid_SolidAssembly)& ent,
   const Handle(IGESData_IGESReaderData)& IR, IGESData_ParamReader& PR) const
{
  //Standard_Boolean st; //szv#4:S4163:12Mar99 moved down
  Standard_Integer nbitems; //szv#4:S4163:12Mar99 `i` moved in for
  //Handle(IGESData_IGESEntity) anent; //szv#4:S4163:12Mar99 moved down
  //Handle(IGESGeom_TransformationMatrix) amatr; //szv#4:S4163:12Mar99 moved down
  Handle(IGESData_HArray1OfIGESEntity) tempItems;
  Handle(IGESGeom_HArray1OfTransformationMatrix) tempMatrices;

  Standard_Boolean st = PR.ReadInteger(PR.Current(), "Number of Items", nbitems);
  if (st && nbitems > 0)
    {
      tempItems = new IGESData_HArray1OfIGESEntity(1, nbitems);
      tempMatrices = new IGESGeom_HArray1OfTransformationMatrix(1, nbitems);

      Handle(IGESData_IGESEntity) anent;
      Standard_Integer i; // svv Jan 10 2000 : porting on DEC
      for (i = 1; i <= nbitems; i++)
	{
          //st = PR.ReadEntity(IR,PR.Current(), "Solid assembly items", anent); //szv#4:S4163:12Mar99 moved in if
	  if (PR.ReadEntity(IR,PR.Current(), "Solid assembly items", anent))
	    tempItems->SetValue(i, anent);
	}

      Handle(IGESGeom_TransformationMatrix) amatr;
      for (i = 1; i <= nbitems; i++)
	{
          //st = PR.ReadEntity(IR,PR.Current(), "Matrices",
			     //STANDARD_TYPE(IGESGeom_TransformationMatrix),
			     //amatr, Standard_True); //szv#4:S4163:12Mar99 moved in if
          if (PR.ReadEntity(IR,PR.Current(), "Matrices",
			    STANDARD_TYPE(IGESGeom_TransformationMatrix), amatr, Standard_True))
	    tempMatrices->SetValue(i, amatr);
	}
    }
  else  PR.AddFail("Number of Items : Not Positive");

  DirChecker(ent).CheckTypeAndForm(PR.CCheck(),ent);
  ent->Init (tempItems, tempMatrices);
}

void  IGESSolid_ToolSolidAssembly::WriteOwnParams
  (const Handle(IGESSolid_SolidAssembly)& ent, IGESData_IGESWriter& IW) const
{
  Standard_Integer nbitems = ent->NbItems();
  Standard_Integer i;

  IW.Send(nbitems);
  for (i = 1; i <= nbitems; i ++)
    IW.Send(ent->Item(i));
  for (i = 1; i <= nbitems; i ++)
    IW.Send(ent->TransfMatrix(i));
}

void  IGESSolid_ToolSolidAssembly::OwnShared
  (const Handle(IGESSolid_SolidAssembly)& ent, Interface_EntityIterator& iter) const
{
  Standard_Integer nbitems = ent->NbItems();
  Standard_Integer i;
  for (i = 1; i <= nbitems; i ++)    iter.GetOneItem(ent->Item(i));
  for (i = 1; i <= nbitems; i ++)    iter.GetOneItem(ent->TransfMatrix(i));
}

void  IGESSolid_ToolSolidAssembly::OwnCopy
  (const Handle(IGESSolid_SolidAssembly)& another,
   const Handle(IGESSolid_SolidAssembly)& ent, Interface_CopyTool& TC) const
{
  Standard_Integer nbitems, i;
  Handle(IGESData_IGESEntity) anent;

  nbitems = another->NbItems();
  Handle(IGESData_HArray1OfIGESEntity) tempItems = new
    IGESData_HArray1OfIGESEntity(1, nbitems);
  Handle(IGESGeom_HArray1OfTransformationMatrix) tempMatrices = new
    IGESGeom_HArray1OfTransformationMatrix(1, nbitems);

  for (i=1; i<=nbitems; i++)
    {
      DeclareAndCast(IGESData_IGESEntity, localent,
		     TC.Transferred(another->Item(i)));
      tempItems->SetValue(i, localent);
    }
  for (i=1; i<=nbitems; i++)
    {
      DeclareAndCast(IGESGeom_TransformationMatrix, newlocalent,
		     TC.Transferred(another->TransfMatrix(i)));
      tempMatrices->SetValue(i, newlocalent);
    }

  ent->Init(tempItems, tempMatrices);
}

IGESData_DirChecker  IGESSolid_ToolSolidAssembly::DirChecker
  (const Handle(IGESSolid_SolidAssembly)& /* ent */ ) const
{
  IGESData_DirChecker DC(184, 0,1);

  DC.Structure  (IGESData_DefVoid);
  DC.LineFont   (IGESData_DefAny);
  DC.Color      (IGESData_DefAny);

  DC.UseFlagRequired (2);
  DC.GraphicsIgnored (1);
  return DC;
}

void  IGESSolid_ToolSolidAssembly::OwnCheck
  (const Handle(IGESSolid_SolidAssembly)& /* ent */,
   const Interface_ShareTool& , Handle(Interface_Check)& /* ach */) const
{
}

void  IGESSolid_ToolSolidAssembly::OwnDump
  (const Handle(IGESSolid_SolidAssembly)& ent, const IGESData_IGESDumper& dumper,
   const Handle(Message_Messenger)& S, const Standard_Integer level) const
{
//  Standard_Integer upper = ent->NbItems();

  S << "IGESSolid_SolidAssembly" << endl;

  S << "Items : ";
  IGESData_DumpEntities(S,dumper ,level,1, ent->NbItems(),ent->Item);
  S << endl;
  S << "Matrices : ";
  IGESData_DumpEntities(S,dumper ,level,1, ent->NbItems(),ent->TransfMatrix);
  S << endl;
}
