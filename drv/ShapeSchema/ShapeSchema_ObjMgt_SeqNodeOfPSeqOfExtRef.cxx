#ifndef _ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef_HeaderFile
#include <ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef.hxx>
#endif
#ifndef _ObjMgt_SeqNodeOfPSeqOfExtRef_HeaderFile
#include <ObjMgt_SeqNodeOfPSeqOfExtRef.hxx>
#endif
#include <ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::New() const
{
  return new ObjMgt_SeqNodeOfPSeqOfExtRef(Storage_stCONSTclCOM());
}

void ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::SAdd(const Handle(ObjMgt_SeqNodeOfPSeqOfExtRef)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"ObjMgt_SeqNodeOfPSeqOfExtRef")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_SeqNodeOfPSeqOfExtRefMyPrevious());
   theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_SeqNodeOfPSeqOfExtRefMyItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetObjMgt_SeqNodeOfPSeqOfExtRefMyNext());

    }
  }
}

void ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::SAdd((Handle(ObjMgt_SeqNodeOfPSeqOfExtRef)&)p,theSchema);
}

void ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_SeqNodeOfPSeqOfExtRef) &pp = (Handle(ObjMgt_SeqNodeOfPSeqOfExtRef)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_SeqNodeOfPSeqOfExtRefMyPrevious(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_SeqNodeOfPSeqOfExtRefMyItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetObjMgt_SeqNodeOfPSeqOfExtRefMyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::SWrite(p,f,theSchema);
}


void ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(ObjMgt_SeqNodeOfPSeqOfExtRef) &pp = (Handle(ObjMgt_SeqNodeOfPSeqOfExtRef)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(ObjMgt_SeqNodeOfPSeqOfExtRef) ObjMgt_SeqNodeOfPSeqOfExtRefMyPrevious;

    theSchema->ReadPersistentReference(ObjMgt_SeqNodeOfPSeqOfExtRefMyPrevious,f);
    pp->_CSFDB_SetObjMgt_SeqNodeOfPSeqOfExtRefMyPrevious(ObjMgt_SeqNodeOfPSeqOfExtRefMyPrevious);

    Handle(ObjMgt_ExternRef) ObjMgt_SeqNodeOfPSeqOfExtRefMyItem;

    theSchema->ReadPersistentReference(ObjMgt_SeqNodeOfPSeqOfExtRefMyItem,f);
    pp->_CSFDB_SetObjMgt_SeqNodeOfPSeqOfExtRefMyItem(ObjMgt_SeqNodeOfPSeqOfExtRefMyItem);

    Handle(ObjMgt_SeqNodeOfPSeqOfExtRef) ObjMgt_SeqNodeOfPSeqOfExtRefMyNext;

    theSchema->ReadPersistentReference(ObjMgt_SeqNodeOfPSeqOfExtRefMyNext,f);
    pp->_CSFDB_SetObjMgt_SeqNodeOfPSeqOfExtRefMyNext(ObjMgt_SeqNodeOfPSeqOfExtRefMyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_ObjMgt_SeqNodeOfPSeqOfExtRef::SRead(p,f,theSchema);
}
