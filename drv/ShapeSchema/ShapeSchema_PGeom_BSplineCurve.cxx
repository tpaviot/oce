#ifndef _ShapeSchema_PGeom_BSplineCurve_HeaderFile
#include <ShapeSchema_PGeom_BSplineCurve.hxx>
#endif
#ifndef _PGeom_BSplineCurve_HeaderFile
#include <PGeom_BSplineCurve.hxx>
#endif
#include <ShapeSchema_PGeom_BSplineCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PGeom_BSplineCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PGeom_BSplineCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PGeom_BSplineCurve::New() const
{
  return new PGeom_BSplineCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PGeom_BSplineCurve::SAdd(const Handle(PGeom_BSplineCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PGeom_BSplineCurve")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineCurvepoles());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineCurveweights());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineCurveknots());
   theSchema->PersistentToAdd(p->_CSFDB_GetPGeom_BSplineCurvemultiplicities());

    }
  }
}

void ShapeSchema_PGeom_BSplineCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PGeom_BSplineCurve::SAdd((Handle(PGeom_BSplineCurve)&)p,theSchema);
}

void ShapeSchema_PGeom_BSplineCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BSplineCurve) &pp = (Handle(PGeom_BSplineCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPGeom_BSplineCurverational());
  f.PutBoolean(pp->_CSFDB_GetPGeom_BSplineCurveperiodic());
  f.PutInteger(pp->_CSFDB_GetPGeom_BSplineCurvespineDegree());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineCurvepoles(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineCurveweights(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineCurveknots(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPGeom_BSplineCurvemultiplicities(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PGeom_BSplineCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PGeom_BSplineCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PGeom_BSplineCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PGeom_BSplineCurve) &pp = (Handle(PGeom_BSplineCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PGeom_BSplineCurverational;
    f.GetBoolean(PGeom_BSplineCurverational);
    pp->_CSFDB_SetPGeom_BSplineCurverational(PGeom_BSplineCurverational);

    Standard_Boolean PGeom_BSplineCurveperiodic;
    f.GetBoolean(PGeom_BSplineCurveperiodic);
    pp->_CSFDB_SetPGeom_BSplineCurveperiodic(PGeom_BSplineCurveperiodic);

    Standard_Integer PGeom_BSplineCurvespineDegree;
    f.GetInteger(PGeom_BSplineCurvespineDegree);
    pp->_CSFDB_SetPGeom_BSplineCurvespineDegree(PGeom_BSplineCurvespineDegree);

    Handle(PColgp_HArray1OfPnt) PGeom_BSplineCurvepoles;

    theSchema->ReadPersistentReference(PGeom_BSplineCurvepoles,f);
    pp->_CSFDB_SetPGeom_BSplineCurvepoles(PGeom_BSplineCurvepoles);

    Handle(PColStd_HArray1OfReal) PGeom_BSplineCurveweights;

    theSchema->ReadPersistentReference(PGeom_BSplineCurveweights,f);
    pp->_CSFDB_SetPGeom_BSplineCurveweights(PGeom_BSplineCurveweights);

    Handle(PColStd_HArray1OfReal) PGeom_BSplineCurveknots;

    theSchema->ReadPersistentReference(PGeom_BSplineCurveknots,f);
    pp->_CSFDB_SetPGeom_BSplineCurveknots(PGeom_BSplineCurveknots);

    Handle(PColStd_HArray1OfInteger) PGeom_BSplineCurvemultiplicities;

    theSchema->ReadPersistentReference(PGeom_BSplineCurvemultiplicities,f);
    pp->_CSFDB_SetPGeom_BSplineCurvemultiplicities(PGeom_BSplineCurvemultiplicities);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PGeom_BSplineCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PGeom_BSplineCurve::SRead(p,f,theSchema);
}
