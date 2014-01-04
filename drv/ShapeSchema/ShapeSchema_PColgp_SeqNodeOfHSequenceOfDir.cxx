#ifndef _ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir_HeaderFile
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir.hxx>
#endif
#ifndef _PColgp_SeqNodeOfHSequenceOfDir_HeaderFile
#include <PColgp_SeqNodeOfHSequenceOfDir.hxx>
#endif
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::New() const
{
  return new PColgp_SeqNodeOfHSequenceOfDir(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::SAdd(const Handle(PColgp_SeqNodeOfHSequenceOfDir)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_SeqNodeOfHSequenceOfDir")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfDirMyPrevious());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfDirMyNext());

    }
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::SAdd((Handle(PColgp_SeqNodeOfHSequenceOfDir)&)p,theSchema);
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfDir) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfDir)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfDirMyPrevious(),f);
    ShapeSchema_gp_Dir::SWrite(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfDirMyItem(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfDirMyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfDir) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfDir)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfDir) PColgp_SeqNodeOfHSequenceOfDirMyPrevious;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfDirMyPrevious,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfDirMyPrevious(PColgp_SeqNodeOfHSequenceOfDirMyPrevious);

    ShapeSchema_gp_Dir::SRead((gp_Dir&)pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfDirMyItem(),f,theSchema);

    Handle(PColgp_SeqNodeOfHSequenceOfDir) PColgp_SeqNodeOfHSequenceOfDirMyNext;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfDirMyNext,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfDirMyNext(PColgp_SeqNodeOfHSequenceOfDirMyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfDir::SRead(p,f,theSchema);
}
