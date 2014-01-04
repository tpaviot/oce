#ifndef _StdLSchema_PDF_TagSource_HeaderFile
#include <StdLSchema_PDF_TagSource.hxx>
#endif
#ifndef _PDF_TagSource_HeaderFile
#include <PDF_TagSource.hxx>
#endif
#include <StdLSchema_PDF_TagSource.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDF_TagSource,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDF_TagSource,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDF_TagSource::New() const
{
  return new PDF_TagSource(Storage_stCONSTclCOM());
}

void StdLSchema_PDF_TagSource::SAdd(const Handle(PDF_TagSource)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDF_TagSource")) {
      
    }
  }
}

void StdLSchema_PDF_TagSource::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDF_TagSource::SAdd((Handle(PDF_TagSource)&)p,theSchema);
}

void StdLSchema_PDF_TagSource::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_TagSource) &pp = (Handle(PDF_TagSource)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDF_TagSourcemyValue());

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDF_TagSource::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDF_TagSource::SWrite(p,f,theSchema);
}


void StdLSchema_PDF_TagSource::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_TagSource) &pp = (Handle(PDF_TagSource)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDF_TagSourcemyValue;
    f.GetInteger(PDF_TagSourcemyValue);
    pp->_CSFDB_SetPDF_TagSourcemyValue(PDF_TagSourcemyValue);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDF_TagSource::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDF_TagSource::SRead(p,f,theSchema);
}
