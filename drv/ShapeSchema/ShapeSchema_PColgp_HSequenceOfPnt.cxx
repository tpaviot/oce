#ifndef _ShapeSchema_PColgp_HSequenceOfPnt_HeaderFile
#include <ShapeSchema_PColgp_HSequenceOfPnt.hxx>
#endif
#ifndef _PColgp_HSequenceOfPnt_HeaderFile
#include <PColgp_HSequenceOfPnt.hxx>
#endif
#include <ShapeSchema_PColgp_HSequenceOfPnt.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HSequenceOfPnt,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HSequenceOfPnt,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HSequenceOfPnt::New() const
{
  return new PColgp_HSequenceOfPnt(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HSequenceOfPnt::SAdd(const Handle(PColgp_HSequenceOfPnt)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HSequenceOfPnt")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfPntFirstItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfPntLastItem());

    }
  }
}

void ShapeSchema_PColgp_HSequenceOfPnt::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HSequenceOfPnt::SAdd((Handle(PColgp_HSequenceOfPnt)&)p,theSchema);
}

void ShapeSchema_PColgp_HSequenceOfPnt::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfPnt) &pp = (Handle(PColgp_HSequenceOfPnt)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfPntFirstItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfPntLastItem(),f);
  f.PutInteger(pp->_CSFDB_GetPColgp_HSequenceOfPntSize());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfPnt::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HSequenceOfPnt::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HSequenceOfPnt::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfPnt) &pp = (Handle(PColgp_HSequenceOfPnt)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfPnt) PColgp_HSequenceOfPntFirstItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfPntFirstItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfPntFirstItem(PColgp_HSequenceOfPntFirstItem);

    Handle(PColgp_SeqNodeOfHSequenceOfPnt) PColgp_HSequenceOfPntLastItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfPntLastItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfPntLastItem(PColgp_HSequenceOfPntLastItem);

    Standard_Integer PColgp_HSequenceOfPntSize;
    f.GetInteger(PColgp_HSequenceOfPntSize);
    pp->_CSFDB_SetPColgp_HSequenceOfPntSize(PColgp_HSequenceOfPntSize);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfPnt::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HSequenceOfPnt::SRead(p,f,theSchema);
}
