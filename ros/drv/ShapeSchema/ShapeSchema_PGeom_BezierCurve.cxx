#ifndef _ShapeSchema_PGeom_BezierCurve_HeaderFile
#include <ShapeSchema_PGeom_BezierCurve.hxx>
#endif
#ifndef _PGeom_BezierCurve_HeaderFile
#include <PGeom_BezierCurve.hxx>
#endif
#include <ShapeSchema_PGeom_BezierCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_BezierCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_BezierCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_BezierCurve::New() const
{
  return new PGeom_BezierCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_BezierCurve::SAdd(const Handle(PGeom_BezierCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_BezierCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BezierCurvepoles());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BezierCurveweights());

    }
  }
}

void ShapeSchema_PGeom_BezierCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_BezierCurve::SAdd((Handle(PGeom_BezierCurve)&)p,theSchema);
}

void ShapeSchema_PGeom_BezierCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BezierCurve) &pp = (Handle(PGeom_BezierCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPGeom_BezierCurverational());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BezierCurvepoles(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BezierCurveweights(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_BezierCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_BezierCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_BezierCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BezierCurve) &pp = (Handle(PGeom_BezierCurve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PGeom_BezierCurverational;
    f.GetBoolean(PGeom_BezierCurverational);
    pp->_CSFDB_SetPGeom_BezierCurverational(PGeom_BezierCurverational);

    Handle(PColgp_HArray1OfPnt) PGeom_BezierCurvepoles;

    theSchema->ReadPersistentReference(PGeom_BezierCurvepoles,f);
    pp->_CSFDB_SetPGeom_BezierCurvepoles(PGeom_BezierCurvepoles);

    Handle(PColStd_HArray1OfReal) PGeom_BezierCurveweights;

    theSchema->ReadPersistentReference(PGeom_BezierCurveweights,f);
    pp->_CSFDB_SetPGeom_BezierCurveweights(PGeom_BezierCurveweights);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_BezierCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_BezierCurve::SRead(p,f,theSchema);
}
