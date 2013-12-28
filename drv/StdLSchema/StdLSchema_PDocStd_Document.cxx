#ifndef _StdLSchema_PDocStd_Document_HeaderFile
#include <StdLSchema_PDocStd_Document.hxx>
#endif
#ifndef _PDocStd_Document_HeaderFile
#include <PDocStd_Document.hxx>
#endif
#include <StdLSchema_PDocStd_Document.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDocStd_Document,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDocStd_Document,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDocStd_Document::New() const
{
  return new PDocStd_Document(Storage_stCONSTclCOM());
}

void StdLSchema_PDocStd_Document::SAdd(const Handle(PDocStd_Document)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDocStd_Document")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDocStd_DocumentmyData());

    }
  }
}

void StdLSchema_PDocStd_Document::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDocStd_Document::SAdd((Handle(PDocStd_Document)&)p,theSchema);
}

void StdLSchema_PDocStd_Document::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDocStd_Document) &pp = (Handle(PDocStd_Document)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDocStd_DocumentmyData(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDocStd_Document::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDocStd_Document::SWrite(p,f,theSchema);
}


void StdLSchema_PDocStd_Document::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDocStd_Document) &pp = (Handle(PDocStd_Document)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PDF_Data) PDocStd_DocumentmyData;

    theSchema->ReadPersistentReference(PDocStd_DocumentmyData,f);
    pp->_CSFDB_SetPDocStd_DocumentmyData(PDocStd_DocumentmyData);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDocStd_Document::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDocStd_Document::SRead(p,f,theSchema);
}
