#ifndef _ShapeSchema_PTopoDS_TSolid_HeaderFile
#include <ShapeSchema_PTopoDS_TSolid.hxx>
#endif
#ifndef _PTopoDS_TSolid_HeaderFile
#include <PTopoDS_TSolid.hxx>
#endif
#include <ShapeSchema_PTopoDS_TSolid.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_TSolid,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_TSolid,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_TSolid::New() const
{
  return new PTopoDS_TSolid(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopoDS_TSolid::SAdd(const Handle(PTopoDS_TSolid)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_TSolid")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());

    }
  }
}

void ShapeSchema_PTopoDS_TSolid::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_TSolid::SAdd((Handle(PTopoDS_TSolid)&)p,theSchema);
}

void ShapeSchema_PTopoDS_TSolid::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TSolid) &pp = (Handle(PTopoDS_TSolid)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TSolid::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_TSolid::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_TSolid::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TSolid) &pp = (Handle(PTopoDS_TSolid)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfHShape) PTopoDS_TShapemyShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShapemyShapes,f);
    pp->_CSFDB_SetPTopoDS_TShapemyShapes(PTopoDS_TShapemyShapes);

    Standard_Integer PTopoDS_TShapemyFlags;
    f.GetInteger(PTopoDS_TShapemyFlags);
    pp->_CSFDB_SetPTopoDS_TShapemyFlags(PTopoDS_TShapemyFlags);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TSolid::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_TSolid::SRead(p,f,theSchema);
}
