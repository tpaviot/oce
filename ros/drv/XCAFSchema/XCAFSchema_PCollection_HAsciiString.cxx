#ifndef _XCAFSchema_PCollection_HAsciiString_HeaderFile
#include <XCAFSchema_PCollection_HAsciiString.hxx>
#endif
#ifndef _PCollection_HAsciiString_HeaderFile
#include <PCollection_HAsciiString.hxx>
#endif
#include <XCAFSchema_PCollection_HAsciiString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PCollection_HAsciiString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PCollection_HAsciiString,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PCollection_HAsciiString::New() const
{
  return new PCollection_HAsciiString(Storage_stCONSTclCOM());
}

void XCAFSchema_PCollection_HAsciiString::SAdd(const Handle(PCollection_HAsciiString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PCollection_HAsciiString")) {
      
    }
  }
}

void XCAFSchema_PCollection_HAsciiString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PCollection_HAsciiString::SAdd((Handle(PCollection_HAsciiString)&)p,theSchema);
}

void XCAFSchema_PCollection_HAsciiString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HAsciiString) &pp = (Handle(PCollection_HAsciiString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    XCAFSchema_DBC_VArrayOfCharacter::SWrite(pp->_CSFDB_GetPCollection_HAsciiStringData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PCollection_HAsciiString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PCollection_HAsciiString::SWrite(p,f,theSchema);
}


void XCAFSchema_PCollection_HAsciiString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCollection_HAsciiString) &pp = (Handle(PCollection_HAsciiString)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    XCAFSchema_DBC_VArrayOfCharacter::SRead((DBC_VArrayOfCharacter&)pp->_CSFDB_GetPCollection_HAsciiStringData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PCollection_HAsciiString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PCollection_HAsciiString::SRead(p,f,theSchema);
}
