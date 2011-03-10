#ifndef _StdSchema_PPrsStd_AISPresentation_HeaderFile
#include <StdSchema_PPrsStd_AISPresentation.hxx>
#endif
#ifndef _PPrsStd_AISPresentation_HeaderFile
#include <PPrsStd_AISPresentation.hxx>
#endif
#include <StdSchema_PPrsStd_AISPresentation.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PPrsStd_AISPresentation,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PPrsStd_AISPresentation,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PPrsStd_AISPresentation::New() const
{
  return new PPrsStd_AISPresentation(Storage_stCONSTclCOM());
}

void StdSchema_PPrsStd_AISPresentation::SAdd(const Handle(PPrsStd_AISPresentation)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPrsStd_AISPresentation")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPPrsStd_AISPresentationmyDriverGUID());

    }
  }
}

void StdSchema_PPrsStd_AISPresentation::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PPrsStd_AISPresentation::SAdd((Handle(PPrsStd_AISPresentation)&)p,theSchema);
}

void StdSchema_PPrsStd_AISPresentation::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPrsStd_AISPresentation) &pp = (Handle(PPrsStd_AISPresentation)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPPrsStd_AISPresentationmyIsDisplayed());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPrsStd_AISPresentationmyDriverGUID(),f);
  f.PutReal(pp->_CSFDB_GetPPrsStd_AISPresentationmyTransparency());
  f.PutInteger(pp->_CSFDB_GetPPrsStd_AISPresentationmyColor());
  f.PutInteger(pp->_CSFDB_GetPPrsStd_AISPresentationmyMaterial());
  f.PutReal(pp->_CSFDB_GetPPrsStd_AISPresentationmyWidth());

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PPrsStd_AISPresentation::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PPrsStd_AISPresentation::SWrite(p,f,theSchema);
}


void StdSchema_PPrsStd_AISPresentation::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPrsStd_AISPresentation) &pp = (Handle(PPrsStd_AISPresentation)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PPrsStd_AISPresentationmyIsDisplayed;
    f.GetBoolean(PPrsStd_AISPresentationmyIsDisplayed);
    pp->_CSFDB_SetPPrsStd_AISPresentationmyIsDisplayed(PPrsStd_AISPresentationmyIsDisplayed);

    Handle(PCollection_HExtendedString) PPrsStd_AISPresentationmyDriverGUID;

    theSchema->ReadPersistentReference(PPrsStd_AISPresentationmyDriverGUID,f);
    pp->_CSFDB_SetPPrsStd_AISPresentationmyDriverGUID(PPrsStd_AISPresentationmyDriverGUID);

    Standard_Real PPrsStd_AISPresentationmyTransparency;
    f.GetReal(PPrsStd_AISPresentationmyTransparency);
    pp->_CSFDB_SetPPrsStd_AISPresentationmyTransparency(PPrsStd_AISPresentationmyTransparency);

    Standard_Integer PPrsStd_AISPresentationmyColor;
    f.GetInteger(PPrsStd_AISPresentationmyColor);
    pp->_CSFDB_SetPPrsStd_AISPresentationmyColor(PPrsStd_AISPresentationmyColor);

    Standard_Integer PPrsStd_AISPresentationmyMaterial;
    f.GetInteger(PPrsStd_AISPresentationmyMaterial);
    pp->_CSFDB_SetPPrsStd_AISPresentationmyMaterial(PPrsStd_AISPresentationmyMaterial);

    Standard_Real PPrsStd_AISPresentationmyWidth;
    f.GetReal(PPrsStd_AISPresentationmyWidth);
    pp->_CSFDB_SetPPrsStd_AISPresentationmyWidth(PPrsStd_AISPresentationmyWidth);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PPrsStd_AISPresentation::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PPrsStd_AISPresentation::SRead(p,f,theSchema);
}
