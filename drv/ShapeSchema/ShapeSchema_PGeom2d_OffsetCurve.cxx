#ifndef _ShapeSchema_PGeom2d_OffsetCurve_HeaderFile
#include <ShapeSchema_PGeom2d_OffsetCurve.hxx>
#endif
#ifndef _PGeom2d_OffsetCurve_HeaderFile
#include <PGeom2d_OffsetCurve.hxx>
#endif
#include <ShapeSchema_PGeom2d_OffsetCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_OffsetCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_OffsetCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_OffsetCurve::New() const
{
  return new PGeom2d_OffsetCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_OffsetCurve::SAdd(const Handle(PGeom2d_OffsetCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_OffsetCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_OffsetCurvebasisCurve());

    }
  }
}

void ShapeSchema_PGeom2d_OffsetCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_OffsetCurve::SAdd((Handle(PGeom2d_OffsetCurve)&)p,theSchema);
}

void ShapeSchema_PGeom2d_OffsetCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_OffsetCurve) &pp = (Handle(PGeom2d_OffsetCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_OffsetCurvebasisCurve(),f);
  f.PutReal(pp->_CSFDB_GetPGeom2d_OffsetCurveoffsetValue());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_OffsetCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_OffsetCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_OffsetCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_OffsetCurve) &pp = (Handle(PGeom2d_OffsetCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom2d_Curve) PGeom2d_OffsetCurvebasisCurve;

    theSchema->ReadPersistentReference(PGeom2d_OffsetCurvebasisCurve,f);
    pp->_CSFDB_SetPGeom2d_OffsetCurvebasisCurve(PGeom2d_OffsetCurvebasisCurve);

    Standard_Real PGeom2d_OffsetCurveoffsetValue;
    f.GetReal(PGeom2d_OffsetCurveoffsetValue);
    pp->_CSFDB_SetPGeom2d_OffsetCurveoffsetValue(PGeom2d_OffsetCurveoffsetValue);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_OffsetCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_OffsetCurve::SRead(p,f,theSchema);
}
