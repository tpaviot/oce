#ifndef _StdLSchema_PDataStd_RealArray_HeaderFile
#include <StdLSchema_PDataStd_RealArray.hxx>
#endif
#ifndef _PDataStd_RealArray_HeaderFile
#include <PDataStd_RealArray.hxx>
#endif
#include <StdLSchema_PDataStd_RealArray.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_RealArray,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_RealArray,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_RealArray::New() const
{
  return new PDataStd_RealArray(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_RealArray::SAdd(const Handle(PDataStd_RealArray)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_RealArray")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_RealArraymyValue());

    }
  }
}

void StdLSchema_PDataStd_RealArray::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_RealArray::SAdd((Handle(PDataStd_RealArray)&)p,theSchema);
}

void StdLSchema_PDataStd_RealArray::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_RealArray) &pp = (Handle(PDataStd_RealArray)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_RealArraymyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_RealArray::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_RealArray::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_RealArray::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_RealArray) &pp = (Handle(PDataStd_RealArray)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfReal) PDataStd_RealArraymyValue;

    theSchema->ReadPersistentReference(PDataStd_RealArraymyValue,f);
    pp->_CSFDB_SetPDataStd_RealArraymyValue(PDataStd_RealArraymyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_RealArray::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_RealArray::SRead(p,f,theSchema);
}
