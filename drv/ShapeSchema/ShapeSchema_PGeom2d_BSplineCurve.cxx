#ifndef _ShapeSchema_PGeom2d_BSplineCurve_HeaderFile
#include <ShapeSchema_PGeom2d_BSplineCurve.hxx>
#endif
#ifndef _PGeom2d_BSplineCurve_HeaderFile
#include <PGeom2d_BSplineCurve.hxx>
#endif
#include <ShapeSchema_PGeom2d_BSplineCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom2d_BSplineCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom2d_BSplineCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom2d_BSplineCurve::New() const
{
  return new PGeom2d_BSplineCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom2d_BSplineCurve::SAdd(const Handle(PGeom2d_BSplineCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom2d_BSplineCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_BSplineCurvepoles());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_BSplineCurveweights());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_BSplineCurveknots());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom2d_BSplineCurvemultiplicities());

    }
  }
}

void ShapeSchema_PGeom2d_BSplineCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom2d_BSplineCurve::SAdd((Handle(PGeom2d_BSplineCurve)&)p,theSchema);
}

void ShapeSchema_PGeom2d_BSplineCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_BSplineCurve) &pp = (Handle(PGeom2d_BSplineCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPGeom2d_BSplineCurverational());
  f.PutBoolean(pp->_CSFDB_GetPGeom2d_BSplineCurveperiodic());
  f.PutInteger(pp->_CSFDB_GetPGeom2d_BSplineCurvespineDegree());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_BSplineCurvepoles(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_BSplineCurveweights(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_BSplineCurveknots(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom2d_BSplineCurvemultiplicities(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_BSplineCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom2d_BSplineCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom2d_BSplineCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom2d_BSplineCurve) &pp = (Handle(PGeom2d_BSplineCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PGeom2d_BSplineCurverational;
    f.GetBoolean(PGeom2d_BSplineCurverational);
    pp->_CSFDB_SetPGeom2d_BSplineCurverational(PGeom2d_BSplineCurverational);

    Standard_Boolean PGeom2d_BSplineCurveperiodic;
    f.GetBoolean(PGeom2d_BSplineCurveperiodic);
    pp->_CSFDB_SetPGeom2d_BSplineCurveperiodic(PGeom2d_BSplineCurveperiodic);

    Standard_Integer PGeom2d_BSplineCurvespineDegree;
    f.GetInteger(PGeom2d_BSplineCurvespineDegree);
    pp->_CSFDB_SetPGeom2d_BSplineCurvespineDegree(PGeom2d_BSplineCurvespineDegree);

    Handle(PColgp_HArray1OfPnt2d) PGeom2d_BSplineCurvepoles;

    theSchema->ReadPersistentReference(PGeom2d_BSplineCurvepoles,f);
    pp->_CSFDB_SetPGeom2d_BSplineCurvepoles(PGeom2d_BSplineCurvepoles);

    Handle(PColStd_HArray1OfReal) PGeom2d_BSplineCurveweights;

    theSchema->ReadPersistentReference(PGeom2d_BSplineCurveweights,f);
    pp->_CSFDB_SetPGeom2d_BSplineCurveweights(PGeom2d_BSplineCurveweights);

    Handle(PColStd_HArray1OfReal) PGeom2d_BSplineCurveknots;

    theSchema->ReadPersistentReference(PGeom2d_BSplineCurveknots,f);
    pp->_CSFDB_SetPGeom2d_BSplineCurveknots(PGeom2d_BSplineCurveknots);

    Handle(PColStd_HArray1OfInteger) PGeom2d_BSplineCurvemultiplicities;

    theSchema->ReadPersistentReference(PGeom2d_BSplineCurvemultiplicities,f);
    pp->_CSFDB_SetPGeom2d_BSplineCurvemultiplicities(PGeom2d_BSplineCurvemultiplicities);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom2d_BSplineCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom2d_BSplineCurve::SRead(p,f,theSchema);
}
