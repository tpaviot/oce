#ifndef _ShapeSchema_PTopoDS_TVertex_HeaderFile
#include <ShapeSchema_PTopoDS_TVertex.hxx>
#endif
#ifndef _PTopoDS_TVertex_HeaderFile
#include <PTopoDS_TVertex.hxx>
#endif
#include <ShapeSchema_PTopoDS_TVertex.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_TVertex,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_TVertex,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_TVertex::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PTopoDS_TVertex::SAdd(const Handle(PTopoDS_TVertex)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_TVertex")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());

    }
  }
}

void ShapeSchema_PTopoDS_TVertex::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_TVertex::SAdd((Handle(PTopoDS_TVertex)&)p,theSchema);
}

void ShapeSchema_PTopoDS_TVertex::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TVertex) &pp = (Handle(PTopoDS_TVertex)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TVertex::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_TVertex::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_TVertex::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TVertex) &pp = (Handle(PTopoDS_TVertex)&)p;

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

void ShapeSchema_PTopoDS_TVertex::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_TVertex::SRead(p,f,theSchema);
}
