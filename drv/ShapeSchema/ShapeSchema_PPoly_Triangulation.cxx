#ifndef _ShapeSchema_PPoly_Triangulation_HeaderFile
#include <ShapeSchema_PPoly_Triangulation.hxx>
#endif
#ifndef _PPoly_Triangulation_HeaderFile
#include <PPoly_Triangulation.hxx>
#endif
#include <ShapeSchema_PPoly_Triangulation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PPoly_Triangulation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PPoly_Triangulation,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PPoly_Triangulation::New() const
{
  return new PPoly_Triangulation(Storage_stCONSTclCOM());
}

void ShapeSchema_PPoly_Triangulation::SAdd(const Handle(PPoly_Triangulation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPoly_Triangulation")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_TriangulationmyNodes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_TriangulationmyUVNodes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPPoly_TriangulationmyTriangles());

    }
  }
}

void ShapeSchema_PPoly_Triangulation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PPoly_Triangulation::SAdd((Handle(PPoly_Triangulation)&)p,theSchema);
}

void ShapeSchema_PPoly_Triangulation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_Triangulation) &pp = (Handle(PPoly_Triangulation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPPoly_TriangulationmyDeflection());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_TriangulationmyNodes(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_TriangulationmyUVNodes(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPoly_TriangulationmyTriangles(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PPoly_Triangulation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PPoly_Triangulation::SWrite(p,f,theSchema);
}


void ShapeSchema_PPoly_Triangulation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPoly_Triangulation) &pp = (Handle(PPoly_Triangulation)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PPoly_TriangulationmyDeflection;
    f.GetReal(PPoly_TriangulationmyDeflection);
    pp->_CSFDB_SetPPoly_TriangulationmyDeflection(PPoly_TriangulationmyDeflection);

    Handle(PColgp_HArray1OfPnt) PPoly_TriangulationmyNodes;

    theSchema->ReadPersistentReference(PPoly_TriangulationmyNodes,f);
    pp->_CSFDB_SetPPoly_TriangulationmyNodes(PPoly_TriangulationmyNodes);

    Handle(PColgp_HArray1OfPnt2d) PPoly_TriangulationmyUVNodes;

    theSchema->ReadPersistentReference(PPoly_TriangulationmyUVNodes,f);
    pp->_CSFDB_SetPPoly_TriangulationmyUVNodes(PPoly_TriangulationmyUVNodes);

    Handle(PPoly_HArray1OfTriangle) PPoly_TriangulationmyTriangles;

    theSchema->ReadPersistentReference(PPoly_TriangulationmyTriangles,f);
    pp->_CSFDB_SetPPoly_TriangulationmyTriangles(PPoly_TriangulationmyTriangles);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PPoly_Triangulation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PPoly_Triangulation::SRead(p,f,theSchema);
}
