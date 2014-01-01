#ifndef _StdLSchema_PDataStd_ExtStringList_HeaderFile
#include <StdLSchema_PDataStd_ExtStringList.hxx>
#endif
#ifndef _PDataStd_ExtStringList_HeaderFile
#include <PDataStd_ExtStringList.hxx>
#endif
#include <StdLSchema_PDataStd_ExtStringList.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDataStd_ExtStringList,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDataStd_ExtStringList,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDataStd_ExtStringList::New() const
{
  return new PDataStd_ExtStringList(Storage_stCONSTclCOM());
}

void StdLSchema_PDataStd_ExtStringList::SAdd(const Handle(PDataStd_ExtStringList)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDataStd_ExtStringList")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDataStd_ExtStringListmyValue());

    }
  }
}

void StdLSchema_PDataStd_ExtStringList::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDataStd_ExtStringList::SAdd((Handle(PDataStd_ExtStringList)&)p,theSchema);
}

void StdLSchema_PDataStd_ExtStringList::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ExtStringList) &pp = (Handle(PDataStd_ExtStringList)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDataStd_ExtStringListmyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDataStd_ExtStringList::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDataStd_ExtStringList::SWrite(p,f,theSchema);
}


void StdLSchema_PDataStd_ExtStringList::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDataStd_ExtStringList) &pp = (Handle(PDataStd_ExtStringList)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PColStd_HArray1OfExtendedString) PDataStd_ExtStringListmyValue;

    theSchema->ReadPersistentReference(PDataStd_ExtStringListmyValue,f);
    pp->_CSFDB_SetPDataStd_ExtStringListmyValue(PDataStd_ExtStringListmyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDataStd_ExtStringList::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDataStd_ExtStringList::SRead(p,f,theSchema);
}
