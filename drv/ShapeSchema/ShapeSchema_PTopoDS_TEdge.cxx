#ifndef _ShapeSchema_PTopoDS_TEdge_HeaderFile
#include <ShapeSchema_PTopoDS_TEdge.hxx>
#endif
#ifndef _PTopoDS_TEdge_HeaderFile
#include <PTopoDS_TEdge.hxx>
#endif
#include <ShapeSchema_PTopoDS_TEdge.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_TEdge,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_TEdge,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_TEdge::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PTopoDS_TEdge::SAdd(const Handle(PTopoDS_TEdge)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_TEdge")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());

    }
  }
}

void ShapeSchema_PTopoDS_TEdge::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_TEdge::SAdd((Handle(PTopoDS_TEdge)&)p,theSchema);
}

void ShapeSchema_PTopoDS_TEdge::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TEdge) &pp = (Handle(PTopoDS_TEdge)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TEdge::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_TEdge::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_TEdge::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TEdge) &pp = (Handle(PTopoDS_TEdge)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfHShape) PTopoDS_TShapemyShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShapemyShapes,f);
    pp->_CSFDB_SetPTopoDS_TShapemyShapes(PTopoDS_TShapemyShapes);

    Standard_Integer PTopoDS_TShapemyFlags;
    f.GetInteger(PTopoDS_TShapemyFlags);
    pp->_CSFDB_SetPTopoDS_TShapemyFlags(PTopoDS_TShapemyFlags);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TEdge::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_TEdge::SRead(p,f,theSchema);
}
