#ifndef _StdLSchema_PDataStd_ReferenceList_HeaderFile
#include <StdLSchema_PDataStd_ReferenceList.hxx>
#endif
#ifndef _PDataStd_ReferenceList_HeaderFile
#include <PDataStd_ReferenceList.hxx>
#endif
#include <StdLSchema_PDataStd_ReferenceList.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_ReferenceList,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_ReferenceList,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_ReferenceList::New() const
{
  return new PDataStd_ReferenceList(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_ReferenceList::SAdd(const Handle(PDataStd_ReferenceList)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_ReferenceList")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ReferenceListmyValue());

    }
  }
}

void StdLSchema_PDataStd_ReferenceList::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_ReferenceList::SAdd((Handle(PDataStd_ReferenceList)&)p,theSchema);
}

void StdLSchema_PDataStd_ReferenceList::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ReferenceList) &pp = (Handle(PDataStd_ReferenceList)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ReferenceListmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_ReferenceList::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_ReferenceList::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_ReferenceList::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ReferenceList) &pp = (Handle(PDataStd_ReferenceList)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfExtendedString) PDataStd_ReferenceListmyValue;

    theSchema->ReadPersistentReference(PDataStd_ReferenceListmyValue,f);
    pp->_CSFDB_SetPDataStd_ReferenceListmyValue(PDataStd_ReferenceListmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_ReferenceList::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_ReferenceList::SRead(p,f,theSchema);
}
