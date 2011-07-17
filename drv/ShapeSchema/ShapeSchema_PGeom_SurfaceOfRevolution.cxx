#ifndef _ShapeSchema_PGeom_SurfaceOfRevolution_HeaderFile
#include <ShapeSchema_PGeom_SurfaceOfRevolution.hxx>
#endif
#ifndef _PGeom_SurfaceOfRevolution_HeaderFile
#include <PGeom_SurfaceOfRevolution.hxx>
#endif
#include <ShapeSchema_PGeom_SurfaceOfRevolution.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_SurfaceOfRevolution,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_SurfaceOfRevolution,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_SurfaceOfRevolution::New() const
{
  return new PGeom_SurfaceOfRevolution(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_SurfaceOfRevolution::SAdd(const Handle(PGeom_SurfaceOfRevolution)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_SurfaceOfRevolution")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_SweptSurfacebasisCurve());

    }
  }
}

void ShapeSchema_PGeom_SurfaceOfRevolution::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_SurfaceOfRevolution::SAdd((Handle(PGeom_SurfaceOfRevolution)&)p,theSchema);
}

void ShapeSchema_PGeom_SurfaceOfRevolution::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SurfaceOfRevolution) &pp = (Handle(PGeom_SurfaceOfRevolution)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_SweptSurfacebasisCurve(),f);
    ShapeSchema_gp_Dir::SWrite(pp->_CSFDB_GetPGeom_SweptSurfacedirection(),f,theSchema);
    ShapeSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPGeom_SurfaceOfRevolutionlocation(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_SurfaceOfRevolution::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_SurfaceOfRevolution::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_SurfaceOfRevolution::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_SurfaceOfRevolution) &pp = (Handle(PGeom_SurfaceOfRevolution)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom_Curve) PGeom_SweptSurfacebasisCurve;

    theSchema->ReadPersistentReference(PGeom_SweptSurfacebasisCurve,f);
    pp->_CSFDB_SetPGeom_SweptSurfacebasisCurve(PGeom_SweptSurfacebasisCurve);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp->_CSFDB_GetPGeom_SweptSurfacedirection(),f,theSchema);

    ShapeSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPGeom_SurfaceOfRevolutionlocation(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_SurfaceOfRevolution::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_SurfaceOfRevolution::SRead(p,f,theSchema);
}
