#ifndef _ShapeSchema_PTopoDS_Compound_HeaderFile
#include <ShapeSchema_PTopoDS_Compound.hxx>
#endif
#ifndef _PTopoDS_Compound_HeaderFile
#include <PTopoDS_Compound.hxx>
#endif
#include <ShapeSchema_PTopoDS_Compound.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_Compound,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_Compound,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_Compound::New() const
{
  return new PTopoDS_Compound(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopoDS_Compound::SAdd(const Handle(PTopoDS_Compound)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_Compound")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_ExternShareablemyEntry());
   theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_HShapemyTShape());
   ShapeSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPTopoDS_HShapemyLocation(),theSchema);

    }
  }
}

void ShapeSchema_PTopoDS_Compound::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_Compound::SAdd((Handle(PTopoDS_Compound)&)p,theSchema);
}

void ShapeSchema_PTopoDS_Compound::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_Compound) &pp = (Handle(PTopoDS_Compound)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_ExternShareablemyEntry(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_HShapemyTShape(),f);
    ShapeSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPTopoDS_HShapemyLocation(),f,theSchema);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_HShapemyOrient());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_Compound::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_Compound::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_Compound::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_Compound) &pp = (Handle(PTopoDS_Compound)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) ObjMgt_ExternShareablemyEntry;

    theSchema->ReadPersistentReference(ObjMgt_ExternShareablemyEntry,f);
    pp->_CSFDB_SetObjMgt_ExternShareablemyEntry(ObjMgt_ExternShareablemyEntry);

    Handle(PTopoDS_TShape) PTopoDS_HShapemyTShape;

    theSchema->ReadPersistentReference(PTopoDS_HShapemyTShape,f);
    pp->_CSFDB_SetPTopoDS_HShapemyTShape(PTopoDS_HShapemyTShape);

    ShapeSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPTopoDS_HShapemyLocation(),f,theSchema);

    TopAbs_Orientation PTopoDS_HShapemyOrient;
    Standard_Integer i_CSFDB_PTopoDS_HShapemyOrient;
    f.GetInteger(i_CSFDB_PTopoDS_HShapemyOrient);
    PTopoDS_HShapemyOrient = (TopAbs_Orientation)i_CSFDB_PTopoDS_HShapemyOrient;
    pp->_CSFDB_SetPTopoDS_HShapemyOrient(PTopoDS_HShapemyOrient);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_Compound::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_Compound::SRead(p,f,theSchema);
}
