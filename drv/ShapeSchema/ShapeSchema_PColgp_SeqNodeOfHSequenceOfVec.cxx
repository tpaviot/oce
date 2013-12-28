#ifndef _ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec_HeaderFile
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec.hxx>
#endif
#ifndef _PColgp_SeqNodeOfHSequenceOfVec_HeaderFile
#include <PColgp_SeqNodeOfHSequenceOfVec.hxx>
#endif
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::New() const
{
  return new PColgp_SeqNodeOfHSequenceOfVec(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::SAdd(const Handle(PColgp_SeqNodeOfHSequenceOfVec)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_SeqNodeOfHSequenceOfVec")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfVecMyPrevious());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfVecMyNext());

    }
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::SAdd((Handle(PColgp_SeqNodeOfHSequenceOfVec)&)p,theSchema);
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfVec) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfVec)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfVecMyPrevious(),f);
    ShapeSchema_gp_Vec::SWrite(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfVecMyItem(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfVecMyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfVec) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfVec)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfVec) PColgp_SeqNodeOfHSequenceOfVecMyPrevious;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfVecMyPrevious,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfVecMyPrevious(PColgp_SeqNodeOfHSequenceOfVecMyPrevious);

    ShapeSchema_gp_Vec::SRead((gp_Vec&)pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfVecMyItem(),f,theSchema);

    Handle(PColgp_SeqNodeOfHSequenceOfVec) PColgp_SeqNodeOfHSequenceOfVecMyNext;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfVecMyNext,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfVecMyNext(PColgp_SeqNodeOfHSequenceOfVecMyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfVec::SRead(p,f,theSchema);
}
