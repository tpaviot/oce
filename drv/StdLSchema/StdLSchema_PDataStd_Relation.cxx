#ifndef _StdLSchema_PDataStd_Relation_HeaderFile
#include <StdLSchema_PDataStd_Relation.hxx>
#endif
#ifndef _PDataStd_Relation_HeaderFile
#include <PDataStd_Relation.hxx>
#endif
#include <StdLSchema_PDataStd_Relation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_Relation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_Relation,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_Relation::New() const
{
  return new PDataStd_Relation(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_Relation::SAdd(const Handle(PDataStd_Relation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_Relation")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_RelationmyName());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_RelationmyVariables());

    }
  }
}

void StdLSchema_PDataStd_Relation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_Relation::SAdd((Handle(PDataStd_Relation)&)p,theSchema);
}

void StdLSchema_PDataStd_Relation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Relation) &pp = (Handle(PDataStd_Relation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_RelationmyName(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_RelationmyVariables(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_Relation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_Relation::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_Relation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_Relation) &pp = (Handle(PDataStd_Relation)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HExtendedString) PDataStd_RelationmyName;

    theSchema->ReadPersistentReference(PDataStd_RelationmyName,f);
    pp->_CSFDB_SetPDataStd_RelationmyName(PDataStd_RelationmyName);

    Handle(PDF_HAttributeArray1) PDataStd_RelationmyVariables;

    theSchema->ReadPersistentReference(PDataStd_RelationmyVariables,f);
    pp->_CSFDB_SetPDataStd_RelationmyVariables(PDataStd_RelationmyVariables);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_Relation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_Relation::SRead(p,f,theSchema);
}
