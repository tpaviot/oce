#ifndef _ShapeSchema_PGeom_BSplineSurface_HeaderFile
#include <ShapeSchema_PGeom_BSplineSurface.hxx>
#endif
#ifndef _PGeom_BSplineSurface_HeaderFile
#include <PGeom_BSplineSurface.hxx>
#endif
#include <ShapeSchema_PGeom_BSplineSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_BSplineSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_BSplineSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_BSplineSurface::New() const
{
  return new PGeom_BSplineSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_BSplineSurface::SAdd(const Handle(PGeom_BSplineSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_BSplineSurface")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineSurfacepoles());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineSurfaceweights());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineSurfaceuKnots());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineSurfacevKnots());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineSurfaceuMultiplicities());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineSurfacevMultiplicities());

    }
  }
}

void ShapeSchema_PGeom_BSplineSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_BSplineSurface::SAdd((Handle(PGeom_BSplineSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_BSplineSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BSplineSurface) &pp = (Handle(PGeom_BSplineSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPGeom_BSplineSurfaceuRational());
  f.PutBoolean(pp->_CSFDB_GetPGeom_BSplineSurfacevRational());
  f.PutBoolean(pp->_CSFDB_GetPGeom_BSplineSurfaceuPeriodic());
  f.PutBoolean(pp->_CSFDB_GetPGeom_BSplineSurfacevPeriodic());
  f.PutInteger(pp->_CSFDB_GetPGeom_BSplineSurfaceuSpineDegree());
  f.PutInteger(pp->_CSFDB_GetPGeom_BSplineSurfacevSpineDegree());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineSurfacepoles(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineSurfaceweights(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineSurfaceuKnots(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineSurfacevKnots(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineSurfaceuMultiplicities(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineSurfacevMultiplicities(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_BSplineSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_BSplineSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_BSplineSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BSplineSurface) &pp = (Handle(PGeom_BSplineSurface)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PGeom_BSplineSurfaceuRational;
    f.GetBoolean(PGeom_BSplineSurfaceuRational);
    pp->_CSFDB_SetPGeom_BSplineSurfaceuRational(PGeom_BSplineSurfaceuRational);

    Standard_Boolean PGeom_BSplineSurfacevRational;
    f.GetBoolean(PGeom_BSplineSurfacevRational);
    pp->_CSFDB_SetPGeom_BSplineSurfacevRational(PGeom_BSplineSurfacevRational);

    Standard_Boolean PGeom_BSplineSurfaceuPeriodic;
    f.GetBoolean(PGeom_BSplineSurfaceuPeriodic);
    pp->_CSFDB_SetPGeom_BSplineSurfaceuPeriodic(PGeom_BSplineSurfaceuPeriodic);

    Standard_Boolean PGeom_BSplineSurfacevPeriodic;
    f.GetBoolean(PGeom_BSplineSurfacevPeriodic);
    pp->_CSFDB_SetPGeom_BSplineSurfacevPeriodic(PGeom_BSplineSurfacevPeriodic);

    Standard_Integer PGeom_BSplineSurfaceuSpineDegree;
    f.GetInteger(PGeom_BSplineSurfaceuSpineDegree);
    pp->_CSFDB_SetPGeom_BSplineSurfaceuSpineDegree(PGeom_BSplineSurfaceuSpineDegree);

    Standard_Integer PGeom_BSplineSurfacevSpineDegree;
    f.GetInteger(PGeom_BSplineSurfacevSpineDegree);
    pp->_CSFDB_SetPGeom_BSplineSurfacevSpineDegree(PGeom_BSplineSurfacevSpineDegree);

    Handle(PColgp_HArray2OfPnt) PGeom_BSplineSurfacepoles;

    theSchema->ReadPersistentReference(PGeom_BSplineSurfacepoles,f);
    pp->_CSFDB_SetPGeom_BSplineSurfacepoles(PGeom_BSplineSurfacepoles);

    Handle(PColStd_HArray2OfReal) PGeom_BSplineSurfaceweights;

    theSchema->ReadPersistentReference(PGeom_BSplineSurfaceweights,f);
    pp->_CSFDB_SetPGeom_BSplineSurfaceweights(PGeom_BSplineSurfaceweights);

    Handle(PColStd_HArray1OfReal) PGeom_BSplineSurfaceuKnots;

    theSchema->ReadPersistentReference(PGeom_BSplineSurfaceuKnots,f);
    pp->_CSFDB_SetPGeom_BSplineSurfaceuKnots(PGeom_BSplineSurfaceuKnots);

    Handle(PColStd_HArray1OfReal) PGeom_BSplineSurfacevKnots;

    theSchema->ReadPersistentReference(PGeom_BSplineSurfacevKnots,f);
    pp->_CSFDB_SetPGeom_BSplineSurfacevKnots(PGeom_BSplineSurfacevKnots);

    Handle(PColStd_HArray1OfInteger) PGeom_BSplineSurfaceuMultiplicities;

    theSchema->ReadPersistentReference(PGeom_BSplineSurfaceuMultiplicities,f);
    pp->_CSFDB_SetPGeom_BSplineSurfaceuMultiplicities(PGeom_BSplineSurfaceuMultiplicities);

    Handle(PColStd_HArray1OfInteger) PGeom_BSplineSurfacevMultiplicities;

    theSchema->ReadPersistentReference(PGeom_BSplineSurfacevMultiplicities,f);
    pp->_CSFDB_SetPGeom_BSplineSurfacevMultiplicities(PGeom_BSplineSurfacevMultiplicities);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_BSplineSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_BSplineSurface::SRead(p,f,theSchema);
}
