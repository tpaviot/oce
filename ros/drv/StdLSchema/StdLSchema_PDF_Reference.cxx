#ifndef _StdLSchema_PDF_Reference_HeaderFile
#include <StdLSchema_PDF_Reference.hxx>
#endif
#ifndef _PDF_Reference_HeaderFile
#include <PDF_Reference.hxx>
#endif
#include <StdLSchema_PDF_Reference.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDF_Reference,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDF_Reference,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDF_Reference::New() const
{
  return new PDF_Reference(Storage_stCONSTclCOM());
}

void StdLSchema_PDF_Reference::SAdd(const Handle(PDF_Reference)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDF_Reference")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDF_ReferencemyValue());

    }
  }
}

void StdLSchema_PDF_Reference::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDF_Reference::SAdd((Handle(PDF_Reference)&)p,theSchema);
}

void StdLSchema_PDF_Reference::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_Reference) &pp = (Handle(PDF_Reference)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDF_ReferencemyValue(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDF_Reference::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDF_Reference::SWrite(p,f,theSchema);
}


void StdLSchema_PDF_Reference::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_Reference) &pp = (Handle(PDF_Reference)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) PDF_ReferencemyValue;

    theSchema->ReadPersistentReference(PDF_ReferencemyValue,f);
    pp->_CSFDB_SetPDF_ReferencemyValue(PDF_ReferencemyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDF_Reference::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDF_Reference::SRead(p,f,theSchema);
}
