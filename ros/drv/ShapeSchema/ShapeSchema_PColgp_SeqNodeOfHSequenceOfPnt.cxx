#ifndef _ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt_HeaderFile
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt.hxx>
#endif
#ifndef _PColgp_SeqNodeOfHSequenceOfPnt_HeaderFile
#include <PColgp_SeqNodeOfHSequenceOfPnt.hxx>
#endif
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::New() const
{
  return new PColgp_SeqNodeOfHSequenceOfPnt(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::SAdd(const Handle(PColgp_SeqNodeOfHSequenceOfPnt)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_SeqNodeOfHSequenceOfPnt")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfPntMyPrevious());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfPntMyNext());

    }
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::SAdd((Handle(PColgp_SeqNodeOfHSequenceOfPnt)&)p,theSchema);
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfPnt) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfPnt)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfPntMyPrevious(),f);
    ShapeSchema_gp_Pnt::SWrite(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfPntMyItem(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfPntMyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfPnt) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfPnt)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfPnt) PColgp_SeqNodeOfHSequenceOfPntMyPrevious;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfPntMyPrevious,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfPntMyPrevious(PColgp_SeqNodeOfHSequenceOfPntMyPrevious);

    ShapeSchema_gp_Pnt::SRead((gp_Pnt&)pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfPntMyItem(),f,theSchema);

    Handle(PColgp_SeqNodeOfHSequenceOfPnt) PColgp_SeqNodeOfHSequenceOfPntMyNext;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfPntMyNext,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfPntMyNext(PColgp_SeqNodeOfHSequenceOfPntMyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfPnt::SRead(p,f,theSchema);
}
