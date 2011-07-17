#ifndef _StdLSchema_PDataStd_ReferenceArray_HeaderFile
#include <StdLSchema_PDataStd_ReferenceArray.hxx>
#endif
#ifndef _PDataStd_ReferenceArray_HeaderFile
#include <PDataStd_ReferenceArray.hxx>
#endif
#include <StdLSchema_PDataStd_ReferenceArray.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_ReferenceArray,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_ReferenceArray,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_ReferenceArray::New() const
{
  return new PDataStd_ReferenceArray(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_ReferenceArray::SAdd(const Handle(PDataStd_ReferenceArray)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_ReferenceArray")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ReferenceArraymyValue());

    }
  }
}

void StdLSchema_PDataStd_ReferenceArray::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_ReferenceArray::SAdd((Handle(PDataStd_ReferenceArray)&)p,theSchema);
}

void StdLSchema_PDataStd_ReferenceArray::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ReferenceArray) &pp = (Handle(PDataStd_ReferenceArray)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ReferenceArraymyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_ReferenceArray::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_ReferenceArray::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_ReferenceArray::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ReferenceArray) &pp = (Handle(PDataStd_ReferenceArray)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfExtendedString) PDataStd_ReferenceArraymyValue;

    theSchema->ReadPersistentReference(PDataStd_ReferenceArraymyValue,f);
    pp->_CSFDB_SetPDataStd_ReferenceArraymyValue(PDataStd_ReferenceArraymyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_ReferenceArray::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_ReferenceArray::SRead(p,f,theSchema);
}
