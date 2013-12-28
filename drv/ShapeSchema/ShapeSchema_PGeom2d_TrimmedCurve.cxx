#ifndef _ShapeSchema_PGeom2d_TrimmedCurve_HeaderFile
#include <ShapeSchema_PGeom2d_TrimmedCurve.hxx>
#endif
#ifndef _PGeom2d_TrimmedCurve_HeaderFile
#include <PGeom2d_TrimmedCurve.hxx>
#endif
#include <ShapeSchema_PGeom2d_TrimmedCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_TrimmedCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_TrimmedCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_TrimmedCurve::New() const
{
  return new PGeom2d_TrimmedCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_TrimmedCurve::SAdd(const Handle(PGeom2d_TrimmedCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_TrimmedCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_TrimmedCurvebasisCurve());

    }
  }
}

void ShapeSchema_PGeom2d_TrimmedCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_TrimmedCurve::SAdd((Handle(PGeom2d_TrimmedCurve)&)p,theSchema);
}

void ShapeSchema_PGeom2d_TrimmedCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_TrimmedCurve) &pp = (Handle(PGeom2d_TrimmedCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_TrimmedCurvebasisCurve(),f);
  f.PutReal(pp->_CSFDB_GetPGeom2d_TrimmedCurvefirstU());
  f.PutReal(pp->_CSFDB_GetPGeom2d_TrimmedCurvelastU());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_TrimmedCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_TrimmedCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_TrimmedCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_TrimmedCurve) &pp = (Handle(PGeom2d_TrimmedCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom2d_Curve) PGeom2d_TrimmedCurvebasisCurve;

    theSchema->ReadPersistentReference(PGeom2d_TrimmedCurvebasisCurve,f);
    pp->_CSFDB_SetPGeom2d_TrimmedCurvebasisCurve(PGeom2d_TrimmedCurvebasisCurve);

    Standard_Real PGeom2d_TrimmedCurvefirstU;
    f.GetReal(PGeom2d_TrimmedCurvefirstU);
    pp->_CSFDB_SetPGeom2d_TrimmedCurvefirstU(PGeom2d_TrimmedCurvefirstU);

    Standard_Real PGeom2d_TrimmedCurvelastU;
    f.GetReal(PGeom2d_TrimmedCurvelastU);
    pp->_CSFDB_SetPGeom2d_TrimmedCurvelastU(PGeom2d_TrimmedCurvelastU);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_TrimmedCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_TrimmedCurve::SRead(p,f,theSchema);
}
