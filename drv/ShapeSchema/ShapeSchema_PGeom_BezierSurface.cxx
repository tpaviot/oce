#ifndef _ShapeSchema_PGeom_BezierSurface_HeaderFile
#include <ShapeSchema_PGeom_BezierSurface.hxx>
#endif
#ifndef _PGeom_BezierSurface_HeaderFile
#include <PGeom_BezierSurface.hxx>
#endif
#include <ShapeSchema_PGeom_BezierSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_BezierSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_BezierSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_BezierSurface::New() const
{
  return new PGeom_BezierSurface(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_BezierSurface::SAdd(const Handle(PGeom_BezierSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_BezierSurface")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BezierSurfacepoles());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BezierSurfaceweights());

    }
  }
}

void ShapeSchema_PGeom_BezierSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_BezierSurface::SAdd((Handle(PGeom_BezierSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_BezierSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BezierSurface) &pp = (Handle(PGeom_BezierSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPGeom_BezierSurfaceuRational());
  f.PutBoolean(pp->_CSFDB_GetPGeom_BezierSurfacevRational());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BezierSurfacepoles(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BezierSurfaceweights(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_BezierSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_BezierSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_BezierSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BezierSurface) &pp = (Handle(PGeom_BezierSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PGeom_BezierSurfaceuRational;
    f.GetBoolean(PGeom_BezierSurfaceuRational);
    pp->_CSFDB_SetPGeom_BezierSurfaceuRational(PGeom_BezierSurfaceuRational);

    Standard_Boolean PGeom_BezierSurfacevRational;
    f.GetBoolean(PGeom_BezierSurfacevRational);
    pp->_CSFDB_SetPGeom_BezierSurfacevRational(PGeom_BezierSurfacevRational);

    Handle(PColgp_HArray2OfPnt) PGeom_BezierSurfacepoles;

    theSchema->ReadPersistentReference(PGeom_BezierSurfacepoles,f);
    pp->_CSFDB_SetPGeom_BezierSurfacepoles(PGeom_BezierSurfacepoles);

    Handle(PColStd_HArray2OfReal) PGeom_BezierSurfaceweights;

    theSchema->ReadPersistentReference(PGeom_BezierSurfaceweights,f);
    pp->_CSFDB_SetPGeom_BezierSurfaceweights(PGeom_BezierSurfaceweights);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_BezierSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_BezierSurface::SRead(p,f,theSchema);
}
