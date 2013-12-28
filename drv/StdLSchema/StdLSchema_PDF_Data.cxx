#ifndef _StdLSchema_PDF_Data_HeaderFile
#include <StdLSchema_PDF_Data.hxx>
#endif
#ifndef _PDF_Data_HeaderFile
#include <PDF_Data.hxx>
#endif
#include <StdLSchema_PDF_Data.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdLSchema_PDF_Data,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdLSchema_PDF_Data,Storage_CallBack)

Handle(Standard_Persistent) StdLSchema_PDF_Data::New() const
{
  return new PDF_Data(Storage_stCONSTclCOM());
}

void StdLSchema_PDF_Data::SAdd(const Handle(PDF_Data)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDF_Data")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPDF_DatamyLabels());
   theSchema->PersistentToAdd(p->_CSFDB_GetPDF_DatamyAttributes());

    }
  }
}

void StdLSchema_PDF_Data::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdLSchema_PDF_Data::SAdd((Handle(PDF_Data)&)p,theSchema);
}

void StdLSchema_PDF_Data::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_Data) &pp = (Handle(PDF_Data)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDF_DatamyVersion());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDF_DatamyLabels(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPDF_DatamyAttributes(),f);

    f.EndWritePersistentObjectData();
  }
}

void StdLSchema_PDF_Data::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdLSchema_PDF_Data::SWrite(p,f,theSchema);
}


void StdLSchema_PDF_Data::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_Data) &pp = (Handle(PDF_Data)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDF_DatamyVersion;
    f.GetInteger(PDF_DatamyVersion);
    pp->_CSFDB_SetPDF_DatamyVersion(PDF_DatamyVersion);

    Handle(PColStd_HArray1OfInteger) PDF_DatamyLabels;

    theSchema->ReadPersistentReference(PDF_DatamyLabels,f);
    pp->_CSFDB_SetPDF_DatamyLabels(PDF_DatamyLabels);

    Handle(PDF_HAttributeArray1) PDF_DatamyAttributes;

    theSchema->ReadPersistentReference(PDF_DatamyAttributes,f);
    pp->_CSFDB_SetPDF_DatamyAttributes(PDF_DatamyAttributes);

    f.EndReadPersistentObjectData();
  }
}

void StdLSchema_PDF_Data::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdLSchema_PDF_Data::SRead(p,f,theSchema);
}
