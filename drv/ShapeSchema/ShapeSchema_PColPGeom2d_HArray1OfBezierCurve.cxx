#ifndef _ShapeSchema_PColPGeom2d_HArray1OfBezierCurve_HeaderFile
#include <ShapeSchema_PColPGeom2d_HArray1OfBezierCurve.hxx>
#endif
#ifndef _PColPGeom2d_HArray1OfBezierCurve_HeaderFile
#include <PColPGeom2d_HArray1OfBezierCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom2d_HArray1OfBezierCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom2d_HArray1OfBezierCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom2d_HArray1OfBezierCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::New() const
{
  return new PColPGeom2d_HArray1OfBezierCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::SAdd(const Handle(PColPGeom2d_HArray1OfBezierCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom2d_HArray1OfBezierCurve")) {
         ShapeSchema_PColPGeom2d_FieldOfHArray1OfBezierCurve::SAdd(p->_CSFDB_GetPColPGeom2d_HArray1OfBezierCurveData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::SAdd((Handle(PColPGeom2d_HArray1OfBezierCurve)&)p,theSchema);
}

void ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom2d_HArray1OfBezierCurve) &pp = (Handle(PColPGeom2d_HArray1OfBezierCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom2d_HArray1OfBezierCurveLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom2d_HArray1OfBezierCurveUpperBound());
    ShapeSchema_PColPGeom2d_FieldOfHArray1OfBezierCurve::SWrite(pp->_CSFDB_GetPColPGeom2d_HArray1OfBezierCurveData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom2d_HArray1OfBezierCurve) &pp = (Handle(PColPGeom2d_HArray1OfBezierCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom2d_HArray1OfBezierCurveLowerBound;
    f.GetInteger(PColPGeom2d_HArray1OfBezierCurveLowerBound);
    pp->_CSFDB_SetPColPGeom2d_HArray1OfBezierCurveLowerBound(PColPGeom2d_HArray1OfBezierCurveLowerBound);

    Standard_Integer PColPGeom2d_HArray1OfBezierCurveUpperBound;
    f.GetInteger(PColPGeom2d_HArray1OfBezierCurveUpperBound);
    pp->_CSFDB_SetPColPGeom2d_HArray1OfBezierCurveUpperBound(PColPGeom2d_HArray1OfBezierCurveUpperBound);

    ShapeSchema_PColPGeom2d_FieldOfHArray1OfBezierCurve::SRead((PColPGeom2d_FieldOfHArray1OfBezierCurve&)pp->_CSFDB_GetPColPGeom2d_HArray1OfBezierCurveData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom2d_HArray1OfBezierCurve::SRead(p,f,theSchema);
}
