#ifndef _StdSchema_PNaming_NamedShape_HeaderFile
#include <StdSchema_PNaming_NamedShape.hxx>
#endif
#ifndef _PNaming_NamedShape_HeaderFile
#include <PNaming_NamedShape.hxx>
#endif
#include <StdSchema_PNaming_NamedShape.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PNaming_NamedShape,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PNaming_NamedShape,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PNaming_NamedShape::New() const
{
  return new PNaming_NamedShape(Storage_stCONSTclCOM());
}

void StdSchema_PNaming_NamedShape::SAdd(const Handle(PNaming_NamedShape)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PNaming_NamedShape")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_NamedShapemyOldShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPNaming_NamedShapemyNewShapes());

    }
  }
}

void StdSchema_PNaming_NamedShape::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PNaming_NamedShape::SAdd((Handle(PNaming_NamedShape)&)p,theSchema);
}

void StdSchema_PNaming_NamedShape::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_NamedShape) &pp = (Handle(PNaming_NamedShape)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_NamedShapemyOldShapes(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPNaming_NamedShapemyNewShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPNaming_NamedShapemyShapeStatus());
  f.PutInteger(pp->_CSFDB_GetPNaming_NamedShapemyVersion());

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PNaming_NamedShape::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PNaming_NamedShape::SWrite(p,f,theSchema);
}


void StdSchema_PNaming_NamedShape::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PNaming_NamedShape) &pp = (Handle(PNaming_NamedShape)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfShape1) PNaming_NamedShapemyOldShapes;

    theSchema->ReadPersistentReference(PNaming_NamedShapemyOldShapes,f);
    pp->_CSFDB_SetPNaming_NamedShapemyOldShapes(PNaming_NamedShapemyOldShapes);

    Handle(PTopoDS_HArray1OfShape1) PNaming_NamedShapemyNewShapes;

    theSchema->ReadPersistentReference(PNaming_NamedShapemyNewShapes,f);
    pp->_CSFDB_SetPNaming_NamedShapemyNewShapes(PNaming_NamedShapemyNewShapes);

    Standard_Integer PNaming_NamedShapemyShapeStatus;
    f.GetInteger(PNaming_NamedShapemyShapeStatus);
    pp->_CSFDB_SetPNaming_NamedShapemyShapeStatus(PNaming_NamedShapemyShapeStatus);

    Standard_Integer PNaming_NamedShapemyVersion;
    f.GetInteger(PNaming_NamedShapemyVersion);
    pp->_CSFDB_SetPNaming_NamedShapemyVersion(PNaming_NamedShapemyVersion);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PNaming_NamedShape::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PNaming_NamedShape::SRead(p,f,theSchema);
}
