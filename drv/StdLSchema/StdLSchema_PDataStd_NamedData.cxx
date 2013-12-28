#ifndef _StdLSchema_PDataStd_NamedData_HeaderFile
#include <StdLSchema_PDataStd_NamedData.hxx>
#endif
#ifndef _PDataStd_NamedData_HeaderFile
#include <PDataStd_NamedData.hxx>
#endif
#include <StdLSchema_PDataStd_NamedData.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_NamedData,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_NamedData,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_NamedData::New() const
{
  return new PDataStd_NamedData(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_NamedData::SAdd(const Handle(PDataStd_NamedData)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_NamedData")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyDimensions());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyIntKeys());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyIntValues());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyRealKeys());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyRealValues());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyStrKeys());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyStrValues());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyByteKeys());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyByteValues());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyArrIntKeys());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyArrIntValues());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyArrRealKeys());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_NamedDatamyArrRealValues());

    }
  }
}

void StdLSchema_PDataStd_NamedData::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_NamedData::SAdd((Handle(PDataStd_NamedData)&)p,theSchema);
}

void StdLSchema_PDataStd_NamedData::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_NamedData) &pp = (Handle(PDataStd_NamedData)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyDimensions(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyIntKeys(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyIntValues(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyRealKeys(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyRealValues(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyStrKeys(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyStrValues(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyByteKeys(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyByteValues(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyArrIntKeys(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyArrIntValues(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyArrRealKeys(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_NamedDatamyArrRealValues(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_NamedData::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_NamedData::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_NamedData::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_NamedData) &pp = (Handle(PDataStd_NamedData)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray2OfInteger) PDataStd_NamedDatamyDimensions;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyDimensions,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyDimensions(PDataStd_NamedDatamyDimensions);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyIntKeys;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyIntKeys,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyIntKeys(PDataStd_NamedDatamyIntKeys);

    Handle(PColStd_HArray1OfInteger) PDataStd_NamedDatamyIntValues;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyIntValues,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyIntValues(PDataStd_NamedDatamyIntValues);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyRealKeys;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyRealKeys,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyRealKeys(PDataStd_NamedDatamyRealKeys);

    Handle(PColStd_HArray1OfReal) PDataStd_NamedDatamyRealValues;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyRealValues,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyRealValues(PDataStd_NamedDatamyRealValues);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyStrKeys;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyStrKeys,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyStrKeys(PDataStd_NamedDatamyStrKeys);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyStrValues;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyStrValues,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyStrValues(PDataStd_NamedDatamyStrValues);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyByteKeys;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyByteKeys,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyByteKeys(PDataStd_NamedDatamyByteKeys);

    Handle(PDataStd_HArray1OfByte) PDataStd_NamedDatamyByteValues;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyByteValues,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyByteValues(PDataStd_NamedDatamyByteValues);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyArrIntKeys;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyArrIntKeys,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyArrIntKeys(PDataStd_NamedDatamyArrIntKeys);

    Handle(PDataStd_HArray1OfHArray1OfInteger) PDataStd_NamedDatamyArrIntValues;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyArrIntValues,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyArrIntValues(PDataStd_NamedDatamyArrIntValues);

    Handle(PColStd_HArray1OfExtendedString) PDataStd_NamedDatamyArrRealKeys;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyArrRealKeys,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyArrRealKeys(PDataStd_NamedDatamyArrRealKeys);

    Handle(PDataStd_HArray1OfHArray1OfReal) PDataStd_NamedDatamyArrRealValues;

    theSchema->ReadPersistentReference(PDataStd_NamedDatamyArrRealValues,f);
    pp->_CSFDB_SetPDataStd_NamedDatamyArrRealValues(PDataStd_NamedDatamyArrRealValues);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_NamedData::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_NamedData::SRead(p,f,theSchema);
}
