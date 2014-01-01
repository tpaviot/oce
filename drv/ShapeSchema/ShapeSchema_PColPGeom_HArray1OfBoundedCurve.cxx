#ifndef _ShapeSchema_PColPGeom_HArray1OfBoundedCurve_HeaderFile
#include <ShapeSchema_PColPGeom_HArray1OfBoundedCurve.hxx>
#endif
#ifndef _PColPGeom_HArray1OfBoundedCurve_HeaderFile
#include <PColPGeom_HArray1OfBoundedCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray1OfBoundedCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray1OfBoundedCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray1OfBoundedCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray1OfBoundedCurve::New() const
{
  return new PColPGeom_HArray1OfBoundedCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray1OfBoundedCurve::SAdd(const Handle(PColPGeom_HArray1OfBoundedCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray1OfBoundedCurve")) {
         ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedCurve::SAdd(p->_CSFDB_GetPColPGeom_HArray1OfBoundedCurveData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray1OfBoundedCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray1OfBoundedCurve::SAdd((Handle(PColPGeom_HArray1OfBoundedCurve)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray1OfBoundedCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfBoundedCurve) &pp = (Handle(PColPGeom_HArray1OfBoundedCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfBoundedCurveLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfBoundedCurveUpperBound());
    ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedCurve::SWrite(pp->_CSFDB_GetPColPGeom_HArray1OfBoundedCurveData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfBoundedCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray1OfBoundedCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray1OfBoundedCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfBoundedCurve) &pp = (Handle(PColPGeom_HArray1OfBoundedCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray1OfBoundedCurveLowerBound;
    f.GetInteger(PColPGeom_HArray1OfBoundedCurveLowerBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfBoundedCurveLowerBound(PColPGeom_HArray1OfBoundedCurveLowerBound);

    Standard_Integer PColPGeom_HArray1OfBoundedCurveUpperBound;
    f.GetInteger(PColPGeom_HArray1OfBoundedCurveUpperBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfBoundedCurveUpperBound(PColPGeom_HArray1OfBoundedCurveUpperBound);

    ShapeSchema_PColPGeom_FieldOfHArray1OfBoundedCurve::SRead((PColPGeom_FieldOfHArray1OfBoundedCurve&)pp->_CSFDB_GetPColPGeom_HArray1OfBoundedCurveData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfBoundedCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray1OfBoundedCurve::SRead(p,f,theSchema);
}
