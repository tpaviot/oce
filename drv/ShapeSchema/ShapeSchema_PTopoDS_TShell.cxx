#ifndef _ShapeSchema_PTopoDS_TShell_HeaderFile
#include <ShapeSchema_PTopoDS_TShell.hxx>
#endif
#ifndef _PTopoDS_TShell_HeaderFile
#include <PTopoDS_TShell.hxx>
#endif
#include <ShapeSchema_PTopoDS_TShell.ixx>
#ifndef _Storage_Schema_HeaderFile
#include <Storage_Schema.hxx>
#endif
#ifndef _Storage_stCONSTclCOM_HeaderFile
#include <Storage_stCONSTclCOM.hxx>
#endif

IMPLEMENT_STANDARD_HANDLE(ShapeSchema_PTopoDS_TShell,Storage_CallBack)
IMPLEMENT_STANDARD_RTTIEXT(ShapeSchema_PTopoDS_TShell,Storage_CallBack)

Handle(Standard_Persistent) ShapeSchema_PTopoDS_TShell::New() const
{
  return new PTopoDS_TShell(Storage_stCONSTclCOM());
}

void ShapeSchema_PTopoDS_TShell::SAdd(const Handle(PTopoDS_TShell)& p, const Handle(Storage_Schema)& theSchema)
{
  if (!p.IsNull()) {
    if (theSchema->AddPersistent(p,"PTopoDS_TShell")) {
         theSchema->PersistentToAdd(p->_CSFDB_GetPTopoDS_TShapemyShapes());

    }
  }
}

void ShapeSchema_PTopoDS_TShell::Add(const Handle(Standard_Persistent)& p, const Handle(Storage_Schema)& theSchema) const
{
  ShapeSchema_PTopoDS_TShell::SAdd((Handle(PTopoDS_TShell)&)p,theSchema);
}

void ShapeSchema_PTopoDS_TShell::SWrite(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TShell) &pp = (Handle(PTopoDS_TShell)&)p;
    theSchema->WritePersistentObjectHeader(p,f);

    (void)pp; // dummy to avoid compiler warning on unused arg
    
    f.BeginWritePersistentObjectData();
    theSchema->WritePersistentReference(pp->_CSFDB_GetPTopoDS_TShapemyShapes(),f);
  f.PutInteger(pp->_CSFDB_GetPTopoDS_TShapemyFlags());

    f.EndWritePersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TShell::Write(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const
{ 
  ShapeSchema_PTopoDS_TShell::SWrite(p,f,theSchema);
}


void ShapeSchema_PTopoDS_TShell::SRead(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema)
{ 
  if (!p.IsNull()) {
    Handle(PTopoDS_TShell) &pp = (Handle(PTopoDS_TShell)&)p;

    (void)pp; // dummy to avoid compiler warning on unused arg

    theSchema->ReadPersistentObjectHeader(f);
    f.BeginReadPersistentObjectData();

    Handle(PTopoDS_HArray1OfHShape) PTopoDS_TShapemyShapes;

    theSchema->ReadPersistentReference(PTopoDS_TShapemyShapes,f);
    pp->_CSFDB_SetPTopoDS_TShapemyShapes(PTopoDS_TShapemyShapes);

    Standard_Integer PTopoDS_TShapemyFlags;
    f.GetInteger(PTopoDS_TShapemyFlags);
    pp->_CSFDB_SetPTopoDS_TShapemyFlags(PTopoDS_TShapemyFlags);

    f.EndReadPersistentObjectData();
  }
}

void ShapeSchema_PTopoDS_TShell::Read(const Handle(Standard_Persistent)& p, Storage_BaseDriver& f, const Handle(Storage_Schema)& theSchema) const

{ 
  ShapeSchema_PTopoDS_TShell::SRead(p,f,theSchema);
}
