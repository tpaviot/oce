#ifndef _StdLSchema_PDataStd_RealList_HeaderFile
#include <StdLSchema_PDataStd_RealList.hxx>
#endif
#ifndef _PDataStd_RealList_HeaderFile
#include <PDataStd_RealList.hxx>
#endif
#include <StdLSchema_PDataStd_RealList.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_RealList,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_RealList,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_RealList::New() const
{
  return new PDataStd_RealList(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_RealList::SAdd(const Handle(PDataStd_RealList)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_RealList")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_RealListmyValue());

    }
  }
}

void StdLSchema_PDataStd_RealList::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_RealList::SAdd((Handle(PDataStd_RealList)&)p,theSchema);
}

void StdLSchema_PDataStd_RealList::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_RealList) &pp = (Handle(PDataStd_RealList)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_RealListmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_RealList::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_RealList::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_RealList::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_RealList) &pp = (Handle(PDataStd_RealList)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfReal) PDataStd_RealListmyValue;

    theSchema->ReadPersistentReference(PDataStd_RealListmyValue,f);
    pp->_CSFDB_SetPDataStd_RealListmyValue(PDataStd_RealListmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_RealList::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_RealList::SRead(p,f,theSchema);
}
