#ifndef _ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve_HeaderFile
#include <ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve.hxx>
#endif
#ifndef _PColPGeom2d_HArray1OfBSplineCurve_HeaderFile
#include <PColPGeom2d_HArray1OfBSplineCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::New() const
{
  return new PColPGeom2d_HArray1OfBSplineCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::SAdd(const Handle(PColPGeom2d_HArray1OfBSplineCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom2d_HArray1OfBSplineCurve")) {
         ShapeSchema_PColPGeom2d_FieldOfHArray1OfBSplineCurve::SAdd(p->_CSFDB_GetPColPGeom2d_HArray1OfBSplineCurveData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::SAdd((Handle(PColPGeom2d_HArray1OfBSplineCurve)&)p,theSchema);
}

void ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom2d_HArray1OfBSplineCurve) &pp = (Handle(PColPGeom2d_HArray1OfBSplineCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom2d_HArray1OfBSplineCurveLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom2d_HArray1OfBSplineCurveUpperBound());
    ShapeSchema_PColPGeom2d_FieldOfHArray1OfBSplineCurve::SWrite(pp->_CSFDB_GetPColPGeom2d_HArray1OfBSplineCurveData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom2d_HArray1OfBSplineCurve) &pp = (Handle(PColPGeom2d_HArray1OfBSplineCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom2d_HArray1OfBSplineCurveLowerBound;
    f.GetInteger(PColPGeom2d_HArray1OfBSplineCurveLowerBound);
    pp->_CSFDB_SetPColPGeom2d_HArray1OfBSplineCurveLowerBound(PColPGeom2d_HArray1OfBSplineCurveLowerBound);

    Standard_Integer PColPGeom2d_HArray1OfBSplineCurveUpperBound;
    f.GetInteger(PColPGeom2d_HArray1OfBSplineCurveUpperBound);
    pp->_CSFDB_SetPColPGeom2d_HArray1OfBSplineCurveUpperBound(PColPGeom2d_HArray1OfBSplineCurveUpperBound);

    ShapeSchema_PColPGeom2d_FieldOfHArray1OfBSplineCurve::SRead((PColPGeom2d_FieldOfHArray1OfBSplineCurve&)pp->_CSFDB_GetPColPGeom2d_HArray1OfBSplineCurveData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom2d_HArray1OfBSplineCurve::SRead(p,f,theSchema);
}
