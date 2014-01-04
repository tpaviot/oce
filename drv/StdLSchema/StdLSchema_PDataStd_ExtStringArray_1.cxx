#ifndef _StdLSchema_PDataStd_ExtStringArray_1_HeaderFile
#include <StdLSchema_PDataStd_ExtStringArray_1.hxx>
#endif
#ifndef _PDataStd_ExtStringArray_1_HeaderFile
#include <PDataStd_ExtStringArray_1.hxx>
#endif
#include <StdLSchema_PDataStd_ExtStringArray_1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_ExtStringArray_1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_ExtStringArray_1,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_ExtStringArray_1::New() const
{
  return new PDataStd_ExtStringArray_1(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_ExtStringArray_1::SAdd(const Handle(PDataStd_ExtStringArray_1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_ExtStringArray_1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ExtStringArray_1myValue());

    }
  }
}

void StdLSchema_PDataStd_ExtStringArray_1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_ExtStringArray_1::SAdd((Handle(PDataStd_ExtStringArray_1)&)p,theSchema);
}

void StdLSchema_PDataStd_ExtStringArray_1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ExtStringArray_1) &pp = (Handle(PDataStd_ExtStringArray_1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ExtStringArray_1myValue(),f);
  f.PutBoolean(pp->_CSFDB_GetPDataStd_ExtStringArray_1myDelta());

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_ExtStringArray_1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_ExtStringArray_1::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_ExtStringArray_1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ExtStringArray_1) &pp = (Handle(PDataStd_ExtStringArray_1)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfExtendedString) PDataStd_ExtStringArray_1myValue;

    theSchema->ReadPersistentReference(PDataStd_ExtStringArray_1myValue,f);
    pp->_CSFDB_SetPDataStd_ExtStringArray_1myValue(PDataStd_ExtStringArray_1myValue);

    Standard_Boolean PDataStd_ExtStringArray_1myDelta;
    f.GetBoolean(PDataStd_ExtStringArray_1myDelta);
    pp->_CSFDB_SetPDataStd_ExtStringArray_1myDelta(PDataStd_ExtStringArray_1myDelta);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_ExtStringArray_1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_ExtStringArray_1::SRead(p,f,theSchema);
}
