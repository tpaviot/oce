#ifndef _ShapeSchema_PColgp_HSequenceOfXYZ_HeaderFile
#include <ShapeSchema_PColgp_HSequenceOfXYZ.hxx>
#endif
#ifndef _PColgp_HSequenceOfXYZ_HeaderFile
#include <PColgp_HSequenceOfXYZ.hxx>
#endif
#include <ShapeSchema_PColgp_HSequenceOfXYZ.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_HSequenceOfXYZ,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_HSequenceOfXYZ,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_HSequenceOfXYZ::New() const
{
  return new PColgp_HSequenceOfXYZ(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_HSequenceOfXYZ::SAdd(const Handle(PColgp_HSequenceOfXYZ)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_HSequenceOfXYZ")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfXYZFirstItem());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_HSequenceOfXYZLastItem());

    }
  }
}

void ShapeSchema_PColgp_HSequenceOfXYZ::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_HSequenceOfXYZ::SAdd((Handle(PColgp_HSequenceOfXYZ)&)p,theSchema);
}

void ShapeSchema_PColgp_HSequenceOfXYZ::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfXYZ) &pp = (Handle(PColgp_HSequenceOfXYZ)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfXYZFirstItem(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_HSequenceOfXYZLastItem(),f);
  f.PutInteger(pp->_CSFDB_GetPColgp_HSequenceOfXYZSize());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfXYZ::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_HSequenceOfXYZ::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_HSequenceOfXYZ::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_HSequenceOfXYZ) &pp = (Handle(PColgp_HSequenceOfXYZ)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfXYZ) PColgp_HSequenceOfXYZFirstItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfXYZFirstItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfXYZFirstItem(PColgp_HSequenceOfXYZFirstItem);

    Handle(PColgp_SeqNodeOfHSequenceOfXYZ) PColgp_HSequenceOfXYZLastItem;

    theSchema->ReadPersistentReference(PColgp_HSequenceOfXYZLastItem,f);
    pp->_CSFDB_SetPColgp_HSequenceOfXYZLastItem(PColgp_HSequenceOfXYZLastItem);

    Standard_Integer PColgp_HSequenceOfXYZSize;
    f.GetInteger(PColgp_HSequenceOfXYZSize);
    pp->_CSFDB_SetPColgp_HSequenceOfXYZSize(PColgp_HSequenceOfXYZSize);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_HSequenceOfXYZ::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_HSequenceOfXYZ::SRead(p,f,theSchema);
}
