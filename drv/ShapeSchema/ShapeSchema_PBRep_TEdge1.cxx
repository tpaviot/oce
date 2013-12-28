#ifndef _ShapeSchema_PBRep_TEdge1_HeaderFile
#include <ShapeSchema_PBRep_TEdge1.hxx>
#endif
#ifndef _PBRep_TEdge1_HeaderFile
#include <PBRep_TEdge1.hxx>
#endif
#include <ShapeSchema_PBRep_TEdge1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PBRep_TEdge1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PBRep_TEdge1,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PBRep_TEdge1::New() const
{
  return new PBRep_TEdge1(Storage_stCONSTclCOM());
}

void ShapeSchema_PBRep_TEdge1::SAdd(const Handle(PBRep_TEdge1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PBRep_TEdge1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShape1myShapes());
   theSchema->PersistentToAdd(p->_CSFDB_GetPBRep_TEdge1myCurves());

    }
  }
}

void ShapeSchema_PBRep_TEdge1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PBRep_TEdge1::SAdd((Handle(PBRep_TEdge1)&)p,theSchema);
}

void ShapeSchema_PBRep_TEdge1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TEdge1) &pp = (Handle(PBRep_TEdge1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShape1myShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShape1myFlags());
  f.PutReal(pp->_CSFDB_GetPBRep_TEdge1myTolerance());
  f.PutInteger(pp->_CSFDB_GetPBRep_TEdge1myFlags());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPBRep_TEdge1myCurves(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PBRep_TEdge1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PBRep_TEdge1::SWrite(p,f,theSchema);
}


void ShapeSchema_PBRep_TEdge1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PBRep_TEdge1) &pp = (Handle(PBRep_TEdge1)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfShape1) PTopoDS_TShape1myShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShape1myShapes,f);
    pp->_CSFDB_SetPTopoDS_TShape1myShapes(PTopoDS_TShape1myShapes);

    Standard_Integer PTopoDS_TShape1myFlags;
    f.GetInteger(PTopoDS_TShape1myFlags);
    pp->_CSFDB_SetPTopoDS_TShape1myFlags(PTopoDS_TShape1myFlags);

    Standard_Real PBRep_TEdge1myTolerance;
    f.GetReal(PBRep_TEdge1myTolerance);
    pp->_CSFDB_SetPBRep_TEdge1myTolerance(PBRep_TEdge1myTolerance);

    Standard_Integer PBRep_TEdge1myFlags;
    f.GetInteger(PBRep_TEdge1myFlags);
    pp->_CSFDB_SetPBRep_TEdge1myFlags(PBRep_TEdge1myFlags);

    Handle(PBRep_CurveRepresentation) PBRep_TEdge1myCurves;

    theSchema->ReadPersistentReference(PBRep_TEdge1myCurves,f);
    pp->_CSFDB_SetPBRep_TEdge1myCurves(PBRep_TEdge1myCurves);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PBRep_TEdge1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PBRep_TEdge1::SRead(p,f,theSchema);
}
