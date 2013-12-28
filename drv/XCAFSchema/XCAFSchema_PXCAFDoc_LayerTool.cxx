#ifndef _XCAFSchema_PXCAFDoc_LayerTool_HeaderFile
#include <XCAFSchema_PXCAFDoc_LayerTool.hxx>
#endif
#ifndef _PXCAFDoc_LayerTool_HeaderFile
#include <PXCAFDoc_LayerTool.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_LayerTool.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_LayerTool,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_LayerTool,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_LayerTool::New() const
{
  return new PXCAFDoc_LayerTool(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_LayerTool::SAdd(const Handle(PXCAFDoc_LayerTool)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_LayerTool")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_LayerTool::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_LayerTool::SAdd((Handle(PXCAFDoc_LayerTool)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_LayerTool::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_LayerTool) &pp = (Handle(PXCAFDoc_LayerTool)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_LayerTool::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_LayerTool::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_LayerTool::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_LayerTool) &pp = (Handle(PXCAFDoc_LayerTool)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_LayerTool::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_LayerTool::SRead(p,f,theSchema);
}
