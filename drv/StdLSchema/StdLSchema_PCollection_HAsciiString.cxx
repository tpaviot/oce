#ifndef _StdLSchema_PCollection_HAsciiString_HeaderFile
#include <StdLSchema_PCollection_HAsciiString.hxx>
#endif
#ifndef _PCollection_HAsciiString_HeaderFile
#include <PCollection_HAsciiString.hxx>
#endif
#include <StdLSchema_PCollection_HAsciiString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PCollection_HAsciiString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PCollection_HAsciiString,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PCollection_HAsciiString::New() const
{
  return new PCollection_HAsciiString(Storage_stCONSTclCOM());
}

void StdLSchema_PCollection_HAsciiString::SAdd(const Handle(PCollection_HAsciiString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PCollection_HAsciiString")) {
      
    }
  }
}

void StdLSchema_PCollection_HAsciiString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PCollection_HAsciiString::SAdd((Handle(PCollection_HAsciiString)&)p,theSchema);
}

void StdLSchema_PCollection_HAsciiString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HAsciiString) &pp = (Handle(PCollection_HAsciiString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    StdLSchema_DBC_VArrayOfCharacter::SWrite(pp->_CSFDB_GetPCollection_HAsciiStringData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PCollection_HAsciiString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PCollection_HAsciiString::SWrite(p,f,theSchema);
}


void StdLSchema_PCollection_HAsciiString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HAsciiString) &pp = (Handle(PCollection_HAsciiString)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    StdLSchema_DBC_VArrayOfCharacter::SRead((DBC_VArrayOfCharacter&)pp->_CSFDB_GetPCollection_HAsciiStringData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PCollection_HAsciiString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PCollection_HAsciiString::SRead(p,f,theSchema);
}
