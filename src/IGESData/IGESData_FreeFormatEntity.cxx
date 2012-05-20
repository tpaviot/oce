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

#include <IGESData_FreeFormatEntity.ixx>
#include <Interface_UndefinedContent.hxx>
#include <Interface_InterfaceError.hxx>
#include <IGESData_IGESEntity.hxx>
#include <TCollection_HAsciiString.hxx>
#include <Interface_Macros.hxx>



//  Donne un acces simple a la constitution d une UndefinedEntity :
//  Methodes de UndefinedContent, + Type & Form, + AddEntities (little gadget)


IGESData_FreeFormatEntity::IGESData_FreeFormatEntity ()    {  }

    void  IGESData_FreeFormatEntity::SetTypeNumber
  (const Standard_Integer typenum)
{  InitTypeAndForm (typenum,0);  }

    void  IGESData_FreeFormatEntity::SetFormNumber
  (const Standard_Integer formnum)
{  InitTypeAndForm (TypeNumber(), formnum);  }


    Standard_Integer  IGESData_FreeFormatEntity::NbParams () const 
{  return UndefinedContent()->NbParams();  }

    Standard_Boolean  IGESData_FreeFormatEntity::ParamData
  (const Standard_Integer num, Interface_ParamType& ptype,
   Handle(IGESData_IGESEntity)& ent, Handle(TCollection_HAsciiString)& val) const 
{  return UndefinedContent()->ParamData (num,ptype,ent,val);  }


    Interface_ParamType  IGESData_FreeFormatEntity::ParamType
  (const Standard_Integer num) const 
{  return UndefinedContent()->ParamType(num);  }

    Standard_Boolean  IGESData_FreeFormatEntity::IsParamEntity
  (const Standard_Integer num) const 
{  return UndefinedContent()->IsParamEntity(num);  }

    Handle(IGESData_IGESEntity)  IGESData_FreeFormatEntity::ParamEntity
  (const Standard_Integer num) const
{
  return Handle(IGESData_IGESEntity)::DownCast
    (UndefinedContent()->ParamEntity(num));
}

    Standard_Boolean  IGESData_FreeFormatEntity::IsNegativePointer
  (const Standard_Integer num) const
{
  if (thenegptrs.IsNull()) return Standard_False;
  Standard_Integer nb = thenegptrs->Length();
  for (Standard_Integer i = 1; i <= nb; i ++)
    if (thenegptrs->Value(i) == num) return Standard_True;
  return Standard_False;
}

    Handle(TCollection_HAsciiString)  IGESData_FreeFormatEntity::ParamValue
  (const Standard_Integer num) const 
{  return UndefinedContent()->ParamValue(num);  }

    Handle(TColStd_HSequenceOfInteger)  IGESData_FreeFormatEntity::NegativePointers () const
      {  return thenegptrs;  }


    void  IGESData_FreeFormatEntity::AddLiteral
  (const Interface_ParamType ptype, const Handle(TCollection_HAsciiString)& val)
{  UndefinedContent()->AddLiteral (ptype,val);  }

    void  IGESData_FreeFormatEntity::AddLiteral
  (const Interface_ParamType ptype, const Standard_CString val)
{  UndefinedContent()->AddLiteral (ptype,new TCollection_HAsciiString(val));  }

    void  IGESData_FreeFormatEntity::AddEntity
  (const Interface_ParamType ptype,
   const Handle(IGESData_IGESEntity)& ent, const Standard_Boolean negative)
{
  UndefinedContent()->AddEntity (ptype,ent);
  if (!negative) return;
  if (thenegptrs.IsNull()) thenegptrs = new TColStd_HSequenceOfInteger();
  thenegptrs->Append(NbParams());
}

    void  IGESData_FreeFormatEntity::AddEntities
  (const Handle(IGESData_HArray1OfIGESEntity)& ents)
{
  if (ents.IsNull()) {
    AddLiteral ( Interface_ParamInteger, new TCollection_HAsciiString("0") );
    return;
  }
  AddLiteral ( Interface_ParamInteger, new TCollection_HAsciiString(ents->Length()) );
  Standard_Integer iup = ents->Upper();
  for (Standard_Integer i = ents->Lower(); i <= iup; i ++) {
    AddEntity (Interface_ParamIdent,ents->Value(i));
  }
}

    
    void  IGESData_FreeFormatEntity::AddNegativePointers
  (const Handle(TColStd_HSequenceOfInteger)& list)
{
  if (thenegptrs.IsNull()) thenegptrs = new TColStd_HSequenceOfInteger();
  thenegptrs->Append(list);
}

    void  IGESData_FreeFormatEntity::ClearNegativePointers ()
      {  thenegptrs.Nullify();  }


    void IGESData_FreeFormatEntity::WriteOwnParams
  (IGESData_IGESWriter& IW) const
{
//  Redefini de UndefinedEntity pour : NegativePointers
  Standard_Integer neg  = 0;
  Standard_Integer fneg = 0;
  if (!thenegptrs.IsNull())
    if (!thenegptrs->IsEmpty())  {  neg = thenegptrs->Value(1);  fneg = 1;  }

  Standard_Integer nb = UndefinedContent()->NbParams();
  for (Standard_Integer i = 1; i <= nb; i ++) {
    Interface_ParamType ptyp = UndefinedContent()->ParamType(i);
    if (ptyp == Interface_ParamVoid) IW.SendVoid();
    else if (UndefinedContent()->IsParamEntity(i)) {
      DeclareAndCast(IGESData_IGESEntity,anent,UndefinedContent()->ParamEntity(i));
//  Send Entity : Redefini
      if (i == neg) {
	IW.Send(anent,Standard_True);
	if (fneg >= thenegptrs->Length()) neg = 0;
	else  {  fneg ++;  neg = thenegptrs->Value(fneg);  }
      }
      else IW.Send(anent,Standard_False);
    }
    else IW.SendString (UndefinedContent()->ParamValue(i));
  }
}
