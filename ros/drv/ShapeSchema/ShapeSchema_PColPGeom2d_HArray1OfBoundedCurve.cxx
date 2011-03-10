#ifndef _ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve_HeaderFile
#include <ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve.hxx>
#endif
#ifndef _PColPGeom2d_HArray1OfBoundedCurve_HeaderFile
#include <PColPGeom2d_HArray1OfBoundedCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::New() const
{
  return new PColPGeom2d_HArray1OfBoundedCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::SAdd(const Handle(PColPGeom2d_HArray1OfBoundedCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom2d_HArray1OfBoundedCurve")) {
         ShapeSchema_PColPGeom2d_FieldOfHArray1OfBoundedCurve::SAdd(p->_CSFDB_GetPColPGeom2d_HArray1OfBoundedCurveData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::SAdd((Handle(PColPGeom2d_HArray1OfBoundedCurve)&)p,theSchema);
}

void ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom2d_HArray1OfBoundedCurve) &pp = (Handle(PColPGeom2d_HArray1OfBoundedCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom2d_HArray1OfBoundedCurveLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom2d_HArray1OfBoundedCurveUpperBound());
    ShapeSchema_PColPGeom2d_FieldOfHArray1OfBoundedCurve::SWrite(pp->_CSFDB_GetPColPGeom2d_HArray1OfBoundedCurveData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom2d_HArray1OfBoundedCurve) &pp = (Handle(PColPGeom2d_HArray1OfBoundedCurve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom2d_HArray1OfBoundedCurveLowerBound;
    f.GetInteger(PColPGeom2d_HArray1OfBoundedCurveLowerBound);
    pp->_CSFDB_SetPColPGeom2d_HArray1OfBoundedCurveLowerBound(PColPGeom2d_HArray1OfBoundedCurveLowerBound);

    Standard_Integer PColPGeom2d_HArray1OfBoundedCurveUpperBound;
    f.GetInteger(PColPGeom2d_HArray1OfBoundedCurveUpperBound);
    pp->_CSFDB_SetPColPGeom2d_HArray1OfBoundedCurveUpperBound(PColPGeom2d_HArray1OfBoundedCurveUpperBound);

    ShapeSchema_PColPGeom2d_FieldOfHArray1OfBoundedCurve::SRead((PColPGeom2d_FieldOfHArray1OfBoundedCurve&)pp->_CSFDB_GetPColPGeom2d_HArray1OfBoundedCurveData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom2d_HArray1OfBoundedCurve::SRead(p,f,theSchema);
}
