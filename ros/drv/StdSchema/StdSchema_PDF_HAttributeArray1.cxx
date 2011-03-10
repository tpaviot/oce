#ifndef _StdSchema_PDF_HAttributeArray1_HeaderFile
#include <StdSchema_PDF_HAttributeArray1.hxx>
#endif
#ifndef _PDF_HAttributeArray1_HeaderFile
#include <PDF_HAttributeArray1.hxx>
#endif
#include <StdSchema_PDF_HAttributeArray1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PDF_HAttributeArray1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PDF_HAttributeArray1,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PDF_HAttributeArray1::New() const
{
  return new PDF_HAttributeArray1(Storage_stCONSTclCOM());
}

void StdSchema_PDF_HAttributeArray1::SAdd(const Handle(PDF_HAttributeArray1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PDF_HAttributeArray1")) {
         StdSchema_PDF_FieldOfHAttributeArray1::SAdd(p->_CSFDB_GetPDF_HAttributeArray1Data(),theSchema);

    }
  }
}

void StdSchema_PDF_HAttributeArray1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PDF_HAttributeArray1::SAdd((Handle(PDF_HAttributeArray1)&)p,theSchema);
}

void StdSchema_PDF_HAttributeArray1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_HAttributeArray1) &pp = (Handle(PDF_HAttributeArray1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPDF_HAttributeArray1LowerBound());
  f.PutInteger(pp->_CSFDB_GetPDF_HAttributeArray1UpperBound());
    StdSchema_PDF_FieldOfHAttributeArray1::SWrite(pp->_CSFDB_GetPDF_HAttributeArray1Data(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PDF_HAttributeArray1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PDF_HAttributeArray1::SWrite(p,f,theSchema);
}


void StdSchema_PDF_HAttributeArray1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PDF_HAttributeArray1) &pp = (Handle(PDF_HAttributeArray1)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PDF_HAttributeArray1LowerBound;
    f.GetInteger(PDF_HAttributeArray1LowerBound);
    pp->_CSFDB_SetPDF_HAttributeArray1LowerBound(PDF_HAttributeArray1LowerBound);

    Standard_Integer PDF_HAttributeArray1UpperBound;
    f.GetInteger(PDF_HAttributeArray1UpperBound);
    pp->_CSFDB_SetPDF_HAttributeArray1UpperBound(PDF_HAttributeArray1UpperBound);

    StdSchema_PDF_FieldOfHAttributeArray1::SRead((PDF_FieldOfHAttributeArray1&)pp->_CSFDB_GetPDF_HAttributeArray1Data(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PDF_HAttributeArray1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PDF_HAttributeArray1::SRead(p,f,theSchema);
}
