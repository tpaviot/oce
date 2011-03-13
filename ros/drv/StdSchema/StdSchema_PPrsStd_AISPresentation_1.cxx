#ifndef _StdSchema_PPrsStd_AISPresentation_1_HeaderFile
#include <StdSchema_PPrsStd_AISPresentation_1.hxx>
#endif
#ifndef _PPrsStd_AISPresentation_1_HeaderFile
#include <PPrsStd_AISPresentation_1.hxx>
#endif
#include <StdSchema_PPrsStd_AISPresentation_1.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(StdSchema_PPrsStd_AISPresentation_1,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(StdSchema_PPrsStd_AISPresentation_1,Storage_CallBack)

Handle(Standard_Persistent) StdSchema_PPrsStd_AISPresentation_1::New() const
{
  return new PPrsStd_AISPresentation_1(Storage_stCONSTclCOM());
}

void StdSchema_PPrsStd_AISPresentation_1::SAdd(const Handle(PPrsStd_AISPresentation_1)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PPrsStd_AISPresentation_1")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPPrsStd_AISPresentation_1myDriverGUID());

    }
  }
}

void StdSchema_PPrsStd_AISPresentation_1::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  StdSchema_PPrsStd_AISPresentation_1::SAdd((Handle(PPrsStd_AISPresentation_1)&)p,theSchema);
}

void StdSchema_PPrsStd_AISPresentation_1::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPrsStd_AISPresentation_1) &pp = (Handle(PPrsStd_AISPresentation_1)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutBoolean(pp->_CSFDB_GetPPrsStd_AISPresentation_1myIsDisplayed());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPPrsStd_AISPresentation_1myDriverGUID(),f);
  f.PutReal(pp->_CSFDB_GetPPrsStd_AISPresentation_1myTransparency());
  f.PutInteger(pp->_CSFDB_GetPPrsStd_AISPresentation_1myColor());
  f.PutInteger(pp->_CSFDB_GetPPrsStd_AISPresentation_1myMaterial());
  f.PutReal(pp->_CSFDB_GetPPrsStd_AISPresentation_1myWidth());
  f.PutInteger(pp->_CSFDB_GetPPrsStd_AISPresentation_1myMode());

    f.EndWritePersistentObjectData();
  }
}

void StdSchema_PPrsStd_AISPresentation_1::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  StdSchema_PPrsStd_AISPresentation_1::SWrite(p,f,theSchema);
}


void StdSchema_PPrsStd_AISPresentation_1::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PPrsStd_AISPresentation_1) &pp = (Handle(PPrsStd_AISPresentation_1)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Boolean PPrsStd_AISPresentation_1myIsDisplayed;
    f.GetBoolean(PPrsStd_AISPresentation_1myIsDisplayed);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myIsDisplayed(PPrsStd_AISPresentation_1myIsDisplayed);

    Handle(PCollection_HExtendedString) PPrsStd_AISPresentation_1myDriverGUID;

    theSchema->ReadPersistentReference(PPrsStd_AISPresentation_1myDriverGUID,f);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myDriverGUID(PPrsStd_AISPresentation_1myDriverGUID);

    Standard_Real PPrsStd_AISPresentation_1myTransparency;
    f.GetReal(PPrsStd_AISPresentation_1myTransparency);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myTransparency(PPrsStd_AISPresentation_1myTransparency);

    Standard_Integer PPrsStd_AISPresentation_1myColor;
    f.GetInteger(PPrsStd_AISPresentation_1myColor);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myColor(PPrsStd_AISPresentation_1myColor);

    Standard_Integer PPrsStd_AISPresentation_1myMaterial;
    f.GetInteger(PPrsStd_AISPresentation_1myMaterial);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myMaterial(PPrsStd_AISPresentation_1myMaterial);

    Standard_Real PPrsStd_AISPresentation_1myWidth;
    f.GetReal(PPrsStd_AISPresentation_1myWidth);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myWidth(PPrsStd_AISPresentation_1myWidth);

    Standard_Integer PPrsStd_AISPresentation_1myMode;
    f.GetInteger(PPrsStd_AISPresentation_1myMode);
    pp->_CSFDB_SetPPrsStd_AISPresentation_1myMode(PPrsStd_AISPresentation_1myMode);

    f.EndReadPersistentObjectData();
  }
}

void StdSchema_PPrsStd_AISPresentation_1::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  StdSchema_PPrsStd_AISPresentation_1::SRead(p,f,theSchema);
}
