#ifndef _XCAFSchema_PXCAFDoc_Datum_HeaderFile
#include <XCAFSchema_PXCAFDoc_Datum.hxx>
#endif
#ifndef _PXCAFDoc_Datum_HeaderFile
#include <PXCAFDoc_Datum.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Datum.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Datum,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Datum,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Datum::New() const
{
  return new PXCAFDoc_Datum(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Datum::SAdd(const Handle(PXCAFDoc_Datum)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Datum")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_DatummyName());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_DatummyDescr());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_DatummyId());

    }
  }
}

void XCAFSchema_PXCAFDoc_Datum::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Datum::SAdd((Handle(PXCAFDoc_Datum)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Datum::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Datum) &pp = (Handle(PXCAFDoc_Datum)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_DatummyName(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_DatummyDescr(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_DatummyId(),f);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Datum::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Datum::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Datum::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Datum) &pp = (Handle(PXCAFDoc_Datum)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) PXCAFDoc_DatummyName;

    theSchema->ReadPersistentReference(PXCAFDoc_DatummyName,f);
    pp->_CSFDB_SetPXCAFDoc_DatummyName(PXCAFDoc_DatummyName);

    Handle(PCollection_HAsciiString) PXCAFDoc_DatummyDescr;

    theSchema->ReadPersistentReference(PXCAFDoc_DatummyDescr,f);
    pp->_CSFDB_SetPXCAFDoc_DatummyDescr(PXCAFDoc_DatummyDescr);

    Handle(PCollection_HAsciiString) PXCAFDoc_DatummyId;

    theSchema->ReadPersistentReference(PXCAFDoc_DatummyId,f);
    pp->_CSFDB_SetPXCAFDoc_DatummyId(PXCAFDoc_DatummyId);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Datum::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Datum::SRead(p,f,theSchema);
}
