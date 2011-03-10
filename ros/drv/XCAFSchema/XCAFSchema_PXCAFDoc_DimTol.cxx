#ifndef _XCAFSchema_PXCAFDoc_DimTol_HeaderFile
#include <XCAFSchema_PXCAFDoc_DimTol.hxx>
#endif
#ifndef _PXCAFDoc_DimTol_HeaderFile
#include <PXCAFDoc_DimTol.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_DimTol.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_DimTol,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_DimTol,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_DimTol::New() const
{
  return new PXCAFDoc_DimTol(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_DimTol::SAdd(const Handle(PXCAFDoc_DimTol)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_DimTol")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_DimTolmyVal());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_DimTolmyName());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_DimTolmyDescr());

    }
  }
}

void XCAFSchema_PXCAFDoc_DimTol::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_DimTol::SAdd((Handle(PXCAFDoc_DimTol)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_DimTol::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_DimTol) &pp = (Handle(PXCAFDoc_DimTol)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutInteger(pp->_CSFDB_GetPXCAFDoc_DimTolmyKind());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_DimTolmyVal(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_DimTolmyName(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_DimTolmyDescr(),f);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_DimTol::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_DimTol::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_DimTol::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_DimTol) &pp = (Handle(PXCAFDoc_DimTol)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Integer PXCAFDoc_DimTolmyKind;
    f.GetInteger(PXCAFDoc_DimTolmyKind);
    pp->_CSFDB_SetPXCAFDoc_DimTolmyKind(PXCAFDoc_DimTolmyKind);

    Handle(PColStd_HArray1OfReal) PXCAFDoc_DimTolmyVal;

    theSchema->ReadPersistentReference(PXCAFDoc_DimTolmyVal,f);
    pp->_CSFDB_SetPXCAFDoc_DimTolmyVal(PXCAFDoc_DimTolmyVal);

    Handle(PCollection_HAsciiString) PXCAFDoc_DimTolmyName;

    theSchema->ReadPersistentReference(PXCAFDoc_DimTolmyName,f);
    pp->_CSFDB_SetPXCAFDoc_DimTolmyName(PXCAFDoc_DimTolmyName);

    Handle(PCollection_HAsciiString) PXCAFDoc_DimTolmyDescr;

    theSchema->ReadPersistentReference(PXCAFDoc_DimTolmyDescr,f);
    pp->_CSFDB_SetPXCAFDoc_DimTolmyDescr(PXCAFDoc_DimTolmyDescr);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_DimTol::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_DimTol::SRead(p,f,theSchema);
}
