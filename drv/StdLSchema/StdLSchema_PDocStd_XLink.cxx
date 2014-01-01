#ifndef _StdLSchema_PDocStd_XLink_HeaderFile
#include <StdLSchema_PDocStd_XLink.hxx>
#endif
#ifndef _PDocStd_XLink_HeaderFile
#include <PDocStd_XLink.hxx>
#endif
#include <StdLSchema_PDocStd_XLink.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDocStd_XLink,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDocStd_XLink,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDocStd_XLink::New() const
{
  return new PDocStd_XLink(Storage_stCONSTclCOM());
}

void StdLSchema_PDocStd_XLink::SAdd(const Handle(PDocStd_XLink)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDocStd_XLink")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDocStd_XLinkmyDocEntry());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDocStd_XLinkmyLabEntry());

    }
  }
}

void StdLSchema_PDocStd_XLink::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDocStd_XLink::SAdd((Handle(PDocStd_XLink)&)p,theSchema);
}

void StdLSchema_PDocStd_XLink::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDocStd_XLink) &pp = (Handle(PDocStd_XLink)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDocStd_XLinkmyDocEntry(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDocStd_XLinkmyLabEntry(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDocStd_XLink::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDocStd_XLink::SWrite(p,f,theSchema);
}


void StdLSchema_PDocStd_XLink::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDocStd_XLink) &pp = (Handle(PDocStd_XLink)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) PDocStd_XLinkmyDocEntry;

    theSchema->ReadPersistentReference(PDocStd_XLinkmyDocEntry,f);
    pp->_CSFDB_SetPDocStd_XLinkmyDocEntry(PDocStd_XLinkmyDocEntry);

    Handle(PCollection_HAsciiString) PDocStd_XLinkmyLabEntry;

    theSchema->ReadPersistentReference(PDocStd_XLinkmyLabEntry,f);
    pp->_CSFDB_SetPDocStd_XLinkmyLabEntry(PDocStd_XLinkmyLabEntry);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDocStd_XLink::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDocStd_XLink::SRead(p,f,theSchema);
}
