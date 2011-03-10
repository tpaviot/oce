#ifndef _XCAFSchema_PXCAFDoc_Location_HeaderFile
#include <XCAFSchema_PXCAFDoc_Location.hxx>
#endif
#ifndef _PXCAFDoc_Location_HeaderFile
#include <PXCAFDoc_Location.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Location.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Location,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Location,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Location::New() const
{
  return new PXCAFDoc_Location(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Location::SAdd(const Handle(PXCAFDoc_Location)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Location")) {
         XCAFSchema_PTopLoc_Location::SAdd(p->_CSFDB_GetPXCAFDoc_LocationmyPLocation(),theSchema);

    }
  }
}

void XCAFSchema_PXCAFDoc_Location::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Location::SAdd((Handle(PXCAFDoc_Location)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Location::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Location) &pp = (Handle(PXCAFDoc_Location)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();
    XCAFSchema_PTopLoc_Location::SWrite(pp->_CSFDB_GetPXCAFDoc_LocationmyPLocation(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Location::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Location::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Location::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Location) &pp = (Handle(PXCAFDoc_Location)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    XCAFSchema_PTopLoc_Location::SRead((PTopLoc_Location&)pp->_CSFDB_GetPXCAFDoc_LocationmyPLocation(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Location::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Location::SRead(p,f,theSchema);
}
