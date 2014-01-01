#ifndef _ShapeSchema_PGeom_SurfaceOfLinearExtrusion_HeaderFile
#include <ShapeSchema_PGeom_SurfaceOfLinearExtrusion.hxx>
#endif
#ifndef _PGeom_SurfaceOfLinearExtrusion_HeaderFile
#include <PGeom_SurfaceOfLinearExtrusion.hxx>
#endif
#include <ShapeSchema_PGeom_SurfaceOfLinearExtrusion.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_SurfaceOfLinearExtrusion,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_SurfaceOfLinearExtrusion,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_SurfaceOfLinearExtrusion::New() const
{
  return new PGeom_SurfaceOfLinearExtrusion(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_SurfaceOfLinearExtrusion::SAdd(const Handle(PGeom_SurfaceOfLinearExtrusion)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_SurfaceOfLinearExtrusion")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_SweptSurfacebasisCurve());

    }
  }
}

void ShapeSchema_PGeom_SurfaceOfLinearExtrusion::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_SurfaceOfLinearExtrusion::SAdd((Handle(PGeom_SurfaceOfLinearExtrusion)&)p,theSchema);
}

void ShapeSchema_PGeom_SurfaceOfLinearExtrusion::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SurfaceOfLinearExtrusion) &pp = (Handle(PGeom_SurfaceOfLinearExtrusion)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_SweptSurfacebasisCurve(),f);
    ShapeSchema_gp_Dir::SWrite(pp->_CSFDB_GetPGeom_SweptSurfacedirection(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_SurfaceOfLinearExtrusion::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_SurfaceOfLinearExtrusion::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_SurfaceOfLinearExtrusion::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SurfaceOfLinearExtrusion) &pp = (Handle(PGeom_SurfaceOfLinearExtrusion)&)p;

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

void ShapeSchema_PGeom_SurfaceOfLinearExtrusion::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_SurfaceOfLinearExtrusion::SRead(p,f,theSchema);
}
