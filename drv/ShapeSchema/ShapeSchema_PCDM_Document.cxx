#ifndef _ShapeSchema_PCDM_Document_HeaderFile
#include <ShapeSchema_PCDM_Document.hxx>
#endif
#ifndef _PCDM_Document_HeaderFile
#include <PCDM_Document.hxx>
#endif
#include <ShapeSchema_PCDM_Document.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PCDM_Document,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PCDM_Document,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PCDM_Document::New() const
{
  Handle(Standard_Persistent) NullObject;
  return NullObject;
}

void ShapeSchema_PCDM_Document::SAdd(const Handle(PCDM_Document)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PCDM_Document")) {
      
    }
  }
}

void ShapeSchema_PCDM_Document::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PCDM_Document::SAdd((Handle(PCDM_Document)&)p,theSchema);
}

void ShapeSchema_PCDM_Document::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    theSchema->WritePersistentObjectHeader(p,f);
    
    f.BeginWritePersistentObjectData();

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PCDM_Document::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PCDM_Document::SWrite(p,f,theSchema);
}


void ShapeSchema_PCDM_Document::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
  
    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PCDM_Document::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PCDM_Document::SRead(p,f,theSchema);
}
