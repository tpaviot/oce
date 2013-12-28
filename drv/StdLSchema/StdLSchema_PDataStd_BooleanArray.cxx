#ifndef _StdLSchema_PDataStd_BooleanArray_HeaderFile
#include <StdLSchema_PDataStd_BooleanArray.hxx>
#endif
#ifndef _PDataStd_BooleanArray_HeaderFile
#include <PDataStd_BooleanArray.hxx>
#endif
#include <StdLSchema_PDataStd_BooleanArray.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_BooleanArray,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_BooleanArray,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_BooleanArray::New() const
{
  return new PDataStd_BooleanArray(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_BooleanArray::SAdd(const Handle(PDataStd_BooleanArray)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_BooleanArray")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_BooleanArraymyValues());

    }
  }
}

void StdLSchema_PDataStd_BooleanArray::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_BooleanArray::SAdd((Handle(PDataStd_BooleanArray)&)p,theSchema);
}

void StdLSchema_PDataStd_BooleanArray::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_BooleanArray) &pp = (Handle(PDataStd_BooleanArray)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_BooleanArraymyValues(),f);
  f.PutInteger(pp->_CSFDB_GetPDataStd_BooleanArraymyLower());
  f.PutInteger(pp->_CSFDB_GetPDataStd_BooleanArraymyUpper());

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_BooleanArray::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_BooleanArray::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_BooleanArray::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_BooleanArray) &pp = (Handle(PDataStd_BooleanArray)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfInteger) PDataStd_BooleanArraymyValues;

    theSchema->ReadPersistentReference(PDataStd_BooleanArraymyValues,f);
    pp->_CSFDB_SetPDataStd_BooleanArraymyValues(PDataStd_BooleanArraymyValues);

    Standard_Integer PDataStd_BooleanArraymyLower;
    f.GetInteger(PDataStd_BooleanArraymyLower);
    pp->_CSFDB_SetPDataStd_BooleanArraymyLower(PDataStd_BooleanArraymyLower);

    Standard_Integer PDataStd_BooleanArraymyUpper;
    f.GetInteger(PDataStd_BooleanArraymyUpper);
    pp->_CSFDB_SetPDataStd_BooleanArraymyUpper(PDataStd_BooleanArraymyUpper);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_BooleanArray::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_BooleanArray::SRead(p,f,theSchema);
}
