#ifndef _ShapeSchema_PBRep_PolygonOnTriangulation_HeaderFile
#include <ShapeSchema_PBRep_PolygonOnTriangulation.hxx>
#endif
#ifndef _PBRep_PolygonOnTriangulation_HeaderFile
#include <PBRep_PolygonOnTriangulation.hxx>
#endif
#include <ShapeSchema_PBRep_PolygonOnTriangulation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_PolygonOnTriangulation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_PolygonOnTriangulation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_PolygonOnTriangulation::New() const
{
  return new PBRep_PolygonOnTriangulation(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_PolygonOnTriangulation::SAdd(const Handle(PBRep_PolygonOnTriangulation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_PolygonOnTriangulation")) {
         ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),theSchema);
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_CurveRepresentationmyNext());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnTriangulationmyPolygon());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_PolygonOnTriangulationmyTriangulation());

    }
  }
}

void ShapeSchema_PBRep_PolygonOnTriangulation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_PolygonOnTriangulation::SAdd((Handle(PBRep_PolygonOnTriangulation)&)p,theSchema);
}

void ShapeSchema_PBRep_PolygonOnTriangulation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnTriangulation) &pp = (Handle(PBRep_PolygonOnTriangulation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPBRep_CurveRepresentationmyLocation(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_CurveRepresentationmyNext(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnTriangulationmyPolygon(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_PolygonOnTriangulationmyTriangulation(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnTriangulation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_PolygonOnTriangulation::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_PolygonOnTriangulation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_PolygonOnTriangulation) &pp = (Handle(PBRep_PolygonOnTriangulation)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

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

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_PolygonOnTriangulation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_PolygonOnTriangulation::SRead(p,f,theSchema);
}
