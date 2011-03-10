#ifndef _ShapeSchema_PBRep_PointOnCurveOnSurface_HeaderFile
#include <ShapeSchema_PBRep_PointOnCurveOnSurface.hxx>
#endif
#ifndef _PBRep_PointOnCurveOnSurface_HeaderFile
#include <PBRep_PointOnCurveOnSurface.hxx>
#endif
#include <ShapeSchema_PBRep_PointOnCurveOnSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PointOnCurveOnSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PointOnCurveOnSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PointOnCurveOnSurface::New() const
{
  return new PBRep_PointOnCurveOnSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PointOnCurveOnSurface::SAdd(const Handle(PBRep_PointOnCurveOnSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PointOnCurveOnSurface")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_PointRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointsOnSurfacemySurface());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointOnCurveOnSurfacemyPCurve());

    }
  }
}

void ShapeSchema_PBRep_PointOnCurveOnSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PointOnCurveOnSurface::SAdd((Handle(PBRep_PointOnCurveOnSurface)&)p,theSchema);
}

void ShapeSchema_PBRep_PointOnCurveOnSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointOnCurveOnSurface) &pp = (Handle(PBRep_PointOnCurveOnSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_PointRepresentationmyParameter());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointsOnSurfacemySurface(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointOnCurveOnSurfacemyPCurve(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointOnCurveOnSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PointOnCurveOnSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PointOnCurveOnSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointOnCurveOnSurface) &pp = (Handle(PBRep_PointOnCurveOnSurface)&)p;

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

    Handle(PGeom2d_Curve) PBRep_PointOnCurveOnSurfacemyPCurve;

    theSchema->ReadPersistentReference(PBRep_PointOnCurveOnSurfacemyPCurve,f);
    pp->_CSFDB_SetPBRep_PointOnCurveOnSurfacemyPCurve(PBRep_PointOnCurveOnSurfacemyPCurve);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointOnCurveOnSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PointOnCurveOnSurface::SRead(p,f,theSchema);
}
