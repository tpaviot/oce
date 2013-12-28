#ifndef _ShapeSchema_PBRep_Curve3D_HeaderFile
#include <ShapeSchema_PBRep_Curve3D.hxx>
#endif
#ifndef _PBRep_Curve3D_HeaderFile
#include <PBRep_Curve3D.hxx>
#endif
#include <ShapeSchema_PBRep_Curve3D.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_Curve3D,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_Curve3D,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_Curve3D::New() const
{
  return new PBRep_Curve3D(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_Curve3D::SAdd(const Handle(PBRep_Curve3D)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_Curve3D")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_Curve3DmyCurve3D());

    }
  }
}

void ShapeSchema_PBRep_Curve3D::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_Curve3D::SAdd((Handle(PBRep_Curve3D)&)p,theSchema);
}

void ShapeSchema_PBRep_Curve3D::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_Curve3D) &pp = (Handle(PBRep_Curve3D)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
  f.PutReal(pp->_CSFDB_GetPBRep_GCurvemyFirst());
  f.PutReal(pp->_CSFDB_GetPBRep_GCurvemyLast());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_Curve3DmyCurve3D(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_Curve3D::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_Curve3D::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_Curve3D::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_Curve3D) &pp = (Handle(PBRep_Curve3D)&)p;

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

    Handle(PGeom_Curve) PBRep_Curve3DmyCurve3D;

    theSchema->ReadPersistentReference(PBRep_Curve3DmyCurve3D,f);
    pp->_CSFDB_SetPBRep_Curve3DmyCurve3D(PBRep_Curve3DmyCurve3D);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_Curve3D::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_Curve3D::SRead(p,f,theSchema);
}
