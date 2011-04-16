#ifndef _XCAFSchema_PMMgt_PManaged_HeaderFile
#include <XCAFSchema_PMMgt_PManaged.hxx>
#endif
#ifndef _PMMgt_PManaged_HeaderFile
#include <PMMgt_PManaged.hxx>
#endif
#include <XCAFSchema_PMMgt_PManaged.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(XCAFSchema_PMMgt_PManaged,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(XCAFSchema_PMMgt_PManaged,Storage_CallBack)

Handle(Standard_Persistent) XCAFSchema_PMMgt_PManaged::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void XCAFSchema_PMMgt_PManaged::SAdd(const Handle(PMMgt_PManaged)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PMMgt_PManaged")) {
      
    }
  }
}

void XCAFSchema_PMMgt_PManaged::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  XCAFSchema_PMMgt_PManaged::SAdd((Handle(PMMgt_PManaged)&)p,theSchema);
}

void XCAFSchema_PMMgt_PManaged::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PMMgt_PManaged) &pp = (Handle(PMMgt_PManaged)&)p;
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void XCAFSchema_PMMgt_PManaged::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  XCAFSchema_PMMgt_PManaged::SWrite(p,f,theSchema);
}


void XCAFSchema_PMMgt_PManaged::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PMMgt_PManaged) &pp = (Handle(PMMgt_PManaged)&)p;

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void XCAFSchema_PMMgt_PManaged::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  XCAFSchema_PMMgt_PManaged::SRead(p,f,theSchema);
}
