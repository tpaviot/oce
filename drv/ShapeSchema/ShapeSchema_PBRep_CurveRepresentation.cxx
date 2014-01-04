#ifndef _ShapeSchema_PBRep_CurveRepresentation_HeaderFile
#include <ShapeSchema_PBRep_CurveRepresentation.hxx>
#endif
#ifndef _PBRep_CurveRepresentation_HeaderFile
#include <PBRep_CurveRepresentation.hxx>
#endif
#include <ShapeSchema_PBRep_CurveRepresentation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_CurveRepresentation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_CurveRepresentation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_CurveRepresentation::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PBRep_CurveRepresentation::SAdd(const Handle(PBRep_CurveRepresentation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_CurveRepresentation")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());

    }
  }
}

void ShapeSchema_PBRep_CurveRepresentation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_CurveRepresentation::SAdd((Handle(PBRep_CurveRepresentation)&)p,theSchema);
}

void ShapeSchema_PBRep_CurveRepresentation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_CurveRepresentation) &pp = (Handle(PBRep_CurveRepresentation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_CurveRepresentation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_CurveRepresentation::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_CurveRepresentation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_CurveRepresentation) &pp = (Handle(PBRep_CurveRepresentation)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_CurveRepresentation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_CurveRepresentation::SRead(p,f,theSchema);
}
