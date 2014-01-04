#ifndef _XCAFSchema_PXCAFDoc_MaterialTool_HeaderFile
#include <XCAFSchema_PXCAFDoc_MaterialTool.hxx>
#endif
#ifndef _PXCAFDoc_MaterialTool_HeaderFile
#include <PXCAFDoc_MaterialTool.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_MaterialTool.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_MaterialTool,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_MaterialTool,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_MaterialTool::New() const
{
  return new PXCAFDoc_MaterialTool(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_MaterialTool::SAdd(const Handle(PXCAFDoc_MaterialTool)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_MaterialTool")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_MaterialTool::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_MaterialTool::SAdd((Handle(PXCAFDoc_MaterialTool)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_MaterialTool::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_MaterialTool) &pp = (Handle(PXCAFDoc_MaterialTool)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_MaterialTool::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_MaterialTool::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_MaterialTool::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_MaterialTool) &pp = (Handle(PXCAFDoc_MaterialTool)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_MaterialTool::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_MaterialTool::SRead(p,f,theSchema);
}
