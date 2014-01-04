#ifndef _ShapeSchema_PPoly_PolygonOnTriangulation_HeaderFile
#include <ShapeSchema_PPoly_PolygonOnTriangulation.hxx>
#endif
#ifndef _PPoly_PolygonOnTriangulation_HeaderFile
#include <PPoly_PolygonOnTriangulation.hxx>
#endif
#include <ShapeSchema_PPoly_PolygonOnTriangulation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PPoly_PolygonOnTriangulation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PPoly_PolygonOnTriangulation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PPoly_PolygonOnTriangulation::New() const
{
  return new PPoly_PolygonOnTriangulation(Storage_stCONSTclCOM());
}

void ShapeSchema_PPoly_PolygonOnTriangulation::SAdd(const Handle(PPoly_PolygonOnTriangulation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPoly_PolygonOnTriangulation")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_PolygonOnTriangulationmyNodes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_PolygonOnTriangulationmyParameters());

    }
  }
}

void ShapeSchema_PPoly_PolygonOnTriangulation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PPoly_PolygonOnTriangulation::SAdd((Handle(PPoly_PolygonOnTriangulation)&)p,theSchema);
}

void ShapeSchema_PPoly_PolygonOnTriangulation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_PolygonOnTriangulation) &pp = (Handle(PPoly_PolygonOnTriangulation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPPoly_PolygonOnTriangulationmyDeflection());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_PolygonOnTriangulationmyNodes(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_PolygonOnTriangulationmyParameters(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PPoly_PolygonOnTriangulation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PPoly_PolygonOnTriangulation::SWrite(p,f,theSchema);
}


void ShapeSchema_PPoly_PolygonOnTriangulation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_PolygonOnTriangulation) &pp = (Handle(PPoly_PolygonOnTriangulation)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PPoly_PolygonOnTriangulationmyDeflection;
    f.GetReal(PPoly_PolygonOnTriangulationmyDeflection);
    pp->_CSFDB_SetPPoly_PolygonOnTriangulationmyDeflection(PPoly_PolygonOnTriangulationmyDeflection);

    Handle(PColStd_HArray1OfInteger) PPoly_PolygonOnTriangulationmyNodes;

    theSchema->ReadPersistentReference(PPoly_PolygonOnTriangulationmyNodes,f);
    pp->_CSFDB_SetPPoly_PolygonOnTriangulationmyNodes(PPoly_PolygonOnTriangulationmyNodes);

    Handle(PColStd_HArray1OfReal) PPoly_PolygonOnTriangulationmyParameters;

    theSchema->ReadPersistentReference(PPoly_PolygonOnTriangulationmyParameters,f);
    pp->_CSFDB_SetPPoly_PolygonOnTriangulationmyParameters(PPoly_PolygonOnTriangulationmyParameters);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PPoly_PolygonOnTriangulation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PPoly_PolygonOnTriangulation::SRead(p,f,theSchema);
}
