#ifndef _XCAFSchema_PXCAFDoc_Color_HeaderFile
#include <XCAFSchema_PXCAFDoc_Color.hxx>
#endif
#ifndef _PXCAFDoc_Color_HeaderFile
#include <PXCAFDoc_Color.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_Color.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_Color,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_Color,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_Color::New() const
{
  return new PXCAFDoc_Color(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_Color::SAdd(const Handle(PXCAFDoc_Color)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_Color")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_Color::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_Color::SAdd((Handle(PXCAFDoc_Color)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_Color::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Color) &pp = (Handle(PXCAFDoc_Color)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    XCAFSchema_Quantity_Color::SWrite(pp->_CSFDB_GetPXCAFDoc_ColormyColor(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Color::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_Color::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_Color::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_Color) &pp = (Handle(PXCAFDoc_Color)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    XCAFSchema_Quantity_Color::SRead((Quantity_Color&)pp->_CSFDB_GetPXCAFDoc_ColormyColor(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_Color::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_Color::SRead(p,f,theSchema);
}
