#ifndef _ShapeSchema_PGeom_TrimmedCurve_HeaderFile
#include <ShapeSchema_PGeom_TrimmedCurve.hxx>
#endif
#ifndef _PGeom_TrimmedCurve_HeaderFile
#include <PGeom_TrimmedCurve.hxx>
#endif
#include <ShapeSchema_PGeom_TrimmedCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_TrimmedCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_TrimmedCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_TrimmedCurve::New() const
{
  return new PGeom_TrimmedCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_TrimmedCurve::SAdd(const Handle(PGeom_TrimmedCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_TrimmedCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_TrimmedCurvebasisCurve());

    }
  }
}

void ShapeSchema_PGeom_TrimmedCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_TrimmedCurve::SAdd((Handle(PGeom_TrimmedCurve)&)p,theSchema);
}

void ShapeSchema_PGeom_TrimmedCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_TrimmedCurve) &pp = (Handle(PGeom_TrimmedCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_TrimmedCurvebasisCurve(),f);
  f.PutReal(pp->_CSFDB_GetPGeom_TrimmedCurvefirstU());
  f.PutReal(pp->_CSFDB_GetPGeom_TrimmedCurvelastU());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_TrimmedCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_TrimmedCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_TrimmedCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_TrimmedCurve) &pp = (Handle(PGeom_TrimmedCurve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom_Curve) PGeom_TrimmedCurvebasisCurve;

    theSchema->ReadPersistentReference(PGeom_TrimmedCurvebasisCurve,f);
    pp->_CSFDB_SetPGeom_TrimmedCurvebasisCurve(PGeom_TrimmedCurvebasisCurve);

    Standard_Real PGeom_TrimmedCurvefirstU;
    f.GetReal(PGeom_TrimmedCurvefirstU);
    pp->_CSFDB_SetPGeom_TrimmedCurvefirstU(PGeom_TrimmedCurvefirstU);

    Standard_Real PGeom_TrimmedCurvelastU;
    f.GetReal(PGeom_TrimmedCurvelastU);
    pp->_CSFDB_SetPGeom_TrimmedCurvelastU(PGeom_TrimmedCurvelastU);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_TrimmedCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_TrimmedCurve::SRead(p,f,theSchema);
}
