#ifndef _XCAFSchema_PXCAFDoc_DimTolTool_HeaderFile
#include <XCAFSchema_PXCAFDoc_DimTolTool.hxx>
#endif
#ifndef _PXCAFDoc_DimTolTool_HeaderFile
#include <PXCAFDoc_DimTolTool.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_DimTolTool.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_DimTolTool,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_DimTolTool,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_DimTolTool::New() const
{
  return new PXCAFDoc_DimTolTool(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_DimTolTool::SAdd(const Handle(PXCAFDoc_DimTolTool)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_DimTolTool")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_DimTolTool::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_DimTolTool::SAdd((Handle(PXCAFDoc_DimTolTool)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_DimTolTool::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_DimTolTool) &pp = (Handle(PXCAFDoc_DimTolTool)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_DimTolTool::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_DimTolTool::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_DimTolTool::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_DimTolTool) &pp = (Handle(PXCAFDoc_DimTolTool)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_DimTolTool::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_DimTolTool::SRead(p,f,theSchema);
}
