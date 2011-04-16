#ifndef _StdLSchema_PColStd_HArray1OfExtendedString_HeaderFile
#include <StdLSchema_PColStd_HArray1OfExtendedString.hxx>
#endif
#ifndef _PColStd_HArray1OfExtendedString_HeaderFile
#include <PColStd_HArray1OfExtendedString.hxx>
#endif
#include <StdLSchema_PColStd_HArray1OfExtendedString.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PColStd_HArray1OfExtendedString,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PColStd_HArray1OfExtendedString,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PColStd_HArray1OfExtendedString::New() const
{
  return new PColStd_HArray1OfExtendedString(Storage_stCONSTclCOM());
}

void StdLSchema_PColStd_HArray1OfExtendedString::SAdd(const Handle(PColStd_HArray1OfExtendedString)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColStd_HArray1OfExtendedString")) {
         StdLSchema_PColStd_FieldOfHArray1OfExtendedString::SAdd(p->_CSFDB_GetPColStd_HArray1OfExtendedStringData(),theSchema);

    }
  }
}

void StdLSchema_PColStd_HArray1OfExtendedString::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PColStd_HArray1OfExtendedString::SAdd((Handle(PColStd_HArray1OfExtendedString)&)p,theSchema);
}

void StdLSchema_PColStd_HArray1OfExtendedString::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray1OfExtendedString) &pp = (Handle(PColStd_HArray1OfExtendedString)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray1OfExtendedStringLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray1OfExtendedStringUpperBound());
    StdLSchema_PColStd_FieldOfHArray1OfExtendedString::SWrite(pp->_CSFDB_GetPColStd_HArray1OfExtendedStringData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PColStd_HArray1OfExtendedString::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PColStd_HArray1OfExtendedString::SWrite(p,f,theSchema);
}


void StdLSchema_PColStd_HArray1OfExtendedString::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray1OfExtendedString) &pp = (Handle(PColStd_HArray1OfExtendedString)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColStd_HArray1OfExtendedStringLowerBound;
    f.GetInteger(PColStd_HArray1OfExtendedStringLowerBound);
    pp->_CSFDB_SetPColStd_HArray1OfExtendedStringLowerBound(PColStd_HArray1OfExtendedStringLowerBound);

    Standard_Integer PColStd_HArray1OfExtendedStringUpperBound;
    f.GetInteger(PColStd_HArray1OfExtendedStringUpperBound);
    pp->_CSFDB_SetPColStd_HArray1OfExtendedStringUpperBound(PColStd_HArray1OfExtendedStringUpperBound);

    StdLSchema_PColStd_FieldOfHArray1OfExtendedString::SRead((PColStd_FieldOfHArray1OfExtendedString&)pp->_CSFDB_GetPColStd_HArray1OfExtendedStringData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PColStd_HArray1OfExtendedString::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PColStd_HArray1OfExtendedString::SRead(p,f,theSchema);
}
