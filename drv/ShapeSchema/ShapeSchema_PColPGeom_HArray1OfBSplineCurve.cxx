#ifndef _ShapeSchema_PColPGeom_HArray1OfBSplineCurve_HeaderFile
#include <ShapeSchema_PColPGeom_HArray1OfBSplineCurve.hxx>
#endif
#ifndef _PColPGeom_HArray1OfBSplineCurve_HeaderFile
#include <PColPGeom_HArray1OfBSplineCurve.hxx>
#endif
#include <ShapeSchema_PColPGeom_HArray1OfBSplineCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColPGeom_HArray1OfBSplineCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColPGeom_HArray1OfBSplineCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColPGeom_HArray1OfBSplineCurve::New() const
{
  return new PColPGeom_HArray1OfBSplineCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PColPGeom_HArray1OfBSplineCurve::SAdd(const Handle(PColPGeom_HArray1OfBSplineCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColPGeom_HArray1OfBSplineCurve")) {
         ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve::SAdd(p->_CSFDB_GetPColPGeom_HArray1OfBSplineCurveData(),theSchema);

    }
  }
}

void ShapeSchema_PColPGeom_HArray1OfBSplineCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColPGeom_HArray1OfBSplineCurve::SAdd((Handle(PColPGeom_HArray1OfBSplineCurve)&)p,theSchema);
}

void ShapeSchema_PColPGeom_HArray1OfBSplineCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfBSplineCurve) &pp = (Handle(PColPGeom_HArray1OfBSplineCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfBSplineCurveLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColPGeom_HArray1OfBSplineCurveUpperBound());
    ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve::SWrite(pp->_CSFDB_GetPColPGeom_HArray1OfBSplineCurveData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfBSplineCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColPGeom_HArray1OfBSplineCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PColPGeom_HArray1OfBSplineCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColPGeom_HArray1OfBSplineCurve) &pp = (Handle(PColPGeom_HArray1OfBSplineCurve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColPGeom_HArray1OfBSplineCurveLowerBound;
    f.GetInteger(PColPGeom_HArray1OfBSplineCurveLowerBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfBSplineCurveLowerBound(PColPGeom_HArray1OfBSplineCurveLowerBound);

    Standard_Integer PColPGeom_HArray1OfBSplineCurveUpperBound;
    f.GetInteger(PColPGeom_HArray1OfBSplineCurveUpperBound);
    pp->_CSFDB_SetPColPGeom_HArray1OfBSplineCurveUpperBound(PColPGeom_HArray1OfBSplineCurveUpperBound);

    ShapeSchema_PColPGeom_FieldOfHArray1OfBSplineCurve::SRead((PColPGeom_FieldOfHArray1OfBSplineCurve&)pp->_CSFDB_GetPColPGeom_HArray1OfBSplineCurveData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColPGeom_HArray1OfBSplineCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColPGeom_HArray1OfBSplineCurve::SRead(p,f,theSchema);
}
