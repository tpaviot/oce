#ifndef _XCAFSchema_PXCAFDoc_ShapeTool_HeaderFile
#include <XCAFSchema_PXCAFDoc_ShapeTool.hxx>
#endif
#ifndef _PXCAFDoc_ShapeTool_HeaderFile
#include <PXCAFDoc_ShapeTool.hxx>
#endif
#include <XCAFSchema_PXCAFDoc_ShapeTool.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PXCAFDoc_ShapeTool,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PXCAFDoc_ShapeTool,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PXCAFDoc_ShapeTool::New() const
{
  return new PXCAFDoc_ShapeTool(Storage_stCONSTclCOM());
}

void XCAFSchema_PXCAFDoc_ShapeTool::SAdd(const Handle(PXCAFDoc_ShapeTool)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PXCAFDoc_ShapeTool")) {
      
    }
  }
}

void XCAFSchema_PXCAFDoc_ShapeTool::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PXCAFDoc_ShapeTool::SAdd((Handle(PXCAFDoc_ShapeTool)&)p,theSchema);
}

void XCAFSchema_PXCAFDoc_ShapeTool::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_ShapeTool) &pp = (Handle(PXCAFDoc_ShapeTool)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_ShapeTool::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PXCAFDoc_ShapeTool::SWrite(p,f,theSchema);
}


void XCAFSchema_PXCAFDoc_ShapeTool::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PXCAFDoc_ShapeTool) &pp = (Handle(PXCAFDoc_ShapeTool)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PXCAFDoc_ShapeTool::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PXCAFDoc_ShapeTool::SRead(p,f,theSchema);
}
