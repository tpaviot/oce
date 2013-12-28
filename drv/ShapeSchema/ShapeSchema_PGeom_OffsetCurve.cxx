#ifndef _ShapeSchema_PGeom_OffsetCurve_HeaderFile
#include <ShapeSchema_PGeom_OffsetCurve.hxx>
#endif
#ifndef _PGeom_OffsetCurve_HeaderFile
#include <PGeom_OffsetCurve.hxx>
#endif
#include <ShapeSchema_PGeom_OffsetCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_OffsetCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_OffsetCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_OffsetCurve::New() const
{
  return new PGeom_OffsetCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_OffsetCurve::SAdd(const Handle(PGeom_OffsetCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_OffsetCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_OffsetCurvebasisCurve());

    }
  }
}

void ShapeSchema_PGeom_OffsetCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_OffsetCurve::SAdd((Handle(PGeom_OffsetCurve)&)p,theSchema);
}

void ShapeSchema_PGeom_OffsetCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_OffsetCurve) &pp = (Handle(PGeom_OffsetCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_OffsetCurvebasisCurve(),f);
    ShapeSchema_gp_Dir::SWrite(pp->_CSFDB_GetPGeom_OffsetCurveoffsetDirection(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPGeom_OffsetCurveoffsetValue());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_OffsetCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_OffsetCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_OffsetCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_OffsetCurve) &pp = (Handle(PGeom_OffsetCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PGeom_Curve) PGeom_OffsetCurvebasisCurve;

    theSchema->ReadPersistentReference(PGeom_OffsetCurvebasisCurve,f);
    pp->_CSFDB_SetPGeom_OffsetCurvebasisCurve(PGeom_OffsetCurvebasisCurve);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp->_CSFDB_GetPGeom_OffsetCurveoffsetDirection(),f,theSchema);

    Standard_Real PGeom_OffsetCurveoffsetValue;
    f.GetReal(PGeom_OffsetCurveoffsetValue);
    pp->_CSFDB_SetPGeom_OffsetCurveoffsetValue(PGeom_OffsetCurveoffsetValue);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_OffsetCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_OffsetCurve::SRead(p,f,theSchema);
}
