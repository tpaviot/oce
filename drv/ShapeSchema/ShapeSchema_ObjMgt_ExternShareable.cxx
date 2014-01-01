#ifndef _ShapeSchema_ObjMgt_ExternShareable_HeaderFile
#include <ShapeSchema_ObjMgt_ExternShareable.hxx>
#endif
#ifndef _ObjMgt_ExternShareable_HeaderFile
#include <ObjMgt_ExternShareable.hxx>
#endif
#include <ShapeSchema_ObjMgt_ExternShareable.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_ObjMgt_ExternShareable,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_ObjMgt_ExternShareable,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_ObjMgt_ExternShareable::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_ObjMgt_ExternShareable::SAdd(const Handle(ObjMgt_ExternShareable)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"ObjMgt_ExternShareable")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_ExternShareablemyEntry());

    }
  }
}

void ShapeSchema_ObjMgt_ExternShareable::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_ObjMgt_ExternShareable::SAdd((Handle(ObjMgt_ExternShareable)&)p,theSchema);
}

void ShapeSchema_ObjMgt_ExternShareable::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_ExternShareable) &pp = (Handle(ObjMgt_ExternShareable)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_ExternShareablemyEntry(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_ExternShareable::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_ObjMgt_ExternShareable::SWrite(p,f,theSchema);
}


void ShapeSchema_ObjMgt_ExternShareable::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_ExternShareable) &pp = (Handle(ObjMgt_ExternShareable)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) ObjMgt_ExternShareablemyEntry;

    theSchema->ReadPersistentReference(ObjMgt_ExternShareablemyEntry,f);
    pp->_CSFDB_SetObjMgt_ExternShareablemyEntry(ObjMgt_ExternShareablemyEntry);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_ExternShareable::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_ObjMgt_ExternShareable::SRead(p,f,theSchema);
}
