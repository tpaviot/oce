#ifndef _ShapeSchema_PGeom2d_BezierCurve_HeaderFile
#include <ShapeSchema_PGeom2d_BezierCurve.hxx>
#endif
#ifndef _PGeom2d_BezierCurve_HeaderFile
#include <PGeom2d_BezierCurve.hxx>
#endif
#include <ShapeSchema_PGeom2d_BezierCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_BezierCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_BezierCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_BezierCurve::New() const
{
  return new PGeom2d_BezierCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_BezierCurve::SAdd(const Handle(PGeom2d_BezierCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_BezierCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_BezierCurvepoles());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_BezierCurveweights());

    }
  }
}

void ShapeSchema_PGeom2d_BezierCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_BezierCurve::SAdd((Handle(PGeom2d_BezierCurve)&)p,theSchema);
}

void ShapeSchema_PGeom2d_BezierCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_BezierCurve) &pp = (Handle(PGeom2d_BezierCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPGeom2d_BezierCurverational());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_BezierCurvepoles(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_BezierCurveweights(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_BezierCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_BezierCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_BezierCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_BezierCurve) &pp = (Handle(PGeom2d_BezierCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PGeom2d_BezierCurverational;
    f.GetBoolean(PGeom2d_BezierCurverational);
    pp->_CSFDB_SetPGeom2d_BezierCurverational(PGeom2d_BezierCurverational);

    Handle(PColgp_HArray1OfPnt2d) PGeom2d_BezierCurvepoles;

    theSchema->ReadPersistentReference(PGeom2d_BezierCurvepoles,f);
    pp->_CSFDB_SetPGeom2d_BezierCurvepoles(PGeom2d_BezierCurvepoles);

    Handle(PColStd_HArray1OfReal) PGeom2d_BezierCurveweights;

    theSchema->ReadPersistentReference(PGeom2d_BezierCurveweights,f);
    pp->_CSFDB_SetPGeom2d_BezierCurveweights(PGeom2d_BezierCurveweights);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_BezierCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_BezierCurve::SRead(p,f,theSchema);
}
