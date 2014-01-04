#ifndef _ShapeSchema_ObjMgt_PSeqOfExtRef_HeaderFile
#include <ShapeSchema_ObjMgt_PSeqOfExtRef.hxx>
#endif
#ifndef _ObjMgt_PSeqOfExtRef_HeaderFile
#include <ObjMgt_PSeqOfExtRef.hxx>
#endif
#include <ShapeSchema_ObjMgt_PSeqOfExtRef.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_ObjMgt_PSeqOfExtRef,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_ObjMgt_PSeqOfExtRef,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_ObjMgt_PSeqOfExtRef::New() const
{
  return new ObjMgt_PSeqOfExtRef(Storage_stCONSTclCOM());
}

void ShapeSchema_ObjMgt_PSeqOfExtRef::SAdd(const Handle(ObjMgt_PSeqOfExtRef)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"ObjMgt_PSeqOfExtRef")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_PSeqOfExtRefFirstItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_PSeqOfExtRefLastItem());

    }
  }
}

void ShapeSchema_ObjMgt_PSeqOfExtRef::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_ObjMgt_PSeqOfExtRef::SAdd((Handle(ObjMgt_PSeqOfExtRef)&)p,theSchema);
}

void ShapeSchema_ObjMgt_PSeqOfExtRef::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_PSeqOfExtRef) &pp = (Handle(ObjMgt_PSeqOfExtRef)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_PSeqOfExtRefFirstItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_PSeqOfExtRefLastItem(),f);
  f.PutInteger(pp->_CSFDB_GetObjMgt_PSeqOfExtRefSize());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_PSeqOfExtRef::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_ObjMgt_PSeqOfExtRef::SWrite(p,f,theSchema);
}


void ShapeSchema_ObjMgt_PSeqOfExtRef::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_PSeqOfExtRef) &pp = (Handle(ObjMgt_PSeqOfExtRef)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(ObjMgt_SeqNodeOfPSeqOfExtRef) ObjMgt_PSeqOfExtRefFirstItem;

    theSchema->ReadPersistentReference(ObjMgt_PSeqOfExtRefFirstItem,f);
    pp->_CSFDB_SetObjMgt_PSeqOfExtRefFirstItem(ObjMgt_PSeqOfExtRefFirstItem);

    Handle(ObjMgt_SeqNodeOfPSeqOfExtRef) ObjMgt_PSeqOfExtRefLastItem;

    theSchema->ReadPersistentReference(ObjMgt_PSeqOfExtRefLastItem,f);
    pp->_CSFDB_SetObjMgt_PSeqOfExtRefLastItem(ObjMgt_PSeqOfExtRefLastItem);

    Standard_Integer ObjMgt_PSeqOfExtRefSize;
    f.GetInteger(ObjMgt_PSeqOfExtRefSize);
    pp->_CSFDB_SetObjMgt_PSeqOfExtRefSize(ObjMgt_PSeqOfExtRefSize);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_PSeqOfExtRef::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_ObjMgt_PSeqOfExtRef::SRead(p,f,theSchema);
}
