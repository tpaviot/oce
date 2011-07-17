#ifndef _ShapeSchema_PBRep_PointOnCurve_HeaderFile
#include <ShapeSchema_PBRep_PointOnCurve.hxx>
#endif
#ifndef _PBRep_PointOnCurve_HeaderFile
#include <PBRep_PointOnCurve.hxx>
#endif
#include <ShapeSchema_PBRep_PointOnCurve.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PointOnCurve,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PointOnCurve,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PointOnCurve::New() const
{
  return new PBRep_PointOnCurve(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PointOnCurve::SAdd(const Handle(PBRep_PointOnCurve)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PointOnCurve")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_PointRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PointOnCurvemyCurve());

    }
  }
}

void ShapeSchema_PBRep_PointOnCurve::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PointOnCurve::SAdd((Handle(PBRep_PointOnCurve)&)p,theSchema);
}

void ShapeSchema_PBRep_PointOnCurve::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointOnCurve) &pp = (Handle(PBRep_PointOnCurve)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);
  f.PutReal(pp->_CSFDB_GetPBRep_PointRepresentationmyParameter());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PointOnCurvemyCurve(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointOnCurve::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PointOnCurve::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PointOnCurve::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PointOnCurve) &pp = (Handle(PBRep_PointOnCurve)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_PointRepresentationmyLocation(),f,theSchema);

    Standard_Real PBRep_PointRepresentationmyParameter;
    f.GetReal(PBRep_PointRepresentationmyParameter);
    pp->_CSFDB_SetPBRep_PointRepresentationmyParameter(PBRep_PointRepresentationmyParameter);

    Handle(PBRep_PointRepresentation) PBRep_PointRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_PointRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_PointRepresentationmyNext(PBRep_PointRepresentationmyNext);

    Handle(PGeom_Curve) PBRep_PointOnCurvemyCurve;

    theSchema->ReadPersistentReference(PBRep_PointOnCurvemyCurve,f);
    pp->_CSFDB_SetPBRep_PointOnCurvemyCurve(PBRep_PointOnCurvemyCurve);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PointOnCurve::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PointOnCurve::SRead(p,f,theSchema);
}
