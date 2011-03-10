#ifndef _ShapeSchema_PBRep_PolygonOnClosedTriangulation_HeaderFile
#include <ShapeSchema_PBRep_PolygonOnClosedTriangulation.hxx>
#endif
#ifndef _PBRep_PolygonOnClosedTriangulation_HeaderFile
#include <PBRep_PolygonOnClosedTriangulation.hxx>
#endif
#include <ShapeSchema_PBRep_PolygonOnClosedTriangulation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PolygonOnClosedTriangulation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PolygonOnClosedTriangulation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PolygonOnClosedTriangulation::New() const
{
  return new PBRep_PolygonOnClosedTriangulation(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PolygonOnClosedTriangulation::SAdd(const Handle(PBRep_PolygonOnClosedTriangulation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PolygonOnClosedTriangulation")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnTriangulationmyPolygon());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnTriangulationmyTriangulation());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnClosedTriangulationmyPolygon2());

    }
  }
}

void ShapeSchema_PBRep_PolygonOnClosedTriangulation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PolygonOnClosedTriangulation::SAdd((Handle(PBRep_PolygonOnClosedTriangulation)&)p,theSchema);
}

void ShapeSchema_PBRep_PolygonOnClosedTriangulation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnClosedTriangulation) &pp = (Handle(PBRep_PolygonOnClosedTriangulation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnTriangulationmyPolygon(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnTriangulationmyTriangulation(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnClosedTriangulationmyPolygon2(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnClosedTriangulation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PolygonOnClosedTriangulation::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PolygonOnClosedTriangulation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnClosedTriangulation) &pp = (Handle(PBRep_PolygonOnClosedTriangulation)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);

    Handle(PBRep_CurveRepresentation) PBRep_CurveRepresentationmyNext;

    theSchema->ReadPersistentReference(PBRep_CurveRepresentationmyNext,f);
    pp->_CSFDB_SetPBRep_CurveRepresentationmyNext(PBRep_CurveRepresentationmyNext);

    Handle(PPoly_PolygonOnTriangulation) PBRep_PolygonOnTriangulationmyPolygon;

    theSchema->ReadPersistentReference(PBRep_PolygonOnTriangulationmyPolygon,f);
    pp->_CSFDB_SetPBRep_PolygonOnTriangulationmyPolygon(PBRep_PolygonOnTriangulationmyPolygon);

    Handle(PPoly_Triangulation) PBRep_PolygonOnTriangulationmyTriangulation;

    theSchema->ReadPersistentReference(PBRep_PolygonOnTriangulationmyTriangulation,f);
    pp->_CSFDB_SetPBRep_PolygonOnTriangulationmyTriangulation(PBRep_PolygonOnTriangulationmyTriangulation);

    Handle(PPoly_PolygonOnTriangulation) PBRep_PolygonOnClosedTriangulationmyPolygon2;

    theSchema->ReadPersistentReference(PBRep_PolygonOnClosedTriangulationmyPolygon2,f);
    pp->_CSFDB_SetPBRep_PolygonOnClosedTriangulationmyPolygon2(PBRep_PolygonOnClosedTriangulationmyPolygon2);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnClosedTriangulation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PolygonOnClosedTriangulation::SRead(p,f,theSchema);
}
