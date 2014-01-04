#ifndef _StdLSchema_PDataStd_IntegerArray_HeaderFile
#include <StdLSchema_PDataStd_IntegerArray.hxx>
#endif
#ifndef _PDataStd_IntegerArray_HeaderFile
#include <PDataStd_IntegerArray.hxx>
#endif
#include <StdLSchema_PDataStd_IntegerArray.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_IntegerArray,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_IntegerArray,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_IntegerArray::New() const
{
  return new PDataStd_IntegerArray(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_IntegerArray::SAdd(const Handle(PDataStd_IntegerArray)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_IntegerArray")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_IntegerArraymyValue());

    }
  }
}

void StdLSchema_PDataStd_IntegerArray::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_IntegerArray::SAdd((Handle(PDataStd_IntegerArray)&)p,theSchema);
}

void StdLSchema_PDataStd_IntegerArray::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_IntegerArray) &pp = (Handle(PDataStd_IntegerArray)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_IntegerArraymyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_IntegerArray::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_IntegerArray::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_IntegerArray::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_IntegerArray) &pp = (Handle(PDataStd_IntegerArray)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfInteger) PDataStd_IntegerArraymyValue;

    theSchema->ReadPersistentReference(PDataStd_IntegerArraymyValue,f);
    pp->_CSFDB_SetPDataStd_IntegerArraymyValue(PDataStd_IntegerArraymyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_IntegerArray::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_IntegerArray::SRead(p,f,theSchema);
}
