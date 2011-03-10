#ifndef _StdLSchema_PDataStd_HArray1OfHArray1OfInteger_HeaderFile
#include <StdLSchema_PDataStd_HArray1OfHArray1OfInteger.hxx>
#endif
#ifndef _PDataStd_HArray1OfHArray1OfInteger_HeaderFile
#include <PDataStd_HArray1OfHArray1OfInteger.hxx>
#endif
#include <StdLSchema_PDataStd_HArray1OfHArray1OfInteger.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_HArray1OfHArray1OfInteger,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_HArray1OfHArray1OfInteger,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_HArray1OfHArray1OfInteger::New() const
{
  return new PDataStd_HArray1OfHArray1OfInteger(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_HArray1OfHArray1OfInteger::SAdd(const Handle(PDataStd_HArray1OfHArray1OfInteger)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_HArray1OfHArray1OfInteger")) {
         StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfInteger::SAdd(p->_CSFDB_GetPDataStd_HArray1OfHArray1OfIntegerData(),theSchema);

    }
  }
}

void StdLSchema_PDataStd_HArray1OfHArray1OfInteger::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_HArray1OfHArray1OfInteger::SAdd((Handle(PDataStd_HArray1OfHArray1OfInteger)&)p,theSchema);
}

void StdLSchema_PDataStd_HArray1OfHArray1OfInteger::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfHArray1OfInteger) &pp = (Handle(PDataStd_HArray1OfHArray1OfInteger)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfIntegerLowerBound());
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfIntegerUpperBound());
    StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfInteger::SWrite(pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfIntegerData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfHArray1OfInteger::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_HArray1OfHArray1OfInteger::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_HArray1OfHArray1OfInteger::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfHArray1OfInteger) &pp = (Handle(PDataStd_HArray1OfHArray1OfInteger)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataStd_HArray1OfHArray1OfIntegerLowerBound;
    f.GetInteger(PDataStd_HArray1OfHArray1OfIntegerLowerBound);
    pp->_CSFDB_SetPDataStd_HArray1OfHArray1OfIntegerLowerBound(PDataStd_HArray1OfHArray1OfIntegerLowerBound);

    Standard_Integer PDataStd_HArray1OfHArray1OfIntegerUpperBound;
    f.GetInteger(PDataStd_HArray1OfHArray1OfIntegerUpperBound);
    pp->_CSFDB_SetPDataStd_HArray1OfHArray1OfIntegerUpperBound(PDataStd_HArray1OfHArray1OfIntegerUpperBound);

    StdLSchema_PDataStd_FieldOfHArray1OfHArray1OfInteger::SRead((PDataStd_FieldOfHArray1OfHArray1OfInteger&)pp->_CSFDB_GetPDataStd_HArray1OfHArray1OfIntegerData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfHArray1OfInteger::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_HArray1OfHArray1OfInteger::SRead(p,f,theSchema);
}
