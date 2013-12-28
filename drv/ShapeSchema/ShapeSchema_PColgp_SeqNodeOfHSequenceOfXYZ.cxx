#ifndef _ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ_HeaderFile
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ.hxx>
#endif
#ifndef _PColgp_SeqNodeOfHSequenceOfXYZ_HeaderFile
#include <PColgp_SeqNodeOfHSequenceOfXYZ.hxx>
#endif
#include <ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::New() const
{
  return new PColgp_SeqNodeOfHSequenceOfXYZ(Storage_stCONSTclCOM());
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::SAdd(const Handle(PColgp_SeqNodeOfHSequenceOfXYZ)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColgp_SeqNodeOfHSequenceOfXYZ")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfXYZMyPrevious());
   theSchema->PersistentToAdd(p->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfXYZMyNext());

    }
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::SAdd((Handle(PColgp_SeqNodeOfHSequenceOfXYZ)&)p,theSchema);
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfXYZ) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfXYZ)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfXYZMyPrevious(),f);
    ShapeSchema_gp_XYZ::SWrite(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfXYZMyItem(),f,theSchema);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfXYZMyNext(),f);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::SWrite(p,f,theSchema);
}


void ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColgp_SeqNodeOfHSequenceOfXYZ) &pp = (Handle(PColgp_SeqNodeOfHSequenceOfXYZ)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColgp_SeqNodeOfHSequenceOfXYZ) PColgp_SeqNodeOfHSequenceOfXYZMyPrevious;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfXYZMyPrevious,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfXYZMyPrevious(PColgp_SeqNodeOfHSequenceOfXYZMyPrevious);

    ShapeSchema_gp_XYZ::SRead((gp_XYZ&)pp->_CSFDB_GetPColgp_SeqNodeOfHSequenceOfXYZMyItem(),f,theSchema);

    Handle(PColgp_SeqNodeOfHSequenceOfXYZ) PColgp_SeqNodeOfHSequenceOfXYZMyNext;

    theSchema->ReadPersistentReference(PColgp_SeqNodeOfHSequenceOfXYZMyNext,f);
    pp->_CSFDB_SetPColgp_SeqNodeOfHSequenceOfXYZMyNext(PColgp_SeqNodeOfHSequenceOfXYZMyNext);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PColgp_SeqNodeOfHSequenceOfXYZ::SRead(p,f,theSchema);
}
