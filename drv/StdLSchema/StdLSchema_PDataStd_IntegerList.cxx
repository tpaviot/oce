#ifndef _StdLSchema_PDataStd_IntegerList_HeaderFile
#include <StdLSchema_PDataStd_IntegerList.hxx>
#endif
#ifndef _PDataStd_IntegerList_HeaderFile
#include <PDataStd_IntegerList.hxx>
#endif
#include <StdLSchema_PDataStd_IntegerList.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_IntegerList,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_IntegerList,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_IntegerList::New() const
{
  return new PDataStd_IntegerList(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_IntegerList::SAdd(const Handle(PDataStd_IntegerList)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_IntegerList")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_IntegerListmyValue());

    }
  }
}

void StdLSchema_PDataStd_IntegerList::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_IntegerList::SAdd((Handle(PDataStd_IntegerList)&)p,theSchema);
}

void StdLSchema_PDataStd_IntegerList::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_IntegerList) &pp = (Handle(PDataStd_IntegerList)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_IntegerListmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_IntegerList::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_IntegerList::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_IntegerList::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_IntegerList) &pp = (Handle(PDataStd_IntegerList)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfInteger) PDataStd_IntegerListmyValue;

    theSchema->ReadPersistentReference(PDataStd_IntegerListmyValue,f);
    pp->_CSFDB_SetPDataStd_IntegerListmyValue(PDataStd_IntegerListmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_IntegerList::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_IntegerList::SRead(p,f,theSchema);
}
