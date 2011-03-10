#ifndef _ShapeSchema_PTopoDS_TFace_HeaderFile
#include <ShapeSchema_PTopoDS_TFace.hxx>
#endif
#ifndef _PTopoDS_TFace_HeaderFile
#include <PTopoDS_TFace.hxx>
#endif
#include <ShapeSchema_PTopoDS_TFace.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_TFace,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_TFace,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_TFace::New() const
{
  return new PTopoDS_TFace(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopoDS_TFace::SAdd(const Handle(PTopoDS_TFace)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_TFace")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());

    }
  }
}

void ShapeSchema_PTopoDS_TFace::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_TFace::SAdd((Handle(PTopoDS_TFace)&)p,theSchema);
}

void ShapeSchema_PTopoDS_TFace::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TFace) &pp = (Handle(PTopoDS_TFace)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TFace::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_TFace::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_TFace::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TFace) &pp = (Handle(PTopoDS_TFace)&)p;

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

void ShapeSchema_PTopoDS_TFace::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_TFace::SRead(p,f,theSchema);
}
