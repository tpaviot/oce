#ifndef _ShapeSchema_PCDMShape_Document_HeaderFile
#include <ShapeSchema_PCDMShape_Document.hxx>
#endif
#ifndef _PCDMShape_Document_HeaderFile
#include <PCDMShape_Document.hxx>
#endif
#include <ShapeSchema_PCDMShape_Document.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PCDMShape_Document,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PCDMShape_Document,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PCDMShape_Document::New() const
{
  return new PCDMShape_Document(Storage_stCONSTclCOM());
}

void ShapeSchema_PCDMShape_Document::SAdd(const Handle(PCDMShape_Document)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PCDMShape_Document")) {
         ShapeSchema_PTopoDS_Shape1::SAdd(p->_CSFDB_GetPCDMShape_DocumentmyShape(),theSchema);

    }
  }
}

void ShapeSchema_PCDMShape_Document::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PCDMShape_Document::SAdd((Handle(PCDMShape_Document)&)p,theSchema);
}

void ShapeSchema_PCDMShape_Document::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCDMShape_Document) &pp = (Handle(PCDMShape_Document)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    ShapeSchema_PTopoDS_Shape1::SWrite(pp->_CSFDB_GetPCDMShape_DocumentmyShape(),f,theSchema);

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PCDMShape_Document::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PCDMShape_Document::SWrite(p,f,theSchema);
}


void ShapeSchema_PCDMShape_Document::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PCDMShape_Document) &pp = (Handle(PCDMShape_Document)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    ShapeSchema_PTopoDS_Shape1::SRead((PTopoDS_Shape1&)pp->_CSFDB_GetPCDMShape_DocumentmyShape(),f,theSchema);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PCDMShape_Document::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PCDMShape_Document::SRead(p,f,theSchema);
}
