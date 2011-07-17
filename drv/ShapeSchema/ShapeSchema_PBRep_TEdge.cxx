#ifndef _ShapeSchema_PBRep_TEdge_HeaderFile
#include <ShapeSchema_PBRep_TEdge.hxx>
#endif
#ifndef _PBRep_TEdge_HeaderFile
#include <PBRep_TEdge.hxx>
#endif
#include <ShapeSchema_PBRep_TEdge.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_TEdge,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_TEdge,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_TEdge::New() const
{
  return new PBRep_TEdge(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_TEdge::SAdd(const Handle(PBRep_TEdge)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_TEdge")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TEdgemyCurves());

    }
  }
}

void ShapeSchema_PBRep_TEdge::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_TEdge::SAdd((Handle(PBRep_TEdge)&)p,theSchema);
}

void ShapeSchema_PBRep_TEdge::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TEdge) &pp = (Handle(PBRep_TEdge)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());
  f.PutReal(pp->_CSFDB_GetPBRep_TEdgemyTolerance());
  f.PutInteger(pp->_CSFDB_GetPBRep_TEdgemyFlags());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TEdgemyCurves(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_TEdge::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_TEdge::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_TEdge::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TEdge) &pp = (Handle(PBRep_TEdge)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfHShape) PTopoDS_TShapemyShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShapemyShapes,f);
    pp->_CSFDB_SetPTopoDS_TShapemyShapes(PTopoDS_TShapemyShapes);

    Standard_Integer PTopoDS_TShapemyFlags;
    f.GetInteger(PTopoDS_TShapemyFlags);
    pp->_CSFDB_SetPTopoDS_TShapemyFlags(PTopoDS_TShapemyFlags);

    Standard_Real PBRep_TEdgemyTolerance;
    f.GetReal(PBRep_TEdgemyTolerance);
    pp->_CSFDB_SetPBRep_TEdgemyTolerance(PBRep_TEdgemyTolerance);

    Standard_Integer PBRep_TEdgemyFlags;
    f.GetInteger(PBRep_TEdgemyFlags);
    pp->_CSFDB_SetPBRep_TEdgemyFlags(PBRep_TEdgemyFlags);

    Handle(PBRep_CurveRepresentation) PBRep_TEdgemyCurves;

    theSchema->ReadPersistentReference(PBRep_TEdgemyCurves,f);
    pp->_CSFDB_SetPBRep_TEdgemyCurves(PBRep_TEdgemyCurves);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_TEdge::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_TEdge::SRead(p,f,theSchema);
}
