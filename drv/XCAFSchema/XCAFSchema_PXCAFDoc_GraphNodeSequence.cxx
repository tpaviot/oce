#ifndef _XCAFSchema_PXCAFDoc_GraphNodeSequence_HeaderFile
#include <XCAFSchema_PXCAFDoc_GraphNodeSequence.hxx>
#endif
#ifndef _PXCAFDoc_GraphNodeSequence_HeaderFile
#include <PXCAFDoc_GraphNodeSequence.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_GraphNodeSequence.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_GraphNodeSequence,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_GraphNodeSequence,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_GraphNodeSequence::New() const
{
  return new PXCAFDoc_GraphNodeSequence(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_GraphNodeSequence::SAdd(const Handle(PXCAFDoc_GraphNodeSequence)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_GraphNodeSequence")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_GraphNodeSequenceFirstItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_GraphNodeSequenceLastItem());

    }
  }
}

void XCAFSchema_PXCAFDoc_GraphNodeSequence::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_GraphNodeSequence::SAdd((Handle(PXCAFDoc_GraphNodeSequence)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_GraphNodeSequence::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_GraphNodeSequence) &pp = (Handle(PXCAFDoc_GraphNodeSequence)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_GraphNodeSequenceFirstItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_GraphNodeSequenceLastItem(),f);
  f.PutInteger(pp->_CSFDB_GetPXCAFDoc_GraphNodeSequenceSize());

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_GraphNodeSequence::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_GraphNodeSequence::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_GraphNodeSequence::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_GraphNodeSequence) &pp = (Handle(PXCAFDoc_GraphNodeSequence)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence) PXCAFDoc_GraphNodeSequenceFirstItem;

    theSchema->ReadPersistentReference(PXCAFDoc_GraphNodeSequenceFirstItem,f);
    pp->_CSFDB_SetPXCAFDoc_GraphNodeSequenceFirstItem(PXCAFDoc_GraphNodeSequenceFirstItem);

    Handle(PXCAFDoc_SeqNodeOfGraphNodeSequence) PXCAFDoc_GraphNodeSequenceLastItem;

    theSchema->ReadPersistentReference(PXCAFDoc_GraphNodeSequenceLastItem,f);
    pp->_CSFDB_SetPXCAFDoc_GraphNodeSequenceLastItem(PXCAFDoc_GraphNodeSequenceLastItem);

    Standard_Integer PXCAFDoc_GraphNodeSequenceSize;
    f.GetInteger(PXCAFDoc_GraphNodeSequenceSize);
    pp->_CSFDB_SetPXCAFDoc_GraphNodeSequenceSize(PXCAFDoc_GraphNodeSequenceSize);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_GraphNodeSequence::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_GraphNodeSequence::SRead(p,f,theSchema);
}
