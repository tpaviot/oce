#ifndef _XCAFSchema_PXCAFDoc_Material_HeaderFile
#include <XCAFSchema_PXCAFDoc_Material.hxx>
#endif
#ifndef _PXCAFDoc_Material_HeaderFile
#include <PXCAFDoc_Material.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Material.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Material,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Material,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Material::New() const
{
  return new PXCAFDoc_Material(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Material::SAdd(const Handle(PXCAFDoc_Material)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Material")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_MaterialmyName());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_MaterialmyDescr());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_MaterialmyDensName());
   theSchema->PersistentToAdd(p->_CSFDB_GetPXCAFDoc_MaterialmyDensValType());

    }
  }
}

void XCAFSchema_PXCAFDoc_Material::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Material::SAdd((Handle(PXCAFDoc_Material)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Material::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Material) &pp = (Handle(PXCAFDoc_Material)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_MaterialmyName(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_MaterialmyDescr(),f);
  f.PutReal(pp->_CSFDB_GetPXCAFDoc_MaterialmyDensity());
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_MaterialmyDensName(),f);
    theSchema->WritePersistentReference(pp->_CSFDB_GetPXCAFDoc_MaterialmyDensValType(),f);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Material::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Material::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Material::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Material) &pp = (Handle(PXCAFDoc_Material)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PCollection_HAsciiString) PXCAFDoc_MaterialmyName;

    theSchema->ReadPersistentReference(PXCAFDoc_MaterialmyName,f);
    pp->_CSFDB_SetPXCAFDoc_MaterialmyName(PXCAFDoc_MaterialmyName);

    Handle(PCollection_HAsciiString) PXCAFDoc_MaterialmyDescr;

    theSchema->ReadPersistentReference(PXCAFDoc_MaterialmyDescr,f);
    pp->_CSFDB_SetPXCAFDoc_MaterialmyDescr(PXCAFDoc_MaterialmyDescr);

    Standard_Real PXCAFDoc_MaterialmyDensity;
    f.GetReal(PXCAFDoc_MaterialmyDensity);
    pp->_CSFDB_SetPXCAFDoc_MaterialmyDensity(PXCAFDoc_MaterialmyDensity);

    Handle(PCollection_HAsciiString) PXCAFDoc_MaterialmyDensName;

    theSchema->ReadPersistentReference(PXCAFDoc_MaterialmyDensName,f);
    pp->_CSFDB_SetPXCAFDoc_MaterialmyDensName(PXCAFDoc_MaterialmyDensName);

    Handle(PCollection_HAsciiString) PXCAFDoc_MaterialmyDensValType;

    theSchema->ReadPersistentReference(PXCAFDoc_MaterialmyDensValType,f);
    pp->_CSFDB_SetPXCAFDoc_MaterialmyDensValType(PXCAFDoc_MaterialmyDensValType);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Material::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Material::SRead(p,f,theSchema);
}
