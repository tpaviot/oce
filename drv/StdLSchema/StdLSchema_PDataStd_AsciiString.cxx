#ifndef _StdLSchema_PDataStd_AsciiString_HeaderFile
#include <StdLSchema_PDataStd_AsciiString.hxx>
#endif
#ifndef _PDataStd_AsciiString_HeaderFile
#include <PDataStd_AsciiString.hxx>
#endif
#include <StdLSchema_PDataStd_AsciiString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_AsciiString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_AsciiString,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_AsciiString::New() const
{
  return new PDataStd_AsciiString(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_AsciiString::SAdd(const Handle(PDataStd_AsciiString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_AsciiString")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_AsciiStringmyValue());

    }
  }
}

void StdLSchema_PDataStd_AsciiString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_AsciiString::SAdd((Handle(PDataStd_AsciiString)&)p,theSchema);
}

void StdLSchema_PDataStd_AsciiString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_AsciiString) &pp = (Handle(PDataStd_AsciiString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_AsciiStringmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_AsciiString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_AsciiString::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_AsciiString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_AsciiString) &pp = (Handle(PDataStd_AsciiString)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) PDataStd_AsciiStringmyValue;

    theSchema->ReadPersistentReference(PDataStd_AsciiStringmyValue,f);
    pp->_CSFDB_SetPDataStd_AsciiStringmyValue(PDataStd_AsciiStringmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_AsciiString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_AsciiString::SRead(p,f,theSchema);
}
