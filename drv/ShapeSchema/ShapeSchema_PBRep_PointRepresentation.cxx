#ifndef _ShapeSchema_PBRep_PointRepresentation_HeaderFile
#include <ShapeSchema_PBRep_PointRepresentation.hxx>
#endif
#ifndef _PBRep_PointRepresentation_HeaderFile
#include <PBRep_PointRepresentation.hxx>
#endif
#include <ShapeSchema_PBRep_PointRepresentation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PointRepresentation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PointRepresentation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PointRepresentation::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PBRep_PointRepresentation::SAdd(const Handle(PBRep_PointRepresentation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PointRepresentation")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_PointRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointRepresentationmyNext());

    }
  }
}

void ShapeSchema_PBRep_PointRepresentation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PointRepresentation::SAdd((Handle(PBRep_PointRepresentation)&)p,theSchema);
}

void ShapeSchema_PBRep_PointRepresentation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointRepresentation) &pp = (Handle(PBRep_PointRepresentation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_PointRepresentationmyParameter());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointRepresentationmyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointRepresentation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PointRepresentation::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PointRepresentation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointRepresentation) &pp = (Handle(PBRep_PointRepresentation)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);

    Standard_Real PBRep_PointRepresentationmyParameter;
    f.GetReal(PBRep_PointRepresentationmyParameter);
    pp->_CSFDB_SetPBRep_PointRepresentationmyParameter(PBRep_PointRepresentationmyParameter);

    Handle(PBRep_PointRepresentation) PBRep_PointRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_PointRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_PointRepresentationmyNext(PBRep_PointRepresentationmyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointRepresentation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PointRepresentation::SRead(p,f,theSchema);
}
