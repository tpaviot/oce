#ifndef _XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence_HeaderFile
#include <XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence.hxx>
#endif
#ifndef _PXCAFDoc_SeqNodeOfGraphNodeSequence_HeaderFile
#include <PXCAFDoc_SeqNodeOfGraphNodeSequence.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::New() const
{
  return new PXCAFDoc_SeqNodeOfGraphNodeSequence(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::SAdd(const Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_SeqNodeOfGraphNodeSequence")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyPrevious());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyNext());

    }
  }
}

void XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::SAdd((Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence) &pp = (Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyPrevious(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence) &pp = (Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence) PXCAFDoc_SeqNodeOfGraphNodeSequenceMyPrevious;

    theSchema->ReadPersistentReference(PXCAFDoc_SeqNodeOfGraphNodeSequenceMyPrevious,f);
    pp->_CSFDB_SetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyPrevious(PXCAFDoc_SeqNodeOfGraphNodeSequenceMyPrevious);

    Handle(PXCAFDoc_GraphNode) PXCAFDoc_SeqNodeOfGraphNodeSequenceMyItem;

    theSchema->ReadPersistentReference(PXCAFDoc_SeqNodeOfGraphNodeSequenceMyItem,f);
    pp->_CSFDB_SetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyItem(PXCAFDoc_SeqNodeOfGraphNodeSequenceMyItem);

    Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence) PXCAFDoc_SeqNodeOfGraphNodeSequenceMyNext;

    theSchema->ReadPersistentReference(PXCAFDoc_SeqNodeOfGraphNodeSequenceMyNext,f);
    pp->_CSFDB_SetPXCAFDoc_SeqNodeOfGraphNodeSequenceMyNext(PXCAFDoc_SeqNodeOfGraphNodeSequenceMyNext);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_SeqNodeOfGraphNodeSequence::SRead(p,f,theSchema);
}
