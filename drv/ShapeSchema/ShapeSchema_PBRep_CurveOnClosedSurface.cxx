#ifndef _ShapeSchema_PBRep_CurveOnClosedSurface_HeaderFile
#include <ShapeSchema_PBRep_CurveOnClosedSurface.hxx>
#endif
#ifndef _PBRep_CurveOnClosedSurface_HeaderFile
#include <PBRep_CurveOnClosedSurface.hxx>
#endif
#include <ShapeSchema_PBRep_CurveOnClosedSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_CurveOnClosedSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_CurveOnClosedSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_CurveOnClosedSurface::New() const
{
  return new PBRep_CurveOnClosedSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_CurveOnClosedSurface::SAdd(const Handle(PBRep_CurveOnClosedSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_CurveOnClosedSurface")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveOnSurfacemyPCurve());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveOnSurfacemySurface());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveOnClosedSurfacemyPCurve2());

    }
  }
}

void ShapeSchema_PBRep_CurveOnClosedSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_CurveOnClosedSurface::SAdd((Handle(PBRep_CurveOnClosedSurface)&)p,theSchema);
}

void ShapeSchema_PBRep_CurveOnClosedSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_CurveOnClosedSurface) &pp = (Handle(PBRep_CurveOnClosedSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
  f.PutReal(pp->_CSFDB_GetPBRep_GCurvemyFirst());
  f.PutReal(pp->_CSFDB_GetPBRep_GCurvemyLast());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveOnSurfacemyPCurve(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveOnSurfacemySurface(),f);
    ShapeSchema_gp_Pnt2d::SWrite(pp->_CSFDB_GetPBRep_CurveOnSurfacemyUV1(),f,theSchema);
    ShapeSchema_gp_Pnt2d::SWrite(pp->_CSFDB_GetPBRep_CurveOnSurfacemyUV2(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveOnClosedSurfacemyPCurve2(),f);
  f.PutInteger(pp->_CSFDB_GetPBRep_CurveOnClosedSurfacemyContinuity());
    ShapeSchema_gp_Pnt2d::SWrite(pp->_CSFDB_GetPBRep_CurveOnClosedSurfacemyUV21(),f,theSchema);
    ShapeSchema_gp_Pnt2d::SWrite(pp->_CSFDB_GetPBRep_CurveOnClosedSurfacemyUV22(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_CurveOnClosedSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_CurveOnClosedSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_CurveOnClosedSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_CurveOnClosedSurface) &pp = (Handle(PBRep_CurveOnClosedSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    Standard_Real PBRep_GCurvemyFirst;
    f.GetReal(PBRep_GCurvemyFirst);
    pp->_CSFDB_SetPBRep_GCurvemyFirst(PBRep_GCurvemyFirst);

    Standard_Real PBRep_GCurvemyLast;
    f.GetReal(PBRep_GCurvemyLast);
    pp->_CSFDB_SetPBRep_GCurvemyLast(PBRep_GCurvemyLast);

    Handle(PGeom2d_Curve) PBRep_CurveOnSurfacemyPCurve;

    theSchema->ReadPersistentReference(PBRep_CurveOnSurfacemyPCurve,f);
    pp->_CSFDB_SetPBRep_CurveOnSurfacemyPCurve(PBRep_CurveOnSurfacemyPCurve);

    Handle(PGeom_Surface) PBRep_CurveOnSurfacemySurface;

    theSchema->ReadPersistentReference(PBRep_CurveOnSurfacemySurface,f);
    pp->_CSFDB_SetPBRep_CurveOnSurfacemySurface(PBRep_CurveOnSurfacemySurface);

    ShapeSchema_gp_Pnt2d::SRead((gp_Pnt2d&)pp->_CSFDB_GetPBRep_CurveOnSurfacemyUV1(),f,theSchema);

    ShapeSchema_gp_Pnt2d::SRead((gp_Pnt2d&)pp->_CSFDB_GetPBRep_CurveOnSurfacemyUV2(),f,theSchema);

    Handle(PGeom2d_Curve) PBRep_CurveOnClosedSurfacemyPCurve2;

    theSchema->ReadPersistentReference(PBRep_CurveOnClosedSurfacemyPCurve2,f);
    pp->_CSFDB_SetPBRep_CurveOnClosedSurfacemyPCurve2(PBRep_CurveOnClosedSurfacemyPCurve2);

    GeomAbs_Shape PBRep_CurveOnClosedSurfacemyContinuity;
    Standard_Integer i_CSFDB_PBRep_CurveOnClosedSurfacemyContinuity;
    f.GetInteger(i_CSFDB_PBRep_CurveOnClosedSurfacemyContinuity);
    PBRep_CurveOnClosedSurfacemyContinuity = (GeomAbs_Shape)i_CSFDB_PBRep_CurveOnClosedSurfacemyContinuity;
    pp->_CSFDB_SetPBRep_CurveOnClosedSurfacemyContinuity(PBRep_CurveOnClosedSurfacemyContinuity);

    ShapeSchema_gp_Pnt2d::SRead((gp_Pnt2d&)pp->_CSFDB_GetPBRep_CurveOnClosedSurfacemyUV21(),f,theSchema);

    ShapeSchema_gp_Pnt2d::SRead((gp_Pnt2d&)pp->_CSFDB_GetPBRep_CurveOnClosedSurfacemyUV22(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_CurveOnClosedSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_CurveOnClosedSurface::SRead(p,f,theSchema);
}
