#ifndef _ShapeSchema_PBRep_GCurve_HeaderFile
#include <ShapeSchema_PBRep_GCurve.hxx>
#endif
#ifndef _PBRep_GCurve_HeaderFile
#include <PBRep_GCurve.hxx>
#endif
#include <ShapeSchema_PBRep_GCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_GCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_GCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_GCurve::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PBRep_GCurve::SAdd(const Handle(PBRep_GCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_GCurve")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());

    }
  }
}

void ShapeSchema_PBRep_GCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_GCurve::SAdd((Handle(PBRep_GCurve)&)p,theSchema);
}

void ShapeSchema_PBRep_GCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_GCurve) &pp = (Handle(PBRep_GCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
  f.PutReal(pp->_CSFDB_GetPBRep_GCurvemyFirst());
  f.PutReal(pp->_CSFDB_GetPBRep_GCurvemyLast());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_GCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_GCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_GCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_GCurve) &pp = (Handle(PBRep_GCurve)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    Standard_Real PBRep_GCurvemyFirst;
    f.GetReal(PBRep_GCurvemyFirst);
    pp->_CSFDB_SetPBRep_GCurvemyFirst(PBRep_GCurvemyFirst);

    Standard_Real PBRep_GCurvemyLast;
    f.GetReal(PBRep_GCurvemyLast);
    pp->_CSFDB_SetPBRep_GCurvemyLast(PBRep_GCurvemyLast);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_GCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_GCurve::SRead(p,f,theSchema);
}
