#ifndef _ShapeSchema_PColPGeom_HArray1OfCurve_HeaderFile
#include <ShapeSchema_PColPGeom_HArray1OfCurve.hxx>
#endif
#ifndef _PColPGeom_HArray1OfCurve_HeaderFile
#include <PColPGeom_HArray1OfCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray1OfCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray1OfCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray1OfCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray1OfCurve::New() const
{
  return new PColPGeom_HArray1OfCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray1OfCurve::SAdd(const Handle(PColPGeom_HArray1OfCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray1OfCurve")) {
         ShapeSchema_PColPGeom_FieldOfHArray1OfCurve::SAdd(p->_CSFDB_GetPColPGeom_HArray1OfCurveData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray1OfCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray1OfCurve::SAdd((Handle(PColPGeom_HArray1OfCurve)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray1OfCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfCurve) &pp = (Handle(PColPGeom_HArray1OfCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfCurveLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfCurveUpperBound());
    ShapeSchema_PColPGeom_FieldOfHArray1OfCurve::SWrite(pp->_CSFDB_GetPColPGeom_HArray1OfCurveData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray1OfCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray1OfCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfCurve) &pp = (Handle(PColPGeom_HArray1OfCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray1OfCurveLowerBound;
    f.GetInteger(PColPGeom_HArray1OfCurveLowerBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfCurveLowerBound(PColPGeom_HArray1OfCurveLowerBound);

    Standard_Integer PColPGeom_HArray1OfCurveUpperBound;
    f.GetInteger(PColPGeom_HArray1OfCurveUpperBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfCurveUpperBound(PColPGeom_HArray1OfCurveUpperBound);

    ShapeSchema_PColPGeom_FieldOfHArray1OfCurve::SRead((PColPGeom_FieldOfHArray1OfCurve&)pp->_CSFDB_GetPColPGeom_HArray1OfCurveData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray1OfCurve::SRead(p,f,theSchema);
}
