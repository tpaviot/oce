#ifndef _ShapeSchema_PBRep_CurveOn2Surfaces_HeaderFile
#include <ShapeSchema_PBRep_CurveOn2Surfaces.hxx>
#endif
#ifndef _PBRep_CurveOn2Surfaces_HeaderFile
#include <PBRep_CurveOn2Surfaces.hxx>
#endif
#include <ShapeSchema_PBRep_CurveOn2Surfaces.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_CurveOn2Surfaces,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_CurveOn2Surfaces,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_CurveOn2Surfaces::New() const
{
  return new PBRep_CurveOn2Surfaces(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_CurveOn2Surfaces::SAdd(const Handle(PBRep_CurveOn2Surfaces)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_CurveOn2Surfaces")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveOn2SurfacesmySurface());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveOn2SurfacesmySurface2());
   ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveOn2SurfacesmyLocation2(),theSchema);

    }
  }
}

void ShapeSchema_PBRep_CurveOn2Surfaces::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_CurveOn2Surfaces::SAdd((Handle(PBRep_CurveOn2Surfaces)&)p,theSchema);
}

void ShapeSchema_PBRep_CurveOn2Surfaces::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_CurveOn2Surfaces) &pp = (Handle(PBRep_CurveOn2Surfaces)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveOn2SurfacesmySurface(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveOn2SurfacesmySurface2(),f);
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveOn2SurfacesmyLocation2(),f,theSchema);
  f.PutInteger(pp->_CSFDB_GetPBRep_CurveOn2SurfacesmyContinuity());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_CurveOn2Surfaces::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_CurveOn2Surfaces::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_CurveOn2Surfaces::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_CurveOn2Surfaces) &pp = (Handle(PBRep_CurveOn2Surfaces)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    Handle(PGeom_Surface) PBRep_CurveOn2SurfacesmySurface;

    theSchema->ReadPersistentReference(PBRep_CurveOn2SurfacesmySurface,f);
    pp->_CSFDB_SetPBRep_CurveOn2SurfacesmySurface(PBRep_CurveOn2SurfacesmySurface);

    Handle(PGeom_Surface) PBRep_CurveOn2SurfacesmySurface2;

    theSchema->ReadPersistentReference(PBRep_CurveOn2SurfacesmySurface2,f);
    pp->_CSFDB_SetPBRep_CurveOn2SurfacesmySurface2(PBRep_CurveOn2SurfacesmySurface2);

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveOn2SurfacesmyLocation2(),f,theSchema);

    GeomAbs_Shape PBRep_CurveOn2SurfacesmyContinuity;
    Standard_Integer i_CSFDB_PBRep_CurveOn2SurfacesmyContinuity;
    f.GetInteger(i_CSFDB_PBRep_CurveOn2SurfacesmyContinuity);
    PBRep_CurveOn2SurfacesmyContinuity = (GeomAbs_Shape)i_CSFDB_PBRep_CurveOn2SurfacesmyContinuity;
    pp->_CSFDB_SetPBRep_CurveOn2SurfacesmyContinuity(PBRep_CurveOn2SurfacesmyContinuity);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_CurveOn2Surfaces::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_CurveOn2Surfaces::SRead(p,f,theSchema);
}
