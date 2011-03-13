#ifndef _StdLSchema_PDataStd_ExtStringArray_HeaderFile
#include <StdLSchema_PDataStd_ExtStringArray.hxx>
#endif
#ifndef _PDataStd_ExtStringArray_HeaderFile
#include <PDataStd_ExtStringArray.hxx>
#endif
#include <StdLSchema_PDataStd_ExtStringArray.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_ExtStringArray,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_ExtStringArray,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_ExtStringArray::New() const
{
  return new PDataStd_ExtStringArray(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_ExtStringArray::SAdd(const Handle(PDataStd_ExtStringArray)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_ExtStringArray")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ExtStringArraymyValue());

    }
  }
}

void StdLSchema_PDataStd_ExtStringArray::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_ExtStringArray::SAdd((Handle(PDataStd_ExtStringArray)&)p,theSchema);
}

void StdLSchema_PDataStd_ExtStringArray::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ExtStringArray) &pp = (Handle(PDataStd_ExtStringArray)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ExtStringArraymyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_ExtStringArray::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_ExtStringArray::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_ExtStringArray::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ExtStringArray) &pp = (Handle(PDataStd_ExtStringArray)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfExtendedString) PDataStd_ExtStringArraymyValue;

    theSchema->ReadPersistentReference(PDataStd_ExtStringArraymyValue,f);
    pp->_CSFDB_SetPDataStd_ExtStringArraymyValue(PDataStd_ExtStringArraymyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_ExtStringArray::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_ExtStringArray::SRead(p,f,theSchema);
}
