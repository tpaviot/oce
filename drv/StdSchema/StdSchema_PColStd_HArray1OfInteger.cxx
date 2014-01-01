#ifndef _StdSchema_PColStd_HArray1OfInteger_HeaderFile
#include <StdSchema_PColStd_HArray1OfInteger.hxx>
#endif
#ifndef _PColStd_HArray1OfInteger_HeaderFile
#include <PColStd_HArray1OfInteger.hxx>
#endif
#include <StdSchema_PColStd_HArray1OfInteger.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PColStd_HArray1OfInteger,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PColStd_HArray1OfInteger,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PColStd_HArray1OfInteger::New() const
{
  return new PColStd_HArray1OfInteger(Storage_stCONSTclCOM());
}

void StdSchema_PColStd_HArray1OfInteger::SAdd(const Handle(PColStd_HArray1OfInteger)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColStd_HArray1OfInteger")) {
      
    }
  }
}

void StdSchema_PColStd_HArray1OfInteger::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PColStd_HArray1OfInteger::SAdd((Handle(PColStd_HArray1OfInteger)&)p,theSchema);
}

void StdSchema_PColStd_HArray1OfInteger::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray1OfInteger) &pp = (Handle(PColStd_HArray1OfInteger)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray1OfIntegerLowerBound());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray1OfIntegerUpperBound());
    StdSchema_PColStd_FieldOfHArray1OfInteger::SWrite(pp->_CSFDB_GetPColStd_HArray1OfIntegerData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PColStd_HArray1OfInteger::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PColStd_HArray1OfInteger::SWrite(p,f,theSchema);
}


void StdSchema_PColStd_HArray1OfInteger::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray1OfInteger) &pp = (Handle(PColStd_HArray1OfInteger)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColStd_HArray1OfIntegerLowerBound;
    f.GetInteger(PColStd_HArray1OfIntegerLowerBound);
    pp->_CSFDB_SetPColStd_HArray1OfIntegerLowerBound(PColStd_HArray1OfIntegerLowerBound);

    Standard_Integer PColStd_HArray1OfIntegerUpperBound;
    f.GetInteger(PColStd_HArray1OfIntegerUpperBound);
    pp->_CSFDB_SetPColStd_HArray1OfIntegerUpperBound(PColStd_HArray1OfIntegerUpperBound);

    StdSchema_PColStd_FieldOfHArray1OfInteger::SRead((PColStd_FieldOfHArray1OfInteger&)pp->_CSFDB_GetPColStd_HArray1OfIntegerData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PColStd_HArray1OfInteger::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PColStd_HArray1OfInteger::SRead(p,f,theSchema);
}
