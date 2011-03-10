#ifndef _XCAFSchema_PXCAFDoc_ColorTool_HeaderFile
#include <XCAFSchema_PXCAFDoc_ColorTool.hxx>
#endif
#ifndef _PXCAFDoc_ColorTool_HeaderFile
#include <PXCAFDoc_ColorTool.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_ColorTool.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_ColorTool,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_ColorTool,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_ColorTool::New() const
{
  return new PXCAFDoc_ColorTool(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_ColorTool::SAdd(const Handle(PXCAFDoc_ColorTool)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_ColorTool")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_ColorTool::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_ColorTool::SAdd((Handle(PXCAFDoc_ColorTool)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_ColorTool::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_ColorTool) &pp = (Handle(PXCAFDoc_ColorTool)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_ColorTool::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_ColorTool::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_ColorTool::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_ColorTool) &pp = (Handle(PXCAFDoc_ColorTool)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_ColorTool::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_ColorTool::SRead(p,f,theSchema);
}
