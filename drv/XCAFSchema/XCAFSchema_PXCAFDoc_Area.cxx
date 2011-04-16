#ifndef _XCAFSchema_PXCAFDoc_Area_HeaderFile
#include <XCAFSchema_PXCAFDoc_Area.hxx>
#endif
#ifndef _PXCAFDoc_Area_HeaderFile
#include <PXCAFDoc_Area.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Area.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Area,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Area,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Area::New() const
{
  return new PXCAFDoc_Area(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Area::SAdd(const Handle(PXCAFDoc_Area)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Area")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_Area::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Area::SAdd((Handle(PXCAFDoc_Area)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Area::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Area) &pp = (Handle(PXCAFDoc_Area)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
  f.PutReal(pp->_CSFDB_GetPXCAFDoc_AreamyValue());

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Area::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Area::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Area::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Area) &pp = (Handle(PXCAFDoc_Area)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Standard_Real PXCAFDoc_AreamyValue;
    f.GetReal(PXCAFDoc_AreamyValue);
    pp->_CSFDB_SetPXCAFDoc_AreamyValue(PXCAFDoc_AreamyValue);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Area::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Area::SRead(p,f,theSchema);
}
