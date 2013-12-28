#ifndef _XCAFSchema_PXCAFDoc_Volume_HeaderFile
#include <XCAFSchema_PXCAFDoc_Volume.hxx>
#endif
#ifndef _PXCAFDoc_Volume_HeaderFile
#include <PXCAFDoc_Volume.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Volume.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Volume,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Volume,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Volume::New() const
{
  return new PXCAFDoc_Volume(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Volume::SAdd(const Handle(PXCAFDoc_Volume)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Volume")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_Volume::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Volume::SAdd((Handle(PXCAFDoc_Volume)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Volume::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Volume) &pp = (Handle(PXCAFDoc_Volume)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPXCAFDoc_VolumemyValue());

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Volume::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Volume::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Volume::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Volume) &pp = (Handle(PXCAFDoc_Volume)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PXCAFDoc_VolumemyValue;
    f.GetReal(PXCAFDoc_VolumemyValue);
    pp->_CSFDB_SetPXCAFDoc_VolumemyValue(PXCAFDoc_VolumemyValue);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Volume::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Volume::SRead(p,f,theSchema);
}
