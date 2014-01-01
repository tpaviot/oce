#ifndef _ShapeSchema_PBRep_PolygonOnSurface_HeaderFile
#include <ShapeSchema_PBRep_PolygonOnSurface.hxx>
#endif
#ifndef _PBRep_PolygonOnSurface_HeaderFile
#include <PBRep_PolygonOnSurface.hxx>
#endif
#include <ShapeSchema_PBRep_PolygonOnSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PolygonOnSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PolygonOnSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PolygonOnSurface::New() const
{
  return new PBRep_PolygonOnSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PolygonOnSurface::SAdd(const Handle(PBRep_PolygonOnSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PolygonOnSurface")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnSurfacemyPolygon2D());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnSurfacemySurface());

    }
  }
}

void ShapeSchema_PBRep_PolygonOnSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PolygonOnSurface::SAdd((Handle(PBRep_PolygonOnSurface)&)p,theSchema);
}

void ShapeSchema_PBRep_PolygonOnSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnSurface) &pp = (Handle(PBRep_PolygonOnSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnSurfacemyPolygon2D(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnSurfacemySurface(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PolygonOnSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PolygonOnSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnSurface) &pp = (Handle(PBRep_PolygonOnSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    Handle(PPoly_Polygon2D) PBRep_PolygonOnSurfacemyPolygon2D;

    theSchema->ReadPersistentReference(PBRep_PolygonOnSurfacemyPolygon2D,f);
    pp->_CSFDB_SetPBRep_PolygonOnSurfacemyPolygon2D(PBRep_PolygonOnSurfacemyPolygon2D);

    Handle(PGeom_Surface) PBRep_PolygonOnSurfacemySurface;

    theSchema->ReadPersistentReference(PBRep_PolygonOnSurfacemySurface,f);
    pp->_CSFDB_SetPBRep_PolygonOnSurfacemySurface(PBRep_PolygonOnSurfacemySurface);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PolygonOnSurface::SRead(p,f,theSchema);
}
