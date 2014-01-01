#ifndef _ShapeSchema_PColgp_HSequenceOfVec_HeaderFile
#include <ShapeSchema_PColgp_HSequenceOfVec.hxx>
#endif
#ifndef _PColgp_HSequenceOfVec_HeaderFile
#include <PColgp_HSequenceOfVec.hxx>
#endif
#include <ShapeSchema_PColgp_HSequenceOfVec.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HSequenceOfVec,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HSequenceOfVec,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HSequenceOfVec::New() const
{
  return new PColgp_HSequenceOfVec(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HSequenceOfVec::SAdd(const Handle(PColgp_HSequenceOfVec)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HSequenceOfVec")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfVecFirstItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfVecLastItem());

    }
  }
}

void ShapeSchema_PColgp_HSequenceOfVec::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HSequenceOfVec::SAdd((Handle(PColgp_HSequenceOfVec)&)p,theSchema);
}

void ShapeSchema_PColgp_HSequenceOfVec::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfVec) &pp = (Handle(PColgp_HSequenceOfVec)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfVecFirstItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfVecLastItem(),f);
  f.PutInteger(pp->_CSFDB_GetPColgp_HSequenceOfVecSize());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfVec::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HSequenceOfVec::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HSequenceOfVec::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfVec) &pp = (Handle(PColgp_HSequenceOfVec)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfVec) PColgp_HSequenceOfVecFirstItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfVecFirstItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfVecFirstItem(PColgp_HSequenceOfVecFirstItem);

    Handle(PColgp_SeqNodeOfHSequenceOfVec) PColgp_HSequenceOfVecLastItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfVecLastItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfVecLastItem(PColgp_HSequenceOfVecLastItem);

    Standard_Integer PColgp_HSequenceOfVecSize;
    f.GetInteger(PColgp_HSequenceOfVecSize);
    pp->_CSFDB_SetPColgp_HSequenceOfVecSize(PColgp_HSequenceOfVecSize);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfVec::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HSequenceOfVec::SRead(p,f,theSchema);
}
