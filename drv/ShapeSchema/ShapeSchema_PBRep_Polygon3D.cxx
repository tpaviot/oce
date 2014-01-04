#ifndef _ShapeSchema_PBRep_Polygon3D_HeaderFile
#include <ShapeSchema_PBRep_Polygon3D.hxx>
#endif
#ifndef _PBRep_Polygon3D_HeaderFile
#include <PBRep_Polygon3D.hxx>
#endif
#include <ShapeSchema_PBRep_Polygon3D.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_Polygon3D,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_Polygon3D,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_Polygon3D::New() const
{
  return new PBRep_Polygon3D(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_Polygon3D::SAdd(const Handle(PBRep_Polygon3D)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_Polygon3D")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_Polygon3DmyPolygon3D());

    }
  }
}

void ShapeSchema_PBRep_Polygon3D::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_Polygon3D::SAdd((Handle(PBRep_Polygon3D)&)p,theSchema);
}

void ShapeSchema_PBRep_Polygon3D::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_Polygon3D) &pp = (Handle(PBRep_Polygon3D)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_Polygon3DmyPolygon3D(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_Polygon3D::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_Polygon3D::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_Polygon3D::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_Polygon3D) &pp = (Handle(PBRep_Polygon3D)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    Handle(PPoly_Polygon3D) PBRep_Polygon3DmyPolygon3D;

    theSchema->ReadPersistentReference(PBRep_Polygon3DmyPolygon3D,f);
    pp->_CSFDB_SetPBRep_Polygon3DmyPolygon3D(PBRep_Polygon3DmyPolygon3D);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_Polygon3D::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_Polygon3D::SRead(p,f,theSchema);
}
