#ifndef _StdLSchema_PDataStd_HArray1OfHAsciiString_HeaderFile
#include <StdLSchema_PDataStd_HArray1OfHAsciiString.hxx>
#endif
#ifndef _PDataStd_HArray1OfHAsciiString_HeaderFile
#include <PDataStd_HArray1OfHAsciiString.hxx>
#endif
#include <StdLSchema_PDataStd_HArray1OfHAsciiString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_HArray1OfHAsciiString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_HArray1OfHAsciiString,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_HArray1OfHAsciiString::New() const
{
  return new PDataStd_HArray1OfHAsciiString(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_HArray1OfHAsciiString::SAdd(const Handle(PDataStd_HArray1OfHAsciiString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_HArray1OfHAsciiString")) {
         StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString::SAdd(p->_CSFDB_GetPDataStd_HArray1OfHAsciiStringData(),theSchema);

    }
  }
}

void StdLSchema_PDataStd_HArray1OfHAsciiString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_HArray1OfHAsciiString::SAdd((Handle(PDataStd_HArray1OfHAsciiString)&)p,theSchema);
}

void StdLSchema_PDataStd_HArray1OfHAsciiString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfHAsciiString) &pp = (Handle(PDataStd_HArray1OfHAsciiString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfHAsciiStringLowerBound());
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfHAsciiStringUpperBound());
    StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString::SWrite(pp->_CSFDB_GetPDataStd_HArray1OfHAsciiStringData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfHAsciiString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_HArray1OfHAsciiString::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_HArray1OfHAsciiString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfHAsciiString) &pp = (Handle(PDataStd_HArray1OfHAsciiString)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataStd_HArray1OfHAsciiStringLowerBound;
    f.GetInteger(PDataStd_HArray1OfHAsciiStringLowerBound);
    pp->_CSFDB_SetPDataStd_HArray1OfHAsciiStringLowerBound(PDataStd_HArray1OfHAsciiStringLowerBound);

    Standard_Integer PDataStd_HArray1OfHAsciiStringUpperBound;
    f.GetInteger(PDataStd_HArray1OfHAsciiStringUpperBound);
    pp->_CSFDB_SetPDataStd_HArray1OfHAsciiStringUpperBound(PDataStd_HArray1OfHAsciiStringUpperBound);

    StdLSchema_PDataStd_FieldOfHArray1OfHAsciiString::SRead((PDataStd_FieldOfHArray1OfHAsciiString&)pp->_CSFDB_GetPDataStd_HArray1OfHAsciiStringData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfHAsciiString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_HArray1OfHAsciiString::SRead(p,f,theSchema);
}
