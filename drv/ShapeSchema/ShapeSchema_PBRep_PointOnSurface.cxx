#ifndef _ShapeSchema_PBRep_PointOnSurface_HeaderFile
#include <ShapeSchema_PBRep_PointOnSurface.hxx>
#endif
#ifndef _PBRep_PointOnSurface_HeaderFile
#include <PBRep_PointOnSurface.hxx>
#endif
#include <ShapeSchema_PBRep_PointOnSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PointOnSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PointOnSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PointOnSurface::New() const
{
  return new PBRep_PointOnSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PointOnSurface::SAdd(const Handle(PBRep_PointOnSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PointOnSurface")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_PointRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointsOnSurfacemySurface());

    }
  }
}

void ShapeSchema_PBRep_PointOnSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PointOnSurface::SAdd((Handle(PBRep_PointOnSurface)&)p,theSchema);
}

void ShapeSchema_PBRep_PointOnSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointOnSurface) &pp = (Handle(PBRep_PointOnSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_PointRepresentationmyParameter());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointsOnSurfacemySurface(),f);
  f.PutReal(pp->_CSFDB_GetPBRep_PointOnSurfacemyParameter2());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointOnSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PointOnSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PointOnSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointOnSurface) &pp = (Handle(PBRep_PointOnSurface)&)p;

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

    Standard_Real PBRep_PointOnSurfacemyParameter2;
    f.GetReal(PBRep_PointOnSurfacemyParameter2);
    pp->_CSFDB_SetPBRep_PointOnSurfacemyParameter2(PBRep_PointOnSurfacemyParameter2);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointOnSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PointOnSurface::SRead(p,f,theSchema);
}
