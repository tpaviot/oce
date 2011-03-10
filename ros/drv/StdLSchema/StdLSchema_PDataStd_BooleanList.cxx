#ifndef _StdLSchema_PDataStd_BooleanList_HeaderFile
#include <StdLSchema_PDataStd_BooleanList.hxx>
#endif
#ifndef _PDataStd_BooleanList_HeaderFile
#include <PDataStd_BooleanList.hxx>
#endif
#include <StdLSchema_PDataStd_BooleanList.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_BooleanList,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_BooleanList,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_BooleanList::New() const
{
  return new PDataStd_BooleanList(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_BooleanList::SAdd(const Handle(PDataStd_BooleanList)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_BooleanList")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_BooleanListmyValue());

    }
  }
}

void StdLSchema_PDataStd_BooleanList::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_BooleanList::SAdd((Handle(PDataStd_BooleanList)&)p,theSchema);
}

void StdLSchema_PDataStd_BooleanList::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_BooleanList) &pp = (Handle(PDataStd_BooleanList)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_BooleanListmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_BooleanList::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_BooleanList::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_BooleanList::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_BooleanList) &pp = (Handle(PDataStd_BooleanList)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfInteger) PDataStd_BooleanListmyValue;

    theSchema->ReadPersistentReference(PDataStd_BooleanListmyValue,f);
    pp->_CSFDB_SetPDataStd_BooleanListmyValue(PDataStd_BooleanListmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_BooleanList::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_BooleanList::SRead(p,f,theSchema);
}
