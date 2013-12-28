#ifndef _ShapeSchema_PBRep_TVertex_HeaderFile
#include <ShapeSchema_PBRep_TVertex.hxx>
#endif
#ifndef _PBRep_TVertex_HeaderFile
#include <PBRep_TVertex.hxx>
#endif
#include <ShapeSchema_PBRep_TVertex.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_TVertex,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_TVertex,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_TVertex::New() const
{
  return new PBRep_TVertex(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_TVertex::SAdd(const Handle(PBRep_TVertex)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_TVertex")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TVertexmyPoints());

    }
  }
}

void ShapeSchema_PBRep_TVertex::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_TVertex::SAdd((Handle(PBRep_TVertex)&)p,theSchema);
}

void ShapeSchema_PBRep_TVertex::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TVertex) &pp = (Handle(PBRep_TVertex)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());
  f.PutReal(pp->_CSFDB_GetPBRep_TVertexmyTolerance());
    ShapeSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPBRep_TVertexmyPnt(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TVertexmyPoints(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_TVertex::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_TVertex::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_TVertex::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TVertex) &pp = (Handle(PBRep_TVertex)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfHShape) PTopoDS_TShapemyShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShapemyShapes,f);
    pp->_CSFDB_SetPTopoDS_TShapemyShapes(PTopoDS_TShapemyShapes);

    Standard_Integer PTopoDS_TShapemyFlags;
    f.GetInteger(PTopoDS_TShapemyFlags);
    pp->_CSFDB_SetPTopoDS_TShapemyFlags(PTopoDS_TShapemyFlags);

    Standard_Real PBRep_TVertexmyTolerance;
    f.GetReal(PBRep_TVertexmyTolerance);
    pp->_CSFDB_SetPBRep_TVertexmyTolerance(PBRep_TVertexmyTolerance);

    ShapeSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPBRep_TVertexmyPnt(),f,theSchema);

    Handle(PBRep_PointRepresentation) PBRep_TVertexmyPoints;

    theSchema->ReadPersistentReference(PBRep_TVertexmyPoints,f);
    pp->_CSFDB_SetPBRep_TVertexmyPoints(PBRep_TVertexmyPoints);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_TVertex::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_TVertex::SRead(p,f,theSchema);
}
