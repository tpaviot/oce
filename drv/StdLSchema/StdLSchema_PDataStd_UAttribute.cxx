#ifndef _StdLSchema_PDataStd_UAttribute_HeaderFile
#include <StdLSchema_PDataStd_UAttribute.hxx>
#endif
#ifndef _PDataStd_UAttribute_HeaderFile
#include <PDataStd_UAttribute.hxx>
#endif
#include <StdLSchema_PDataStd_UAttribute.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_UAttribute,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_UAttribute,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_UAttribute::New() const
{
  return new PDataStd_UAttribute(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_UAttribute::SAdd(const Handle(PDataStd_UAttribute)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_UAttribute")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_UAttributemyID());

    }
  }
}

void StdLSchema_PDataStd_UAttribute::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_UAttribute::SAdd((Handle(PDataStd_UAttribute)&)p,theSchema);
}

void StdLSchema_PDataStd_UAttribute::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_UAttribute) &pp = (Handle(PDataStd_UAttribute)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_UAttributemyID(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_UAttribute::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_UAttribute::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_UAttribute::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_UAttribute) &pp = (Handle(PDataStd_UAttribute)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HExtendedString) PDataStd_UAttributemyID;

    theSchema->ReadPersistentReference(PDataStd_UAttributemyID,f);
    pp->_CSFDB_SetPDataStd_UAttributemyID(PDataStd_UAttributemyID);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_UAttribute::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_UAttribute::SRead(p,f,theSchema);
}
