#ifndef _ShapeSchema_PGeom_SweptSurface_HeaderFile
#include <ShapeSchema_PGeom_SweptSurface.hxx>
#endif
#ifndef _PGeom_SweptSurface_HeaderFile
#include <PGeom_SweptSurface.hxx>
#endif
#include <ShapeSchema_PGeom_SweptSurface.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_SweptSurface,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_SweptSurface,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_SweptSurface::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PGeom_SweptSurface::SAdd(const Handle(PGeom_SweptSurface)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_SweptSurface")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_SweptSurfacebasisCurve());

    }
  }
}

void ShapeSchema_PGeom_SweptSurface::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_SweptSurface::SAdd((Handle(PGeom_SweptSurface)&)p,theSchema);
}

void ShapeSchema_PGeom_SweptSurface::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SweptSurface) &pp = (Handle(PGeom_SweptSurface)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_SweptSurfacebasisCurve(),f);
    ShapeSchema_gp_Dir::SWrite(pp->_CSFDB_GetPGeom_SweptSurfacedirection(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_SweptSurface::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_SweptSurface::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_SweptSurface::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SweptSurface) &pp = (Handle(PGeom_SweptSurface)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom_Curve) PGeom_SweptSurfacebasisCurve;

    theSchema->ReadPersistentReference(PGeom_SweptSurfacebasisCurve,f);
    pp->_CSFDB_SetPGeom_SweptSurfacebasisCurve(PGeom_SweptSurfacebasisCurve);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp->_CSFDB_GetPGeom_SweptSurfacedirection(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_SweptSurface::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_SweptSurface::SRead(p,f,theSchema);
}
