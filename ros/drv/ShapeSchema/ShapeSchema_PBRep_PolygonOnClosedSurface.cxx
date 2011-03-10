#ifndef _ShapeSchema_PBRep_PolygonOnClosedSurface_HeaderFile
#include <ShapeSchema_PBRep_PolygonOnClosedSurface.hxx>
#endif
#ifndef _PBRep_PolygonOnClosedSurface_HeaderFile
#include <PBRep_PolygonOnClosedSurface.hxx>
#endif
#include <ShapeSchema_PBRep_PolygonOnClosedSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PolygonOnClosedSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PolygonOnClosedSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PolygonOnClosedSurface::New() const
{
  return new PBRep_PolygonOnClosedSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PolygonOnClosedSurface::SAdd(const Handle(PBRep_PolygonOnClosedSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PolygonOnClosedSurface")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnSurfacemyPolygon2D());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnSurfacemySurface());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnClosedSurfacemyPolygon2());

    }
  }
}

void ShapeSchema_PBRep_PolygonOnClosedSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PolygonOnClosedSurface::SAdd((Handle(PBRep_PolygonOnClosedSurface)&)p,theSchema);
}

void ShapeSchema_PBRep_PolygonOnClosedSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnClosedSurface) &pp = (Handle(PBRep_PolygonOnClosedSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnSurfacemyPolygon2D(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnSurfacemySurface(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnClosedSurfacemyPolygon2(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnClosedSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PolygonOnClosedSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PolygonOnClosedSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnClosedSurface) &pp = (Handle(PBRep_PolygonOnClosedSurface)&)p;

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

    Handle(PPoly_Polygon2D) PBRep_PolygonOnClosedSurfacemyPolygon2;

    theSchema->ReadPersistentReference(PBRep_PolygonOnClosedSurfacemyPolygon2,f);
    pp->_CSFDB_SetPBRep_PolygonOnClosedSurfacemyPolygon2(PBRep_PolygonOnClosedSurfacemyPolygon2);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnClosedSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PolygonOnClosedSurface::SRead(p,f,theSchema);
}
