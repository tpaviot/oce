#ifndef _StdLSchema_PColStd_HArray2OfInteger_HeaderFile
#include <StdLSchema_PColStd_HArray2OfInteger.hxx>
#endif
#ifndef _PColStd_HArray2OfInteger_HeaderFile
#include <PColStd_HArray2OfInteger.hxx>
#endif
#include <StdLSchema_PColStd_HArray2OfInteger.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PColStd_HArray2OfInteger,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PColStd_HArray2OfInteger,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PColStd_HArray2OfInteger::New() const
{
  return new PColStd_HArray2OfInteger(Storage_stCONSTclCOM());
}

void StdLSchema_PColStd_HArray2OfInteger::SAdd(const Handle(PColStd_HArray2OfInteger)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PColStd_HArray2OfInteger")) {
      
    }
  }
}

void StdLSchema_PColStd_HArray2OfInteger::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PColStd_HArray2OfInteger::SAdd((Handle(PColStd_HArray2OfInteger)&)p,theSchema);
}

void StdLSchema_PColStd_HArray2OfInteger::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray2OfInteger) &pp = (Handle(PColStd_HArray2OfInteger)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfIntegermyLowerRow());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfIntegermyLowerCol());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfIntegermyUpperRow());
  f.PutInteger(pp->_CSFDB_GetPColStd_HArray2OfIntegermyUpperCol());
    StdLSchema_PColStd_FieldOfHArray2OfInteger::SWrite(pp->_CSFDB_GetPColStd_HArray2OfIntegerData(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PColStd_HArray2OfInteger::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PColStd_HArray2OfInteger::SWrite(p,f,theSchema);
}


void StdLSchema_PColStd_HArray2OfInteger::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PColStd_HArray2OfInteger) &pp = (Handle(PColStd_HArray2OfInteger)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PColStd_HArray2OfIntegermyLowerRow;
    f.GetInteger(PColStd_HArray2OfIntegermyLowerRow);
    pp->_CSFDB_SetPColStd_HArray2OfIntegermyLowerRow(PColStd_HArray2OfIntegermyLowerRow);

    Standard_Integer PColStd_HArray2OfIntegermyLowerCol;
    f.GetInteger(PColStd_HArray2OfIntegermyLowerCol);
    pp->_CSFDB_SetPColStd_HArray2OfIntegermyLowerCol(PColStd_HArray2OfIntegermyLowerCol);

    Standard_Integer PColStd_HArray2OfIntegermyUpperRow;
    f.GetInteger(PColStd_HArray2OfIntegermyUpperRow);
    pp->_CSFDB_SetPColStd_HArray2OfIntegermyUpperRow(PColStd_HArray2OfIntegermyUpperRow);

    Standard_Integer PColStd_HArray2OfIntegermyUpperCol;
    f.GetInteger(PColStd_HArray2OfIntegermyUpperCol);
    pp->_CSFDB_SetPColStd_HArray2OfIntegermyUpperCol(PColStd_HArray2OfIntegermyUpperCol);

    StdLSchema_PColStd_FieldOfHArray2OfInteger::SRead((PColStd_FieldOfHArray2OfInteger&)pp->_CSFDB_GetPColStd_HArray2OfIntegerData(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PColStd_HArray2OfInteger::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PColStd_HArray2OfInteger::SRead(p,f,theSchema);
}
