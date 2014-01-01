#ifndef _ShapeSchema_PBRep_PointsOnSurface_HeaderFile
#include <ShapeSchema_PBRep_PointsOnSurface.hxx>
#endif
#ifndef _PBRep_PointsOnSurface_HeaderFile
#include <PBRep_PointsOnSurface.hxx>
#endif
#include <ShapeSchema_PBRep_PointsOnSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PointsOnSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PointsOnSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PointsOnSurface::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PBRep_PointsOnSurface::SAdd(const Handle(PBRep_PointsOnSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PointsOnSurface")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_PointRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointsOnSurfacemySurface());

    }
  }
}

void ShapeSchema_PBRep_PointsOnSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PointsOnSurface::SAdd((Handle(PBRep_PointsOnSurface)&)p,theSchema);
}

void ShapeSchema_PBRep_PointsOnSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointsOnSurface) &pp = (Handle(PBRep_PointsOnSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_PointRepresentationmyParameter());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointsOnSurfacemySurface(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointsOnSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PointsOnSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PointsOnSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointsOnSurface) &pp = (Handle(PBRep_PointsOnSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);

    Standard_Real PBRep_PointRepresentationmyParameter;
    f.GetReal(PBRep_PointRepresentationmyParameter);
    pp->_CSFDB_SetPBRep_PointRepresentationmyParameter(PBRep_PointRepresentationmyParameter);

    Handle(PBRep_PointRepresentation) PBRep_PointRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_PointRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_PointRepresentationmyNext(PBRep_PointRepresentationmyNext);

    Handle(PGeom_Surface) PBRep_PointsOnSurfacemySurface;

    theSchema->ReadPersistentReference(PBRep_PointsOnSurfacemySurface,f);
    pp->_CSFDB_SetPBRep_PointsOnSurfacemySurface(PBRep_PointsOnSurfacemySurface);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointsOnSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PointsOnSurface::SRead(p,f,theSchema);
}
