#ifndef _XCAFSchema_PXCAFDoc_DocumentTool_HeaderFile
#include <XCAFSchema_PXCAFDoc_DocumentTool.hxx>
#endif
#ifndef _PXCAFDoc_DocumentTool_HeaderFile
#include <PXCAFDoc_DocumentTool.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_DocumentTool.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_DocumentTool,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_DocumentTool,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_DocumentTool::New() const
{
  return new PXCAFDoc_DocumentTool(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_DocumentTool::SAdd(const Handle(PXCAFDoc_DocumentTool)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_DocumentTool")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_DocumentTool::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_DocumentTool::SAdd((Handle(PXCAFDoc_DocumentTool)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_DocumentTool::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_DocumentTool) &pp = (Handle(PXCAFDoc_DocumentTool)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_DocumentTool::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_DocumentTool::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_DocumentTool::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_DocumentTool) &pp = (Handle(PXCAFDoc_DocumentTool)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_DocumentTool::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_DocumentTool::SRead(p,f,theSchema);
}
