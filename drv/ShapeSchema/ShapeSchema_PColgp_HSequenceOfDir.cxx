#ifndef _ShapeSchema_PColgp_HSequenceOfDir_HeaderFile
#include <ShapeSchema_PColgp_HSequenceOfDir.hxx>
#endif
#ifndef _PColgp_HSequenceOfDir_HeaderFile
#include <PColgp_HSequenceOfDir.hxx>
#endif
#include <ShapeSchema_PColgp_HSequenceOfDir.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HSequenceOfDir,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HSequenceOfDir,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HSequenceOfDir::New() const
{
  return new PColgp_HSequenceOfDir(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HSequenceOfDir::SAdd(const Handle(PColgp_HSequenceOfDir)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HSequenceOfDir")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfDirFirstItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfDirLastItem());

    }
  }
}

void ShapeSchema_PColgp_HSequenceOfDir::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HSequenceOfDir::SAdd((Handle(PColgp_HSequenceOfDir)&)p,theSchema);
}

void ShapeSchema_PColgp_HSequenceOfDir::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfDir) &pp = (Handle(PColgp_HSequenceOfDir)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfDirFirstItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfDirLastItem(),f);
  f.PutInteger(pp->_CSFDB_GetPColgp_HSequenceOfDirSize());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfDir::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HSequenceOfDir::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HSequenceOfDir::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfDir) &pp = (Handle(PColgp_HSequenceOfDir)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfDir) PColgp_HSequenceOfDirFirstItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfDirFirstItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfDirFirstItem(PColgp_HSequenceOfDirFirstItem);

    Handle(PColgp_SeqNodeOfHSequenceOfDir) PColgp_HSequenceOfDirLastItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfDirLastItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfDirLastItem(PColgp_HSequenceOfDirLastItem);

    Standard_Integer PColgp_HSequenceOfDirSize;
    f.GetInteger(PColgp_HSequenceOfDirSize);
    pp->_CSFDB_SetPColgp_HSequenceOfDirSize(PColgp_HSequenceOfDirSize);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfDir::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HSequenceOfDir::SRead(p,f,theSchema);
}
