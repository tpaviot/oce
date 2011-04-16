#ifndef _StdSchema_PCollection_HExtendedString_HeaderFile
#include <StdSchema_PCollection_HExtendedString.hxx>
#endif
#ifndef _PCollection_HExtendedString_HeaderFile
#include <PCollection_HExtendedString.hxx>
#endif
#include <StdSchema_PCollection_HExtendedString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PCollection_HExtendedString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PCollection_HExtendedString,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PCollection_HExtendedString::New() const
{
  return new PCollection_HExtendedString(Storage_stCONSTclCOM());
}

void StdSchema_PCollection_HExtendedString::SAdd(const Handle(PCollection_HExtendedString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PCollection_HExtendedString")) {
      
    }
  }
}

void StdSchema_PCollection_HExtendedString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PCollection_HExtendedString::SAdd((Handle(PCollection_HExtendedString)&)p,theSchema);
}

void StdSchema_PCollection_HExtendedString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HExtendedString) &pp = (Handle(PCollection_HExtendedString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    StdSchema_DBC_VArrayOfExtCharacter::SWrite(pp->_CSFDB_GetPCollection_HExtendedStringData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PCollection_HExtendedString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PCollection_HExtendedString::SWrite(p,f,theSchema);
}


void StdSchema_PCollection_HExtendedString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HExtendedString) &pp = (Handle(PCollection_HExtendedString)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    StdSchema_DBC_VArrayOfExtCharacter::SRead((DBC_VArrayOfExtCharacter&)pp->_CSFDB_GetPCollection_HExtendedStringData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PCollection_HExtendedString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PCollection_HExtendedString::SRead(p,f,theSchema);
}
