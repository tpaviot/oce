#ifndef _StdLSchema_PDataStd_HArray1OfByte_HeaderFile
#include <StdLSchema_PDataStd_HArray1OfByte.hxx>
#endif
#ifndef _PDataStd_HArray1OfByte_HeaderFile
#include <PDataStd_HArray1OfByte.hxx>
#endif
#include <StdLSchema_PDataStd_HArray1OfByte.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_HArray1OfByte,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_HArray1OfByte,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_HArray1OfByte::New() const
{
  return new PDataStd_HArray1OfByte(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_HArray1OfByte::SAdd(const Handle(PDataStd_HArray1OfByte)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_HArray1OfByte")) {
      
    }
  }
}

void StdLSchema_PDataStd_HArray1OfByte::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_HArray1OfByte::SAdd((Handle(PDataStd_HArray1OfByte)&)p,theSchema);
}

void StdLSchema_PDataStd_HArray1OfByte::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfByte) &pp = (Handle(PDataStd_HArray1OfByte)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfByteLowerBound());
  f.PutInteger(pp->_CSFDB_GetPDataStd_HArray1OfByteUpperBound());
    StdLSchema_PDataStd_FieldOfHArray1OfByte::SWrite(pp->_CSFDB_GetPDataStd_HArray1OfByteData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfByte::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_HArray1OfByte::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_HArray1OfByte::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_HArray1OfByte) &pp = (Handle(PDataStd_HArray1OfByte)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDataStd_HArray1OfByteLowerBound;
    f.GetInteger(PDataStd_HArray1OfByteLowerBound);
    pp->_CSFDB_SetPDataStd_HArray1OfByteLowerBound(PDataStd_HArray1OfByteLowerBound);

    Standard_Integer PDataStd_HArray1OfByteUpperBound;
    f.GetInteger(PDataStd_HArray1OfByteUpperBound);
    pp->_CSFDB_SetPDataStd_HArray1OfByteUpperBound(PDataStd_HArray1OfByteUpperBound);

    StdLSchema_PDataStd_FieldOfHArray1OfByte::SRead((PDataStd_FieldOfHArray1OfByte&)pp->_CSFDB_GetPDataStd_HArray1OfByteData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_HArray1OfByte::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_HArray1OfByte::SRead(p,f,theSchema);
}
