#ifndef _ShapeSchema_ObjMgt_ExternRef_HeaderFile
#include <ShapeSchema_ObjMgt_ExternRef.hxx>
#endif
#ifndef _ObjMgt_ExternRef_HeaderFile
#include <ObjMgt_ExternRef.hxx>
#endif
#include <ShapeSchema_ObjMgt_ExternRef.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_ObjMgt_ExternRef,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_ObjMgt_ExternRef,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_ObjMgt_ExternRef::New() const
{
  return new ObjMgt_ExternRef(Storage_stCONSTclCOM());
}

void ShapeSchema_ObjMgt_ExternRef::SAdd(const Handle(ObjMgt_ExternRef)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"ObjMgt_ExternRef")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_ExternRefmyEntryId());

    }
  }
}

void ShapeSchema_ObjMgt_ExternRef::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_ObjMgt_ExternRef::SAdd((Handle(ObjMgt_ExternRef)&)p,theSchema);
}

void ShapeSchema_ObjMgt_ExternRef::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_ExternRef) &pp = (Handle(ObjMgt_ExternRef)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_ExternRefmyEntryId(),f);
  f.PutInteger(pp->_CSFDB_GetObjMgt_ExternRefmyBindingIndex());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_ExternRef::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_ObjMgt_ExternRef::SWrite(p,f,theSchema);
}


void ShapeSchema_ObjMgt_ExternRef::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_ExternRef) &pp = (Handle(ObjMgt_ExternRef)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) ObjMgt_ExternRefmyEntryId;

    theSchema->ReadPersistentReference(ObjMgt_ExternRefmyEntryId,f);
    pp->_CSFDB_SetObjMgt_ExternRefmyEntryId(ObjMgt_ExternRefmyEntryId);

    Standard_Integer ObjMgt_ExternRefmyBindingIndex;
    f.GetInteger(ObjMgt_ExternRefmyBindingIndex);
    pp->_CSFDB_SetObjMgt_ExternRefmyBindingIndex(ObjMgt_ExternRefmyBindingIndex);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_ExternRef::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_ObjMgt_ExternRef::SRead(p,f,theSchema);
}
